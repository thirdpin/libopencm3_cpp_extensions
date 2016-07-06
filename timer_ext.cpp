#include "timer_ext.h"
using namespace TIMER_CPP_Extension;

//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::enable_counter()
{
	TIM_CR1(_timer) |= TIM_CR1_CEN;
	return OK;
}
//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::disable_counter()
{
	TIM_CR1(_timer) &= ~TIM_CR1_CEN;
	return OK;
}
//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::enable_update_event_generation()
{
	TIM_CR1(_timer) &= ~TIM_CR1_UDIS;
	return OK;
}
//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::disable_update_event_generation()
{
	TIM_CR1(_timer) |= TIM_CR1_UDIS;
	return OK;
}
//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::set_update_event_source(UEV_Source source)
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
Result TIMER_ext::set_counter_mode(CounterMode mode)
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
Result TIMER_ext::set_counter_direction(CounterDirection dir)
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
Result TIMER_ext::set_alignment(Alignment alignment)
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
Result TIMER_ext::enable_autoreload_preload()
{
	TIM_CR1(_timer) |= TIM_CR1_ARPE;
	return OK;
}
//1,2,3,4,5,6,7,8,9,10,11,12,13,14
Result TIMER_ext::disable_autoreload_preload()
{
	TIM_CR1(_timer) &= ~TIM_CR1_ARPE;
	return OK;
}
//1,2,3,4,5,8,9,10,11,12,13,14
Result TIMER_ext::set_clock_division(ClockDivision div)
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
Result TIMER_ext::set_master_mode(MasterMode mode)
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
Result TIMER_ext::set_slave_mode(SlaveMode mode)
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
Result TIMER_ext::set_trigger(Trigger trigger)
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
Result TIMER_ext::enable_master_slave_mode()
{
	TIM_SMCR(_timer) |= TIM_SMCR_MSM;
	return OK;
}
//9,12
Result TIMER_ext::disable_master_slave_mode()
{
	TIM_SMCR(_timer) &= ~TIM_SMCR_MSM;
	return OK;
}
//9,12
Result TIMER_ext::enable_update_interrupt()
{
	TIM_DIER(_timer) |= TIM_DIER_UIE;
	return OK;
}
//9,12
Result TIMER_ext::disable_update_interrupt()
{
	TIM_DIER(_timer) &= ~TIM_DIER_UIE;
	return OK;
}
//9,12
Result TIMER_ext::enable_capture_compare_1_interrupt()
{
	TIM_DIER(_timer) |= TIM_DIER_CC1IE;
	return OK;
}
//9,12
Result TIMER_ext::disable_capture_compare_1_interrupt()
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC1IE;
	return OK;
}
//9,12
Result TIMER_ext::enable_capture_compare_2_interrupt()
{
	TIM_DIER(_timer) |= TIM_DIER_CC2IE;
	return OK;
}
//9,12
Result TIMER_ext::disable_capture_compare_2_interrupt()
{
	TIM_DIER(_timer) &= ~TIM_DIER_CC2IE;
	return OK;
}
//9,12
Result TIMER_ext::enable_trigger_interrupt()
{
	TIM_DIER(_timer) |= TIM_DIER_TIE;
	return OK;
}
//9,12
Result TIMER_ext::disable_trigger_interrupt()
{
	TIM_DIER(_timer) &= ~TIM_DIER_TIE;
	return OK;
}
//9,12
bool TIMER_ext::get_flag_status(Flag flag)
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
		case TRIGGER_INTERRUPT:
			status = TIM_SR(_timer) & TIM_SR_TIF;
			break;
		case CAPTURE_COMPARE_1_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC1OF;
			break;
		case CAPTURE_COMPARE_2_OVERCAPTURE:
			status = TIM_SR(_timer) & TIM_SR_CC2OF;
			break;
	}

	return status;
}
//9,12
Result TIMER_ext::clear_flag_status(Flag flag)
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
		case TRIGGER_INTERRUPT:
			TIM_SR(_timer) &= ~TIM_SR_TIF;
			break;
		case CAPTURE_COMPARE_1_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC1OF;
			break;
		case CAPTURE_COMPARE_2_OVERCAPTURE:
			TIM_SR(_timer) &= ~TIM_SR_CC2OF;
			break;
	}

	return OK;
}
//9,12
Result TIMER_ext::set_capture_compare_1_mode(CC_Mode mode)
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
	}

	return OK;
}
//9,12
Result TIMER_ext::set_capture_compare_2_mode(CC_Mode mode)
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
	}

	return OK;
}
//9,12
Result TIMER_ext::set_input_capture_1_prescaler(Prescaler prescaler)
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
Result TIMER_ext::set_input_capture_2_prescaler(Prescaler prescaler)
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
Result TIMER_ext::set_input_capture_1_filter(Filter filter)
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
Result TIMER_ext::set_input_capture_2_filter(Filter filter)
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
Result TIMER_ext::enable_fast_output_compare_1()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC1FE;
	return OK;
}
//9,12
Result TIMER_ext::disable_fast_output_compare_1()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC1FE;
	return OK;
}
//9,12
Result TIMER_ext::enable_fast_output_compare_2()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC2FE;
	return OK;
}
//9,12
Result TIMER_ext::disable_fast_output_compare_2()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC2FE;
	return OK;
}
//9,12
Result TIMER_ext::enable_output_compare_1_preload()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC1PE;
	return OK;
}
//9,12
Result TIMER_ext::disable_output_compare_1_preload()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC1S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC1PE;
	return OK;
}
//9,12
Result TIMER_ext::enable_output_compare_2_preload()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) |= TIM_CCMR1_OC2PE;
	return OK;
}
//9,12
Result TIMER_ext::disable_output_compare_2_preload()
{
	bool channel_is_input = TIM_CCMR1(_timer) & TIM_CCMR1_CC2S_MASK;

	if (channel_is_input) {
		return USAGE_ERROR;
	}

	TIM_CCMR1(_timer) &= ~TIM_CCMR1_OC2PE;
	return OK;
}
//9,12
Result TIMER_ext::set_output_compare_1_mode(OC_Mode mode)
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
Result TIMER_ext::set_output_compare_2_mode(OC_Mode mode)
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
Result TIMER_ext::enable_capture_compare_1()
{
	TIM_CCER(_timer) |= TIM_CCER_CC1E;
	return OK;
}
//9,12
Result TIMER_ext::disable_capture_compare_1()
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC1E;
	return OK;
}
//9,12
Result TIMER_ext::set_capture_compare_1_polarity(Polarity polarity)
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
//9,12
Result TIMER_ext::enable_capture_compare_2()
{
	TIM_CCER(_timer) |= TIM_CCER_CC2E;
	return OK;
}
//9,12
Result TIMER_ext::disable_capture_compare_2()
{
	TIM_CCER(_timer) &= ~TIM_CCER_CC2E;
	return OK;
}
//9,12
Result TIMER_ext::set_capture_compare_2_polarity(Polarity polarity)
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
//9,12
uint16_t TIMER_ext::get_counter_value()
{
	return TIM_CNT(_timer);
}
//9,12
void TIMER_ext::set_counter_value(uint16_t value)
{
	TIM_CNT(_timer) = value;
}
//9,12
uint16_t TIMER_ext::get_prescaler_value()
{
	return TIM_PSC(_timer);
}
//9,12
void TIMER_ext::set_prescaler_value(uint32_t value)
{
	TIM_PSC(_timer) = value;
}
//9,12
uint16_t TIMER_ext::get_autoreload_value()
{
	return TIM_ARR(_timer);
}
//9,12
void TIMER_ext::set_autoreload_value(uint32_t value)
{
	TIM_ARR(_timer) = value;
}
//9,12
uint16_t TIMER_ext::get_capture_compare_1_value()
{
	return TIM_CCR1(_timer);
}
//9,12
void TIMER_ext::set_capture_compare_1_value(uint32_t value)
{
	TIM_CCR1(_timer) = value;
}
//9,12
uint16_t TIMER_ext::get_capture_compare_2_value()
{
	return TIM_CCR2(_timer);
}
//9,12
void TIMER_ext::set_capture_compare_2_value(uint32_t value)
{
	TIM_CCR2(_timer) = value;
}
