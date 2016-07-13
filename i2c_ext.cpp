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
using namespace I2C_CPP_Extension;

I2C_ext::I2C_ext(I2C_Conf i2c_conf)
{
	switch(i2c_conf.i2c_number)
	{
		case 1: _i2c = I2C1; break;
		case 2: _i2c = I2C2; break;
		default: break;
	}

	GPIO_ext scl(i2c_conf.scl_pin);
	scl.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
	scl.set_output_options(GPIO_CPP_Extension::OutputType::OPEN_DRAIN, GPIO_CPP_Extension::Speed::LOW_2MHz);
	scl.set_af(GPIO_CPP_Extension::AF_Number::AF4);

	GPIO_ext sda(i2c_conf.sda_pin);
	sda.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
	sda.set_output_options(GPIO_CPP_Extension::OutputType::OPEN_DRAIN, GPIO_CPP_Extension::Speed::LOW_2MHz);
	sda.set_af(GPIO_CPP_Extension::AF_Number::AF4);

	_timer = new TimerMs(TimerMode::ONE_SHOT, MAX_TRANSMIT_TIME_MS);
}

bool I2C_ext::master_transfer(I2C_MasterTransferCfg cfg)
{
	uint32_t reg __attribute__((unused));
	bool timeout_error = false;

	_timer->start();

	send_start();
	while (!(get_flag_status(MASTER_MODE_SELECTED))) {
		if(_timer->timeout()) {
		    timeout_error = true;
		    break;
		}
	}

	send_7bit_address(cfg.device_address, WRITE);
	while (!get_flag_status(MASTER_TRANSMITTER_MODE_SELECTED)) {
		if(_timer->timeout()) {
		   timeout_error = true;
		   break;
		}
	}

    uint8_t index = 0;

    while(cfg.write_len > 0)
    {
    	send_data(cfg.write_buf[index]);

    	while (!(get_flag_status(MASTER_BYTE_TRANSMITTED))) {
    		if(_timer->timeout()) {
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
    		if(_timer->timeout()) {
    			timeout_error = true;
    			break;
    		}
    	}

    	enable_ack();

    	send_7bit_address(cfg.device_address, READ);
    	while (!get_flag_status(MASTER_RECEIVER_MODE_SELECTED)) {
    		if(_timer->timeout()) {
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
    			if(_timer->timeout()) {
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
    _timer->stop();

    if (timeout_error)
    	return false;
    return true;
}
