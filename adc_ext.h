#ifndef ADC_EXT_H
#define ADC_EXT_H

#include <stdint.h>
#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/memorymap.h>

#define ADC1			(PERIPH_BASE_APB2 + 0x2000)
#define ADC2			(PERIPH_BASE_APB2 + 0x2100)
#define ADC3			(PERIPH_BASE_APB2 + 0x2200)
#define ADC0            (PERIPH_BASE_APB2 + 0x2300)

/* --- ADC registers ------------------------------------------------------- */
#define ADC_SR(block)                   MMIO32((block) + 0x00)
#define ADC_CR1(block)                  MMIO32((block) + 0x04)
#define ADC_CR2(block)                  MMIO32((block) + 0x08)
#define ADC_SMPR1(block)                MMIO32((block) + 0x0c)
#define ADC_SMPR2(block)                MMIO32((block) + 0x10)
#define ADC_JOFR1(block)				MMIO32((block) + 0x14)
#define ADC_JOFR2(block)				MMIO32((block) + 0x18)
#define ADC_JOFR3(block)				MMIO32((block) + 0x1c)
#define ADC_JOFR4(block)				MMIO32((block) + 0x20)
#define ADC_HTR(block)					MMIO32((block) + 0x24)
#define ADC_LTR(block)					MMIO32((block) + 0x28)
#define ADC_SQR1(block)					MMIO32((block) + 0x2c)
#define ADC_SQR2(block)					MMIO32((block) + 0x30)
#define ADC_SQR3(block)					MMIO32((block) + 0x34)
#define ADC_JSQR(block)					MMIO32((block) + 0x38)
#define ADC_JDR1(block)					MMIO32((block) + 0x3c)
#define ADC_JDR2(block)					MMIO32((block) + 0x40)
#define ADC_JDR3(block)					MMIO32((block) + 0x44)
#define ADC_JDR4(block)					MMIO32((block) + 0x48)
#define ADC_DR(block)					MMIO32((block) + 0x4c)
#define ADC_CSR							MMIO32(ADC0 + 0x0)
#define ADC_CCR							MMIO32(ADC0 + 0x4)
#define ADC_CDR							MMIO32(ADC0 + 0x8)

#define ADC1_SR                         ADC_SR(ADC1)
#define ADC1_CR1                        ADC_CR1(ADC1)
#define ADC1_CR2                        ADC_CR2(ADC1)
#define ADC1_SMPR1                      ADC_SMPR1(ADC1)
#define ADC1_SMPR2                      ADC_SMPR2(ADC1)
#define ADC1_JOFR1                      ADC_JOFR1(ADC1)
#define ADC1_JOFR2                      ADC_JOFR2(ADC1)
#define ADC1_JOFR3                      ADC_JOFR3(ADC1)
#define ADC1_JOFR4                      ADC_JOFR4(ADC1)
#define ADC1_HTR                        ADC_HTR(ADC1)
#define ADC1_LTR                        ADC_LTR(ADC1)
#define ADC1_SQR1                       ADC_SQR1(ADC1)
#define ADC1_SQR2                       ADC_SQR2(ADC1)
#define ADC1_SQR3                       ADC_SQR3(ADC1)
#define ADC1_JSQR                       ADC_JSQR(ADC1)
#define ADC1_JDR1                       ADC_JDR1(ADC1)
#define ADC1_JDR2                       ADC_JDR2(ADC1)
#define ADC1_JDR3                       ADC_JDR3(ADC1)
#define ADC1_JDR4                       ADC_JDR4(ADC1)
#define ADC1_DR                         ADC_DR(ADC1)

#define ADC2_SR                         ADC_SR(ADC2)
#define ADC2_CR1                        ADC_CR1(ADC2)
#define ADC2_CR2                        ADC_CR2(ADC2)
#define ADC2_SMPR1                      ADC_SMPR1(ADC2)
#define ADC2_SMPR2                      ADC_SMPR2(ADC2)
#define ADC2_JOFR1                      ADC_JOFR1(ADC2)
#define ADC2_JOFR2                      ADC_JOFR2(ADC2)
#define ADC2_JOFR3                      ADC_JOFR3(ADC2)
#define ADC2_JOFR4                      ADC_JOFR4(ADC2)
#define ADC2_HTR                        ADC_HTR(ADC2)
#define ADC2_LTR                        ADC_LTR(ADC2)
#define ADC2_SQR1                       ADC_SQR1(ADC2)
#define ADC2_SQR2                       ADC_SQR2(ADC2)
#define ADC2_SQR3                       ADC_SQR3(ADC2)
#define ADC2_JSQR                       ADC_JSQR(ADC2)
#define ADC2_JDR1                       ADC_JDR1(ADC2)
#define ADC2_JDR2                       ADC_JDR2(ADC2)
#define ADC2_JDR3                       ADC_JDR3(ADC2)
#define ADC2_JDR4                       ADC_JDR4(ADC2)
#define ADC2_DR                         ADC_DR(ADC2)

