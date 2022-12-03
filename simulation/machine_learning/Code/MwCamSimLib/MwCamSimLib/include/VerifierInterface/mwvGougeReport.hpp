// (C) 2013-2015 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVGOUGEREPORT_HPP_
#define MW_MWVGOUGEREPORT_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwvLabel.hpp"

namespace VerifierUtil
{
struct mwvGougeReport : public mwvLabel
{
	mwMachSimVerifier::GougeReport report;

	float3d normal;
	float pinLength;

	bool active;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVGOUGEREPORT_HPP_
