// (C) 2018 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVENGAGEMENTHELPERS_HPP_
#define MW_MWVENGAGEMENTHELPERS_HPP_
#include "mwVerifierMoves.hpp"

#include <mwAutoPointer.hpp>
#include <mwCadcamFwdDecl.hpp>
#include <mwMathUtilitiesDefinitions.hpp>
#include <mwTPoint2d.hpp>
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
namespace mwvEngagementHelpers
{
typedef cadcam::mw2dPolyLine<double> EngagementProfile;
typedef misc::mwAutoPointer<const EngagementProfile> EngagementProfilePtr;
typedef cadcam::mw2dBoundingBox<float> EngagementBox;
typedef std::vector<EngagementBox> EngagementBoxList;
typedef std::vector<EngagementBoxList> EngagementBoxListList;

/*
COORDINATE SYSTEMS

In engagement we use different coordinate systems.

World system: coordinate system of the stock.
	* tool tip: position specified in the Cut APIs.
	* tool orientation: specified in the Cut APIs.

Tool system: local coordinate system of the tool
	* tool tip: located at (0, 0, 0)
	* tool orientation: identity quaternion (the tool's revolution axis is Z)

Tool profile system: 2d coordinate system of the tool profile
	To convert the 2d system to a 3d system the profile is revolved around the y axis.
	The y axis is then mapped to the tool's revolution axis (Z axis in 3d).
	* x: distance from the tool's revolution axis
	* y: height on the tool, starting from the tip at y=0

Feed system:
	* tool tip: located at (0, 0, 0)
	* tool orientation: Z axis is unchanged, X axis points into move direction

The engagement angles and -boxes are specified in the feed system. You can use the helper methods
below to transform them to the world system.
*/

MW_VERIFIER_API Frame::Quaternion GetFeedToToolTransformation(const mwLinearMove& move);

MW_VERIFIER_API Frame GetFeedToWorldTransformation(const mwLinearMove& move);

MW_VERIFIER_API cadcam::mwPoint2df GetPositionOnToolProfile(
	const float profileParameter, const size_t sliceIndex, const EngagementProfile& toolProfile);

MW_VERIFIER_API cadcam::mwPoint3df GetPositionInFeedSystem(
	const float angle, const cadcam::mwPoint2df& positionOnToolProfile);

// This function is only partially implemented. You will get triangles for the engaging area, but
// none for the non-engaging tool surface.
MW_VERIFIER_API void TriangulateInFeedSystem(
	const EngagementBoxListList& engagementBoxes,
	const EngagementProfile& toolProfile,
	const int radialSteps,  //< number of interpolated points in revolution direction
	cadcam::mwTMesh<float>& engagingToolSurface,
	cadcam::mwTMesh<float>& nonEngagingToolSurface);

}  // namespace mwvEngagementHelpers
}  // namespace VerifierUtil
#endif  //	MW_MWVENGAGEMENTHELPERS_HPP_
