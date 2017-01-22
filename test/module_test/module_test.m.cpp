#include <ixxor/kernel/kernel.hpp>

using namespace ixxor;

int main()
{
    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    return 0;
}

