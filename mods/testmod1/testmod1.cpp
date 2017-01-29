#include "my_i1.hpp"
#include "my_i2.hpp"
#include "rnd_source.hpp"

#include <ixxor/kernel/module_util.hpp>
#include <iostream>

namespace {
char const* ixxo_module_name = "testmod1";
}

extern "C" __attribute__((visibility ("default")))
void ixxo_init(char const* name, ixxor::Kernel* kernel)
{
    using namespace ixxor::module_util;
    std::cout << "Plugin " << name << " Initialization called....\n";
    register_indicator<ixxor::MyI1, int>("MyI1",
            kernel, ixxo_module_name);

    register_indicator<ixxor::MyI2, int, double>("MyI2",
            kernel, ixxo_module_name);

    // This is a temp restriction... needs to have at least one argument for now
    register_data_source<ixxor::RndSource, int>("FoobarSource",
            kernel, ixxo_module_name);

}

extern "C" __attribute__((visibility ("default")))
void ixxo_cleanup(char const* name, ixxor::Kernel* kernel)
{
    std::cout << "Plugin " << name << " Clean up called....\n";
}
