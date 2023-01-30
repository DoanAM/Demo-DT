// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWMXPDLLIMPEXPDEF_HPP_
#define MW_MWMXPDLLIMPEXPDEF_HPP_
//#############################################################################
#if defined(MWMXP_EXPORTS)
	#if defined(_WIN32)
		#define MWMXP_API __declspec(dllexport)
	#elif (defined(__linux__) || defined(__APPLE__))
		#define MWMXP_API __attribute__ ((visibility ("default")))
	#endif
#else
	#define MWMXP_API 
#endif
//#############################################################################
#endif	//	MW_MWMXPDLLIMPEXPDEF_HPP_
