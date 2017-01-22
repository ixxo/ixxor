#ifndef INCLUDED_KERNEL
#define INCLUDED_KERNEL
#include <string>
#include <unordered_map>

#include "indicator_registry.hpp"

namespace ixxor {

class Kernel
{
public:
    Kernel();
    ~Kernel();

    void load(std::string const& module);
    void unload(std::string const& module);

    void associate(IndicatorRegItem const& item);

private:
    using handle_map =
        std::unordered_map<std::string, std::shared_ptr<void> >;
    using indicator_map =
        std::unordered_map<std::string, IndicatorRegItem>;

    handle_map hmap_;
    indicator_map imap_;

};

inline
void Kernel::associate(IndicatorRegItem const& item)
{
    imap_.insert(std::make_pair(item.name, item));
}



} // close ixxor

#endif // INCLUDED_KERNEL

