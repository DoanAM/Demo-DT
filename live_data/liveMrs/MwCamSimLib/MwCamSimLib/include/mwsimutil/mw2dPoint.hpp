// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOINT_HPP_
#define MW_MW2DPOINT_HPP_
#include "mw2dGeometry.hpp"
#include "mwAutoPointer.hpp"
#include "mwTPoint2d.hpp"

namespace cadcam
{
template <class T>
class mw2dPoint;
template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw2dPoint<T>& p, unsigned int);
/// @class mw2dPoint
/// Implements 2D point as a part of mw2dGeometry hierarchy.
/// Should only be used when polymorphic behavior is required.
template <class T>
class MW_5AXUTIL_API mw2dPoint: public mw2dGeometry<T>
{
	template <class Archive, class T2>
	friend void cadcam::serialize(Archive& ar, cadcam::mw2dPoint<T2>& p, unsigned int);

public:
	typedef typename misc::mwAutoPointer<mw2dPoint<T>> Ptr;
	// Linux specific
	typedef typename mw2dGeometry<T>::TPoint TPoint;
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	typedef typename mw2dGeometry<T>::Point Point;
	typedef typename mw2dGeometry<T>::BoundingBox BoundingBox;
	// Linux specific

	mw2dPoint(): m_pnt() {}
	/// Create 2D point
	mw2dPoint(const T x, const T y): m_pnt(x, y) {}
	/// Copy 2D point
	mw2dPoint(const mwTPoint2d<T>& tc): m_pnt(tc) {}
	/// Copy 2D point
	mw2dPoint(const mw2dPoint<T>& tc): m_pnt(tc.m_pnt) {}
	const mw2dPoint& operator=(const mw2dPoint& tc)
	{
		m_pnt = tc.m_pnt;
		return *this;
	}
	const mw2dPoint& operator=(const TPoint& tc)
	{
		m_pnt = tc;
		return *this;
	}
	/// Are given points equal?
	bool operator==(const mw2dPoint& tc) const { return (tc.m_pnt == m_pnt); }
	/// Are given points unequal?
	bool operator!=(const mw2dPoint& tc) const { return !((*this) == tc); }
	/// Set 2D point X coordinate
	void x(const T newx) { m_pnt.x(newx); }
	/// Set 2D point Y coordinate
	void y(const T newy) { m_pnt.y(newy); }
	/// Get 2D point X coordinate
	const T x() const { return m_pnt.x(); }
	/// Get 2D point Y coordinate
	const T y() const { return m_pnt.y(); }
	/// Get 2D point coordinates array address
	const T* GetArray() const { return m_pnt.GetArray(); }
	/// Add 2D vector
	void operator+=(const mw2dPoint& ta) { m_pnt += ta.m_pnt; }
	/// Subtract 2D vector
	void operator-=(const mw2dPoint& ta) { m_pnt -= ta.m_pnt; }
	/// Get length of a vector
	const T operator~() const { return ~m_pnt; }
	/// Scalar multiplication
	void operator*=(const T scFactor) { m_pnt *= scFactor; }
	/// Divide by scalar
	void operator/=(const T scFactor) { m_pnt /= scFactor; }

	/// Get inverse vector
	mw2dPoint<T> operator-() const { return mw2dPoint<T>(-x(), -y()); }

	/// Normalize this vector
	const mw2dPoint<T> Normalize()
	{
		m_pnt.Normalize();
		return *this;
	}

	/// Get normalized copy of the vector
	const mw2dPoint<T> Normalized() const { return m_pnt.Normalized(); }

	/// Gets the constant reference of the internal point
	const TPoint& getTPoint() const { return m_pnt; }

