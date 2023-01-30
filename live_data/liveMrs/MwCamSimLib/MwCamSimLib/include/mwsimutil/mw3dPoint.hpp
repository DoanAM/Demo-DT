// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOINT_HPP_
#define MW_MW3DPOINT_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwTPoint3d.hpp"

namespace cadcam
{
/// \class mw3dPoint
///	Implements 3D point as a part of @ref mw3dGeometry hierarchy.
/// Should only be used when polymorphic behavior is required.
/// For example, as an element in @ref mw3dContour.
///
/// @tparam T type of scalars used to store coordinates
template <class T>
class MW_5AXUTIL_API mw3dPoint: public mw3dGeometry<T>
{
	template <class Archive, class T2>
	friend void serialize(Archive& ar, typename cadcam::mw3dPoint<T2>& p, unsigned int);

public:
	typedef typename misc::mwAutoPointer<mw3dPoint<T>> Ptr;
	/// @hidden
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	/// @hidden
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	/// @hidden
	typedef typename mw3dGeometry<T>::Point Point;

	/// Creates default point (0,0,0)
	mw3dPoint(): m_pnt(0, 0, 0) {}
	mw3dPoint(const T x, const T y, const T z): m_pnt(x, y, z) {}
	mw3dPoint(const TPoint& tc): m_pnt(tc) {}
	mw3dPoint(const mw3dPoint<T>& tc): m_pnt(tc.m_pnt) {}
	/// Gets the underlying mwTPoint3d point
	const TPoint& getTPoint() const { return m_pnt; }
	/// Sets new x-coordinate of the 3d point.
	/// @param newx const x-coordinate of the 3d point
	void x(const T newx) { m_pnt.x(newx); }
	/// Sets new y-coordinate of the 3d point.
	/// @param newy const y-coordinate of the 3d point
	void y(const T newy) { m_pnt.y(newy); }
	/// Sets new z-coordinate of the 3d point.
	/// @param newz const z-coordinate of the 3d point
	void z(const T newz) { m_pnt.z(newz); }
	/// Gets the x-coordinate
	const T x() const { return m_pnt.x(); }
	/// Gets the y-coordinate
	const T y() const { return m_pnt.y(); }
	/// Gets the z-coordinate
	const T z() const { return m_pnt.z(); }
	/// Gets a pointer to the 3d point array.
	///	@returns constant pointer to the 3d point array
	const T* GetArray() const { return m_pnt.GetArray(); }
	const mw3dPoint<T> operator=(const mw3dPoint<T>& tc)
	{
		m_pnt = tc.m_pnt;
		return *this;
	}
	const bool operator==(const mw3dPoint<T>& tc) const { return tc.m_pnt == m_pnt; }
	const bool operator!=(const mw3dPoint<T>& tc) const { return !((*this) == tc); }
	/// Add a point to a current
	void operator+=(const mw3dPoint<T>& ta) { m_pnt += ta.m_pnt; }
	/// Subtract a point from a current
	void operator-=(const mw3dPoint<T>& ta) { m_pnt -= ta.m_pnt; }
	/// Return the length of a vector represented by current point
	const T operator~() const { return ~m_pnt; }
	/// Multiply current point by scalar value
	void operator*=(const T scFactor) { m_pnt *= scFactor; }
	/// Divide current point by scalar value
	void operator/=(const T scFactor) { m_pnt /= scFactor; }
	/// Normalize this point and return normalized version
	const mw3dPoint<T> Normalize()
	{
		m_pnt.Normalize();
		return *this;
	}
	/// Get normalized point, leaving this point unchanged
	const mw3dPoint<T> Normalized() const { return m_pnt.Normalized(); }
	/// Apply matrix transormation
	void Transform(const mwMatrix<T, 4, 4>& homomatrix) { m_pnt.Transform(homomatrix); }
	/// Return start point of geometry. Returns itself.
	virtual const TPoint& GetStartPoint() const { return m_pnt; }
	/// Return end point of geometry. Returns itself.
	virtual const TPoint& GetEndPoint() const { return m_pnt; }
	/// Point is considered continuous. Always returns true
	virtual bool IsContinuous(const T) const { return true; }
	/// Check if this point is in tolerance to a given one
	///	@param src point to check with
	/// @param factor epsilon-distance defining the tolerance
	///	@returns true if src is within specified distance to this point
	bool IsTolerant(const Point& src, const T factor = mathdef::mw_tol(T())) const
	{
		return m_pnt.IsTolerant(src.getTPoint(), factor);
	}
	/// Length is always 0 for a point
	virtual T GetLength() const { return static_cast<T>(0.0); }
	/// Returns a bounding box consisting of a single point
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		m_bbox.SetCorners(m_pnt, m_pnt);
		return m_bbox;
	}
	virtual ~mw3dPoint() {}
	/// @hidden
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	/// @hidden
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

private:
	TPoint m_pnt;
	mutable mw3dBoundingBox<T> m_bbox;
};

/// @hidden
template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw3dPoint<T>& p, unsigned int);

/// Negate given point
template <class T>
mw3dPoint<T> operator-(const mw3dPoint<T>& p)
{
	return mw3dPoint<T>(-p.x(), -p.y(), -p.z());
}
/// Add two points
template <class T>
const mw3dPoint<T> operator+(const mw3dPoint<T>& first, const mw3dPoint<T>& second)
{
	return mw3dPoint<T>(first.x() + second.x(), first.y() + second.y(), first.z() + second.z());
}
/// Subtract two points
template <class T>
const mw3dPoint<T> operator-(const mw3dPoint<T>& first, const mw3dPoint<T>& second)
{
	return mw3dPoint<T>(first.x() - second.x(), first.y() - second.y(), first.z() - second.z());
}
/// Multiply point by scalar
template <class T>
const mw3dPoint<T> operator*(const mw3dPoint<T>& pt, const T factor)
{
	return mw3dPoint<T>(pt.x() * factor, pt.y() * factor, pt.z() * factor);
}
/// Multiply point by scalar
template <class T>
const mw3dPoint<T> operator*(const T factor, const mw3dPoint<T>& pt)
{
	return mw3dPoint<T>(pt.x() * factor, pt.y() * factor, pt.z() * factor);
}
/// Divide point by scalar
template <class T>
const mw3dPoint<T> operator/(const mw3dPoint<T>& pt, const T factor)
{
	return mw3dPoint<T>(pt.x() / factor, pt.y() / factor, pt.z() / factor);
}
/// Dot product of two points
template <class T>
const T operator*(const mw3dPoint<T>& first, const mw3dPoint<T>& second)
{
	return first.x() * second.x() + first.y() * second.y() + first.z() * second.z();
}
/// Cross (vector) product of two points
template <class T>
const mw3dPoint<T> operator%(const mw3dPoint<T>& first, const mw3dPoint<T>& second)
{
	return mw3dPoint<T>(
		first.y() * second.z() - first.z() * second.y(),
		first.z() * second.x() - first.x() * second.z(),
		first.x() * second.y() - first.y() * second.x());
}
}  // namespace cadcam
#endif  //	MW_MW3DPOINT_HPP_
