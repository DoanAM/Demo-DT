// (C) 2020-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWLANGUAGEFEATURES_HPP_
#define MW_MWLANGUAGEFEATURES_HPP_

#include "mwPreprocessor.hpp"

//Info: clang does define __GNUC__ to 4 and __GNUC_MINOR__ to 2 and __GNUC_PATCHLEVEL__ to 1


//For Visual Studio 2010 and below there is no 'override' and 'final'.
//VS2010 warns about them as "nonstandard extension".
//For VS>=2012 and all other compilers they are available.
#if !defined(_MSC_VER) || (_MSC_VER >= 1700)
#define MW_OVERRIDE override
#define MW_FINAL final
#else
#define MW_OVERRIDE
#define MW_FINAL
#endif

// '= default' and '= delete' were added since VS2013.
// This macro can be applied safely only on destructors.
// Constructors, copy constructors, move operators and
//  other basic functions cannot have '{}' as an implementation.
#if !defined(_MSC_VER) || (_MSC_VER >= 1800)
#define MW_DEFAULT_DESTRUCTOR_IMPL = default;
#else
#define MW_DEFAULT_DESTRUCTOR_IMPL {}
#endif

#if !defined(_MSC_FULL_VER) || (_MSC_FULL_VER >= 190023026)
#define MW_HAS_CXX11_REF_QUALIFIERS
#endif



#if defined(__clang__)
//CLANG

#if __has_feature(cxx_noexcept)
#define MW_DETAIL_HAS_CXX_NOEXCEPT
#endif

#elif defined(__GNUC__)
//GCC

#define MW_DETAIL_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#define MW_DETAIL_GCC_CXX11
#endif

#if (MW_DETAIL_GCC_VERSION >= 40600) && defined(MW_DETAIL_GCC_CXX11)
#define MW_DETAIL_HAS_CXX_NOEXCEPT
#endif

#undef MW_DETAIL_GCC_VERSION
#undef MW_DETAIL_GCC_CXX11

#elif defined(_MSC_VER)
//VISUAL STUDIO

#if (_MSC_FULL_VER >= 190023026)
#define MW_DETAIL_HAS_CXX_NOEXCEPT
#endif

#else
#error The compiler you use is currently not supported.
#endif


//Now that we have checked for the support of certain C++-features,
//we provide compatibility macros.

#ifdef MW_DETAIL_HAS_CXX_NOEXCEPT
#  define MW_NOEXCEPT noexcept
#  define MW_NOEXCEPT_OR_NOTHROW noexcept
#  define MW_NOEXCEPT_IF(Predicate) noexcept((Predicate))
#  define MW_NOEXCEPT_EXPR(Expression) noexcept((Expression))
#  undef MW_DETAIL_HAS_CXX_NOEXCEPT
#else
#  define MW_NOEXCEPT
#  define MW_NOEXCEPT_OR_NOTHROW throw()
#  define MW_NOEXCEPT_IF(Predicate)
#  define MW_NOEXCEPT_EXPR(Expression) false
#endif

#if _MSC_VER >= 1900 || \
	__GNUC__ > 4 || \
	(__GNUC__ == 4 && __GNUC_MINOR__ >= 3) || \
	__clang_major__ > 2  || \
	(__clang_major__ == 2 && __clang_minor__ >= 9)
#define MW_COMPILER_HAS_MAGIC_STATICS
#endif

#if _MSC_VER >= 1900 || \
	__GNUC__ > 4 || \
	(__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || \
	__clang_major__ > 3  || \
	(__clang_major__ == 3 && __clang_minor__ >= 9)
#define MW_COMPILER_HAS_INHERITING_CONSTRUCTORS
#endif

#if _MSC_VER >= 1900 || \
	__GNUC__ > 4 || \
	(__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || \
	__clang_major__ > 3  || \
	(__clang_major__ == 3 && __clang_minor__ >= 3)
#define MW_NORETURN [[noreturn]]
#elif defined _MSC_VER 
#define MW_NORETURN __declspec(noreturn) 
#else
#define MW_NORETURN __attribute__((noreturn))
#endif

#ifdef __cpp_constexpr
#define MW_CONSTEXPR constexpr
#else
#define MW_CONSTEXPR
#endif

#if defined _MSC_VER && _MSC_VER == 1800
#define MW_REQUIRES_ATOMIC_INIT 1
#else
#define MW_REQUIRES_ATOMIC_INIT 0
#endif

// Before VS2015 Update 3, VS compiler generates a warning for while(0) generates a warning:
// C4127: conditional expression is constant
#if defined _MSC_VER && _MSC_VER <= 1910
#define MW_DETAIL_WHILE_FALSE \
__pragma(warning(push)) \
__pragma(warning(disable:4127)) \
while (0) \
__pragma(warning(pop))
#else
#define MW_DETAIL_WHILE_FALSE \
while (0)
#endif

#if !defined(__cpp_init_captures) && _MSC_VER >= 1900 
// Add missing feature-test macro
#define __cpp_init_captures 201304L
#endif

#if _MSC_VER >= 1914
#define MW_USE_STD_CHARCONV 1
#if _MSC_VER >= 1924
#define MW_USE_STD_CHARCONV_FP 1
#else
#define MW_USE_STD_CHARCONV_FP 0
#endif
#else
#define MW_USE_STD_CHARCONV 0
#define MW_USE_STD_CHARCONV_FP 0
#endif

#if (defined(_MSC_VER) && _MSC_VER >= 1910 && _MSVC_LANG >= 201703L) || defined(__cpp_if_constexpr)
#define MW_IF_CONST(condition) if constexpr (condition)
#elif defined(_MSC_VER)
#define MW_IF_CONST(condition) \
	__pragma(warning(push)) __pragma(warning(disable : 4127)) if (condition) __pragma(warning(pop))
#else
#define MW_IF_CONST(condition) if (condition)
#endif


//The macro MW_STATIC_ASSERT_MSG(B, Msg) expands to static_assert(B, Msg) on VS2010 and all versions of GCC and clang.
//For VS2008 it expands to a workaround, inspired by boost.

#if defined(_MSC_VER) && (_MSC_VER < 1600)

namespace mwCppLanguageSupport { namespace detail {

template<bool X> struct STATIC_ASSERTION_FAILURE;

template<> struct STATIC_ASSERTION_FAILURE<true> { };

template<int> struct static_assert_test {};

} }

#define MW_STATIC_ASSERT_MSG(B, Msg)\
typedef ::mwCppLanguageSupport::detail::static_assert_test<\
	sizeof(::mwCppLanguageSupport::detail::STATIC_ASSERTION_FAILURE< static_cast<bool>(B) >)>\
		MW_PP_CONCAT(mw_static_assert_typedef_, __COUNTER__)

#else
#define MW_STATIC_ASSERT_MSG(B, Msg) \
	do                               \
	{                                \
		static_assert(B, Msg);       \
	}                                \
	MW_DETAIL_WHILE_FALSE
#endif

/// Use MW_UNREFERENCED_PARAMETER to name a parameter in the function signature, which is not used by the code.
/// e.g. when the parameter requires name for documentation and cannot be removed.
#define MW_UNREFERENCED_PARAMETER(x) MW_STATIC_ASSERT_MSG(sizeof(x) >= 0, "Parameter must be used")

#if defined(_MSC_VER) && (_MSC_VER < 1910)
#undef MW_UNREFERENCED_PARAMETER
#define MW_UNREFERENCED_PARAMETER(x) x
#endif

#endif	// MW_MWLANGUAGEFEATURES_HPP_
