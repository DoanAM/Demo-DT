// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPOINTUTILS_HPP_
#define MW_MWTPOINTUTILS_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMatrixTransformationsFactory.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"
#include "mwTrig.hpp"

#include <cfloat>


namespace cadcam
{
/// different utils involving points
template <typename TPoint>
class MW_5AXUTIL_API mwTPointUtils
{
public:
	typedef typename TPoint::ValueType ValueType;
	typedef TPoint Point;

	/// Convert point from one base to another
	template <class Tsrc>
	static cadcam::mwTPoint2d<ValueType> ConvPoint(const mwTPoint2d<Tsrc>& orgPnt)
	{
		return cadcam::mwTPoint2d<ValueType>(
			static_cast<ValueType>(orgPnt.x()), static_cast<ValueType>(orgPnt.y()));
	}

	/// Convert point from one base to another
	template <class Tsrc>
	static cadcam::mwTPoint3d<ValueType> ConvPoint(const mwTPoint3d<Tsrc>& orgPnt)
	{
		return cadcam::mwTPoint3d<ValueType>(
			static_cast<ValueType>(orgPnt.x()),
			static_cast<ValueType>(orgPnt.y()),
			static_cast<ValueType>(orgPnt.z()));
	}

	/// Convert to Point type and zero down denormalized values for coordinates
	template <class SrcPoint>
	static Point ConvZeroSubnormal(const SrcPoint& src)
	{
		Point res;
		for (size_t i = 0; i < 3; ++i)
		{
			if (mathdef::IsSubnormal<typename Point::ValueType>(src[i]))
			{
				res[i] = 0.;
			}
			else
			{
				res[i] = static_cast<typename Point::ValueType>(src[i]);
			}
		}
		return res;
	}

	/// finds the smallest angle between two vectors.Value is between 0 and PI
	///
	///	@param first the first vector
	///	@param second the second vector
	///	@returns the angle
	static const ValueType GetSmallestAngle(const Point& first, const Point& second)
	{
		Point normedFirst(first.Normalized());
		Point normedSecond(second.Normalized());
		ValueType firstDotSecond(normedFirst * normedSecond);

		if (mathdef::is_eq(firstDotSecond, static_cast<ValueType>(1)))
			return static_cast<ValueType>(0.0);
		if (mathdef::is_eq(firstDotSecond, static_cast<ValueType>(-1)))
			return static_cast<ValueType>(mathdef::MW_PI);
		return acos(firstDotSecond);
	}

	/// Returns point rotated on degreeAngle in counterclockwise direction relatively origin
	///
	/// @param point initial point
	/// @param angleDeg angle in degrees
	/// @returns the resulting point
	static TPoint GetRotatedPoint(const TPoint& point, const ValueType angleDeg)
	{
		const ValueType angleRad = static_cast<ValueType>(mathdef::MW_D2R) * angleDeg;
		const ValueType cosA = static_cast<ValueType>(mathdef::Cos(1. * angleRad));
		const ValueType sinA = static_cast<ValueType>(mathdef::Sin(1. * angleRad));
		return TPoint(point.x() * cosA - point.y() * sinA, point.x() * sinA + point.y() * cosA);
	}

	static TPoint GetRotatedPointTrig(const TPoint& point, const ValueType sina)
	{
		ValueType cosa = sqrt(1 - sina * sina);
		return TPoint(point.x() * cosa - point.y() * sina, point.x() * sina + point.y() * cosa);
	}

	/// Get left normal vector
	static Point GetLeftNormal(const Point& src) { return Point(-src.y(), src.x()); }

	/// Get right normal vector
	static Point GetRightNormal(const Point& src) { return Point(src.y(), -src.x()); }

	static Point GetNormal(const Point& src, const bool isLeft)
	{
		return isLeft ? Point(-src.y(), src.x()) : Point(src.y(), -src.x());
	}

	/// Rotates a 3D point around an axis by given the axis and the axis base point
	///
	///	@param toRotate point beeing rotated (returns rotated point)
	///	@param axis specifies the rotation axis
	///	@param axisBasePoint specifies the rotation axis base point
	/// @param degreeAngle angle to rotate in degrees
	static TPoint GetRotatedPoint(
		const TPoint& toRotate,
		const TPoint& axis,
		const TPoint& axisBasePoint,
		const ValueType degreeAngle)
	{
		mwMatrix<ValueType, 4, 4> rotationMatrix =
			mwMatrixTransformationsFactory<ValueType>::Create3dRotation(
				axis.Normalized(), degreeAngle);

		return GetRotatedPoint(toRotate, axisBasePoint, rotationMatrix);
	}

