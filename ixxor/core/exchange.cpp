#include "exchange.hpp"
#include <algorithm>

namespace ixxor {

ExchangeID::ExchangeID()
{
    id_.fill('\0');
}

ExchangeID::ExchangeID(std::string const& id):
    ExchangeID()
{
    std::copy(id.begin(), std::min(id.begin() + id_.size(), id.end()),
              id_.begin());
}

} // close ixxor

