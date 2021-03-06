#include "rnd_source.hpp"
#include <thread>
#include <atomic>
#include <random>
#include <iostream>
#include <algorithm>

namespace ixxor {

RndSource::RndSource(int max_ticks, double frequency)
    : max_ticks_(max_ticks), freq_(frequency)
{
    symbols_ = {SymbolID{"IXXORND"}};
    sem_= false;
}

RndSource::RndSource():
    RndSource(0, 1.0) {}

RndSource::~RndSource()
{
    if (sem_) {
        sem_ = false;
        t_->join();
    }
}

bool RndSource::init_source()
{
    // Initialize the worker...
    sem_ = true;
    t_.reset(new std::thread{
            worker, this, std::ref(sem_)
            });
    return true;
}

bool RndSource::subscribe_symbol(SymbolID const& symbol)
{
    auto it = std::find(symbols_.begin(), symbols_.end(), symbol);
    if (it == symbols_.end()) {
        std::cerr << "Symbol not found in subscribe_symbol\n";
        return false;
    }
    return true;
}

std::vector<SymbolID> const&
RndSource::available_symbols() const
{
    return symbols_;
}


void RndSource::worker(RndSource* parent, std::atomic_bool& sem)
{
    std::default_random_engine eng;
    std::exponential_distribution<double> expd(parent->freq_);
    std::uniform_real_distribution<> reald(-1.5,1.5);
    std::uniform_int_distribution<> vold(1, 3);

    Price price{100.0};
    Price quant{0.01};

    Ptime timepoint{2016,1,10,6,0,0};

    int count = 0;
    while(sem.load() && (parent->max_ticks_ && count < parent->max_ticks_)) {
        SymbolID symbol{"IXXORND"};
        auto n_us = static_cast<int>(1e6 * expd(eng));
        int v = vold(eng);
        Tick tick;
        tick.p = price;
        tick.v = Volume{v};
        tick.t = timepoint;
        std::this_thread::sleep_for(std::chrono::microseconds(n_us));
        parent->publish(symbol, tick);
        ++count;
        int dif = round(reald(eng));
        price += dif * quant;
        timepoint += Duration::microseconds(n_us);
    }
}


} // :: ixxor

