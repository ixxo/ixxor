get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CXXHDR
    currency.hpp
    date.hpp
    duration.hpp
    exchange.hpp
    futures.hpp
    instrument.hpp
    price.hpp
    ptime.hpp
    side.hpp
    symbol.hpp
    tick.hpp
    tick_series.hpp
    tick_util.hpp
    time_series.hpp
    volume.hpp
    detail/identifier.hpp
    )

set(CXXSRC
    currency.cpp
    exchange.cpp
    instrument.cpp
    tick_series.cpp
    )

add_library(${target} STATIC ${CXXHDR} ${CXXSRC})

set_target_properties(${target} PROPERTIES FOLDER Libs)
