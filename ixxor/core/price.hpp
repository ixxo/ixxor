#ifndef INCLUDED_CORE_PRICE
#define INCLUDED_CORE_PRICE
#include <type_traits>
#include <ostream>

namespace ixxor {

struct Price
{
    double p_; // This should be fixed precision but will do for now.

    Price() = default;
    Price(Price const&) = default;

    explicit Price(double p): p_(p) {}

    Price& operator=(Price const&) = default;

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, Price&>::type
    operator*=(T factor)
    {
        p_ *= factor;
        return *this;
    }

    Price& operator+=(Price const& add)
    {
        p_ += add.p_;
        return *this;
    }
};


template<typename T>
Price operator*(Price const& x, T z)
{
    Price w{x};
    w *= z;
    return w;
}

template<typename T>
Price operator*(T z, Price const& x)
{
    return x * z;
}


} // close ixxor

namespace std {

inline
std::ostream& operator<<(std::ostream& ss, ixxor::Price const& p)
{
    return ss << p.p_;
}

}

#endif


