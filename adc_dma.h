#include <adc_ext.h>
#include <libopencm3/stm32/dma.h>
#include <string.h>


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
	~AdcDma() = delete; // prevent memory leak

    uint16_t get_value(uint8_t index);

private:
	Adc *_adc;
	uint16_t *_data;
};


} // namespace adc

} // namespace cm3ext
