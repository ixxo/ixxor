#include "kernel.hpp"
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <sstream>

#include <sys/stat.h>

namespace ixxor {

namespace {

bool file_exists(char const* filename)
{
  struct stat buffer;
  return stat (filename, &buffer) == 0; 
}

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

void* module_load(char const* name)
{
    std::string so_file = name;
    if (!file_exists(so_file.c_str())) {
        if (char const* ixxor_root = std::getenv("IXXOR_ROOT")) {
            std::ostringstream ss;
            ss << ixxor_root << "/share/ixxor/modules/lib" << name << ".so";
            so_file = ss.str();
        }
    }
    if (!file_exists(so_file.c_str())) {
        return nullptr;
    }
    if (void* h = dlopen(so_file.c_str(), RTLD_LOCAL | RTLD_LAZY)) {
        return h;
    } else {
        std::cerr << "Unable to load a module " << so_file << ": " <<
                     dlerror() << "\n";
    }
    return nullptr;
}

} // :: ixxor::<anonymous>


Kernel::Kernel() = default;

Kernel::~Kernel() = default;

void Kernel::load(std::string const& module)
{
    if (!hmap_.count(module)) {
        std::string so_file = module; // for now.
        if (void* handle = module_load(module.c_str())) {
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

