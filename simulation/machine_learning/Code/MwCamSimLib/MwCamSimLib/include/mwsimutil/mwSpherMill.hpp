// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWSPHERMILL_HPP_
#define MW_MWSPHERMILL_HPP_
#include "mwDeprecated.hpp"
#include "mwSphereMill.hpp"

#ifdef _MSC_VER
#pragma message( \
	"Deprecated since 2020.12. Please include mwSphereMill.hpp instead of mwSpherMill.hpp")
#endif

namespace cadcam
{
MW_DEPRECATED("Deprecated since 2020.12. Please use mwSphereMill instead of mwSpherMill")
typedef mwSphereMill mwSpherMill;
}  // namespace cadcam

#endif  //	MW_MWSPHERMILL_HPP_
