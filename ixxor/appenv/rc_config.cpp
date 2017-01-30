#include "rc_config.hpp"
#include "path_util.hpp"
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <string>
#include <iostream>


namespace ixxor {

RCConfig::RCConfig()
{
}


void RCConfig::load()
{
    std::string home;
    if ((home = std::getenv("HOME")).empty()) {
        home = getpwuid(getuid())->pw_dir;
    }
    std::string config_u = path_util::join(home, ".ixxorrc");
    if (path_util::exists(config_u)) {
        std::cerr << "Yes there's a config file " << config_u << "\n";
    }

}

void RCConfig::save() const
{

}




} // : ixxor

