#include <gtest/gtest.h>
#include <ixxor/math/accumulator.hpp>
#include <type_traits>

TEST(ixxor_math, accumulator_test_double)
{
    ixxor::Accumulator<double> acc;
    acc << 1.0;
    auto m = acc.mean();
    static_assert(std::is_same<decltype(m), double>::value, "Invalid mean type");
    EXPECT_NEAR(1.0, acc.mean(), 1e-10);
    acc << 2.0;
    EXPECT_NEAR(1.5, acc.mean(), 1e-10);
    acc << 3.0;
    EXPECT_NEAR(2.0, acc.mean(), 1e-10);
    acc << 4.0;
    EXPECT_NEAR(2.5, acc.mean(), 1e-10);
}

TEST(ixxor_math, accumulator_test_int)
{
    ixxor::Accumulator<int> acc;
    acc << 1;
    auto m = acc.mean();
    static_assert(std::is_same<decltype(m), double>::value, "Invalid mean type");
    EXPECT_NEAR(1.0, acc.mean(), 1e-10);
    acc << 2;
    EXPECT_NEAR(1.5, acc.mean(), 1e-10);
    acc << 3;
    EXPECT_NEAR(2.0, acc.mean(), 1e-10);
    acc << -4;
    EXPECT_NEAR(0.5, acc.mean(), 1e-10);
}

