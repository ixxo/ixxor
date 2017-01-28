#ifndef INCLUDED_CORE_FUTURE
#define INCLUDED_CORE_FUTURE
#include "instrument.hpp"
#include "volume.hpp"
#include "ptime.hpp"
#include "symbol.hpp"

namespace ixxor {

class Futures
{
public:
    Instrument instrument_;
    Volume lotsize_;
    Ptime expiry_;
    SymbolID symbol_;
};

} // close ixxor

#endif

