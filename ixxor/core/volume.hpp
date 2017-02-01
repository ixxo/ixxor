#ifndef INCLUDED_CORE_VOLUME
#define INCLUDED_CORE_VOLUME

#include <type_traits>

namespace ixxor {

struct Volume
{
    int v_;
    
    explicit operator int() const
    {
        return v_;
    }
    
    template<typename T,
        typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
    Volume& operator*=(T const& factor)
    {
        v_ *= factor;
        return *this;
    }
};

template<typename T>
typename std::enable_if<std::is_integral<T>::value, Volume>::type
operator*=(Volume const& v, T const& fac)
{
    return Volume(v) *= fac;
}

} // :: ixxor

namespace std {

template<>
struct is_integral<ixxor::Volume>: public std::true_type {};
} // :: std

#endif

