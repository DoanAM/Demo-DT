// (C) 2013 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVMEASUREMENTPOINT_HPP_
#define MW_MWVMEASUREMENTPOINT_HPP_
#include "mwvLabel.hpp"

namespace VerifierUtil
{
struct mwvMeasurementPoint : public mwvLabel
{
	float3d vert;
	float3d norm;
	float devi;
	bool deviationValid;
	float moveID;
	int partID;
	bool partIDValid;
	int toolID;
	int targetID;
	bool colliding;
	bool moveIndexValid;

	mwvMeasurementPoint() : devi(0){};
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMEASUREMENTPOINT_HPP_
