// (C) 2008-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DOFFSETERHELPER_HPP_
#define MW_MW2DOFFSETERHELPER_HPP_
#include "mw2dOffsetterHelper.hpp"
#include "mwDeprecated.hpp"

MW_COMPILE_WARNING("mw2dOffseterHelper.hpp is deprecated and will be removed in future releases. Please, include mw2dOffsetterHelper.hpp instead.")

namespace cadcam
{
template <class T>
class MW_5AXUTIL_API
MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper instead.")
mw2dOffseterHelper
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

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static Contour2dVec OffsetOutside(const Contour2dVec& contours, const T offsetDistance)
	{
		return mw2dOffsetterHelper<T>::OffsetOutside(contours, offsetDistance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::DoubleOffset instead.")
	static Contour2dVec DoubleOffset(const Contour2dVec& contours, const T doubleOffsetDistance)
	{
		return mw2dOffsetterHelper<T>::DoubleOffset(contours, doubleOffsetDistance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static Contour2dVec OffsetOutside(const Polyline2dVec& src, const T offsetDistance)
	{
		return mw2dOffsetterHelper<T>::OffsetOutside(src, offsetDistance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static MultiPolyline2dVec OffsetOutside(
		const MultiPolyline2dVec& slice,
		const T offset,
		const T polygonizationTolerance)
	{
		return mw2dOffsetterHelper<T>::OffsetOutside(slice, offset, polygonizationTolerance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static Polyline2dVec OffsetOutside(
		const Contour2dVec& src,
		const T offset,
		const T polygonizationTolerance)
	{
		return mw2dOffsetterHelper<T>::OffsetOutside(src, offset, polygonizationTolerance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static Polyline2dVec OffsetOutside(
		const Polyline2dVec& src,
		const T offset,
		const T polygonizationTolerance)
	{
		return mw2dOffsetterHelper<T>::OffsetOutside(src, offset, polygonizationTolerance);
	}

	template<typename Boundary>
	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetOutside instead.")
	static Boundary DoubleOffset(
		const Boundary& src,
		const T doubleOffsetDistance,
		const T doubleOffsetTolerance)
	{
		return mw2dOffsetterHelper<T>::DoubleOffset(src, doubleOffsetDistance, doubleOffsetTolerance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetLeft instead.")
	static Contour2dVec OffsetLeft(const Contour2dVec& contours, const T offsetDistance)
	{
		return mw2dOffsetterHelper<T>::OffsetLeft(contours, offsetDistance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetLeft instead.")
	static Polyline2dVec OffsetLeft(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T polygonizationTolerance)
	{
		return mw2dOffsetterHelper<T>::OffsetLeft(contours, offsetDistance, polygonizationTolerance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetLeft instead.")
	static Contour2dVec OffsetLeft(const Polyline2dVec& src, const T offsetDist)
	{
		return mw2dOffsetterHelper<T>::OffsetLeft(src, offsetDist);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::OffsetLeft instead.")
	static Polyline2dVec OffsetLeft(
		const Polyline2dVec& src,
		const T offsetDistance,
		const T polygonizationTolerance)
	{
		return mw2dOffsetterHelper<T>::OffsetLeft(src, offsetDistance, polygonizationTolerance);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::SharpCornersOffsetContourOutside instead.")
	static Contour2dVec SharpCornersOffsetContourOutside(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T startAngleDeg,
		const T endAngleDeg,
		const T extensionLength)
	{
		return mw2dOffsetterHelper<T>::SharpCornersOffsetContourOutside(
			contours, offsetDistance, startAngleDeg, endAngleDeg, extensionLength);
	}

	MW_DEPRECATED("Deprecated since 2018.12. Please use mw2dOffsetterHelper::SharpCornersOffsetContourLeft instead.")
	static Contour2dVec SharpCornersOffsetContourLeft(
		const Contour2dVec& contours,
		const T offsetDistance,
		const T startAngleDeg,
		const T endAngleDeg,
		const T extensionLength,
		const T checkDistance)
	{
		return mw2dOffsetterHelper<T>::SharpCornersOffsetContourLeft(
			contours, offsetDistance, startAngleDeg, endAngleDeg, extensionLength, checkDistance);
	}
};
} // namespace cadcam
#endif	//	MW_MW2DOFFSETERHELPER_HPP_
