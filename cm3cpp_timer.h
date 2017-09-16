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

#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

namespace cm3cpp {

namespace tim {

class Timer
{
public:
	enum Result {
		OK,
		USAGE_ERROR,
		NOT_SUPPORTED
	};

	enum UevSource {
		COUNTER_OVERFLOW_AND_UG,
		COUNTER_OVERFLOW,
	};

	enum CounterMode {
		ONE_SHOT,
		CONTINUOUS
	};

	enum CounterDirection {
		UP,
		DOWN
	};

	enum Alignment {
		EDGE,
		CENTER_DOWN,
		CENTER_UP,
		CENTER_UP_DOWN
	};

	enum ClockDivision {
		TIMER_CLOCK_MUL_1,
		TIMER_CLOCK_MUL_2,
		TIMER_CLOCK_MUL_4
	};

	enum MasterMode {
		MASTER_RESET,
		ENABLE,
		UPDATE,
		COMPARE_PULSE,
		COMPARE_OC1REF,
		COMPARE_OC2REF
	};

	enum SlaveMode {
		DISABLED,
		SLAVE_RESET,
		GATED,
		TRIGGER,
		EXTERNAL_CLOCK
	};

	enum Trigger {
		INTERNAL_TRIGGER_0,
		INTERNAL_TRIGGER_1,
		INTERNAL_TRIGGER_2,
		INTERNAL_TRIGGER_3,
		EDGE_DETECTOR,
		FILTERED_TIMER_INPUT_1,
		FILTERED_TIMER_INPUT_2
	};

	enum Flag {
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

	enum CcMode {
		OUTPUT,
		INPUT_MAPPED_TI1,
		INPUT_MAPPED_TI2,
		INPUT_MAPPED_TI3,
		INPUT_MAPPED_TI4,
		INPUT_MAPPED_TRC
	};

	enum Prescaler {
		NO_PRESCALER,
		CAPTURE_EVERY_2_EVENTS,
		CAPTURE_EVERY_4_EVENTS,
		CAPTURE_EVERY_8_EVENTS
	};

	enum Filter {
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

	enum OcMode {
		FROZEN,
		ACTIVE_LEVEL_ON_MATCH,
		INACTIVE_LEVEL_ON_MATCH,
		TOGGLE,
		FORCE_INACTIVE_LEVEL,
		FORCE_ACTIVE_LEVEL,
		PWM_MODE_1,
		PWM_MODE_2
	};

	enum Polarity {
		LO_FALLING_EDGE,
		HI_RISING_EDGE
	};

	Timer(uint8_t timer_num)
	{
#if defined(STM32F2) || defined(STM32F4)
		switch (timer_num)
		{
		case 1:
			_timer = TIM1;
			rcc_periph_reset_pulse(RST_TIM1);
			break;
		case 2:
			_timer = TIM2;
			rcc_periph_reset_pulse(RST_TIM2);
			break;
		case 3:
			_timer = TIM3;
			rcc_periph_reset_pulse(RST_TIM3);
			break;
		case 4:
			_timer = TIM4;
			rcc_periph_reset_pulse(RST_TIM4);
			break;
		case 5:
			_timer = TIM5;
			rcc_periph_reset_pulse(RST_TIM5);
			break;
		case 6:
			_timer = TIM6;
			rcc_periph_reset_pulse(RST_TIM6);
			break;
		case 7:
			_timer = TIM7;
			rcc_periph_reset_pulse(RST_TIM7);
			break;
		case 8:
			_timer = TIM8;
			rcc_periph_reset_pulse(RST_TIM8);
			break;
		case 9:
			_timer = TIM9;
			rcc_periph_reset_pulse(RST_TIM9);
			break;
		case 10:
			_timer = TIM10;
			rcc_periph_reset_pulse(RST_TIM10);
			break;
		case 11:
			_timer = TIM11;
			rcc_periph_reset_pulse(RST_TIM11);
			break;
		case 12:
			_timer = TIM12;
			rcc_periph_reset_pulse(RST_TIM12);
			break;
		case 13:
			_timer = TIM13;
			rcc_periph_reset_pulse(RST_TIM13);
			break;
		case 14:
			_timer = TIM14;
			rcc_periph_reset_pulse(RST_TIM14);
			break;
		}
#endif
	}
	//CR1//////////////////////////////////////////////////////
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
	//CR2//////////////////////////////////////////////////////
	Result set_master_mode(MasterMode mode);
	//SMCR/////////////////////////////////////////////////////
	Result set_slave_mode(SlaveMode mode);
	Result set_trigger(Trigger trigger);
	Result enable_master_slave_mode();
	Result disable_master_slave_mode();
	//DIER/////////////////////////////////////////////////////
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
	//SR///////////////////////////////////////////////////////
	bool get_flag_status(Flag flag);
	Result clear_flag_status(Flag flag);
	//EGR//////////////////////////////////////////////////////
	void update_generation();
	//CCMR1////////////////////////////////////////////////////
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
	//CCMR2////////////////////////////////////////////////////
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
	//CCER/////////////////////////////////////////////////////
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
	//CNT//////////////////////////////////////////////////////
	uint16_t get_counter_value();
	uint32_t get_counter_value32();
	void set_counter_value(uint16_t value);
	//PSC//////////////////////////////////////////////////////
	uint16_t get_prescaler_value();
	void set_prescaler_value(uint32_t value);
	//ARR//////////////////////////////////////////////////////
	uint16_t get_autoreload_value();
	void set_autoreload_value(uint32_t value);
	//CCR1/////////////////////////////////////////////////////
	uint16_t get_capture_compare_1_value();
	void set_capture_compare_1_value(uint32_t value);
	//CCR2/////////////////////////////////////////////////////
	uint16_t get_capture_compare_2_value();
	void set_capture_compare_2_value(uint32_t value);
	//CCR3/////////////////////////////////////////////////////
	uint16_t get_capture_compare_3_value();
	void set_capture_compare_3_value(uint32_t value);
	//CCR4/////////////////////////////////////////////////////
	uint16_t get_capture_compare_4_value();
	void set_capture_compare_4_value(uint32_t value);

private:
	uint32_t _timer;
};


}  // namespace cm3ext

}  // namespace tim

#endif /* CM3CPP_TIMER_H_ */
