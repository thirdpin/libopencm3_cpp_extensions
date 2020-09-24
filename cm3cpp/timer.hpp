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
TIM C++ Wrapper of libopencm3 library for STM32F2, STM32F4
*/

#ifndef CM3CPP_TIMER_H_
#define CM3CPP_TIMER_H_

#include <cassert>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

namespace cm3cpp {

namespace tim {

class Timer
{
 public:
    enum Result
    {
        OK,
        USAGE_ERROR,
        NOT_SUPPORTED
    };

    enum UevSource
    {
        COUNTER_OVERFLOW_AND_UG,
        COUNTER_OVERFLOW,
    };

    enum CounterMode
    {
        ONE_SHOT,
        CONTINUOUS
    };

    enum CounterDirection
    {
        UP,
        DOWN
    };

    enum Alignment
    {
        EDGE,
        CENTER_DOWN,
        CENTER_UP,
        CENTER_UP_DOWN
    };

    enum ClockDivision
    {
        TIMER_CLOCK_MUL_1,
        TIMER_CLOCK_MUL_2,
        TIMER_CLOCK_MUL_4
    };

    enum MasterMode
    {
        MASTER_RESET,
        ENABLE,
        UPDATE,
        COMPARE_PULSE,
        COMPARE_OC1REF,
        COMPARE_OC2REF,
        COMPARE_OC3REF,
        COMPARE_OC4REF,
    };

    enum SlaveMode
    {
        DISABLED,
        SLAVE_RESET,
        GATED,
        TRIGGER,
        EXTERNAL_CLOCK
    };

    enum Trigger
    {
        INTERNAL_TRIGGER_0,
        INTERNAL_TRIGGER_1,
        INTERNAL_TRIGGER_2,
        INTERNAL_TRIGGER_3,
        EDGE_DETECTOR,
        FILTERED_TIMER_INPUT_1,
        FILTERED_TIMER_INPUT_2
    };

    enum Flag
    {
        UPDATE_INTERRUPT,
        CAPTURE_COMPARE_1_INTERRUPT,
        CAPTURE_COMPARE_2_INTERRUPT,
        CAPTURE_COMPARE_3_INTERRUPT,
        CAPTURE_COMPARE_4_INTERRUPT,
        TRIGGER_INTERRUPT,
        CAPTURE_COMPARE_1_OVERCAPTURE,
        CAPTURE_COMPARE_2_OVERCAPTURE,
        CAPTURE_COMPARE_3_OVERCAPTURE,
        CAPTURE_COMPARE_4_OVERCAPTURE
    };

    enum CcMode
    {
        OUTPUT,
        INPUT_MAPPED_TI1,
        INPUT_MAPPED_TI2,
        INPUT_MAPPED_TI3,
        INPUT_MAPPED_TI4,
        INPUT_MAPPED_TRC
    };

    enum Prescaler
    {
        NO_PRESCALER,
        CAPTURE_EVERY_2_EVENTS,
        CAPTURE_EVERY_4_EVENTS,
        CAPTURE_EVERY_8_EVENTS
    };

    enum Filter
    {
        NO_FILTER,
        CK_INT_N_2,
        CK_INT_N_4,
        CK_INT_N_8,
        DTF_DIV_2_N_6,
        DTF_DIV_2_N_8,
        TF_DIV_4_N_6,
        DTF_DIV_4_N_8,
        DTF_DIV_8_N_6,
        DTF_DIV_8_N_8,
        DTF_DIV_16_N_5,
        DTF_DIV_16_N_6,
        DTF_DIV_16_N_8,
        DTF_DIV_32_N_5,
        DTF_DIV_32_N_6,
        DTF_DIV_32_N_8,
    };

    enum OcMode
    {
        FROZEN,
        ACTIVE_LEVEL_ON_MATCH,
        INACTIVE_LEVEL_ON_MATCH,
        TOGGLE,
        FORCE_INACTIVE_LEVEL,
        FORCE_ACTIVE_LEVEL,
        PWM_MODE_1,
        PWM_MODE_2
    };

    enum Polarity
    {
        LO_FALLING_EDGE,
        HI_RISING_EDGE
    };

    using ExtTriggerFilter = tim_ic_filter;
    using ExtTriggerPrescaler = tim_ic_psc;
    using ExtTriggerPolarity = tim_et_pol;

