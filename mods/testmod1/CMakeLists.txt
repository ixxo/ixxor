get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CXXHDR
    my_i1.hpp
    my_i2.hpp
    rnd_source.hpp
    )
set(CXXSRC
    testmod1.cpp
    rnd_source.cpp
    )

add_library(${target} MODULE ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )
target_link_libraries(${target}
    PRIVATE
    kernel
    core
    )

install(TARGETS ${target}
    DESTINATION modules
    )

