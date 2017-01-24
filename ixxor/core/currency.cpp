#include "currency.hpp"

namespace ixxor {


Currency::Currency():
    ccy_ { { 0,0,0,0} } {}

Currency::Currency(Currency const& other):
    ccy_ { other.ccy_ } {}


Currency& Currency::operator=(Currency const& other)
{
    ccy_ = other.ccy_;
    return *this;
}


bool operator==(Currency const& lhs, Currency const& rhs)
{
    return lhs.ccy_ == rhs.ccy_;
}

bool operator!=(Currency const& lhs, Currency const& rhs)
{
    return lhs.ccy_ != rhs.ccy_;
}

}
