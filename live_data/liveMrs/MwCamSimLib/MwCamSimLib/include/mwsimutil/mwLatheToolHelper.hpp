// (C) 2009-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWLATHETOOLHELPER_HPP_
#define MW_MWLATHETOOLHELPER_HPP_
#include "mwDeprecated.hpp"
#include "mwGenericExtrudedToolHelper.hpp"


#pragma deprecated(mwLatheToolHelper)

/*
Deprecation reasons explained:
Instead of e.g.
	mwLatheToolHelper<T>
please use:
	mwGenericExtrudedToolHelper<T>;
*/


namespace cadcam
{
#pragma warning(push)
#pragma warning(disable : 4995)

template <typename T>
class MW_DEPRECATED("Deprecated in 2014.04. Please use mwGenericExtrudedToolHelper instead.")
	mwLatheToolHelper: public mwGenericExtrudedToolHelper<T>
{
};

#pragma warning(pop)

}  // namespace cadcam
#endif  //	MW_MWLATHETOOLHELPER_HPP_
