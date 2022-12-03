// (C) 2009-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPOLYLINEARCFITTER_HPP_
#define MW_MWPOLYLINEARCFITTER_HPP_
#include "mw2dContour.hpp"
#include "mw2dPolyLine.hpp"
#include "mw3dContour.hpp"
#include "mw3dPolyLine.hpp"

#include <vector>

namespace cadcam
{
/// @if internal
/// @deprecated Kept for Backward compatibility. For better functionality see @ref mwContourArcFitter.
/// @else
/// @deprecated Kept for Backward compatibility.
/// @endif
class MW_5AXUTIL_API mwPolyLineArcFitter
{
public:
	/// @hidden
	typedef mwTPoint2d<double> TPoint2d;
	/// @hidden
	typedef mwTPoint3d<double> TPoint3d;
	/// @hidden
	typedef mw2dPolyLine<double> Polyline2d;
	/// @hidden
	typedef mw3dPolyLine<double> Polyline3d;
	/// @hidden
	typedef mw2dContour<double> Contour2d;
	/// @hidden
	typedef mw3dContour<double> Contour3d;
	/// @hidden
	typedef Polyline2d::PointListConstIt Point2dConstIterator;
	/// @hidden
	typedef Polyline3d::PointListConstIt Point3dConstIterator;

	mwPolyLineArcFitter(): m_maxRadius(1000), m_isFittingLineAllowed(true) {}

	/// @param maxRadius is maximum allowed radius for fit arcs
	explicit mwPolyLineArcFitter(const double maxRadius)
		: m_maxRadius(maxRadius), m_isFittingLineAllowed(true)
	{
	}

	/// @deprecated Arc fitter will always fit lines.
	MW_DEPRECATED("Deprecated Arc fitter will always fit lines")
	void SetFittingLineAllowedFlg(const bool toSet);

	/// @deprecated Arc fitter will always fit lines.
	MW_DEPRECATED("Deprecated Arc fitter will always fit lines")
	bool GetFittingLineAllowedFlg() const;

	/// @name Arc fitting
	/// @{
	/// Create a contour with arcs and lines approximated to given polyline
	/// @param tolerance Maximum allowed deviation from resulting contour to source polyline and
	/// vice versa.
	/// @throws misc::mwException if the fit is numerically unsable (ratio of largest to smallest
	/// geometry is too small).
	Contour2d::Ptr Fit2dPolyline(const Polyline2d& src, const double tolerance) const;

	Contour2d::Ptr Fit2dPolyline(const Contour2d& src, const double tolerance) const;
	/// @}

	/// Create a self-intersection free contour with arcs and lines approximated to given polyline.
	/// @param src polyline to arc-fit
	/// @param tolerance Maximum allowed deviation from resulting contour to source contour and vice
	/// versa.
	std::vector<Contour2d> Fit2dPolylineToNonSelfintersectedContour(
		const std::vector<Polyline2d>& src, const double tolerance) const;

	/// Create a 3d contour with arcs and lines approximated to given polyline.
	/// @param src polyline to arc-fit
	/// @param tolerance Maximum allowed deviation from resulting contour to source contour and vice
	/// versa.
	Contour3d::Ptr Fit3dPolylineWithAnyPlanes(const Polyline3d& src, const double tolerance) const;

	/// Create a 3d contour with arcs and lines approximated to given polyline.
	///		But arcs will be created only in XY, YZ, ZX planes.
	/// @param src polyline to arc-fit
	/// @param tolerance Maximum allowed deviation from resulting contour to source contour and vice
	/// versa.
	Contour3d::Ptr Fit3dPolylineWithCoordinatePlanes(
		const Polyline3d& src, const double tolerance) const;

	/// @hidden
	Contour3d::Ptr FitPlanar3dPolyline(const Polyline3d& src, const double tolerance) const;

	/// Create a 3d contour with arcs and lines approximated to given polyline.
	/// @param src polyline to arc-fit
	/// @param planarityTolerance Consecutive geometries will be considered planar
	///			only if they are in planarityTolerance distance to "best-fit" plane.
	/// @param arcFittingTolerance Maximum allowed deviation from resulting contour to source
	/// contour and vice versa.
	/// @param useAnyPlaneToFit useAnyPlaneToFit when this parameter is false,
	///			arc fitter creates arcs in XY, XZ and YZ planes only.
	Contour3d::Ptr Fit3dPolyline(
		const Polyline3d& src,
		const double planarityTolerance,
		const double arcFittingTolerance,
		const bool useAnyPlaneToFit) const;

	/// Arc fitter has numerical limitations to best achievable tolerance,
	///			use this method to find smallest possible tolerance for an input.
	static double GetMinPossibleTolerance(const Polyline2d& scene);

	/// Arc fitter has numerical limitations to best achievable tolerance,
	///			use this method to find smallest possible tolerance for an input.
	static double GetMinPossibleTolerance(const Contour2d& scene);

private:
	double m_maxRadius;
	bool m_isFittingLineAllowed;
};
}  // namespace cadcam
#endif  //	MW_MWPOLYLINEARCFITTER_HPP_
