# @file CMakeLists.txt
# @brief CMake configuration to build the Pixie-Net programs.
# @authors S. V. Paulauskas
# @date November 10, 2019
# @copyright Copyright (c) 2019 S. V. Paulauskas. 
cmake_minimum_required(VERSION 3.10)

project(pixie-net)

if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "7.0.0")
        message(FATAL_ERROR "GCC version 7.0.0+ required.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fPIC -fdiagnostics-color=auto -pthread")
endif ()

# If user does not specify prefix we assign it to the project root directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Install Prefix not specified.")
    get_filename_component(INSTALL_DIR ${PROJECT_SOURCE_DIR}/install REALPATH)
    set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE PATH "Install Prefix" FORCE)
endif ()
message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Build type, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
    message(STATUS "Build type not defined, using default: ${CMAKE_BUILD_TYPE}")
endif (NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

include(CMakeDependentOption)
option(BUILD_TESTS "Builds programs designed to test the package. Including UnitTest++ test." OFF)
option(USE_KAFKA "Builds acquire with Kafka support" ON)
option(USE_NETDAQ "Builds network connected DAQ" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Threads REQUIRED)
find_package(Boost 1.65.1 REQUIRED COMPONENTS date_time chrono atomic program_options system thread log python)

if (USE_NETDAQ)
    find_package(ZeroMQ REQUIRED)
endif (USE_NETDAQ)

if (USE_KAFKA)
    find_package(LibRDKafka 0.11.0 REQUIRED)
endif (USE_KAFKA)

# https://github.com/unittest-cpp/unittest-cpp.git
if (BUILD_TESTS)
    find_package(UnitTest++ REQUIRED)
    link_directories(${UNITTEST++_LIBRARY_DIR})
    include_directories(${UNITTEST++_INCLUDE_DIR})
    enable_testing()
endif (BUILD_TESTS)

include_directories(include)
add_subdirectory(src)
