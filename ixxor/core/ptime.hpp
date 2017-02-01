#ifndef INCLUDED_CORE_PTIME
#define INCLUDED_CORE_PTIME
#include "duration.hpp"
#include "date.hpp"

#include <cstddef>

// I don't like boost::date_time. Period. This will do until I find
// something decent.

namespace ixxor {

class Ptime
{
    Duration ts;
public:

    Ptime() = default;
    Ptime(Ptime const&) = default;
    Ptime& operator=(Ptime const&) = default;

    Ptime(Date const& date, Duration const& tod):
        Ptime{Duration::hours(date.days_since_epoch() * 24) + tod} {}

    Ptime(int y, int m, int d, int H, int M, int S=0, int uS=0):
        Ptime{Date{y,m,d}, Duration::from_HMSu(H, M, S, uS)} {}

private:

    Ptime(Duration const& dur): ts{dur} {}

public:

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
    Ptime p(ts);
    return p += d;
}

inline
Ptime operator-(Ptime const& ts, Duration const& d)
{
    Ptime p(ts);
    return p -= d;
}

inline
Duration operator-(Ptime const& ts1, Ptime const& ts2)
{
    return ts1.from_epoch() - ts2.from_epoch();
}

inline
bool operator==(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.from_epoch() == rhs.from_epoch();
}

inline
bool operator<(Ptime const& lhs, Ptime const& rhs)
{
    return lhs.from_epoch() < rhs.from_epoch();
}


inline
bool operator!=(Ptime const& lhs, Ptime const& rhs)
{
    return !(lhs == rhs);
}


inline
bool operator>(Ptime const& lhs, Ptime const& rhs)
{
    return rhs < lhs;
}

inline
bool operator<=(Ptime const& lhs, Ptime const& rhs)
{
    return !(lhs > rhs);
}

inline
bool operator>=(Ptime const& lhs, Ptime const& rhs)
{
    return rhs <= lhs;
}






} // close ixxor

#endif

