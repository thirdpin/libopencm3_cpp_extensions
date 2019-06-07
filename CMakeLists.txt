cmake_minimum_required(VERSION 3.10)

project(cm3cpp LANGUAGES C CXX ASM)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/extra/one_wire.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/irq/irq.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/utils/round_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/adc_dma.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/adc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/i2c.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/spi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/systick.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/usart_rb.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/usart.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/rs485.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cm3cpp/dma.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)