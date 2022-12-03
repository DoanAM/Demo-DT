// (C) 2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWPREPROCESSOR_HPP_
#define MW_MWPREPROCESSOR_HPP_


#define MW_PP_STRINGIZE(X) MW_PP_STRINGIZE_PRIMITIVE(X)
#define MW_PP_STRINGIZE_PRIMITIVE(X) #X


#define MW_PP_CONCAT(A, B) MW_PP_CONCAT_PRIMITIVE(A, B)
#define MW_PP_CONCAT_PRIMITIVE(A, B) A ## B


#endif	// MW_MWPREPROCESSOR_HPP_