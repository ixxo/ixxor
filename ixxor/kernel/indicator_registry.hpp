#ifndef INCLUDED_IXXOR_INDICATOR_REGISTRY
#define INCLUDED_IXXOR_INDICATOR_REGISTRY
#include <string>
#include <cstddef>

namespace ixxor {

class IndicatorRegItem
{
public:
    std::string name;
    std::string module;
    std::size_t arity;
    void*(*creator)(void*);
};

}

#endif

