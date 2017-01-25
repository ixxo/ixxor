#ifndef INCLUDED_TESTMOD1_MYI2
#define INCLUDED_TESTMOD1_MYI2

#include <ixxor/kernel/indicator.hpp>
#include <iostream>

namespace ixxor {

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

} // :: ixxor

#endif