#define ADC3_SR                         ADC_SR(ADC3)
#define ADC3_CR1                        ADC_CR1(ADC3)
#define ADC3_CR2                        ADC_CR2(ADC3)
#define ADC3_SMPR1                      ADC_SMPR1(ADC3)
#define ADC3_SMPR2                      ADC_SMPR2(ADC3)
#define ADC3_JOFR1                      ADC_JOFR1(ADC3)
#define ADC3_JOFR2                      ADC_JOFR2(ADC3)
#define ADC3_JOFR3                      ADC_JOFR3(ADC3)
#define ADC3_JOFR4                      ADC_JOFR4(ADC3)
#define ADC3_HTR                        ADC_HTR(ADC3)
#define ADC3_LTR                        ADC_LTR(ADC3)
#define ADC3_SQR1                       ADC_SQR1(ADC3)
#define ADC3_SQR2                       ADC_SQR2(ADC3)
#define ADC3_SQR3                       ADC_SQR3(ADC3)
#define ADC3_JSQR                       ADC_JSQR(ADC3)
#define ADC3_JDR1                       ADC_JDR1(ADC3)
#define ADC3_JDR2                       ADC_JDR2(ADC3)
#define ADC3_JDR3                       ADC_JDR3(ADC3)
#define ADC3_JDR4                       ADC_JDR4(ADC3)
#define ADC3_DR                         ADC_DR(ADC3)

#define ADC_CR1_RES_MASK                (uint32_t)(0x3 << 24)
#define ADC_CR1_SCAN_MASK               (uint32_t)(0x1 << 8)
#define ADC_CR2_ALIGN_MASK              (uint32_t)(0x1 << 11)
#define ADC_CR2_EXTSEL_MASK             (uint32_t)(0xF << 24)
#define ADC_CR2_EXTEN_MASK              (uint32_t)(0x3 << 28)
#define ADC_CR2_CONT_MASK               (uint32_t)(0x1 << 1)
#define ADC_CR2_DDS_MASK                (uint32_t)(0x1 << 9)
#define ADC_CR2_DMA_MASK                (uint32_t)(0x1 << 8)
#define ADC_CR2_ADON_MASK               (uint32_t)(0x1)
#define ADC_CR2_SWSTART_MASK            (uint32_t)(0x1 << 30)
#define ADC_SQR1_L_MASK                 (uint32_t)(0xF << 20)
#define ADC_SMP_MASK                    (uint32_t)(0x3)
#define ADC_SQR_MASK                    (uint32_t)(0x1F)
#define ADC_CCR_ADCPRE_MASK             (uint32_t)(0x3 << 16)
#define ADC_CCR_DMA_MASK                (uint32_t)(0x3 << 14)
#define ADC_CCR_DELAY_MASK              (uint32_t)(0xF << 8)
#define ADC_CCR_MULTI_MASK              (uint32_t)(0x1F)
#define ADC_CCR_TSVREFE_MASK            (uint32_t)(0x1 << 23)

