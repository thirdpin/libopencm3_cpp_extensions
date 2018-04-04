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

#include "cm3cpp_timer.h"

namespace cm3cpp {

namespace tim {

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::enable_counter() -> Result
{
	TIM_CR1(_timer) |= TIM_CR1_CEN;
	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::disable_counter() -> Result
{
	TIM_CR1(_timer) &= ~TIM_CR1_CEN;
	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::enable_update_event_generation() -> Result
{
	TIM_CR1(_timer) &= ~TIM_CR1_UDIS;
	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::disable_update_event_generation() -> Result
{
	TIM_CR1(_timer) |= TIM_CR1_UDIS;
	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::set_update_event_source(UevSource source) -> Result
{
	switch (source)
	{
		case COUNTER_OVERFLOW_AND_UG:
			TIM_CR1(_timer) &= ~TIM_CR1_URS;
			break;
		case COUNTER_OVERFLOW:
			TIM_CR1(_timer) |= TIM_CR1_URS;
			break;
	}

	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::set_counter_mode(CounterMode mode) -> Result
{
	switch (mode)
	{
		case ONE_SHOT:
			TIM_CR1(_timer) |= TIM_CR1_OPM;
			break;
		case CONTINUOUS:
			TIM_CR1(_timer) &= ~TIM_CR1_OPM;
			break;
	}

	return OK;
}

//1,2,3,4,5,8
auto Timer::set_counter_direction(CounterDirection dir) -> Result
{
	if((_timer != TIM1) && (_timer != TIM2) &&
	   (_timer != TIM3) && (_timer != TIM4) &&
	   (_timer != TIM5) && (_timer != TIM8)) {
		return NOT_SUPPORTED;
	}

	switch (dir)
	{
		case UP:
			TIM_CR1(_timer) &= ~TIM_CR1_DIR_DOWN;
			break;
		case DOWN:
			TIM_CR1(_timer) |= TIM_CR1_DIR_DOWN;
			break;
	}

	return OK;
}

//1,2,3,4,5,8
auto Timer::set_alignment(Alignment alignment) -> Result
{
	if((_timer != TIM1) && (_timer != TIM2) &&
	   (_timer != TIM3) && (_timer != TIM4) &&
	   (_timer != TIM5) && (_timer != TIM8)) {
		return NOT_SUPPORTED;
	}

	bool counter_enable = TIM_CR1(_timer) & TIM_CR1_CEN;

	switch (alignment)
	{
		case EDGE:
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CMS_MASK) |
			                   TIM_CR1_CMS_EDGE ;
			return OK;
		case CENTER_DOWN:
			if (counter_enable) {
				return USAGE_ERROR;
			}
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CMS_MASK) |
							   TIM_CR1_CMS_CENTER_1;
			return OK;
		case CENTER_UP:
			if (counter_enable) {
				return USAGE_ERROR;
			}
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CMS_MASK) |
			                   TIM_CR1_CMS_CENTER_2 ;
			return OK;
		case CENTER_UP_DOWN:
			if (counter_enable) {
				return USAGE_ERROR;
			}
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CMS_MASK) |
			                   TIM_CR1_CMS_CENTER_3 ;
			return OK;
	}

	return NOT_SUPPORTED;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::enable_autoreload_preload() -> Result
{
	TIM_CR1(_timer) |= TIM_CR1_ARPE;
	return OK;
}

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
auto Timer::disable_autoreload_preload() -> Result
{
	TIM_CR1(_timer) &= ~TIM_CR1_ARPE;
	return OK;
}

//1,2,3,4,5,8,9,10,11,12,13,14
auto Timer::set_clock_division(ClockDivision div) -> Result
{
	if((_timer == TIM6) || (_timer == TIM7)) {
		return USAGE_ERROR;
	}

	switch (div)
	{
		case TIMER_CLOCK_MUL_1:
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CKD_CK_INT_MASK) |
			                   TIM_CR1_CKD_CK_INT ;
			break;
		case TIMER_CLOCK_MUL_2:
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CKD_CK_INT_MASK) |
			                   TIM_CR1_CKD_CK_INT_MUL_2 ;
			break;
		case TIMER_CLOCK_MUL_4:
			TIM_CR1(_timer) = (TIM_CR1(_timer) & ~TIM_CR1_CKD_CK_INT_MASK) |
			                   TIM_CR1_CKD_CK_INT_MUL_4 ;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_master_mode(MasterMode mode) -> Result
{
	switch (mode)
	{
		case MASTER_RESET:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_RESET ;
			break;
		case ENABLE:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_ENABLE ;
			break;
		case UPDATE:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_UPDATE ;
			break;
		case COMPARE_PULSE:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_COMPARE_PULSE ;
			break;
		case COMPARE_OC1REF:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_COMPARE_OC1REF ;
			break;
		case COMPARE_OC2REF:
			TIM_CR2(_timer) = (TIM_CR2(_timer) & ~TIM_CR2_MMS_MASK) |
			                   TIM_CR2_MMS_COMPARE_OC2REF ;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_slave_mode(SlaveMode mode) -> Result
{
	switch (mode)
	{
	    case DISABLED:
			TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_SMS_MASK) |
			                    TIM_SMCR_SMS_OFF ;
			break;
		case SLAVE_RESET:
			TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_SMS_MASK) |
			                    TIM_SMCR_SMS_RM ;
			break;
		case GATED:
			if(TIM_SMCR(_timer) & TIM_SMCR_TS_TI1F_ED) {
				return USAGE_ERROR;
			}
			TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_SMS_MASK) |
			                    TIM_SMCR_SMS_GM ;
			break;
		case TRIGGER:
			TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_SMS_MASK) |
			                    TIM_SMCR_SMS_TM ;
			break;
		case EXTERNAL_CLOCK:
			TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_SMS_MASK) |
			                    TIM_SMCR_SMS_ECM1 ;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_trigger(Trigger trigger) -> Result
{
	switch (trigger)
		{
		    case INTERNAL_TRIGGER_0:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_ITR0 ;
				break;
			case INTERNAL_TRIGGER_1:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_ITR1 ;
				break;
			case INTERNAL_TRIGGER_2:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_ITR2 ;
				break;
			case INTERNAL_TRIGGER_3:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_ITR3 ;
				break;
			case EDGE_DETECTOR:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_TI1F_ED ;
				break;
			case FILTERED_TIMER_INPUT_1:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_TI1FP1 ;
				break;
			case FILTERED_TIMER_INPUT_2:
				TIM_SMCR(_timer) = (TIM_SMCR(_timer) & ~TIM_SMCR_TS_MASK) |
				                    TIM_SMCR_TS_TI2FP2 ;
				break;
		}

		return OK;
}

//9,12
auto Timer::enable_master_slave_mode() -> Result
{
	TIM_SMCR(_timer) |= TIM_SMCR_MSM;
	return OK;
}

//9,12
auto Timer::disable_master_slave_mode() -> Result
{
	TIM_SMCR(_timer) &= ~TIM_SMCR_MSM;
	return OK;
}

//9,12
auto Timer::enable_update_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_UIE;
	return OK;
}

//9,12
auto Timer::disable_update_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_UIE;
	return OK;
}

//9,12
auto Timer::enable_capture_compare_1_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_CC1IE;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_1_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC1IE;
	return OK;
}

