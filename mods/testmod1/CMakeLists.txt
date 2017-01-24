get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CXXHDR)
set(CXXSRC
    testmod1.cpp
    )

add_library(${target} MODULE ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )


install(TARGETS ${target}
    DESTINATION modules
    )

