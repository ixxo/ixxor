#ifndef INCLUDED_IXXOR_INDICATOR_REGISTRY
#define INCLUDED_IXXOR_INDICATOR_REGISTRY
#include "indicator.hpp"
#include "protobuf.hpp"

#include <string>
#include <cstddef>
#include <memory>
#include <iostream>
#include <type_traits>
#include <array>
#include <tuple>

namespace ixxor {

class IndicatorRegItem
{
public:
    std::string name;
    std::string module;
    std::size_t arity;
    void*(*creator)(void*);
};

namespace detail {

template<int...>
struct seq {};

template<int N, int... S>
struct generate_seq: generate_seq<N-1, N-1, S...> {};

template<int... S>
struct generate_seq<0, S...> {
    using type = seq<S...>;
};


template<class IndicatorT, class... Args>
struct indicator_creator
{
    std::tuple<Args...> args;

    template<int... S>
    std::shared_ptr<Indicator> dispatch(seq<S...>) const
    {
        return std::make_shared<IndicatorT>(std::get<S>(args)...);
    }
};

template<class Arg, class... Args>
struct convert_parameter_pack
{
    std::tuple<Arg, Args...>
    static convert(Protobuf const* buf)
    {
        return std::tuple_cat(
            std::make_tuple<Arg>(
                protobuf_converter<Arg>::from_protobuf(buf[0])),
            convert_parameter_pack<Args...>::convert(buf+1)
            );
    }
};

template<class Arg>
struct convert_parameter_pack<Arg>
{

    static std::tuple<Arg>
    convert(Protobuf const* buf)
    {
        return std::make_tuple<Arg>(
            protobuf_converter<Arg>::from_protobuf(buf[0]));
    }
};

template<class IndicatorT, class... Args>
std::shared_ptr<Indicator>
make_concrete_indicator(std::array<Protobuf, sizeof...(Args)> const& args)
{
    constexpr std::size_t const N = sizeof...(Args);
    indicator_creator<IndicatorT, Args...> creator {
        convert_parameter_pack<Args...>::convert(args.data())
    };
    return creator.dispatch(typename generate_seq<sizeof...(Args)>::type());
}

} // :: ixxor::detail

template<class IndicatorT, class... Args>
IndicatorRegItem
make_indicator_registry_entry(std::string const& name,
                              std::string const& module)
{
    IndicatorRegItem item {
        name,
        module,
        sizeof...(Args),
        reinterpret_cast<void*(*)(void*)>(
            &detail::make_concrete_indicator<IndicatorT, Args...>)
    };
    return item;
}

} // :: ixxor

#endif