    using TimerNumber = uint8_t;
    enum TimerRegister
    {
#if (TIM1 + 0)
        TIM_1 = TIM1
#endif
#if (TIM2 + 0)
        ,
        TIM_2 = TIM2
#endif
#if (TIM3 + 0)
        ,
        TIM_3 = TIM3
#endif
#if (TIM4 + 0)
        ,
        TIM_4 = TIM4
#endif
#if (TIM5 + 0)
        ,
        TIM_5 = TIM5
#endif
#if (TIM6 + 0)
        ,
        TIM_6 = TIM6
#endif
#if (TIM7 + 0)
        ,
        TIM_7 = TIM7
#endif
#if (TIM8 + 0)
        ,
        TIM_8 = TIM8
#endif
#if (TIM9 + 0)
        ,
        TIM_9 = TIM9
#endif
#if (TIM10 + 0)
        ,
        TIM_10 = TIM10
#endif
#if (TIM11 + 0)
        ,
        TIM_11 = TIM11
#endif
#if (TIM12 + 0)
        ,
        TIM_12 = TIM12
#endif
#if (TIM13 + 0)
        ,
        TIM_13 = TIM13
#endif
#if (TIM14 + 0)
        ,
        TIM_14 = TIM14
#endif
#if (TIM15 + 0)
        ,
        TIM_15 = TIM15
#endif
#if (TIM16 + 0)
        ,
        TIM_16 = TIM16
#endif
#if (TIM17 + 0)
        ,
        TIM_17 = TIM17
#endif
#if (TIM21 + 0)
        ,
        TIM_21 = TIM21
#endif
#if (TIM22 + 0)
        ,
        TIM_22 = TIM22
#endif
    };

    Timer(TimerNumber timer_num)
    {
#if defined(STM32F2) || defined(STM32F4)
        switch (timer_num) {
            case 1:
                _timer = static_cast<TimerRegister>(TIM1);
                rcc_periph_reset_pulse(RST_TIM1);
                break;
            case 2:
                _timer = static_cast<TimerRegister>(TIM2);
                rcc_periph_reset_pulse(RST_TIM2);
                break;
            case 3:
                _timer = static_cast<TimerRegister>(TIM3);
                rcc_periph_reset_pulse(RST_TIM3);
                break;
            case 4:
                _timer = static_cast<TimerRegister>(TIM4);
                rcc_periph_reset_pulse(RST_TIM4);
                break;
            case 5:
                _timer = static_cast<TimerRegister>(TIM5);
                rcc_periph_reset_pulse(RST_TIM5);
                break;
            case 6:
                _timer = static_cast<TimerRegister>(TIM6);
                rcc_periph_reset_pulse(RST_TIM6);
                break;
            case 7:
                _timer = static_cast<TimerRegister>(TIM7);
                rcc_periph_reset_pulse(RST_TIM7);
                break;
            case 8:
                _timer = static_cast<TimerRegister>(TIM8);
                rcc_periph_reset_pulse(RST_TIM8);
                break;
            case 9:
                _timer = static_cast<TimerRegister>(TIM9);
                rcc_periph_reset_pulse(RST_TIM9);
                break;
            case 10:
                _timer = static_cast<TimerRegister>(TIM10);
                rcc_periph_reset_pulse(RST_TIM10);
                break;
            case 11:
                _timer = static_cast<TimerRegister>(TIM11);
                rcc_periph_reset_pulse(RST_TIM11);
                break;
            case 12:
                _timer = static_cast<TimerRegister>(TIM12);
                rcc_periph_reset_pulse(RST_TIM12);
                break;
            case 13:
                _timer = static_cast<TimerRegister>(TIM13);
                rcc_periph_reset_pulse(RST_TIM13);
                break;
            case 14:
                _timer = static_cast<TimerRegister>(TIM14);
                rcc_periph_reset_pulse(RST_TIM14);
                break;
            default:
                assert(false);
        }
#endif
    }
    // CR1//////////////////////////////////////////////////////
    Result enable_counter();
    Result disable_counter();
    Result enable_update_event_generation();
    Result disable_update_event_generation();
    Result set_update_event_source(UevSource source);
    Result set_counter_mode(CounterMode mode);
    Result set_counter_direction(CounterDirection dir);
    Result set_alignment(Alignment alignment);
    Result enable_autoreload_preload();
    Result disable_autoreload_preload();
    Result set_clock_division(ClockDivision div);
    // CR2//////////////////////////////////////////////////////
    Result set_master_mode(MasterMode mode);
    // SMCR/////////////////////////////////////////////////////
    Result set_slave_mode(SlaveMode mode);
    Result set_trigger(Trigger trigger);
    Result enable_master_slave_mode();
    Result disable_master_slave_mode();

    // ETR config (external trigger), TIM 1-8 (F4, F2)
    void enable_etr_clock();  //!< Enable CNT after ETR clock enabling
    void disable_etr_clock();
    void set_etr_filter(ExtTriggerFilter);
    void set_etr_prescaler(ExtTriggerPrescaler);
    void set_etr_polarity(ExtTriggerPolarity);

