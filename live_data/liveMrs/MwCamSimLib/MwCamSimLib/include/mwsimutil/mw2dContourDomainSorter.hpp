// (C) 2003-2014 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DCONTOURDOMAINSORTER_HPP_
#define MW_MW2DCONTOURDOMAINSORTER_HPP_
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
/// allows domain sorting of contours
template <typename T>
class MW_5AXUTIL_API mw2dContourDomainSorter
{
public:
	typedef mw2dContour<T> Contour2d;
	typedef mw2dGeometry<T> Geometry2d;
	typedef typename Contour2d::ItemListIt ItemListIt;
	typedef typename mw2dPolyLine<T>::Ptr Polyline2dPtr;
	typedef typename Contour2d::Ptr Contour2dPtr;

	/// Polygonize contours, rearrange them and connect them such as to create one continuous
	/// polyline
	///   @param src contour to process
	///   @param tolerance tolerance of polygonization
	///   @param connectionTol minimal distance withing which the geometries are considered
	///   connected
	///   @return the continuous polyline
	static const Polyline2dPtr GetContinuousPolyline(
		const Contour2d& src, const T tolerance, const T connectionTol = 1e-5);

	/// Get continuous contours from given contour
	///
	/// Extracts continuous contours from (non-continuous) given one based on tolerance
	///	@param geometries array of geometries represented as Contour2d to search continuous contours in
	///	@param connectionTolerance connection tolerance
	///	@return contours successfully connected
	static std::vector<Contour2d> GetContinuousContours(
		const Contour2d& geometries, const T connectionTolerance);

	/// Calculates connection tolerance for GetContinuousContours based world size 
	/// (square [-worldSize, worldSize]^2)
	static T CalculateConnectionTolerance(const T& worldSize);

	/// Calculates connection tolerance for GetContinuousContours based on set of geometries
	static T CalculateConnectionTolerance(const mw2dContour<T>& geometries);

	/// Calculates connection tolerance for GetContinuousContours based on set of geometries
	static T CalculateConnectionTolerance(const std::vector<Contour2d>& geometries);

	/// Calculates connection tolerance for GetContinuousContours based on set of geometries
	static T CalculateConnectionTolerance(const std::vector<mw2dPolyLine<T>>& geometries);

private:
	typedef mwTPoint2d<T> Point2d;
	typedef typename cadcam::mw2dGeometry<T>::Ptr Geometry2dPtr;

	static std::vector<Contour2d> StabilizeAndAddContoursToResult(
		const std::vector<Contour2d>& toAdd, const T isClosedTolerance);

	/// Constructor not allowed since it's a static class
	mw2dContourDomainSorter();
};
}  // namespace cadcam
#endif  //	MW_MW2DCONTOURDOMAINSORTER_HPP_
