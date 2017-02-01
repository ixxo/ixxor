#ifndef INCLUDED_CORE_TIME_SERIES
#define INCLUDED_CORE_TIME_SERIES
//!
//! \file core/time_series.hpp
//! \brief Implementation of a time-series container
//! \details The time-series container is a vector-like container optimized
//! for frequent additions and truncation of old values.
//! \author ixxo
//!
#include <vector>
#include <algorithm>
#include <cassert>
#include <initializer_list>

namespace ixxor {

//!
//! \class TimeSeries
//! \tparam VT Value type
//! \tparam TS Timestamp time (default ixxor::Ptime)
//! \brief Time series type
//!
template<class VT, class TS>
class TimeSeries
{
    using impl_type = std::vector<std::pair<TS, VT> >;
public:
    using iterator = typename impl_type::iterator;
    using const_iterator = typename impl_type::const_iterator;
    using reverse_iterator = typename impl_type::reverse_iterator;
    using const_reverse_iterator = typename impl_type::const_reverse_iterator;
    using size_type = typename impl_type::size_type;
    using key_type = TS;
    using mapped_type = VT;
    using value_type = typename impl_type::value_type;

public:
    TimeSeries() = default;
    TimeSeries(TimeSeries const&) = default;
    TimeSeries(TimeSeries&&) = default;
    TimeSeries(std::initializer_list<value_type> list);
    TimeSeries& operator=(TimeSeries const&) = default;
    TimeSeries& operator=(TimeSeries&&) = default;
    ~TimeSeries() = default;

    bool empty() const;

    size_type size() const;

    size_type capacity() const;

    template<class... Args>
    void emplace_back(Args&&... args);

    void push_back(value_type const& val);

    template<class... Args>
    iterator emplace(Args&&... args);

    iterator insert(value_type const& val);
    
    iterator tail(TS const& earliest);
    void ntail(size_type items);
    
    void pop_front();

    void pop_back();
    
    value_type const& front() const;
    
    value_type const& back() const;
    
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    
    reverse_iterator rend();
    const_reverse_iterator rend() const;

private:
    using this_type = TimeSeries<VT,TS>;
    size_type beg_ = 0;
    impl_type v_;
    constexpr static int const consolidate_threshold = 1024;
};


//
// Implementation
//

template<class VT, class TS>
TimeSeries<VT,TS>::TimeSeries(std::initializer_list<value_type> list):
    beg_(0),
    v_(list)
{
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::size_type
TimeSeries<VT,TS>::size() const
{
    return v_.size() - beg_;
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::size_type
TimeSeries<VT,TS>::capacity() const
{
    return v_.capacity() - beg_;
}

template<class VT, class TS>
bool TimeSeries<VT,TS>::empty() const
{
    return !size();
}

template<class VT, class TS>
template<class... Args>
void TimeSeries<VT,TS>::emplace_back(Args&&... args)
{
    // Is reallocation needed?
    if (v_.size() > consolidate_threshold &&
        v_.size() + 1 > v_.capacity() &&
        2 * beg_ > v_.size()) {
        // Oh, it makes more sense to simply move everything to the beginning
        assert(begin() >= v_.begin() + size());
        std::copy(std::move_iterator<iterator>(begin()),
                  std::move_iterator<iterator>(end()),
                  v_.begin());
        v_.resize(size());
        beg_ = 0;
    }
    v_.emplace_back(std::forward<Args>(args)...);
}

template<class VT, class TS>
void TimeSeries<VT,TS>::push_back(value_type const& value)
{
    emplace_back(value);
}


template<class VT, class TS>
template<class... Args>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::emplace(Args&&... args)
{
    emplace_back(std::forward<Args>(args)...);
    auto it = v_.rbegin();
    auto rend = v_.rbegin() + size()-1;
    while(it != rend && it->first < (it+1)->first) {
        auto it2 = it + 1;
        std::swap(*it, *it2);
        it = it2;
    }
    return (it+1).base(); // safe... (see size-1 above)
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::insert(value_type const& value)
{
    return emplace(value_type{value});
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::tail(TS const& earliest)
{
    auto itbeg = std::lower_bound(begin(), end(), earliest,
    [](auto const& v, auto const& k) { return v.first < k; });
    beg_ = static_cast<size_type>(itbeg - v_.begin());
    return begin();
}

template<class VT, class TS>
void TimeSeries<VT,TS>::ntail(size_type nitems)
{
    assert(nitems <= size() && "ntail shouldnt exceed the size");
    beg_ += size() - nitems;
}

template<class VT, class TS>
void TimeSeries<VT,TS>::pop_front()
{
    // well if it's empty the behavior is undefined.
    ++beg_;
}

template<class VT, class TS>
void TimeSeries<VT,TS>::pop_back()
{
    v_.pop_back();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::value_type const&
TimeSeries<VT,TS>::front() const
{
    return *begin();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::value_type const&
TimeSeries<VT,TS>::back() const
{
    return v_.back();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::begin()
{
    return v_.begin() + beg_;
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_iterator
TimeSeries<VT,TS>::begin() const
{
    return const_cast<this_type*>(this)->begin();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_iterator
TimeSeries<VT,TS>::cbegin() const
{
    return begin();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::iterator
TimeSeries<VT,TS>::end()
{
    return v_.end();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_iterator
TimeSeries<VT,TS>::end() const
{
    return const_cast<this_type*>(this)->end();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_iterator
TimeSeries<VT,TS>::cend() const
{
    return end();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::reverse_iterator
TimeSeries<VT,TS>::rbegin()
{
    return v_.rbegin();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_reverse_iterator
TimeSeries<VT,TS>::rbegin() const
{
    return const_cast<this_type*>(this)->rbegin();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::reverse_iterator
TimeSeries<VT,TS>::rend()
{
    return v_.rbegin() + size();
}

template<class VT, class TS>
typename TimeSeries<VT,TS>::const_reverse_iterator
TimeSeries<VT,TS>::rend() const
{
    return const_cast<this_type*>(this)->rend();
}

} // close ixxor

#endif

