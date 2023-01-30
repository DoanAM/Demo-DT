// (C) 2003-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

/// \file
/// Pure Virtual Functions Macros

#ifndef MW_MWVIRTUALPUREDEF_HPP_
#define MW_MWVIRTUALPUREDEF_HPP_
#include "mwCompilerSettings.hpp"
#include "mwMessageBoxWrapper.hpp"


// macro to avoid unreferenced parameters (C4100)
#define MW_AVOID_WARNING_UNREFERENCED_PARAM(...) { __VA_ARGS__; };

// as it is now
#ifdef STRICT_VIRTUAL_PURE_DEFINITION
#define MW_VIRTUAL_PURE_DEFINITION(...) = 0
#endif

//Throw exception
#ifdef RUNTIME_EXCEPTION_PURE_DEFINITION
#define MW_VIRTUAL_PURE_DEFINITION(R,...) { __VA_ARGS__; MW_EXCEPTION("Must implement pure virtual functions!"); };
#endif

// show messagebox
#ifdef WARNING_DEBUG_RELEASE_VIRTUAL_PURE_DEFINITION
//!Note -> R from macro params is return type of the function, pass it as first parameter always, including void.Check usage sample in mwParamInteractor.hpp
#define MW_VIRTUAL_PURE_DEFINITION(R,...) {misc::detail::mwMessageBox(_T("Must implement pure virtual functions!"), _T("")); __VA_ARGS__; return R();};
#endif

//show messagebox only in debug, ignore in release
#if (defined WARNING_DEBUG_VIRTUAL_PURE_DEFINITION && defined _DEBUG)
//!Note -> R from macro params is return type of the function, pass it as first parameter always, including void.Check usage sample in mwParamInteractor.hpp
#define MW_VIRTUAL_PURE_DEFINITION(R,...) { misc::detail::mwMessageBox(_T("Must implement pure virtual functions!"), _T("")); __VA_ARGS__; return R();};
#elif (defined WARNING_DEBUG_VIRTUAL_PURE_DEFINITION && !defined _DEBUG)
//!Note -> R from macro params is return type of the function, pass it as first parameter always, including void.Check usage sample in mwParamInteractor.hpp
#define MW_VIRTUAL_PURE_DEFINITION(R,...) {__VA_ARGS__; return R();};
#endif

// ignore in debug, ignore in release
#ifdef IGNORE_VIRTUAL_PURE_DEFINITION
//!Note -> R from macro params is return type of the function, pass it as first parameter always, including void.Check usage sample in mwParamInteractor.hpp
#define MW_VIRTUAL_PURE_DEFINITION(R,...) { __VA_ARGS__; return R();};
#endif

#define MW_VIRTUAL_PURE_DEFINITION_SILENT(R,...) { __VA_ARGS__; return R();};
#endif	//	MW_MWVIRTUALPUREDEF_HPP_
