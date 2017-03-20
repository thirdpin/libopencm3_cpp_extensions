#include "libopencm3/stm32/dma.h"
#include "string.h"
#include "adc_ext.h"

typedef struct
{
	uint32_t number;
	uint32_t stream;
	uint32_t channel;
}AdcDma_DMA_Conf;

typedef struct
{
	ADC_Number number;
	ADC_Channel *channels;
	uint8_t channels_count;
}AdcDma_ADC_Conf;

class AdcDma
{
public:
	AdcDma(AdcDma_DMA_Conf dma, AdcDma_ADC_Conf adc);
    uint16_t get_value(uint8_t index);

private:
	ADC_ext *_adc;
	uint16_t *_data;
};
