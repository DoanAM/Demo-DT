// (C) 2014 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPROFILEHEALING_HPP_
#define MW_MWTOOLPROFILEHEALING_HPP_
#include "mwSimUtilDllImpExpDef.hpp"


namespace cadcam
{
template <typename T>
class MW_SIMUTIL_API mw2dContour;
template <typename T>
class MW_SIMUTIL_API mw2dPolyLine;
template <typename T>
class MW_SIMUTIL_API mwRevolvedSolidDefinition;
namespace mwToolProfile
{
/// @{
///
/// Heal profile to be used in generic revolved tools.
///    Use this, if your generated profiles throw exceptions
///	when used by mwGenericRevolvedTool. This is usually due to
///	thin spikes in the profile.
bool MW_SIMUTIL_API HealPolyline(mw2dPolyLine<float>& polyline);
bool MW_SIMUTIL_API HealPolyline(mw2dPolyLine<double>& polyline);
bool MW_SIMUTIL_API HealContour(mw2dContour<float>& contour);
bool MW_SIMUTIL_API HealContour(mw2dContour<double>& contour);
bool MW_SIMUTIL_API HealRevolvedSolid(mwRevolvedSolidDefinition<float>& revolvedSolid);
bool MW_SIMUTIL_API HealRevolvedSolid(mwRevolvedSolidDefinition<double>& revolvedSolid);
/// @}
}  // namespace mwToolProfile
}  // namespace cadcam
#endif  //	MW_MWTOOLPROFILEHEALING_HPP_
