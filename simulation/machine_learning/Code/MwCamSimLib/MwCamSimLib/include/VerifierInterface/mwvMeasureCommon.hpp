// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Commonly used types included by all API files.

#ifndef MW_MWVMEASURECOMMON_HPP_
#define MW_MWVMEASURECOMMON_HPP_

#include "mwvMeasureForward.hpp"

#include <map>
#include <mwMiscFwdDecl.hpp>
#include <vector>

namespace VerifierUtil
{
namespace Measure
{
typedef std::map<MeasuredObjectID, misc::mwstring> MeasuredObjectIDnameMap;
typedef std::map<misc::mwstring, MeasuredObjectID> MeasuredObjectNameIDmap;

/// Approaches for measurement the distance between measure-points.
struct DistanceMode
{
	enum Value
	{
		direct,
		featureAligned,
		axisAligned,
	};
};

typedef std::vector<DrawnMeasurement> DrawnMeasurements;

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASURECOMMON_HPP_
