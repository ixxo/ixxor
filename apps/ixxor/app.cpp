#include "app.hpp"
#include <chrono>
#include <iostream>

namespace ixxor {


App::App(volatile std::sig_atomic_t& sig):
    sig_(sig),
    t_(new std::thread(&worker, this))
{
}

App::~App()
{
    if (t_) {
        t_->join();
    }
}

void App::worker(App* parent)
{
    while(!parent->sig_) {
        std::cout << "worker is working in " << parent << "...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


} // :: ixxor

