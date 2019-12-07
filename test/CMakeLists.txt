
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

function(add_library_test LIBRARY)

    message(STATUS "Adding test for ${LIBRARY}")
    set(TESTNAME test_${LIBRARY})

    add_executable(${TESTNAME} ${TESTNAME}.cpp)
    add_dependencies(${TESTNAME} CppUTest-project)
    target_link_libraries(${TESTNAME} ${LIBRARY} CppUTest CppUTestExt mocks)

    add_test(NAME ${LIBRARY} COMMAND ${TESTNAME})
endfunction()

include_directories(${CPPUTEST_INC_DIR})
link_directories(${CPPUTEST_LIB_DIR} ${CPPUTESTEXT_LIB_DIR})

add_library(mocks SHARED mocks/flash_mock.cpp
                         mocks/mutex_mock.cpp
                         mocks/crc8_mock.cpp
                         mocks/device_mock.cpp)
add_dependencies(mocks CppUTest-project)

add_library_test("nvs")
