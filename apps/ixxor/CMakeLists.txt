get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    app.hpp
    )
set(CXXSRC
    app.cpp
    ixxor.m.cpp
    )

add_executable(${target} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )

target_link_libraries(${target}
    PRIVATE
    kernel
    core
    maths
    appenv
    )

    
set_target_properties(${target} PROPERTIES FOLDER Apps)

install(TARGETS ${target}
    DESTINATION bin
    )

