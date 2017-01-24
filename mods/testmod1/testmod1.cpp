#include <ixxor/kernel/module_util.hpp>
#include <ixxor/kernel/indicator.hpp>
#include <iostream>

namespace {

char const* module_name = "testmod1";

}

namespace ixxor {

class MyIndicator: public Indicator
{
    int period_;
public:
    explicit MyIndicator(int period)
        : period_(period)
    {
        std::cout << "MyIndicator created, period=" << period << ".\n";
    }
    MyIndicator(MyIndicator&&) = default;
    MyIndicator(MyIndicator const&) = default;
    MyIndicator& operator=(MyIndicator&&) = default;
    MyIndicator& operator=(MyIndicator const&) = default;
    ~MyIndicator()
    {
        std::cout << "MyIndicator destroyed.\n";
    
    }

    void init(int const& period) { period_ = period; }
};

}

extern "C" __attribute__((visibility ("default")))
void ixxo_init(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Initialization called....\n";
    ixxor::module_util::register_indicator<ixxor::MyIndicator, int>(
            kernel, "MyI1", module_name);

}

extern "C" __attribute__((visibility ("default")))
void ixxo_cleanup(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Clean up called....\n";
}
