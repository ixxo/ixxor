#include <ixxor/kernel/kernel.hpp>
#include <ixxor/kernel/indicator.hpp>

// this is still very manual.. just check the output if you get the right
// period in the constructed indicator...

using namespace ixxor;

int main()
{
    Kernel kernel;
    kernel.load("mods/testmod1/libtestmod1.so");

    auto MyI1 = kernel.get<Indicator>("MyI1", 123);
    auto MyI2 = kernel.get<Indicator>("MyI2", 123, 34.51);

    // Let's initialize the source then...
    
    MyI1.reset();
    MyI2.reset();


    return 0;
}

