set(CXXHDR
    )
set(CXXSRC
    accumulator.t.cpp
    )

ixxor_add_lib_test(
    FILES ${CXXHDR} ${CXXSRC}
    )
