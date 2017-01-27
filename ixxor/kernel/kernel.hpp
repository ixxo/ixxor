#ifndef INCLUDED_KERNEL
#define INCLUDED_KERNEL
#include "protobuf.hpp"
#include "indicator.hpp"
#include "indicator_registry.hpp"

#include <string>
#include <unordered_map>
#include <array>

namespace ixxor {

class Kernel
{
public:
    Kernel();
    ~Kernel();

    // For now, 'module' is a relative path to a '.so' file
    void load(std::string const& module);
    void unload(std::string const& module);

    void associate(IndicatorRegItem const& item);

    // Create an indicator by name.
    template<class... Args>
    std::shared_ptr<Indicator> // should be unique but yeah
    indicator(std::string const& name, Args&&... args) const;


private:
    using handle_map =
        std::unordered_map<std::string, std::shared_ptr<void> >;
    using indicator_map =
        std::unordered_map<std::string, IndicatorRegItem>;

    handle_map hmap_;
    indicator_map imap_;
};


// inline implementation
template<class... Args>
std::shared_ptr<Indicator>
Kernel::indicator(std::string const& name, Args&&... args) const
{
    auto it = imap_.find(name);
    if (it == imap_.end()) return nullptr;
    auto const& entry = it->second;
    constexpr std::size_t const Np = sizeof...(Args);
    using param_type = std::array<Protobuf, Np>;
    param_type pack { { protobuf_converter<Args>::to_protobuf(args)... } };
    auto creator = reinterpret_cast<
            std::shared_ptr<Indicator>(*)(param_type const&)
                                    >(entry.creator);
    return creator(pack);
}

inline
void Kernel::associate(IndicatorRegItem const& item)
{
    imap_.insert(std::make_pair(item.name, item));
}

} // close ixxor

#endif // INCLUDED_KERNEL

