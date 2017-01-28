#ifndef INCLUDED_IXXOR_KERNEL_KERNEL_COMPONENT_ENTRY
#define INCLUDED_IXXOR_KERNEL_KERNEL_COMPONENT_ENTRY

#include "kernel_component.hpp"
#include "protobuf.hpp"
#include <tuple>
#include <string>
#include <memory>

namespace ixxor {


class KernelComponentEntry
{
public:
    std::string name;
    std::string module;
    int arity;
    void*(*creator)(void*);
};


namespace detail {
template<class Arg, class... Args>
struct convert_parameter_pack
{
    std::tuple<Arg, Args...>
    static convert(Protobuf const* buf)
    {
        return std::tuple_cat(
            std::make_tuple<Arg>(
                protobuf_converter<Arg>::from_protobuf(buf[0])),
            convert_parameter_pack<Args...>::convert(buf+1)
            );
    }
};

template<class Arg>
struct convert_parameter_pack<Arg>
{

    static std::tuple<Arg>
    convert(Protobuf const* buf)
    {
        return std::make_tuple<Arg>(
            protobuf_converter<Arg>::from_protobuf(buf[0]));
    }
};

template<int...>
struct seq {};

template<int N, int... S>
struct generate_seq: generate_seq<N-1, N-1, S...> {};

template<int... S>
struct generate_seq<0, S...> {
    using type = seq<S...>;
};


template<class T>
struct ComponentDeleter
{
    void(*deleter_)(T*);
    static void my_deleter(T* ptr)
    {
        delete ptr;
    }
public:
    ComponentDeleter(): deleter_(&ComponentDeleter<T>::my_deleter) {}
    ComponentDeleter(ComponentDeleter const&) = default;
    ComponentDeleter& operator=(ComponentDeleter const&) = default;

    void operator()(T* ptr) const
    {
        deleter_(ptr);
    }
};

template<class BaseComponent, class ComponentT, class... Args>
struct kernel_component_creator
{
    std::tuple<Args...> args;

    template<int... S>
    std::shared_ptr<BaseComponent> dispatch(seq<S...>) const
    {
        std::shared_ptr<ComponentT> ptr{
            new ComponentT{std::get<S>(args)...},
            ComponentDeleter<ComponentT>{}
        };
        return ptr;
    }
};

template<class Component, class ComponentT, class... Args>
std::shared_ptr<Component>
make_concrete_component(std::array<Protobuf, sizeof...(Args)> const& args)
{
    constexpr std::size_t const N = sizeof...(Args);
    kernel_component_creator<Component, ComponentT, Args...> creator {
        convert_parameter_pack<Args...>::convert(args.data())
    };
    return creator.dispatch(typename generate_seq<sizeof...(Args)>::type());
}


} // :: ixxor::detail


template<class ComponentBase, class ComponentT, class... Args>
KernelComponentEntry
make_kernel_component_entry(std::string const& name,
                            std::string const& module)
{
    KernelComponentEntry item {
        name,
        module,
        sizeof...(Args),
        reinterpret_cast<void*(*)(void*)>(
            &detail::make_concrete_component<ComponentBase, ComponentT, Args...>)
    };
    return item;
}

} // :: ixxor

#endif


