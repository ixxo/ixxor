cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
project(Ixxor)


include(config)
include(macros)

add_subdirectory(ixxor)
add_subdirectory(mods)
add_subdirectory(tests)


