#ifndef SYSTICK_API_H
#define SYSTICK_API_H

#include <stdint.h>
#include <libopencm3/cm3/systick.h>

#define SYSTEM_CORE_CLOCK						(uint32_t)120000000
#define SYSTEM_CORE_CLOCK_DIV                   (uint32_t)1000

extern "C" void sys_tick_handler(void);
extern "C" void delay_nop(uint32_t count);

typedef enum {
	CYCLE,
	ONE_SHOT
}TimerMode;

void systick_init(uint32_t div = SYSTEM_CORE_CLOCK_DIV);
uint32_t get_counter_ms();
void delay_ms(uint32_t ms);

class TimerMs
{
public:
	TimerMs(TimerMode mode, uint32_t period_ms);
	bool timeout();
	bool start();
	bool stop();

private:
	uint32_t _saved_ms;
	uint32_t _period_ms;
	TimerMode _mode;
	bool _is_active;
};


#endif
