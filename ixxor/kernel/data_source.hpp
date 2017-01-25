#ifndef INCLUDED_KERNEL_DATA_SOURCE
#define INCLUDED_KERNEL_DATA_SOURCE
#include <ixxor/core/symbol.hpp>
#include <unordered_map>
#include <vector>

namespace ixxor {

class DataSource
{
    bool is_available(SymbolID const& symbol) const;
    bool subscribe(SymbolID const& symbol);

private:
    virtual bool init() = 0;
    virtual bool subscribe_impl(SymbolID const& symbol) const = 0;
    virtual std::vector<SymbolID> const& available_symbols() = 0;
private:
    std::unordered_map<SymbolID, bool> symbols_;
};

} // close ixxor

#endif