	/// Rotates 3D points around an axis by given the axis and the axis base point
	///
	///	@param src points to be rotated
	///	@param axis specifies the rotation axis
	///	@param axisBasePoint specifies the rotation axis base point
	/// @param degreeAngle angle to rotate in degrees
	static std::vector <TPoint> GetRotatedPoints(
		const std::vector<TPoint>& src,
		const TPoint& axis,
		const TPoint& axisBasePoint,
		const ValueType degreeAngle)
	{ 
		std::vector<TPoint> dst(src.size());
		for (size_t idx = 0; idx < src.size(); ++idx)
		{
			dst[idx] = mwTPointUtils<TPoint>::GetRotatedPoint(
				src[idx], axis, axisBasePoint, degreeAngle);
		}

		return dst;
	}

	static TPoint GetRotatedPoint(
		const TPoint& toRotate,
		const TPoint& axisBasePoint,
		const mwMatrix<ValueType, 4, 4>& rotationMatrix)
	{
		mwMatrix<ValueType, 4, 1> pntTransl2Origin;
		mwMatrix<ValueType, 4, 1> rotatedPntMatrix;

		pntTransl2Origin[0][0] = toRotate.x() - axisBasePoint.x();
		pntTransl2Origin[1][0] = toRotate.y() - axisBasePoint.y();
		pntTransl2Origin[2][0] = toRotate.z() - axisBasePoint.z();
		pntTransl2Origin[3][0] = 1;

		rotatedPntMatrix =
			MultiplyMatrices<ValueType, 4, 4, 4, 1>(rotationMatrix, pntTransl2Origin);
		return TPoint(
			rotatedPntMatrix[0][0] + axisBasePoint.x(),
			rotatedPntMatrix[1][0] + axisBasePoint.y(),
			rotatedPntMatrix[2][0] + axisBasePoint.z());
	}

	static bool IsEqual(const Point& p1, const Point& p2)
	{
		return mathdef::is_zero(
			(p1 - p2).Length2(), static_cast<ValueType>(mathdef::MW_MATH_TOL_SQR));
	}

	static bool VectorsLookTowardsEachOther(
		const Point& firstFVStart,
		const Point& firstFVEnd,
		const Point& secondFVStart,
		const Point& secondFVEnd)
	{
		return (firstFVStart - secondFVStart).Length2() > (firstFVEnd - secondFVEnd).Length2();
	}

	static ValueType GetXoYDistance(const Point& v1, const Point& v2)
	{
		const cadcam::mwTPoint2d<ValueType> v(v1.x() - v2.x(), v1.y() - v2.y());
		return ~v;
	}

	static Point GetClosestPoint(
		const Point& dst, const std::vector<Point>& points, const bool skipEqual = false)
	{
		if (points.empty())
			MW_EXCEPTION("Points container must not be empty.");

		std::vector<Point> src = points;
		if (skipEqual && dst == src.front())
		{
			src.erase(src.begin());
		}

		Point closestPoint = src.front();
		ValueType minDistance = (dst - closestPoint).Length2();

		for (size_t i = 1; i < src.size(); ++i)
		{
			if (skipEqual && dst == src[i])
				continue;

			const ValueType distance = (dst - src[i]).Length2();
			if (minDistance > distance)
			{
				minDistance = distance;
				closestPoint = src[i];
			}
		}
		return closestPoint;
	}

