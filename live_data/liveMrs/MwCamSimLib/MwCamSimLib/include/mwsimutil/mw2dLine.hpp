// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DLINE_HPP_
#define MW_MW2DLINE_HPP_
#include "mw2dBoundingBox.hpp"
#include "mw2dGeometry.hpp"
#include "mw2dPoint.hpp"
#include "mwAutoPointer.hpp"

namespace cadcam
{
template <class T>
class mw2dLine;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw2dLine<T>& line, unsigned int);
/// Implements a 3D linear segment
template <class T>
class MW_5AXUTIL_API mw2dLine: public mw2dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw2dLine<Ty>& line, unsigned int);

public:
	typedef typename misc::mwAutoPointer<mw2dLine<T>> Ptr;
	// Linux specific
	typedef typename mw2dGeometry<T>::TPoint TPoint;
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	typedef typename mw2dGeometry<T>::Point Point;
	typedef typename mw2dGeometry<T>::BoundingBox BoundingBox;
	// Linux specific

	mw2dLine();
	/// Create 2D line from a pair of 2D coordinates
	///
	/// @param x0 First point's x
	/// @param y0 First point's y
	/// @param x1 Second point's x
	/// @param y1 Second point's y
	mw2dLine(const T x0, const T y0, const T x1, const T y1);
	/// Create line from 2 points
	///
	/// @param startPnt First point of a line
	/// @param endPnt Second point of a line
	mw2dLine(const TPoint& startPnt, const TPoint& endPnt);
	/// Get line start/end points
	///
	/// @param startPnt start point
	/// @param endPnt end point
	void GetVertices(TPoint& startPnt, TPoint& endPnt) const;
	/// Set line start/end points
	///
	/// @param startPnt start point
	/// @param endPnt end point
	void SetVertices(const TPoint& startPnt, const TPoint& endPnt);
	/// Get line start point
	virtual const TPoint& GetStartPoint() const;
	/// Get line end point
	virtual const TPoint& GetEndPoint() const;
	/// Set line start point
	void SetStartPoint(const TPoint& startPnt);
	/// Set line end point
	void SetEndPoint(const TPoint& endPnt);
	/// Get line length
	virtual T GetLength() const;
	/// Always true for 2D line
	virtual bool IsContinuous(const T) const;
	/// Inverse this line segment direction
	virtual void Reverse();
	bool operator==(const mw2dLine<T>& line) const;
	/// Get vector direction = end - start
	TPoint GetDirection() const;
	/// Get 2D object's bounding box
	virtual const BoundingBox& GetBoundingBox() const;
	/// Implements visitor pattern
	virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const;
	/// Implements visitor pattern
	virtual void AcceptVisitor(mw2dGeometryVisitor<T>& visitor);
	/// Function is deprecated
	mw2dLine(const Point& startPnt, const Point& endPnt);
	/// Function is deprecated
	mw2dLine(const PointPtr& startPnt, const PointPtr& endPnt);

private:
	TPoint m_start;
	TPoint m_end;
	mutable BoundingBox m_bbox;
	mutable bool m_bBoxDirty;
};

template <class T>
inline mw2dLine<T>::mw2dLine(): m_bBoxDirty(true)
{
}

template <class T>
inline mw2dLine<T>::mw2dLine(const T x0, const T y0, const T x1, const T y1)
	: m_start(x0, y0), m_end(x1, y1), m_bBoxDirty(true)
{
}

template <class T>
inline mw2dLine<T>::mw2dLine(const TPoint& startPnt, const TPoint& endPnt)
	: m_start(startPnt), m_end(endPnt), m_bBoxDirty(true)
{
}

template <class T>
inline void mw2dLine<T>::GetVertices(TPoint& startPnt, TPoint& endPnt) const
{
	startPnt = this->m_start;
	endPnt = this->m_end;
}

template <class T>
inline void mw2dLine<T>::SetVertices(const TPoint& startPnt, const TPoint& endPnt)
{
	this->m_start = startPnt;
	this->m_end = endPnt;
	m_bBoxDirty = true;
}

template <class T>
inline const typename mw2dLine<T>::TPoint& mw2dLine<T>::GetStartPoint() const
{
	return m_start;
}

template <class T>
inline const typename mw2dLine<T>::TPoint& mw2dLine<T>::GetEndPoint() const
{
	return m_end;
}

template <class T>
inline void mw2dLine<T>::SetStartPoint(const TPoint& startPnt)
{
	this->m_start = startPnt;
	this->m_bBoxDirty = true;
}

template <class T>
inline void mw2dLine<T>::SetEndPoint(const TPoint& endPnt)
{
	this->m_end = endPnt;
	this->m_bBoxDirty = true;
}

template <class T>
inline T mw2dLine<T>::GetLength() const
{
	return ~(m_start - m_end);
}

template <class T>
inline void mw2dLine<T>::AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const
{
	visitor.Visit(*this);
}

template <class T>
inline void mw2dLine<T>::AcceptVisitor(mw2dGeometryVisitor<T>& visitor)
{
	visitor.Visit(*this);
}

template <class T>
inline bool mw2dLine<T>::IsContinuous(const T) const
{
	return true;
}

template <class T>
inline void mw2dLine<T>::Reverse()
{
	mathdef::mw_swap(m_start, m_end);
}

template <class T>
inline bool mw2dLine<T>::operator==(const mw2dLine<T>& line) const
{
	return m_start == line.m_start && m_end == line.m_end;
}

template <class T>
inline typename mw2dLine<T>::TPoint mw2dLine<T>::GetDirection() const
{
	return m_end - m_start;
}

template <class T>
inline const typename mw2dLine<T>::BoundingBox& mw2dLine<T>::GetBoundingBox() const
{
	if (m_bBoxDirty)
	{
		m_bbox.SetCorners(m_start, m_end);
		m_bBoxDirty = false;
	}
	return m_bbox;
}

template <class T>
inline mw2dLine<T>::mw2dLine(const Point& startPnt, const Point& endPnt)
	: m_start(startPnt.getTPoint()), m_end(endPnt.getTPoint()), m_bBoxDirty(true)
{
}

template <class T>
inline mw2dLine<T>::mw2dLine(const PointPtr& startPnt, const PointPtr& endPnt)
	: m_start(startPnt->getTPoint()), m_end(endPnt->getTPoint()), m_bBoxDirty(true)
{
}

template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mw2dLine<T>& toDump)
{
	os << _T("class cadcam::mw2dLine\n");
	// public properties from cadcam::mw2dLine class.
	os << _T("GetStartPoint  = ") << toDump.GetStartPoint() << _T("\n");
	os << _T("GetEndPoint    = ") << toDump.GetEndPoint() << _T("\n");
	os << _T("GetLength      = ") << toDump.GetLength() << _T("\n");
	os << _T("GetBoundingBox = ") << toDump.GetBoundingBox() << _T("\n");
	return os;
}
}  // namespace cadcam
#endif  //	MW_MW2DLINE_HPP_
