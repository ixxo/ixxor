#ifndef INCLUDED_CORE_INSTRUMENT
#define INCLUDED_CORE_INSTRUMENT
#include "currency.hpp"
#include "exchange.hpp"
#include "price.hpp"
#include <array>

namespace ixxor {

struct InstrumentID
{
    std::array<char, 16> id_;
};

class Instrument
{
public:
    Instrument();
    ~Instrument();
public:
    InstrumentID id_;
    ExchangeID exchange_;
    Currency ccy_;
    Price ticksize_;
};

}

#endif

