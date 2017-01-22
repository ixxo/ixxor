#include <iostream>
#include <ixxor/kernel/module_util.hpp>
#include <ixxor/kernel/indicator.hpp>

namespace {


char const* module_name = "testmod1";

}

namespace ixxor {

class MyIndicator: public Indicator
{
    int period_;
public:
    explicit MyIndicator() {}//nt period) {}
    MyIndicator(MyIndicator&&) = default;
    MyIndicator(MyIndicator const&) = default;
    MyIndicator& operator=(MyIndicator&&) = default;
    MyIndicator& operator=(MyIndicator const&) = default;
    ~MyIndicator() {}
};

}

extern "C" __attribute__((visibility ("default")))
void ixxo_init(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Initialization called....\n";
    ixxor::module_util::register_indicator<ixxor::MyIndicator>(
            kernel, "MyI1", module_name);

}

extern "C" __attribute__((visibility ("default")))
void ixxo_cleanup(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Clean up called....\n";
}
