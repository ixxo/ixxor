#include "rnd_source.hpp"
#include <thread>
#include <atomic>
#include <random>

namespace ixxor {

struct RndSource::Impl
{
    std::atomic_bool sem_;
    std::unique_ptr<std::thread> t_;
    static void worker(RndSource*, std::atomic_bool&);
};


RndSource::RndSource()
{
    impl_.reset(new Impl);
    impl_->sem_ = false;
}
RndSource::~RndSource()
{
    if (impl_->sem_ && impl_->t_) {
        impl_->sem_ = false;
        impl_->t_->join();
    }
}

bool RndSource::init_source()
{
    // Initialize the worker...
    impl_->sem_ = true;
    impl_->t_.reset(new std::thread(Impl::worker, this, std::ref(impl_->sem_)));
    return true;
}

bool RndSource::subscribe_symbol(SymbolID const& symbol)
{
    return false;
}

std::vector<SymbolID> const&
RndSource::available_symbols() const
{
    return symbols_;
}


void RndSource::Impl::worker(RndSource* parent, std::atomic_bool& sem)
{
    std::default_random_engine eng;
    std::uniform_int_distribution<> intd(1,1000);
    std::uniform_real_distribution<> reald(-1.2,1.2);
    std::uniform_int_distribution<> vold(1, 3);

    Price price{100.0};
    Price quant{0.01};

    Datetime timepoint;//(2017, 1, 13, 6, 0, 0);

    while(sem.load()) {
        SymbolID symbol{"IXXORND"};
        auto n_ms = intd(eng);
        int v = vold(eng);
        Tick tick;
        tick.p = price;
        tick.v = Volume{v};
        tick.t = timepoint;
        // well yeah we don't handle dates very well yet...
        std::this_thread::sleep_for(std::chrono::milliseconds(n_ms));
        parent->publish(symbol, tick);
        int dif = round(reald(eng));
        price += dif * quant;
    }
}


} // :: ixxor