//9,12
auto Timer::enable_capture_compare_2_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_CC2IE;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_2_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC2IE;
	return OK;
}

auto Timer::enable_capture_compare_3_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_CC3IE;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_3_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC3IE;
	return OK;
}

//9,12
auto Timer::enable_capture_compare_4_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_CC4IE;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_4_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC4IE;
	return OK;
}

//9,12
auto Timer::enable_trigger_interrupt() -> Result
{
	TIM_DIER(_timer) |= TIM_DIER_TIE;
	return OK;
}

//9,12
auto Timer::disable_trigger_interrupt() -> Result
{
	TIM_DIER(_timer) &= ~TIM_DIER_TIE;
	return OK;
}

//9,12
bool Timer::get_flag_status(Flag flag)
{
	bool status = false;

	switch (flag)
	{
		case UPDATE_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_UIF;
			break;
		case CAPTURE_COMPARE_1_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_CC1IF;
			break;
		case CAPTURE_COMPARE_2_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_CC2IF;
			break;
		case CAPTURE_COMPARE_3_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_CC3IF;
			break;
		case CAPTURE_COMPARE_4_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_CC4IF;
			break;
		case TRIGGER_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_TIF;
			break;
		case CAPTURE_COMPARE_1_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC1OF;
			break;
		case CAPTURE_COMPARE_2_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC2OF;
			break;
		case CAPTURE_COMPARE_3_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC3OF;
			break;
		case CAPTURE_COMPARE_4_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC4OF;
			break;
	}

	return status;
}

