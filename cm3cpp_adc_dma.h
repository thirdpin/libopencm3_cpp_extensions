#ifndef CM3CPP_ADC_DMA_H_
#define CM3CPP_ADC_DMA_H_

#include <libopencm3/stm32/dma.h>
#include <cm3cpp_config.h>
#include <cstring>

#include "private/assert.h"
#include "cm3cpp_adc.h"

namespace cm3cpp {

namespace adc {

class AdcDma
{
public:
	struct DmaConf
	{
		uint32_t number;
		uint32_t stream;
		uint32_t channel;
	};

	struct AdcConf
	{
		Adc::Number number;
		Adc::Channel *channels;
		uint8_t channels_count;
	};

	AdcDma(DmaConf dma, AdcConf adc, bool is_temp_sensor);

	CM3CPP_EXPLISIT_DESTRUCTOR(AdcDma)

    uint16_t get_value(uint8_t index);

private:
	Adc *_adc;
	uint16_t *_data;
};

} // namespace adc

} // namespace cm3cpp

#endif /* CM3CPP_ADC_DMA_H_ */
