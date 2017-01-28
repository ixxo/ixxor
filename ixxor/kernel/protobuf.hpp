#ifndef INCLUDED_IXXOR_PROTOBUF
#define INCLUDED_IXXOR_PROTOBUF
//!
//! @file ixxor/kernel/protobuf.hpp
//! @brief Protocol Buffer
//! @details The protocol buffer is used in the communication between the
//! kernel and modules.
//!
#include <string>
#include <sstream>
#include <type_traits>

namespace ixxor {

//!
//! @class Protobuf
//! @brief Protocol buffer type
//! @details The implementation of a protocol buffer type
//!
class Protobuf
{
public:
    std::string erased; // :)
};

template<class T, class Enabled=void>
struct protobuf_converter
{
    // undefined: needs to be specialized...
    static Protobuf to_protobuf(T const& t);
    static T from_protobuf(Protobuf const& t);
};

// specialize for a few known things...
// dummy but who cares...
template<class T>
struct protobuf_converter<T,
    typename std::enable_if<
        std::is_integral<T>::value ||
        std::is_floating_point<T>::value
    >::type
    >
{
    static Protobuf to_protobuf(T const& t)
    {
        std::ostringstream ss;
        ss << t;
        return Protobuf{ ss.str() };
    }

    static T from_protobuf(Protobuf const& pb)
    {
        std::istringstream ss(pb.erased);
        T val;
        ss >> val;
        return val;
    }
};

template<>
struct protobuf_converter<std::string>
{
    static Protobuf to_protobuf(std::string const& t)
    {
        return Protobuf{ t };
    }

    static std::string from_protobuf(Protobuf const& pb)
    {
        return pb.erased;
    }
};

template<>
struct protobuf_converter<Protobuf>
{
    static Protobuf const& to_protobuf(Protobuf const& t)
    {
        return t;
    }

    static Protobuf const& from_protobuf(Protobuf const& pb)
    {
        return pb;
    }
};


} // close ixxor

#endif