//9,12
auto Timer::clear_flag_status(Flag flag) -> Result
{
	switch (flag)
	{
		case UPDATE_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_UIF;
			break;
		case CAPTURE_COMPARE_1_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_CC1IF;
			break;
		case CAPTURE_COMPARE_2_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_CC2IF;
			break;
		case CAPTURE_COMPARE_3_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_CC3IF;
			break;
		case CAPTURE_COMPARE_4_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_CC4IF;
			break;
		case TRIGGER_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_TIF;
			break;
		case CAPTURE_COMPARE_1_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC1OF;
			break;
		case CAPTURE_COMPARE_2_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC2OF;
			break;
		case CAPTURE_COMPARE_3_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC3OF;
			break;
		case CAPTURE_COMPARE_4_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC4OF;
			break;
	}

	return OK;
}

void Timer::update_generation()
{
	TIM_EGR(_timer) |= TIM_EGR_UG;
}

//9,12
auto Timer::set_capture_compare_1_mode(CcMode mode) -> Result
{
	bool channel_on = TIM_CCER(_timer) & TIM_CCER_CC1E;

	if (channel_on) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case OUTPUT:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC1S_MASK) |
			                     TIM_CCMR1_CC1S_OUT;
			break;
		case INPUT_MAPPED_TI1:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC1S_MASK) |
			                     TIM_CCMR1_CC1S_IN_TI1;
			break;
		case INPUT_MAPPED_TI2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC1S_MASK) |
			                     TIM_CCMR1_CC1S_IN_TI2;
			break;
		case INPUT_MAPPED_TRC:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC1S_MASK) |
			                     TIM_CCMR1_CC1S_IN_TRC;
			break;

		default: break;
	}

	return OK;
}

