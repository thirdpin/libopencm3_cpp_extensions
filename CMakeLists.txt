cmake_minimum_required(VERSION 3.10)

project(cm3cpp LANGUAGES C CXX ASM)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/extra/one_wire.cpp
    ${CMAKE_CURRENT_LIST_DIR}/irq/cm3cpp_irq.cpp
    ${CMAKE_CURRENT_LIST_DIR}/utils/round_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_adc_dma.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_adc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_i2c.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_spi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_systick.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_usart_rb.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_usart.cpp
    ${CMAKE_CURRENT_LIST_DIR}/rs485.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp_dma.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/../
)