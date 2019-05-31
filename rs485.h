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

#ifndef RS_485_H
#define RS_485_H

#include <stdint.h>

#include <libopencm3/stm32/usart.h>
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif

#include "cm3cpp_gpio.h"
#include "private/assert.h"
#include "utils/round_buffer.h"
#include <cm3cpp_config.h>

namespace cm3cpp {

class RS485
{
 public:
    using Gpio = gpio::Gpio;

    struct Settings
    {
        uint32_t baud_rate;
        uint16_t word_length;
        uint16_t stop_bits;
        uint16_t parity;
        uint16_t mode;
        uint16_t flow_control;
    };

    struct Struct
    {
        uint32_t number;
        Gpio::Pinout tx;
        Gpio::Pinout rx;
        Gpio::Pinout de;
    };

    utils::RoundBuffer* rb_in;
    utils::RoundBuffer* rb_out;

    RS485(Struct rs485,
          Settings settings,
          utils::RoundBuffer rb_in_size,
          utils::RoundBuffer rb_out_size);

    CM3CPP_EXPLISIT_DESTRUCTOR(RS485)

    void usart_enable_tc_interrupt() { USART_CR1(_rs485) |= USART_CR1_TCIE; }

    void usart_disable_tc_interrupt() { USART_CR1(_rs485) &= ~USART_CR1_TCIE; }

    bool interrupt_source_RXNE()
    {
        return (((USART_CR1(_rs485) & USART_CR1_RXNEIE) != 0) &&
                usart_get_flag(_rs485, USART_SR_RXNE));
    }

    bool interrupt_source_TXE()
    {
        return (((USART_CR1(_rs485) & USART_CR1_TXEIE) != 0) &&
                usart_get_flag(_rs485, USART_SR_TXE));
    }

    bool interrupt_source_TC()
    {
        return (((USART_CR1(_rs485) & USART_CR1_TCIE) != 0) &&
                usart_get_flag(_rs485, USART_SR_TC));
    }

    void start_send()
    {
        _de.set();
        usart_enable_tx_interrupt(_rs485);
    }

    void receive_handler()
    {
        if (interrupt_source_RXNE()) {
            rb_in->push(usart_recv(_rs485));
        }
    }

    void transmit_handler()
    {
        if (interrupt_source_TXE()) {
            if (rb_out->get_count()) {
                usart_send(_rs485, rb_out->pop());
            }
            else {
                usart_disable_tx_interrupt(_rs485);
                usart_enable_tc_interrupt();
            }
        }
        if (interrupt_source_TC()) {
            _de.clear();
            usart_disable_tc_interrupt();
        }
    }

    void inirq()
    {
        receive_handler();
        transmit_handler();
    }

 private:
    uint32_t _rs485;
    gpio::Gpio _de;
};

}  // namespace cm3cpp
#endif
