cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
OPTION(BUILD_AVR "Use AVR toolchain for compiling library" OFF)
OPTION(BUILD_MSP430 "Use MSP430 toolchain for compiling library" OFF)

IF(BUILD_AVR)
    include("${CMAKE_MODULE_PATH}/avr_options.cmake")
ELSEIF(BUILD_MSP430)
    include("${CMAKE_MODULE_PATH}/msp430_options.cmake")
    include_directories(inc/Platforms/MSP430)
ENDIF()

project(ZephNVS)
 
SET ( ZEPH_NVS_TITLE "ZephNVS" )
SET ( ZEPH_NVS_SUBTITLE "Zephyrs NVS - as a library" )
SET ( ZEPH_NVS_VERSION "0.0.0-cmake" )
OPTION(BUILD_ZEPH_NVS_DOC "Create doxygen documentation for developers" OFF)

set_property(GLOBAL PROPERTY C_STANDARD 99)

include_directories(inc)
add_subdirectory(src)
add_subdirectory(example/arduino_nano)

IF (BUILD_AVR)
    message(STATUS "Skipping tests & doc when compiling for avr")
ELSEIF(BUILD_MSP430)
    message(STATUS "Skipping tests & doc when compiling for msp430")
ELSE()
    enable_testing()
    add_subdirectory(test)
    add_subdirectory(doc)
ENDIF()
