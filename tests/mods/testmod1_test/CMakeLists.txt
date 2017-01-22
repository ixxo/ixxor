set(CXXHDR)
set(CXXSRC
    rnd_source.t.cpp
    loading.t.cpp
    )

ixxor_add_module_test(
    FILES ${CXXHDR} ${CXXSRC}
    )

