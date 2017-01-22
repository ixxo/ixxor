#ifndef INCLUDED_CORE_TIME_SERIES
#define INCLUDED_CORE_TIME_SERIES
#include "ptime.hpp"
#include <vector>
#include <algorithm>

namespace ixxor {

template<class VT, class TS=Ptime>
class TimeSeries
{
    using impl_type = std::vector<std::pair<TS, VT> >;
public:
    using iterator = typename impl_type::iterator;
    using const_iterator = typename impl_type::const_iterator;
    using size_type = typename impl_type::size_type;
    using key_type = TS;
    using mapped_type = VT;
    using value_type = typename impl_type::value_type;

    TimeSeries() = default;
    TimeSeries(TimeSeries const&) = default;
    TimeSeries(TimeSeries&&) = default;
    TimeSeries& operator=(TimeSeries const&) = default;
    TimeSeries& operator=(TimeSeries&&) = default;
    ~TimeSeries() = default;

    size_type size() const;
    iterator insert(value_type const& val);

    template<class... Args>
    iterator emplace(Args&&... args);


private:
    impl_type v_;
};

}

//
// Implementation
//

namespace ixxor {

template<class VT, class TS>
typename TimeSeries<VT,TS>::size_type
TimeSeries<VT,TS>::size() const
{
    return v_.size();
}


template<class VT, class TS>
template<class... Args>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::emplace(Args&&... args)
{
    value_type value { std::forward<Args>(args)... };
    v_.reserve(v_.size() + 1);
    auto it = std::upper_bound(v_.begin(), v_.end(), value.first,
            [](TS const& k, value_type const& v) { return k < v.first; }
            );
    if (it == v_.end()) {
        v_.emplace_back(std::move(value));
    } else {
        v_.resize(v_.size() + 1);
        for(auto zit = v_.begin() + v_.size() - 1; zit > it; --zit) {
            *zit = std::move(*(zit - 1));
        }
        *it = std::move(value);
    }
    return it;
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::insert(value_type const& value)
{
    return emplace(value_type{value});
}

} // close ixxor

#endif