//9,12
auto Timer::set_capture_compare_2_mode(CcMode mode) -> Result
{
	bool channel_on = TIM_CCER(_timer) & TIM_CCER_CC2E;

	if (channel_on) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case OUTPUT:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC2S_MASK) |
								 TIM_CCMR1_CC2S_OUT;
			break;
		case INPUT_MAPPED_TI1:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC2S_MASK) |
								 TIM_CCMR1_CC2S_IN_TI1;
			break;
		case INPUT_MAPPED_TI2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC2S_MASK) |
								 TIM_CCMR1_CC2S_IN_TI2;
			break;
		case INPUT_MAPPED_TRC:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_CC2S_MASK) |
								 TIM_CCMR1_CC2S_IN_TRC;
			break;

		default: break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_1_prescaler(Prescaler prescaler) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (prescaler)
	{
		case NO_PRESCALER:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1PSC_MASK) |
			                     TIM_CCMR1_IC1PSC_OFF;
			break;
		case CAPTURE_EVERY_2_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1PSC_MASK) |
			                     TIM_CCMR1_IC1PSC_2;
			break;
		case CAPTURE_EVERY_4_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1PSC_MASK) |
			                     TIM_CCMR1_IC1PSC_4;
			break;
		case CAPTURE_EVERY_8_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1PSC_MASK) |
			                     TIM_CCMR1_IC1PSC_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_2_prescaler(Prescaler prescaler) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (prescaler)
	{
		case NO_PRESCALER:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2PSC_MASK) |
								 TIM_CCMR1_IC2PSC_OFF;
			break;
		case CAPTURE_EVERY_2_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2PSC_MASK) |
								 TIM_CCMR1_IC2PSC_2;
			break;
		case CAPTURE_EVERY_4_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2PSC_MASK) |
								 TIM_CCMR1_IC2PSC_4;
			break;
		case CAPTURE_EVERY_8_EVENTS:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2PSC_MASK) |
								 TIM_CCMR1_IC2PSC_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_1_filter(Filter filter) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (filter)
	{
		case NO_FILTER:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_OFF;
			break;
		case CK_INT_N_2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_CK_INT_N_2;
			break;
		case CK_INT_N_4:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_CK_INT_N_4;
			break;
		case CK_INT_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_CK_INT_N_8;
			break;
		case DTF_DIV_2_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_2_N_6;
			break;
		case DTF_DIV_2_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_2_N_8;
			break;
		case TF_DIV_4_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_4_N_6;
			break;
		case DTF_DIV_4_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_4_N_8;
			break;
		case DTF_DIV_8_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_8_N_6;
			break;
		case DTF_DIV_8_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_8_N_8;
			break;
		case DTF_DIV_16_N_5:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_16_N_5;
			break;
		case DTF_DIV_16_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_16_N_6;
			break;
		case DTF_DIV_16_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_16_N_8;
			break;
		case DTF_DIV_32_N_5:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_32_N_5;
			break;
		case DTF_DIV_32_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_32_N_6;
			break;
		case DTF_DIV_32_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC1F_MASK) |
			TIM_CCMR1_IC1F_DTF_DIV_32_N_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_2_filter(Filter filter) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (filter)
	{
		case NO_FILTER:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_OFF;
			break;
		case CK_INT_N_2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_CK_INT_N_2;
			break;
		case CK_INT_N_4:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_CK_INT_N_4;
			break;
		case CK_INT_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_CK_INT_N_8;
			break;
		case DTF_DIV_2_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_2_N_6;
			break;
		case DTF_DIV_2_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_2_N_8;
			break;
		case TF_DIV_4_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_4_N_6;
			break;
		case DTF_DIV_4_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_4_N_8;
			break;
		case DTF_DIV_8_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_8_N_6;
			break;
		case DTF_DIV_8_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_8_N_8;
			break;
		case DTF_DIV_16_N_5:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_16_N_5;
			break;
		case DTF_DIV_16_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_16_N_6;
			break;
		case DTF_DIV_16_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_16_N_8;
			break;
		case DTF_DIV_32_N_5:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_32_N_5;
			break;
		case DTF_DIV_32_N_6:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_32_N_6;
			break;
		case DTF_DIV_32_N_8:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_IC2F_MASK) |
			TIM_CCMR1_IC2F_DTF_DIV_32_N_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::enable_fast_output_compare_1() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC1FE;
	return OK;
}

//9,12
auto Timer::disable_fast_output_compare_1() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC1FE;
	return OK;
}

//9,12
auto Timer::enable_fast_output_compare_2() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC2FE;
	return OK;
}

//9,12
auto Timer::disable_fast_output_compare_2() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC2FE;
	return OK;
}

//9,12
auto Timer::enable_output_compare_1_preload() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC1PE;
	return OK;
}

//9,12
auto Timer::disable_output_compare_1_preload() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC1PE;
	return OK;
}

//9,12
auto Timer::enable_output_compare_2_preload() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC2PE;

	return OK;
}

//9,12
auto Timer::disable_output_compare_2_preload() -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC2PE;
	return OK;
}

