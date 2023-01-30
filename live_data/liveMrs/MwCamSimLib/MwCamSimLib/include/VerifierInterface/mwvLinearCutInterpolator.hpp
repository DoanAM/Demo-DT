// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVLINEARCUTINTERPOLATOR_HPP_
#define MW_MWVLINEARCUTINTERPOLATOR_HPP_
#include "mwVerifierMoves.hpp"
#include "mwvCutInterpolator.hpp"

#include <mwOverrideFinal.hpp>

namespace VerifierUtil
{
/// Interpolates linear cuts, as defined in @ref VerifierUtil::mwLinearMove, or @ref
/// mwMachSimVerifier::BufferedCut().
class MW_VERIFIER_API mwvLinearCutInterpolator : public mwvCutInterpolator
{
public:
	explicit mwvLinearCutInterpolator(const mwLinearMove& move);
	mwvLinearCutInterpolator(const Frame& start, const Frame& end);

	Frame GetFrame(const float t) const MW_FINAL;
	float3d GetVelocity(const float t, const float3d& p) const MW_FINAL;
	float GetLength() const MW_FINAL;

private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_start;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame m_end;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVLINEARCUTINTERPOLATOR_HPP_
