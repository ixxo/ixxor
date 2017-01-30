#ifndef INCLUDED_APPENV_PATH_UTIL
#define INCLUDED_APPENV_PATH_UTIL
#include <string>

namespace ixxor {
namespace path_util {

bool exists(std::string const& filename);
bool exists(char const*);

std::string join(std::string const& root, std::string const& add);


} // : ixxor::path_util
} // : ixxor


#endif