//9,12
auto Timer::set_output_compare_1_mode(OcMode mode) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case FROZEN:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_FROZEN;
			break;
		case ACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_ACTIVE;
			break;
		case INACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_INACTIVE;
			break;
		case TOGGLE:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_TOGGLE;
			break;
		case FORCE_INACTIVE_LEVEL:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_FORCE_LOW;
			break;
		case FORCE_ACTIVE_LEVEL:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_FORCE_HIGH;
			break;
		case PWM_MODE_1:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_PWM1;
			break;
		case PWM_MODE_2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC1M_MASK) |
			TIM_CCMR1_OC1M_PWM2;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_output_compare_2_mode(OcMode mode) -> Result
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case FROZEN:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_FROZEN;
			break;
		case ACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_ACTIVE;
			break;
		case INACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_INACTIVE;
			break;
		case TOGGLE:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_TOGGLE;
			break;
		case FORCE_INACTIVE_LEVEL:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_FORCE_LOW;
			break;
		case FORCE_ACTIVE_LEVEL:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_FORCE_HIGH;
			break;
		case PWM_MODE_1:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_PWM1;
			break;
		case PWM_MODE_2:
			TIM_CCMR1(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR1_OC2M_MASK) |
			TIM_CCMR1_OC2M_PWM2;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_capture_compare_3_mode(CcMode mode) -> Result
{
	bool channel_on = TIM_CCER(_timer) & TIM_CCER_CC3E;

	if (channel_on) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case OUTPUT:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC3S_MASK) |
			                     TIM_CCMR2_CC3S_OUT;
			break;
		case INPUT_MAPPED_TI3:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC3S_MASK) |
			                     TIM_CCMR2_CC3S_IN_TI3;
			break;
		case INPUT_MAPPED_TI4:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC3S_MASK) |
			                     TIM_CCMR2_CC3S_IN_TI4;
			break;
		case INPUT_MAPPED_TRC:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC3S_MASK) |
			                     TIM_CCMR2_CC3S_IN_TRC;
			break;

		case INPUT_MAPPED_TI1:
		case INPUT_MAPPED_TI2:
			break;
	}

	return OK;
}

//9,12
auto Timer::set_capture_compare_4_mode(CcMode mode) -> Result
{
	bool channel_on = TIM_CCER(_timer) & TIM_CCER_CC4E;

	if (channel_on) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case OUTPUT:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC4S_MASK) |
								 TIM_CCMR2_CC4S_OUT;
			break;
		case INPUT_MAPPED_TI3:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC4S_MASK) |
								 TIM_CCMR2_CC4S_IN_TI3;
			break;
		case INPUT_MAPPED_TI4:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC4S_MASK) |
								 TIM_CCMR2_CC4S_IN_TI4;
			break;
		case INPUT_MAPPED_TRC:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_CC4S_MASK) |
								 TIM_CCMR2_CC4S_IN_TRC;
			break;

		case INPUT_MAPPED_TI1:
		case INPUT_MAPPED_TI2:
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_3_prescaler(Prescaler prescaler) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (prescaler)
	{
		case NO_PRESCALER:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC3PSC_MASK) |
			                     TIM_CCMR2_IC3PSC_OFF;
			break;
		case CAPTURE_EVERY_2_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC3PSC_MASK) |
			                     TIM_CCMR2_IC3PSC_2;
			break;
		case CAPTURE_EVERY_4_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC3PSC_MASK) |
			                     TIM_CCMR2_IC3PSC_4;
			break;
		case CAPTURE_EVERY_8_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC3PSC_MASK) |
			                     TIM_CCMR2_IC3PSC_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_4_prescaler(Prescaler prescaler) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (prescaler)
	{
		case NO_PRESCALER:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC4PSC_MASK) |
								 TIM_CCMR2_IC4PSC_OFF;
			break;
		case CAPTURE_EVERY_2_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC4PSC_MASK) |
								 TIM_CCMR2_IC4PSC_2;
			break;
		case CAPTURE_EVERY_4_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC4PSC_MASK) |
								 TIM_CCMR2_IC4PSC_4;
			break;
		case CAPTURE_EVERY_8_EVENTS:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_IC4PSC_MASK) |
								 TIM_CCMR2_IC4PSC_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_3_filter(Filter filter) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (filter)
	{
		case NO_FILTER:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_OFF;
			break;
		case CK_INT_N_2:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_CK_INT_N_2;
			break;
		case CK_INT_N_4:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_CK_INT_N_4;
			break;
		case CK_INT_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_CK_INT_N_8;
			break;
		case DTF_DIV_2_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_2_N_6;
			break;
		case DTF_DIV_2_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_2_N_8;
			break;
		case TF_DIV_4_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_4_N_6;
			break;
		case DTF_DIV_4_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_4_N_8;
			break;
		case DTF_DIV_8_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_8_N_6;
			break;
		case DTF_DIV_8_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_8_N_8;
			break;
		case DTF_DIV_16_N_5:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_16_N_5;
			break;
		case DTF_DIV_16_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_16_N_6;
			break;
		case DTF_DIV_16_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_16_N_8;
			break;
		case DTF_DIV_32_N_5:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_32_N_5;
			break;
		case DTF_DIV_32_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_32_N_6;
			break;
		case DTF_DIV_32_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC3F_MASK) |
			TIM_CCMR2_IC3F_DTF_DIV_32_N_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_input_capture_4_filter(Filter filter) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (!channel_is_input) {
		return USAGE_ERROR;
	}

	switch (filter)
	{
		case NO_FILTER:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_OFF;
			break;
		case CK_INT_N_2:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_CK_INT_N_2;
			break;
		case CK_INT_N_4:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_CK_INT_N_4;
			break;
		case CK_INT_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_CK_INT_N_8;
			break;
		case DTF_DIV_2_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_2_N_6;
			break;
		case DTF_DIV_2_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_2_N_8;
			break;
		case TF_DIV_4_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_4_N_6;
			break;
		case DTF_DIV_4_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_4_N_8;
			break;
		case DTF_DIV_8_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_8_N_6;
			break;
		case DTF_DIV_8_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_8_N_8;
			break;
		case DTF_DIV_16_N_5:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_16_N_5;
			break;
		case DTF_DIV_16_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_16_N_6;
			break;
		case DTF_DIV_16_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_16_N_8;
			break;
		case DTF_DIV_32_N_5:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_32_N_5;
			break;
		case DTF_DIV_32_N_6:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_32_N_6;
			break;
		case DTF_DIV_32_N_8:
			TIM_CCMR2(_timer) = (TIM_CCMR1(_timer) & ~TIM_CCMR2_IC4F_MASK) |
			TIM_CCMR2_IC4F_DTF_DIV_32_N_8;
			break;
	}

	return OK;
}

