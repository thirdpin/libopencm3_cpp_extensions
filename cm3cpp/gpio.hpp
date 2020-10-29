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
GPIO C++ Wrapper of libopencm3 library for STM32F2, STM32F4
*/

#ifndef CM3CPP_GPIO_H_
#define CM3CPP_GPIO_H_

// GENERAL INCLUDES
#include "stdint.h"

// LIBOPENCM3 INCLUDES
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif

// CM3CPP INCLUDES
#include "private/pinout.h"

namespace cm3cpp {

namespace gpio {

class Gpio
{
 public:
    struct Pinout
    {
        enum Port
        {
// Check preprocessor value is not empty
// Works for integer values
// https://stackoverflow.com/questions/4102351/test-for-empty-macro-definition
#if (GPIOA + 0)
            PORT_A = GPIOA
#endif
#if (GPIOB + 0)
            ,
            PORT_B = GPIOB
#endif
#if (GPIOC + 0)
            ,
            PORT_C = GPIOC
#endif
#if (GPIOD + 0)
            ,
            PORT_D = GPIOD
#endif
#if (GPIOE + 0)
            ,
            PORT_E = GPIOE
#endif
#if (GPIOF + 0)
            ,
            PORT_F = GPIOF
#endif
#if (GPIOG + 0)
            ,
            PORT_G = GPIOG
#endif
#if (GPIOH + 0)
            ,
            PORT_H = GPIOH
#endif
#if (GPIOI + 0)
            ,
            PORT_I = GPIOI
#endif
#if (GPIOJ + 0)
            ,
            PORT_J = GPIOJ
#endif
#if (GPIOK + 0)
            ,
            PORT_K = GPIOK
#endif
        };

        Port port;
        uint16_t pin;
        uint8_t pin_number;
    };

    enum Mode
    {
        INPUT,
        OUTPUT,
        ALTERNATE_FUNCTION,
        ANALOG
    };

    enum PullMode
    {
        NO_PULL,
        PULL_UP,
        PULL_DOWN
    };

    enum OutputType
    {
        PUSH_PULL,
        OPEN_DRAIN
    };

    enum Speed
    {
        LOW_2MHz,
        MEDIUM_25MHz,
        FAST_50MHz,
        HIGH_SPEED_100MHz
    };

    enum AltFuncNumber
    {
        AF0,
        AF1,
        AF2,
        AF3,
        AF4,
        AF5,
        AF6,
        AF7,
        AF8,
        AF9,
        AF10,
        AF11,
        AF12,
        AF13,
        AF14,
        AF15
    };

    Gpio() {}
    Gpio(Pinout pinout);

    void init(Pinout pinout);
    void set();
    void clear();
    bool get() const;
    void toggle();
    uint16_t port_read() const;
    void port_write(uint16_t data);
    void port_config_lock();
    void mode_setup(Mode mode, PullMode pull_mode);
    void set_output_options(OutputType type, Speed speed);
    void set_af(AltFuncNumber af_num);
    void setup_exti(enum exti_trigger_type trigger);
    void clear_exti_pending_bit();
    bool get_exti_flag_status() const;

 private:
    Pinout _pinout;
};  // namespace gpio

}  // namespace gpio

}  // namespace cm3cpp

#endif /* CM3CPP_GPIO_H_ */
