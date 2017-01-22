get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    symbol.hpp
    detail/identifier.hpp
    )

set(CXXSRC
    instrument.cpp
    currency.cpp
    exchange.cpp
    )

add_library(${target} STATIC ${CXXHDR} ${CXXSRC})

