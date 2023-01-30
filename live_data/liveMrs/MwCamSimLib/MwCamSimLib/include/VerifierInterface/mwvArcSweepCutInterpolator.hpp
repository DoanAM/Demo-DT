// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVARCSWEEPCUTINTERPOLATOR_HPP_
#define MW_MWVARCSWEEPCUTINTERPOLATOR_HPP_
#include "mwVerifierMoves.hpp"
#include "mwvCutInterpolator.hpp"
#include "mwvUtilDefines.hpp"

#include <mwOverrideFinal.hpp>

namespace VerifierUtil
{
/// Interpolates circular sweep cuts, as defined in @ref VerifierUtil::mwCircularSweepMove, or @ref
/// mwMachSimVerifier::BufferedCircularSweepCut().
class MW_VERIFIER_API mwvArcSweepCutInterpolator : public mwvCutInterpolator
{
public:
	mwvArcSweepCutInterpolator(const mwCircularSweepMove& move);
	mwvArcSweepCutInterpolator(
		const Frame& start,
		const float sweepAngle,
		const float3d circleCenter,
		const float3d circlePlaneNormal,
		const float heightChange,
		const float radiusChange,
		const bool centerOnLine =
			false  ///< If true, the circleCenter can be on an orthogonal line through the center.
	);

	Frame GetFrame(const float t) const MW_FINAL;

	float3d GetVelocity(const float t, const float3d& p) const MW_FINAL;

	float GetLength() const MW_FINAL;

protected:
#ifndef MW_GENERATE_DOCUMENTATION
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_start;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_end;
	float3d m_circleCenter;
	float m_sweepAngle;
	float m_length;

	float m_heightChange;
	float m_radiusChange;
	float3d m_circlePlaneNormal;
#endif

private:
	void Init(const mwCircularSweepMove& move, const bool centerOnLine);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVARCSWEEPCUTINTERPOLATOR_HPP_
