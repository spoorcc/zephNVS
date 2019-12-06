
if (BUILD_AVR)
    add_avr_library(nvs STATIC nvs.c)
elseif(BUILD_MSP430)
    msp430_add_library_compilation(nvs STATIC nvs.c)
else()
    add_library(nvs SHARED nvs.c)
endif()