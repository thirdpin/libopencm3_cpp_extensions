#ifndef CM3CPP_CONFIG_H_
#define CM3CPP_CONFIG_H_

#define CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE  0
//*** Or you can use custom systick source (like timer)
#if (CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE == 1)
#define CM3CPP_INT_SOURCE 					        TIM1
#define CM3CPP_SYS_TICK_INT_FUNC			        tim1_isr
#endif

//*** User assert function define
#define CM3CPP_ASSERT( x ) 	configASSERT( x )

//*** Must be changed according to your RCC configuration
#define CM3CPP_SYSTEM_CORE_CLOCK					(uint32_t)120000000
#define CM3CPP_SYSTEM_CORE_CLOCK_DIV                (uint32_t)1000

//*** This option enable destructors for classes using a heap allocation
//    inside. If you can't destruct an object it prevents a memory leak.
#define CM3CPP_ENABLE_IMPLISIT_DESTRUCTOR_CALLS     0



#endif /* CM3CPP_CONFIG_H_ */
