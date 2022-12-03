// (C) 2014-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWINTERLOCKOPERATION_HPP_
#define MW_MWINTERLOCKOPERATION_HPP_

#pragma message ("Warning: please don't include mwInterlockOperation.hpp, it is deprecated and will be removed")

#include "mwDeprecated.hpp"
#include "mwWindowsInterlocked.hpp"

namespace misc
{
template<class T>
class MW_DEPRECATED("Deprecated since 2021.12, please use the atomic facilities from the STL or boost.") mwInterlockOperation : public T
{
};

typedef mwInterlockOperation<WindowsInterlocked> mwInterlocked;

}  // namespace misc
#endif	//	MW_MWINTERLOCKOPERATION_HPP_
