#ifndef INCLUDED_CORE_DATETIME
#define INCLUDED_CORE_DATETIME

#include <cstddef>

namespace ixxor {

// will be replaced with boost::ptime probably...
struct Datetime
{
    std::size_t ts;
};

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

}

#endif

