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

#include "systick.hpp"

#ifndef CM3CPP_CUSTOM_SYSTICK
static volatile uint32_t counter;

void sys_tick_handler(void)
{
    counter++;
}
#endif

void delay_nop(uint32_t count)
{
    while (count--) {
        __asm("nop");
    }
}

namespace cm3cpp {

namespace systick {

#ifndef CM3CPP_CUSTOM_SYSTICK
void delay_systick(uint32_t ms)
{
    uint32_t time = get_counter();
    while ((get_counter() - time) < ms) {
        __asm("nop");
    }
}
#endif  // CM3CPP_CUSTOM_SYSTICK

void init(uint32_t system_core_freq, uint32_t clock_div)
{
#ifndef CM3CPP_CUSTOM_SYSTICK
    counter = 0;
#endif
    systick_set_reload(system_core_freq / clock_div);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    systick_interrupt_enable();
}

void deinit()
{
    systick_interrupt_disable();
    systick_counter_disable();
}

#ifndef CM3CPP_CUSTOM_SYSTICK
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

    switch (_mode) {
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
        switch (_mode) {
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
    if (_mode == CYCLE)
        return false;
    _saved = get_counter();
    _is_active = true;
    return true;
}

bool Counter::stop()
{
    if (_mode == CYCLE)
        return false;
    _is_active = false;
    return true;
}

#endif  // CM3CPP_CUSTOM_SYSTICK
}  // namespace systick


}  // namespace cm3cpp
