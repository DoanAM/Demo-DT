// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef __mwAvoid_Warnings_hpp__
#define __mwAvoid_Warnings_hpp__

#ifdef _MSC_VER

#if defined(MW_IGNORE_GL) || defined(MW_NO_GL) || defined(_NO_GUI)
#pragma warning(disable : 4100)  // Ignoring "unreferenced formal parameter" for mwGLFunctions.hpp
#pragma warning(disable : 4702)  // Ignoring "unreachable code"
#pragma warning(disable : 4722)  // Ignoring "destructor never returns"
#endif

#ifdef MW_EXPORTING_STL
#pragma warning(disable : 4251)  // needs to have dll-interface to be used by clients of exported class
#endif

#ifdef MW_USING_SHARED_DLL
#pragma warning(disable : 4275)  // non dll-interface class used as base for dll-interface class
#pragma warning(disable : 4251)  // needs to have dll-interface to be used by clients of exported class
#endif

#if _MSC_VER >= 1800
#ifndef NO_WARN_MBCS_MFC_DEPRECATION
#define NO_WARN_MBCS_MFC_DEPRECATION
#endif
#endif
//

#if _MSC_VER >= 1600
// avoid deprecated warning for SECURE_SCL_THROWS
#ifndef _SILENCE_DEPRECATION_OF_SECURE_SCL_THROWS
#define _SILENCE_DEPRECATION_OF_SECURE_SCL_THROWS
#endif

#endif

#elif defined(__linux__) || defined(__APPLE__)
#define BOOST_NO_AUTO_PTR
#endif

#define MW_NULL 0

#endif  //__mwAvoid_Warnings_hpp__
