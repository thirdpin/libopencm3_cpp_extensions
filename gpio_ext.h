/*
 * This file is part of the libopencm3_cpp_extensions project.
 * hosted at http://github.com/thirdpin/libopencm3_cpp_extensions
 *
 * Copyright (C) 2016  Third Pin LLC
 * Written by Anastasiia Lazareva <a.lazareva@thirdpin.ru>
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
GPIO C++ Wrapper of libopencm3 library for STM32F2, STM32F4 
*/

#ifndef GPIO_EXT_H
#define GPIO_EXT_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif

#define PINOUT_CTOR(port, pin)                     	{GPIO##port, GPIO##pin}

#define PA0										   	PINOUT_CTOR(A, 0)
#define PA1											PINOUT_CTOR(A, 1)
#define PA2											PINOUT_CTOR(A, 2)
#define PA3											PINOUT_CTOR(A, 3)
#define PA4										    PINOUT_CTOR(A, 4)
#define PA5											PINOUT_CTOR(A, 5)
#define PA6											PINOUT_CTOR(A, 6)
#define PA7											PINOUT_CTOR(A, 7)
#define PA8											PINOUT_CTOR(A, 8)
#define PA9											PINOUT_CTOR(A, 9)
#define PA10										PINOUT_CTOR(A, 10)
#define PA11										PINOUT_CTOR(A, 11)
#define PA12										PINOUT_CTOR(A, 12)
#define PA13										PINOUT_CTOR(A, 13)
#define PA14										PINOUT_CTOR(A, 14)
#define PA15										PINOUT_CTOR(A, 15)

#define PB0											PINOUT_CTOR(B, 0)
#define PB1											PINOUT_CTOR(B, 1)
#define PB2											PINOUT_CTOR(B, 2)
#define PB3											PINOUT_CTOR(B, 3)
#define PB4											PINOUT_CTOR(B, 4)
#define PB5											PINOUT_CTOR(B, 5)
#define PB6											PINOUT_CTOR(B, 6)
#define PB7											PINOUT_CTOR(B, 7)
#define PB8											PINOUT_CTOR(B, 8)
#define PB9											PINOUT_CTOR(B, 9)
#define PB10										PINOUT_CTOR(B, 10)
#define PB11										PINOUT_CTOR(B, 11)
#define PB12										PINOUT_CTOR(B, 12)
#define PB13										PINOUT_CTOR(B, 13)
#define PB14										PINOUT_CTOR(B, 14)
#define PB15										PINOUT_CTOR(B, 15)

#define PC0											PINOUT_CTOR(C, 0)
#define PC1											PINOUT_CTOR(C, 1)
#define PC2											PINOUT_CTOR(C, 2)
#define PC3											PINOUT_CTOR(C, 3)
#define PC4											PINOUT_CTOR(C, 4)
#define PC5											PINOUT_CTOR(C, 5)
#define PC6											PINOUT_CTOR(C, 6)
#define PC7											PINOUT_CTOR(C, 7)
#define PC8											PINOUT_CTOR(C, 8)
#define PC9											PINOUT_CTOR(C, 9)
#define PC10										PINOUT_CTOR(C, 10)
#define PC11										PINOUT_CTOR(C, 11)
#define PC12										PINOUT_CTOR(C, 12)
#define PC13										PINOUT_CTOR(C, 13)
#define PC14										PINOUT_CTOR(C, 14)
#define PC15										PINOUT_CTOR(C, 15)

#define PD0											PINOUT_CTOR(D, 0)
#define PD1											PINOUT_CTOR(D, 1)
#define PD2											PINOUT_CTOR(D, 2)
#define PD3											PINOUT_CTOR(D, 3)
#define PD4											PINOUT_CTOR(D, 4)
#define PD5											PINOUT_CTOR(D, 5)
#define PD6											PINOUT_CTOR(D, 6)
#define PD7											PINOUT_CTOR(D, 7)
#define PD8											PINOUT_CTOR(D, 8)
#define PD9											PINOUT_CTOR(D, 9)
#define PD10										PINOUT_CTOR(D, 10)
#define PD11										PINOUT_CTOR(D, 11)
#define PD12										PINOUT_CTOR(D, 12)
#define PD13										PINOUT_CTOR(D, 13)
#define PD14										PINOUT_CTOR(D, 14)
#define PD15										PINOUT_CTOR(D, 15)

#define PE0											PINOUT_CTOR(E, 0)
#define PE1											PINOUT_CTOR(E, 1)
#define PE2											PINOUT_CTOR(E, 2)
#define PE3											PINOUT_CTOR(E, 3)
#define PE4											PINOUT_CTOR(E, 4)
#define PE5											PINOUT_CTOR(E, 5)
#define PE6											PINOUT_CTOR(E, 6)
#define PE7											PINOUT_CTOR(E, 7)
#define PE8											PINOUT_CTOR(E, 8)
#define PE9											PINOUT_CTOR(E, 9)
#define PE10									    PINOUT_CTOR(E, 10)
#define PE11										PINOUT_CTOR(E, 11)
#define PE12										PINOUT_CTOR(E, 12)
#define PE13										PINOUT_CTOR(E, 13)
#define PE14										PINOUT_CTOR(E, 14)
#define PE15										PINOUT_CTOR(E, 15)

