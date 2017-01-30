#include "app.hpp"
#include <csignal>

namespace {

volatile std::sig_atomic_t g_signal_status;

void signal_handler(int signal)
{
    g_signal_status = signal;
}

} // : <anonymous>

int main(int argc, char** argv)
{
    std::signal(SIGINT, signal_handler);
    ixxor::App app(g_signal_status);
    return 0;    
}
