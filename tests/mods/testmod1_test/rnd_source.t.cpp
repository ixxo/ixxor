#include <gtest/gtest.h>
#include <ixxor/kernel/kernel.hpp>
#include <ixxor/kernel/data_source.hpp>
#include <ixxor/maths/accumulator.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <list>

TEST(IXXOR_TEST_SUITE, rnd_source_count)
{
    using namespace ixxor;

    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    std::list<Tick> ticks;
    auto callback = [&ticks](SymbolID const& id, Tick const& tick) {
        ticks.push_back(tick);
    };

    int const n_ticks = 100;
    double const freq = 300.0; // 300 ticks per second, on average
    auto rndsrc = kernel.get<DataSource>("FoobarSource", n_ticks, freq);
    rndsrc->init();

    std::vector<SymbolID> symbols;
    rndsrc->support(std::back_inserter(symbols));
    ASSERT_FALSE(symbols.empty());
    auto symbol = symbols.front();

    bool sub_rv = rndsrc->subscribe(symbol, callback);
    ASSERT_TRUE(sub_rv);

    auto t_kill = std::chrono::steady_clock::now() + std::chrono::minutes(1);
    while(ticks.size() < n_ticks &&
          std::chrono::steady_clock::now() < t_kill) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    EXPECT_EQ(n_ticks, ticks.size());
}

TEST(IXXOR_TEST_SUITE, rnd_source_frequency)
{
    using namespace ixxor;

    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    std::vector<Ptime> ticks;
    auto callback = [&ticks](SymbolID const& id, Tick const& tick) {
        ticks.push_back(tick.t);
    };

    // Should take around 5 seconds
    int const n_ticks = 5000;
    double const freq = 1000.0; // 1000 ticks per second, on average
    auto rndsrc = kernel.get<DataSource>("FoobarSource", n_ticks, freq);
    rndsrc->init();

    std::vector<SymbolID> symbols;
    rndsrc->support(std::back_inserter(symbols));
    ASSERT_FALSE(symbols.empty());
    auto symbol = symbols.front();

    bool sub_rv = rndsrc->subscribe(symbol, callback);
    ASSERT_TRUE(sub_rv);

    auto t_kill = std::chrono::steady_clock::now() + std::chrono::minutes(1);
    while(ticks.size() < n_ticks &&
          std::chrono::steady_clock::now() < t_kill) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    Accumulator<std::int64_t> acc;
    for(std::size_t i=0;i<ticks.size()-1;++i) {
        auto ts = (ticks[i+1] - ticks[i]) / Duration::microseconds(1);
        acc << ts;
    }
    double ex_period = 1e6 / freq; // in microseconds
    // 10% around the expected mean...
    EXPECT_NEAR(ex_period, acc.mean(), 0.10 * ex_period);
}



