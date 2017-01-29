#ifndef INCLUDED_TESTMOD1_RND_SOURCE
#define INCLUDED_TESTMOD1_RND_SOURCE
#include <ixxor/kernel/data_source.hpp>
#include <memory>
#include <vector>
#include <atomic>
#include <thread>

namespace ixxor {

class RndSource: public DataSource
{
public:
    explicit RndSource(int max_ticks);
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
    int const max_ticks_;
    std::vector<SymbolID> symbols_;
    std::atomic_bool sem_;
    static void worker(RndSource*, std::atomic_bool&);
    std::unique_ptr<std::thread> t_;
};

} // :: ixxor

#endif

