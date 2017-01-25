#include "data_source.hpp"
#include <stdexcept>

namespace ixxor {

bool DataSource::is_available(SymbolID const& symbol) const
{
    return symbols_.count(symbol);
}

bool DataSource::subscribe(SymbolID const& symbol)
{
    auto it = symbols_.find(symbol);
    if (it == symbols_.end()) {
        throw std::runtime_error(
            "You should have checked first if we support this symbol, "
            "shouldn't you. We don't provide 'is_available' for fun."
            );
    }
    if (it->second) return false;
    bool succ = subscribe_impl(symbol);
    it->second = succ;
    return succ;
}

} // :: ixxor

