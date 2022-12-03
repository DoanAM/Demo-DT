// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVARCSWEEPCUTSTEPINTERPOLATOR_HPP_
#define MW_MWVARCSWEEPCUTSTEPINTERPOLATOR_HPP_
#include "mwvArcSweepCutInterpolator.hpp"

namespace VerifierUtil
{
/// Interpolates circular sweep cuts, as defined in @ref VerifierUtil::mwCircularSweepMove, or @ref
/// mwMachSimVerifier::BufferedCircularSweepCut().
class MW_VERIFIER_API mwvArcSweepCutStepInterpolator : private mwvArcSweepCutInterpolator
{
public:
	/// @param maxLength  Maximum distance between two interpolated points
	/// @param toolPathTolerance  Used to calculate the number of steps for piecewise-linear
	///                           interpolation. Replaces maxStepAngle if != 0.
	/// @param maxStepAngle  maximum angle difference between two interpolated points
	mwvArcSweepCutStepInterpolator(
		const float maxLength,
		const Frame& start,
		const float sweepAngle,
		const float3d& circleCenter,
		float3d circlePlaneNormal,
		const float heightChange,
		const float radiusChange,
		const float toolPathTolerance,
		const float maxStepAngle,
		bool centerOnLine = false);

	/// Returns the next segment and updates the internal step counter.
	bool GetNextStep(Frame& start, Frame& end);
	bool GetNextStep(Frame& start, float& sweepAngle, float& heightChange, float& radiusChange);

	/// Returns the number of interpolated points.
	size_t GetStepNum() const { return (size_t)m_stepCount; }

	// MW_DEPRECATED("Please use GetStepNum instead.");
	size_t GetStepSize() const { return (size_t)m_stepCount; }

private:
	float GetMaxStepAngle(const float errorTolerance, const float maxStepAngle);

	int m_curStep;
	int m_stepCount;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_lastFrame;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVARCSWEEPCUTSTEPINTERPOLATOR_HPP_
