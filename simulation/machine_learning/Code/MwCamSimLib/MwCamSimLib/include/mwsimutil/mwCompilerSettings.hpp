// (C) 2003-2016 by ModuleWorks GmbH
// Owner: ARB Library Structure

/// \file
/// this module sets the compiler settings

#ifndef MW_MWCOMPILERSETTINGS_HPP_
#define MW_MWCOMPILERSETTINGS_HPP_
// The possible compiler setting are:
// STRICT_VIRTUAL_PURE_DEFINITION
// - An exception is thrown at compile time
//
// RUNTIME_EXCEPTION_PURE_DEFINITION
// - An exception is thrown at runtime
//
// WARNING_DEBUG_RELEASE_VIRTUAL_PURE_DEFINITION
// - A message box appears on both debug and release builds
//
// WARNING_DEBUG_VIRTUAL_PURE_DEFINITION
// - Should be default for clients
// - A message box appears only on debug
// - Nothing happens for release
//
// IGNORE_VIRTUAL_PURE_DEFINITION
// - Nothing happens for both debug and release builds
//
// The default is WARNING_DEBUG_VIRTUAL_PURE_DEFINITION
//
// If you want to change the default behavior please comment 
// the default define and uncomment the desired one
//
// MW_EXTERNAL_COMPILER_SETTING
// - compiler setting will be specified in the project settings 

#if !defined(MW_EXTERNAL_COMPILER_SETTING)

#define WARNING_DEBUG_VIRTUAL_PURE_DEFINITION
//#define STRICT_VIRTUAL_PURE_DEFINITION
//#define RUNTIME_EXCEPTION_PURE_DEFINITION
//#define WARNING_DEBUG_RELEASE_VIRTUAL_PURE_DEFINITION
//#define IGNORE_VIRTUAL_PURE_DEFINITION
#endif
#endif	//	MW_MWCOMPILERSETTINGS_HPP_
