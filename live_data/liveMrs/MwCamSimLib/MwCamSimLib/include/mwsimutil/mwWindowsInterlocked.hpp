// (C) 2014-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINDOWSINTERLOCKED_HPP_
#define MW_MWWINDOWSINTERLOCKED_HPP_
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"



namespace misc
{
namespace detail
{
class MW_5AXUTIL_API WindowsInterlocked
{
public:
	static	long  mwInterlockedIncrement(long volatile* pn);
	static	long  mwInterlockedDecrement(long volatile* pn);
	static long  mwInterlockedExchange(long volatile*, long);
	static long  mwInterlockedExchangeAdd(long volatile*, long);
	static long  mwInterlockedCompareExchange(long volatile*, long, long);
	static void  mwSwitchToThread(void);
};
}

MW_DEPRECATED("Deprecated since 2021.12, please use the atomic facilities from the STL or boost.")
typedef detail::WindowsInterlocked WindowsInterlocked;

}
#endif	//	MW_MWWINDOWSINTERLOCKED_HPP_
