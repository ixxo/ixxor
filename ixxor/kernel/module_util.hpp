#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE
#include "kernel_component_entry.hpp"
#include "kernel.hpp"
#include "indicator.hpp"
#include <string>

namespace ixxor {

namespace module_util {

template<class IndicatorT, class... Args>
void register_indicator(std::string const& name,
                        Kernel* kernel,
                        std::string const& module)
{
    static_cast<Kernel*>(kernel)->associate(
        make_kernel_component_entry<Indicator, IndicatorT, Args...>(
            name,module
            )
        );
}

template<class DataSource>
void register_data_source(std::string name,
                          Kernel* kernel,
                          std::string const& module)
{

}

} // close ixxor::module_util
} // close ixxor

#endif

