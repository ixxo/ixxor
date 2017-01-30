macro(ixxor_add_module_test)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs FILES LIBRARIES INCLUDE_DIRS)
    cmake_parse_arguments(IXXOR_ADD_MODULE_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if(NOT IXXOR_ADD_MODULE_TEST_TARGET)
        get_filename_component(IXXOR_ADD_MODULE_TEST_TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    endif()
    set(target ${IXXOR_ADD_MODULE_TEST_TARGET})

    string(REPLACE "_test" "" __module ${target})

    enable_testing()
    find_package(GTest REQUIRED)

    set(FILES ${IXXOR_ADD_MODULE_TEST_FILES})

    add_definitions(
        -DIXXOR_TEST_SUITE=${target}
        )
    add_executable(${target} ${FILES})

    if(IXXOR_ADD_MODULE_TEST_INCLUDE_DIRS)
        target_include_directories(${target}
            PRIVATE ${IXXOR_ADD_MODULE_TEST_INCLUDE_DIRS}
            )
    endif()

    target_include_directories(${target}
        PRIVATE ${CMAKE_SOURCE_DIR}
        )

    target_include_directories(${target}
        SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS}
        )

    if(IXXOR_ADD_MODULE_TEST_LIBRARIES)
        target_link_libraries(${target}
            PRIVATE ${IXXOR_ADD_MODULE_TEST_LIBRARIES}
            )
    endif()

    target_link_libraries(${target}
        PRIVATE
            kernel
            core
            appenv
        )

    target_link_libraries(${target}
        PRIVATE
        ${GTEST_BOTH_LIBRARIES}
        )

    add_dependencies(${target}
        ${__module}
        )

    install(TARGETS ${target}
        DESTINATION share/ixxor/tests
        )

endmacro()
