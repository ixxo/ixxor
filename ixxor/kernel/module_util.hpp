#ifndef INCLUDED_IXXOR_MODULE
#define INCLUDED_IXXOR_MODULE

namespace ixxor {


// fwd declaration.
class Kernel;


// This header file is intended to be used in modules to register various
// components with the kernel  -- modules.
// Examples are indicators.
namespace module_util {


template<
    class IndicatorT // explicit
    >
void register_indicator(void* kernel);




} // close ixxor::module_util
} // close ixxor


// IN-header implementation
namespace ixxor {
namespace module_util {

namespace detail {


template<class IndicatorT>
std::shared_ptr<Indicator>
make_concrete_indicator()
{
    std::shared_ptr<Indicator> p_i = std::make_shared<IndicatorT>();
    return p_i;
}



} // close ixxor::module_util::detail

template<class IndicatorT>
void register_indicator(void* kernel)
{
    // Register the constructor and the destructor with that thing...

}



} // close ixxor::module_util
} // close ixxor

#endif

