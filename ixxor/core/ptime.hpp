#ifndef INCLUDED_CORE_PTIME
#define INCLUDED_CORE_PTIME
#include "duration.hpp"

#include <cstddef>

namespace ixxor {

class Ptime
{
public:
    Duration ts;

    Ptime() = default;
    Ptime(Ptime const&) = default;
    Ptime& operator=(Ptime const&) = default;
    //Ptime(int y, int m, int d, int H, int M, int S=0, int us=0);

    Duration const& from_epoch() const;
    Ptime& operator+=(Duration const&);
    Ptime& operator-=(Duration const&);
};

inline
Duration const& Ptime::from_epoch() const
{
    return ts;
}

inline
Ptime& Ptime::operator+=(Duration const& d)
{
    ts += d;
    return *this;
}

inline
Ptime& Ptime::operator-=(Duration const& d)
{
    ts -= d;
    return *this;
}

inline
Ptime operator+(Ptime const& ts, Duration const& d)
{
    return Ptime{ ts.ts + d };
}

inline
Ptime operator-(Ptime const& ts, Duration const& d)
{
    return Ptime{ ts.ts - d };
}


inline
Duration operator-(Ptime const& ts1, Ptime const& ts2)
{
    return ts1.ts - ts2.ts;
}

inline
bool operator<(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts < rhs.ts;
}

inline
bool operator==(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts == rhs.ts;
}

inline
bool operator<=(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts <= rhs.ts;
}

inline
bool operator>=(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts >= rhs.ts;
}

inline
bool operator>(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts > rhs.ts;
}

inline
bool operator!=(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.ts != rhs.ts;
}

} // close ixxor

#endif

