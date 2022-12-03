// (C) 2016-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWDEPRECATED_HPP_
#define MW_MWDEPRECATED_HPP_

#include "mwPreprocessor.hpp"

// Mark methods and classes in public API as deprecated.
// Will generate a compiler warning, when deprecated elements are used.
//
// Usage:
//
// MW_DEPRECATED("Deprecated since 2014.12, please use IsCounterClockWise()")
// bool IsClockWise() const;
// 
// template <typename T>
// class MW_DEPRECATED("Deprecated since 2014.04. Use mwGenericExtrudedToolHelper instead.") mwLatheToolHelper
//
//
// Note:  This macro deprecation does not work for typedefs in MSCV before VS2017 !!
//
// In order to deprecate typedefs for MSVC compiler use '#pragma deprecated', e.g.:
//
// typedef mwMSimCollisionEvent mwMachSimCollisionInformation;
// #pragma deprecated(mwMachSimCollisionInformation)
//
#ifndef MW_DEPRECATED
#if defined(_MSC_VER) && _MSC_VER <= 1900 // VS2015 does not support deprecated constructors using modern attribute syntax
#define MW_DEPRECATED(text) __declspec(deprecated(text))
#elif defined __clang__
	// clang does not support C++11 attributes for explicitly instantiated templates nor mixing old and new style attributes
#define MW_DEPRECATED(text) __attribute__((deprecated))
#else 
	// feature testing is not possible as boost redefines __has_cpp_attribute
#define MW_DEPRECATED(text) [[deprecated(text)]]
#endif
#endif//MW_DEPRECATED


// Mark header files as deprecated by issuing a user defined warning at compile time for the included file.
//
// Usage:
//
// MW_COMPILE_WARNING("mwMachSimCollisionInformation.hpp is deprecated and will be removed in next release, please include mwMSimCollisionEvent.hpp instead!")
//
#ifndef MW_COMPILE_WARNING
#if defined(_MSC_VER)
#define MW_COMPILE_PRAGMA(x) __pragma(x)
#define MW_COMPILE_WARNING_MESSAGE(msg) message(__FILE__ "(" MW_PP_STRINGIZE(__LINE__) ") : Warning: " #msg)
#define MW_COMPILE_WARNING(msg) MW_COMPILE_PRAGMA(MW_COMPILE_WARNING_MESSAGE(msg))
#elif ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406 //GCC 4.6 (4.5.3 patched)
#define MW_COMPILE_PRAGMA(x) _Pragma(#x)
#define MW_COMPILE_WARNING(msg) MW_COMPILE_PRAGMA(GCC warning #msg)
#else//other c++ compilers
#define MW_COMPILE_PRAGMA(x) _Pragma(#x)
#define MW_COMPILE_WARNING(msg) MW_COMPILE_PRAGMA(message("Warning: " #msg))
#endif
#endif //MW_COMPILE_WARNING


#endif	//	MW_MWDEPRECATED_HPP_
