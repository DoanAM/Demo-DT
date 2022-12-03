// (C) 2017-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWWWARNINGPRAGMAS_HPP_
#define MW_MWWWARNINGPRAGMAS_HPP_

/// This header file provides a compiler independent way of disabling warnings.
/// Although every developer is encouraged to resolve warnings instead of disabling them, 
/// disabling warnings is sometimes necessary, e.g. 
/// - when writing back compatible code for deprecated API functions
/// - in the compiler occur bugs
/// - warning of the compiler does not make sense
///
/// Sample usage:
/// MW_WARNING_PUSH
/// MW_WARNING_DISABLE_DEPRECATED
/// Your intended usage of deprecated code
/// MW_WARNING_POP

#if defined(_MSC_VER)
#define MW_WARNING_PUSH __pragma(warning(push))
#define MW_WARNING_POP __pragma(warning(pop))
#define MW_WARNING_DISABLE_DEPRECATED __pragma(warning(disable:4995 4996))
#define MW_WARNING_DISABLE_DLLINTERFACE __pragma(warning(disable:4251))
#define MW_WARNING_SUPPRESS_DLLINTERFACE __pragma(warning(suppress:4251))
// disable: non dll-interface class used as base for dll-interface class
#define MW_WARNING_DISABLE_NON_DLLINTERFACE_BASE_CLASS __pragma(warning(disable:4275))
// enable: enumeration value not handled in switch
#define MW_WARNING_ENABLE_ENUM_UNHANDLED_IN_SWITCH __pragma(warning(default:4062))
// disable: assignment operator could not be generated
#define MW_WARNING_DISABLE_ASSIGNMENT_OP_NOT_GENERATED __pragma(warning(disable:4512))
#elif defined(__clang__)
#define MW_WARNING_PUSH _Pragma("clang diagnostic push")
#define MW_WARNING_POP _Pragma("clang diagnostic pop")
#define MW_WARNING_DISABLE_DEPRECATED _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#define MW_WARNING_DISABLE_DLLINTERFACE
#define MW_WARNING_SUPPRESS_DLLINTERFACE
#define MW_WARNING_DISABLE_NON_DLLINTERFACE_BASE_CLASS
#define MW_WARNING_ENABLE_ENUM_UNHANDLED_IN_SWITCH //-WSwitch
#define MW_WARNING_DISABLE_ASSIGNMENT_OP_NOT_GENERATED
#else
#define MW_WARNING_PUSH _Pragma("GCC diagnostic push")
#define MW_WARNING_POP _Pragma("GCC diagnostic pop")
#define MW_WARNING_DISABLE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define MW_WARNING_DISABLE_DLLINTERFACE
#define MW_WARNING_SUPPRESS_DLLINTERFACE
#define MW_WARNING_DISABLE_NON_DLLINTERFACE_BASE_CLASS
#define MW_WARNING_ENABLE_ENUM_UNHANDLED_IN_SWITCH //-WSwitch
#define MW_WARNING_DISABLE_ASSIGNMENT_OP_NOT_GENERATED
#endif


#endif	//	MW_MWWWARNINGPRAGMAS_HPP_
