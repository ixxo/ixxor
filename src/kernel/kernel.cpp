#include "kernel.hpp"
#include <dlfcn.h>
#include <stdexcept>

namespace ixxor {


namespace {

void module_init(std::string const& name, void* handle, Kernel* kernel)
{
    if (void* ixxo_init_sym = dlsym(handle, "ixxo_init")) {
        auto f_init = 
            reinterpret_cast<void(*)(char const*, void*)>(ixxo_init_sym);
        f_init(name.c_str(), kernel);
    }
}

void module_cleanup(std::string const& name, void* handle, Kernel* kernel)
{
    // just call the cleanup function, if there's one.
    if (void* ixxo_cleanup_sym = dlsym(handle, "ixxo_cleanup")) {
        auto f_cleanup = 
            reinterpret_cast<void(*)(char const*, void*)>(ixxo_cleanup_sym);
        f_cleanup(name.c_str(), kernel);
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
            hmap_[module] = handle;
            // Cool now initialize that stufff...
            module_init(module, handle, this);
        } else {
            throw std::runtime_error("loading module failed.. rc=...");
        }
    }
}

void Kernel::unload(std::string const& module)
{
    auto it = hmap_.find(module);
    if (it != hmap_.end()) {
        if (int rc = dlclose(it->second)) {
            throw std::runtime_error("error unlloading module");
        }
        module_cleanup(module, it->second, this);
        hmap_.erase(it);
    }
}


} // close ixxor

