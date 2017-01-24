#ifndef INCLUDED_CORE_CURRENCY
#define INCLUDED_CORE_CURRENCY
#include <string>
#include <array>

namespace ixxor {
class Currency;

bool operator==(Currency const& lhs, Currency const& rhs);
bool operator!=(Currency const& lhs, Currency const& rhs);

class Currency
{
    using impl_type = std::array<char, 4>;
    impl_type ccy_;
public:
    Currency(std::string const&);
    Currency();
    Currency(Currency const& other);
    Currency& operator=(Currency const&);
private:
    friend bool operator==(Currency const& lhs, Currency const& rhs);
    friend bool operator!=(Currency const& lhs, Currency const& rhs);
};


}

#endif
