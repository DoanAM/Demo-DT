// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DGEOMETRY_HPP_
#define MW_MW3DGEOMETRY_HPP_
#include "mw3dGeometryTypedefs.hpp"
#include "mw3dObject.hpp"
#include "mwDeprecated.hpp"
#include "mwException.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include "mwTChar.hpp"
#endif


namespace cadcam
{
/// Interface for 3d Geometric entities like Line, Arc, Spline, Contour.
template <class T>
class MW_5AXUTIL_API mw3dGeometry: public mw3dObject<T>
{
public:
	typedef misc::mwAutoPointer<mw3dGeometry<T>> Ptr;
	typedef T ValueType;
	typedef mwTPoint3d<T> TPoint;
	typedef mw3dPoint<T> Point;
	typedef misc::mwAutoPointer<Point> PointPtr;
	typedef mw3dBoundingBox<T> BoundingBox;
	typedef mw3dGeometry<T> Geometry;

	/// The AcceptVisitor function
	/// @param	visitor	a parameter of type mw3dObjectVisitor &
	virtual void AcceptVisitor(mw3dObjectVisitor<T>& visitor) { visitor.Visit(*this); }

	/// The AcceptVisitor function
	/// @param	visitor	a parameter of type const mw3dObjectVisitor &
	virtual void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const { visitor.Visit(*this); }

	/// AcceptVisitor implements constant visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const = 0;

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) = 0;

	virtual const mw3dBoundingBox<T>& GetBoundingBox() const = 0;

	/// GetStartPoint
	///
	/// Returns the geometry start point
	///	@returns const ref to mwTPoint2d
	virtual const TPoint& GetStartPoint() const = 0;

	/// GetEndPoint
	///
	/// Returns the geometry ending point
	///	@returns const ref to mwTPoint2d
	virtual const TPoint& GetEndPoint() const = 0;

	///	IsContinuous
	///
	/// Returns true if the geometric object is continuous
	///	@returns const bool
	virtual bool IsContinuous(const T tolerance = 0) const = 0;

	///	GetLength
	///
	/// Returns the length of geometric object.
	///	@returns length
	virtual T GetLength() const = 0;

	///	Reverse
	///
	/// Reverse the start and the end.
	/// @returns true, if it has been done
	virtual void Reverse() { throw misc::mwException(0, _T("Not implemented")); }

	virtual ~mw3dGeometry() {}
};

template <class T>
class MW_5AXUTIL_API mw3dGeometryConstVisitor
{
public:
	virtual void Visit(const mw3dPoint<T>& tv) = 0;
	virtual void Visit(const mw3dLine<T>& tv) = 0;
	virtual void Visit(const mw3dArc<T>& tv) = 0;
	virtual void Visit(const mw3dHelix<T>& tv) = 0;
	virtual void Visit(const mw3dContour<T>& tv) = 0;
	virtual void Visit(const mw3dClosedContour<T>&) {}
	virtual void Visit(const mw3dPolyLine<T>& tv) = 0;
	virtual ~mw3dGeometryConstVisitor() {}
};

template <class T>
class MW_5AXUTIL_API mw3dGeometryVisitor
{
public:
	virtual void Visit(mw3dPoint<T>& tv) = 0;
	virtual void Visit(mw3dLine<T>& tv) = 0;
	virtual void Visit(mw3dArc<T>& tv) = 0;
	virtual void Visit(mw3dHelix<T>& tv) = 0;
	virtual void Visit(mw3dContour<T>& tv) = 0;
	virtual void Visit(mw3dClosedContour<T>&) {}
	virtual void Visit(mw3dPolyLine<T>& tv) = 0;
	virtual ~mw3dGeometryVisitor() {}
};

}  // namespace cadcam
#endif  //	MW_MW3DGEOMETRY_HPP_
