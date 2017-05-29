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
RS485 implementation, public interface
*/

#include "rs485.h"

namespace cm3ext {


RS485::RS485(RS485_Struct rs485, RS485_Settings settings, RoundBuffer rb_in_size, RoundBuffer rb_out_size)
{
	rb_in = new RoundBuffer(rb_in_size);
	rb_out = new RoundBuffer(rb_out_size);

	if (rs485.rx.pin)
	{
		gpio::Gpio rx(rs485.rx);
		rx.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
		rx.set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::MEDIUM_25MHz);
		rx.set_af(gpio::AltFuncNumber::AF7);
	}

	if (rs485.tx.pin)
	{
		gpio::Gpio tx(rs485.tx);
		tx.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
		tx.set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::MEDIUM_25MHz);
		tx.set_af(gpio::AltFuncNumber::AF7);
	}

	_de = new gpio::Gpio(rs485.de);
	_de->mode_setup(gpio::Mode::OUTPUT, gpio::PullMode::NO_PULL);
	_de->set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::MEDIUM_25MHz);
	_de->clear();

	switch (rs485.number)
	{
		case 1: _rs485 = USART1;
				nvic_enable_irq(NVIC_USART1_IRQ);
				break;
		case 2: _rs485 = USART2;
				nvic_enable_irq(NVIC_USART2_IRQ);
				break;
		case 3: _rs485 = USART3;
				nvic_enable_irq(NVIC_USART3_IRQ);
				break;
		}

		usart_set_baudrate(_rs485, settings.baud_rate);
		usart_set_databits(_rs485, settings.word_length);
		usart_set_stopbits(_rs485, settings.stop_bits);
		usart_set_mode(_rs485, settings.mode);
		usart_set_parity(_rs485, settings.parity);
		usart_set_flow_control(_rs485, settings.flow_control);

		if (settings.mode & USART_MODE_RX)
			usart_enable_rx_interrupt(_rs485);

		usart_enable(_rs485);
}


} // namespace cm3ext

