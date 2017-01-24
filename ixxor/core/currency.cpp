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

char const* Currency::data() const
{
    return ccy_.data();
}

bool operator==(Currency const& lhs, Currency const& rhs)
{
    return lhs.ccy_ == rhs.ccy_;
}

bool operator!=(Currency const& lhs, Currency const& rhs)
{
    return lhs.ccy_ != rhs.ccy_;
}

std::ostream& operator<<(std::ostream& ss, Currency const& ccy)
{
    return ss << ccy.data();
}

}
