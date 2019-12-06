#toolchain cmake file for msp430-gcc/avrdude toolchain

# needs the following variables:
# MSP430_MCU : mcu type
# MSP430_MCU_FREQ : clock frequency (defines F_CPU)

#generic avr flags
set(MSP430_CFLAGS "-ffunction-sections -fdata-sections" CACHE STRING "MSP430 compilation flags")
set(MSP430_LFLAGS "-Wl,--relax,--gc-sections" CACHE STRING "MSP430 link flags")

#find toolchain programs
find_program(MSP430_GCC msp430-gcc)
find_program(MSP430_GXX msp430-g++)
find_program(MSP430_OBJCOPY msp430-objcopy)
find_program(MSP430_SIZE msp430-size)
find_program(MSP430_OBJDUMP msp430-objdump)
find_program(MSPDEBUG mspdebug)

set(CMAKE_C_COMPILER_FORCED True)
set(CMAKE_CXX_COMPILER_FORCED True)

#define toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp430)
set(CMAKE_C_COMPILER ${MSP430_GCC})
set(CMAKE_CXX_COMPILER ${MSP430_GXX})

#Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif(NOT CMAKE_BUILD_TYPE)


function(msp430_add_executable_compilation EXECUTABLE)

    set(EXECUTABLE_ELF "${EXECUTABLE}.elf")

    # main target for the executable depends of elf
    add_custom_target(${EXECUTABLE} ALL DEPENDS ${EXECUTABLE_ELF})

    # compile and link elf file
    add_executable(${EXECUTABLE_ELF} ${ARGN})
    set_target_properties(${EXECUTABLE_ELF} PROPERTIES
        COMPILE_FLAGS "-mmcu=${MSP430_MCU} -DF_CPU=${MSP430_MCU_FREQ} ${MSP430_CFLAGS}"
        LINK_FLAGS "-mmcu=${MSP430_MCU} ${MSP430_LFLAGS}")

    # display size info after compilation
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${MSP430_SIZE} ${EXECUTABLE_ELF})
endfunction(msp430_add_executable_compilation)

function(msp430_add_library_compilation LIBRARY)

    set(LIBRARY_ELF "${LIBRARY}.a")

    # main target for the library depends of elf
    add_custom_target(${LIBRARY} ALL DEPENDS ${LIBRARY_ELF})

    # compile and link elf file
    add_library(${LIBRARY_ELF} STATIC ${ARGN})
    set_target_properties(${LIBRARY_ELF} PROPERTIES
        COMPILE_FLAGS "-mmcu=${MSP430_MCU} -DF_CPU=${MSP430_MCU_FREQ} ${MSP430_CFLAGS}"
        LINK_FLAGS "-mmcu=${MSP430_MCU} ${MSP430_LFLAGS}")

endfunction(msp430_add_library_compilation)

function(msp430_add_executable_upload ${EXECUTABLE})
    add_custom_target(upload_${EXECUTABLE} 
        COMMAND ${MSPDEBUG} -q rf2500 "prog ${EXECUTABLE}.elf"
        DEPENDS ${EXECUTABLE})
endfunction(msp430_add_executable_upload)

function(msp430_add_executable EXECUTABLE)
    if(NOT MSP430_MCU)
        message(FATAL_ERROR "MSP430_MCU not defined")
    endif(NOT MSP430_MCU)
    msp430_add_executable_compilation(${EXECUTABLE} ${ARGN})
    msp430_add_executable_upload(${EXECUTABLE})
endfunction(msp430_add_executable)


