get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    data_source.hpp
    indicator.hpp
    kernel.hpp
    kernel_component.hpp
    kernel_component_entry.hpp
    module_util.hpp
    protobuf.hpp
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
set_target_properties(${target} PROPERTIES FOLDER Libs)

