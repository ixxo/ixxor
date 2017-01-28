set(CXXHDR)
set(CXXSRC
    loading.t.cpp
    )

ixxor_add_plugin_test(
    FILES ${CXXHDR} ${CXXSRC}
    )

