// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWALIGNMENTDEFS_HPP_
#define MW_MWALIGNMENTDEFS_HPP_
// alignment macros
    #ifndef MW_ALIGN
        #ifdef _WIN32
            #define MW_ALIGN(X) __declspec(align(X))
        #elif (defined(__linux__) || defined(__APPLE__)) && defined(__GNUC__)
            #define MW_ALIGN(X) __attribute__((aligned(X)))
        #else
            #define MW_ALIGN(X) "ERROR: Unable to define alignment for this platform"
        #endif

        #define MW_ALIGN8  MW_ALIGN(8)
        #define MW_ALIGN16 MW_ALIGN(16)
        #define MW_ALIGN32 MW_ALIGN(32)
    #endif
    // alignment macros - end
#endif	//	MW_MWALIGNMENTDEFS_HPP_
