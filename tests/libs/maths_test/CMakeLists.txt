get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

enable_testing()
find_package(GTest REQUIRED)

set(CXXSRC
    accumulator.t.cpp
    )

add_executable(${target} ${CXXSRC})

target_include_directories(${target}
    PRIVATE ${CMAKE_SOURCE_DIR}
    )

target_include_directories(${target}
    SYSTEM PRIVATE ${GTEST_INCLUDE_DIRS}
    )

target_link_libraries(${target}
    PRIVATE
        core
        maths
    )

target_link_libraries(${target}
    PRIVATE
    ${GTEST_BOTH_LIBRARIES}
    )
    
install(TARGETS ${target}
    DESTINATION share/ixxor/tests
    )