//9,12
auto Timer::enable_fast_output_compare_3() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) |= TIM_CCMR2_OC3FE;
	return OK;
}
//9,12
auto Timer::disable_fast_output_compare_3() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) &= ~TIM_CCMR2_OC3FE;
	return OK;
}

//9,12
auto Timer::enable_fast_output_compare_4() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) |= TIM_CCMR2_OC4FE;
	return OK;
}

//9,12
auto Timer::disable_fast_output_compare_4() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) &= ~TIM_CCMR2_OC4FE;
	return OK;
}

//9,12
auto Timer::enable_output_compare_3_preload() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) |= TIM_CCMR2_OC3PE;
	return OK;
}

//9,12
auto Timer::disable_output_compare_3_preload() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) &= ~TIM_CCMR2_OC3PE;
	return OK;
}

//9,12
auto Timer::enable_output_compare_4_preload() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) |= TIM_CCMR2_OC4PE;
	return OK;
}

//9,12
auto Timer::disable_output_compare_4_preload() -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR2(_timer) &= ~TIM_CCMR2_OC4PE;
	return OK;
}

//9,12
auto Timer::set_output_compare_3_mode(OcMode mode) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC3S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case FROZEN:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_FROZEN;
			break;
		case ACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_ACTIVE;
			break;
		case INACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_INACTIVE;
			break;
		case TOGGLE:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_TOGGLE;
			break;
		case FORCE_INACTIVE_LEVEL:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_FORCE_LOW;
			break;
		case FORCE_ACTIVE_LEVEL:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_FORCE_HIGH;
			break;
		case PWM_MODE_1:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_PWM1;
			break;
		case PWM_MODE_2:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC3M_MASK) |
			TIM_CCMR2_OC3M_PWM2;
			break;
	}

	return OK;
}

//9,12
auto Timer::set_output_compare_4_mode(OcMode mode) -> Result
{
	bool channel_is_input = TIM_CCMR2(_timer) & TIM_CCMR2_CC4S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	switch (mode)
	{
		case FROZEN:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_FROZEN;
			break;
		case ACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_ACTIVE;
			break;
		case INACTIVE_LEVEL_ON_MATCH:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_INACTIVE;
			break;
		case TOGGLE:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_TOGGLE;
			break;
		case FORCE_INACTIVE_LEVEL:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_FORCE_LOW;
			break;
		case FORCE_ACTIVE_LEVEL:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_FORCE_HIGH;
			break;
		case PWM_MODE_1:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_PWM1;
			break;
		case PWM_MODE_2:
			TIM_CCMR2(_timer) = (TIM_CCMR2(_timer) & ~TIM_CCMR2_OC4M_MASK) |
			TIM_CCMR2_OC4M_PWM2;
			break;
	}

	return OK;
}

