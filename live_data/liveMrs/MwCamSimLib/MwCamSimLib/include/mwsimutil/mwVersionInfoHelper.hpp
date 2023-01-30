// (C) 2014-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWVERSIONINFOHELPER_HPP_
#define MW_MWVERSIONINFOHELPER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"

namespace misc
{
class MW_5AXUTIL_API mwVersionInfoHelper
{
public:
	static int GetDay();
	static int GetMonth();
	static int GetYear();
	static mwstring GetVersionString();
	static int GetRevision();
	static mwstring GetRevisionString();
	static mwstring GetReleaseString();
	static mwstring GetReleaseDotsString();
	static mwstring GetConfiguration();
	static mwstring GetPlatform();
	static bool GetIsDebug();
	static mwstring GetCompiler();
	static mwstring GetCopyright();
};
}
#endif	//	MW_MWVERSIONINFOHELPER_HPP_
