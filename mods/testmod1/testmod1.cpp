#include <iostream>

extern "C" __attribute__((visibility ("default")))
void ixxo_init(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Initialization called....\n";

}

extern "C" __attribute__((visibility ("default")))
void ixxo_cleanup(char const* name, void* kernel)
{
    std::cout << "Plugin " << name << " Clean up called....\n";
}
