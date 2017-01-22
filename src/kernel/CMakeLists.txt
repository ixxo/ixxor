get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    kernel.hpp
    )

set(CXXSRC
    kernel.cpp
    )

add_library(${target} ${CXXHDR} ${CXXSRC})

