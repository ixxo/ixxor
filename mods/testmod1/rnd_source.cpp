#include "rnd_source.hpp"
#include <thread>
#include <atomic>

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
    // Start doing some shit.
    while(sem.load()) {
        SymbolID symbol{"IXXORND"};
        Tick tick;
        parent->publish(symbol, tick);
        // publish some tick...
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


} // :: ixxor

