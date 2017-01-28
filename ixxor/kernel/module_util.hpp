#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE
#include "indicator_registry.hpp"
#include "kernel.hpp"
#include <string>

namespace ixxor {

// fwd declaration.
class Kernel;

namespace module_util {


template<class IndicatorT, class... Args>
void register_indicator(std::string const& name,
                        void* kernel,
                        std::string const& module)
{
    auto item = make_indicator_registry_entry<IndicatorT, Args...>(
            name, module);
    static_cast<Kernel*>(kernel)->associate(item);
}

template<class DataSource>
void register_data_source(std::string name,
                          void* kernel,
                          std::string const& module)
{


}

} // close ixxor::module_util
} // close ixxor

#endif

