get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    kernel.hpp
    indicator.hpp
    data_source.hpp
    )

set(CXXSRC
    kernel.cpp
    indicator.cpp
    data_source.cpp
    )

add_library(${target} STATIC ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )

