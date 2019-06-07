#include "one_wire.hpp"

namespace cm3cpp {

namespace extra {

OneWire::OneWire(Gpio::Pinout p, uint8_t tim_number, uint32_t tim_presc) :
  _pinout(p),
  _timer(tim_number)
{
    _timer.set_counter_direction(Timer::CounterDirection::UP);
    _timer.set_alignment(Timer::Alignment::EDGE);
    _timer.set_clock_division(Timer::ClockDivision::TIMER_CLOCK_MUL_1);
    _timer.set_prescaler_value(tim_presc);
    _timer.set_counter_mode(Timer::CounterMode::CONTINUOUS);
    _timer.disable_autoreload_preload();
    _timer.set_counter_value(0);

    _last_discrepancy = 0;
    _last_device = false;
    _last_family_discrepancy = 0;
}

uint8_t OneWire::read_byte(void)
{
    uint8_t data = 0;

    for (uint8_t bit_count = 0; bit_count < 8; bit_count++) {
        /*pull low to initiate read*/
        _pinout.mode_setup(Gpio::Mode::OUTPUT, Gpio::PullMode::PULL_UP);
        _pinout.set_output_options(Gpio::OutputType::OPEN_DRAIN,
                                   Gpio::Speed::FAST_50MHz);
        _pinout.clear();
        _wait(_LOW_PULSE_TIME_US);

        /*float high*/
        _pinout.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::PULL_UP);
        _wait(_READ_SAMPLE_WAIT_US);

        /*sample bus and shift into msb*/
        data = data >> 1;
        if (_pinout.get() != 0)
            data |= 0x80;

        /*wait until end of time slot*/
        _wait(_END_READ_SLOT_WAIT_US);
    }

    return data;
}

void OneWire::write_byte(uint8_t data)
{
    for (uint8_t bit_count = 0; bit_count < 8; bit_count++) {
        /*pull low to initiate write*/
        _pinout.mode_setup(Gpio::Mode::OUTPUT, Gpio::PullMode::PULL_UP);
        _pinout.set_output_options(Gpio::OutputType::OPEN_DRAIN,
                                   Gpio::Speed::FAST_50MHz);
        _pinout.clear();
        _wait(_LOW_PULSE_TIME_US);

        /*write next bit*/
        ((bool)(data & 0x01)) ? _pinout.set() : _pinout.clear();
        data = data >> 1;

        /*wait until end of slot*/
        _wait(_WRITE_SLOT_WAIT_US);

        /*float high and let device recover*/
        _pinout.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::PULL_UP);
        _wait(_RECOVERY_TIME_US);
    }
}

bool OneWire::read_bit(void)
{
    bool bit;

    /*pull low to initiate read*/
    _pinout.mode_setup(Gpio::Mode::OUTPUT, Gpio::PullMode::PULL_UP);
    _pinout.set_output_options(Gpio::OutputType::OPEN_DRAIN,
                               Gpio::Speed::FAST_50MHz);
    _pinout.clear();

    _wait(_LOW_PULSE_TIME_US);

    /*float high*/
    _pinout.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::PULL_UP);
    _wait(_READ_SAMPLE_WAIT_US);

    /*sample bus*/
    if (_pinout.get() > 0)
        bit = true;
    else
        bit = false;

    /*wait until end of time slot*/
    _wait(_END_READ_SLOT_WAIT_US);

    return bit;
}

void OneWire::write_bit(bool bit)
{
    /*pull low to initiate write*/
    _pinout.mode_setup(Gpio::Mode::OUTPUT, Gpio::PullMode::PULL_UP);
    _pinout.set_output_options(Gpio::OutputType::OPEN_DRAIN,
                               Gpio::Speed::FAST_50MHz);
    _pinout.clear();

    _wait(_LOW_PULSE_TIME_US);

    /*write next bit*/
    bit ? _pinout.set() : _pinout.clear();

    /*wait until end of slot*/
    _wait(_WRITE_SLOT_WAIT_US);

    /*float high and let device recover*/
    _pinout.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::PULL_UP);
    _wait(_RECOVERY_TIME_US);
}

bool OneWire::touch_reset(void)
{
    bool presence = false;
    char sample_count = (_RESET_PULSE_TIME_US / 8);

    /*low reset pulse*/
    _pinout.mode_setup(Gpio::Mode::OUTPUT, Gpio::PullMode::PULL_UP);
    _pinout.set_output_options(Gpio::OutputType::OPEN_DRAIN,
                               Gpio::Speed::FAST_50MHz);
    _pinout.clear();
    _wait(_RESET_PULSE_TIME_US);

    /*float high*/
    _pinout.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::PULL_UP);

    while (sample_count-- != 0) {
        _wait(8);

        /*sample bus to check for connected devices*/
        if (_pinout.get() == 0)
            presence = true;
    }

    return presence;
}

bool OneWire::search_first(bool do_reset, bool alarm_only)
{
    _last_discrepancy = 0;
    _last_device = false;
    _last_family_discrepancy = 0;
    return search_next(do_reset, alarm_only);
}

