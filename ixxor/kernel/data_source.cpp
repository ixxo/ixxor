#include "data_source.hpp"
#include <stdexcept>
#include <iostream>

namespace ixxor {

void DataSource::init()
{
    init_source();
}

bool DataSource::is_available(SymbolID const& symbol) const
{
    return symbols_.count(symbol);
}

bool DataSource::subscribe(SymbolID const& symbol, callback_type callback)
{
    auto rv = symbols_.emplace(symbol, callback);
    if (!rv.second) {
        std::cerr << "It is subscribed already\n";
        // It's subscribed already
        return false;
    }
    auto it = rv.first;
    if (!subscribe_symbol(symbol)) {
        std::cerr << "Could not subscribe symbol...\n";
        // Invalid.
        symbols_.erase(it);
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
    auto callback = it->second;
    if (callback) {
        callback(symbol, tick);
    }
}

} // :: ixxor

