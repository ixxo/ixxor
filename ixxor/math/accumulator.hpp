#ifndef INCLUDED_IXXOR_MATH_ACCUMULATOR
#define INCLUDED_IXXOR_MATH_ACCUMULATOR

namespace ixxor {

template<typename T, class BinaryOperation = std::plus<T> >
class Accumulator
{
public:
    Accumulator(T const& init=0):
        acc_(init), cnt_(0u) {}

    void push(T const& t)
    {
        acc_ = op_(acc_, t);
        ++cnt_;
    }

    decltype( T{} / 2.0) mean() const
    {
        return acc_  / static_cast<double>(cnt_);
    }

    T const& value() const
    {
        return acc_;
    }

    unsigned int size() const
    {
        return cnt_;
    }

    Accumulator<T>& operator<<(T const& t)
    {
        push(t);
        return *this;
    }

private:
    T acc_;
    unsigned int cnt_;
    BinaryOperation op_;
};


} // :: ixxor

#endif

