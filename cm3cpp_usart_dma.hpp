/**
 ******************************************************************************
 * @file    cm3cpp_usart_dma.hpp
 * @author
 * @version V1.0
 * @date    05-2019
 * @brief   This is file realise usart.
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

// LIBOPENCM3 INCLUDES
#include <libopencm3/stm32/usart.h>

// CM3CPP INCLUDES
#include "cm3cpp_dma.hpp"
#include "cm3cpp_gpio.h"

namespace cm3cpp {

namespace usart_dma {

enum DataBits : uint8_t
{
    _8 = 8,
    _9 = 9
};

enum Mode : uint16_t
{
    RX = USART_MODE_RX,
    TX = USART_MODE_TX,
    RX_TX = USART_MODE_TX_RX
};

enum StopBits : uint16_t
{
    _0_5 = USART_STOPBITS_0_5,
    _1 = USART_STOPBITS_1,
    _1_5 = USART_STOPBITS_1_5,
    _2 = USART_STOPBITS_2
};

enum Parity : uint16_t
{
    PAR_NONE = USART_PARITY_NONE,
    PAR_EVEN = USART_PARITY_EVEN,
    PAR_ODD = USART_PARITY_ODD
};

enum FlowControl : uint16_t
{
    NONE = USART_FLOWCONTROL_NONE,
    RTS = USART_FLOWCONTROL_RTS,
    CTS = USART_FLOWCONTROL_CTS,
    RTS_CTS = USART_FLOWCONTROL_RTS_CTS
};

/// Low level config for USART
struct LowLevelConfigUsart
{
    uint8_t usart_number;
    gpio::Gpio::Pinout tx;
    gpio::Gpio::Pinout rx;
};

/// Settings USART
struct Settings
{
    uint32_t baud_rate;
    DataBits word_length;
    StopBits stop_bits;
    Parity parity;
    Mode mode;
    FlowControl flow_control;
};

/**
 * Class Usart & Dma
 */
class UsartDma
{
 public:
    /// Constructor
    UsartDma(const LowLevelConfigUsart& usart_config,
             const Settings& settings,
             const dma::LowLevelConfig& dma_tx_config,
             const dma::LowLevelConfig& dma_rx_config);

    /// Usart enable
    void enable() const;

    /// Usart disable
    void disable() const;

    /// Sending data to USART(not safe)
    void write(uint8_t& data, uint16_t len);

    /* These classes must be public because
        they can be accessed by interrupt handlers */
    class dma::Dma _dma_tx;  ///< DMA for transmission
    class dma::Dma _dma_rx;  ///< DMA for receive

 protected:
    UsartDma() = delete;                    /// Constructor default is delete
    UsartDma(const UsartDma& a) = delete;   /// Constructor copy is delete
    UsartDma(const UsartDma&& a) = delete;  /// Constructor move is delete

    UsartDma& operator=(const UsartDma&) = delete;  /// Operator copy is delete
    UsartDma& operator=(UsartDma&&) = delete;       /// Operator move is delete

 private:
    /// Set clock port GPIO
    void port_config_clock_enable(uint32_t port) const;

    /// Config USART
    void init_uasrt(const Settings& settings) const;

    uint32_t _usart;  ///< Number USART
};

}  // namespace usart_dma

}  // namespace cm3cpp
