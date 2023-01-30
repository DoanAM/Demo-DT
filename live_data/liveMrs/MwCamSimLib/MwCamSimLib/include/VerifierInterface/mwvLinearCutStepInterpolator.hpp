// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVLINEARCUTSTEPINTERPOLATOR_HPP_
#define MW_MWVLINEARCUTSTEPINTERPOLATOR_HPP_
#include "mwvLinearCutInterpolator.hpp"

namespace VerifierUtil
{
/// Interpolates linear cuts, as defined in @ref VerifierUtil::mwLinearMove, or @ref
/// mwMachSimVerifier::BufferedCut().
class MW_VERIFIER_API mwvLinearCutStepInterpolator : private mwvLinearCutInterpolator
{
public:
	/// @param maxLength  Maximum distance between two interpolated points
	mwvLinearCutStepInterpolator(const float maxLength, const Frame& start, const Frame& end);

	/// Returns the next point and updates the internal step counter.
	bool GetNextStep(Frame& start, Frame& end);

	/// Returns the number of interpolated points.
	size_t GetStepNum() const { return (size_t)(m_stepCount); }

private:
	int m_curStep;
	int m_stepCount;
	Frame m_lastFrame;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVLINEARCUTSTEPINTERPOLATOR_HPP_
