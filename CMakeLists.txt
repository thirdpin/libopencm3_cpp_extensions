cmake_minimum_required(VERSION 3.10)

project(cm3cpp LANGUAGES C CXX ASM)

add_library(${PROJECT_NAME} INTERFACE)

set(CM3CPP_LOCATION ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME} INTERFACE
	${CM3CPP_LOCATION}/extra/one_wire.cpp
    ${CM3CPP_LOCATION}/irq/cm3cpp_irq.cpp
    ${CM3CPP_LOCATION}/utils/round_buffer.cpp
    ${CM3CPP_LOCATION}/cm3cpp_adc_dma.cpp
    ${CM3CPP_LOCATION}/cm3cpp_adc.cpp
    ${CM3CPP_LOCATION}/cm3cpp_gpio.cpp
    ${CM3CPP_LOCATION}/cm3cpp_i2c.cpp
    ${CM3CPP_LOCATION}/cm3cpp_spi.cpp
    ${CM3CPP_LOCATION}/cm3cpp_systick.cpp
    ${CM3CPP_LOCATION}/cm3cpp_timer.cpp
    ${CM3CPP_LOCATION}/cm3cpp_usart_rb.cpp
    ${CM3CPP_LOCATION}/cm3cpp_usart.cpp
    ${CM3CPP_LOCATION}/rs485.cpp
    ${CM3CPP_LOCATION}/cm3cpp_dma.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CM3CPP_LOCATION}/../
)