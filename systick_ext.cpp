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

#include "systick_ext.h"
#if CM3EXT_ENABLE_CUSTOM_SYSTICK_SOURCE == 1
extern "C" {
    void CM3EXT_SYS_TICK_INT_FUNC(void);
}
#include "libopencm3/stm32/timer.h"
#else
#define CM3EXT_SYS_TICK_INT_FUNC sys_tick_handler
#endif

volatile uint32_t counter;

void SYS_TICK_INT_FUNC(void)
{
#if CM3EXT_ENABLE_CUSTOM_SYSTICK_SOURCE == 1
    if (timer_get_flag(CM3EXT_INT_SOURCE, TIM_SR_UIF)) {
        timer_clear_flag(CM3EXT_INT_SOURCE, TIM_SR_UIF);
        counter++;
    }
#else
    counter++;
#endif
}

void delay_nop(uint32_t count)
{
	while(count--) {
		__asm("nop");
	}
}

namespace cm3ext {

namespace systick {


void delay_systick(uint32_t ms)
{
	uint32_t time = counter;
	while((counter - time) < ms);
}

//by default sets up a timer to create 1ms ticks (div = 1000)
//at system clock 120mhz.
void init(uint32_t div)
{
	counter = 0;
	systick_set_reload(CM3EXT_SYSTEM_CORE_CLOCK / div);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();
}

uint32_t get_counter()
{
	return counter;
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
	if (_is_active && ((counter - _saved) >= _period)) {
		switch (_mode)
		{
			case CYCLE:
				_saved = counter;
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
	_saved = counter;
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

}  // namespace cm3ext