	/// Implements visitor pattern
	virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }
	/// Implements visitor pattern
	virtual void AcceptVisitor(mw2dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	/// Returns the current position
	virtual const TPoint& GetStartPoint() const { return m_pnt; }
	/// Returns the current position
	virtual const TPoint& GetEndPoint() const { return m_pnt; }
	/// Always true for point
	virtual bool IsContinuous(const T) const { return true; }

	/// Always 0 for point
	virtual T GetLength() const { return static_cast<T>(0.0); }

	/// Return square of a vector length
	T Length2() const { return m_pnt.Length2(); }

	/// Is this point within given distance to specified point?
	bool IsTolerant(const Point& src, const T factor = mathdef::mw_tol(T())) const
	{
		return m_pnt.IsTolerant(src.getTPoint(), factor);
	}
	/// Returns bounding box degenerate to one point
	virtual const BoundingBox& GetBoundingBox() const
	{
		m_bbox.SetCorners(m_pnt, m_pnt);
		return m_bbox;
	}

private:
	/// Internal point instance
	TPoint m_pnt;
	mutable BoundingBox m_bbox;
};

template <typename T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mw2dPoint<T>& toDump)
{
	os << _T("class cadcam::mw2dPoint\n");
	// public properties from cadcam::mw2dPoint class.
	os << _T("x              = ") << toDump.x() << _T("\n");
	os << _T("y              = ") << toDump.y() << _T("\n");
	return os;
}
/// + operator
///
/// Add each component of a 2d point to another
///	@param first const reference of a 2d point
///	@param second const reference of a 2d point
///	@returns added const 2d point
template <class T>
mw2dPoint<T> operator+(const mw2dPoint<T>& first, const mw2dPoint<T>& second)
{
	return mw2dPoint<T>(first.x() + second.x(), first.y() + second.y());
}

/// - operator
///
/// Subtract each 2d point component from another
///	@param first const reference of a 2d point
///	@param second const reference of a 2d point
///	@returns subtracted const 2d point
template <class T>
mw2dPoint<T> operator-(const mw2dPoint<T>& first, const mw2dPoint<T>& second)
{
	return mw2dPoint<T>(first.x() - second.x(), first.y() - second.y());
}

/// * operator
///
/// Multiply each 2d component with a factor.
///	@param pt const reference to a 2d point
///	@param factor const reference to a factor to Multiply with
///	@returns new 2d point object
template <class T>
mw2dPoint<T> operator*(const mw2dPoint<T>& pt, const T factor)
{
	return mw2dPoint<T>(pt.x() * factor, pt.y() * factor);
}

/// * operator
///
/// Multiply each 2d component with a factor.
///	@param factor const reference to a factor to Multiply with
///	@param pt const reference to a 2d point
///	@returns new 2d point object
template <class T>
inline mw2dPoint<T> operator*(const T factor, const mw2dPoint<T>& pt)
{
	return mw2dPoint<T>(pt.x() * factor, pt.y() * factor);
}

//// operator
///
/// Divide each 2d component with a factor.
///	@param pt const reference to a 2d point
///	@param factor const reference to a factor to divide with
///	@returns new 2d point object
template <class T>
mw2dPoint<T> operator/(const mw2dPoint<T>& pt, const T factor)
{
	return mw2dPoint<T>(pt.x() / factor, pt.y() / factor);
}

/// * operator
///
/// Scalar product of to 2d points.
///	@param first const reference to a 2d point
///	@param second const reference to a 2d point
///	@returns scalar product of the input vectors
template <class T>
T operator*(const mw2dPoint<T>& first, const mw2dPoint<T>& second)
{
	return first.x() * second.x() + first.y() * second.y();
}

/// % operator
///
/// Cross (vector) product of to 2d points (= determinant)
///	@param first const reference to a 2d point
///	@param second const reference to a 2d point
///	@returns determinant of the input vectors as scalar
template <class T>
T operator%(const mw2dPoint<T>& first, const mw2dPoint<T>& second)
{
	return first.x() * second.y() - second.x() * first.y();
}
}  // namespace cadcam
#endif  // MW_MW2DPOINT_HPP_
