/*
 * This file is part of the libopencm3_cpp_extensions project.
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

volatile uint32_t counter_ms;

void sys_tick_handler(void)
{
	counter_ms++;
}

void delay_nop(uint32_t count)
{
	while(count--) {
		__asm("nop");
	}
}

void delay_ms(uint32_t ms)
{
	uint32_t time = counter_ms;
	while((counter_ms - time) < ms);
}

//by default sets up a timer to create 1ms ticks (div = 1000)
//at system clock 120mhz.
void systick_init(uint32_t div)
{
	counter_ms = 0;
	systick_set_reload(SYSTEM_CORE_CLOCK / div);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();
}

uint32_t get_counter_ms()
{
	return counter_ms;
}

TimerMs::TimerMs(TimerMode mode, uint32_t period_ms)
{
	_mode = mode;
	_saved_ms = get_counter_ms();
	_period_ms = period_ms;

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

bool TimerMs::timeout()
{
	if (_is_active && ((counter_ms - _saved_ms) >= _period_ms)) {
		switch (_mode)
		{
			case CYCLE:
				_saved_ms = counter_ms;
				return true;
			case ONE_SHOT:
				return true;
		}
	}

	return false;
}

bool TimerMs::start()
{
	if(_mode == CYCLE)
		return false;
	_saved_ms = counter_ms;
	_is_active = true;
	return true;
}

bool TimerMs::stop()
{
	if(_mode == CYCLE)
		return false;
	_is_active = false;
	return true;
}
