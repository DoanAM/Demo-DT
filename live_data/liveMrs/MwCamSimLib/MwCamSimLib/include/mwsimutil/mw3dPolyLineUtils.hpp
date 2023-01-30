// (C) 2008-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOLYLINEUTILS_HPP_
#define MW_MW3DPOLYLINEUTILS_HPP_

#include "mw3dPolyLine.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mw3dPolyLineUtils
{
	typedef mw3dPolyLine<T> PolyLine;
	typedef typename PolyLine::TPoint TPoint;
	typedef typename PolyLine::Point Point;
	typedef typename PolyLine::Line Line;
	typedef std::vector<PolyLine> PolyLineVec;
	typedef std::vector<PolyLineVec> PolyLineVecVec;
	typedef typename PolyLine::PointListIt PointListIt;
	typedef typename PolyLine::PointListConstIt PointListConstIt;
	typedef typename PolyLine::LineListConstIt LineListConstIt;

public:
	static bool IsFlat(const mw3dPolyLine<T>& src)
	{
		return mathdef::is_zero(src.GetBoundingBox().GetSizeZ());
	}

	static const double GetAverageHeight(const mw3dPolyLine<T>& polyline, const T tolerance)
	{
		const mw3dBoundingBox<T> bbox = polyline.GetBoundingBox();
		const T minHeight = bbox.GetMinZ();
		const T maxHeight = bbox.GetMaxZ();

		if (mathdef::is_neq(minHeight, maxHeight, tolerance))
			MW_EXCEPTION("Polyline should be planar and normal to machining direction.");

		return (minHeight + maxHeight) / 2.0;
	}

	static bool GetPolyLinePlaneIfItIsPossible(
		const PolyLine& poly,
		TPoint& planeOrigin,
		TPoint& planeNormal,
		const T planarTolerance = mathdef::mw_tol(T()))
	{
		if (poly.GetPointCount() == 0)
			MW_EXCEPTION("Can't get plane params for empty polyline");

		if (poly.GetPointCount() < 3)
			return false;

		// calculate average normal vector
		TPoint averageNormal;
		typename PolyLine::PointList::const_iterator pntIt = poly.GetPointBegin();
		++pntIt;
		for (; pntIt != poly.GetPointEnd(); ++pntIt)
		{
			typename PolyLine::PointList::const_iterator prevPntIt = pntIt;
			typename PolyLine::PointList::const_iterator nextPntIt = pntIt;
			--prevPntIt;
			++nextPntIt;
			if (nextPntIt == poly.GetPointEnd())
				break;

			TPoint currNormal = (*prevPntIt - *pntIt) % (*nextPntIt - *pntIt);
			if (mathdef::is_not_zero(~currNormal))
			{
				currNormal.Normalize();
				averageNormal +=
					mathdef::is_lt(averageNormal * currNormal, T(0)) ? -currNormal : currNormal;
			}
		}

		if (mathdef::is_zero(~averageNormal))
			return false;

		averageNormal.Normalize();

		// calculate average projection on normal
		TPoint originPoint = poly.GetStartPoint();
		T averageProjection = 0;
		for (pntIt = poly.GetPointBegin(); pntIt != poly.GetPointEnd(); ++pntIt)
		{
			averageProjection += (*pntIt - originPoint) * averageNormal;
		}
		averageProjection /= static_cast<T>(poly.GetPointCount());

		originPoint += averageNormal * averageProjection;

		if (IsPolyLineLocatedInPlane(poly, originPoint, averageNormal, planarTolerance))
		{
			planeOrigin = originPoint;
			planeNormal = averageNormal;
			return true;
		}
		return false;
	}

	static bool IsPolyLineLocatedInPlane(
		const PolyLine& poly,
		const TPoint& planeOrigin,
		const TPoint& planeNormal,
		const T planarTolerance = mathdef::mw_tol(T()))
	{
		if (poly.GetPointCount() == 0)
			MW_EXCEPTION("Empty polyline provided");

		if (mathdef::is_zero(~planeNormal))
			MW_EXCEPTION("Plane normal is zero length");

		const TPoint normal = planeNormal.Normalized();
		for (typename PolyLine::PointList::const_iterator pntIt = poly.GetPointBegin();
			 pntIt != poly.GetPointEnd();
			 ++pntIt)
		{
			const T projection = (*pntIt - planeOrigin) * planeNormal;
			if (mathdef::is_gt(mathdef::Abs(projection), planarTolerance))
				return false;
		}
		return true;
	}

	static PolyLine SplitLine(
		const typename PolyLine::Line& lineSrc, typename PolyLine::ValueType maxSegment)
	{
		PolyLine result;
		int noSteps = (int)ceil(lineSrc.GetLength() / maxSegment);

		Point startPt = lineSrc.GetStartPoint();
		Point endPt = lineSrc.GetEndPoint();
		Point diff = endPt - startPt;

		for (int i = 0; i < noSteps; ++i)
		{
			result.AddPoint(startPt + ((typename PolyLine::ValueType)i / noSteps) * diff);
		}
		result.AddPoint(endPt);
		return result;
	}


	static void JoinPolyLines(PolyLine& polyline1, const PolyLine& polyline2)
	{
		typename PolyLine::PointListConstIt pntIt = polyline2.GetPointBegin();
		for (; pntIt != polyline2.GetPointEnd(); ++pntIt)
		{
			polyline1.AddPoint(*pntIt);
		}
	}

	static PolyLine SplitPolyline(
		const PolyLine& polylineSrc, typename PolyLine::ValueType maxSegment)
	{
		PolyLine result;
		typename PolyLine::LineListConstIt lineIt = polylineSrc.GetLineBegin();
		for (; lineIt != polylineSrc.GetLineEnd(); ++lineIt)
		{
			JoinPolyLines(result, SplitLine(*lineIt, maxSegment));
		}
		return result;
	}

	static size_t GetIndexOfLongestSegment(const PolyLine& polyline)
	{
		const size_t pointCount = polyline.GetPointCount();
		if (0 >= pointCount)
			MW_EXCEPTION("Empty polyline");

		T maximumDistance2 = 0;
		size_t maximumDistancePoint1Idx = 0;
		for (size_t i = 0; (i + 2) <= pointCount; ++i)
		{
			const TPoint& p1 = polyline[i];
			const TPoint& p2 = polyline[i + 1];
			T distance2 = (p1 - p2).Length2();
			if (distance2 > maximumDistance2)
			{
				maximumDistancePoint1Idx = i;
				maximumDistance2 = distance2;
			}
		}
		return maximumDistancePoint1Idx;
	}

	static const TPoint GetCenterPointOfLongestLineSegment(const PolyLine& polyline)
	{
		const size_t pointCount = polyline.GetPointCount();
		if (0 >= pointCount)
			MW_EXCEPTION("Empty polyline");
		if (1 == pointCount)
			return polyline.GetStartPoint();

		const size_t maximumDistancePoint1Idx = GetIndexOfLongestSegment(polyline);

		return 0.5 * (polyline[maximumDistancePoint1Idx] + polyline[maximumDistancePoint1Idx + 1]);
	}

	static void RotateStartToLongestSegment(PolyLine& polyline)
	{
		if (polyline.GetPointCount() < 3 || !polyline.IsClosed())
		{
			return;
		}

		const size_t maximumDistancePoint1Idx = GetIndexOfLongestSegment(polyline);
		polyline.SetBegin(polyline.GetPointBegin() + maximumDistancePoint1Idx);
	}

	static void RotateStartToClosestPoint(const cadcam::mwPoint3d& point, PolyLine& polyline)
	{
		// easy version
		if (polyline.GetPointCount() < 3 || !polyline.IsClosed())
		{
			return;
		}
		size_t closestIndex = 0;
		FindClosestIndex(point, polyline, closestIndex);

		polyline.SetBegin(polyline.GetPointBegin() + closestIndex);
	}

	static void FindClosestIndex(
		const cadcam::mwPoint3d& point, const PolyLine& polyline, size_t& closestIndex)
	{
		double minDistance = mathdef::MW_MAX_DOUBLE;
		closestIndex = 0;
		for (size_t i = 0; i < polyline.GetPointCount(); ++i)
		{
			const double currentDistance2 = (polyline[i] - point).Length2();
			if (currentDistance2 < minDistance)
			{
				minDistance = currentDistance2;
				closestIndex = i;
			}
		}
	}

	/// @param polyline	    the polyline where segment to find
	/// @param hitPoint     point in picking space
	/// @param maxDistance  max allowed distance to segment in picking space
	/// @param polyLineHomogenousMatrix matrix to project the polyline to 2d picking space
	/// @returns  (serment index, (pos in segment, min distance))
	static std::pair<size_t, cadcam::mwPoint2d> FindClosestSegment(
		const PolyLine& polyline,
		const cadcam::mwTPoint2d<T>& hitPoint,
		const double maxDistance,
		const cadcam::mwHomogenousMatrix& polyLineHomogenousMatrix)
	{
		(maxDistance);

		if (polyline.IsEmpty())
			return std::make_pair(0, cadcam::mwPoint2d(0, FLT_MAX));

		typedef cadcam::mwTPoint2d<T> TPoint2d;
		typedef cadcam::mwTPoint3d<T> TPoint3d;

		PointListConstIt it = polyline.GetPointBegin();
		PointListConstIt itEnd = polyline.GetPointEnd();

		TPoint3d pointA = polyline.IsClosed() ? *polyline.GetReversePointBegin() : *it++;
		pointA.Transform(polyLineHomogenousMatrix);

		double minDistance2 = (TPoint2d(pointA.x(), pointA.y()) - hitPoint).Length2();
		double minT = 0;
		size_t minIndex = polyline.IsClosed() ? polyline.GetPointCount() : 0;

		while (it != itEnd)
		{
			TPoint3d pointB(*it++);
			pointB.Transform(polyLineHomogenousMatrix);

			const TPoint2d vAB(pointB.x() - pointA.x(), pointB.y() - pointA.y());
			const TPoint2d vAC(hitPoint.x() - pointA.x(), hitPoint.y() - pointA.y());
			const TPoint2d vBC(hitPoint.x() - pointB.x(), hitPoint.y() - pointB.y());

			const double d = vAB * vAB;
			const double d1 = vAB * vAC;
			const double d2 = vAB * vBC;

			double distance2;
			double t;
			if (d1 > 0 && d2 < 0 && d > std::numeric_limits<float>::epsilon())
			{
				const double S = vAB.x() * vAC.y() - vAB.y() * vAC.x();
				distance2 = (S * S) / d;
				t = d1 / (d1 - d2);
			}
			else
			{
				distance2 = vBC.Length2();
				t = 1.0;
			}

			if (distance2 < minDistance2)
			{
				minIndex = static_cast<size_t>(std::distance(polyline.GetPointBegin(), it));
				minDistance2 = distance2;
				minT = t;
			}

			pointA = pointB;
		}

		const double maxDistance2 = maxDistance * maxDistance;

		if (minDistance2 < maxDistance2)
			return std::make_pair(minIndex, cadcam::mwPoint2d(minT, sqrt(minDistance2)));
		else
			return std::make_pair(0, cadcam::mwPoint2d(0, FLT_MAX));
	}
};
}  // namespace cadcam
#endif  //	MW_MW3DPOLYLINEUTILS_HPP_
