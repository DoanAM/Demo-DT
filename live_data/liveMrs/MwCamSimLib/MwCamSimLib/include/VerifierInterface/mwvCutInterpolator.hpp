// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVCUTINTERPOLATOR_HPP_
#define MW_MWVCUTINTERPOLATOR_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mwMathUtilitiesDefinitions.hpp>

namespace VerifierUtil
{
/// Base class for cut interpolation
///
/// Cut interpolation can be useful to draw tool paths as the verifier would simulate them.
class MW_VERIFIER_API mwvCutInterpolator
{
public:
	typedef MATH::Frame<float> Frame;
	typedef cadcam::mwTPoint3d<float> float3d;

	/// @returns the tool frame at time parameter `t` (between 0 and 1)
	virtual Frame GetFrame(const float t) const = 0;

	/// @note You're unlikely to need this function.
	///
	/// @returns the velocity vector of a revolved tool at time parameter `t` (between 0 and
	/// 1) for a query point `position` (in world coordinates).
	virtual float3d GetVelocity(const float t, const float3d& position) const = 0;

	/// @returns the length of the entire move
	virtual float GetLength() const = 0;

	static Quaternion InterpolateOrientation(
		const Quaternion& start, const Quaternion& end, const float time);

	virtual ~mwvCutInterpolator() {}
};
}  // namespace VerifierUtil
#endif  //	MW_MWVCUTINTERPOLATOR_HPP_
