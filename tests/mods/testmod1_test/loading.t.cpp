#include <gtest/gtest.h>
#include <ixxor/kernel/kernel.hpp>
#include <ixxor/kernel/data_source.hpp>


TEST(IXXOR_TEST_SUITE, loading_test)
{
    using namespace ixxor;

    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");
    // And then unload...
    SUCCEED();
}

