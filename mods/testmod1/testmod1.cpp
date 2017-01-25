#include <ixxor/kernel/module_util.hpp>
#include <ixxor/kernel/indicator.hpp>
#include <iostream>

namespace {

char const* module_name = "testmod1";

}

namespace ixxor {

class MyI1: public Indicator
{
    int period_;
public:
    explicit MyI1(int period)
        : period_(period)
    {
        std::cout << "MyI1 created, period=" << period << ".\n";
    }
    ~MyI1()
    {
        std::cout << "MyI1 destroyed.\n";
    }

private:
    void push_impl(SymbolID const& symbol, Tick const& tick) override
    {
        // do nothing for now.
    }

};

class MyI2: public Indicator
{
    int period_;
    double factor_;
public:
    explicit MyI2(int period, double factor):
        period_(period),
        factor_(factor)

    {
        std::cout << "MyI2 created, period=" << period << ", factor=" <<
                     factor<< ".\n";
    }
    ~MyI2()
    {
        std::cout << "MyI2 destroyed.\n";
    
    }
private:
    void push_impl(SymbolID const& symbol, Tick const& tick) override
    {
        // do nothing for now.
    }
};

}

extern "C" __attribute__((visibility ("default")))
void ixxo_init(char const* name, void* kernel)
{
    using namespace ixxor::module_util;
    std::cout << "Plugin " << name << " Initialization called....\n";
    register_indicator<ixxor::MyI1, int>("MyI1",
            kernel, module_name);

    register_indicator<ixxor::MyI2, int, double>("MyI2",
            kernel, module_name);
}

extern "C" __attribute__((visibility ("default")))
void ixxo_cleanup(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Clean up called....\n";
}
