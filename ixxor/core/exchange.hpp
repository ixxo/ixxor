#ifndef INCLUDED_CORE_EXCHANGE
#define INCLUDED_CORE_EXCHANGE
#include <array>
#include <string>

namespace ixxor {

class ExchangeID
{
    std::array<char, 8> id_;
public:
    ExchangeID();
    ExchangeID(std::string const& id);
};

class Exchange
{
public:
    ExchangeID id_;
};

}

#endif

