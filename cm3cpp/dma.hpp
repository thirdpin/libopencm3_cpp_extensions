/**
 ******************************************************************************
 * @file    dma.hpp
 * @author
 * @version V1.0
 * @date    05-2019
 * @brief   This is file realise DMA.
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

// LIBOPENCM3 INCLUDES
#include <libopencm3/stm32/dma.h>

namespace cm3cpp {

namespace dma {

enum DmaNumber
{
    _1 = DMA1,
    _2 = DMA2,
};

/// Streams for USARTs
enum Stream
{
    STREAM1 = DMA_STREAM1,
    STREAM2 = DMA_STREAM2,
    STREAM3 = DMA_STREAM3,
    STREAM4 = DMA_STREAM4,
    STREAM5 = DMA_STREAM5,
    STREAM6 = DMA_STREAM6,
    STREAM7 = DMA_STREAM7
};

/// Channels for USARTs
enum Channel
{
    CHANNEL1 = DMA_SxCR_CHSEL_1,
    CHANNEL2 = DMA_SxCR_CHSEL_2,
    CHANNEL3 = DMA_SxCR_CHSEL_3,
    CHANNEL4 = DMA_SxCR_CHSEL_4,
    CHANNEL5 = DMA_SxCR_CHSEL_5,
    CHANNEL6 = DMA_SxCR_CHSEL_6,
    CHANNEL7 = DMA_SxCR_CHSEL_7
};

enum DataTransferDirection
{
    MEM_TO_PERIPHERAL = DMA_SxCR_DIR_MEM_TO_PERIPHERAL,
    PERIPHERAL_TO_MEM = DMA_SxCR_DIR_PERIPHERAL_TO_MEM,
    MEM_TO_MEM = DMA_SxCR_DIR_MEM_TO_MEM
};

/// Shows where or where data will be sent, to the periphery or memory
enum class IncrementedMode
{
    DISABLE,
    ENABLE
};

/// Shows how much the size will be increased for the periphery
enum DataSize
{
    PERIPHERAL_BYTE = DMA_SxCR_PSIZE_8BIT,
    PERIPHERAL_HALF_WORD = DMA_SxCR_PSIZE_16BIT,
    PERIPHERAL_WORD = DMA_SxCR_PSIZE_32BIT,

    MEMORY_BYTE = DMA_SxCR_MSIZE_8BIT,
    MEMORY_HALF_WORD = DMA_SxCR_MSIZE_16BIT,
    MEMORY_WORD = DMA_SxCR_MSIZE_32BIT,
};

/// DMA data recording mode, cyclic or normal
enum class Mode
{
    NORMAL,
    CIRCULAR
};

/// The priorities of DMA
enum Priority
{
    LOW = DMA_SxCR_PL_LOW,
    MEDIUM = DMA_SxCR_PL_MEDIUM,
    HIGH = DMA_SxCR_PL_HIGH,
    VERY_HIGH = DMA_SxCR_PL_VERY_HIGH
};

/// Low level config for DMA
struct LowLevelConfig
{
    DmaNumber dma_num;
    Stream stream;
    Channel channel;
    uint32_t peripheral_base_addr;
    DataTransferDirection direction;
    IncrementedMode periph_inc_mode;
    IncrementedMode mem_inc_mode;
    DataSize periph_size;
    DataSize mem_size;
    Mode mode;
    Priority priority;
    uint8_t irq;
};

/**
 * Class hard DMA
 */
class Dma
{
 public:
    Dma(const LowLevelConfig& config);

    ~Dma() = default;

    bool get_interrupt_flag() const;

    void clear_interrupt_flag() const;

    void set_memory_address(uint32_t address) const;

    void enable_stream() const;

    void disable_stream() const;

    void set_data_counter(uint16_t len) const;

    void enable_irq() const;

    void disable_irq() const;

 protected:
    Dma() = delete;              /// Constructor default is delete
    Dma(const Dma& a) = delete;  /// Constructor copy is delete
    Dma(Dma&& a) = delete;       /// Constructor move is delete

    Dma& operator=(const Dma&) = delete;  /// Operator copy is delete
    Dma& operator=(Dma&&) = delete;       /// Operator move is delete

 private:
    DmaNumber _dma_num;  ///< Number configured DMA
    Stream _stream;      ///< Shows the stream on which DMA is configured

    uint8_t _irq;  ///< Interrupt number
};

}  // namespace dma

}  // namespace cm3cpp
