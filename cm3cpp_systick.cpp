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
SYSTICK implementation, public interface
*/

#include "cm3cpp_systick.h"

#define __EXPAND2(a,b) a ## b
#define __EXPAND3(a,b,c) a ## b ## c

#define __INT_SOURCE(n)          __EXPAND2(TIM, n)
#define __RCC(n)			     __EXPAND2(rcc_periph_clken::RCC_TIM, n)
#define __SYSTICK_INT_FUNC(n)    __EXPAND3(tim, n, _isr)

#define CM3CPP_INT_SOURCE        __INT_SOURCE(CM3CPP_TIMER_N)
#define CM3CPP_INT_SOURCE_RCC    __RCC(CM3CPP_TIMER_N)
#define CM3CPP_SYSTICK_INT_FUNC  __SYSTICK_INT_FUNC(CM3CPP_TIMER_N)

#if CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE == 1
extern "C" {
    void CM3CPP_SYSTICK_INT_FUNC(void);
}
#include "libopencm3/stm32/timer.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3_cpp_extensions/irq/cm3cpp_irq.h>
#else
#define CM3CPP_SYSTICK_INT_FUNC sys_tick_handler
#endif

volatile uint32_t counter;

#if CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE != 1
void CM3CPP_SYSTICK_INT_FUNC(void)
{
    counter++;
}
#endif

void delay_nop(uint32_t count)
{
	while(count--) {
		__asm("nop");
	}
}

namespace cm3cpp {

namespace systick {


void delay_systick(uint32_t ms)
{
	uint32_t time = get_counter();
	while((get_counter() - time) < ms);
}

void init(uint32_t clock_div)
{
#if CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE == 1
	rcc_periph_clock_enable(CM3CPP_INT_SOURCE_RCC);
	timer_reset(CM3CPP_INT_SOURCE);
	timer_set_mode(CM3CPP_INT_SOURCE, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(CM3CPP_INT_SOURCE, (CM3CPP_SYSTICK_CLOCK / clock_div) - 1);
	timer_disable_preload(CM3CPP_INT_SOURCE);
	timer_continuous_mode(CM3CPP_INT_SOURCE);
	timer_set_period(CM3CPP_INT_SOURCE, CM3CPP_SYSTICK_PERIOD);
	timer_enable_counter(CM3CPP_INT_SOURCE);
#else
	counter = 0;
	systick_set_reload(CM3CPP_SYSTEM_CORE_CLOCK / clock_div);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();
#endif
}

uint32_t get_counter()
{
#if CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE == 1
	return timer_get_counter(CM3CPP_INT_SOURCE);
#else
	return counter;
#endif
}

Counter::Counter(Mode mode, uint32_t period)
{
	init(mode, period);
}

void Counter::init(Mode mode, uint32_t period)
{
	_mode = mode;
	_saved = get_counter();
	_period = period;

	switch (_mode)
	{
		case CYCLE:
			_is_active = true;
			break;
		case ONE_SHOT:
			_is_active = false;
			break;
	}
}

bool Counter::timeout()
{
	if (_is_active && ((get_counter() - _saved) >= _period)) {
		switch (_mode)
		{
			case CYCLE:
				_saved = get_counter();
				return true;
			case ONE_SHOT:
				return true;
		}
	}

	return false;
}

bool Counter::start()
{
	if(_mode == CYCLE)
		return false;
	_saved = get_counter();
	_is_active = true;
	return true;
}

bool Counter::stop()
{
	if(_mode == CYCLE)
		return false;
	_is_active = false;
	return true;
}


}  // namespace systick

}  // namespace cm3cpp
