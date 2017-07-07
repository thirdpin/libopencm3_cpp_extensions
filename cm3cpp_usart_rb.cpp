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
USART C++ Wrapper of libopencm3 library for STM32F2, STM32F4 
*/

#include "cm3cpp_usart_rb.h"

namespace cm3cpp {

namespace usart {

UsartRb::UsartRb(LowLevelConfig config, Settings settings,
			     utils::RoundBuffer rb_in_size,
			     utils::RoundBuffer rb_out_size)
    : Usart(config, settings)
{
	rb_in = new utils::RoundBuffer(rb_in_size);
	rb_out = new utils::RoundBuffer(rb_out_size);

	if (settings.mode & USART_MODE_RX)
		usart_enable_rx_interrupt(_usart);
}

} // usart

} // namespace cm3cpp
