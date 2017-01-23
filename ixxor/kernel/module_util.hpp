#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE
#include <string>
#include <memory>
#include "indicator.hpp"
#include "indicator_registry.hpp"
#include "kernel.hpp"

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
    item.arity = 0; // for now
    item.creator = reinterpret_cast<void*(*)(void*)>(creator);
    static_cast<Kernel*>(kernel)->associate(item);
}



} // close ixxor::module_util
} // close ixxor

#endif

