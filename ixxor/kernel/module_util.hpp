#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE
#include "indicator.hpp"
#include "indicator_registry.hpp"
#include "kernel.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <type_traits>

// In-header implementation
namespace ixxor {

// fwd declaration.
class Kernel;

namespace module_util {
namespace detail {

template<class IndicatorT>
std::shared_ptr<Indicator>
make_concrete_indicator()
{
    auto p_i = std::make_shared<IndicatorT>();
    return p_i;
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


template<class IndicatorT>
void register_indicator(void* kernel,
                        std::string const& name,
                        std::string const& module)
{
    // Register the constructor and the destructor with that thing...
    // No arguments for now.
    auto creator = &detail::make_concrete_indicator<IndicatorT>;

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

