/**
 ******************************************************************************
 * @file    cm3cpp_usart_dma.cpp
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
#include "cm3cpp_usart_dma.hpp"

#include <cm3cpp_config.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <string.h>

namespace cm3cpp {

namespace usart_dma {

/**
 * Constructor USART-DMA
 * @param usart_config - low level config usart
 * @param settings - usart settings
 * @param dma_tx_config - DMA config for transmission
 * @param dma_rx_config - DMA config for receive
 */
UsartDma::UsartDma(const LowLevelConfigUsart& usart_config,
                   const Settings& settings,
                   const dma::LowLevelConfig& dma_tx_config,
                   const dma::LowLevelConfig& dma_rx_config) :
  _dma_tx(dma_tx_config),
  _dma_rx(dma_rx_config)
{
    // For reset and clock periph
    rcc_periph_rst rcc_rst;
    rcc_periph_clken rcc_clken;

    switch (usart_config.usart_number) {
        case 1: {
            _usart = USART1;
            rcc_rst = RST_USART1;
            rcc_clken = RCC_USART1;
            break;
        }
        case 2: {
            _usart = USART2;
            rcc_rst = RST_USART2;
            rcc_clken = RCC_USART2;
            break;
        }
        case 3: {
            _usart = USART3;
            rcc_rst = RST_USART3;
            rcc_clken = RCC_USART3;
            break;
        }
        case 4: {
            _usart = UART4;
            rcc_rst = RST_UART4;
            rcc_clken = RCC_UART5;
            break;
        }
        case 5: {
            _usart = UART5;
            rcc_rst = RST_UART5;
            rcc_clken = RCC_UART5;
            break;
        }
        default: {
            _usart = USART6;
            rcc_rst = RST_USART6;
            rcc_clken = RCC_USART6;
            break;
        }
    }

    // Reset periph
    rcc_periph_reset_pulse(rcc_rst);
    // Clock enable
    rcc_periph_clock_enable(rcc_clken);

    uint8_t af = GPIO_AF8;
    if ((usart_config.usart_number >= 1) && (usart_config.usart_number <= 3)) {
        af = GPIO_AF7;
    }

    // Config GPIO
    if (settings.mode == TX || settings.mode == RX_TX) {
        // Pin transmit
        port_config_clock_enable(usart_config.tx.port);
        gpio_mode_setup(usart_config.tx.port, GPIO_MODE_AF, GPIO_PUPD_NONE,
                        usart_config.tx.pin);

        gpio_set_af(usart_config.tx.port, af, usart_config.tx.pin);
        usart_enable_tx_dma(_usart);
    }

    if (settings.mode == RX || settings.mode == RX_TX) {
        // Pin receive
        port_config_clock_enable(usart_config.rx.port);
        gpio_mode_setup(usart_config.rx.port, GPIO_MODE_AF, GPIO_PUPD_NONE,
                        usart_config.rx.pin);

        gpio_set_af(usart_config.tx.port, af, usart_config.tx.pin);
        gpio_set_output_options(usart_config.rx.port, GPIO_OTYPE_OD,
                                GPIO_OSPEED_100MHZ, usart_config.rx.pin);
        usart_enable_rx_dma(_usart);
    }

    // Config USART
    init_uasrt(settings);

    // Enable USART
    enable();
}

/**
 * Enable clock port GPIO
 * @param port - port GPIO
 */
void UsartDma::port_config_clock_enable(uint32_t port) const
{
    rcc_periph_clken clken;
    if (port == GPIOA) {
        clken = RCC_GPIOA;
    }
    else if (port == GPIOB) {
        clken = RCC_GPIOB;
    }
    else if (port == GPIOC) {
        clken = RCC_GPIOC;
    }
    else if (port == GPIOD) {
        clken = RCC_GPIOD;
    }
    else if (port == GPIOE) {
        clken = RCC_GPIOE;
    }
    else if (port == GPIOF) {
        clken = RCC_GPIOF;
    }
    else if (port == GPIOG) {
        clken = RCC_GPIOG;
    }

    rcc_periph_clock_enable(clken);
}

/**
 * Config USART
 * @param settings - settings for usart
 */
void UsartDma::init_uasrt(const Settings& settings) const
{
    // Setup parameters
    usart_set_baudrate(_usart, settings.baud_rate);
    usart_set_databits(_usart, settings.word_length);
    usart_set_stopbits(_usart, settings.stop_bits);
    usart_set_mode(_usart, settings.mode);
    usart_set_parity(_usart, settings.parity);
    usart_set_flow_control(_usart, settings.flow_control);
}

/**
 * Usart enable
 */
void UsartDma::enable() const
{
    usart_enable(_usart);
}

/**
 * Usart disable
 */
void UsartDma::disable() const
{
    usart_disable(_usart);
}

/**
 * Sending data to USART(not safe)
 * @param data - data reference
 * @param len - data length
 */
void UsartDma::write(uint8_t& data, uint16_t len)
{
    _dma_tx.set_memory_address((uint32_t)(&data));
    _dma_tx.set_data_counter(len);

    // Enable sending, disable it in the interrupt
    _dma_tx.enable_stream();
}

}  // namespace usart_dma

}  // namespace cm3cpp
