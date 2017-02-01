#ifndef INCLUDED_CORE_CURRENCY
#define INCLUDED_CORE_CURRENCY
#include <string>
#include <array>
#include <ostream>

namespace ixxor {

class Currency
{
    using impl_type = std::array<char, 4>;
    impl_type ccy_;
public:
    Currency(std::string const&);
    Currency();
    Currency(Currency const& other);
    Currency(Currency&& other);
    Currency& operator=(Currency const&);
    Currency& operator=(Currency&&);

    char const* data() const;
    
    bool operator==(Currency const& other) const;
    bool operator!=(Currency const& other) const;
};

std::ostream& operator<<(std::ostream&, Currency const&);

} // close ixxor

#endif
