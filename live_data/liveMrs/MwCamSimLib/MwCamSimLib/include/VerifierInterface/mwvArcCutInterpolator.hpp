// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVARCCUTINTERPOLATOR_HPP_
#define MW_MWVARCCUTINTERPOLATOR_HPP_
#include "mwVerifierMoves.hpp"
#include "mwvCutInterpolator.hpp"
#include "mwvUtilDefines.hpp"

#include <mwOverrideFinal.hpp>

namespace VerifierUtil
{
/// Interpolates circular cuts, as defined in @ref VerifierUtil::mwCircularMove, or @ref
/// mwMachSimVerifier::BufferedCircularCut().
class MW_VERIFIER_API mwvArcCutInterpolator : public mwvCutInterpolator
{
public:
	mwvArcCutInterpolator(const mwCircularMove& move);
	mwvArcCutInterpolator(
		const Frame& start,
		const Frame& end,
		const float3d& circleCenter,
		float3d circlePlaneNormal);

	/// @returns the tool frame at time step t, with t between 0 and 1.
	Frame GetFrame(const float t) const MW_FINAL;

	float3d GetVelocity(const float t, const float3d& p) const MW_FINAL;

	float GetLength() const MW_FINAL;

	/// @returns the total sweep angle in degree.
	float GetSweepAngle() { return m_angleRad * 360.0f / static_cast<float>(2 * mathdef::MW_PI); }

protected:
#ifndef MW_GENERATE_DOCUMENTATION
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_start;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_end;
	float3d m_circleCenter;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Quaternion m_rotateFromCirclePlane;

	float m_startRadius;
	float m_endRadius;
	float3d m_arcStartVector;
	float3d m_arcEndVector;
	float m_angleRad;
	float2d m_circleStartDirection;
#endif

private:
	void Init(
		const Frame& start,
		const Frame& end,
		const float3d& circleCenter,
		float3d circlePlaneNormal);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVARCCUTINTERPOLATOR_HPP_
