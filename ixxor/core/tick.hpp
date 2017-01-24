#ifndef INCLUDED_CORE_TICK
#define INCLUDED_CORE_TICK
#include "datetime.hpp"
#include "volume.hpp"
#include "price.hpp"
#include "side.hpp"

namespace ixxor {

struct Tick
{
    Datetime t;
    Price p;
    Volume v;
    Side s;
};

}

#endif
