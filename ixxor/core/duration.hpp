#ifndef INCLUDED_CORE_DURATION
#define INCLUDED_CORE_DURATION

#include <cstdint>
#include <type_traits>

namespace ixxor {

struct Duration
{
    std::int64_t ts;
public:

    Duration() = default;
    Duration(Duration const&) = default;
    Duration(Duration&&) = default;
    Duration& operator=(Duration const&) = default;
    Duration& operator=(Duration&&) = default;


    template<class T, typename = 
        typename std::enable_if<std::is_integral<T>::value>::type>
    explicit Duration(T const& count):
        ts(static_cast<std::int64_t>(count)) {}

    static Duration hours(int count);
    static Duration minutes(int count);
    static Duration seconds(int count);
    static Duration milliseconds(int count);
    static Duration microseconds(int count);

    Duration& operator+=(Duration const& z)
    {
        ts += z.ts;
        return *this;
    }
    Duration& operator-=(Duration const& z)
    {
        ts -= z.ts;
        return *this;
    }

    template<class T>
    typename std::enable_if<std::is_integral<T>::value, Duration&>::type
    operator*=(T factor)
    {
        ts *= factor;
        return *this;
    }

    bool operator==(Duration const& other) const
    {
        return ts == other.ts;
    }
    bool operator!=(Duration const& other) const
    {
        return ts != other.ts;
    }

    bool operator<(Duration const& other) const
    {
        return ts < other.ts;
    }
};


inline
Duration operator+(Duration const& d1, Duration const& d2)
{
    Duration s(d1);
    return s += d2;
}

inline
Duration operator-(Duration const& d1, Duration const& d2)
{
    Duration s(d1);
    return s -= d2;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, Duration>::type
operator*(Duration const& x, T factor)
{
    Duration z{x};
    return z *= factor;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, Duration>::type
operator*(T factor, Duration const& x)
{
    Duration z{x};
    return z *= factor;
}


inline 
Duration Duration::hours(int count)
{
    return count * Duration::seconds(3600);
}

inline
Duration Duration::minutes(int count)
{
    return count * Duration::seconds(60);
}

inline
Duration Duration::seconds(int count)
{
    return count * Duration::microseconds(1000000);
}

inline
Duration Duration::milliseconds(int count)
{
    return count * Duration::microseconds(1000);
}

inline
Duration Duration::microseconds(int count)
{
    return Duration{count};
}

} // close ixxor

#endif

