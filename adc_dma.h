#ifndef ADC_DMA_EXT_H
#define ADC_DMA_EXT_H

#include <libopencm3/stm32/dma.h>
#include <cstring>

#include <cm3ext_config.h>
#include "private/assert.h"
#include "adc_ext.h"

namespace cm3ext {

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
		Number number;
		Channel *channels;
		uint8_t channels_count;
	};

	AdcDma(DmaConf dma, AdcConf adc, bool is_temp_sensor);

	CM3EXT_EXPLISIT_DESTRUCTOR(AdcDma)

    uint16_t get_value(uint8_t index);

private:
	Adc *_adc;
	uint16_t *_data;
};


} // namespace adc

} // namespace cm3ext

#endif
