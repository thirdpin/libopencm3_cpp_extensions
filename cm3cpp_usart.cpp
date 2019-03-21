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

#include "cm3cpp_usart.h"

namespace cm3cpp {

namespace usart {

Usart::Usart(LowLevelConfig config, Settings settings)
{
    init(config, settings);
}

void Usart::init(LowLevelConfig config, Settings settings)
{
    _mode = settings.mode;

    switch (config.usart_number) {
        case 1:
            _usart = USART1;
            _usart_nvic = NVIC_USART1_IRQ;
            break;
        case 2:
            _usart = USART2;
            _usart_nvic = NVIC_USART2_IRQ;
            break;
        case 3:
            _usart = USART3;
            _usart_nvic = NVIC_USART3_IRQ;
            break;
        case 4:
            _usart = UART4;
            _usart_nvic = NVIC_UART4_IRQ;
            break;
        case 5:
            _usart = UART5;
            _usart_nvic = NVIC_UART5_IRQ;
            break;
        case 6:
            _usart = USART6;
            _usart_nvic = NVIC_USART6_IRQ;
            break;
    }

    set_settings(settings);
    usart_enable(_usart);

    if (_mode == Mode::RX or _mode == Mode::RX_TX) {
        _rx.init(config.rx);

        if ((config.usart_number >= 1) && (config.usart_number <= 3))
            _rx.set_af(Gpio::AltFuncNumber::AF7);
        else
            _rx.set_af(Gpio::AltFuncNumber::AF8);

        _rx.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
        _rx.set_output_options(Gpio::OutputType::PUSH_PULL,
                               Gpio::Speed::MEDIUM_25MHz);
    }

    if (_mode == Mode::TX or _mode == Mode::RX_TX) {
        _tx.init(config.tx);

        if ((config.usart_number >= 1) && (config.usart_number <= 3))
            _tx.set_af(Gpio::AltFuncNumber::AF7);
        else
            _tx.set_af(Gpio::AltFuncNumber::AF8);

        _tx.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
        _tx.set_output_options(Gpio::OutputType::PUSH_PULL,
                               Gpio::Speed::MEDIUM_25MHz);
    }

    nvic_set_priority(_usart_nvic, config.nvic_priority);
    nvic_enable_irq(_usart_nvic);
}

void Usart::deinit()
{
    usart_disable(_usart);
    nvic_disable_irq(_usart_nvic);

    if (_mode == Mode::RX or _mode == Mode::RX_TX)
        _rx.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::NO_PULL);

    if (_mode == Mode::TX or _mode == Mode::RX_TX)
        _tx.mode_setup(Gpio::Mode::INPUT, Gpio::PullMode::NO_PULL);
}

void Usart::set_settings(Settings settings)
{
    _mode = settings.mode;
    usart_set_baudrate(_usart, settings.baud_rate);
    usart_set_databits(_usart, settings.word_length);
    usart_set_stopbits(_usart, settings.stop_bits);
    usart_set_mode(_usart, settings.mode);
    usart_set_parity(_usart, settings.parity);
    usart_set_flow_control(_usart, settings.flow_control);
}

}  // namespace usart

}  // namespace cm3cpp
