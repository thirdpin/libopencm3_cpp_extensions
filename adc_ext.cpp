#include "adc_ext.h"

ADC_ext::ADC_ext(ADC_Number adc)
{
	switch(adc)
	{
		case ADC_1: _adc = ADC1; break;
		case ADC_2: _adc = ADC2; break;
		case ADC_3: _adc = ADC3; break;
	}
}

void ADC_ext::set_resolution(ADC_Resolution res)
{
	ADC_CR1(_adc) &= ~ADC_CR1_RES_MASK;
	ADC_CR1(_adc) |= (uint32_t)res;
}

void ADC_ext::enable_scan_mode()
{
	ADC_CR1(_adc) |= ADC_CR1_SCAN_MASK;
}

void ADC_ext::disable_scan_mode()
{
	ADC_CR1(_adc) &= ~ADC_CR1_SCAN_MASK;
}

void ADC_ext::set_data_alignment(ADC_Alignment align)
{
	switch(align)
	{
	case RIGHT_ALIGN:
		ADC_CR2(_adc) &= ~ADC_CR2_ALIGN_MASK;
		break;
	case LEFT_ALIGN:
		ADC_CR2(_adc) |= ADC_CR2_ALIGN_MASK;
		break;
	}
}

void ADC_ext::set_external_trigger_for_regular_group(ADC_RegularGroupTrigger trigger)
{
	ADC_CR2(_adc) &= ~ADC_CR2_EXTSEL_MASK;
	ADC_CR2(_adc) |= (uint32_t)trigger;
}

void ADC_ext::set_external_trigger_polarity_for_regular_group(ADC_RegularGroupTriggerPolarity polarity)
{
	ADC_CR2(_adc) &= ~ADC_CR2_EXTEN_MASK;
	ADC_CR2(_adc) |= (uint32_t)polarity;
}

void ADC_ext::set_conversion_mode(ADC_ConversionMode mode)
{
	switch(mode)
	{
	case CONTINUOUS_CONV:
		ADC_CR2(_adc) |=ADC_CR2_CONT_MASK;
		break;
	case SINGLE_CONV:
		ADC_CR2(_adc) &= ~ADC_CR2_CONT_MASK;
		break;
	}
}

void ADC_ext::enable_dma_request()
{
	ADC_CR2(_adc) |= ADC_CR2_DDS_MASK;
}

void ADC_ext::disable_dma_request()
{
	ADC_CR2(_adc) &= ~ADC_CR2_DDS_MASK;
}

void ADC_ext::enable_dma()
{
	ADC_CR2(_adc) |= ADC_CR2_DMA_MASK;
}

void ADC_ext::disable_dma()
{
	ADC_CR2(_adc) &= ~ADC_CR2_DMA_MASK;
}

void ADC_ext::enable()
{
	ADC_CR2(_adc) |= ADC_CR2_ADON_MASK;
}

void ADC_ext::disable()
{
	ADC_CR2(_adc) &= ~ADC_CR2_ADON_MASK;
}

void ADC_ext::start_conversion()
{
	ADC_CR2(_adc) |= ADC_CR2_SWSTART_MASK;
}

void ADC_ext::set_number_of_conversions(uint8_t number)
{
	ADC_SQR1(_adc) &= ~ADC_SQR1_L_MASK;
	ADC_SQR1(_adc) |= (uint32_t)((number - 1) & 0x0F);
}

void ADC_ext::set_channel_sampling_time_selection(ADC_SamplingTime time, ADC_Channel channel)
{
	uint32_t offset;

	if (channel < ADC_CHANNEL10)
	{
		offset = ((uint8_t)channel * ADC_SMP_MASK);
		ADC_SMPR2(_adc) &= ~(ADC_SMP_MASK << offset);
		ADC_SMPR2(_adc) |= ((uint8_t)time << offset);
	}

	else
	{
		offset = (((uint8_t)channel - ADC_CHANNEL10) * ADC_SMP_MASK);
		ADC_SMPR1(_adc) &= ~(ADC_SMP_MASK << offset);
		ADC_SMPR1(_adc) |= ((uint8_t)time << offset);
	}
}

void ADC_ext::set_conversion_number_in_sequence(ADC_Rank rank, ADC_Channel channel)
{
	uint32_t offset;

	if (rank < RANK_7)
	{
		offset = (rank - RANK_1) * ADC_SQR_MASK;
		ADC_SQR3(_adc) &= ~(ADC_SQR_MASK << offset);
		ADC_SQR3(_adc) |= ((uint8_t)channel << offset);
	}

	else if (rank < RANK_13)
	{
		offset = (rank - RANK_7) * ADC_SQR_MASK;
		ADC_SQR2(_adc) &= ~(ADC_SQR_MASK << offset);
		ADC_SQR2(_adc) |= ((uint8_t)channel << offset);
	}

	else
	{
		offset = (rank - RANK_13) * ADC_SQR_MASK;
		ADC_SQR1(_adc) &= ~(ADC_SQR_MASK << offset);
		ADC_SQR1(_adc) |= ((uint8_t)channel << offset);
	}
}

void ADC_ext::set_prescaler(ADC_Prescaler prescaler)
{
	ADC_CCR &= ~ADC_CCR_ADCPRE_MASK;
	ADC_CCR |= (uint32_t)prescaler;
}

void ADC_ext::set_dma_mode(ADC_DMA_Mode mode)
{
	ADC_CCR &= ~ADC_CCR_DMA_MASK;
	ADC_CCR |= (uint32_t)mode;
}

void ADC_ext::set_delay_between_two_samples(ADC_Delay delay)
{
	ADC_CCR &= ~ADC_CCR_DELAY_MASK;
	ADC_CCR |= (uint32_t)delay;
}

void ADC_ext::set_multi_mode(ADC_MultiMode mode)
{
	ADC_CCR &= ~ADC_CCR_MULTI_MASK;
	ADC_CCR |= (uint32_t)mode;
}
