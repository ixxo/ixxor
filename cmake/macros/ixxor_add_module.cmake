macro(ixxor_add_module)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs FILES LIBRARIES INCLUDE_DIRS)
    cmake_parse_arguments(IXXOR_ADD_MODULE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if(NOT IXXOR_ADD_MODULE_TARGET)
        get_filename_component(IXXOR_ADD_MODULE_TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    endif()
    set(target ${IXXOR_ADD_MODULE_TARGET})

    if(NOT IXXOR_ADD_MODULE_FILES)
        set(IXXOR_ADD_MODULE_FILES ${CXXHDR} ${CXXSRC})
    endif()

    add_library(${target} MODULE ${IXXOR_ADD_MODULE_FILES})

    if(IXXOR_ADD_MODULE_INCLUDE_DIRS)
        target_include_directories(${target}
            PRIVATE ${IXXOR_ADD_MODULE_INCLUDE_DIRS})
    endif()

    target_include_directories(${target}
        PRIVATE ${CMAKE_SOURCE_DIR}
        )

    if(IXXOR_ADD_MODULE_LIBRARIES)
        target_link_libraries(${target}
            PRIVATE ${IXXOR_ADD_MODULE_LIBRARIES}
            )
    endif()

    target_link_libraries(${target}
        PRIVATE
            kernel
            core
        )

    install(TARGETS ${target}
        DESTINATION ${IXXOR_PLUGINS_DIR}
        )

endmacro()
