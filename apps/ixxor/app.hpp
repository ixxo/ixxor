#ifndef INCLUDED_APPS_IXXOR_APP
#define INCLUDED_APPS_IXXOR_APP
#include <atomic>
#include <thread>
#include <csignal>

namespace ixxor {

class App
{
public:
    App(volatile std::sig_atomic_t& sig);
    ~App();

private:
    volatile std::sig_atomic_t& sig_;
    std::unique_ptr<std::thread> t_;
    static void worker(App* parent);
};

} // :: ixxor

#endif
