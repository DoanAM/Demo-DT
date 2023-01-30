// (C) 2017-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWHARDWAREINFOHELPER_HPP_
#define MW_MWHARDWAREINFOHELPER_HPP_
#include "mwString.hpp"

namespace misc
{
namespace mwHardwareInfoHelper
{

MW_5AXUTIL_API mwstring GetCpuString();
MW_5AXUTIL_API size_t GetCoresNum();
MW_5AXUTIL_API size_t GetActiveCoresNum();
MW_5AXUTIL_API size_t GetTotalRamInGB();
MW_5AXUTIL_API mwstring GetCachingStatus();


#if defined(_MSC_VER) && _MSC_VER >= 1900 && defined(_M_X64)
#define MW_FPU_FMA3_STATUS_ENABLED
#endif
/*! 
	_get_FMA3_enable defined starting from MS CRT vs2015 x64.
	for other platforms GetFpuFma3Status returns "unknown"
*/
MW_5AXUTIL_API mwstring GetFpuFma3Status();

}  // namespace mwHardwareInfoHelper
}  // namespace misc
#endif	//	MW_MWHARDWAREINFOHELPER_HPP_
