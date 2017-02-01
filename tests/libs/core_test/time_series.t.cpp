#include <gtest/gtest.h>
#include <ixxor/core/time_series.hpp>
#include <ixxor/core/ptime.hpp>
#include <ixxor/core/price.hpp>
#include <random>

TEST(ixxor_core, time_series_emplace)
{
    using namespace ixxor;
    Ptime ts(Date(2016,1,1), Duration::hours(6));
    Price price{100.0};
    
    TimeSeries<Price, Ptime> series;
    EXPECT_TRUE(series.empty());
    auto it1 = series.emplace(ts, price);
    EXPECT_EQ(series.begin(), it1);
    auto it2 = series.emplace(ts + Duration::seconds(10), price);
    EXPECT_NE(series.begin(), it2);
    auto it3 = series.emplace(ts + Duration::seconds(-10), price);
    EXPECT_EQ(series.begin(), it3);
    auto it4 = series.emplace(ts + Duration::seconds(-5), price);
    EXPECT_NE(series.begin(), it4);
    EXPECT_EQ(series.begin()+1, it4);
}

TEST(ixxor_core, time_series_tail_and_emplace_to_front)
{
    using namespace ixxor;
    Ptime ts(Date(2016,1,1), Duration::hours(6));
    Price price{100.0};
    auto dts = Duration::seconds(1);
    
    TimeSeries<Price, Ptime> series{
        {ts + 0*dts, price},
        {ts + 1*dts, price},
        {ts + 2*dts, price},
        {ts + 3*dts, price},
        {ts + 4*dts, price},
        {ts + 5*dts, price},
        {ts + 6*dts, price}
    };
    EXPECT_EQ(7, series.size());
    series.tail(ts + 3*dts);
    EXPECT_EQ(4, series.size());
    EXPECT_EQ(ts + 3*dts, series.front().first);
    series.emplace(ts - dts, price);
    EXPECT_EQ(5, series.size());
    EXPECT_EQ(ts - dts, series.front().first);
    EXPECT_EQ(ts + 3*dts, (series.begin()+1)->first);
}

TEST(ixxor_core, time_series_ntail)
{
    using namespace ixxor;
    Ptime ts(Date(2016,1,1), Duration::hours(6));
    Price price{100.0};
    auto dts = Duration::seconds(1);
    
    TimeSeries<Price, Ptime> series{
        {ts + 0*dts, price},
        {ts + 1*dts, price},
        {ts + 2*dts, price},
        {ts + 3*dts, price},
        {ts + 4*dts, price},
        {ts + 5*dts, price},
        {ts + 6*dts, price}
    };
    EXPECT_EQ(7, series.size());
    series.ntail(4);
    EXPECT_EQ(4, series.size());
    EXPECT_EQ(ts + 3*dts, series.front().first);
    series.ntail(0);
    EXPECT_TRUE(series.empty());
    EXPECT_EQ(0, series.size());
    EXPECT_EQ(series.end(), series.end());
    EXPECT_EQ(series.rend(), series.rbegin());
}

TEST(ixxor_core, time_series_remains_ordered)
{
    using namespace ixxor;
    Ptime ts(Date(2016,1,1), Duration::hours(6));
    Price price{100.0};
    
    TimeSeries<Price, Ptime> series;
    EXPECT_TRUE(series.empty());
    int n = 1000;
    std::default_random_engine eng;
    std::uniform_int_distribution<int> rndi(-500, 500);
    for(int i=0;i<n;++i) {
        series.emplace(ts + Duration::seconds(rndi(eng)), price);
    }
    ASSERT_LT(series.front().first, series.back().first);
    for(auto it = series.begin(); it+1 != series.end(); ++it) {
        ASSERT_LE(it->first, (it+1)->first);
    }
}

TEST(ixxor_core, time_series_test)
{
    using namespace ixxor;
    TimeSeries<Price, Ptime> series;
    EXPECT_TRUE(series.empty());
    Ptime ts(Date(2016,1,1), Duration::hours(6));
    auto const start = ts;
    auto inc = [](auto& t, auto& p) {
        t += Duration::seconds(1);
        p += Price{0.001};
    };
    Price price{100.0};
    int n = 280;
    for(int i=0;i<n;++i, inc(ts, price)) {
        series.emplace_back(ts, price);
    };
    EXPECT_FALSE(series.empty());
    EXPECT_EQ(n, series.size());
    if (series.capacity() == series.size()) {
        // a little fix...
        series.push_back({ts, price});
        inc(ts, price);
        ++n;
    }
    EXPECT_EQ(n, series.size());
    // Let's cut something...
    // First cut nothing.
    series.tail(start);
    EXPECT_EQ(n, series.size());
    series.tail(start + Duration::seconds(1));
    EXPECT_EQ(n-1, series.size());
    // Now cut seriously.
    int n_cut = n / 3;
    series.tail(start + Duration::seconds(n_cut));
    // Should be way less..
    EXPECT_EQ(n - n_cut, series.size());
    int n_left = static_cast<int>(series.capacity()) - static_cast<int>(series.size());
    EXPECT_LT(0, n_left);
    for(int i=0;i<n_left; ++i, inc(ts, price)) {
        series.emplace(ts, price);
    };
    // Now it should be
    EXPECT_EQ(series.size(), series.capacity());
}

