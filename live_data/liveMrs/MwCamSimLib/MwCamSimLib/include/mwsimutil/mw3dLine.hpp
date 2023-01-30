// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DLINE_HPP_
#define MW_MW3DLINE_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dPoint.hpp"
#include "mwAutoPointer.hpp"

namespace cadcam
{
template <class T>
class mw3dLine;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw3dLine<T>& line, unsigned int);
/// Implements a 3D linear segment
template <class T>
class MW_5AXUTIL_API mw3dLine: public mw3dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw3dLine<Ty>& line, unsigned int);

public:
	typedef misc::mwAutoPointer<mw3dLine<T>> Ptr;
	// Linux specific
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	typedef typename mw3dGeometry<T>::Point Point;
	// Linux specific

	/// Constructor
	///
	/// This constructor initializes both vertices to 0,0
	mw3dLine(): m_bBoxDirty(true) {}

	/// Copy Constructor, performing deep copy
	mw3dLine(const mw3dLine<T>& toCopy)
		: m_start(toCopy.m_start),
		  m_end(toCopy.m_end),
		  m_bbox(toCopy.m_bbox),
		  m_bBoxDirty(toCopy.m_bBoxDirty)
	{
	}

	/// Constructor
	///
	/// This constructor inits the line by passing the two vertices
	///	@param startPnt a parameter of type cadcam::mw2dGeometry::TPoint &
	///	@param endPnt a parameter of type cadcam::mw2dGeometry::TPoint &
	mw3dLine(const TPoint& startPnt, const TPoint& endPnt)
		: m_start(startPnt), m_end(endPnt), m_bBoxDirty(true)
	{
	}

	mw3dLine(const T x0, const T y0, const T z0, const T x1, const T y1, const T z1)
		: m_start(x0, y0, z0), m_end(x1, y1, z1), m_bBoxDirty(true)
	{
	}

	/// GetVertices
	///
	/// Returns the line endpoints
	///	@param startPnt ref to 1st vertex
	///	@param endPnt ref to 2nd vertex
	void GetVertices(TPoint& startPnt, TPoint& endPnt) const
	{
		startPnt = this->m_start;
		endPnt = this->m_end;
	}

	/// SetVertices
	///
	/// Sets the line endpoints
	///	@param startPnt const ref to 1st vertex
	///	@param endPnt const ref to 2nd vertex
	void SetVertices(const TPoint& startPnt, const TPoint& endPnt)
	{
		this->m_start = startPnt;
		this->m_end = endPnt;
		m_bBoxDirty = true;
	}

	/// GetStartPoint
	///
	/// Returns the line starting point
	///	@returns const ref to mwTPoint2d
	virtual const TPoint& GetStartPoint() const { return m_start; }

	/// GetEndPoint
	///
	/// Returns the line ending point
	///	@returns const ref to mwTPoint2d
	virtual const TPoint& GetEndPoint() const { return m_end; }
	/// SetStartPoint
	///
	/// Sets the line starting point
	///	@param startPnt const ref to mwTPoint2d
	void SetStartPoint(const TPoint& startPnt)
	{
		this->m_start = startPnt;
		this->m_bBoxDirty = true;
	}

	/// SetEndPoint
	///
	/// Sets the line ending point
	///	@param endPnt const ref to mwTPoint2d
	void SetEndPoint(const TPoint& endPnt)
	{
		this->m_end = endPnt;
		this->m_bBoxDirty = true;
	}

	/// GetLength
	///
	/// Returns the distance between line endpoints
	///	@returns line length
	virtual T GetLength() const { return ~(m_start - m_end); }

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

	/// Reverse line segment direction
	virtual void Reverse() { mathdef::mw_swap(m_start, m_end); }
	/// GetBoundingBox function
	///
	///	@returns GetBoundingBox of type virtual const mw2dBoundingBox< T >&
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		if (m_bBoxDirty)
		{
			m_bbox.SetCorners(m_start, m_end);
			m_bBoxDirty = false;
		}
		return m_bbox;
	}

	///	IsContinuous
	///
	/// Returns true if the geometric object is continuous
	///	@returns const bool
	virtual bool IsContinuous(const T) const { return true; }

	/// Get line direction vector
	TPoint GetDirection() const { return m_end - m_start; }

	/// Equality operator
	///
	/// Are given lines equal?
	/// @param tc line to compare the current line with
	/// @returns <b>true</b> if start and end points of this line coincide
	///   with same points of tc, <b>false</b> otherwise
	bool operator==(const mw3dLine<T>& tc) const
	{
		return tc.m_start == m_start && tc.m_end == m_end;
	}

	// Back capability functions. Don't use it anywhere.
	/// Don't use this function. It's back capability.
	mw3dLine(const Point& startPnt, const Point& endPnt)
		: m_start(startPnt.getTPoint()), m_end(endPnt.getTPoint()), m_bBoxDirty(true)
	{
	}
	/// Don't use this function. It's back capability.
	mw3dLine(const PointPtr& startPnt, const PointPtr& endPnt)
		: m_start(startPnt->getTPoint()), m_end(endPnt->getTPoint()), m_bBoxDirty(true)
	{
	}

	virtual ~mw3dLine() {}

private:
	TPoint m_start;
	TPoint m_end;
	mutable mw3dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
};
}  // namespace cadcam
#endif  //	MW_MW3DLINE_HPP_
