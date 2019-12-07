
set(CPPUTEST_DIR ${CMAKE_BINARY_DIR}/ext/cpputest)
set(CPPUTEST_SRC_DIR ${CPPUTEST_DIR}/src/CppUtest)
set(CPPUTEST_INC_DIR ${CPPUTEST_SRC_DIR}/include)
set(CPPUTEST_LIB_DIR ${CPPUTEST_SRC_DIR}/src/CppUTest)
set(CPPUTESTEXT_LIB_DIR ${CPPUTEST_SRC_DIR}/src/CppUTestExt)

file(MAKE_DIRECTORY ${CPPUTEST_DIR})
include(ExternalProject)
externalproject_add(CppUTest-project
    PREFIX                ${CPPUTEST_DIR}
    GIT_REPOSITORY        https://github.com/cpputest/cpputest.git
    GIT_TAG               "v3.8"
    SOURCE_DIR            ${CPPUTEST_SRC_DIR}
    BUILD_IN_SOURCE       1
    CMAKE_COMMAND         "cmake"
    CMAKE_ARGS            -DTESTS=OFF
    INSTALL_COMMAND       ""
 )

function(add_library_test)
    set(options)
    set(oneValueArgs TESTNAME LIBRARY_UNDER_TEST)
    set(multiValueArgs DEPS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    message(STATUS "Adding test for ${ARG_LIBRARY_UNDER_TEST}")

    add_executable("${ARG_TESTNAME}" "${ARG_TESTNAME}.cpp")
    add_dependencies("${ARG_TESTNAME}" CppUTest-project)
    target_link_libraries("${ARG_TESTNAME}" "${ARG_LIBRARY_UNDER_TEST}" "${ARG_DEPS}" CppUTest CppUTestExt)

    add_test(NAME "${ARG_TESTNAME}" COMMAND "${ARG_TESTNAME}")
endfunction()

include_directories(${CPPUTEST_INC_DIR})
link_directories(${CPPUTEST_LIB_DIR} ${CPPUTESTEXT_LIB_DIR})

add_library(mocks SHARED mocks/mutex_mock.cpp
                         mocks/crc8_mock.cpp
                         mocks/device_mock.cpp)
add_dependencies(mocks CppUTest-project)

add_library(flash_mock SHARED mocks/flash_mock.cpp)
add_dependencies(flash_mock CppUTest-project)

add_library(emulator SHARED emulator/flash.c)

add_library_test(TESTNAME "test_nvs"
                 LIBRARY_UNDER_TEST nvs
                 DEPS mocks flash_mock)

add_library_test(TESTNAME "test_nvs_emulated"
                 LIBRARY_UNDER_TEST nvs
                 DEPS mocks emulator)