    // DIER/////////////////////////////////////////////////////
    Result enable_update_interrupt();
    Result disable_update_interrupt();
    Result enable_capture_compare_1_interrupt();
    Result disable_capture_compare_1_interrupt();
    Result enable_capture_compare_2_interrupt();
    Result disable_capture_compare_2_interrupt();
    Result enable_capture_compare_3_interrupt();
    Result disable_capture_compare_3_interrupt();
    Result enable_capture_compare_4_interrupt();
    Result disable_capture_compare_4_interrupt();
    Result enable_trigger_interrupt();
    Result disable_trigger_interrupt();
    // SR///////////////////////////////////////////////////////
    bool get_flag_status(Flag flag) const;
    Result clear_flag_status(Flag flag);
    // EGR//////////////////////////////////////////////////////
    void update_generation();
    // CCMR1////////////////////////////////////////////////////
    Result set_capture_compare_1_mode(CcMode mode);
    Result set_capture_compare_2_mode(CcMode mode);
    Result set_input_capture_1_prescaler(Prescaler prescaler);
    Result set_input_capture_2_prescaler(Prescaler prescaler);
    Result set_input_capture_1_filter(Filter filter);
    Result set_input_capture_2_filter(Filter filter);
    Result enable_fast_output_compare_1();
    Result disable_fast_output_compare_1();
    Result enable_fast_output_compare_2();
    Result disable_fast_output_compare_2();
    Result enable_output_compare_1_preload();
    Result disable_output_compare_1_preload();
    Result enable_output_compare_2_preload();
    Result disable_output_compare_2_preload();
    Result set_output_compare_1_mode(OcMode mode);
    Result set_output_compare_2_mode(OcMode mode);
    // CCMR2////////////////////////////////////////////////////
    Result set_capture_compare_3_mode(CcMode mode);
    Result set_capture_compare_4_mode(CcMode mode);
    Result set_input_capture_3_prescaler(Prescaler prescaler);
    Result set_input_capture_4_prescaler(Prescaler prescaler);
    Result set_input_capture_3_filter(Filter filter);
    Result set_input_capture_4_filter(Filter filter);
    Result enable_fast_output_compare_3();
    Result disable_fast_output_compare_3();
    Result enable_fast_output_compare_4();
    Result disable_fast_output_compare_4();
    Result enable_output_compare_3_preload();
    Result disable_output_compare_3_preload();
    Result enable_output_compare_4_preload();
    Result disable_output_compare_4_preload();
    Result set_output_compare_3_mode(OcMode mode);
    Result set_output_compare_4_mode(OcMode mode);
    // CCER/////////////////////////////////////////////////////
    Result enable_capture_compare_1();
    Result disable_capture_compare_1();
    Result set_capture_compare_1_polarity(Polarity polarity);
    Result set_capture_compare_1_com_polarity(Polarity polarity);
    Result enable_capture_compare_2();
    Result disable_capture_compare_2();
    Result set_capture_compare_2_polarity(Polarity polarity);
    Result enable_capture_compare_3();
    Result disable_capture_compare_3();
    Result set_capture_compare_3_polarity(Polarity polarity);
    Result set_capture_compare_3_com_polarity(Polarity polarity);
    Result enable_capture_compare_4();
    Result disable_capture_compare_4();
    Result set_capture_compare_4_polarity(Polarity polarity);
    Result set_capture_compare_4_com_polarity(Polarity polarity);
    // CNT//////////////////////////////////////////////////////
    uint16_t get_counter_value() const;
    uint32_t get_counter_value32() const;
    void set_counter_value(uint16_t value);
    // PSC//////////////////////////////////////////////////////
    uint16_t get_prescaler_value() const;
    void set_prescaler_value(uint32_t value);
    // ARR//////////////////////////////////////////////////////
    uint16_t get_autoreload_value() const;
    void set_autoreload_value(uint32_t value);
    // CCR1/////////////////////////////////////////////////////
    uint16_t get_capture_compare_1_value() const;
    void set_capture_compare_1_value(uint32_t value);
    // CCR2/////////////////////////////////////////////////////
    uint16_t get_capture_compare_2_value() const;
    void set_capture_compare_2_value(uint32_t value);
    // CCR3/////////////////////////////////////////////////////
    uint16_t get_capture_compare_3_value() const;
    void set_capture_compare_3_value(uint32_t value);
    // CCR4/////////////////////////////////////////////////////
    uint16_t get_capture_compare_4_value() const;
    void set_capture_compare_4_value(uint32_t value);

    uint32_t periph_address() const { return _timer; }

 private:
    TimerRegister _timer;
};

}  // namespace tim

}  // namespace cm3cpp

#endif /* CM3CPP_TIMER_H_ */
