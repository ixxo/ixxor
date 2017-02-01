#include "currency.hpp"

namespace ixxor {

Currency::Currency():
    ccy_ { { '\0', '\0', '\0', '\0'} } {}

Currency::Currency(Currency const& other):
    ccy_ { other.ccy_ } {}

Currency::Currency(Currency&& other):
    ccy_ { std::move(other.ccy_) } {}


Currency& Currency::operator=(Currency const& other)
{
    ccy_ = other.ccy_;
    return *this;
}

Currency& Currency::operator=(Currency&& other)
{
    ccy_ = std::move(other.ccy_);
    return *this;
}


char const* Currency::data() const
{
    return ccy_.data();
}

bool Currency::operator==(Currency const& rhs) const
{
    return ccy_ == rhs.ccy_;
}

bool Currency::operator!=(Currency const& rhs) const
{
    return ccy_ != rhs.ccy_;
}

std::ostream& operator<<(std::ostream& ss, Currency const& ccy)
{
    return ss << ccy.data();
}

} // close ixxor

