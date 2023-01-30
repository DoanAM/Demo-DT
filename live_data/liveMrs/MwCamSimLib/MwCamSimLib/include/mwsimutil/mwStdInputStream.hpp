// (C) 2003-2022 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTDINPUTSTREAM_HPP_
#define MW_MWSTDINPUTSTREAM_HPP_
#include "mwBinInputStreamAdapter.hpp"
#include "mwDeprecated.hpp"


namespace misc
{
MW_DEPRECATED("Deprecated since 2022.04, please use misc::mwBinInputStreamAdapter.")
typedef mwBinInputStreamAdapter mwStdInputStream;
#pragma deprecated(mwStdInputStream)  // For MSVC < 2017
}  // namespace misc
#endif  //	MW_MWSTDINPUTSTREAM_HPP_
