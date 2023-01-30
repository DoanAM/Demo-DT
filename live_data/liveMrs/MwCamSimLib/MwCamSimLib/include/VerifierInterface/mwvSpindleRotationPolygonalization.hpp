// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSPINDLEROTATIONPOLYGONALIZATION_HPP_
#define MW_MWVSPINDLEROTATIONPOLYGONALIZATION_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierNestedEnums.hpp"

#include <mw3dPolyLine.hpp>
#include <mwMathUtilities.hpp>
#include <mwTPoint3d.hpp>

namespace Verifier
{
/// polygonize a general arc-curve, which can be helix-like and have non-constant radius
class MW_VERIFIER_API mwvSpindleRotationPolygonalization
{
public:
	typedef std::vector<MATH::Frame<float>> Polygonization;
	typedef cadcam::mwTPoint3d<float> float3d;

	static void Polygonize(
		const float3d& start,
		const float3d& end,
		const MATH::Quaternion<float>& startOrientation,
		const MATH::Quaternion<float>& endOrientation,
		VerifierUtil::StockSpindleAxis spindleAxis,
		float spindleStart,
		float spindleEnd,
		float maxAngleDegree,
		Polygonization& result);
};

}  // namespace Verifier
#endif  //	MW_MWVSPINDLEROTATIONPOLYGONALIZATION_HPP_
