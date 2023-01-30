// (C) 2013 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVLABEL_HPP_
#define MW_MWVLABEL_HPP_
#include "mwvUtilDefines.hpp"

namespace VerifierUtil
{
struct mwvLabel
{
	float3d minWindowCoordinates;
	float3d maxWindowCoordinates;
	float3d labeloffset;

	mwvLabel() : labeloffset(0, 0, 0){};
};
}  // namespace VerifierUtil
#endif  //	MW_MWVLABEL_HPP_
