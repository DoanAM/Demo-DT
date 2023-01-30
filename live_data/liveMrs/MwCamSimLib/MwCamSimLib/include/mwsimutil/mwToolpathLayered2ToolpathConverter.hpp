// (C) 2014-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHLAYERED2TOOLPATHCONVERTER_HPP_
#define MW_MWTOOLPATHLAYERED2TOOLPATHCONVERTER_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMiscFwdDecl.hpp"

namespace interact
{
class mwUpdateHandlerExecutant;
}

namespace cadcam
{
class mwToolPath;
class mwToolpathLayered;

namespace mwToolpathLayered2ToolpathConverter
{
/// Converts new layered toolpath to old one
///
///	@param src is the a toolpath layered object to be converted.
///	@param tolerance is used to create Helix fits.
///	@param uh is update handler to show converting progress.
///	@return mwToolPath object.
MW_5AXUTIL_API mwToolPath Convert(
	const mwToolpathLayered& src,
	const double tolerance,
	misc::mwAutoPointer<interact::mwUpdateHandlerExecutant> uh =
		misc::mwAutoPointer<interact::mwUpdateHandlerExecutant>());
}  // namespace mwToolpathLayered2ToolpathConverter
}  // namespace cadcam
#endif  //	MW_MWTOOLPATHLAYERED2TOOLPATHCONVERTER_HPP_
