// (C) 2017-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWDEFINES_HPP_
#define MW_MWDEFINES_HPP_
#if defined(_MSC_VER) && _MSC_VER < 1600
#define MW_USE_VS2008_COMPATIBILITY
#endif


#if defined(__LP64__) || defined(_WIN64)
	#ifndef MW_X64
		#define MW_X64
	#endif
#endif

#endif	//	MW_MWDEFINES_HPP_
