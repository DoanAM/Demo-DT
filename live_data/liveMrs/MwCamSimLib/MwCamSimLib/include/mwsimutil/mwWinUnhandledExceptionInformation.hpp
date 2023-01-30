// (C) 2015-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINUNHANDLEDEXCEPTIONINFORMATION_HPP_
#define MW_MWWINUNHANDLEDEXCEPTIONINFORMATION_HPP_
#if defined (_WIN32)
#include "mwString.hpp"
#include <windows.h>

namespace misc
{
	//! this class catch unhandled exceptions just before application crash and display a message box for allowing end user to save his work
	/*! it's doing this at process level, so it catch any unhandled exception at process level
		note that it will overwrite any previous registered handlers (see constructor documentation)
	*/
	class MW_5AXUTIL_API mwProcessLevelCrashHandler
	{
	public:
		//! exceptions type that this class know to handle
		enum CrashType
		{
			MW_SEH_EXCEPTION,
			MW_PURE_FUNCTION_CALL,
			MW_INVALID_PARAMETER,
			MW_NEW_OPERATOR_FAIL
		};
		//! constructor, it's registering the class as handler for the following winappi functions
		/*! SetUnhandledExceptionFilter,_set_purecall_handler,_set_new_handler,_set_invalid_parameter_handler
			This means it will overwrite any handler previous setup at process level for any of the upper functions
		*/
		mwProcessLevelCrashHandler();

	private :
		static void HandleException(const CrashType crashType, const misc::mwstring& details);
		static void __cdecl PureCallHandler();
		static void __cdecl InvalidParameterHandler(const wchar_t* expression,
			const wchar_t* function, const wchar_t* file,
			unsigned int line, uintptr_t pReserved);
		static int __cdecl NewHandler(size_t);
		static LONG WINAPI SehHandler(PEXCEPTION_POINTERS pExceptionPtrs);
	};
	
	MW_5AXUTIL_API void UnhandledExceptionInformation(EXCEPTION_POINTERS * ExceptionInfo, misc::mwstring& cause);
};
#endif
#endif	//	MW_MWWINUNHANDLEDEXCEPTIONINFORMATION_HPP_
