// (C) 2018-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_UTILITY_HPP_
#define MW_UTILITY_HPP_

#if !defined(MWSTD_EXCEPTION_API)
#if defined(__APPLE__)
#define MWSTD_EXCEPTION_API __attribute__ ((__visibility__("default")))
#else
#define MWSTD_EXCEPTION_API
#endif
#endif

#include "mwstd/detail/CompilerConfig.hpp"

//If either std-optional or std-variant is available, also the in_place_* will be available in <utility>. So <utility> will be included to provide the using declaration within namespace mwstd.
#if defined(MW_STD_DETAIL_HAS_STD_OPTIONAL) || defined(MW_STD_DETAIL_HAS_STD_VARIANT)
#include <utility>
#endif

//If std-variant is not available mwstd needs to define in_place_index_t. This needs std::size_t, which is defined in <cstddef>.
#ifndef MW_STD_DETAIL_HAS_STD_VARIANT
#include <cstddef>
#endif

//https://en.cppreference.com/w/cpp/utility/in_place
//[Missing]: Due to compiler and language limitations the inline variable templates (in_place_type and in_place_index) are not provided in mwstd.

namespace mwstd
{

#ifdef MW_STD_DETAIL_HAS_STD_OPTIONAL

using std::in_place_t;
using std::in_place;

#else

struct in_place_t
{
	explicit in_place_t() {}
};

const in_place_t in_place;

#endif

#ifdef MW_STD_DETAIL_HAS_STD_VARIANT

using std::in_place_type_t;
using std::in_place_index_t;

#else

template<class T>
struct in_place_type_t
{
	explicit in_place_type_t() {}
};

template<std::size_t I>
struct in_place_index_t
{
	explicit in_place_index_t() {}
};

#endif

} //namespace mwstd
#endif	//	MW_UTILITY_HPP_
