# ZephNVS
ZephNVS is a port of the Zephyr NVS. This enables to use this wonderfull storage in non-Zephyr projects.

See Documentation on [github.com](https://spoorcc.github.io/zephnvs). 
Or get the source code on [github.com/spoorcc](https://github.com/spoorcc/zephnvs).

## Main design goals

* No Dynamic memory
* A portable pure C Core
* Compilable for any platform
* Thread-safe (at some point :) )
* Complete documentation
* Extensible for your needs

## Basic Usage


# Developing

## Compiling

Make sure to have CMake and a compiler installed.

~~~~~~~~~~~~~~~{.sh}
    mkdir bld
    cd bld
    cmake ..
    make
~~~~~~~~~~~~~~~

## Running tests

~~~~~~~~~~~~~~~{.sh}
    cd bld
    make test
~~~~~~~~~~~~~~~

For more verbose test output use CTest directly

~~~~~~~~~~~~~~~{.sh}
    ctest --verbose
~~~~~~~~~~~~~~~

## Generating documentation

The documentation is generated with Doxygen and CMake.

~~~~~~~~~~~~~~~{.sh}
    cd bld
    make doc
~~~~~~~~~~~~~~~