//9,12
auto Timer::enable_capture_compare_1() -> Result
{
	TIM_CCER(_timer) |= TIM_CCER_CC1E;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_1() -> Result
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC1E;
	return OK;
}

//9,12
auto Timer::set_capture_compare_1_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC1P;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC1P;
			break;
	}

	return OK;
}

auto Timer::set_capture_compare_1_com_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC1NP;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC1NP;
			break;
	}

	return OK;
}

//9,12
auto Timer::enable_capture_compare_2() -> Result
{
	TIM_CCER(_timer) |= TIM_CCER_CC2E;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_2() -> Result
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC2E;
	return OK;
}

//9,12
auto Timer::set_capture_compare_2_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC2P;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC2P;
			break;
	}

	return OK;
}

auto Timer::enable_capture_compare_3() -> Result
{
	TIM_CCER(_timer) |= TIM_CCER_CC3E;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_3() -> Result
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC3E;
	return OK;
}

//9,12
auto Timer::set_capture_compare_3_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC3P;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC3P;
			break;
	}

	return OK;
}

auto Timer::set_capture_compare_3_com_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC3NP;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC3NP;
			break;
	}

	return OK;
}

//9,12
auto Timer::enable_capture_compare_4() -> Result
{
	TIM_CCER(_timer) |= TIM_CCER_CC4E;
	return OK;
}

//9,12
auto Timer::disable_capture_compare_4() -> Result
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC4E;
	return OK;
}

//9,12
auto Timer::set_capture_compare_4_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= TIM_CCER_CC4P;
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~TIM_CCER_CC4P;
			break;
	}

	return OK;
}

auto Timer::set_capture_compare_4_com_polarity(Polarity polarity) -> Result
{
	switch (polarity)
	{
		case LO_FALLING_EDGE:
			TIM_CCER(_timer) |= (1<<15);
			break;
		case HI_RISING_EDGE:
			TIM_CCER(_timer) &= ~(1<<15);
			break;
	}

	return OK;
}

//9,12
uint16_t Timer::get_counter_value()
{
	return TIM_CNT(_timer);
}

//9,12
void Timer::set_counter_value(uint16_t value)
{
	TIM_CNT(_timer) = value;
}

//9,12
uint16_t Timer::get_prescaler_value()
{
	return TIM_PSC(_timer);
}

//9,12
void Timer::set_prescaler_value(uint32_t value)
{
	TIM_PSC(_timer) = value;
}

//9,12
uint16_t Timer::get_autoreload_value()
{
	return TIM_ARR(_timer);
}

//9,12
void Timer::set_autoreload_value(uint32_t value)
{
	TIM_ARR(_timer) = value;
}

//9,12
uint16_t Timer::get_capture_compare_1_value()
{
	return TIM_CCR1(_timer);
}

//9,12
void Timer::set_capture_compare_1_value(uint32_t value)
{
	TIM_CCR1(_timer) = value;
}

//9,12
uint16_t Timer::get_capture_compare_2_value()
{
	return TIM_CCR2(_timer);
}

//9,12
void Timer::set_capture_compare_2_value(uint32_t value)
{
	TIM_CCR2(_timer) = value;
}

uint16_t Timer::get_capture_compare_3_value()
{
	return TIM_CCR3(_timer);
}

//9,12
void Timer::set_capture_compare_3_value(uint32_t value)
{
	TIM_CCR3(_timer) = value;
}

//9,12
uint16_t Timer::get_capture_compare_4_value()
{
	return TIM_CCR4(_timer);
}

//9,12
void Timer::set_capture_compare_4_value(uint32_t value)
{
	TIM_CCR4(_timer) = value;
}


}  // namespace cm3cpp

}  // namespace tim
