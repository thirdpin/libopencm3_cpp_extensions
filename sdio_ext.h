#ifndef HW_SDIO_H_
#define HW_SDIO_H_

#include "gpio_ext.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/sdio.h>

namespace cm3ext {

namespace sdio {


namespace config {
constexpr auto RCC_PERIPH_DATA_CLK = rcc_periph_clken::RCC_GPIOC;
constexpr auto RCC_PERIPH_CMD = rcc_periph_clken::RCC_GPIOD;
constexpr uint8_t COUNT_OF_DATA_PINS = 4;
constexpr gpio::Pinout DATA_PINS[COUNT_OF_DATA_PINS] = {PC8, PC9, PC10, PC11};
constexpr gpio::Pinout CLK_PIN = PC12;
constexpr gpio::Pinout CMD_PIN = PD2;
constexpr gpio::AltFuncNumber SDIO_ALTERNATIVE_FUNC_NUMBER = gpio::AltFuncNumber::AF12;
}

class Sdio {
public:
	struct Config {

	};
	
	Sdio() {
		_init();
	}

	~Sdio() = default;

private:
	void _init();
	void _init_rcc();
	void _init_gpio();
};

} /* namespace SDIO_CPP_Extension */


} // namespace cm3ext

#endif /* HW_SDIO_H_ */
