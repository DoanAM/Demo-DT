// (C) 2019-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_COMPILERCONFIG_HPP_
#define MW_COMPILERCONFIG_HPP_
//Check whether C++17 std::optional is available.
#ifdef __has_include
#  if __has_include(<optional>) && __cplusplus >= 201703L
#    define MW_STD_DETAIL_HAS_STD_OPTIONAL
#  endif
#endif

//Check whether C++17 std::variant is available.
#ifdef __has_include
#  if __has_include(<variant>) && __cplusplus >= 201703L
#    define MW_STD_DETAIL_HAS_STD_VARIANT
#  endif
#endif

//Following additional check is based on https://github.com/abseil/abseil-cpp/blob/master/absl/base/config.h
//For MSVC, `__has_include` is supported in VS 2017 15.3, which is later than
//the support for <optional> and <variant>. So we use _MSC_VER to check whether we have
//VS 2017 RTM (when <optional> and <variant> is implemented) or higher. Also, `__cplusplus`
//is not correctly set by MSVC, so we use `_MSVC_LANG` to check the language version.
#if defined(_MSC_VER) && _MSC_VER >= 1910 && \
	((defined(_MSVC_LANG) && _MSVC_LANG > 201402) || __cplusplus > 201402)
#define MW_STD_DETAIL_HAS_STD_OPTIONAL
#define MW_STD_DETAIL_HAS_STD_VARIANT
#endif

//TODO: Activate this code as soon as C++20 (and span) got released
//Check whether C++20 std::span is available.
//#ifdef __has_include
//#  if __has_include(<span>) && __cplusplus > 202012L <- This value probably has to be adapted.
//#    define MW_STD_DETAIL_HAS_STD_SPAN
//#  endif
//#endif


// undef the defines for now since we need to support VS2015 ABI
// TODO: remove these when we have dropped VS2015
#undef MW_STD_DETAIL_HAS_STD_OPTIONAL
#undef MW_STD_DETAIL_HAS_STD_VARIANT

#endif	//	MW_COMPILERCONFIG_HPP_
