#include <memory>
#include <cstddef>
#include <cassert>
#include <iterator>
#include <type_traits>

namespace ixxor {
namespace itl {

template<typename T, bool is_const> 
class ring_iterator
{
public:

    using Tx = typename std::conditional<is_const, T const, T>::type;
    using ringx = typename std::conditional<is_const, ring<T> const, ring<T> >::type;
    using value_type = T;
    using reference = Tx&;
    using pointer = Tx*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    ring_iterator()
        : obj_(nullptr), idx_(0)
    {
    }

    ring_iterator(ring_iterator const& other) = default;
    ring_iterator(ring_iterator&& other) = default;
    
    ring_iterator& operator=(ring_iterator const& other) = default;
    ring_iterator& operator=(ring_iterator&& other) = default;

    ring_iterator& operator++()
    {
        if (!obj_) {
            return *this;
        }
        ++idx_;
        if (idx_ >= obj_->size_) {
            obj_ = nullptr;
            idx_ = 0;
        }
        return *this;
    }
    
    ring_iterator& operator+=(difference_type dif)
    {
        if (!obj_) {
            return *this;
        }
        idx_ += dif;
        if (idx_ >= obj_->size_) {
            obj_ = nullptr;
            idx_ = 0;
        }
        return *this;
    }

    ring_iterator& operator--()
    {
        if (!obj_) {
            return *this;
        }
        if (idx_) {
            --idx_;
        } else {
            obj_ = nullptr;
            idx_ = 0;
        }
        return *this;
    }
    
    ring_iterator& operator-=(difference_type dif)
    {
        if (!obj_ || dif > idx_) {
            obj_ = nullptr;
            idx_ = 0;
            return *this;
        }
        idx_ -= dif;
        return *this;
    }

    ring_iterator operator+(difference_type dif) const
    {
        ring_iterator copy{*this};
        copy += dif;
        return copy;
    }

    ring_iterator operator-(difference_type dif) const
    {
        ring_iterator copy{*this};
        copy -= dif;
        return copy;
    }

    ring_iterator operator++(int)
    {
        auto prev = *this;
        ++(*this);
        return prev;
    }
    
    ring_iterator operator--(int)
    {
        auto prev = *this;
        --(*this);
        return prev;
    }

    reference operator[](difference_type n) const
    {
        return obj_->c_.get()[(obj_->pos_ + idx_ + n) % obj_->max_size_];
    }

    bool operator==(ring_iterator const& other) const
    {
        return obj_ == other.obj_ && (!obj_ || idx_ == other.idx_);
    }
    bool operator!=(ring_iterator const& other) const
    {
        return !operator==(other);
    }

    reference operator*() const
    {
        return obj_->c_.get()[(obj_->pos_ + idx_) % obj_->max_size_];
    }


private:
    explicit ring_iterator(ringx* obj, std::size_t idx):
        obj_(obj), idx_(idx)
    {
        if (idx_ >= obj_->size_) {
            obj_ = nullptr;
            idx_ = 0;
        }
    }

    template<class Tx>
    friend class ring;

    ringx* obj_;
    std::size_t idx_;
};

} // :: ixxor::itl
} // :: ixxor
