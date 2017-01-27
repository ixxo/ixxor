#ifndef INCLUDED_TESTMOD1_RND_SOURCE
#define INCLUDED_TESTMOD1_RND_SOURCE
#include <ixxor/kernel/data_source.hpp>
#include <memory>
#include <vector>

namespace ixxor {

class RndSource: public DataSource
{
public:
    RndSource();
    ~RndSource();
    RndSource(RndSource const&) = delete;
    RndSource(RndSource&&) = delete;
    RndSource& operator=(RndSource const&) = delete;
    RndSource& operator=(RndSource&&) = delete;

private:
    bool init_source() override;
    bool subscribe_symbol(SymbolID const& symbol) override;
    std::vector<SymbolID> const& available_symbols() const override;

private:
    std::vector<SymbolID> symbols_;
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // :: ixxor

#endif

