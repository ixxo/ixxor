#include "kernel.hpp"
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <functional>


namespace ixxor {

namespace {

void module_init(char const* name, void* handle, Kernel* kernel)
{
    if (void* f = dlsym(handle, "ixxo_init")) {
        auto ixxo_init = reinterpret_cast<void(*)(char const*, void*)>(f);
        ixxo_init(name, kernel);
    } else {
        std::cerr << "No initializatino function found.\n";
    }
}

void module_cleanup(char const* name, void* handle, Kernel* kernel)
{
    // just call the cleanup function, if there's one.
    if (void* f = dlsym(handle, "ixxo_cleanup")) {
        auto ixxo_cleanup = reinterpret_cast<void(*)(char const*, void*)>(f);
        ixxo_cleanup(name, kernel);
    } else {
        std::cerr << "no cleanup function found....\n";
    }
}

} // :: ixxor::<anonymous>


Kernel::Kernel() = default;

Kernel::~Kernel() = default;

void Kernel::load(std::string const& module)
{
    if (!hmap_.count(module)) {
        std::string so_file = module; // for now.
        if (void* handle = dlopen(so_file.c_str(), RTLD_LOCAL | RTLD_LAZY)) {
            // Make sure the cleanup is called when this module is unloaded...
            module_init(module.c_str(), handle, this);
            std::shared_ptr<void> hmod {
                handle,
                [this,module](void* h) {
                    module_cleanup(module.c_str(), h, this); 
                    dlclose(h);
                }
            };
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


} // :: ixxor

