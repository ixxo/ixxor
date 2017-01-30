#include "app.hpp"
#include <chrono>
#include <iostream>
#include <ixxor/kernel/kernel.hpp>

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
    Kernel kernel;

    // Read the database and initialize kernel. Probably MongoDB.
    
    while(!parent->sig_) {
        // Maybe wait for requests from ZeroMQ/RabbitMQ.... and pass a request
        // to the kernel
        std::cout << "worker is working in " << parent << "...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


} // :: ixxor

