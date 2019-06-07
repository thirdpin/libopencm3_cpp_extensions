/**
 ******************************************************************************
 * @file    dma
 * @author
 * @version V1.0
 * @date    05-2019
 * @brief   This is file realise uart.
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "dma.hpp"

// LIBOPENCM3 INCLUDES
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scs.h>
#include <libopencm3/stm32/rcc.h>

namespace cm3cpp {

namespace dma {

Dma::Dma(const LowLevelConfig& config) :
  _dma_num(config.dma_num),
  _stream(config.stream),
  _irq(config.irq)
{
    // Enable clock DMA
    if (_dma_num == DmaNumber::_1) {
        rcc_periph_clock_enable(RCC_DMA1);
    }
    else {
        rcc_periph_clock_enable(RCC_DMA2);
    }

    // Reset channel
    dma_stream_reset(_dma_num, _stream);

    // Config DMA
    dma_set_priority(_dma_num, _stream, config.priority);
    dma_set_memory_size(_dma_num, _stream, config.mem_size);
    dma_set_peripheral_size(_dma_num, _stream, config.periph_size);

    if (config.periph_inc_mode == IncrementedMode::ENABLE) {
        dma_enable_peripheral_increment_mode(_dma_num, _stream);
    }
    else {
        dma_disable_peripheral_increment_mode(_dma_num, _stream);
    }

    if (config.mem_inc_mode == IncrementedMode::ENABLE) {
        dma_enable_memory_increment_mode(_dma_num, _stream);
    }
    else {
        dma_disable_memory_increment_mode(_dma_num, _stream);
    }

    if (config.mode == Mode::CIRCULAR) {
        dma_enable_circular_mode(_dma_num, _stream);
    }

    dma_set_transfer_mode(_dma_num, _stream, config.direction);

    dma_set_peripheral_address(_dma_num, _stream, config.peripheral_base_addr);

    dma_channel_select(_dma_num, _stream, config.channel);

    /// Configure interrupt
    dma_enable_transfer_complete_interrupt(_dma_num, _stream);
    enable_irq();
}

void Dma::set_memory_address(uint32_t address) const
{
    dma_set_memory_address(_dma_num, _stream, address);
}

void Dma::set_data_counter(uint16_t len) const
{
    dma_set_number_of_data(_dma_num, _stream, len);
}

void Dma::enable_stream() const
{
    dma_enable_stream(_dma_num, _stream);
}

void Dma::disable_stream() const
{
    dma_disable_stream(_dma_num, _stream);
}

void Dma::enable_irq() const
{
    nvic_enable_irq(_irq);
}

void Dma::disable_irq() const
{
    nvic_disable_irq(_irq);
}

bool Dma::get_interrupt_flag() const
{
    return dma_get_interrupt_flag(_dma_num, _stream, DMA_TCIF);
}

void Dma::clear_interrupt_flag() const
{
    dma_clear_interrupt_flags(_dma_num, _stream, DMA_TCIF);
}

}  // namespace dma
}  // namespace cm3cpp
