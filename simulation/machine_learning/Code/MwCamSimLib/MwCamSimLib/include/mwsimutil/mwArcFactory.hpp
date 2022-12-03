// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWARCFACTORY_HPP_
#define MW_MWARCFACTORY_HPP_
#include "mw2dArc.hpp"
#include "mwCadcamFwdDecl.hpp"

namespace cadcam
{
/// This class is used to create circular arcs
namespace mwArcFactory
{
template <class T>
typename mw2dArc<T>::Ptr CreateTangent2Lines(
	const mw2dLine<T>& l1,
	const mw2dLine<T>& l2,
	const T radius,
	const T couplingDistance,
	const typename mw2dPoint<T>::Ptr pCen,
	bool directed);

/// Create an arc given directions of start and end radii, radius length, and center point
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dPoint<T>& dir1,
	const mw2dPoint<T>& dir2,
	const T radius,
	const cadcam::mwTPoint2d<T>& pCen);

/// Create an arc given directions of start and end radii, radius length, center point, and angle
/// measure flag
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dPoint<T>& dir1,
	const mw2dPoint<T>& dir2,
	const T radius,
	const mwTPoint2d<T>& pCen,
	const bool isClockwise);

/// Create an arc tangent to given two line segments
///
/// Creates tangent arc to given line segments. If line segments
/// don't intersect, infinite lines intersection point is found and used as arc center
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dLine<T>& l1,
	const mw2dLine<T>& l2,
	const typename mw2dPoint<T>::Ptr pCen = typename cadcam::mw2dPoint<T>::Ptr());

/// Create an arc tangent to a given arc and a given line segment
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dArc<T>& arc,
	const mw2dLine<T>& line,
	const typename mw2dPoint<T>::Ptr pCen = mw2dPoint<T>::Ptr());

/// Create an arc tangent to a given line segment and a given arc
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dLine<T>& line,
	const mw2dArc<T>& arct,
	const typename mw2dPoint<T>::Ptr pCen = mw2dPoint<T>::Ptr());

/// Create an arc tangent to given arcs and a given line segment
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dArc<T>& arc1,
	const mw2dArc<T>& arc2,
	const typename mw2dPoint<T>::Ptr pCen = mw2dPoint<T>::Ptr());

/// Create an arc given start and end points and direction in the end point
template <class T>
typename mw2dArc<T>::Ptr Create(
	const mw2dPoint<T>& p1,
	const mw2dPoint<T>& p2,
	const mw2dPoint<T>& direction2,
	const typename mw2dPoint<T>::Ptr pCen = typename cadcam::mw2dPoint<T>::Ptr());

/// Create 2D arc through 3 points
///
/// @param startPoint start point of an arc
/// @param pointOnArc point on arc between start and end points
/// @param endPoint end point of an arc
template <class T>
MW_5AXUTIL_API typename mw2dArc<T>::Ptr Create2dArcThroughThreePoints(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& pointOnArc,
	const mwTPoint2d<T>& endPoint);

/// Create 3D arc through 3 points. Rotates points to a plane, creates 2d arc, and then rotates it
/// back.
///
/// @param startPoint start point of an arc
/// @param pointOnArc point on arc between start and end points
/// @param endPoint end point of an arc
template <class T>
MW_5AXUTIL_API typename mw3dArc<T>::Ptr Create3dArcThroughThreePoints(
	const mwTPoint3d<T>& startPoint,
	const mwTPoint3d<T>& pointOnArc,
	const mwTPoint3d<T>& endPoint);

/// Create 2D arc through 2 points given the arc height
///
/// @param startPoint start point of an arc
/// @param endPoint end point of an arc
/// @param height perpendicular bisector of [startPoint, endPoint] segment length
template <class T>
MW_5AXUTIL_API typename mw2dArc<T>::Ptr Create2dArcThroughTwoPoints(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& endPoint,
	const T height);  // if height is positive - [(endPoint-startPoint), (circleCenter-midPoint)]
// are positively oriented. negatively otherwise.

/// Create 2D arc through 2 points given the arc height
///
/// @param startPoint start point of an arc
/// @param endPoint end point of an arc
/// @param radius arc radius
/// @param isClockwise arc direction flag
template <class T>
MW_5AXUTIL_API typename mw2dArc<T>::Ptr Create2dArcThroughTwoPoints(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& endPoint,
	const T radius,
	const bool isClockwise);

template <class T>
typename mw2dGeometry<T>::Ptr CreateGeometryThroughThreePoints(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& middlePoint,
	const mwTPoint2d<T>& endPoint);

template <class T>
typename mw2dGeometry<T>::Ptr CreateGeometryThroughThreePoints(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& middlePoint,
	const mwTPoint2d<T>& endPoint,
	const T tolerance);

template <class T>
typename mw3dGeometry<T>::Ptr CreateGeometry3dThroughThreePoints(
	const mwTPoint3d<T>& startPoint,
	const mwTPoint3d<T>& middlePoint,
	const mwTPoint3d<T>& endPoint);

/// Create a 2D arc through 3 points.
/// @returns Null pointer if arc is degenerate. Returns a valid arc otherwise.
template <class T>
typename mw2dArc<T>::Ptr Create2dArcThroughThreePointsSafe(
	const mwTPoint2d<T>& startPoint,
	const mwTPoint2d<T>& pointOnArc,
	const mwTPoint2d<T>& endPoint);

}  // namespace mwArcFactory
}  // namespace cadcam
#endif  //	MW_MWARCFACTORY_HPP_
