# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann

if (BUILD_AVR)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  find_library(C_LIB c)
  add_avr_executable(NvsExample main.c
                               bsp/led.c
                               bsp/ramflash.c)
  avr_target_link_libraries(NvsExample ${C_LIB} nvs)

endif()
