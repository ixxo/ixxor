#ifndef INCLUDED_KERNEL_DATA_SOURCE
#define INCLUDED_KERNEL_DATA_SOURCE
#include <ixxor/core/symbol.hpp>
#include <ixxor/core/tick.hpp>
#include <unordered_map>
#include <vector>

namespace ixxor {

class DataSource
{
public:
    using callback_type = void(*)(SymbolID const&, Tick const&);
    bool is_available(SymbolID const& symbol) const;
    bool subscribe(SymbolID const& symbol, callback_type callback);

protected:
    void publish(SymbolID const& symbol, Tick const& tick);
private:
    virtual bool init_impl() = 0;
    virtual bool subscribe_impl(SymbolID const& symbol) const = 0;
    virtual std::vector<SymbolID> const& available_symbols() = 0;
private:
    std::unordered_map<SymbolID, callback_type> symbols_;
};

} // :: ixxor

#endif

