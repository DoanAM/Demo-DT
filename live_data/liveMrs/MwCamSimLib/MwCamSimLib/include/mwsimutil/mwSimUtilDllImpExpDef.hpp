// (C) 2010-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSIMUTILDLLIMPEXPDEF_HPP_
#define MW_MWSIMUTILDLLIMPEXPDEF_HPP_
#ifdef _WIN32
	#if defined(MW_SIMUTIL_DOES_NOT_EXPORT)
		#define MW_SIMUTIL_API
	#elif defined (MW_SIMUTIL_EXPORTS)
		#define		MW_SIMUTIL_API __declspec(dllexport)
	#elif defined(MW_SIMUTIL_IMPORT)
		#define		MW_SIMUTIL_API  __declspec(dllimport)
	#else
		#define MW_SIMUTIL_API
	#endif
#elif defined(__linux__)
	#if defined (MW_SIMUTIL_EXPORTS)
		#define	MW_SIMUTIL_API [[gnu::visibility("default")]]
	#else
		#define MW_SIMUTIL_API
	#endif
#elif defined(__APPLE__)
	#define	MW_SIMUTIL_API __attribute__ ((visibility ("default")))
#endif
#endif	//	MW_MWSIMUTILDLLIMPEXPDEF_HPP_
