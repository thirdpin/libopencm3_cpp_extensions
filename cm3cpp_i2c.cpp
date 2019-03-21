/*
 * This file is part of the libopencm3_cpp_extensions project.
 * hosted at http://github.com/thirdpin/libopencm3_cpp_extensions
 *
 * Copyright (C) 2016  Third Pin LLC
 * Written by Anastasiia Lazareva <a.lazareva@thirdpin.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
I2C C++ Wrapper of libopencm3 library for STM32F2, STM32F4
*/

#include "cm3cpp_i2c.h"

namespace cm3cpp {

namespace i2c {

I2c::I2c(Config i2c_conf) :
  _counter_ms(new systick::Counter(systick::Counter::Mode::ONE_SHOT,
                                   MAX_TRANSMIT_TIME_MS))
{
    _config = i2c_conf;

    switch (_config.number) {
        case 1:
            _i2c = I2C1;
            break;
        case 2:
            _i2c = I2C2;
            break;
        default:
            break;
    }

    Gpio scl(_config.scl_pin);
    scl.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
    scl.set_output_options(Gpio::OutputType::OPEN_DRAIN, Gpio::Speed::LOW_2MHz);
    scl.set_af(Gpio::AltFuncNumber::AF4);

    Gpio sda(_config.sda_pin);
    sda.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
    sda.set_output_options(Gpio::OutputType::OPEN_DRAIN, Gpio::Speed::LOW_2MHz);
    sda.set_af(Gpio::AltFuncNumber::AF4);
}

void I2c::reset()
{
    i2c_reset(_i2c);
}

void I2c::enable()
{
    i2c_peripheral_enable(_i2c);
}

void I2c::disable()
{
    i2c_peripheral_disable(_i2c);
}

void I2c::set_clock_frequency(ClockFrequency freq)
{
    i2c_set_clock_frequency(_i2c, freq);
}

void I2c::set_ccr(uint16_t freq)
{
    i2c_set_ccr(_i2c, freq);
}

void I2c::set_trise(uint16_t trise)
{
    i2c_set_trise(_i2c, trise);
}

void I2c::set_mode(Mode mode)
{
    switch (mode) {
        case STANDARD:
            i2c_set_standard_mode(_i2c);
            break;
        case FAST:
            i2c_set_fast_mode(_i2c);
            break;
    }
}

void I2c::set_address_mode(AddressMode mode)
{
    switch (mode) {
        case ADDRESS_MODE_7BIT:
            I2C_OAR1(_i2c) &= ~I2C_OAR1_ADDMODE;
            break;
        case ADDRESS_MODE_10BIT:
            I2C_OAR1(_i2c) |= I2C_OAR1_ADDMODE;
            break;
    }
}

void I2c::set_dutycycle(FastModeDuty dutycycle)
{
    i2c_set_dutycycle(_i2c, dutycycle);
}

void I2c::set_own_7bit_slave_address(uint8_t slave)
{
    i2c_set_own_7bit_slave_address(_i2c, slave);
}

void I2c::set_own_10bit_slave_address(uint16_t slave)
{
    i2c_set_own_10bit_slave_address(_i2c, slave);
}

void I2c::set_own_7bit_slave_address_two(uint8_t slave)
{
    i2c_set_own_7bit_slave_address_two(_i2c, slave);
}

void I2c::enable_dual_addressing_mode()
{
    i2c_enable_dual_addressing_mode(_i2c);
}

void I2c::disable_dual_addressing_mode()
{
    i2c_disable_dual_addressing_mode(_i2c);
}

void I2c::enable_interrupt(Interrupt interrupt)
{
    switch (interrupt) {
        case IT_BUFFER:
            i2c_enable_interrupt(_i2c, I2C_CR2_ITBUFEN);
            break;
        case IT_EVENT:
            i2c_enable_interrupt(_i2c, I2C_CR2_ITEVTEN);
            break;
        case IT_ERROR:
            i2c_enable_interrupt(_i2c, I2C_CR2_ITERREN);
            break;
    }
}

void I2c::disable_interrupt(Interrupt interrupt)
{
    switch (interrupt) {
        case IT_BUFFER:
            i2c_disable_interrupt(_i2c, I2C_CR2_ITBUFEN);
            break;
        case IT_EVENT:
            i2c_disable_interrupt(_i2c, I2C_CR2_ITEVTEN);
            break;
        case IT_ERROR:
            i2c_disable_interrupt(_i2c, I2C_CR2_ITERREN);
            break;
    }
}

auto I2c::master_transfer(MasterTransferCfg cfg) -> Result
{
    uint32_t reg __attribute__((unused));
    Result result = OK;

    _counter_ms->start();

    _send_start();
    while (_get_flag_status(MASTER_MODE_SELECTED) == Result::ERROR) {
        if (_counter_ms->timeout()) {
            result = TIMEOUT;
            break;
        }
    }

    _send_7bit_address(cfg.device_address, WRITE);
    while (_get_flag_status(MASTER_TRANSMITTER_MODE_SELECTED) ==
           Result::ERROR) {
        if (_counter_ms->timeout()) {
            result = TIMEOUT;
            break;
        }
    }

    uint8_t index = 0;

    while (cfg.write_len > 0) {
        _send_data(cfg.write_buf[index]);

        while (_get_flag_status(MASTER_BYTE_TRANSMITTED) == Result::ERROR) {
            if (_counter_ms->timeout()) {
                result = TIMEOUT;
                break;
            }
        }

        cfg.write_len--;
        index++;
    }

    if (cfg.read_len != 0) {
        _send_start();
        while (_get_flag_status(MASTER_MODE_SELECTED) == Result::ERROR) {
            if (_counter_ms->timeout()) {
                result = TIMEOUT;
                break;
            }
        }

        _enable_ack();

        _send_7bit_address(cfg.device_address, READ);
        while (_get_flag_status(MASTER_RECEIVER_MODE_SELECTED) ==
               Result::ERROR) {
            if (_counter_ms->timeout()) {
                result = TIMEOUT;
                break;
            }
        }

        uint8_t size_to_read = cfg.read_len;
        index = 0;

        while (size_to_read > 0) {
            size_to_read--;
            if (!size_to_read)
                _disable_ack();
            while (_get_flag_status(MASTER_BYTE_RECEIVED) == Result::ERROR) {
                if (_counter_ms->timeout()) {
                    result = TIMEOUT;
                    break;
                }
            }

            uint8_t data = _get_data();
            cfg.read_buf[index] = data;
            index++;
        }
    }

    _send_stop();
    _counter_ms->stop();

    return result;
}

void I2c::_send_start()
{
    i2c_send_start(_i2c);
}

void I2c::_send_stop()
{
    i2c_send_stop(_i2c);
}

void I2c::_clear_stop()
{
    i2c_clear_stop(_i2c);
}

void I2c::_send_data(uint8_t data)
{
    i2c_send_data(_i2c, data);
}

uint8_t I2c::_get_data()
{
    return i2c_get_data(_i2c);
}

void I2c::_send_7bit_address(uint8_t slave, Command readwrite)
{
    i2c_send_7bit_address(_i2c, slave, readwrite);
}

void I2c::_enable_ack()
{
    i2c_enable_ack(_i2c);
}

void I2c::_disable_ack()
{
    i2c_disable_ack(_i2c);
}

auto I2c::_get_flag_status(Event event) -> Result
{
    Result result = ERROR;
    uint32_t reg_sr1 = I2C_SR1(_i2c);
    uint32_t reg_sr2 = (I2C_SR2(_i2c)) << 16;
    uint32_t lastevent = (reg_sr1 | reg_sr2) & I2C_FLAG_MASK;

    switch (event) {
        case MASTER_MODE_SELECTED:
            if ((lastevent & MASTER_MODE_SELECTED_MASK) ==
                MASTER_MODE_SELECTED_MASK) {
                result = OK;
            }
            break;
        case MASTER_TRANSMITTER_MODE_SELECTED:
            if ((lastevent & MASTER_TRANSMITTER_MODE_SELECTED_MASK) ==
                MASTER_TRANSMITTER_MODE_SELECTED_MASK) {
                result = OK;
            }
            break;
        case MASTER_RECEIVER_MODE_SELECTED:
            if ((lastevent & MASTER_RECEIVER_MODE_SELECTED_MASK) ==
                MASTER_RECEIVER_MODE_SELECTED_MASK) {
                result = OK;
            }
            break;
        case MASTER_MODE_ADDRESS10:
            if ((lastevent & MASTER_MODE_ADDRESS10_MASK) ==
                MASTER_MODE_ADDRESS10_MASK) {
                result = OK;
            }
            break;
        case MASTER_BYTE_RECEIVED:
            if ((lastevent & MASTER_BYTE_RECEIVED_MASK) ==
                MASTER_BYTE_RECEIVED_MASK) {
                result = OK;
            }
            break;
        case MASTER_BYTE_TRANSMITTING:
            if ((lastevent & MASTER_BYTE_TRANSMITTING_MASK) ==
                MASTER_BYTE_TRANSMITTING_MASK) {
                result = OK;
            }
            break;
        case MASTER_BYTE_TRANSMITTED:
            if ((lastevent & MASTER_BYTE_TRANSMITTED_MASK) ==
                MASTER_BYTE_TRANSMITTED_MASK) {
                result = OK;
            }
            break;
    }

    return result;
}

}  // namespace i2c

}  // namespace cm3cpp
