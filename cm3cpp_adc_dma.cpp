#include "cm3cpp_adc_dma.h"

namespace cm3cpp {

namespace adc {

AdcDma::AdcDma(DmaConf dma, AdcConf adc, bool is_temp_sensor)
{
	_adc = new Adc(adc.number);
	_data = new uint16_t[adc.channels_count];
	memset(_data, 0, (adc.channels_count * sizeof(uint16_t)));

	dma_stream_reset(dma.number, dma.stream);
	dma_channel_select(dma.number, dma.stream, dma.channel);
	dma_set_memory_address(dma.number, dma.stream, (uint32_t)_data);
	dma_set_peripheral_address(dma.number, dma.stream, (uint32_t)&ADC_DR(_adc->get_base_address()));
	dma_set_transfer_mode(dma.number, dma.stream, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
	dma_set_number_of_data(dma.number, dma.stream, adc.channels_count);
	dma_disable_peripheral_increment_mode(dma.number, dma.stream);
	dma_enable_memory_increment_mode(dma.number, dma.stream);
	dma_set_peripheral_size(dma.number, dma.stream, DMA_SxCR_PSIZE_16BIT);
	dma_set_memory_size(dma.number, dma.stream, DMA_SxCR_MSIZE_16BIT);
	dma_enable_circular_mode(dma.number, dma.stream);
	dma_set_priority(dma.number, dma.stream, DMA_SxCR_PL_MEDIUM);
	dma_enable_fifo_mode(dma.number, dma.stream);
	dma_set_fifo_threshold(dma.number, dma.stream, DMA_SxFCR_FTH_2_4_FULL);
	dma_set_memory_burst(dma.number, dma.stream, DMA_SxCR_MBURST_SINGLE);
	dma_set_peripheral_burst(dma.number, dma.stream, DMA_SxCR_PBURST_SINGLE);
	dma_enable_stream(dma.number, dma.stream);

	if (is_temp_sensor) {
		_adc->enable_temp_sensor();
	}
	_adc->set_multi_mode(Adc::MultiMode::MODE_INDEPENDENT);
	_adc->set_prescaler(Adc::Prescaler::PRESCALER_8);
	_adc->set_dma_mode(Adc::DmaMode::MODE_NONE);
	_adc->set_delay_between_two_samples(Adc::Delay::DELAY_CYCLES_20);
	_adc->set_resolution(Adc::Resolution::RES_12_BIT);
	_adc->enable_scan_mode();
	_adc->set_conversion_mode(Adc::ConversionMode::CONTINUOUS_CONV);
	_adc->set_external_trigger_polarity_for_regular_group(Adc::RegularGroupTriggerPolarity::TRIGGER_NONE);
	_adc->set_external_trigger_for_regular_group(Adc::RegularGroupTrigger::T1_CC1);
	_adc->set_data_alignment(Adc::Alignment::RIGHT_ALIGN);
	_adc->set_conversion_number_in_sequence(adc.channels_count, adc.channels);

	for(int i = 0; i < adc.channels_count; ++i) {
		_adc->set_channel_sampling_time_selection(Adc::SamplingTime::CYCLES_480, adc.channels[i]);
	}

	_adc->enable_dma_request();
	_adc->enable_dma();
	_adc->enable();
	_adc->start_conversion();
}

uint16_t AdcDma::get_value(uint8_t index)
{
    return(_data[index]);
}

}  // namespace adc

}  // namespace cm3cpp
