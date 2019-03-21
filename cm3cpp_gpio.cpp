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

#include "cm3cpp_gpio.h"

namespace cm3cpp {

namespace gpio {

Gpio::Gpio(Pinout pinout)
{
    _pinout = pinout;
}

void Gpio::init(Pinout pinout)
{
    _pinout = pinout;
}

void Gpio::set()
{
    gpio_set(_pinout.port, _pinout.pin);
}

void Gpio::clear()
{
    gpio_clear(_pinout.port, _pinout.pin);
}

bool Gpio::get() const
{
    return gpio_get(_pinout.port, _pinout.pin);
}

void Gpio::toggle()
{
    gpio_toggle(_pinout.port, _pinout.pin);
}

uint16_t Gpio::port_read() const
{
    return gpio_port_read(_pinout.port);
}

void Gpio::port_write(uint16_t data)
{
    gpio_port_write(_pinout.port, data);
}

void Gpio::port_config_lock()
{
    gpio_port_config_lock(_pinout.port, _pinout.pin);
}

void Gpio::mode_setup(Mode mode, PullMode pull_mode)
{
    uint8_t _mode;
    uint8_t _pull_mode;

    switch (mode) {
        case INPUT:
            _mode = GPIO_MODE_INPUT;
            break;
        case OUTPUT:
            _mode = GPIO_MODE_OUTPUT;
            break;
        case ALTERNATE_FUNCTION:
            _mode = GPIO_MODE_AF;
            break;
        case ANALOG:
            _mode = GPIO_MODE_ANALOG;
            break;
    }

    switch (pull_mode) {
        case NO_PULL:
            _pull_mode = GPIO_PUPD_NONE;
            break;
        case PULL_UP:
            _pull_mode = GPIO_PUPD_PULLUP;
            break;
        case PULL_DOWN:
            _pull_mode = GPIO_PUPD_PULLDOWN;
            break;
    }

    gpio_mode_setup(_pinout.port, _mode, _pull_mode, _pinout.pin);
}

void Gpio::set_output_options(OutputType type, Speed speed)
{
    uint8_t _type;
    uint8_t _speed;

    switch (type) {
        case PUSH_PULL:
            _type = GPIO_OTYPE_PP;
            break;
        case OPEN_DRAIN:
            _type = GPIO_OTYPE_OD;
            break;
    }

    switch (speed) {
        case LOW_2MHz:
            _speed = GPIO_OSPEED_2MHZ;
            break;
        case MEDIUM_25MHz:
            _speed = GPIO_OSPEED_25MHZ;
            break;
        case FAST_50MHz:
            _speed = GPIO_OSPEED_50MHZ;
            break;
        case HIGH_SPEED_100MHz:
            _speed = GPIO_OSPEED_100MHZ;
            break;
    }

    gpio_set_output_options(_pinout.port, _type, _speed, _pinout.pin);
}

void Gpio::set_af(AltFuncNumber af_num)
{
    uint8_t _af;
    switch (af_num) {
        case AF0:
            _af = GPIO_AF0;
            break;
        case AF1:
            _af = GPIO_AF1;
            break;
        case AF2:
            _af = GPIO_AF2;
            break;
        case AF3:
            _af = GPIO_AF3;
            break;
        case AF4:
            _af = GPIO_AF4;
            break;
        case AF5:
            _af = GPIO_AF5;
            break;
        case AF6:
            _af = GPIO_AF6;
            break;
        case AF7:
            _af = GPIO_AF7;
            break;
        case AF8:
            _af = GPIO_AF8;
            break;
        case AF9:
            _af = GPIO_AF9;
            break;
        case AF10:
            _af = GPIO_AF10;
            break;
        case AF11:
            _af = GPIO_AF11;
            break;
        case AF12:
            _af = GPIO_AF12;
            break;
        case AF13:
            _af = GPIO_AF13;
            break;
        case AF14:
            _af = GPIO_AF14;
            break;
        case AF15:
            _af = GPIO_AF15;
            break;
    }

    gpio_set_af(_pinout.port, _af, _pinout.pin);
}

void Gpio::setup_exti(exti_trigger_type trigger)
{
    exti_select_source(_pinout.pin, _pinout.port);
    exti_set_trigger(_pinout.pin, trigger);
    exti_enable_request(_pinout.pin);
}

void Gpio::clear_exti_pending_bit()
{
    exti_reset_request(_pinout.pin);
}

bool Gpio::get_exti_flag_status() const
{
    uint32_t flag = exti_get_flag_status(_pinout.pin);
    if (flag != 0)
        return true;
    return false;
}

}  // namespace gpio

}  // namespace cm3cpp
