// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVARCCUTSTEPINTERPOLATOR_HPP_
#define MW_MWVARCCUTSTEPINTERPOLATOR_HPP_
#include "mwvArcCutInterpolator.hpp"

namespace VerifierUtil
{
/// Interpolates circular cuts, as defined in @ref VerifierUtil::mwCircularMove, or @ref
/// mwMachSimVerifier::BufferedCircularCut().
class MW_VERIFIER_API mwvArcCutStepInterpolator : private mwvArcCutInterpolator
{
public:
	/// @param maxLength  Maximum distance between two interpolated points
	/// @param errorTolerance  Used to calculate the number of steps for piecewise-linear
	///                        interpolation. Replaces maxStepAngle if != 0.
	/// @param maxStepAngle  maximum angle difference between two interpolated points
	mwvArcCutStepInterpolator(
		const float maxLength,
		const Frame& start,
		const Frame& end,
		const float3d& circleCenter,
		float3d circlePlaneNormal,
		const float errorTolerance,
		const float maxStepAngle = 1);

	/// Returns the next segment and updates the internal step counter.
	bool GetNextStep(Frame& start, Frame& end);

	/// Returns the number of interpolated points.
	size_t GetStepNum() const { return (size_t)m_stepCount; }

private:
	float GetMaxStepAngle(const float errorTolerance, const float maxStepAngle);

	int m_curStep;
	int m_stepCount;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_lastFrame;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVARCCUTSTEPINTERPOLATOR_HPP_
