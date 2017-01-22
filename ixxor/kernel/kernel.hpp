#ifndef INCLUDED_KERNEL
#define INCLUDED_KERNEL
#include "protobuf.hpp"
#include "kernel_component_entry.hpp"
#include <string>
#include <array>
#include <unordered_map>
#include <memory>
#include <algorithm>

namespace ixxor {

class Kernel
{
public:
    Kernel();
    ~Kernel();
    Kernel(Kernel const&) = delete;
    Kernel& operator=(Kernel const&) = delete;
    Kernel(Kernel&&) = delete;
    Kernel& operator=(Kernel&&) = delete;

    void load(std::string const& module);
    void unload(std::string const& module);
    void associate(KernelComponentEntry const& item);

    template<class Component, class... Args>
    std::shared_ptr<Component> // should be unique but yeah
    get(std::string const& name, Args... args) const;

    template<class OutputIt>
    OutputIt support(OutputIt dst) const;

private:
    using handle_map =
        std::unordered_map<std::string, std::shared_ptr<void> >;
    using component_map =
        std::unordered_map<std::string, KernelComponentEntry>;

    handle_map hmap_;
    component_map components_;

    using fptr_type = void*(*)(void*);
    fptr_type get_creator(std::string const& name) const;
};

// inline implementation
template<class Component, class... Args>
std::shared_ptr<Component>
Kernel::get(std::string const& name, Args... args) const
{
    using param_type = std::array<Protobuf, sizeof...(Args)>;
    param_type pack { { protobuf_converter<Args>::to_protobuf(args)... } };
    if (fptr_type dfunc = get_creator(name)) {
        using df_type = std::shared_ptr<Component>(*)(param_type const&);
        return reinterpret_cast<df_type>(dfunc)(pack);
    }
    return nullptr;
}

template<class OutputIt>
OutputIt Kernel::support(OutputIt dst) const
{
    return std::transform(components_.begin(), components_.end(), dst,
            [](component_map::value_type const& vp) { return vp.first; });
}

} // :: ixxor

#endif // INCLUDED_KERNEL

