#ifndef LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_
#define LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_

#include <cm3ext_config.h>

#ifndef CM3_ASSERT
#define CM3_ASSERT( x ) if( ( x ) == 0 ) { while(true) { asm(""); } }
#endif

#if CM3EXT_ENABLE_IMPLISIT_DESTRUCTOR_CALLS == 0
#define CM3EXT_EXPLISIT_DESTRUCTOR(c) ~c() { CM3_ASSERT(false) }
#else
#define CM3EXT_EXPLISIT_DESTRUCTOR(c) ~c() = default;
#endif

#endif /* LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_ */
