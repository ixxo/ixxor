#ifndef INCLUDED_APPENV_SYS_UTIL
#define INCLUDED_APPENV_SYS_UTIL

#include <string>

namespace ixxor {
namespace sys_util {

char const* get_env(char const* name);
std::string get_env(std::string const&);
std::string get_home_directory();
void* load_module(char const* so_file);
void* find_module_symbol(void* handle, char const* symbol_name);


template<class Sig>
Sig find_symbol(void* handle, char const* symbol_name)
{
    return reinterpret_cast<Sig>(find_module_symbol(handle, symbol_name));
}

void close_module(void* handle);

} // : ixxor::sys_util
} // : ixxor

#endif


