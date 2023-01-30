// (C) 2011-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVARCCUTPOLYGONALIZATION_HPP_
#define MW_MWVARCCUTPOLYGONALIZATION_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mw3dPolyLine.hpp>
#include <mwTPoint3d.hpp>

namespace Verifier
{
/// polygonize a general arc-curve, which can be helix-like and have non-constant radius
// TODO: can we maybe unify this with mwvCircleInterpolation?
class MW_VERIFIER_API mwvArcCutPolygonalization
{
public:
	typedef cadcam::mwTPoint3d<float> float3d;
	typedef cadcam::mw3dPolyLine<float> PolyLine;

	static void Polygonize(
		const float3d& start,
		const float3d& end,
		float sweepNormal,
		const float3d& circleCenter,
		float3d circlePlaneNormal,
		const float maxAngleDegree,
		PolyLine& result);
};

}  // namespace Verifier
#endif  //	MW_MWVARCCUTPOLYGONALIZATION_HPP_
