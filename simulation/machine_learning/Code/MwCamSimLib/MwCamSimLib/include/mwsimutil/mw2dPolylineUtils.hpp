// (C) 2006-2015 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYLINEUTILS_HPP_
#define MW_MW2DPOLYLINEUTILS_HPP_
#include "mw2dPolyLine.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

#include <utility>
#include <vector>


namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mw2dPolyLineUtils
{
public:
	typedef T ValueType;
	typedef mwTPoint2d<T> Point2d;

	typedef mw2dLine<ValueType> Line2d;

	typedef mw2dPolyLine<ValueType> PolyLine2d;
	typedef misc::mwAutoPointer<PolyLine2d> PolyLine2dPtr;
	typedef std::vector<PolyLine2d> PolyLine2dVec;
	typedef std::vector<PolyLine2dVec> PolyLine2dVecVec;
	typedef typename PolyLine2d::LineListConstIt LineListConstIt;
	typedef typename PolyLine2d::PointListIt PointListIt;

	typedef mw2dPolyLine<T> Polygon2d;
	typedef std::vector<Polygon2d> Polygon2dVec;

	typedef std::vector<size_t> PolyPointIndexArray;

	/// If the contour have many crosses then it breaks it down and collects them in the vector
	///    as a open or closed contour. The contours may be disconnected.
	///	@return void
	static void BreakDownPolyIfIntersected(
		const PolyLine2d& poly, PolyLine2dVec& polyGrp, const T tolerance = 0);

	/// Filter and fix closed polyline -
	///    if it is not finished within tolerance- finish it and filter short segment
	///	@param poly polyline to process
	///	@param tolerance tolerance to be used while filtering
	static void FilterPolyLine(PolyLine2d& poly, const T tolerance);

	/// Filter and fix closed polylines in given container
	///    if it is not finished within tolerance- finish it and filter short segment
	///	@param polylines contain items to process
	///	@param tolerance is used while filtering
	static void FilterPolyLines(PolyLine2dVec& polylines, const T tolerance);

	/// RemovePolygonsWithZeroArea
	///
	/// Polygons with zero area are removed from given container
	///	@param polygons contain items to process
	/// @param skipOpenPolygons ignore open polygons?
	///	@return none
	static void RemovePolygonsWithZeroArea(
		Polygon2dVec& polygons, const bool skipOpenPolygons = false);

	static bool IsPointInPoly(
		const PolyLine2dVec& poly, const Point2d& pt, const T tolerance = 0.0);

	/// Checks for convexity a closed polyline
	/// @param polyline of type mw2dPolyLine<T2> - the polyline to be checked
	/// @return true if it is convex, false otherwise
	static const bool IsConvex(const PolyLine2d& polyline);

	/// Converts a mw2dPolyLine<T2> type object to a mw2dPolyLine<T> type object
	///
	/// This is needed as a consequence of always using mwExtrudedSolidDefinitions of type double
	/// regardless of local type T
	/// @param src of type mw2dPolyLine<T2> - the source for the conversion
	/// @return PolyLiny2dPtr pointing to mw2dPolyLine<T> type object, the conversion's destination
	template <typename T2>
	static const PolyLine2dPtr ConvertToOtherType(const mw2dPolyLine<T2>& src);

	/// The Reduce function
	/// implements the worm algorithm, which can be found in the file "WormAlgorithm.pdf".
	/// in the same folder.
	static void Reduce(PolyLine2d& toFilter, const T filterTol);

	/// Rotate polyline around zero by specified angle
	static void RotatePolyLine(PolyLine2d& toRotate, const T degreeAngle);

	/// Group polyline vector to vector of Simply connected polylines vectors.
	static void GroupPolyLinesToSimplyConnectedGroups(
		const PolyLine2dVec& src, PolyLine2dVecVec& res);

	/// Gets so called "spike" points in the polyline which are horizontal (parallel with OX axis)
	///
	/// Such points are invalid in tool profile and we check for their existence and filter them out
	/// if such points are found. A point Pk is considered a spike point if it is located in a Vec
	/// of consecutive points starting with Pi and ending with Pj, all points in interval [Pi,Pj]
	/// have the same Y coordinate (all are at the same height) and X coordinate for Pk point ->
	/// Pk[X] doesn't keep the relation Pi[X] < Pk[X] < Pj[X]
	///	@param poly is 2d polyline to be tested
	///	@return an array of indexes in the polyline for all spike points found
	static const PolyPointIndexArray GetHorizontalSpikePointsIndexes(const PolyLine2d& poly);

	/// Removes so called horizontal "spike" points in the polyline (which are parallel with OX
	/// axis)
	///
	/// Such points are invalid in tool profile and we check for their existence and filter them out
	/// if such points are found. A point Pk is considered a spike point if it is located in a Vec
	/// of consecutive points starting with Pi and ending with Pj, all points in interval [Pi,Pj]
	/// have the same Y coordinate (all are at the same height) and X coordinate for Pk point ->
	/// Pk[X] doesn't keep the relation Pi[X] < Pk[X] < Pj[X]
	///	@param poly is 2d polyline to be filtered
	///	@return true if polyline contained horizontal spike points and these were removed
	///			false if polyline doesn't contain horizontal spike points
	static const bool RemoveHorizontalSpikePoints(PolyLine2d& poly);


private:
	mw2dPolyLineUtils();

	/// Calculates the triangles oriented area
	/// @param pt1 first ordered vertex in triangle
	/// @param pt2 second ordered vertex in triangle
	/// @param pt3 third ordered vertex in triangle
	/// @return the oriented area
	static const T GetTriangleOrientedArea(
		const mw2dPoint<T>& pt1, const mw2dPoint<T>& pt2, const mw2dPoint<T>& pt3)
	{
		return (pt3 - pt2) % (pt1 - pt2);
	}

	static void FindIntersectionOfCurrentElement(
		const PolyLine2d& poly,
		const LineListConstIt& it1,
		LineListConstIt& it2,
		bool& bIntersection,
		T tolerance);
};

template <typename T>
class MW_5AXUTIL_API mw2dPolyLineShortSegmentsFilter
{
public:
	typedef mw2dPolyLine<T> PolyLine2d;
	typedef std::vector<PolyLine2d> PolyLine2dVec;

	/// Eliminate segments that are short enough to neglect them
	///
	///	@param src polyline to filter
	///	@param threshold user-allowed tolerance
	static const PolyLine2d EliminateShortSegments(const PolyLine2d& src, const T threshold);
	static const PolyLine2dVec EliminateShortSegments(const PolyLine2dVec& src, const T threshold);
	static const PolyLine2dVec EliminateScaledShortSegments(const PolyLine2dVec& src);

private:
	mw2dPolyLineShortSegmentsFilter();
};
}  // namespace cadcam
#endif  //	MW_MW2DPOLYLINEUTILS_HPP_
