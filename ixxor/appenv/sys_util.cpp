#include "sys_util.hpp"

#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <dlfcn.h>
#include <iostream>

namespace ixxor {
namespace sys_util {

char const* get_env(char const* name)
{
    return std::getenv(name);
}

std::string get_env(std::string const& name)
{
    return get_env(name.c_str());
}

std::string get_home_directory()
{
    std::string home;
    if ((home = std::getenv("HOME")).empty()) {
        home = getpwuid(getuid())->pw_dir;
    }
    return home;
}

void* load_module(char const* so_file)
{
    if (void* h = dlopen(so_file, RTLD_LOCAL | RTLD_LAZY)) {
        return h;
    } else {
        std::cerr << "Unable to load a module " << so_file << ": " << dlerror() << "\n";
    }
    return nullptr;
}

void* find_module_symbol(void* handle, char const* symbol_name)
{
    return dlsym(handle, symbol_name);
}


void close_module(void* handle)
{
    dlclose(handle);

}

} // : ixxor::sys_util
} // : ixxor

