#include <gtest/gtest.h>
#include <ixxor/kernel/kernel.hpp>

TEST(IXXOR_TEST_SUITE, loading_test)
{
    using namespace ixxor;

    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    //auto rndsrc = kernel.data_source("FoobarSource");


    SUCCEED();
}

