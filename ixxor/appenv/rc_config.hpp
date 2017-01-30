#ifndef INCLUDED_APPENV_RC_CONFIG
#define INCLUDED_APPENV_RC_CONFIG

namespace ixxor {

class RCConfig
{
public:
    RCConfig();

    void load();
    void save() const;
};

} // :: ixxor

#endif


