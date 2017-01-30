get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXSRC
    module_test.m.cpp
    )

add_executable(${target} ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )


target_link_libraries(${target}
    PRIVATE
    kernel
    appenv
    )

install(TARGETS ${target}
    DESTINATION bin
    )
