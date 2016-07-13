/*
 * This file is part of the libopencm3_cpp_extensions project.
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
USART C++ Wrapper of libopencm3 library for STM32F2, STM32F4 
*/

#include "usart_ext.h"

USART_ext::USART_ext(USART_Struct usart, USART_Settings settings, RoundBuffer rb_in_size, RoundBuffer rb_out_size)
{
	rb_in = new RoundBuffer(rb_in_size);
	rb_out = new RoundBuffer(rb_out_size);

	if (usart.rx.pin)
	{
		GPIO_ext rx(usart.rx);
		rx.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
		rx.set_output_options(GPIO_CPP_Extension::OutputType::PUSH_PULL, GPIO_CPP_Extension::Speed::MEDIUM_25MHz);

		if ((usart.number >= 1) && (usart.number <= 3)) {
			rx.set_af(GPIO_CPP_Extension::AF_Number::AF7);
		}
		if ((usart.number >= 4) && (usart.number <= 6)) {
			rx.set_af(GPIO_CPP_Extension::AF_Number::AF8);
		}
	}

	if (usart.tx.pin)
	{
		GPIO_ext tx(usart.tx);
		tx.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
		tx.set_output_options(GPIO_CPP_Extension::OutputType::PUSH_PULL, GPIO_CPP_Extension::Speed::MEDIUM_25MHz);
		if ((usart.number >= 1) && (usart.number <= 3)) {
			tx.set_af(GPIO_CPP_Extension::AF_Number::AF7);
		}
		if ((usart.number >= 4) && (usart.number <= 6)) {
			tx.set_af(GPIO_CPP_Extension::AF_Number::AF8);
		}
	}

	switch (usart.number)
	{
		case 1: _usart = USART1;
				nvic_enable_irq(NVIC_USART1_IRQ);
				break;
		case 2: _usart = USART2;
				nvic_enable_irq(NVIC_USART2_IRQ);
				break;
		case 3: _usart = USART3;
				nvic_enable_irq(NVIC_USART3_IRQ);
				break;
		case 4: _usart = UART4;
			    nvic_enable_irq(NVIC_UART4_IRQ);
				break;
		case 5: _usart = UART5;
				nvic_enable_irq(NVIC_UART5_IRQ);
				break;
		case 6: _usart = USART6;
				nvic_enable_irq(NVIC_USART6_IRQ);
				break;
	}

	usart_set_baudrate(_usart, settings.baud_rate);
	usart_set_databits(_usart, settings.word_length);
	usart_set_stopbits(_usart, settings.stop_bits);
	usart_set_mode(_usart, settings.mode);
	usart_set_parity(_usart, settings.parity);
	usart_set_flow_control(_usart, settings.flow_control);

	if (settings.mode & USART_MODE_RX)
		usart_enable_rx_interrupt(_usart);

	usart_enable(_usart);
}
