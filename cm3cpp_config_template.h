#ifndef CM3CPP_CONFIG_H_
#define CM3CPP_CONFIG_H_

//*** Must be changed according to your RCC configuration
#define CM3CPP_SYSTEM_CORE_CLOCK (uint32_t)120000000

#define CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE 1
//*** Or you can use custom systick source (like timer)
#if (CM3CPP_ENABLE_CUSTOM_SYSTICK_SOURCE == 1)
#define CM3CPP_TIMER_N 12
#define CM3CPP_SYSTICK_CLOCK (30000000 * 2)
#define CM3CPP_SYSTICK_CLOCK_DIV 1000  // 1 kHz
#define CM3CPP_SYSTICK_PERIOD 0xffff
#else
#define CM3CPP_SYSTICK_CLOCK_DIV 1000  // 1 kHz
#define CM3CPP_SYSTICK_CLOCK CM3CPP_SYSTEM_CORE_CLOCK
#endif

//*** User assert function define
#define CM3_ASSERT(x)                                                          \
    if ((x) == 0)                                                              \
    user_assert_func(__FILE__, __LINE__)

//*** This option enable destructors for classes using a heap allocation
//    inside. If you can't destruct an object it prevents a memory leak.
#define CM3CPP_ENABLE_IMPLISIT_DESTRUCTOR_CALLS 0

#endif /* CM3CPP_CONFIG_H_ */