namespace cm3ext {

namespace adc {


enum Number
{
	ADC_1,
	ADC_2,
	ADC_3,
};

enum Resolution
{
	RES_12_BIT = (uint32_t)(0 << 24),
	RES_10_BIT = (uint32_t)(1 << 24),
	RES_08_BIT = (uint32_t)(2 << 24),
	RES_06_BIT = (uint32_t)(3 << 24),
};

enum Alignment
{
	RIGHT_ALIGN,
	LEFT_ALIGN,
};

enum RegularGroupTrigger
{
	T1_CC1 = (uint32_t)(0 << 24),
	T1_CC2 = (uint32_t)(1 << 24),
	T1_CC3 = (uint32_t)(2 << 24),
	T2_CC2 = (uint32_t)(3 << 24),
	T2_CC3 = (uint32_t)(4 << 24),
	T2_CC4 = (uint32_t)(5 << 24),
	T2_TRGO = (uint32_t)(6 << 24),
	T3_CC1 = (uint32_t)(7 << 24),
	T3_TRGO = (uint32_t)(8 << 24),
	T4_CC4 = (uint32_t)(9 << 24),
	T5_CC1 = (uint32_t)(10 << 24),
	T5_CC2 = (uint32_t)(11 << 24),
	T5_CC3 = (uint32_t)(12 << 24),
	T8_CC1 = (uint32_t)(13 << 24),
	T8_TRGO = (uint32_t)(14 << 24),
	EXTI_LINE_11 = (uint32_t)(15 << 24),
};

enum RegularGroupTriggerPolarity
{
	TRIGGER_NONE       = (uint32_t)(0 << 28),
	TRIGGER_ON_RISING  = (uint32_t)(1 << 28),
	TRIGGER_ON_FALLING = (uint32_t)(2 << 28),
	TRIGGER_ON_BOTH    = (uint32_t)(3 << 28),
};

enum ConversionMode
{
	CONTINUOUS_CONV,
	SINGLE_CONV,
};

enum MultiMode
{
	MODE_INDEPENDENT = 0,
};

enum SamplingTime
{
	CYCLES_3   = 0,
	CYCLES_15  = 1,
	CYCLES_28  = 2,
	CYCLES_56  = 3,
	CYCLES_84  = 4,
	CYCLES_112 = 5,
	CYCLES_144 = 6,
	CYCLES_480 = 7,
};

enum Channel
{
	ADC_CHANNEL0	= 0x00,
	ADC_CHANNEL1	= 0x01,
	ADC_CHANNEL2	= 0x02,
	ADC_CHANNEL3	= 0x03,
	ADC_CHANNEL4	= 0x04,
	ADC_CHANNEL5	= 0x05,
	ADC_CHANNEL6	= 0x06,
	ADC_CHANNEL7	= 0x07,
	ADC_CHANNEL8	= 0x08,
	ADC_CHANNEL9    = 0x09,
	ADC_CHANNEL10   = 0x0A,
	ADC_CHANNEL11   = 0x0B,
	ADC_CHANNEL12   = 0x0C,
	ADC_CHANNEL13   = 0x0D,
	ADC_CHANNEL14   = 0x0E,
	ADC_CHANNEL15   = 0x0F,
	ADC_CHANNEL16   = 0x10,
	ADC_CHANNEL17   = 0x11,
	ADC_CHANNEL18   = 0x12,
};

enum Rank
{
	RANK_1 = 1,
	RANK_2 = 2,
	RANK_3 = 3,
	RANK_4 = 4,
	RANK_5 = 5,
	RANK_6 = 6,
	RANK_7 = 7,
	RANK_8 = 8,
	RANK_9 = 9,
	RANK_10 = 10,
	RANK_11 = 11,
	RANK_12 = 12,
	RANK_13 = 13,
	RANK_14 = 14,
	RANK_15 = 15,
	RANK_16 = 16,
};

enum Prescaler
{
	PRESCALER_2 = (uint32_t)(0 << 16),
	PRESCALER_4 = (uint32_t)(1 << 16),
	PRESCALER_6 = (uint32_t)(2 << 16),
	PRESCALER_8 = (uint32_t)(3 << 16),
};

enum DmaMode
{
	MODE_NONE = (uint32_t)(0 << 14),
	MODE_1    = (uint32_t)(1 << 14),
	MODE_2    = (uint32_t)(2 << 14),
	MODE_3    = (uint32_t)(3 << 14),
};

enum Delay
{
	DELAY_CYCLES_5  = (uint32_t)(0 << 8),
	DELAY_CYCLES_6  = (uint32_t)(1 << 8),
	DELAY_CYCLES_7  = (uint32_t)(2 << 8),
	DELAY_CYCLES_8  = (uint32_t)(3 << 8),
	DELAY_CYCLES_9  = (uint32_t)(4 << 8),
	DELAY_CYCLES_10 = (uint32_t)(5 << 8),
	DELAY_CYCLES_11 = (uint32_t)(6 << 8),
	DELAY_CYCLES_12 = (uint32_t)(7 << 8),
	DELAY_CYCLES_13 = (uint32_t)(8 << 8),
	DELAY_CYCLES_14 = (uint32_t)(9 << 8),
	DELAY_CYCLES_15 = (uint32_t)(10 << 8),
	DELAY_CYCLES_16 = (uint32_t)(11 << 8),
	DELAY_CYCLES_17 = (uint32_t)(12 << 8),
	DELAY_CYCLES_18 = (uint32_t)(13 << 8),
	DELAY_CYCLES_19 = (uint32_t)(14 << 8),
	DELAY_CYCLES_20 = (uint32_t)(15 << 8),
};

class Adc
{
public:
	Adc(Number adc);

	void set_resolution(Resolution res);

	void enable_scan_mode();
	void disable_scan_mode();

	void set_data_alignment(Alignment align);
	void set_external_trigger_for_regular_group(RegularGroupTrigger trigger);
	void set_external_trigger_polarity_for_regular_group(RegularGroupTriggerPolarity polarity);
	void set_conversion_mode(ConversionMode mode);

	void enable_dma_request();
	void disable_dma_request();

	void enable_dma();
	void disable_dma();

	void enable();
	void disable();

	void start_conversion();

	void set_number_of_conversions(uint8_t number);
	void set_channel_sampling_time_selection(SamplingTime time, Channel channel);
	void set_conversion_number_in_sequence(uint8_t length, Channel *channel);
	void set_prescaler(Prescaler prescaler);
	void set_dma_mode(DmaMode mode);
	void set_delay_between_two_samples(Delay delay);
	void set_multi_mode(MultiMode mode);

	void enable_temp_sensor();
	void disable_temp_sensor();

	uint32_t get_base_address() {
		return (_adc);
	}

private:
	uint32_t _adc;
};


}  // namespace adc

}  // namespace cm3ext

#endif
