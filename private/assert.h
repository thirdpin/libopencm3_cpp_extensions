#ifndef LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_
#define LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_

#include <cm3ext_config.h>

#ifndef CM3EXT_ASSERT
#define CM3EXT_ASSERT( x ) if( ( x ) ) { while(true) { asm(""); } }
#endif

#if CM3EXT_ENABLE_IMPLISIT_DESTRUCTOR_CALLS == 1
#define CM3EXT_EXPLISIT_DESTRUCTOR(c) ~c() = default;
#else
#define CM3EXT_EXPLISIT_DESTRUCTOR(c) ~c() { CM3EXT_ASSERT(false) }
#endif

#endif /* LIBOPENCM3_CPP_EXTENSIONS_ASSERT_H_ */
