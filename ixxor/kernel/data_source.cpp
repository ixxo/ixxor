#include "data_source.hpp"
#include <stdexcept>

namespace ixxor {

bool DataSource::is_available(SymbolID const& symbol) const
{
    return symbols_.count(symbol);
}

bool DataSource::subscribe(SymbolID const& symbol, callback_type callback)
{
    auto it = symbols_.find(symbol);
    if (it == symbols_.end()) {
        throw std::runtime_error(
            "You should have checked first if we support this symbol, "
            "shouldn't you. We don't provide 'is_available' for fun."
            );
    }
    if (it->second) return false;
    it->second = callback;
    if (!subscribe_symbol(symbol)) {
        it->second = nullptr;
        return false;
    }
    return true;
}

void DataSource::publish(SymbolID const& symbol, Tick const& tick)
{
    auto it = symbols_.find(symbol);
    if (it == symbols_.end() || !it->second) {
        throw std::runtime_error(
                "Weird. Ticks for an unsupported/unregistered symbol??");
    }
    // Dispach the parent.
    it->second(symbol, tick);
}

} // :: ixxor

