#ifndef CM3EXT_CONFIG_H_
#define CM3EXT_CONFIG_H_

#define CM3EXT_ENABLE_CUSTOM_SYSTICK_SOURCE  0

//*** Or you can use custom systick source (like timer)
//#define CM3EXT_ENABLE_CUSTOM_SYSTICK_SOURCE       1
//#define CM3EXT_INT_SOURCE 					    TIM1
//#define CM3EXT_SYS_TICK_INT_FUNC			        tim1_isr


//*** Must be changed according to your RCC configuration
#define CM3EXT_SYSTEM_CORE_CLOCK					(uint32_t)120000000
#define CM3EXT_SYSTEM_CORE_CLOCK_DIV                (uint32_t)1000

//*** This option enable destructors for classes using a heap allocation
//    inside. If you can't destruct an object it prevents a memory leak.
#define CM3EXT_ENABLE_IMPLISIT_DESTRUCTOR_CALLS     0

#endif /* CM3EXT_CONFIG_H_ */
