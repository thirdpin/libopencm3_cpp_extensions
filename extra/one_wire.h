#ifndef EXTRA_ONE_WIRE_H_
#define EXTRA_ONE_WIRE_H_

#include <string.h>
#include "../cm3cpp_gpio.h"
#include "../cm3cpp_timer.h"

namespace cm3cpp {

namespace extra {

namespace timer = cm3cpp::tim;

class OneWire
{
public:
	using Timer = cm3cpp::tim::Timer;
	using Gpio = cm3cpp::gpio::Gpio;

	OneWire(Gpio::Pinout p, uint8_t tim_number, uint32_t tim_presc);
	~OneWire() = default;

	uint8_t read_byte(void);
	void write_byte(uint8_t data);
	bool read_bit(void);
	void write_bit(bool bit);
	bool touch_reset(void);
	bool search_first(bool do_reset, bool alarm_only);
	bool search_next(bool do_reset, bool alarm_only);
	void get_serial_number(uint8_t *sn_buffer, bool do_read);

private:
	static constexpr uint16_t _SLOT_LENGTH           = 78;
	static constexpr uint16_t _RESET_PULSE_TIME_US   = 520;
	static constexpr uint16_t _LOW_PULSE_TIME_US     = 3;
	static constexpr uint16_t _READ_SAMPLE_TIME_US   = 12;
	static constexpr uint16_t _READ_SAMPLE_WAIT_US   = (_READ_SAMPLE_TIME_US - _LOW_PULSE_TIME_US);
	static constexpr uint16_t _END_READ_SLOT_WAIT_US = (_SLOT_LENGTH - _READ_SAMPLE_TIME_US);
	static constexpr uint16_t _RECOVERY_TIME_US      = 6;
	static constexpr uint16_t _WRITE_SLOT_WAIT_US    = (_SLOT_LENGTH - _LOW_PULSE_TIME_US);
	static constexpr uint8_t  _SERIAL_LENGTH         = 8;

	static constexpr uint8_t  _SEARCH                = 0xF0;
	static constexpr uint8_t  _SEARCH_ALARM          = 0xEC;

	Gpio _pinout;
	Timer *_timer;
    uint8_t _serial[_SERIAL_LENGTH];

    int8_t _last_discrepancy;
    int8_t _last_family_discrepancy;
    bool _last_device;

	void _wait(uint16_t time);
	void _crc_check(uint8_t data, uint8_t *crc_byte);
};

} /* namespace extra */

} /* namespace cm3cpp */

#endif /* EXTRA_ONE_WIRE_H_ */
