#ifndef INCLUDED_CORE_TICK
#define INCLUDED_CORE_TICK
#include "ptime.hpp"
#include "volume.hpp"
#include "price.hpp"

namespace ixxor {

struct Tick
{
    Ptime t;
    Price p;
    Volume v;
};

} // : ixxor

#endif

