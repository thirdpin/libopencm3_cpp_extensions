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

#include "i2c_ext.h"

namespace cm3cpp {

namespace i2c {


I2c::I2c(Config i2c_conf)
{
	switch(i2c_conf.i2c_number)
	{
		case 1: _i2c = I2C1; break;
		case 2: _i2c = I2C2; break;
		default: break;
	}

	gpio::Gpio scl(i2c_conf.scl_pin);
	scl.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
	scl.set_output_options(gpio::OutputType::OPEN_DRAIN, gpio::Speed::LOW_2MHz);
	scl.set_af(gpio::AltFuncNumber::AF4);

	gpio::Gpio sda(i2c_conf.sda_pin);
	sda.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
	sda.set_output_options(gpio::OutputType::OPEN_DRAIN, gpio::Speed::LOW_2MHz);
	sda.set_af(gpio::AltFuncNumber::AF4);

	_counter_ms = i2c_conf.counter_ms;
	_counter_ms->init(systick::Counter::Mode::ONE_SHOT,
					  MAX_TRANSMIT_TIME_MS);
}

bool I2c::master_transfer(MasterTransferCfg cfg)
{
	uint32_t reg __attribute__((unused));
	bool timeout_error = false;

	_counter_ms->start();

	send_start();
	while (!(get_flag_status(MASTER_MODE_SELECTED))) {
		if(_counter_ms->timeout()) {
		    timeout_error = true;
		    break;
		}
	}

	send_7bit_address(cfg.device_address, WRITE);
	while (!get_flag_status(MASTER_TRANSMITTER_MODE_SELECTED)) {
		if(_counter_ms->timeout()) {
		   timeout_error = true;
		   break;
		}
	}

    uint8_t index = 0;

    while(cfg.write_len > 0)
    {
    	send_data(cfg.write_buf[index]);

    	while (!(get_flag_status(MASTER_BYTE_TRANSMITTED))) {
    		if(_counter_ms->timeout()) {
    			timeout_error = true;
    			break;
    		}
    	}

    	cfg.write_len--;
        index++;
    }

    uint16_t temp;
    if(cfg.read_len != 0) {
    	send_start();
    	while (!(get_flag_status(MASTER_MODE_SELECTED))) {
    		if(_counter_ms->timeout()) {
    			timeout_error = true;
    			break;
    		}
    	}

    	enable_ack();

    	send_7bit_address(cfg.device_address, READ);
    	while (!get_flag_status(MASTER_RECEIVER_MODE_SELECTED)) {
    		if(_counter_ms->timeout()) {
    			timeout_error = true;
    			break;
    		}
    	}


    	uint8_t size_to_read = cfg.read_len;
    	index = 0;

    	while (size_to_read > 0)
    	{
    		size_to_read--;
    		if (!size_to_read)
    			disable_ack();
    		while (!get_flag_status(MASTER_BYTE_RECEIVED)) {
    			if(_counter_ms->timeout()) {
    				timeout_error = true;
    				break;
    			}
    		}

    		uint8_t data = get_data();
    		cfg.read_buf[index] = data;
    		index++;
    	}
    }

    send_stop();
    _counter_ms->stop();

    if (timeout_error)
    	return false;
    return true;
}


}  // namespace i2c

}  // namespace cm3ext
