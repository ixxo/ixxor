#include "kernel.hpp"
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <functional>

namespace ixxor {


namespace {

void module_init(std::string const& name, void* handle, Kernel* kernel)
{
    if (void* ixxo_init_sym = dlsym(handle, "ixxo_init")) {
        auto f_init = 
            reinterpret_cast<void(*)(char const*, void*)>(ixxo_init_sym);
        f_init(name.c_str(), kernel);
    } else {
        std::cerr << "No initializatino function found.\n";

    }
}

void module_cleanup(std::string const& name, void* handle, Kernel* kernel)
{
    // just call the cleanup function, if there's one.
    if (void* ixxo_cleanup_sym = dlsym(handle, "ixxo_cleanup")) {
        auto f_cleanup = 
            reinterpret_cast<void(*)(char const*, void*)>(ixxo_cleanup_sym);
        f_cleanup(name.c_str(), kernel);
    } else {
        std::cerr << "no cleanup function found....\n";

    }
}

}





Kernel::Kernel() = default;

Kernel::~Kernel() = default;

void Kernel::load(std::string const& module)
{
    // for now we don't support and don't expect multiple module loading...
    // but this will change... at some point... .i just want to make a test
    // really.
    if (!hmap_.count(module)) {
        if (void* handle = dlopen(module.c_str(), RTLD_LOCAL | RTLD_LAZY)) {
            // Make sure the cleanup is called when this module is unloaded...
            module_init(module, handle, this);
            std::shared_ptr<void> hmod {
                handle,
                [this,module](void* h) {
                    module_cleanup(module, h, this); 
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


} // close ixxor

