#ifndef INCLUDED_CORE_DURATION
#define INCLUDED_CORE_DURATION

#include <cstdint>

namespace ixxor {

struct Duration
{
    std::int64_t ts;

    Duration& operator+=(Duration const&);
    Duration& operator-=(Duration const&);
};

inline
Duration& Duration::operator+=(Duration const& z)
{
    ts += z.ts;
    return *this;
}

inline
Duration& Duration::operator-=(Duration const& z)
{
    ts -= z.ts;
    return *this;
}

inline
Duration operator+(Duration const& d1, Duration const& d2)
{
    return Duration { d1.ts + d2.ts };
}

inline
Duration operator-(Duration const& d1, Duration const& d2)
{
    return Duration { d1.ts - d2.ts };
}

inline
bool operator==(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts == rhs.ts;
}

inline
bool operator!=(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts != rhs.ts;
}

inline
bool operator<(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts < rhs.ts;
}

inline
bool operator<=(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts <= rhs.ts;
}

inline
bool operator>=(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts >= rhs.ts;
}

inline
bool operator>(Duration const& lhs, Duration const& rhs)
{
    return lhs.ts > rhs.ts;
}


} // close ixxor

#endif

