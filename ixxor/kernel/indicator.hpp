#ifndef INCLUDED_IXXOR_CORE_INDICATOR
#define INCLUDED_IXXOR_CORE_INDICATOR

#include <ixxor/core/tick.hpp>
#include <ixxor/core/symbol.hpp>
#include <atomic>
#include <unordered_map>

namespace ixxor {

// A base class..
// This one cares about the symbols...
class Indicator
{
public:

    Indicator() {}
    virtual ~Indicator() {}

    void push(SymbolID const& symbol, Tick const& tick);

    std::pair<Ptime,double> get(SymbolID const&) const;
    Ptime timestamp() const;

protected:

    template<class Iter>
    void initialize(Iter first, Iter last);

    template<class Iter>
    void update(Ptime const& ts, Iter first, Iter last);

private:

    virtual void push_impl(SymbolID const& symbol, Tick const& tick) = 0;

    std::atomic<Ptime> ts_;
    std::unordered_map<SymbolID, std::atomic<double> > sigs_;
};

template<class Iter>
void Indicator::update(Ptime const& ts, Iter first, Iter last)
{
    // we should probably lock it for a bit until we get out of here
    for(auto it = first; it != last; ++it) {
        sigs_.find(it->first)->second = it->second;
    }
    ts_ = ts;
}


} // close ixxor

#endif

