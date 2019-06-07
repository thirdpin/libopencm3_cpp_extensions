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

#ifndef SPI_EXT_H
#define SPI_EXT_H

#include <libopencm3/stm32/spi.h>

#include "cm3cpp_gpio.h"
#include "irq/cm3cpp_irq.h"

namespace cm3cpp {

namespace spi {

constexpr bool OK = true;
constexpr bool ERROR = false;

enum Flag : uint32_t
{
    RECEIVE_BUFFER_NOT_EMPTY = 0x0001,
    TRANSMIT_BUFFER_EMPTY = 0x0002,
    CHANEL_SIDE = 0x0004,
    UNDERRUN_FLAG = 0x0008,
    CRC_ERROR = 0x0010,
    MODE_FAULT = 0x0020,
    OVERRUN_FLAG = 0x0040,
    BUSY_FLAG = 0x0080,
    TI_FRAME_FORMAT_ERROR = 0x0100,
};

enum BaudRate : uint8_t
{
    BAUDRATE_FPCLK_DIV_2 = 0x00,
    BAUDRATE_FPCLK_DIV_4 = 0x01,
    BAUDRATE_FPCLK_DIV_8 = 0x02,
    BAUDRATE_FPCLK_DIV_16 = 0x03,
    BAUDRATE_FPCLK_DIV_32 = 0x04,
    BAUDRATE_FPCLK_DIV_64 = 0x05,
    BAUDRATE_FPCLK_DIV_128 = 0x06,
    BAUDRATE_FPCLK_DIV_256 = 0x07,
};

enum NextTx
{
    NEXT_TX_FROM_BUFFER,
    NEXT_TX_FROM_CRC
};

enum DataFrameFormat
{
    DFF_8BIT,
    DFF_16BIT
};

enum State
{
    DISABLE,
    ENABLE
};

enum NssState
{
    LOW,
    HIGH
};

enum Polarity
{
    POLARITY_LOW,
    POLARITY_HIGH
};

enum Phase
{
    PHASE_LOW,
    PHASE_HIGH
};

enum BitPos
{
    MSB_FIRST,
    LSB_FIRST
};

enum StdMode
{
    MODE_0 = 0,
    MODE_1,
    MODE_2,
    MODE_3
};

class Spi : public IInterruptable
{
 public:
    using Gpio = gpio::Gpio;

    struct Config
    {
        uint8_t spi_number;
        Gpio::Pinout mosi_pin;
        Gpio::Pinout miso_pin;
        Gpio::Pinout scl_pin;
    };

    Spi();
    Spi(Config spi_conf);

    void call();

    bool get_flag_status(Flag flag) const;

    void reset() { spi_reset(_spi); }

    void enable() { spi_enable(_spi); }

    void disable() { spi_disable(_spi); }

    void clean_disable() { spi_clean_disable(_spi); }

    void write(uint16_t data)
    {
        while (!get_flag_status(Flag::TRANSMIT_BUFFER_EMPTY))
            ;
        SPI_DR(_spi) = data;
    }

    void write_end()
    {
        while (!get_flag_status(Flag::RECEIVE_BUFFER_NOT_EMPTY))
            ;
        (void)SPI_DR(_spi);
    }

    uint16_t read(uint16_t data)
    {
        while (!get_flag_status(Flag::TRANSMIT_BUFFER_EMPTY))
            ;
        SPI_DR(_spi) = data;
        while (!get_flag_status(Flag::RECEIVE_BUFFER_NOT_EMPTY))
            ;
        return SPI_DR(_spi);
    }

    void set_master_mode() { spi_set_master_mode(_spi); }

    void set_slave_mode() { spi_set_slave_mode(_spi); }

    void full_duplex_mode() { spi_set_full_duplex_mode(_spi); }

    void set_bidirectional_mode() { spi_set_bidirectional_mode(_spi); }

    void set_bidirectional_transmit_only_mode()
    {
        spi_set_bidirectional_transmit_only_mode(_spi);
    }

    void set_bidirectional_receive_only_mode()
    {
        spi_set_bidirectional_receive_only_mode(_spi);
    }

    void set_unidirectional_mode() { spi_set_unidirectional_mode(_spi); }

    void set_receive_only_mode() { spi_set_receive_only_mode(_spi); }

    void enable_crc() { spi_enable_crc(_spi); }

    void disable_crc() { spi_disable_crc(_spi); }

    void set_next_tx_from(NextTx next);
    void set_data_drame_format(DataFrameFormat dff);
    void set_software_slave_management(State state);
    void set_nss(NssState nss);
    void set_bit_position(BitPos pos);

    void set_baudrate_prescaler(BaudRate baudrate)
    {
        spi_set_baudrate_prescaler(_spi, (uint8_t)baudrate);
    }

    void set_clock_polarity(Polarity polarity);
    void set_clock_phase(Phase phase);

    void enable_nvic();

    void enable_tx_buffer_empty_interrupt()
    {
        spi_enable_tx_buffer_empty_interrupt(_spi);
    }

    void disable_tx_buffer_empty_interrupt()
    {
        spi_disable_tx_buffer_empty_interrupt(_spi);
    }

    void enable_rx_buffer_not_empty_interrupt()
    {
        spi_enable_rx_buffer_not_empty_interrupt(_spi);
    }

    void disable_rx_buffer_not_empty_interrupt()
    {
        spi_disable_rx_buffer_not_empty_interrupt(_spi);
    }

    void enable_error_interrupt() { spi_enable_error_interrupt(_spi); }

    void disable_error_interrupt() { spi_disable_error_interrupt(_spi); }

    void enable_ss_output() { spi_enable_ss_output(_spi); }

    void disable_ss_output() { spi_disable_ss_output(_spi); }

    void enable_tx_dma() { spi_enable_tx_dma(_spi); }

    void disable_tx_dma() { spi_disable_tx_dma(_spi); }

    void enable_rx_dma() { spi_enable_rx_dma(_spi); }

    void disable_rx_dma() { spi_disable_rx_dma(_spi); }

    void set_standard_mode(StdMode mode) { spi_set_standard_mode(_spi, mode); }

 private:
    uint32_t _spi;
    Interrupt _irq;
};

}  // namespace spi

}  // namespace cm3cpp

#endif
