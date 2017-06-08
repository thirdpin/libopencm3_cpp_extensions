#include "sdio_ext.h"

namespace cm3ext {

namespace sdio {

namespace cfg = config;

void Sdio::_init()
{
	_init_rcc();
	_init_gpio();
}

void Sdio::_init_rcc()
{
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_SDIOEN);

	rcc_periph_clock_enable(cfg::RCC_PERIPH_DATA_CLK);
	rcc_periph_clock_enable(cfg::RCC_PERIPH_CMD);
}

void Sdio::_init_gpio()
{
    // Pin mappings for STM32F217.
    // PC8  - SDIO_D0
    // PC9  - SDIO_D1
    // PC10 - SDIO_D2
    // PC11 - SDIO_D3
    // PC12 - SDIO_CK
    // PD2  - SDIO_CMD

	// Data pins
	gpio::Gpio data_pins[cfg::COUNT_OF_DATA_PINS];
	for (int i = 0; i < cfg::COUNT_OF_DATA_PINS; ++i) {
		data_pins[i].init(cfg::DATA_PINS[i]);
		data_pins[i].mode_setup(gpio::Mode::ALTERNATE_FUNCTION,
							    gpio::PullMode::NO_PULL);
		data_pins[i].set_output_options(gpio::OutputType::PUSH_PULL,
									    gpio::Speed::FAST_50MHz);
		data_pins[i].set_af(cfg::SDIO_ALTERNATIVE_FUNC_NUMBER);
	}

	// Command pin
	gpio::Gpio cmd_pin(cfg::CMD_PIN);
	cmd_pin.mode_setup(gpio::Mode::ALTERNATE_FUNCTION,
					   gpio::PullMode::NO_PULL);
	cmd_pin.set_output_options(gpio::OutputType::PUSH_PULL,
							   gpio::Speed::FAST_50MHz);
	cmd_pin.set_af(cfg::SDIO_ALTERNATIVE_FUNC_NUMBER);

	// Clock pin
	gpio::Gpio clk_pin(cfg::CLK_PIN);
	clk_pin.mode_setup(gpio::Mode::ALTERNATE_FUNCTION,
					   gpio::PullMode::NO_PULL);
	clk_pin.set_output_options(gpio::OutputType::PUSH_PULL,
							   gpio::Speed::FAST_50MHz);
	clk_pin.set_af(cfg::SDIO_ALTERNATIVE_FUNC_NUMBER);
}


} // namespace sdio

} // namespace cm3ext
