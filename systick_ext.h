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

#ifndef SYSTICK_API_H
#define SYSTICK_API_H

#include <stdint.h>
#include <libopencm3/cm3/systick.h>

//must be changed according to your RCC configuration
#define SYSTEM_CORE_CLOCK						(uint32_t)120000000
#define SYSTEM_CORE_CLOCK_DIV                   (uint32_t)1000

extern "C" void sys_tick_handler(void);
extern "C" void delay_nop(uint32_t count);

typedef enum {
	CYCLE,
	ONE_SHOT
}TimerMode;

void systick_init(uint32_t div = SYSTEM_CORE_CLOCK_DIV);
uint32_t get_counter_ms();
void delay_ms(uint32_t ms);

class TimerMs
{
public:
	TimerMs(TimerMode mode, uint32_t period_ms);
	bool timeout();
	bool start();
	bool stop();

private:
	uint32_t _saved_ms;
	uint32_t _period_ms;
	TimerMode _mode;
	bool _is_active;
};


#endif
