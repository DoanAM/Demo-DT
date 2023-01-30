// (C) 2006-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTARGET_PLATFORM_HPP_
#define MW_MWTARGET_PLATFORM_HPP_
//jumping from 10 to 10 to support further expansion without major rewrites
	#define MW_TARGET_DEFAULT	1
	//MW_TARGET_DEFAULT means leave compiler defaults

	#define MW_TARGET_95		20
	#define MW_TARGET_98		30
	#define MW_TARGET_NT4		40
	#define MW_TARGET_ME		50
	#define MW_TARGET_2000		60
	#define MW_TARGET_XP		70
	#define MW_TARGET_2003		80
	#define MW_TARGET_VISTA		90
	#define MW_TARGET_WIN7		100
	#define MW_TARGET_CE		500	  // is this ever used...

	#ifndef MW_TARGET_PLATFORM
	#ifdef UNDER_CE
		#define MW_TARGET_PLATFORM MW_TARGET_CE
	#else
		#if (_MSC_VER < 1600)     //VC++ 2010
			#define MW_TARGET_PLATFORM MW_TARGET_XP
		#else
			#define MW_TARGET_PLATFORM MW_TARGET_WIN7
		#endif
	#endif

	#endif // MW_TARGET_PLATFORM

	//next one is used to ensure that at least of the followings branches are entered in by the preprocessor
	#undef ENTERED_IN_SOME_BRANCH

	#if MW_TARGET_PLATFORM == MW_TARGET_DEFAULT
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH
	#endif

	#if MW_TARGET_PLATFORM == MW_TARGET_95
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0400

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0400

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0400

		#undef _WIN32_IE
		#define _WIN32_IE 0x0400
	#endif // MW_TARGET_PLATFORM == MW_WIN_95

	#if MW_TARGET_PLATFORM == MW_TARGET_98
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0410

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0410

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0410

		#undef _WIN32_IE
		#define _WIN32_IE 0x0410
	#endif // MW_TARGET_PLATFORM == MW_TARGET_98

	#if MW_TARGET_PLATFORM == MW_TARGET_NT4
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0400

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0400

		#undef _WIN32_WINDOWS
		//#define _WIN32_WINDOWS 0x0400

		#undef _WIN32_IE
		#define _WIN32_IE 0x0400
	#endif // MW_TARGET_PLATFORM == MW_TARGET_NT4

	#if MW_TARGET_PLATFORM == MW_TARGET_ME
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0500

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0410

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0500

		#undef _WIN32_IE
		#define _WIN32_IE 0x0500
	#endif // MW_TARGET_PLATFORM == MW_TARGET_ME

	#if MW_TARGET_PLATFORM == MW_TARGET_2000
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0500

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0500

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0500

		#undef _WIN32_IE
		#define _WIN32_IE 0x0500
	#endif // MW_TARGET_PLATFORM == MW_TARGET_2000

	#if MW_TARGET_PLATFORM == MW_TARGET_XP
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0501

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0501

		#undef _WIN32_IE
		#define _WIN32_IE 0x0600
	#endif // MW_TARGET_PLATFORM == MW_TARGET_XP

	#if MW_TARGET_PLATFORM == MW_TARGET_2003
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0502

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0502

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0502

		#undef _WIN32_IE
		#define _WIN32_IE 0x0600
	#endif // MW_TARGET_PLATFORM == MW_TARGET_2003

	#if MW_TARGET_PLATFORM == MW_TARGET_VISTA
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
			ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0600

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0600

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0600

		#undef _WIN32_IE
		#define _WIN32_IE 0x0700
	#endif // MW_TARGET_PLATFORM == MW_TARGET_VISTA

	#if MW_TARGET_PLATFORM == MW_TARGET_WIN7
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
					ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER 0x0601

		#undef _WIN32_WINNT
		#define _WIN32_WINNT 0x0601

		#undef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0601

		#undef _WIN32_IE
		#define _WIN32_IE 0x0900
	#endif //MW_TARGET_PLATFORM == MW_TARGET_WIN7
	
	#if MW_TARGET_PLATFORM == MW_TARGET_CE
		#ifdef ENTERED_IN_SOME_BRANCH
		#pragma message ("error in preprocessor code. please revisit")
							ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT;
		#endif
		#define ENTERED_IN_SOME_BRANCH

		#undef WINVER
		#define WINVER _WIN32_WCE
	#endif //MW_TARGET_PLATFORM == MW_TARGET_CE


	#ifndef ENTERED_IN_SOME_BRANCH
	#pragma message ("error in preprocessor code. please revisit. no branch entered")
		ERROR_IN_PREPROCESSOR_CODE_PLEASE_REVISIT_NO_BRANCH_ENTERED;
	#endif


    #if defined(__linux__) || defined(__APPLE__)
        #define DO_PRAGMA(x) _Pragma (#x)
        #define MW_TODO(x) DO_PRAGMA(message ("TODO - " #x))
    #else
        #define MW_TODO(x) ""
    #endif

#if defined __GNUC__
#define MW_HAS_LONG_LONG
#elif defined _MSC_VER
#if (_MSC_VER >= 1310) && (defined(_MSC_EXTENSIONS) || (_MSC_VER >= 1400))
#   define MW_HAS_LONG_LONG
#else
#   define MW_NO_LONG_LONG
#endif
#endif
#endif	//	MW_MWTARGET_PLATFORM_HPP_
