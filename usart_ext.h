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

#ifndef USART_EXT_H
#define USART_EXT_H


#include <stdint.h>
#include <libopencm3/stm32/usart.h>
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif

#include "round_buffer.h"
#include "gpio_ext.h"


namespace cm3ext {


typedef struct {
	uint32_t baud_rate;
	uint16_t word_length;
	uint16_t stop_bits;
	uint16_t parity;
	uint16_t mode;
	uint16_t flow_control;
	uint8_t  nvic_priority;
}USART_Settings;

typedef struct {
    uint32_t number;
	gpio::Pinout tx;
	gpio::Pinout rx;
}USART_Struct;

class USART_ext
{
public:
	utils::RoundBuffer *rb_in;
	utils::RoundBuffer *rb_out;

	USART_ext(USART_Struct usart, USART_Settings settings,
			  utils::RoundBuffer rb_in_size, utils::RoundBuffer rb_out_size);

	bool interrupt_source_RXNE() {
		return (((USART_CR1(_usart) & USART_CR1_RXNEIE) != 0) && usart_get_flag(_usart, USART_SR_RXNE));
	}

	bool interrupt_source_TXE() {
		return (((USART_CR1(_usart) & USART_CR1_TXEIE) != 0) && usart_get_flag(_usart, USART_SR_TXE));
	}

	void start_send() {
		usart_enable_tx_interrupt(_usart);
	}

    void enable_irq() {
        nvic_enable_irq(_usart_nvic);
    }

	void disable_irq() {
	    nvic_disable_irq(_usart_nvic);
	}

	void receive_handler()
	{
		if (interrupt_source_RXNE()) {
			rb_in->push(uart_read());
		}
	}

	void transmit_handler()
	{
		if (interrupt_source_TXE()) {
			if (rb_out->get_count()) {
				usart_send(_usart, rb_out->pop());
			}
			else {
				usart_disable_tx_interrupt(_usart);
			}
		}
	}

	void uart_write_blocking(uint16_t data) {
	    usart_send_blocking(_usart, data);
	}

    void uart_write(uint16_t data) {
        usart_send(_usart, data);
    }

	uint16_t uart_read() {
	    return usart_recv(_usart);
	}

	void inirq()
	{
		receive_handler();
		transmit_handler();
	}

private:
	uint32_t _usart;
	uint32_t _usart_nvic;
};


} // namespace cm3ext

#endif
