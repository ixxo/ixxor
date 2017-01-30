#include "kernel.hpp"
#include <ixxor/appenv/path_util.hpp>
#include <ixxor/appenv/sys_util.hpp>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <sstream>

namespace ixxor {

namespace {

void module_init(std::string const& name, void* handle, Kernel* kernel)
{
    using f_sig = void(*)(char const*, void*);
    if (auto f = sys_util::find_symbol<f_sig>(handle, "ixxo_init")) {
        f(name.c_str(), kernel);
    } else {
        std::cerr << "No initializatino function found.\n";
    }
}

void module_cleanup(std::string const& name, void* handle, Kernel* kernel)
{
    // just call the cleanup function, if there's one.
    using f_sig = void(*)(char const*, void*);
    if (auto f = sys_util::find_symbol<f_sig>(handle, "ixxo_cleanup")) {
        f(name.c_str(), kernel);
    } else {
        std::cerr << "no cleanup function found....\n";
    }
}

std::shared_ptr<void> module_load(std::string const& name, Kernel* kernel)
{
    std::string so_file = name;
    if (!path_util::exists(so_file.c_str())) {
        if (char const* ixxor_root = sys_util::get_env("IXXOR_ROOT")) {
            std::ostringstream ss;
            ss << ixxor_root << "/share/ixxor/modules/lib" << name << ".so";
            so_file = ss.str();
        }
    }
    if (!path_util::exists(so_file.c_str())) {
        return nullptr;
    }
    void* handle = sys_util::load_module(so_file.c_str());
    module_init(name, handle, kernel);
    std::shared_ptr<void> hmod {
        handle,
        [kernel,name](void* w) {
            module_cleanup(name, w, kernel); 
            sys_util::close_module(w);
        }
    };
    return hmod;
}

} // :: ixxor::<anonymous>


Kernel::Kernel() = default;

Kernel::~Kernel() = default;

void Kernel::load(std::string const& module)
{
    if (!hmap_.count(module)) {
        std::string so_file = module; // for now.
        if (auto hmod = module_load(module, this)) {
            hmap_[module] = hmod;
        } else {
            throw std::runtime_error("loading module failed.. rc=...");
        }
    }
}

void Kernel::unload(std::string const& module)
{
    auto it = hmap_.find(module);
    if (it != hmap_.end() && it->second.unique()) {
        hmap_.erase(it);
    }
}

void Kernel::associate(KernelComponentEntry const& item)
{
    components_.insert(std::make_pair(item.name, item));
}

Kernel::fptr_type Kernel::get_creator(std::string const& name) const
{
    auto it = components_.find(name);
    if (it == components_.end()) return nullptr;
    return reinterpret_cast<fptr_type>(it->second.creator);
}


} // :: ixxor

