// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DGEOMETRY_HPP_
#define MW_MW2DGEOMETRY_HPP_
#include "mw2dGeometryTypedefs.hpp"
#include "mwDeprecated.hpp"
#include "mwException.hpp"

#if defined(__linux__) || defined(__APPLE__)
#include "mwTChar.hpp"
#endif
#include "mw2dBoundingBox.hpp"


namespace cadcam
{
template <class T>
class mw2dBoundingBox;
template <class T>
class mw2dPoint;
template <class T>
class mw2dGeometryConstVisitor;
template <class T>
class mw2dGeometryVisitor;


/// Interface for 2d Geometric entities like Line, Arc, Spline, Contour
template <class T>
class MW_5AXUTIL_API mw2dGeometry
{
public:
	typedef T ValueType;
	typedef misc::mwAutoPointer<mw2dGeometry<T>> Ptr;
	typedef mwTPoint2d<T> TPoint;
	typedef mw2dPoint<T> Point;
	typedef typename misc::mwAutoPointer<Point> PointPtr;
	typedef mw2dBoundingBox<T> BoundingBox;
	typedef mw2dGeometry<T> Geometry;

	/// Implements visitor pattern, non-modifying
	virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const = 0;

	/// Implements visitor pattern, modifying
	virtual void AcceptVisitor(mw2dGeometryVisitor<T>& visitor) = 0;

	/// Get 2D bounding box
	virtual const mw2dBoundingBox<T>& GetBoundingBox() const = 0;

	/// Get geometry start point
	virtual const TPoint& GetStartPoint() const = 0;

	/// Get geometry end point
	virtual const TPoint& GetEndPoint() const = 0;

	///	Is geometry continuous?
	virtual bool IsContinuous(const T tolerance = 0) const = 0;

	///	Get length
	virtual T GetLength() const = 0;

	///	Reverse (start/end points flip)
	inline virtual void Reverse();

	inline virtual ~mw2dGeometry();
};

///  Parent class for non-modifying visitors
/// The class is a part of visitor pattern.
/// Used to detect which concrete type is behind the base class pointer or reference.
template <class T>
class MW_5AXUTIL_API mw2dGeometryConstVisitor
{
public:
	virtual void Visit(const mw2dPoint<T>& tv) = 0;
	virtual void Visit(const mw2dLine<T>& tv) = 0;
	virtual void Visit(const mw2dArc<T>& tv) = 0;
	virtual void Visit(const mw2dContour<T>& tv) = 0;
	virtual void Visit(const mw2dClosedContour<T>&) {}
	virtual void Visit(const mw2dPolyLine<T>& tv) = 0;
	virtual void Visit(const mw2dCurve<T>& tv) = 0;
	inline virtual ~mw2dGeometryConstVisitor();
};

///  Parent class for modifying visitors
/// The class is a part of visitor pattern.
/// Used to detect which concrete type is behind the base class pointer or reference.
template <class T>
class MW_5AXUTIL_API mw2dGeometryVisitor
{
public:
	virtual void Visit(mw2dPoint<T>& tv) = 0;
	virtual void Visit(mw2dLine<T>& tv) = 0;
	virtual void Visit(mw2dArc<T>& tv) = 0;
	virtual void Visit(mw2dContour<T>& tv) = 0;
	virtual void Visit(mw2dClosedContour<T>&) {}
	virtual void Visit(mw2dPolyLine<T>& tv) = 0;
	virtual void Visit(mw2dCurve<T>& tv) = 0;
	inline virtual ~mw2dGeometryVisitor();
};

template <class T>
inline void mw2dGeometry<T>::Reverse()
{
	throw misc::mwException(0, _T("Not implemented"));
}

template <class T>
inline mw2dGeometry<T>::~mw2dGeometry()
{
}

template <class T>
inline mw2dGeometryConstVisitor<T>::~mw2dGeometryConstVisitor()
{
}

template <class T>
inline mw2dGeometryVisitor<T>::~mw2dGeometryVisitor()
{
}
}  // namespace cadcam
#endif  //	MW_MW2DGEOMETRY_HPP_
