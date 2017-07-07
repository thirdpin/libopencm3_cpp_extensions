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

#ifndef CM3CPP_USART_H_
#define CM3CPP_USART_H_

/**************************************************************************************************
 * GENERAL INCLUDES
 *************************************************************************************************/
#include <cstdint>
/**************************************************************************************************
 * LIBOPENCM3 INCLUDES
 *************************************************************************************************/
#include <libopencm3/stm32/usart.h>
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif
/**************************************************************************************************
 * CM3CPP INCLUDES
 *************************************************************************************************/
#include "private/assert.h"
#include "cm3cpp_config.h"
#include "cm3cpp_gpio.h"

namespace cm3cpp {

class Usart
{
public:
	struct Settings {
		uint32_t baud_rate;
		uint16_t word_length;
		uint16_t stop_bits;
		uint16_t parity;
		uint16_t mode;
		uint16_t flow_control;
	};

	struct LowLevelConfig {
	    uint32_t usart_number;
		gpio::Pinout tx;
		gpio::Pinout rx;
		uint8_t nvic_priority;
	};

	Usart(LowLevelConfig config, Settings settings);

	CM3CPP_EXPLISIT_DESTRUCTOR(Usart)

	bool interrupt_source_rx() {
		return (((USART_CR1(_usart) & USART_CR1_RXNEIE) != 0) &&
				 usart_get_flag(_usart, USART_SR_RXNE));
	}

	bool interrupt_source_tx() {
		return (((USART_CR1(_usart) & USART_CR1_TXEIE) != 0) &&
				 usart_get_flag(_usart, USART_SR_TXE));
	}

    void enable_irq() {
        //nvic_enable_irq(_usart_nvic);
    }

	void disable_irq() {
	    //nvic_disable_irq(_usart_nvic);
	}

	void enable_rx_interrupt()
	{
		usart_enable_rx_interrupt(_usart);
	}

	void enable_tx_interrupt() {
		usart_enable_tx_interrupt(_usart);
	}

	void disable_rx_interrupt()
	{
		usart_disable_rx_interrupt(_usart);
	}

	void disable_tx_interrupt() {
		usart_disable_tx_interrupt(_usart);
	}

	void write_blocking(uint16_t data) {
	    usart_send_blocking(_usart, data);
	}

    void write(uint16_t data) {
        usart_send(_usart, data);
    }

	uint16_t read() {
	    return usart_recv(_usart);
	}

	uint16_t read_blocking() {
		return usart_recv_blocking(_usart);
	}

protected:
	uint32_t _usart;
	uint32_t _usart_nvic;
};

} // namespace cm3ext

#endif /* CM3CPP_USART_H_ */
