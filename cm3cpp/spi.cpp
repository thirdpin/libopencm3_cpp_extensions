/*
 * This file is part of the libopencm3_cpp_extensions project.
 * hosted at http://github.com/thirdpin/libopencm3_cpp_extensions
 *
 * Copyright (C) 2016  Third Pin LLC
 * Written by Anastasiia Lazareva <a.lazareva@thirdpin.ru>
 * Written by Maxim Ambrosevich
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
SPI C++ Wrapper of libopencm3 library for STM32F2, STM32F4
*/

#include "spi.hpp"

namespace cm3cpp {

namespace spi {

Spi::Spi(Config spi_conf)
{
    switch (spi_conf.spi_number) {
        case 1:
            _spi = SPI1;
            _irq = Interrupt::ISR_SPI1;
            break;
        case 2:
            _spi = SPI2;
            _irq = Interrupt::ISR_SPI2;
            break;
        case 3:
            _spi = SPI3;
            _irq = Interrupt::ISR_SPI3;
            break;
        default:
            break;
    }

    Gpio mosi(spi_conf.mosi_pin);
    mosi.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
    mosi.set_output_options(Gpio::OutputType::PUSH_PULL,
                            Gpio::Speed::HIGH_SPEED_100MHz);

    Gpio miso(spi_conf.miso_pin);
    miso.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
    miso.set_output_options(Gpio::OutputType::PUSH_PULL,
                            Gpio::Speed::HIGH_SPEED_100MHz);

    Gpio scl(spi_conf.scl_pin);
    scl.mode_setup(Gpio::Mode::ALTERNATE_FUNCTION, Gpio::PullMode::NO_PULL);
    scl.set_output_options(Gpio::OutputType::PUSH_PULL,
                           Gpio::Speed::HIGH_SPEED_100MHz);

    switch (_spi) {
        case SPI1:
        case SPI2:
            mosi.set_af(Gpio::AltFuncNumber::AF5);
            miso.set_af(Gpio::AltFuncNumber::AF5);
            scl.set_af(Gpio::AltFuncNumber::AF5);
            break;

        case SPI3:
            mosi.set_af(Gpio::AltFuncNumber::AF6);
            miso.set_af(Gpio::AltFuncNumber::AF6);
            scl.set_af(Gpio::AltFuncNumber::AF6);
            break;

        default:
            break;
    }
}

void Spi::set_next_tx_from(NextTx next)
{
    switch (next) {
        case NEXT_TX_FROM_BUFFER:
            spi_set_next_tx_from_buffer(_spi);
            break;
        case NEXT_TX_FROM_CRC:
            spi_set_next_tx_from_crc(_spi);
            break;
    }
}

void Spi::set_data_drame_format(DataFrameFormat dff)
{
    switch (dff) {
        case DFF_8BIT:
            spi_set_dff_8bit(_spi);
            break;
        case DFF_16BIT:
            spi_set_dff_16bit(_spi);
            break;
    }
}

void Spi::set_software_slave_management(State state)
{
    switch (state) {
        case DISABLE:
            spi_disable_software_slave_management(_spi);
            break;
        case ENABLE:
            spi_enable_software_slave_management(_spi);
            break;
    }
}

void Spi::set_nss(NssState nss)
{
    switch (nss) {
        case LOW:
            spi_set_nss_low(_spi);
            break;
        case HIGH:
            spi_set_nss_high(_spi);
            break;
    }
}

void Spi::set_bit_position(BitPos pos)
{
    switch (pos) {
        case MSB_FIRST:
            spi_send_msb_first(_spi);
            break;
        case LSB_FIRST:
            spi_send_lsb_first(_spi);
            break;
    }
}

void Spi::set_clock_polarity(Polarity polarity)
{
    switch (polarity) {
        case POLARITY_LOW:
            spi_set_clock_polarity_0(_spi);
            break;
        case POLARITY_HIGH:
            spi_set_clock_polarity_1(_spi);
            break;
    }
}

void Spi::set_clock_phase(Phase phase)
{
    switch (phase) {
        case PHASE_LOW:
            spi_set_clock_phase_0(_spi);
            break;
        case PHASE_HIGH:
            spi_set_clock_phase_1(_spi);
            break;
    }
}

bool Spi::get_flag_status(Flag flag) const
{
    const uint32_t reg_sr = SPI_SR(_spi);
    const uint32_t flag_state = reg_sr & static_cast<uint32_t>(flag);

    return flag == static_cast<Flag>(flag_state);
}

inline void Spi::enable_nvic()
{
    nvic_enable_irq(static_cast<uint8_t>(_irq));
}

}  // namespace spi

}  // namespace cm3cpp
