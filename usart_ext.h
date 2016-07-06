#ifndef USART_EXT_H
#define USART_EXT_H

#include <stdint.h>
#include <libopencm3/stm32/usart.h>
#include "round_buffer.h"
#include "gpio_ext.h"
#ifdef STM32F2
#include <libopencm3/stm32/f2/nvic.h>
#endif
#ifdef STM32F4
#include <libopencm3/stm32/f4/nvic.h>
#endif

using namespace GPIO_CPP_Extension;

typedef struct {
	uint32_t baud_rate;
	uint16_t word_length;
	uint16_t stop_bits;
	uint16_t parity;
	uint16_t mode;
	uint16_t flow_control;
}USART_Settings;

typedef struct {
	uint32_t number;
	Pinout tx;
	Pinout rx;
}USART_Struct;

class USART_ext
{
public:
	RoundBuffer *rb_in;
	RoundBuffer *rb_out;

	USART_ext(USART_Struct usart, USART_Settings settings, RoundBuffer rb_in_size, RoundBuffer rb_out_size);

	bool interrupt_source_RXNE()
	{
		return (((USART_CR1(_usart) & USART_CR1_RXNEIE) != 0) && usart_get_flag(_usart, USART_SR_RXNE));
	}
	bool interrupt_source_TXE()
	{
		return (((USART_CR1(_usart) & USART_CR1_TXEIE) != 0) && usart_get_flag(_usart, USART_SR_TXE));
	}
	void start_send()
	{
		usart_enable_tx_interrupt(_usart);
	}
	void receive_handler()
	{
		if (interrupt_source_RXNE()) {
			rb_in->push(usart_recv(_usart));
		}
	}
	void transmit_handler()
	{
		if (interrupt_source_TXE()) {
			if (rb_out->get_count()) {
				usart_send(_usart, rb_out->pop());
			}
			else {
				usart_disable_tx_interrupt(_usart);
			}
		}
	}
	void inirq()
	{
		receive_handler();
		transmit_handler();
	}

private:
	uint32_t _usart;
};
#endif
