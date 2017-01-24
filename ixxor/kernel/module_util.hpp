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
struct sequence {};

template<int N, int... S>
struct gens: gens<N-1, N-1, S...> {};

template<int... S>
struct gens<0, S...> {
    using type = sequence<S...>;
};

template<class IndicatorT, class... Args>
struct indicator_creator
{
    std::tuple<Args...> args;

    template<int... S>
    std::shared_ptr<Indicator> dispatch(sequence<S...>) const
    {
        return std::make_shared<IndicatorT>(std::get<S>(args)...);
    }

    std::shared_ptr<Indicator> call() const
    {
        return dispatch(typename gens<sizeof...(Args)>::type());
    }
};

template<class Arg, class Arg2, class... Args>
std::tuple<Arg, Args...>
convert_parameter_pack(Protobuf const* buf)
{
    return std::tuple_cat(
            convert_parameter_pack<Arg>(buf),
            convert_parameter_pack<Arg2, Args...>(buf+1)
            );
}

template<class Arg>
std::tuple<Arg>
convert_parameter_pack(Protobuf const* buf)
{
    return std::make_tuple<Arg>(protobuf_converter<Arg>::from_protobuf(buf[0]));
}


template<class IndicatorT, class... Args>
std::shared_ptr<Indicator>
make_concrete_indicator(std::array<Protobuf, sizeof...(Args)> const& args)
{
    constexpr std::size_t const N = sizeof...(Args);
    indicator_creator<IndicatorT, Args...> creator {
        convert_parameter_pack<Args...>(args.data())
    };
    return creator.call();
}

template<class T> struct bla {};


template<class T, class... Args> struct bla<void(T::*)(Args...)>
{
    using type = decltype(std::get<0>(std::tuple<Args...>{}));

};

template<class T, class... Args> struct bla<void(T::*)(Args&&...)>
{
    using type = decltype(std::get<0>(std::tuple<Args...>{}));

};

template<class T>
struct function_arity {};

template<class T, class... Args>
struct function_arity<void(T::*)(Args...)>
{
    constexpr static std::size_t const value = sizeof...(Args);
};


template<class IT>
using indicator_arity =
    std::integral_constant<std::size_t, 
                           function_arity<decltype(&IT::init)>::value >;

} // close ixxor::module_util::detail


template<class IndicatorT, class... Args>
void register_indicator(void* kernel,
                        std::string const& name,
                        std::string const& module)
{
    // Register the constructor and the destructor with that thing...
    // No arguments for now.
    auto creator = &detail::make_concrete_indicator<IndicatorT, Args...>;

    IndicatorRegItem item;
    item.name = name;
    item.module = module;
    item.arity = detail::indicator_arity<IndicatorT>::value;
    item.creator = reinterpret_cast<void*(*)(void*)>(creator);
    static_cast<Kernel*>(kernel)->associate(item);
}



} // close ixxor::module_util
} // close ixxor

#endif

