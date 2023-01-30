// (C) 2019-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_TYPE_TRAITS_HPP_
#define MW_TYPE_TRAITS_HPP_
#include <type_traits>

namespace mwstd {

//Backport of https://en.cppreference.com/w/cpp/types/remove_cvref

template<class T>
struct remove_cvref
{
	using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template<class T>
using remove_cvref_t = typename remove_cvref<T>::type;


}
#endif	//	MW_TYPE_TRAITS_HPP_
