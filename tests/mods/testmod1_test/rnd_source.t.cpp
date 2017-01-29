#include <gtest/gtest.h>
#include <ixxor/kernel/kernel.hpp>
#include <ixxor/kernel/data_source.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <list>

TEST(IXXOR_TEST_SUITE, rnd_source_test)
{
    using namespace ixxor;

    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    std::list<Tick> ticks;
    auto callback = [&ticks](SymbolID const& id, Tick const& tick) {
        ticks.push_back(tick);
    };

    int const n_ticks = 10;
    auto rndsrc = kernel.get<DataSource>("FoobarSource", n_ticks);
    rndsrc->init();

    bool sub_rv = rndsrc->subscribe(SymbolID{"IXXORND"}, callback);
    ASSERT_TRUE(sub_rv);

    auto t_kill = std::chrono::steady_clock::now() + std::chrono::minutes(1);
    while(ticks.size() < n_ticks &&
          std::chrono::steady_clock::now() < t_kill) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    EXPECT_EQ(10, ticks.size());
}

