// (C) 2003-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

// this header file does not need to have include guards
// as its code must be included/executed every time needed

// This is the new version of providing exp/imp declarations
#ifndef MW_5AXUTIL_API
    #if defined(__APPLE__)
        #define	MW_5AXUTIL_API __attribute__ ((visibility ("default")))
    #else
        #define	MW_5AXUTIL_API
    #endif
#endif

#ifndef MW_5AXMFCUIUTILS_API
    #define	MW_5AXMFCUIUTILS_API __declspec(dllexport)
#endif

// this is used when building the 5axcore project
#ifndef		MW_5AXCORE_API
    #if defined(__APPLE__)
        #define	MW_5AXCORE_API __attribute__ ((visibility ("default")))
    #else
        #define	MW_5AXCORE_API
    #endif
#endif

//#endif //__mwDllImpExpDef_hpp__
