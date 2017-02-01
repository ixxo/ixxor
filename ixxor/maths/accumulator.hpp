#ifndef INCLUDED_IXXOR_MATH_ACCUMULATOR
#define INCLUDED_IXXOR_MATH_ACCUMULATOR

#include <functional>
#include <type_traits>

namespace ixxor {

template<typename T, class BinaryOperation = std::plus<T> >
class Accumulator
{
public:
    
    Accumulator(T const& init):
        acc_(init), cnt_(0u) {}

    Accumulator(): Accumulator(0) {}
    
    auto mean() const;

    T const& value() const;

    auto size() const;

    Accumulator<T, BinaryOperation>& operator<<(T const& t);

private:
    T acc_;
    using size_type = unsigned int;
    size_type cnt_;
    BinaryOperation op_;
};

//
// Implementation
//

template<typename T, class BinaryOperation>
Accumulator<T, BinaryOperation>&
Accumulator<T, BinaryOperation>::operator<<(T const& t)
{
    acc_ = op_(acc_, t);
    ++cnt_;
    return *this;
}

template<typename T, class BinaryOperation>
auto Accumulator<T, BinaryOperation>::size() const
{
    return cnt_;
}

template<typename T, class BinaryOperation>
T const&
Accumulator<T, BinaryOperation>::value() const
{
    return acc_;
}

template<typename T, class BinaryOperation>
auto
Accumulator<T, BinaryOperation>::mean() const
{
    return acc_  / static_cast<double>(cnt_);
}



} // :: ixxor

#endif

