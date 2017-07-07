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

#ifndef I2C_EXT_H
#define I2C_EXT_H

#include <libopencm3/stm32/i2c.h>
#include <cm3cpp_config.h>
#include <libopencm3_cpp_extensions/cm3cpp_gpio.h>

#include "private/assert.h"
#include "systick_ext.h"

namespace cm3cpp {

namespace i2c {

constexpr bool OK										     = true;
constexpr bool ERROR       							         = false;
constexpr uint8_t MAX_TRANSMIT_TIME_MS        			     = 3;
constexpr uint32_t I2C_FLAG_MASK               			     = 0x00FFFFFF;
constexpr uint32_t MASTER_MODE_SELECTED_MASK  		    	 = 0x00030001;
constexpr uint32_t MASTER_TRANSMITTER_MODE_SELECTED_MASK     = 0x00070082;
constexpr uint32_t MASTER_RECEIVER_MODE_SELECTED_MASK        = 0x00030002;
constexpr uint32_t MASTER_MODE_ADDRESS10_MASK                = 0x00030008;
constexpr uint32_t MASTER_BYTE_RECEIVED_MASK                 = 0x00030040;
constexpr uint32_t MASTER_BYTE_TRANSMITTING_MASK             = 0x00070080;
constexpr uint32_t MASTER_BYTE_TRANSMITTED_MASK              = 0x00070084;

struct Config {
	uint8_t i2c_number;
	gpio::Pinout scl_pin;
	gpio::Pinout sda_pin;
	//systick::Counter* counter_ms;
};

struct MasterTransferCfg {
	uint16_t device_address;
	uint8_t* write_buf;
	uint8_t write_len;
	uint8_t read_len;
	uint8_t* read_buf;
};

enum Mode {
	STANDARD = 0,
	FAST
};

enum FastModeDuty {
	DUTY_DIV2 = 0,
	DUTY_16_DIV_9
};

enum AddressMode {
	ADDRESS_MODE_7BIT  = 0,
	ADDRESS_MODE_10BIT = 1
};

enum Command {
	WRITE = 0,
	READ  = 1
};

enum Event {
	MASTER_MODE_SELECTED,
	MASTER_TRANSMITTER_MODE_SELECTED,
	MASTER_RECEIVER_MODE_SELECTED,
	MASTER_MODE_ADDRESS10,
	MASTER_BYTE_RECEIVED,
	MASTER_BYTE_TRANSMITTING,
	MASTER_BYTE_TRANSMITTED
};

enum TransferStatus {
	MASTER_MODE_SELECTED_ERROR,
	MASTER_TRANSMITTER_MODE_SELECTED_ERROR,
	MASTER_RECEIVER_MODE_SELECTED_ERROR,
	MASTER_MODE_ADDRESS10_ERROR,
	MASTER_BYTE_RECEIVED_ERROR,
	MASTER_BYTE_TRANSMITTING_ERROR,
	MASTER_BYTE_TRANSMITTED_ERROR,
	SUCCESS
};

enum Interrupt {
	IT_BUFFER,
	IT_EVENT,
	IT_ERROR
};

enum ClockFrequency {
	FREQ_2MHZ	=	0x02,
	FREQ_3MHZ	=	0x03,
	FREQ_4MHZ	=	0x04,
	FREQ_5MHZ	=	0x05,
	FREQ_6MHZ	=	0x06,
	FREQ_7MHZ	=	0x07,
	FREQ_8MHZ	=	0x08,
	FREQ_9MHZ	=	0x09,
	FREQ_10MHZ	=	0x0a,
	FREQ_11MHZ	=	0x0b,
	FREQ_12MHZ	=	0x0c,
	FREQ_13MHZ	=	0x0d,
	FREQ_14MHZ	=	0x0e,
	FREQ_15MHZ	=	0x0f,
	FREQ_16MHZ	=	0x10,
	FREQ_17MHZ	=	0x11,
	FREQ_18MHZ	=	0x12,
	FREQ_19MHZ	=	0x13,
	FREQ_20MHZ	=	0x14,
	FREQ_21MHZ	=	0x15,
	FREQ_22MHZ	=	0x16,
	FREQ_23MHZ	=	0x17,
	FREQ_24MHZ	=	0x18,
	FREQ_25MHZ	=	0x19,
	FREQ_26MHZ	=	0x1a,
	FREQ_27MHZ	=	0x1b,
	FREQ_28MHZ	=	0x1c,
	FREQ_29MHZ	=	0x1d,
	FREQ_30MHZ	=	0x1e,
	FREQ_31MHZ	=	0x1f,
	FREQ_32MHZ	=	0x20,
	FREQ_33MHZ	=	0x21,
	FREQ_34MHZ	=	0x22,
	FREQ_35MHZ	=	0x23,
	FREQ_36MHZ	=	0x24,
	FREQ_37MHZ	=	0x25,
	FREQ_38MHZ	=	0x26,
	FREQ_39MHZ	=	0x27,
	FREQ_40MHZ	=	0x28,
	FREQ_41MHZ	=	0x29,
	FREQ_42MHZ	=	0x2a
};

class I2c
{
public:
	I2c();
	I2c(Config i2c_conf);

	CM3CPP_EXPLISIT_DESTRUCTOR(I2c)


	inline void reset() {
		i2c_reset(_i2c);
	}

	void enable() {
		i2c_peripheral_enable(_i2c);
	}

	void disable() {
		i2c_peripheral_disable(_i2c);
	}

	void set_clock_frequency(ClockFrequency freq) {
		i2c_set_clock_frequency(_i2c, freq);
	}

