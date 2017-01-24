#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE
#include "indicator.hpp"
#include "indicator_registry.hpp"
#include "kernel.hpp"
#include "protobuf.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <type_traits>
#include <array>
#include <tuple>

// In-header implementation
namespace ixxor {

// fwd declaration.
class Kernel;

namespace module_util {
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
                protobuf_converter<Arg>::from_protobuf(buf[0])
                ),
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
            protobuf_converter<Arg>::from_protobuf(buf[0])
            );
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


} // close ixxor::module_util::detail


template<class IndicatorT, class... Args>
void register_indicator(std::string const& name,
                        void* kernel,
                        std::string const& module)
{
    // Register the constructor and the destructor with that thing...
    // No arguments for now.
    auto creator = &detail::make_concrete_indicator<IndicatorT, Args...>;

    IndicatorRegItem item;
    item.name = name;
    item.module = module;
    item.arity = sizeof...(Args);
    item.creator = reinterpret_cast<void*(*)(void*)>(creator);
    static_cast<Kernel*>(kernel)->associate(item);
}


} // close ixxor::module_util
} // close ixxor

#endif

