// (C) 2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_FUNCTIONAL_HPP_
#define MW_FUNCTIONAL_HPP_
#include <functional>
#include <type_traits>
#include <utility>

namespace mwstd
{

//Backport of https://en.cppreference.com/w/cpp/utility/functional/invoke

template<class F, class... Args,
	std::enable_if_t<std::is_member_pointer<std::decay_t<F>>::value, int> = 0>
	inline auto invoke(F&& f, Args&&... args) -> decltype(std::mem_fn(f)(std::forward<Args>(args)...))
{
	return std::mem_fn(f)(std::forward<Args>(args)...);
}

template<class F, class... Args,
	std::enable_if_t<!std::is_member_pointer<std::decay_t<F>>::value, int> = 0>
	inline auto invoke(F&& f, Args&&... args) -> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
	return std::forward<F>(f)(std::forward<Args>(args)...);
}


//Backport of https://en.cppreference.com/w/cpp/utility/functional/not_fn

namespace detail
{

template<class F>
struct not_fn_t
{
    F f;

    template<class... Args>
    auto operator()(Args&&... args) -> decltype(!invoke(f, std::forward<Args>(args)...))
    {
        return !invoke(f, std::forward<Args>(args)...);
    }

    template<class... Args>
    auto operator()(Args&&... args) const -> decltype(!invoke(f, std::forward<Args>(args)...))
    {
        return !invoke(f, std::forward<Args>(args)...);
    }
};

}

template<class F>
inline detail::not_fn_t<std::decay_t<F>> not_fn(F&& f)
{
    return { std::forward<F>(f) };
}

}
#endif	//	MW_FUNCTIONAL_HPP_
