#include "path_util.hpp"
#include <sys/stat.h>

namespace ixxor {
namespace path_util {

bool exists(std::string const& filename)
{
    return exists(filename.c_str());
}

bool exists(char const* filename)
{
  struct stat buffer;
  return stat (filename, &buffer) == 0; 
}

std::string join(std::string const& path1, std::string const& path2)
{
    std::string rv;
    if (!path1.empty()) {
        rv = path1;
        if (*rv.rbegin() != '/')
            rv += "/";
    }
    rv += path2;
    return rv;
}


} // : ixxor::path_util
} // : ixxor


