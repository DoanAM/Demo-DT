// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMINSQUAREDDISTANCE_HPP_
#define MW_MWMINSQUAREDDISTANCE_HPP_
#include "mwCadcamFwdDecl.hpp"

#include <list>
#include <vector>


namespace cadcam
{
namespace mwMinSquaredDistance
{
/// Get the shortest distance between point and linear segment
///
///	@param[in] point The point to calculate distance from
///	@param[in] segmentSource Start point of segment
///	@param[in] segmentTarget End point of segment
///	@param[out] witnessPointParamOnSegment Closest segment point to the given point
///	@param[out] witnessPointOnsegment Witness parameter in range [0,1] on the segment
///	@returns Shortest distance from point to segment
template <class TPoint>
typename TPoint::ValueType Calculate(
	const TPoint& point,
	const TPoint& segmentSource,
	const TPoint& segmentTarget,
	typename TPoint::ValueType& witnessPointParamOnSegment,
	TPoint& witnessPointOnsegment);

/// Get the shortest distance between point and linear segment
///
///	@param[in] point The point to calculate distance from
///	@param[in] segmentSource Start point of segment
///	@param[in] segmentTarget End point of segment
///	@returns Shortest distance from point to segment
template <class TPoint>
typename TPoint::ValueType CalculateToSegment(
	const TPoint& point, const TPoint& segmentSource, const TPoint& segmentTarget);

/// Get the shortest distance between two geometries
///
///	@param[in] first First geometry
///	@param[in] second Second geometry
///	@returns Shortest distance between two geometries
template <class TGeometry1, class TGeometry2>
typename TGeometry1::ValueType Calculate(const TGeometry1& first, const TGeometry2& second);

/// Get the shortest distance between two geometries
///
///	@param[in] first First geometry
///	@param[in] second Second geometry
///	@param[out] witnessPointOnSecond Closest second geometry point to the first geometry
///	@returns Shortest distance between two geometries
template <class TGeometry1, class TGeometry2, class TPoint>
typename TPoint::ValueType Calculate(
	const TGeometry1& first, const TGeometry2& second, TPoint& witnessPointOnSecond);

/// Get the shortest distance between two geometries
///
///	@param[in] first First geometry
///	@param[in] second Second geometry
///	@param[out] witnessPointParamOnSecond Witness parameter on second geometry
///	@param[out] witnessPointOnSecond Closest second geometry point to the first geometry
///	@returns Shortest distance between two geometries
template <class TGeometry1, class TGeometry2, class TPoint>
typename TGeometry1::ValueType Calculate(
	const TGeometry1& first,
	const TGeometry2& second,
	typename TGeometry1::ValueType& witnessPointParamOnSecond,
	TPoint& witnessPointOnSecond);

/// Get the shortest distance between geometry and contour
///
///	@param[in] first Geometry
///	@param[in] second Contour
///	@param[out] item Closest contour's item to the given geometry
///	@param[out] witnessPointParamOnItem Witness parameter on contour`s item
///	@returns Shortest distance between geometry and contour
template <class TGeometry, class TContour, class TThroughContourIter>
typename TGeometry::ValueType Calculate(
	const TGeometry& first,
	const TContour& second,
	TThroughContourIter& item,
	typename TGeometry::ValueType& witnessPointParamOnItem);


/// Get the shortest distance from point to the closest contour
///
///	@param[in] first The point to calculate distance from
///	@param[in] second Vector of contours
///	@param[out] witnessContourIndex Index of the closest contour to the given point
///	@param[out] witnessPointOnContour Witness point on the closest contour
///	@returns Shortest distance from point to the closest contour
template <class TPoint, class TContour>
typename TPoint::ValueType Calculate(
	const TPoint& first,
	const std::vector<TContour>& second,
	size_t& witnessContourIndex,
	TPoint& witnessPointOnContour);

/// Get the shortest distance from point to the closest contour
///
///	@param[in] first The point to calculate distance from
///	@param[in] second Vector of contours
///	@param[out] witnessContourIndex Index of the closest contour to the given point
///	@param[out] item Iterator to contour's item on which witness point located
///	@param[out] witnessPointParameterOnItem Witness parameter on the closest contour
///	@returns Shortest distance from point to the closest contour
template <class TPoint, class TContour, class TThroughContourIter>
typename TPoint::ValueType Calculate(
	const TPoint& first,
	const std::vector<TContour>& second,
	size_t& witnessContourIndex,
	TThroughContourIter& item,
	typename TPoint::ValueType& witnessPointParameterOnItem);

/// Get the shortest distance between two polylines
///
///	@param[in] first First polyline
///	@param[in] second Second polyline
///	@param[out] witnessPointOnFirst Witness point on first polyline
///	@param[out] witnessPointOnSecond Witness point on second polyline
///	@returns Shortest distance between two polylines
template <class TPolyLine1, class TPolyLine2, class TPoint>
typename TPoint::ValueType Calculate(
	const TPolyLine1& first,
	const TPolyLine2& second,
	TPoint& witnessPointOnFirst,
	TPoint& witnessPointOnSecond);

/// Get the shortest distance between point and line
///
///	@param[in] point The point to calculate distance from
///	@param[in] firstPointOnLine First point on line
///	@param[in] secondPointOnLine Second point on line
///	@param[out] witnessPointParameterOnLine Witness parameter on the line
///	@param[out] witnessPointOnLine Closest line point to the given point
///	@returns Shortest distance from point to line
template <class TPoint>
typename TPoint::ValueType CalculateToLine(
	const TPoint& point,
	const TPoint& firstPointOnLine,
	const TPoint& secondPointOnLine,
	typename TPoint::ValueType& witnessPointParameterOnLine,
	TPoint& witnessPointOnLine);

/// Get the shortest distance between point and line
///
///	@param[in] point The point to calculate distance from
///	@param[in] firstPointOnLine First point on line
///	@param[in] secondPointOnLine Second point on line
///	@returns Shortest distance from point to line
template <class TPoint>
typename TPoint::ValueType CalculateToLine(
	const TPoint& point, const TPoint& firstPointOnLine, const TPoint& secondPointOnLine)
{
	TPoint witnessPointOnLine;
	typename TPoint::ValueType witnessPointParameterOnLine;
	return CalculateToLine<TPoint>(
		point,
		firstPointOnLine,
		secondPointOnLine,
		witnessPointParameterOnLine,
		witnessPointOnLine);
}

/// Get the shortest distance between point and ray
///
///	@param[in] point The point to calculate distance from
///	@param[in] startOfRay Start of ray
///	@param[in] secondPointOnRay Second point on ray
///	@param[out] witnessPointParameterOnRay Witness parameter on the ray
///	@param[out] witnessPointOnRay Closest ray point to the given point
///	@returns Shortest distance from point to ray
template <class TPoint>
typename TPoint::ValueType CalculateToRay(
	const TPoint& point,
	const TPoint& startOfRay,
	const TPoint& secondPointOnRay,
	typename TPoint::ValueType& witnessPointParameterOnRay,
	TPoint& witnessPointOnRay);

/// Get the shortest distance between point and ray
///
///	@param[in] point The point to calculate distance from
///	@param[in] startOfRay Start of ray
///	@param[in] secondPointOnRay Second point on ray
///	@returns Shortest distance from point to ray
template <class TPoint>
typename TPoint::ValueType CalculateToRay(
	const TPoint& point, const TPoint& startOfRay, const TPoint& secondPointOnRay)
{
	TPoint witnessPointOnRay;
	typename TPoint::ValueType witnessPointParameterOnRay;
	return CalculateToRay<TPoint>(
		point, startOfRay, secondPointOnRay, witnessPointParameterOnRay, witnessPointOnRay);
}

/// Get the shortest distance between point and plane
///
///	@param[in] point The point to calculate distance from
///	@param[in] firstPlanePoint First point on plane
///	@param[in] secondPlanePoint Second point on plane
///	@param[in] thirdPlanePoint Third point on plane
///	@returns Shortest distance from point to plane
template <class T>
T CalculateToPlane(
	const mwTPoint3d<T>& point,
	const mwTPoint3d<T>& firstPlanePoint,
	const mwTPoint3d<T>& secondPlanePoint,
	const mwTPoint3d<T>& thirdPlanePoint);

}  // namespace mwMinSquaredDistance
}  // namespace cadcam
#endif  // MW_MWMINSQUAREDDISTANCE_HPP_
