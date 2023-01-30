// (C) 2008-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DSELFINTERSECTIONRESOLVER_HPP_
#define MW_MW2DSELFINTERSECTIONRESOLVER_HPP_
#include "mwDllImpExpDef.hpp"

#include <vector>

namespace cadcam
{
namespace mw2dSelfintersectionResolver
{
/// Resolves self intersections for 2dContour
/// First it checks for selfintersections then
/// polygonizes the contour and calls Resolve function for PolyLine
/// Returns resolved contour
template <class ClosedContour>
MW_5AXUTIL_API std::vector<ClosedContour> ResolveContour(
	const std::vector<ClosedContour>& src, const typename ClosedContour::ValueType tolerance);

/// Resolves self intersections for polyline
/// Returns resolved polyline
/// It does not guarantee the complete solution
/// Experience shows that one polyline transforms to one polyline
/// after resolving, but it can be transformed in several
template <class TPolyline>
MW_5AXUTIL_API TPolyline
ResolveSingle(const TPolyline& src, const typename TPolyline::ValueType shiftIntersection);

/// Resolves polyline, returns one or more polylines
template <class TPolyline>
MW_5AXUTIL_API std::vector<TPolyline> Resolve(
	const TPolyline& src, const typename TPolyline::ValueType shiftIntersection);

/// Resolves vector of polylines and returns vector
template <class TPolyline>
MW_5AXUTIL_API std::vector<TPolyline> Resolve(
	const std::vector<TPolyline>& src, const typename TPolyline::ValueType shiftIntersection);

/// Resolves vector of polylines to vector of touching polylines
/// @returns true when result has touching points/lines
template <class TPolyline>
bool ResolveToTouching(const std::vector<TPolyline>& src, std::vector<TPolyline>& res);

/// Tries to move touching points to avoid touching
///
/// @param touchingPolys has to be result of ResolveToTouching
/// @param res - result
/// @param shiftIntersection shift distance
/// @returns true if shift succeeded
template <class TPolyline>
bool TryShift(
	const std::vector<TPolyline>& touchingPolys,
	std::vector<TPolyline>& res,
	const typename TPolyline::ValueType shiftIntersection);
}  // namespace mw2dSelfintersectionResolver
}  // namespace cadcam
#endif  //	MW_MW2DSELFINTERSECTIONRESOLVER_HPP_
