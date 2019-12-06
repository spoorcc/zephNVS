
# Set mandatory MCU variables
set(MSP430_MCU msp430g2553)
set(MSP430_MCU_FREQ 1000000UL)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_MODULE_PATH}/generic-gcc-msp430.cmake")