	template <class T>
	static cadcam::mwTPoint3d<T> GetMaxPoint(
		const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
	{
		return cadcam::mwTPoint3d<T>(
			mathdef::mw_max(first.x(), second.x()),
			mathdef::mw_max(first.y(), second.y()),
			mathdef::mw_max(first.z(), second.z()));
	}

	/// GetMinPoint
	///
	///	@returns the point with smallest coordinate
	template <class T>
	static cadcam::mwTPoint3d<T> GetMinPoint(
		const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
	{
		return cadcam::mwTPoint3d<T>(
			mathdef::mw_min(first.x(), second.x()),
			mathdef::mw_min(first.y(), second.y()),
			mathdef::mw_min(first.z(), second.z()));
	}

	/// GetMaxPoint
	///
	///	@return the point with biggest coordinate
	template <class T>
	static cadcam::mwTPoint2d<T> GetMaxPoint(
		const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
	{
		return cadcam::mwTPoint2d<T>(
			mathdef::mw_max(first.x(), second.x()), mathdef::mw_max(first.y(), second.y()));
	}

	/// GetMinPoint
	///
	///	@returns the point with smallest coordinate
	template <class T>
	static cadcam::mwTPoint2d<T> GetMinPoint(
		const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
	{
		return cadcam::mwTPoint2d<T>(
			mathdef::mw_min(first.x(), second.x()), mathdef::mw_min(first.y(), second.y()));
	}

	/// GetMinCoordinate
	///
	///	@returns the coordinate with minimum value
	template <class T>
	static T GetMinCoordinate(const mwTPoint2d<T>& point)
	{
		return mathdef::mw_min(point.x(), point.y());
	}

	/// GetMinCoordinate
	///
	///	@returns the coordinate with minimum value
	template <class T>
	static T GetMinCoordinate(const mwTPoint3d<T>& point)
	{
		return mathdef::mw_min(point.x(), point.y(), point.z());
	}

	/// GetMaxCoordinate
	///
	///	@returns the coordinate with maximum value
	template <class T>
	static T GetMaxCoordinate(const mwTPoint2d<T>& point)
	{
		return mathdef::mw_max(point.x(), point.y());
	}

	/// GetMaxCoordinate
	///
	///	@returns the coordinate with maximum value
	template <class T>
	static T GetMaxCoordinate(const mwTPoint3d<T>& point)
	{
		return mathdef::mw_max(point.x(), point.y(), point.z());
	}

	/// Gets mirror of a point across a mirroring plane
	///
	///	@param toMirror is point to be mirrored
	///	@param planeNormal specifies normal unit of mirroring plane
	///	@param planePoint specifies a point on the mirroring plane (base point),
	///		establish plane distance from origin of CS
	///	@return mirrored point
	static TPoint GetMirroredPoint(
		const TPoint& toMirror, const TPoint& planeNormal, const TPoint& planePoint)
	{
		mwMatrix<ValueType, 4, 4> mirroringMatrix =
			mwMatrixTransformationsFactory<ValueType>::Create3dMirroring(planeNormal, planePoint);

		mwMatrix<ValueType, 4, 1> pnt2MirrorMatrix;

		pnt2MirrorMatrix[0][0] = toMirror.x();
		pnt2MirrorMatrix[1][0] = toMirror.y();
		pnt2MirrorMatrix[2][0] = toMirror.z();
		pnt2MirrorMatrix[3][0] = 1;

		mwMatrix<ValueType, 4, 1> mirroredPntMatrix;

		mirroredPntMatrix =
			MultiplyMatrices<ValueType, 4, 4, 4, 1>(mirroringMatrix, pnt2MirrorMatrix);

		return TPoint(mirroredPntMatrix[0][0], mirroredPntMatrix[1][0], mirroredPntMatrix[2][0]);
	}

private:
	/// disable constructor of static class
	mwTPointUtils();
};

template <typename Point2d>
class mwPointLess
{
public:
	typedef typename Point2d::ValueType T;

	mwPointLess(const T tolerance = 0): m_tolerance(tolerance) {}

	bool operator()(const Point2d& A, const Point2d& B) const
	{
		if (mathdef::is_neq(A.y(), B.y(), m_tolerance))
			return mathdef::is_lt(A.y(), B.y(), m_tolerance);
		return mathdef::is_lt(A.x(), B.x(), m_tolerance);
	}

private:
	T m_tolerance;
};

template <typename Point3d>
class mwPoint3dLess
{
public:
	typedef typename Point3d::ValueType T;
	mwPoint3dLess(const T tolerance = 0): m_tolerance(tolerance) {}

	bool operator()(const Point3d& A, const Point3d& B) const
	{
		if (mathdef::is_neq(A.x(), B.x(), m_tolerance))
			return mathdef::is_lt(A.x(), B.x(), m_tolerance);
		if (mathdef::is_neq(A.y(), B.y(), m_tolerance))
			return mathdef::is_lt(A.y(), B.y(), m_tolerance);
		return mathdef::is_lt(A.z(), B.z(), m_tolerance);
	}

private:
	T m_tolerance;
};

template <typename Point>
struct mwPointXLessYGreater
{
	bool operator()(const Point& first, const Point& second) const
	{
		if (first.x() != second.x())
			return first.x() < second.x();
		if (first.y() != second.y())
			return first.y() > second.y();
		return false;
	}
};

template <typename Point>
struct mwPointYGreaterXLess
{
	bool operator()(const Point& first, const Point& second) const
	{
		if (first.y() != second.y())
			return first.y() > second.y();
		if (first.x() != second.x())
			return first.x() < second.x();
		return false;
	}
};

namespace mwTPointProjection
{
template <typename T>
mwTPoint2d<T> ProjectOnXY(const mwTPoint3d<T>& p)
{
	return mwTPoint2d<T>(p.x(), p.y());
}
template <typename T>
mwTPoint2d<T> ProjectOnYZ(const mwTPoint3d<T>& p)
{
	return mwTPoint2d<T>(p.y(), p.z());
}
template <typename T>
mwTPoint2d<T> ProjectOnZX(const mwTPoint3d<T>& p)
{
	return mwTPoint2d<T>(p.z(), p.x());
}
template <typename T>
mwTPoint3d<T> UnprojectFromXY(const mwTPoint2d<T>& p, const T z = static_cast<T>(0))
{
	return mwTPoint3d<T>(p.x(), p.y(), z);
}
template <typename T>
mwTPoint3d<T> UnprojectFromYZ(const mwTPoint2d<T>& p, const T x = static_cast<T>(0))
{
	return mwTPoint3d<T>(x, p.x(), p.y());
}
template <typename T>
mwTPoint3d<T> UnprojectFromZX(const mwTPoint2d<T>& p, const T y = static_cast<T>(0))
{
	return mwTPoint3d<T>(p.y(), y, p.x());
}
}  // namespace mwTPointProjection

}  // namespace cadcam
#endif  //	MW_MWTPOINTUTILS_HPP_
