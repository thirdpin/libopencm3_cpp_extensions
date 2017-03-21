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

void ADC_ext::set_conversion_number_in_sequence(uint8_t length, ADC_Channel *channel)
{
	uint32_t fifth6 = 0;
	uint32_t fourth6 = 0;
	uint32_t third6 = 0;
	uint32_t second6 = 0;
	uint32_t first6 = 0;
	uint8_t i = 0;

	if (length > 16) {
		return;
	}

	for (i = 1; i <= length; i++) {
		if (i <= 6) {
			first6 |= (channel[i - 1] << ((i - 1) * 5));
		}
		if ((i > 6) & (i <= 12)) {
			second6 |= (channel[i - 1] << ((i - 6 - 1) * 5));
		}
		if ((i > 12) & (i <= 18)) {
			third6 |= (channel[i - 1] << ((i - 12 - 1) * 5));
		}
		if ((i > 18) & (i <= 24)) {
			fourth6 |= (channel[i - 1] << ((i - 18 - 1) * 5));
		}
		if ((i > 24) & (i <= 28)) {
			fifth6 |= (channel[i - 1] << ((i - 24 - 1) * 5));
		}
	}

	ADC_SQR1(_adc) = third6 | ((length - 1) << 20);
	ADC_SQR2(_adc) = second6;
	ADC_SQR3(_adc) = first6;
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

void ADC_ext::enable_temp_sensor()
{
	ADC_CCR |= ADC_CCR_TSVREFE_MASK;
}

void ADC_ext::disable_temp_sensor()
{
	ADC_CCR &= ~ADC_CCR_TSVREFE_MASK;
}
