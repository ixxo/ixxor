get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

string(REPLACE "_test" "" __module ${target})

enable_testing()
find_package(GTest REQUIRED)

set(CXXHDR)
set(CXXSRC
    loading.t.cpp
    )

add_definitions(-DIXXOR_TEST_SUITE=${target})
add_executable(${target} ${CXXHDR} ${CXXSRC})

target_include_directories(${target}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
    )

target_include_directories(${target}
    SYSTEM PRIVATE
    ${GTEST_INCLUDE_DIRS}
    )


target_link_libraries(${target}
    PRIVATE
    kernel
    core
    )

target_link_libraries(${target}
    PRIVATE
    ${GTEST_BOTH_LIBRARIES}
    )


# Make the datafile...
add_custom_target(${target}_config
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:${__module}>" > ${CMAKE_CURRENT_BINARY_DIR}/${target}.conf
    )

add_dependencies(${target}
    ${__module}
    ${target}_config
    )
