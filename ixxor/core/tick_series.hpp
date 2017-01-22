#ifndef INCLUDED_CORE_TICK_SERIES
#define INCLUDED_CORE_TICK_SERIES
#include "ptime.hpp"
#include "tick.hpp"
#include "time_series.hpp"

namespace ixxor {

using TickSeries = TimeSeries<Tick, Ptime>;

}

#endif
