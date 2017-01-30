get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    rc_config.hpp
    path_util.hpp
    sys_util.hpp
    )

set(CXXSRC
    rc_config.cpp
    path_util.cpp
    sys_util.cpp
    )

add_library(${target} STATIC ${CXXHDR} ${CXXSRC})


target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )

set_target_properties(${target} PROPERTIES FOLDER Libs)
