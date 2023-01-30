// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Declares all the types of geometries that can be measured.

#ifndef MW_MWVMEASUREGEOMETRIES_HPP_
#define MW_MWVMEASUREGEOMETRIES_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw3dPolyLine.hpp>
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
namespace Measure
{
struct MW_VERIFIER_API Geometry
{
	MeasuredObjectID objectID;
	cadcam::mwPoint3df point;
	float maxDeviation;

	explicit Geometry(
		MeasuredObjectID objectID, const cadcam::mwPoint3df& point, float maxDeviation);

	virtual ~Geometry() {}
};

/// Represents a vertex on an edge.
struct MW_VERIFIER_API Vertex : Geometry
{
	explicit Vertex(MeasuredObjectID objectID, const cadcam::mwPoint3df& point, float maxDeviation);
};

struct MW_VERIFIER_API Edge : Geometry
{
	cadcam::mwPoint3df bitangents[2];
	cadcam::mw3dfPolyLine polyline;
	bool startVertex;  ///< is there a vertex at the start
	bool endVertex;  ///< is there a vertex at the end

	explicit Edge(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& leftBitangent,
		const cadcam::mwPoint3df& rightBitangent,
		const cadcam::mw3dfPolyLine& polyline,
		bool startVertex,
		bool endVertex,
		float maxDeviation);
};

// Represents a linear segment of the edge.
struct MW_VERIFIER_API LinearEdge : Edge
{
	cadcam::mwPoint3df direction;  ///< line direction

	explicit LinearEdge(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& direction,
		const cadcam::mwPoint3df& leftBitangent,
		const cadcam::mwPoint3df& rightBitangent,
		const cadcam::mw3dfPolyLine& polyline,
		bool startVertex,
		bool endVertex,
		float maxDeviation);
};

// Represents an arc segment of the edge.
struct MW_VERIFIER_API ArcEdge : Edge
{
	cadcam::mwPoint3df center;
	cadcam::mwPoint3df axis;  ///< axial direction
	cadcam::mwPoint3df start;  ///< radial direction
	float radius;
	float angle;

	explicit ArcEdge(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& center,
		const cadcam::mwPoint3df& axis,
		const cadcam::mwPoint3df& start,
		float radius,
		float angle,
		const cadcam::mwPoint3df& leftBitangent,
		const cadcam::mwPoint3df& rightBitangent,
		const cadcam::mw3dfPolyLine& polyline,
		bool startVertex,
		bool endVertex,
		float maxDeviation);
};

// Represents a point on the surface.
struct MW_VERIFIER_API Surface : Geometry
{
	cadcam::mwPoint3df normal;

	explicit Surface(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& normal,
		float maxDeviation);

	/// @deprecated No longer used.
	// MW_DEPRECATED("No longer used")
	cadcam::mwPoint3df tangent;

	/// @deprecated No longer used.
	// MW_DEPRECATED("No longer used")
	cadcam::mwPoint3df bitangent;

	/// @deprecated No longer used.
	// MW_DEPRECATED("No longer used")
	cadcam::mwPoint3df up;
};

// Represents a point on the axis.
struct MW_VERIFIER_API Axis : Geometry
{
	cadcam::mwPoint3df direction;

	explicit Axis(
		MeasuredObjectID objectID,
		const cadcam::mwPoint3df& point,
		const cadcam::mwPoint3df& direction,
		float maxDeviation);
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREGEOMETRIES_HPP_
