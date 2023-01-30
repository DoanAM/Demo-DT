// (C) 2008-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DOFFSETTERHELPER_HPP_
#define MW_MW2DOFFSETTERHELPER_HPP_
#include "mw2dLine.hpp"
#include "mw2dMultipleClosedPolyLine.hpp"
#include "mw2dContourDomainSorter.hpp"
#include <vector>

namespace cadcam
{
template <class T>
class MW_5AXUTIL_API mw2dOffsetterHelper
{
public:
	typedef mwTPoint2d<T>						Point2d;
	typedef std::vector<Point2d>				Point2dVec;
	typedef mw2dGeometry<T>						Geometry2d;
	typedef typename mw2dGeometry<T>::Ptr		Geometry2dPtr;
	typedef mw2dPolyLine<T>						Polyline2d;
	typedef std::vector<Polyline2d>				Polyline2dVec;
	typedef mw2dMultipleClosedPolyLine<T>		MultiPolyline2d;
	typedef std::vector<MultiPolyline2d>		MultiPolyline2dVec;
	typedef mw2dContour<T>						Contour2d;
	typedef typename mw2dContour<T>::Ptr		Contour2dPtr;
	typedef std::vector<Contour2d>				Contour2dVec;
	typedef std::vector<Contour2dPtr>			Contour2dPtrVec;

	/// Offset 2d contour outside
	static void OffsetContourOutside(Contour2dVec& contours, const T offsetDistance);

	/// OffsetOutside
	///
	/// Offsets 2d region bounded by contours outside
	static Contour2dVec OffsetOutside(
		const Contour2dVec& contours,
		const T offsetDistance);

	static Contour2dVec DoubleOffset(
		const Contour2dVec& contours,
		const T doubleOffsetDistance);

	/// OffsetOutside
	///
	/// Offset 2d region bounded by contours outside
	///	@param offsetDistance distance to offset, could be negative
	///	@returns vector of contours as a result
	static Contour2dVec OffsetOutside(
		const Polyline2dVec& src,
		const T offsetDistance);

	/// OffsetOutside
	///
	/// Offset a given vector of multiple closed polylines
	///	@param slice is a given vector of multiple closed polylines
	///	@param offset is the length of offset (positive is outward, negative is inward)
	///	@param polygonizationTolerance is a tolerance for offset polygonization
	///	@returns vector of multiple closed polylines as a result
	static MultiPolyline2dVec OffsetOutside(
		const MultiPolyline2dVec& slice,
		const T offset,
		const T polygonizationTolerance);

	/// Offset and Polygonize a given vector of contours
	///
	///	@param src is a given vector of contours
	///	@param offset distance to offset, could be negative
	///	@param polygonizationTolerance is a tolerance for polygonization
	///	@return vector of polylines after offset and polygonization

	static Polyline2dVec OffsetOutside(
		const Contour2dVec& src,
		const T offset,
		const T polygonizationTolerance);

	/// OffsetOutsideAndPolygonize
	///
	/// Offsets 2d region bounded by polygons outside and poligonize result
	static Polyline2dVec OffsetOutside(
		const Polyline2dVec& src,
		const T offset,
		const T polygonizationTolerance);

	template<typename Boundary>
	static Boundary DoubleOffset(
		const Boundary& src,
		const T doubleOffsetDistance,
		const T doubleOffsetTolerance);

	/// OffsetLeft
	///
	/// Offsets 2d region bounded by contours left
	static Contour2dVec OffsetLeft(
		const Contour2dVec& contours,
		const T offsetDistance);

	static Polyline2dVec OffsetLeft(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T polygonizationTolerance);

	static Contour2dVec OffsetLeft(
		const Polyline2dVec& src,
		const T offsetDist);
	
	/// CalcMaxExtensionLengthForSharpCorners
	///
	/// Calculates maximum possible extension length for Sharp Corners
	///	offsetLength = applied offset value;
	///	minAngleDeg = minimum corner angle for sharpening
	static T CalcMaxExtensionLengthForSharpCorners(const T offsetLength, const T minAngleDeg = T(1.0));

	/// OffsetLeft
	///
	/// Offset 2d polylines left
	static Polyline2dVec OffsetLeft(
		const Polyline2dVec& src,
		const T offsetDistance,
		const T polygonizationTolerance);
	
	/// OffsetOutside
	///
	/// Offsets 2d region bounded by contours outside when sharp corners are applied
	static Contour2dVec SharpCornersOffsetContourOutside(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T startAngleDeg,
		const T endAngleDeg,
		const T extensionLength);

	/// OffsetOutside
	///
	/// SharpCornersOffsetContourOutside called with two params pass to
	/// SharpCornersOffsetContourOutside default values
	/// startAngleDeg = 5,
	/// endAngleDeg = 179,
	/// Abs(offsetDistance) / Sin(0.5 degree)));
	/// these values suits to get perfect sharp corners for angles lower than 1 degree
	static Contour2dVec SharpCornersOffsetContourOutside(
		const Contour2dVec& contours,
		const T offsetDistance);

	/// OffsetLeft
	///
	/// Offsets 2d region bounded by contours left when sharp corners are applied
	static Contour2dVec SharpCornersOffsetContourLeft(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T startAngleDeg,
		const T endAngleDeg,
		const T extensionLength,
		const T checkDistance);
};
} // namespace cadcam
#endif	//	MW_MW2DOFFSETTERHELPER_HPP_
