#include <ixxor/kernel/kernel.hpp>

// this is still very manual.. just check the output if you get the right
// period in the constructed indicator...

using namespace ixxor;

int main()
{
    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    auto MyI = kernel.indicator("MyI1", 123);
    MyI.reset();

    return 0;
}

