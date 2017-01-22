#ifndef INCLUDED_KERNEL
#define INCLUDED_KERNEL
#include <string>
#include <unordered_map>

namespace ixxor {

class Kernel
{
public:
    Kernel();
    ~Kernel();

    void load(std::string const& module);
    void unload(std::string const& module);

private:
    using handle_map = std::unordered_map<std::string, void*>;
    handle_map hmap_;

};



} // close ixxor

#endif // INCLUDED_KERNEL

