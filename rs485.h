#ifndef RS_485_H
#define RS_485_H

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
}RS485_Settings;

typedef struct {
	uint32_t number;
	Pinout tx;
	Pinout rx;
	Pinout de;
}RS485_Struct;

class RS485
{
public:
	RoundBuffer *rb_in;
	RoundBuffer *rb_out;

	RS485(RS485_Struct rs485, RS485_Settings settings, RoundBuffer rb_in_size, RoundBuffer rb_out_size);

	void usart_enable_tc_interrupt()
	{
		USART_CR1(_rs485) |= USART_CR1_TCIE;
	}
	void usart_disable_tc_interrupt()
	{
		USART_CR1(_rs485) &= ~USART_CR1_TCIE;
	}
	bool interrupt_source_RXNE()
	{
		return (((USART_CR1(_rs485) & USART_CR1_RXNEIE) != 0) && usart_get_flag(_rs485, USART_SR_RXNE));
	}
	bool interrupt_source_TXE()
	{
		return (((USART_CR1(_rs485) & USART_CR1_TXEIE) != 0) && usart_get_flag(_rs485, USART_SR_TXE));
	}
	bool interrupt_source_TC()
	{
		return (((USART_CR1(_rs485) & USART_CR1_TCIE) != 0) && usart_get_flag(_rs485, USART_SR_TC));
	}
	void start_send()
	{
		_de->set();
		usart_enable_tx_interrupt(_rs485);
	}
	void receive_handler()
	{
		if (interrupt_source_RXNE()) {
			rb_in->push(usart_recv(_rs485));
		}
	}
	void transmit_handler()
	{
		if (interrupt_source_TXE()) {
			if (rb_out->get_count()) {
				usart_send(_rs485, rb_out->pop());
			}
			else {
				usart_disable_tx_interrupt(_rs485);
				usart_enable_tc_interrupt();
			}
		}
		if (interrupt_source_TC()) {
			_de->clear();
			usart_disable_tc_interrupt();
		}
	}
	void inirq()
	{
		receive_handler();
		transmit_handler();
	}

private:
	uint32_t _rs485;
	GPIO_ext *_de;
};
#endif