bool OneWire::search_next(bool do_reset, bool alarm_only)
{
    uint8_t bit_test, search_direction, bit_number;
    uint8_t last_zero, serial_byte_number;
    uint8_t serial_byte_mask;
    uint8_t lastcrc8 = 0;

    // initialize for search
    bit_number = 1;
    last_zero = 0;
    serial_byte_number = 0;
    serial_byte_mask = 1;
    bool next_result = 0;

    // if the last call was not the last one
    if (!_last_device) {
        // check if reset first is requested
        if (do_reset) {
            // reset the 1-wire
            // if there are no parts on 1-wire, return FALSE
            if (!touch_reset()) {
                _last_discrepancy = 0;
                _last_family_discrepancy = 0;
                return false;
            }
        }

        // If finding alarming devices issue a different command
        if (alarm_only)
            write_byte(_SEARCH_ALARM);  // issue the alarming search command
        else
            write_byte(_SEARCH);  // issue the search command

        // loop to do the search
        do {
            // read a bit and its compliment
            bit_test = ((uint8_t)read_bit()) << 1;
            bit_test |= ((uint8_t)read_bit());

            // check for no devices on 1-wire
            if (bit_test == 3)
                break;
            else {
                // all devices coupled have 0 or 1
                if (bit_test > 0)
                    search_direction =
                      !(bit_test & 0x01);  // bit write value for search
                else {
                    // if this discrepancy if before the Last Discrepancy
                    // on a previous next then pick the same as last time
                    if (bit_number < _last_discrepancy)
                        search_direction = ((_serial[serial_byte_number] &
                                             serial_byte_mask) > 0);
                    else
                        // if equal to last pick 1, if not then pick 0
                        search_direction = (bit_number == _last_discrepancy);

                    // if 0 was picked then record its position in LastZero
                    if (search_direction == 0) {
                        last_zero = bit_number;

                        // check for Last discrepancy in family
                        if (last_zero < 9)
                            _last_family_discrepancy = last_zero;
                    }
                }

                // set or clear the bit in the SerialNum[portnum] byte
                // serial_byte_number with mask serial_byte_mask
                if (search_direction == 1)
                    _serial[serial_byte_number] |= serial_byte_mask;
                else
                    _serial[serial_byte_number] &= ~serial_byte_mask;

                // serial number search direction write bit
                write_bit((bool)search_direction);

                // increment the byte counter bit_number
                // and shift the mask serial_byte_mask
                bit_number++;
                serial_byte_mask <<= 1;

                // if the mask is 0 then go to new SerialNum[portnum] byte
                // serial_byte_number and reset mask
                if (serial_byte_mask == 0) {
                    // The below has been added to accomidate the valid CRC with
                    // the possible changing serial number values of the
                    // DS28E04.
                    if (((_serial[0] & 0x7F) == 0x1C) &&
                        (serial_byte_number == 1))
                        _crc_check(0x7F, &lastcrc8);
                    else
                        _crc_check(_serial[serial_byte_number],
                                   &lastcrc8);  // accumulate the CRC

                    serial_byte_number++;
                    serial_byte_mask = 1;
                }
            }
        } while (serial_byte_number <
                 8);  // loop until through all SerialNum[portnum] bytes 0-7

        // if the search was successful then
        if (!((bit_number < 65) || lastcrc8)) {
            // search successful so set
            // LastDiscrepancy[portnum],LastDevice[portnum],next_result
            _last_discrepancy = last_zero;
            _last_device = (_last_discrepancy == 0);
            next_result = true;
        }
    }

    // if no device found then reset counters so next 'next' will be
    // like a first
    if (!next_result || !_serial[0]) {
        _last_discrepancy = 0;
        _last_device = false;
        _last_family_discrepancy = 0;
        next_result = false;
    }

    return next_result;
}

void OneWire::get_serial_number(uint8_t* sn_buffer, bool do_read)
{
    if (do_read)
        memcpy(sn_buffer, _serial, _SERIAL_LENGTH);
    else
        memcpy(_serial, sn_buffer, _SERIAL_LENGTH);
}

void OneWire::_wait(uint16_t time)
{
    _timer.set_autoreload_value(time);
    _timer.enable_counter();

    while (_timer.get_counter_value() < time) {}

    _timer.disable_counter();
    _timer.set_counter_value(0);
}

void OneWire::_crc_check(uint8_t data, uint8_t* crc_byte)
{
    uint8_t tmp = *crc_byte;

    for (uint8_t bit_count = 0; bit_count < 8; bit_count++) {
        if ((data & 0x01) ^ (tmp & 0x01)) {
            tmp = tmp >> 1;
            tmp = tmp ^ 0x8c;  // 0b10001100;
        }
        else {
            tmp = tmp >> 1;
        }

        data = data >> 1;
    }

    *crc_byte = tmp;
}

} /* namespace extra */

} /* namespace cm3cpp */
