#ifndef INCLUDED_IXXOR_PROTOBUF
#define INCLUDED_IXXOR_PROTOBUF

#include <string>
#include <sstream>

namespace ixxor {

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
    typename std::enable_if<std::is_integral<T>::value>::type
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


} // close ixxor


#endif
