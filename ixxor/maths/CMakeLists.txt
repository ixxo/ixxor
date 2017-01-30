get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    accumulator.hpp
    )

set(CXXSRC
    accumulator.cpp
    )

add_library(${target} STATIC ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )

set_target_properties(${target} PROPERTIES FOLDER Libs)

