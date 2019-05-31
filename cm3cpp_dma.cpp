/**
 ******************************************************************************
 * @file    cm3cpp_dma
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
#include "cm3cpp_dma.hpp"

// LIBOPENCM3 INCLUDES
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scs.h>
#include <libopencm3/stm32/rcc.h>

namespace cm3cpp {

namespace dma {

Dma::Dma(const LowLevelConfig& config) :
  _num_dma(config.num_dma),
  _stream(config.stream),
  _irq(config.irq)
{
    // Enable clock DMA
    if (_num_dma == _1) {
        rcc_periph_clock_enable(RCC_DMA1);
    }
    else {
		rcc_periph_clock_enable(RCC_DMA2);
	}

	// Reset channel
    dma_stream_reset(_num_dma, _stream);

    // Config DMA
    dma_set_priority(_num_dma, _stream, config.priority);
    dma_set_memory_size(_num_dma, _stream, config.mem_size);
    dma_set_peripheral_size(_num_dma, _stream, config.periph_size);

    if (config.periph_inc_mode == INCREMENTED_ENABLE) {
        dma_enable_peripheral_increment_mode(_num_dma, _stream);
    }
    else {
        dma_disable_peripheral_increment_mode(_num_dma, _stream);
    }

    if (config.mem_inc_mode == INCREMENTED_ENABLE) {
        dma_enable_memory_increment_mode(_num_dma, _stream);
    }
    else {
        dma_disable_memory_increment_mode(_num_dma, _stream);
    }

    if (config.mode == CIRCULAR) {
        dma_enable_circular_mode(_num_dma, _stream);
    }

    dma_set_transfer_mode(_num_dma, _stream, config.direction);

    dma_set_peripheral_address(_num_dma, _stream, config.peripheral_base_addr);

    dma_channel_select(_num_dma, _stream, config.channel);

    /// Configure interrupt
    dma_enable_transfer_complete_interrupt(_num_dma, _stream);
    enable_irq();
}

void Dma::set_memory_address(uint32_t address) const
{
    dma_set_memory_address(_num_dma, _stream, address);
}

void Dma::set_data_counter(uint16_t len) const
{
    dma_set_number_of_data(_num_dma, _stream, len);
}

void Dma::enable_stream() const
{
    dma_enable_stream(_num_dma, _stream);
}

void Dma::disable_stream() const
{
    dma_disable_stream(_num_dma, _stream);
}

void Dma::enable_irq() const
{
    nvic_enable_irq(_irq);
}

void Dma::disable_irq() const
{
    nvic_disable_irq(_irq);
}
}

}  // namespace cm3cpp
