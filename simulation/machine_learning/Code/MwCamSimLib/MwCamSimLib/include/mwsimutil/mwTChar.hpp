// (C) 2013-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTCHAR_HPP_
#define MW_MWTCHAR_HPP_
/* WARNING!!! Do not place C++ code in this header, it is used with C files as well */

#ifdef _WIN32
	#include <tchar.h>
#else
	#if defined(UNICODE) || defined (_UNICODE)
		#define _TCHAR wchar_t
		#define _T(x) L##x

		#define _totlower towlower
		#define _totupper towupper
		#define _tcscpy wcscpy
		#define _tcstok_s wcstok
		#define _tcslen wcslen
		#define _tcsstr wcsstr
		#define _tmain wmain
	#else
		#define _TCHAR char
		#define _T(x) x

		#define _totlower tolower
		#define _totupper toupper
		#define _tcscpy strcpy
		#define _tcstok_s strtok_r
		#define _tcslen strlen
		#define _tcsstr strstr
		#define _tmain main
	#endif
	#define TCHAR _TCHAR
#endif
#endif	//	MW_MWTCHAR_HPP_
