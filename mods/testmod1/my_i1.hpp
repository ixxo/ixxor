#ifndef INCLUDED_TESTMOD1_MYI1
#define INCLUDED_TESTMOD1_MYI1

#include <ixxor/kernel/indicator.hpp>
#include <iostream>

namespace ixxor {

class MyI1: public Indicator
{
    int period_;
public:
    explicit MyI1(int period)
        : period_(period)
    {
        std::cout << "MyI1 created, period=" << period_ << ".\n";
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

} // :: ixxor

#endif

