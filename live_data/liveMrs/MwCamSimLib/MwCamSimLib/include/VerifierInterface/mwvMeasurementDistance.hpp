// (C) 2013 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVMEASUREMENTDISTANCE_HPP_
#define MW_MWVMEASUREMENTDISTANCE_HPP_
#include "mwvLabel.hpp"

namespace VerifierUtil
{
struct mwvMeasurementDistance : public mwvLabel
{
	float3d pointA;
	float3d pointB;
	float3d normal;
	float deviA;
	float deviB;
	float distance;
	float pinLength;

	mwvMeasurementDistance() : distance(0){};
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMEASUREMENTDISTANCE_HPP_
