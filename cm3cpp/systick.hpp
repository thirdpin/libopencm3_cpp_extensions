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

#ifndef SYSTICK_API_H
#define SYSTICK_API_H

#include <libopencm3/cm3/systick.h>
#include <stdint.h>

#ifndef CM3CPP_CUSTOM_SYSTICK
extern "C" void sys_tick_handler(void);
#endif

extern "C" void delay_nop(uint32_t count);

namespace cm3cpp {

namespace systick {

void init(uint32_t system_core_freq, uint32_t div = 1000);
void deinit();

#ifndef CM3CPP_CUSTOM_SYSTICK

uint32_t get_counter();
void delay_systick(uint32_t ms);

class Counter
{
 public:
    enum Mode
    {
        CYCLE,
        ONE_SHOT
    };

    Counter(Mode mode, uint32_t period);
    void init(Mode mode, uint32_t period);
    bool timeout();
    bool start();
    bool stop();
    bool is_active() const;

    void set_period(uint32_t const period) { _period = period; }
    uint32_t period() const { return _period; }

 private:
    uint32_t _saved;
    uint32_t _period;
    Mode _mode;
    bool _is_active;
};

#endif  // CM3CPP_CUSTOM_SYSTICK

}  // namespace systick

}  // namespace cm3cpp
#endif
