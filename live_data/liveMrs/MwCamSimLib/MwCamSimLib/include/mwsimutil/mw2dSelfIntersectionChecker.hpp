// (C) 2009-2014 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DSELFINTERSECTIONCHECKER_HPP_
#define MW_MW2DSELFINTERSECTIONCHECKER_HPP_
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mw2dSelfIntersectionChecker
{
public:
	typedef mw2dPolyLine<T> Polyline2d;
	typedef std::vector<Polyline2d> Polyline2dVec;
	typedef mw2dContour<T> Contour2d;
	typedef std::vector<Contour2d> Contour2dVec;

	///	Checks open or closed contour on self intersection.
	static bool IsSelfintersected(const Contour2d& contour);

	///	Checks set of closed contours on self intersection.
	///
	/// It is hard to define criteria of intersection for set of mixed open and
	///	closed contours. So this method supports only closed contours.
	static bool IsSelfintersected(const Contour2dVec& contours);

	///	Checks single polyline (open polyline) or polygon (closed polyline)
	/// for self intersection.
	static bool IsSelfintersected(const Polyline2d& polyline);

	///	Checks set of polygons (closed polylines) on self-intersection and mutual intersection
	static bool IsSelfintersected(const Polyline2dVec& polygons);

protected:
	/// Checks object (contour, set of contours, polyline, polygon or set of polygons
	///
	///	but not set of open contours or polylines) on self-intersection.

	template <typename Contour2dVecOrPolyline2dVec>
	static bool HasSelfintersection(const Contour2dVecOrPolyline2dVec& objects);

	///	Checks single contour or several contours.
	///
	/// Several open contours are allowed to be connected consequently,
	///	so this case doesn't correspond to mathematical definition of self-intersection.

	template <typename Contour2dVecOrPolyline2dVec>
	static bool HasSelfIntersectionsOnlogn(const Contour2dVecOrPolyline2dVec& objects);

	template <typename Contour2dVecOrPolyline2dVec>
	static bool HasSelfIntersectionsOn2(const Contour2dVecOrPolyline2dVec& objects);
};
}  // namespace cadcam
#endif  //	MW_MW2DSELFINTERSECTIONCHECKER_HPP_
