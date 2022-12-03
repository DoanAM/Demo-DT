// (C) 2007-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DLINEUTILS_HPP_
#define MW_MW2DLINEUTILS_HPP_
#include "mw2dPolyLine.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

//#pragma deprecated(mw2dLineUtils)
/*
Deprecation reasons explained:

Instead of e.g.
mw2dLineUtils<double>::LinesIntersect(line1, line2, intersection);
please use:
std::vector<Point> intersections;
mwIsintersect::Check(line1, line2, intersections);

intersection == intersections[0];
*/

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mw2dLineUtils
{
	typedef mwTPoint2d<T> Point;
	typedef mw2dPolyLine<T> Polyline2d;
	typedef mw2dLine<T> Line;

public:
	enum CutMode
	{
		CM_NO,
		CM_PARTIAL,
		CM_FULL,
		CM_UNDEFINED
	};

	enum LinesIntersectClass
	{
		NO_INTERSECTION,
		INTERSECTION,
		TOUCH_POINT,
		TOUCH_LINE
	};

	enum PointLineClass
	{
		PLC_LEFT,
		PLC_RIGHT,
		PLC_BEYOND,
		PLC_BEHIND,
		PLC_BETWEEN,
		PLC_ORIGIN,
		PLC_DESTINATION
	};


	/// ClassifyPoint
	///
	/// Classify point position against line segment
	///	@param v0 start vertice of segment
	///	@param v1 end vertice of segment
	///	@param pt point to check status of
	/// @param tol tolerance
	///	@return PointLineClass status of point against line
	static PointLineClass ClassifyPoint(
		const Point& v0,
		const Point& v1,
		const Point& pt,
		const T tol = mathdef::mw_tol(T()));


	/// LinesIntersect function
	///
	/// @param seg1 of type const mw2dLine<T> &
	/// @param seg2 of type const mw2dLine<T> &
	/// @param intersectionPnt of type mw2dPoint<T> &
	/// @param tolerance value for comparing two elements
	/// @returns LinesIntersect of type template < class T > bool
	static LinesIntersectClass LinesIntersect(
		const mw2dLine<T>& seg1,
		const mw2dLine<T>& seg2,
		Point& intersectionPnt,
		const T tolerance = 0.0);

	static LinesIntersectClass LineCircleIntersect(
		const mw2dLine<T>& src,
		const typename Point::Ptr& center,
		const T radius,
		T& t1,
		T& t2);

	/// Cuts given line by the given circle.
	/// @param src line to cut
	/// @param center the center of the circle.
	/// @param radius the radius of the circle.
	/// @param l1 ref pointer to the first result of cutting. Null if not exist.
	/// @param l2 ref pointer to the second result of cutting. Null if not exist.
	static CutMode CutCircle(
		const mw2dLine<T>& src,
		const typename Point::Ptr& center,
		const T radius,
		typename mw2dLine<T>::Ptr& l1,
		typename mw2dLine<T>::Ptr& l2);

	/// Cuts given line by the given circle - II, more precious.
	///
	/// Cuts given line by the given circle.
	/// @param src line to cut
	/// @param center the center of the circle.
	/// @param radius the radius of the circle.
	/// @param l1 ref pointer to the first result of cutting. Null if not exist.
	/// @param l2 ref pointer to the second result of cutting. Null if not exist.
	/// @return 0 - no intersection, 1 - partial cut, 2 - line is entirely inside circle
	static int CutCircle2(
		const mw2dLine<T>& src,
		const typename Point::Ptr& center,
		const T radius,
		typename mw2dLine<T>::Ptr& l1,
		typename mw2dLine<T>::Ptr& l2);

	/// Cut given line by given rectangle using Cyrus-Beck clipping
	///
	/// Cuts given line by the given rectangle.
	/// @param src line to cut
	/// @param axle the axle of the rectangle.
	/// @param radius the radius of the rectangle.
	/// @param l1 ref pointer to the first result of cutting. Null if not exist.
	/// @param l2 ref pointer to the second result of cutting. Null if not exist.
	/// @return 0 - no intersection, 1 - partial cut, 2 - line is entirely inside circle
	static CutMode CutRectangle(
		const mw2dLine<T>& src,
		const mw2dLine<T>& axle,
		const T radius,
		typename mw2dLine<T>::Ptr& l1,
		typename mw2dLine<T>::Ptr& l2);
	static CutMode CutTriangle(
		const mw2dLine<T>& src,
		const Point& p1,
		const Point& p2,
		const Point& p3,
		typename mw2dLine<T>::Ptr& l1,
		typename mw2dLine<T>::Ptr& l2);


	static bool GetClosestPoint(
		const Point& point,
		const Line& line,
		Point& witnessPoint,
		T& tValue);

	/// Check if two lines are parallel
	///
	///	@param line1 of type const Line&
	///	@param line2 of type const Line&
	///	@returns true if the lines are parallel
	static bool AreParallel(const Line& line1, const Line& line2);

	/// Check if two lines are parallel
	///
	///	@param firstSource is start point of first line
	///	@param firstTarget is end point of first line
	///	@param secondSource is start point of second line
	///	@param secondTarget is end point of second line
	///	@returns true
	static bool AreParallel(
		const Point& firstSource,
		const Point& firstTarget,
		const Point& secondSource,
		const Point& secondTarget);

private:
	mw2dLineUtils();
};
//#pragma warning(pop)

}  // namespace cadcam
#endif  //	MW_MW2DLINEUTILS_HPP_
