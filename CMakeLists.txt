cmake_minimum_required(VERSION 3.1.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
project(Ixxor)

option(WITH_TESTS "Build Tests" ON)

include(config)
include(macros)

add_subdirectory(ixxor)
add_subdirectory(mods)
add_subdirectory(apps)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()


