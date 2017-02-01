set(CXXHDR)
set(CXXSRC
    time_series.t.cpp
    )

ixxor_add_lib_test(
    FILES ${CXXHDR} ${CXXSRC}
    )


