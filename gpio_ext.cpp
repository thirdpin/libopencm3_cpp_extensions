#include "gpio_ext.h"
using namespace GPIO_CPP_Extension;

GPIO_ext::GPIO_ext(Pinout pinout)
{
	_pinout = pinout;
}
void GPIO_ext::init(Pinout pinout)
{
	_pinout = pinout;
}
void GPIO_ext::set()
{
	gpio_set(_pinout.port, _pinout.pin);
}
void GPIO_ext::clear()
{
	gpio_clear(_pinout.port, _pinout.pin);
}
uint16_t GPIO_ext::get()
{
	return gpio_get(_pinout.port, _pinout.pin);
}
void GPIO_ext::toggle()
{
	gpio_toggle(_pinout.port, _pinout.pin);
}
uint16_t GPIO_ext::port_read()
{
	return gpio_port_read(_pinout.port);
}
void GPIO_ext::port_write(uint16_t data)
{
	gpio_port_write(_pinout.port, data);
}
void GPIO_ext::port_config_lock()
{
	gpio_port_config_lock (_pinout.port, _pinout.pin);
}
void GPIO_ext::mode_setup(Mode mode, PullMode pull_mode)
{
	uint8_t _mode;
	uint8_t _pull_mode;

	switch (mode)
	{
		case INPUT:
			_mode = GPIO_MODE_INPUT;
			break;
		case OUTPUT:
			_mode = GPIO_MODE_OUTPUT;
			break;
		case ALTERNATE_FUNCTION:
			_mode = GPIO_MODE_AF;
			break;
		case ANALOG:
			_mode = GPIO_MODE_ANALOG;
			break;
	}

	switch (pull_mode)
	{
		case NO_PULL:
			_pull_mode = GPIO_PUPD_NONE;
			break;
		case PULL_UP:
			_pull_mode = GPIO_PUPD_PULLUP;
			break;
		case PULL_DOWN:
			_pull_mode = GPIO_PUPD_PULLDOWN;
			break;
	}

	gpio_mode_setup(_pinout.port, _mode, _pull_mode, _pinout.pin);
}
void GPIO_ext::set_output_options(OutputType type, Speed speed)
{
	uint8_t _type;
	uint8_t _speed;

	switch (type)
	{
		case PUSH_PULL:
			_type = GPIO_OTYPE_PP;
			break;
		case OPEN_DRAIN:
			_type = GPIO_OTYPE_OD;
			break;
	}

	switch (speed)
	{
		case LOW_2MHz:
			_speed = GPIO_OSPEED_2MHZ;
			break;
		case MEDIUM_25MHz:
			_speed = GPIO_OSPEED_25MHZ;
			break;
		case FAST_50MHz:
			_speed = GPIO_OSPEED_50MHZ;
			break;
		case HIGH_SPEED_100MHz:
			_speed = GPIO_OSPEED_100MHZ;
			break;
	}

	gpio_set_output_options(_pinout.port, _type, _speed, _pinout.pin);
}

void GPIO_ext::set_af(AF_Number af_num)
{
	uint8_t _af;
	switch (af_num)
	{
		case AF0:
			_af = GPIO_AF0;
			break;
		case AF1:
			_af = GPIO_AF1;
			break;
		case AF2:
			_af = GPIO_AF2;
			break;
		case AF3:
			_af = GPIO_AF3;
			break;
		case AF4:
			_af = GPIO_AF4;
			break;
		case AF5:
			_af = GPIO_AF5;
			break;
		case AF6:
			_af = GPIO_AF6;
			break;
		case AF7:
			_af = GPIO_AF7;
			break;
		case AF8:
			_af = GPIO_AF8;
			break;
		case AF9:
			_af = GPIO_AF9;
			break;
		case AF10:
			_af = GPIO_AF10;
			break;
		case AF11:
			_af = GPIO_AF11;
			break;
		case AF12:
			_af = GPIO_AF12;
			break;
		case AF13:
			_af = GPIO_AF13;
			break;
		case AF14:
			_af = GPIO_AF14;
			break;
		case AF15:
			_af = GPIO_AF15;
			break;
	}

	gpio_set_af(_pinout.port, _af, _pinout.pin);
}

void GPIO_ext::set_exti_irq(exti_trigger_type trigger, uint8_t nvic)
{
	nvic_enable_irq(nvic);
	exti_select_source(_pinout.pin, _pinout.port);
	exti_set_trigger(_pinout.pin, trigger);
	exti_enable_request(_pinout.pin);
}

void GPIO_ext::clear_exti_pending_bit()
{
	exti_reset_request(_pinout.pin);
}
