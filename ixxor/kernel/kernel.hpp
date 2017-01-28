#ifndef INCLUDED_KERNEL
#define INCLUDED_KERNEL
#include "protobuf.hpp"
#include "kernel_component_entry.hpp"

#include <string>
#include <unordered_map>
#include <array>

namespace ixxor {

class Kernel
{
public:
    // No unloading for now...
    Kernel();
    ~Kernel();
    Kernel(Kernel const&) = delete;
    Kernel& operator=(Kernel const&) = delete;
    Kernel(Kernel&&) = delete;
    Kernel& operator=(Kernel&&) = delete;

    void load(std::string const& module);
    void unload(std::string const& module);

    void associate(KernelComponentEntry const& item);

    // Create an indicator by name.
    template<class Component, class... Args>
    std::shared_ptr<Component> // should be unique but yeah
    get(std::string const& name, Args&&... args) const;

private:
    using handle_map =
        std::unordered_map<std::string, std::shared_ptr<void> >;
    using component_map =
        std::unordered_map<std::string, KernelComponentEntry>;

    handle_map hmap_;
    component_map components_;
};

// inline implementation
template<class Component, class... Args>
std::shared_ptr<Component>
Kernel::get(std::string const& name, Args&&... args) const
{
    auto it = components_.find(name);
    if (it == components_.end()) return nullptr;
    auto const& entry = it->second;
    constexpr std::size_t const Np = sizeof...(Args);
    using param_type = std::array<Protobuf, Np>;
    param_type pack { { protobuf_converter<Args>::to_protobuf(args)... } };
    auto creator = reinterpret_cast<
            std::shared_ptr<Component>(*)(param_type const&)>(entry.creator);
    return creator(pack);
}

inline
void Kernel::associate(KernelComponentEntry const& item)
{
    components_.insert(std::make_pair(item.name, item));
}

} // :: ixxor

#endif // INCLUDED_KERNEL

