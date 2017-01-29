#include "indicator.hpp"

namespace ixxor {

void Indicator::push(SymbolID const& symbol, Tick const& tick)
{
    push_impl(symbol, tick);
}

std::pair<Ptime,double> Indicator::get(SymbolID const& symbol) const
{
    return std::make_pair(
            ts_.load(), sigs_.find(symbol)->second.load()
            );
}

Ptime Indicator::timestamp() const
{
    return ts_.load();
}

} // close ixxor