	void set_ccr(uint16_t freq) {
		i2c_set_ccr(_i2c, freq);
	}

	void set_trise(uint16_t trise) {
		i2c_set_trise(_i2c, trise);
	}

	void set_mode(Mode mode)
	{
		switch (mode)
		{
			case STANDARD :
				i2c_set_standard_mode(_i2c);
				break;
			case FAST     :
				i2c_set_fast_mode(_i2c);
				break;
		}
	}

	void set_address_mode(AddressMode mode)
	{
		switch (mode)
		{
		case ADDRESS_MODE_7BIT  :
			I2C_OAR1(_i2c) &= ~I2C_OAR1_ADDMODE;
			break;
		case ADDRESS_MODE_10BIT :
			I2C_OAR1(_i2c) |= I2C_OAR1_ADDMODE;
			break;
		}
	}

	void set_dutycycle(FastModeDuty dutycycle) {
		i2c_set_dutycycle(_i2c, dutycycle);
	}

	void set_own_7bit_slave_address(uint8_t slave) {
		i2c_set_own_7bit_slave_address(_i2c, slave);
	}

	void set_own_10bit_slave_address(uint16_t slave) {
		i2c_set_own_10bit_slave_address(_i2c, slave);
	}

	void set_own_7bit_slave_address_two(uint8_t slave) {
		i2c_set_own_7bit_slave_address_two(_i2c, slave);
	}

	void enable_dual_addressing_mode() {
		i2c_enable_dual_addressing_mode(_i2c);
	}

	void disable_dual_addressing_mode() {
		i2c_disable_dual_addressing_mode(_i2c);
	}

	void enable_interrupt(Interrupt interrupt)
	{
		switch (interrupt)
		{
			case IT_BUFFER :
				i2c_enable_interrupt(_i2c, I2C_CR2_ITBUFEN);
				break;
			case IT_EVENT  :
				i2c_enable_interrupt(_i2c, I2C_CR2_ITEVTEN);
				break;
			case IT_ERROR  :
				i2c_enable_interrupt(_i2c, I2C_CR2_ITERREN);
				break;
		}
	}

	void disable_interrupt(Interrupt interrupt)
	{
		switch (interrupt)
		{
			case IT_BUFFER :
				i2c_disable_interrupt(_i2c, I2C_CR2_ITBUFEN);
				break;
			case IT_EVENT  :
				i2c_disable_interrupt(_i2c, I2C_CR2_ITEVTEN);
				break;
			case IT_ERROR  :
				i2c_disable_interrupt(_i2c, I2C_CR2_ITERREN);
				break;
		}
	}

	bool master_transfer(MasterTransferCfg cfg);

private:
	uint32_t _i2c;
	systick::Counter *_counter_ms;

	void send_start() {
		i2c_send_start(_i2c);
	}

	void send_stop() {
		i2c_send_stop(_i2c);
	}

	void clear_stop() {
		i2c_clear_stop(_i2c);
	}

	void send_data(uint8_t data) {
		i2c_send_data(_i2c, data);
	}

	uint8_t get_data() {
		return i2c_get_data(_i2c);
	}

	void send_7bit_address(uint8_t slave, Command readwrite) {
		i2c_send_7bit_address(_i2c, slave, readwrite);
	}

	void enable_ack() {
		i2c_enable_ack(_i2c);
	}

	void disable_ack() {
		i2c_disable_ack(_i2c);
	}

	bool get_flag_status(Event event)
	{
		bool result = ERROR;
		uint32_t reg_sr1 = I2C_SR1(_i2c);
		uint32_t reg_sr2 = (I2C_SR2(_i2c)) << 16;
		uint32_t lastevent = (reg_sr1 | reg_sr2) & I2C_FLAG_MASK;

		switch (event)
		{
			case MASTER_MODE_SELECTED			       :
				if ((lastevent & MASTER_MODE_SELECTED_MASK) ==
								 MASTER_MODE_SELECTED_MASK) {
					result = OK;
				}
				break;
			case MASTER_TRANSMITTER_MODE_SELECTED  :
				if ((lastevent & MASTER_TRANSMITTER_MODE_SELECTED_MASK) ==
								 MASTER_TRANSMITTER_MODE_SELECTED_MASK) {
					result = OK;
				}
				break;
			case MASTER_RECEIVER_MODE_SELECTED     :
				if ((lastevent & MASTER_RECEIVER_MODE_SELECTED_MASK) ==
								 MASTER_RECEIVER_MODE_SELECTED_MASK) {
					result = OK;
				}
				break;
			case MASTER_MODE_ADDRESS10	           :
				if ((lastevent & MASTER_MODE_ADDRESS10_MASK) ==
								 MASTER_MODE_ADDRESS10_MASK) {
					result = OK;
				}
				break;
			case MASTER_BYTE_RECEIVED              :
				if ((lastevent & MASTER_BYTE_RECEIVED_MASK) ==
								 MASTER_BYTE_RECEIVED_MASK) {
					result = OK;
				}
				break;
			case MASTER_BYTE_TRANSMITTING          :
				if ((lastevent & MASTER_BYTE_TRANSMITTING_MASK) ==
								MASTER_BYTE_TRANSMITTING_MASK) {
					result = OK;
				}
				break;
			case MASTER_BYTE_TRANSMITTED           :
				if ((lastevent & MASTER_BYTE_TRANSMITTED_MASK) ==
								 MASTER_BYTE_TRANSMITTED_MASK) {
					result = OK;
				}
				break;
		}

		return result;
	}
};


}  // namespace i2c

}  // namespace cm3ext

#endif
