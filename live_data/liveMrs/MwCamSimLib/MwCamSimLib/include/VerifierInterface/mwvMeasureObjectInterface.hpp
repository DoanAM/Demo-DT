// (C) 2020-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Abstract interface for custom measured objects.

#ifndef MW_MWVMEASUREOBJECTINTERFACE_HPP_
#define MW_MWVMEASUREOBJECTINTERFACE_HPP_

#include "mwVerifierNestedEnums.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mw3dGeometryTypedefs.hpp>
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
namespace Measure
{
class MeasuredObjectInterface
{
public:
	virtual ~MeasuredObjectInterface(){};


	/// @return whether the object shape has been modified and needs to be redrawn in depth- and
	/// stencil buffers.
	virtual bool IsModified() const = 0;

	/// Called after the object has been redrawn in depth- and stencil buffers.
	virtual void ResetModified() = 0;


	virtual cadcam::mw3dfBoundingBox GetBoundingBox() const = 0;

	struct CastRayResult
	{
		float distance;
		cadcam::mwPoint3df normal;  ///< normalized
		float maxDeviation;  ///< maximal possible deviation of the determined distance

		inline CastRayResult() {}

		explicit CastRayResult(
			float distance, const cadcam::mwPoint3df& normal, float maxDeviation);
	};
	/// Determines the closest intersection of the specified ray with the stock mesh.
	/// @param [in] origin Position of the ray origin.
	/// @param [in] direction Normalized ray direction.
	/// @param [in] maxDistance Maximal casting distance along the ray.
	/// @param [in] face Specifies the desired face orientation, relative to the ray direction.
	/// @return true if succeed.
	virtual bool CastRay(
		CastRayResult& result,
		const cadcam::mwPoint3df& origin,
		const cadcam::mwPoint3df& direction,
		float maxDistance,
		RayCastFace face = RAYCAST_ANY_FACE) const = 0;

	struct Edge
	{
		cadcam::mw2dfContourPtr contour;
		cadcam::mwHomogenousMatrix transform;
		float maxDeviation;  ///< maximal possible deviation of the determined contour

		cadcam::mw3dfPolyLinePtr trace;  ///< optional

		inline Edge() {}

		explicit Edge(
			const cadcam::mw2dfContourPtr& contour,
			const cadcam::mwHomogenousMatrix& transform,
			float maxDeviation,
			const cadcam::mw3dfPolyLinePtr& trace = NULL);
	};
	/// Traces contour of a closest edge.
	/// @param [in] pos Reference position for the search of a closest contour.
	/// @param [in] minDistance Tolerance of arc fitting, if zero, uses the default.
	/// @return true if succeed.
	virtual bool TraceEdge(
		Edge& edge, const cadcam::mwPoint3df& pos, float minDistance = 0) const = 0;

	struct Section
	{
		cadcam::mw2dfContourPtr contour;
		cadcam::mwHomogenousMatrix transform;
		float maxDeviation;  ///< maximal possible deviation of the determined section

		inline Section() {}

		explicit Section(
			const cadcam::mw2dfContourPtr& contour,
			const cadcam::mwHomogenousMatrix& transform,
			float maxDeviation);
	};
	/// Traces contour on the section-plane, defined by specified @p pos and @p normal.
	/// @param [in] pos Reference position on the section plane for the search of a closest contour.
	/// @param [in] normal Normalized normal of the section plane.
	/// @param [in] minDistance Tolerance of arc fitting, if zero, uses the default.
	/// @return true if succeed.
	virtual bool TraceSection(
		Section& section,
		const cadcam::mwPoint3df& pos,
		const cadcam::mwPoint3df& normal,
		float minDistance = 0) const = 0;

	struct Bitangents
	{
		cadcam::mwPoint3df first;
		cadcam::mwPoint3df second;

		inline Bitangents() : leftBitangent(first), rightBitangent(second) {}

		explicit Bitangents(const cadcam::mwPoint3df& first, const cadcam::mwPoint3df& second);

		/// @deprecated Use first instead.
		// MW_DEPRECATED("Deprecated in 2021.04, use first instead")
		cadcam::mwPoint3df& leftBitangent;

		/// @deprecated Use second instead.
		// MW_DEPRECATED("Deprecated in 2021.04, use second instead")
		cadcam::mwPoint3df& rightBitangent;

		Bitangents& operator=(const Bitangents& other);
	};
	/// Determines the bitangents at the specified @p pos. Called to determine the corner for a
	/// point on an edge.
	/// @return true if succeed.
	virtual bool DetermineBitangents(
		Bitangents& bitangents,
		const cadcam::mwPoint3df& pos,
		const cadcam::mwPoint3df& tangent) const = 0;

	struct Directions
	{
		cadcam::mwPoint3df vertical;  ///< normalized, zero if undefined
		cadcam::mwPoint3df
			curvatureSections[2];  ///< normalized normal of section, zero if undefined

		inline Directions() {}

		explicit Directions(
			const cadcam::mwPoint3df& vertical,
			const cadcam::mwPoint3df& curvatureSection0,
			const cadcam::mwPoint3df& curvatureSection1);
	};
	/// Determines additional directions at the specified @p pos.
	/// @return true if succeed.
	virtual bool DetermineDirections(
		Directions& directions, const cadcam::mwPoint3df& pos) const = 0;


	/// @return position tolerance of object shape.
	virtual float GetPosTolerance() const = 0;

	/// @return tolerace used to polygonize displayed contours.
	virtual float GetPolygonizationTolerance() const = 0;

	/// @return threshold value for measured distances.
	virtual float GetDistanceThreshold() const = 0;
};

inline MeasuredObjectInterface::CastRayResult::CastRayResult(
	float distance, const cadcam::mwPoint3df& normal, float maxDeviation)
	: distance(distance), normal(normal), maxDeviation(maxDeviation)
{
}

inline MeasuredObjectInterface::Edge::Edge(
	const cadcam::mw2dfContourPtr& contour,
	const cadcam::mwHomogenousMatrix& transform,
	float maxDeviation,
	const cadcam::mw3dfPolyLinePtr& trace /*=NULL*/)
	: contour(contour), transform(transform), maxDeviation(maxDeviation), trace(trace)
{
}

inline MeasuredObjectInterface::Section::Section(
	const cadcam::mw2dfContourPtr& contour,
	const cadcam::mwHomogenousMatrix& transform,
	float maxDeviation)
	: contour(contour), transform(transform), maxDeviation(maxDeviation)
{
}

inline MeasuredObjectInterface::Bitangents::Bitangents(
	const cadcam::mwPoint3df& first, const cadcam::mwPoint3df& second)
	: first(first),
	  second(second),
	  leftBitangent(Bitangents::first),
	  rightBitangent(Bitangents::second)
{
}

inline MeasuredObjectInterface::Bitangents& MeasuredObjectInterface::Bitangents::operator=(
	const Bitangents& other)
{
	first = other.first;
	second = other.second;
	return *this;
}

inline MeasuredObjectInterface::Directions::Directions(
	const cadcam::mwPoint3df& vertical,
	const cadcam::mwPoint3df& curvatureSection0,
	const cadcam::mwPoint3df& curvatureSection1)
	: vertical(vertical)
{
	curvatureSections[0] = curvatureSection0;
	curvatureSections[1] = curvatureSection1;
}

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREOBJECTINTERFACE_HPP_
