.. role:: cpp(code)
   :language: cpp

==============
cm3cpp library
==============

-----------------------------------
C++ extensions over OpenCM3 library
-----------------------------------

CMake target
============

CMake target name for this library is cm3cpp. Target
is a interface library. Just use ``add_subdirectory`` to
add library to your build.

Required dependency of this library is opencm3 library.
Be sure you link it to your target that uses cm3cpp.

Library supports only F2 and F4 microcontrollers.

Library defines:
================

    - ``CM3CPP_CUSTOM_SYSTICK`` — disable library systick realization
      (enabled by default). If define enabled you could not use
      :cpp:`systick::Counter` class;

    - ``CM3CPP_ENABLE_IMPLISIT_DESTRUCTOR_CALLS`` — do not call
      ``assert(false)`` if dangerous destructor of library class is
      called.
