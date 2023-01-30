// (C) 2014-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSHAREDLIBRARY_HPP_
#define MW_MWSHAREDLIBRARY_HPP_
#include "mwSimUtilDllImpExpDef.hpp"


namespace misc
{
	class mwstring;
}

namespace VerifierUtil
{
	class MW_SIMUTIL_API mwSharedLibrary
	{
	public:
		static void* LoadDLibrary(const misc::mwstring& fileName);
		static void* LoadDLibraryNoThrow(const misc::mwstring& fileName);
		static void FreeDLibrary(void* module);
		static void* GetSymbol(void* module,const char* symbolName);
	};
}
#endif	//	MW_MWSHAREDLIBRARY_HPP_
