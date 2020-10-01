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

#ifndef CM3CPP_USART_RB_H_
#define CM3CPP_USART_RB_H_

#include <cassert>
#include <limits>

/**************************************************************************************************
 * CM3CPP INCLUDES
 *************************************************************************************************/
#include "usart.hpp"
#include "utils/round_buffer.hpp"

namespace cm3cpp {

namespace usart {

class UsartRb : public Usart
{
 public:
    utils::RoundBuffer* rb_in;
    utils::RoundBuffer* rb_out;

    UsartRb(LowLevelConfig config,
            Settings settings,
            uint32_t rb_in_size,
            uint32_t rb_out_size);

    CM3CPP_EXPLISIT_DESTRUCTOR(UsartRb)

    void start_send() { usart_enable_tx_interrupt(_usart); }

    void receive_handler()
    {
        if (interrupt_source_rx()) {
            using byte_t = uint8_t;

            const uint16_t byte16 = read();
            assert(byte16 < std::numeric_limits<byte_t>::max());

            rb_in->push(static_cast<byte_t>(byte16));
        }
    }

    void transmit_handler()
    {
        if (interrupt_source_tx()) {
            if (rb_out->get_count()) {
                write(rb_out->pop());
            }
            else {
                usart_disable_tx_interrupt(_usart);
            }
        }
    }

    void inirq()
    {
        receive_handler();
        transmit_handler();
    }
};

}  // namespace usart

}  // namespace cm3cpp

#endif /* CM3CPP_USART_RB_H_ */
