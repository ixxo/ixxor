#ifndef INCLUDED_IXXOR_CORE_DATE
#define INCLUDED_IXXOR_CORE_DATE

#include <cassert>
#include <cstdint>
#include <numeric>

namespace ixxor {

class Date
{
private:
    std::int32_t d_;

public:
    Date(): d_(-1) {}

    Date(Date const&) = default;
    Date(Date&&) = default;
    Date& operator=(Date const&) = default;
    Date& operator=(Date&&) = default;

    explicit Date(int y, int m, int d);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, Date&>::type
    operator+=(T days)
    {
        d_ += days;
        return *this;
    }
    
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, Date&>::type
    operator-=(T days)
    {
        d_ -= days;
        return *this;
    }

    bool operator==(Date const& other) const
    {
        return d_ == other.d_;
    }
    bool operator!=(Date const& other) const
    {
        return d_ != other.d_;
    }

    
    std::int32_t days_since_epoch() const
    {
        return d_;
    }

};

inline
bool is_leap_year(int y)
{
    return y % 4 == 0 && !( y%100 == 0 && !(y%400 == 0));
}

inline
Date::Date(int y, int m, int d)
{
    int days = (y - 1970) * 365 + (y-1972)/4; // from 1901 to 2099...
    assert(m>=1 && m<=12);
    static int const days_m[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    days += std::accumulate(std::begin(days_m), std::begin(days_m)+(m-1), 0);
    if (m >= 3 && is_leap_year(y)) ++days; // 29th feb...
    assert( (d >= 1 && d <= days_m[m-1]) ||
            (m == 2 && d==29 && is_leap_year(y)));
    days += (d-1);
    d_ = static_cast<std::int32_t>(days);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, Date>::type
operator+(Date const& d, T days)
{
    Date dx(d);
    dx += days;
    return dx;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, Date>::type
operator-(Date const& d, T days)
{
    Date dx(d);
    dx -= days;
    return dx;
}


} // :: ixxor

#endif

