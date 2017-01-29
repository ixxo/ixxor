#ifndef INCLUDED_KERNEL_DATA_SOURCE
#define INCLUDED_KERNEL_DATA_SOURCE
#include <ixxor/core/symbol.hpp>
#include <ixxor/core/tick.hpp>
#include <unordered_map>
#include <functional>
#include <vector>

namespace ixxor {

class DataSource
{
public:
    DataSource() = default;
    virtual ~DataSource() = default;
    using callback_type = std::function<void(SymbolID const&, Tick const&)>;
    bool is_available(SymbolID const& symbol) const;
    bool subscribe(SymbolID const& symbol, callback_type callback);

    void init();

protected:
    void publish(SymbolID const& symbol, Tick const& tick);
private:
    virtual bool init_source() = 0;
    virtual bool subscribe_symbol(SymbolID const& symbol) = 0;
    virtual std::vector<SymbolID> const& available_symbols() const = 0;
private:
    std::unordered_map<SymbolID, callback_type> symbols_;
};

} // :: ixxor

#endif

