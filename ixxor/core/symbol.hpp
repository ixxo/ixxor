#ifndef INCLUDED_CORE_SYMBOL
#define INCLUDED_CORE_SYMBOL
#include <array>

namespace ixxor {

// Unique identifier...
class SymbolID
{
    std::array<char,32> id_;
};

} // close ixxor

#endif

