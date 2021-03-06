#ifndef INCLUDED_IXXOR_ITL_RING
#define INCLUDED_IXXOR_ITL_RING

#include <memory>
#include <cstddef>
#include <cassert>
#include <iterator>
#include <initializer_list>

namespace ixxor {
namespace itl {

template<typename T, bool is_const> 
class ring_iterator;


template<typename T>
class ring
{
    template<class Tx, bool isConst> friend class ring_iterator;

public:
    using size_type = std::size_t;
    using value_type = T;
private:

    size_type pos_;
    size_type size_;
    size_type max_size_;
    std::unique_ptr<value_type[]> c_;

public:
    using iterator = ring_iterator<T, false>;
    using const_iterator = ring_iterator<T, true>;

public:
    ring();
    ring(ring const&);
    ring(ring&&);
    ring& operator=(ring const&);
    ring& operator=(ring&&);
    ring(std::initializer_list<value_type> lst);
  
    explicit ring(size_type count);

    bool empty() const;

    size_type size() const;
    size_type max_size() const;

    void resize(size_type count);
    void resize(size_type count, value_type const& value);

    void push_back(value_type const&);
    template<class... Args>
    void emplace_back(Args&&...);

    iterator begin() { return iterator{this, 0}; }
    const_iterator begin() const { return const_iterator{this, 0}; }
    iterator end() { return iterator{}; }
    const_iterator end() const { return const_iterator{}; }

};

//
// Implementation
//

template<class T>
ring<T>::ring():
    pos_(0u),
    size_(0u),
    max_size_(0u),
    c_(nullptr)
{
}

template<class T>
ring<T>::ring(std::initializer_list<value_type> lst):
    pos_(0u),
    size_(lst.size()),
    max_size_(lst.size()),
    c_(new value_type[lst.size()])
{
    if (size_) {
        std::copy(std::begin(lst), std::end(lst), c_.get());
    }
}

template<class T>
ring<T>::ring(ring const& other)
{
    if (other.max_size()) {
        c_.reset(new value_type[other.max_size()]);
    }
    max_size_ = other.max_size_;
    size_ = other.size_;
    pos_ = 0;
    if (size_) {
        std::copy(other.begin(), other.end(), begin());
    }
}

template<class T>
ring<T>::ring(ring&& other):
    pos_(other.pos_),
    size_(other.size_),
    max_size_(other.max_size_),
    c_(std::move(other.c_))
{
}


template<class T>
ring<T>& ring<T>::operator=(ring<T>&& other)
{
    pos_ = other.pos_;
    size_ = other.size_;
    max_size_ = other.max_size_;
    c_ = std::move(other.c_);
    return *this;
}

template<class T>
ring<T>& ring<T>::operator=(ring<T> const& other)
{
    pos_ = 0;
    size_ = other.size_;
    max_size_ = other.max_size_;
    if (max_size_) {
        c_.reset(new value_type[max_size_]);
        std::copy(other.begin(), other.end(), begin());
    }
    return *this;
}


template<class T>
ring<T>::ring(size_type count):
    ring()
{
    if (count) {
        c_.reset(new value_type[count]);
        max_size_ = count;
    }
}

template<class T>
bool ring<T>::empty() const
{
    return size_==0;
}

template<class T>
typename ring<T>::size_type
ring<T>::size() const
{
    return size_;
}

template<class T>
typename ring<T>::size_type
ring<T>::max_size() const
{
    return max_size_;
}

template<class T>
void ring<T>::resize(size_type count)
{
    assert(count > max_size_); // only enlarging supported for now...
    std::unique_ptr<value_type[]> newp(new value_type[count]);
    std::copy(begin(), end(), newp.get());
    c_ = std::move(newp);
    pos_ = 0;
    max_size_ = count;
}

template<class T>
template<class... Args>
void ring<T>::emplace_back(Args&&... args)
{
    assert(max_size_ > 0);
    value_type* arr = c_.get();
    if (size_ < max_size_) {
        arr[size_] = value_type{std::forward<Args>(args)...};
        ++size_;
        return;
    } else {
        arr[pos_] = value_type{std::forward<Args>(args)...};
        ++pos_;
        if (pos_ == size_) pos_ = 0;
    }
}

template<class T>
void ring<T>::push_back(value_type const& value)
{
    return emplace_back(value);
}

} // :: ixxor::itl
} // :: ixxor


#include "ring_iterator.ipp"


#endif

