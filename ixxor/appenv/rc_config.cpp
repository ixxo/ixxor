#include "rc_config.hpp"
#include "path_util.hpp"
#include "sys_util.hpp"
#include <string>
#include <iostream>

namespace ixxor {

RCConfig::RCConfig()
{
}

void RCConfig::load()
{
    std::string home = sys_util::get_home_directory();
    std::string config_u = path_util::join(home, ".ixxorrc");
    if (path_util::exists(config_u)) {
        std::cerr << "Yes there's a config file " << config_u << "\n";
    }

}

void RCConfig::save() const
{
}


} // : ixxor

