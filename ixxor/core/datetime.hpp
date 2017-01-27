#ifndef INCLUDED_CORE_DATETIME
#define INCLUDED_CORE_DATETIME
#include "duration.hpp"

#include <cstddef>

namespace ixxor {

// will be replaced with boost::ptime probably...
class Datetime
{
public:
    Duration ts;

    Datetime() = default;
    Datetime(Datetime const&) = default;
    Datetime& operator=(Datetime const&) = default;
    //Datetime(int y, int m, int d, int H, int M, int S=0, int us=0);

    Duration const& from_epoch() const;
    Datetime& operator+=(Duration const&);
    Datetime& operator-=(Duration const&);
};

inline
Duration const& Datetime::from_epoch() const
{
    return ts;
}

inline
Datetime& Datetime::operator+=(Duration const& d)
{
    ts += d;
    return *this;
}

inline
Datetime& Datetime::operator-=(Duration const& d)
{
    ts -= d;
    return *this;
}

inline
Datetime operator+(Datetime const& ts, Duration const& d)
{
    return Datetime{ ts.ts + d };
}

inline
Datetime operator-(Datetime const& ts, Duration const& d)
{
    return Datetime{ ts.ts - d };
}


inline
Duration operator-(Datetime const& ts1, Datetime const& ts2)
{
    return ts1.ts - ts2.ts;
}

inline
bool operator<(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts < rhs.ts;
}

inline
bool operator==(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts == rhs.ts;
}

inline
bool operator<=(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts <= rhs.ts;
}

inline
bool operator>=(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts >= rhs.ts;
}

inline
bool operator>(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts > rhs.ts;
}

inline
bool operator!=(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.ts != rhs.ts;
}

} // close ixxor

#endif

