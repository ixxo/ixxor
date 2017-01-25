#ifndef INCLUDED_IXXOR_INDICATOR
#define INCLUDED_IXXOR_INDICATOR

#include <ixxor/core/tick.hpp>
#include <ixxor/core/symbol.hpp>

namespace ixxor {

// A base class..
class Indicator
{
public:
    Indicator() {}
    virtual ~Indicator() {}

    void push(SymbolID const& symbol, Tick const& tick);
private:
    virtual void push_impl(SymbolID const& symbol, Tick const& tick) = 0;
};

} // close ixxor

#endif

