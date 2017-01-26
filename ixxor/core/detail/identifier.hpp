#ifndef INCLUDED_CORE_DETAIL_IDENTIFIER
#define INCLUDED_CORE_DETAIL_IDENTIFIER
#include <array>
#include <functional>
#include <string>
#include <cstddef>
#include <algorithm>

namespace ixxor {
namespace detail {

template<int N> class Identifier;


template<int N>
class Identifier
{
    using impl_type = std::array<char, N>;
public:
    using size_type = typename impl_type::size_type;

    Identifier();
    template<int M>
    Identifier(char const (&id)[M]);
    Identifier(Identifier const&) = default;
    Identifier& operator=(Identifier const&) = default;
    ~Identifier() = default;

    char const* data() const;

    bool empty() const;

    size_type length() const;

    bool operator==(Identifier<N> const& other) const;
    bool operator!=(Identifier<N> const& other) const;

private:
    impl_type id_;
};

} // close ixxor::detail
} // close ixxor

namespace std {

template<int N>
struct hash<ixxor::detail::Identifier<N> >
{
    std::size_t operator()(ixxor::detail::Identifier<N> const& id) const;
};

} // close std



//
// Implementation
//
namespace ixxor {
namespace detail {

template<int N>
Identifier<N>::Identifier()
{
    id_.fill('\0');
}

template<int N>
template<int M>
Identifier<N>::Identifier(char const (&id)[M])
{
    static_assert(M <= N, "ID capacity overflow");
    std::copy(&id[0], &id[0] + M, id_.data());
}

template<int N>
typename Identifier<N>::size_type
Identifier<N>::length() const
{
    return std::find(id_.begin(), id_.end(), '\0') - id_.begin();
}

template<int N>
bool Identifier<N>::empty() const
{
    return id_[0] != '\0';
}

template<int N>
char const* Identifier<N>::data() const
{
    return id_.data();
}
    
template<int N>
bool Identifier<N>::operator==(Identifier<N> const& other) const
{
    return id_ == other.id_;
}

template<int N>
bool Identifier<N>::operator!=(Identifier<N> const& other) const
{
    return id_ != other.id_;
}

} // close ixxor:detail
} // close ixxor

namespace std {

template<int N>
std::size_t 
hash<
    ixxor::detail::Identifier<N>
    >::operator()(ixxor::detail::Identifier<N> const& id) const
{
    return std::hash<std::string>()(id.data());
}


} // close std

#endif

