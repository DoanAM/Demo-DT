// (C) 2018-2020 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Declares the dimension structures that represent the results of the measurement.

#ifndef MW_MWVMEASUREDIMENSIONS_HPP_
#define MW_MWVMEASUREDIMENSIONS_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw3dPolyLine.hpp>
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
namespace Measure
{
struct MW_VERIFIER_API Distance
{
	struct Segment
	{
		cadcam::mwPoint3df start;
		cadcam::mwPoint3df end;
		float distance;
		bool reliable;

		explicit Segment(
			const cadcam::mwPoint3df& start,
			const cadcam::mwPoint3df& end,
			float distance,
			bool reliable);
	};
	MeasuredObjectID objectID;
	cadcam::mwPoint3df start;
	cadcam::mwPoint3df end;
	std::vector<Segment> segments;
	std::vector<cadcam::mw3dfPolyLine> helpers;
	float maxDeviation;
	DistanceMode::Value mode;

	explicit Distance(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& start,
		const cadcam::mwPoint3df& end,
		const std::vector<Segment>& segments,
		const std::vector<cadcam::mw3dfPolyLine>& helpers,
		float maxDeviation,
		DistanceMode::Value mode);
};

struct MW_VERIFIER_API Corner
{
	MeasuredObjectID objectID;
	cadcam::mwPoint3df point;
	cadcam::mwPoint3df axis;
	cadcam::mwPoint3df leftTangent;
	cadcam::mwPoint3df rightTangent;
	float angle;

	explicit Corner(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& axis,
		const cadcam::mwPoint3df& leftTangent,
		const cadcam::mwPoint3df& rightTangent,
		float angle);
};

struct MW_VERIFIER_API Curvature
{
	struct Arc
	{
		cadcam::mwPoint3df center;
		cadcam::mwPoint3df axis;
		float radius;
		cadcam::mw3dfPolyLine polyline;

		explicit Arc(
			const cadcam::mwPoint3df& center,
			const cadcam::mwPoint3df& axis,
			float radius,
			const cadcam::mw3dfPolyLine& polyline);
	};
	MeasuredObjectID objectID;
	cadcam::mwPoint3df point;
	std::vector<Arc> sectionArcs;
	float maxDeviation;

	explicit Curvature(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const std::vector<Arc>& sectionArcs,
		float maxDeviation);
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREDIMENSIONS_HPP_
