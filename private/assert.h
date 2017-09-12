#ifndef CM3CPP_ASSERT_H_
#define CM3CPP_ASSERT_H_

#include <cm3cpp_config.h>

#ifndef CM3CPP_ASSERT
#define CM3CPP_ASSERT( x ) if( ( x ) ) { while(true) { asm(""); } }
#endif

#if CM3CPP_ENABLE_IMPLISIT_DESTRUCTOR_CALLS == 1
#define CM3CPP_EXPLISIT_DESTRUCTOR(c) ~c() = default;
#else
#define CM3CPP_EXPLISIT_DESTRUCTOR(c) ~c() { CM3CPP_ASSERT(false); }
#endif

#endif /* CM3CPP_ASSERT_H_ */