#define PF0											PINOUT_CTOR(F, 0)
#define PF1											PINOUT_CTOR(F, 1)
#define PF2											PINOUT_CTOR(F, 2)
#define PF3											PINOUT_CTOR(F, 3)
#define PF4											PINOUT_CTOR(F, 4)
#define PF5											PINOUT_CTOR(F, 5)
#define PF6											PINOUT_CTOR(F, 6)
#define PF7											PINOUT_CTOR(F, 7)
#define PF8											PINOUT_CTOR(F, 8)
#define PF9											PINOUT_CTOR(F, 9)
#define PF10										PINOUT_CTOR(F, 10)
#define PF11										PINOUT_CTOR(F, 11)
#define PF12										PINOUT_CTOR(F, 12)
#define PF13										PINOUT_CTOR(F, 13)
#define PF14										PINOUT_CTOR(F, 14)
#define PF15										PINOUT_CTOR(F, 15)

#define PG0											PINOUT_CTOR(G, 0)
#define PG1											PINOUT_CTOR(G, 1)
#define PG2											PINOUT_CTOR(G, 2)
#define PG3											PINOUT_CTOR(G, 3)
#define PG4											PINOUT_CTOR(G, 4)
#define PG5											PINOUT_CTOR(G, 5)
#define PG6											PINOUT_CTOR(G, 6)
#define PG7											PINOUT_CTOR(G, 7)
#define PG8											PINOUT_CTOR(G, 8)
#define PG9											PINOUT_CTOR(G, 9)
#define PG10										PINOUT_CTOR(G, 10)
#define PG11										PINOUT_CTOR(G, 11)
#define PG12										PINOUT_CTOR(G, 12)
#define PG13										PINOUT_CTOR(G, 13)
#define PG14										PINOUT_CTOR(G, 14)
#define PG15										PINOUT_CTOR(G, 15)

#define PH0		                                    PINOUT_CTOR(H, 0)
#define PH1		                                    PINOUT_CTOR(H, 1)
#define PH2		                                    PINOUT_CTOR(H, 2)
#define PH3		                                    PINOUT_CTOR(H, 3)
#define PH4		                                    PINOUT_CTOR(H, 4)
#define PH5		                                    PINOUT_CTOR(H, 5)
#define PH6											PINOUT_CTOR(H, 6)
#define PH7											PINOUT_CTOR(H, 7)
#define PH8											PINOUT_CTOR(H, 8)
#define PH9											PINOUT_CTOR(H, 9)
#define PH10										PINOUT_CTOR(H, 10)
#define PH11										PINOUT_CTOR(H, 11)
#define PH12										PINOUT_CTOR(H, 12)
#define PH13										PINOUT_CTOR(H, 13)
#define PH14										PINOUT_CTOR(H, 14)
#define PH15										PINOUT_CTOR(H, 15)

#define PI0											PINOUT_CTOR(I, 0)
#define PI1											PINOUT_CTOR(I, 1)
#define PI2											PINOUT_CTOR(I, 2)
#define PI3											PINOUT_CTOR(I, 3)
#define PI4											PINOUT_CTOR(I, 4)
#define PI5											PINOUT_CTOR(I, 5)
#define PI6											PINOUT_CTOR(I, 6)
#define PI7											PINOUT_CTOR(I, 7)
#define PI8											PINOUT_CTOR(I, 8)
#define PI9											PINOUT_CTOR(I, 9)
#define PI10										PINOUT_CTOR(I, 10)
#define PI11										PINOUT_CTOR(I, 11)
#define PI12										PINOUT_CTOR(I, 12)
#define PI13										PINOUT_CTOR(I, 13)
#define PI14										PINOUT_CTOR(I, 14)
#define PI15										PINOUT_CTOR(I, 15)

namespace cm3ext {

namespace gpio {


struct Pinout {
	uint32_t port;
	uint16_t pin;
};

enum Mode {
	INPUT,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
};

enum PullMode {
	NO_PULL,
	PULL_UP,
	PULL_DOWN
};

enum OutputType {
	PUSH_PULL,
	OPEN_DRAIN
};

enum Speed {
	LOW_2MHz,
	MEDIUM_25MHz,
	FAST_50MHz,
	HIGH_SPEED_100MHz
};

enum AltFuncNumber {
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
};

class Gpio
{
public:
	Gpio() {}
	Gpio(Pinout pinout);

	void init(Pinout pinout);
	void set();
	void clear();
	uint16_t get();
	void toggle();
	uint16_t port_read();
	void port_write(uint16_t data);
	void port_config_lock();
	void mode_setup(Mode mode, PullMode pull_mode);
	void set_output_options(OutputType type, Speed speed);
	void set_af(AltFuncNumber af_num);
	void set_exti_irq(enum exti_trigger_type trigger, uint8_t nvic);
	void clear_exti_pending_bit();

private:
	Pinout _pinout;
};


} // namespace gpio

} // namespace cm3ext
#endif
