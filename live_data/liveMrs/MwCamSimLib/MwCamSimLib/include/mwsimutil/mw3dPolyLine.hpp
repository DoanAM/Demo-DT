// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOLYLINE_HPP_
#define MW_MW3DPOLYLINE_HPP_
#include "mw3dGeometry.hpp"
#include "mw3dLine.hpp"
#include "mwDefines.hpp"
#include "mwLineContainerIteratorConvertor.hpp"

#include <algorithm>
#include <utility>
#include <vector>


namespace cadcam
{
// serialize
template <class T>
class mw3dPolyLine;
template <class Archive, class T>
void serialize(Archive& archive, mw3dPolyLine<T>& polyline, unsigned int);
// end serialize
template <class T>
class MW_5AXUTIL_API mw3dPolyLine: public mw3dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& archive, mw3dPolyLine<Ty>& polyline, unsigned int);

public:
	// Linux specific
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	typedef typename mw3dGeometry<T>::Point Point;
	// Linux specific
	typedef typename misc::mwAutoPointer<mw3dPolyLine<T>> Ptr;
	typedef typename std::vector<TPoint> PointList;
	typedef typename PointList::iterator PointListIt;
	typedef typename PointList::const_iterator PointListConstIt;
	typedef typename PointList::const_reverse_iterator PointListConstReverseIt;

	typedef mw3dLine<T> Line;
	typedef cadcam::mwLineContainerConstIteratorConvertor<TPoint, Line> LineListConstIt;
	typedef mw3dBoundingBox<T> BoundingBox;

	/// Default constructor
	mw3dPolyLine() {}

	/// Copy constructor
	///
	/// Creates an exact copy of the polyline
	///	@param toCopy polyline to create a copy of
	mw3dPolyLine(const mw3dPolyLine<T>& toCopy): m_pointList(toCopy.m_pointList) {}

	/// Assignment operator
	mw3dPolyLine<T>& operator=(const mw3dPolyLine<T>& toCopy)
	{
		m_pointList = toCopy.m_pointList;

		return *this;
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	/// Initializer list constructor
	mw3dPolyLine(std::initializer_list<cadcam::mwTPoint3d<T>> points)
		: mw3dPolyLine(points.begin(), points.end())
	{
	}

	/// Move constructor
	mw3dPolyLine(mw3dPolyLine<T>&& toMove) noexcept: m_pointList(std::move(toMove.m_pointList)) {}

	/// Move assignment operator
	mw3dPolyLine<T>& operator=(mw3dPolyLine<T>&& toMove) noexcept
	{
		m_pointList = std::move(toMove.m_pointList);

		return *this;
	}
#endif  // MW_USE_VS2008_COMPATIBILITY

private:
	template <typename Vector, typename Itr>
	static void reserve(Vector& vector, Itr begin, Itr end, std::forward_iterator_tag)
	{
		vector.reserve(std::distance(begin, end));
	}

	template <typename Vector, typename Itr>
	static void reserve(Vector&, Itr, Itr, std::input_iterator_tag)
	{
	}

public:
	template <typename InputIterator>
	mw3dPolyLine(const InputIterator& begIt, const InputIterator& endIt)
	{
		reserve(
			m_pointList,
			begIt,
			endIt,
			typename std::iterator_traits<InputIterator>::iterator_category());

		for (InputIterator it = begIt; it != endIt; ++it)
		{
			if (!m_pointList.empty() && m_pointList.back().IsTolerant(*it))
				continue;
			m_pointList.push_back(*it);
		}
	}

	///	AddPoint
	///
	/// Adds a new point to the polyline
	///	@param newPoint ref to mwTPoint3d
	void AddPoint(const TPoint& newPoint)
	{
		if (!m_pointList.empty() && m_pointList.back().IsTolerant(newPoint))
			return;
		m_pointList.push_back(newPoint);
	}

	///	AddPoint
	///
	/// Adds a new point to the poly line
	void AddPoint(const T x, const T y, const T z) { AddPoint(TPoint(x, y, z)); }

	///	InsertPoint
	///
	/// Inserts point prior to specified polyline vertice iterator
	///	@param newPoint point to insert
	///	@param pos position before which point has to be added
	///	@return iterator referencing newly-added point
	PointListIt InsertPoint(const TPoint& newPoint, const PointListIt& pos)
	{
		if (pos != GetPointBegin())
		{
			const PointListIt prv(--PointListIt(pos));
			if (prv->IsTolerant(newPoint))
				return prv;  // do nothing if too close to neighbor(s)
		}
		if (pos != GetPointEnd())
		{
			if (pos->IsTolerant(newPoint))
				return pos;  // do nothing if too close to neighbor(s)
		}
		PointListIt ret(m_pointList.insert(pos, newPoint));
		return ret;
	}

	size_t InsertPoint(const TPoint& newPoint, const size_t pointPositionIdx)
	{
		if (pointPositionIdx >= m_pointList.size())
			throw misc::mwException(0, _T("3d polyline point to insert index is out of bounds"));

		PointListIt i = InsertPoint(newPoint, GetPointBegin() + pointPositionIdx);
		return i - GetPointBegin();
	}

	void InsertPoints(const PointListIt& first, const PointListIt& last, const PointListIt& pos)
	{
		PointListIt newLastPos = last;
		if (pos != GetPointEnd())
		{
			for (; newLastPos != first; --newLastPos)
			{
				if (!(newLastPos - 1)->IsTolerant(*pos))
					break;
			}
		}
		PointListIt insertPos = pos;
		for (PointListIt it = first; it != newLastPos; ++it)
		{
			if (insertPos != GetPointBegin())
			{
				const PointListIt prv(--PointListIt(insertPos));
				if (prv->IsTolerant(*it))
					continue;
			}
			insertPos = m_pointList.insert(insertPos, *it);
			++insertPos;
		}
	}

	///	Remove
	///
	/// Remove point from the point Vec
	///	@param it iterator pointing to the item to be removed
	PointListIt RemovePoint(const PointListIt& it)
	{
		if (it == m_pointList.end())
			throw misc::mwException(0, _T("PolyLine::RemovePoint(). Bad Argument."));
		PointListIt ret(m_pointList.erase(it));
		return ret;
	}

	PointListIt RemovePoints(const PointListIt& it, const PointListIt& it2)
	{
		if (it == m_pointList.end() || it2 > m_pointList.end())
			throw misc::mwException(0, _T("PolyLine::RemovePoint(). Bad Argument."));
		PointListIt ret(m_pointList.erase(it, it2));
		return ret;
	}

	size_t RemovePoint(const size_t pointIdx)
	{
		if (pointIdx >= m_pointList.size())
			throw misc::mwException(0, _T("3d polyline point to remove index is out of bounds"));

		PointListIt nextIterator(RemovePoint(GetPointBegin() + pointIdx));
		return nextIterator - GetPointBegin();
	}

	/// Adds a new line to the poly line
	///	@param line reference to mw3dLine
	void AddLine(const Line& line)
	{
		AddPoint(line.GetStartPoint());
		AddPoint(line.GetEndPoint());
	}

	/// Set begin point
	///
	/// Set begin point at vertex given by point Vec iterator
	///	@param begIt vertex iterator to begin at
	void SetBegin(const PointListConstIt& begIt)
	{
		if (!IsClosed())
			MW_EXCEPTION("Can't cycle begin point on open polyline.");
		if (begIt == m_pointList.end())
			MW_EXCEPTION("Invalid input iterator");
		if (begIt == m_pointList.begin() || begIt == m_pointList.end() - 1)
			return;
		const size_t begIdx = std::distance<PointListConstIt>(m_pointList.begin(), begIt);
		m_pointList.pop_back();
		std::rotate(m_pointList.begin(), m_pointList.begin() + begIdx, m_pointList.end());
		m_pointList.push_back(m_pointList.front());
	}

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

	///	IsContinuous
	///
	/// Returns true if the geometric object is continuous
	///	@returns bool
	bool IsContinuous(const T) const { return !IsEmpty(); }

	///	GetLength
	///
	/// Returns the length of geometric object.
	///	@returns length
	T GetLength() const
	{
		T length(0.0);
		for (LineListConstIt it = GetLineBegin(); it != GetLineEnd(); ++it)
		{
			length += it->GetLength();
		}
		return length;
	}

	/// Gets the number of points
	size_t GetPointCount() const { return m_pointList.size(); }

	/// Gets the number of segments
	size_t GetSegmentsCount() const { return m_pointList.size() < 2 ? 0 : m_pointList.size() - 1; }

	/// GetPointBegin returns first point of polyline
	///
	/// @returns PointListIt
	PointListIt GetPointBegin() { return m_pointList.begin(); }

	/// GetPointEnd returns end of point Vec of polyline
	///
	/// @returns PointListIt
	PointListIt GetPointEnd() { return m_pointList.end(); }

	/// GetPointBegin returns first point of polyline
	///
	/// @returns PointListConstIt
	PointListConstIt GetPointBegin() const { return m_pointList.begin(); }

	/// GetEnd returns end of point Vec of polyline
	///
	/// @returns PointListConstIt
	PointListConstIt GetPointEnd() const { return m_pointList.end(); }

	/// GetReversePointBegin returns first point of reversed polyline
	///
	/// @returns PointListConstReverseIt
	PointListConstReverseIt GetReversePointBegin() const { return m_pointList.rbegin(); }

	/// GetReversePointEnd returns end of point Vec of reversed polyline
	///
	/// @returns PointListConstReverseIt
	PointListConstReverseIt GetReversePointEnd() const { return m_pointList.rend(); }

	/// GetLineBegin returns first line of polyline
	///
	/// @returns LineListConstIt
	LineListConstIt GetLineBegin() const
	{
		return LineListConstIt(m_pointList, m_pointList.begin());
	}

	/// GetLineEnd returns end of line Vec of polyline
	///
	/// @returns LineListConstIt
	LineListConstIt GetLineEnd() const { return LineListConstIt(m_pointList, m_pointList.end()); }

	/// Clear polyline
	void Clear() { m_pointList.clear(); }

	/// confirms if there are no elements inside the polyline
	///
	///	@returns true if the polyline is empty
	const bool IsEmpty() const { return m_pointList.empty(); }

	/// GetStartPoint
	///
	/// Returns the line starting point
	///	@returns const ref to mwTPoint3d
	virtual const TPoint& GetStartPoint() const
	{
		if (m_pointList.empty())
			throw mwcadcamException(mwcadcamException::EMPTY_POLYLINE_DOESNT_HAVE_STARTENDPOINTS);
		return m_pointList.front();
	}

	/// GetEndPoint
	///
	/// Returns the line ending point
	///	@returns const ref to mwTPoint3d
	virtual const TPoint& GetEndPoint() const
	{
		if (m_pointList.empty())
			throw mwcadcamException(mwcadcamException::EMPTY_POLYLINE_DOESNT_HAVE_STARTENDPOINTS);
		return m_pointList.back();
	}


	/// operator []
	///
	/// Provide access to point by index
	///	@param pntIndex point index to access
	///	@returns reference to specified point

	TPoint& operator[](const size_t pntIndex) { return m_pointList.at(pntIndex); }

	/// operator [] const
	///
	/// Provide access to point by index
	///	@param pntIndex point index to access
	///	@returns constant reference to specified point
	const TPoint& operator[](const size_t pntIndex) const { return m_pointList.at(pntIndex); }

	/// Add src polyline to the end of this
	void operator+=(const mw3dPolyLine<T>& src)
	{
		PointListConstIt startSrcIt = src.m_pointList.begin();
		if (!m_pointList.empty())
		{
			for (;
				 startSrcIt != src.m_pointList.end() && m_pointList.back().IsTolerant(*startSrcIt);
				 ++startSrcIt)
				;
		}
		m_pointList.insert(m_pointList.end(), startSrcIt, src.m_pointList.end());
	}

	/// Reverse point sequence in polyline
	void Reverse() { std::reverse(m_pointList.begin(), m_pointList.end()); }

	/// GetBoundingBox function
	///
	///	@returns GetBoundingBox of type virtual const mw2dBoundingBox< T >&
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		using std::swap;

		cadcam::mw3dBoundingBox<T> curBox;
		for (PointListConstIt it = m_pointList.begin(); it != m_pointList.end(); ++it)
		{
			curBox.EnlargeForPoint(*it);
		}
		swap(m_bbox, curBox);
		return m_bbox;
	}

	/// Compare this polyline for equality with given precisely
	bool operator==(const mw3dPolyLine<T>& other) const
	{
		if (other.m_pointList.size() != m_pointList.size())
			return false;

		if (m_pointList.empty())
			return true;

		for (size_t idx = 0; idx < m_pointList.size(); ++idx)
		{
			if (m_pointList[idx] != other.m_pointList[idx])
				return false;
		}

		return true;
	}

	/// Compare this polyline for inequality with given precisely
	bool operator!=(const mw3dPolyLine<T>& other) const { return !(*this == other); }

	/// Swaps this polyline with an other
	void Swap(mw3dPolyLine<T>& other)
	{
		using std::swap;

		swap(m_pointList, other.m_pointList);
		swap(m_bbox, other.m_bbox);
	}

	/// Get segment from point iterator
	///
	///	@param src point iterator
	///	@return segment iterator starting with given point
	LineListConstIt GetLineIt(const PointListConstIt& src) const
	{
		if (*src == GetStartPoint())
			return GetLineBegin();
		return LineListConstIt(m_pointList, src);
	}

	///	IsClosed
	///
	/// Tests and returns true if the polyline is closed
	///	@returns const bool
	bool IsClosed() const
	{
		if (m_pointList.empty())
			throw mwcadcamException(mwcadcamException::CANNOT_DEFINE_IF_EMPTY_CONTOUR_IS_CLOSED);

		// Please don't use GetStartPoint() and GetEndPoint() methods here.
		// It may cause data race in multithreading environment.
		return m_pointList.front() == m_pointList.back();
	}

	/// Close polyline
	void Close()
	{
		if (GetPointCount() < 2)
			throw mwcadcamException(mwcadcamException::CANNOT_CLOSE_POLY_LINE);
		if (!IsClosed())
		{
			for (; GetEndPoint().IsTolerant(GetStartPoint());)
			{
				PointListIt it = GetPointEnd();
				RemovePoint(--it);
				if (GetPointCount() < 2)
					throw mwcadcamException(mwcadcamException::CANNOT_CLOSE_POLY_LINE);
			}
			// we can't put const reference to vector element into push_back to this vector
			// we copy start point to avoid it
			AddPoint(TPoint(GetStartPoint()));
		}
	}

	// Back capability functions. Don't use it anywhere.
	/// Don't use this function. It's back capability.
	void AddPoint(const Point& newPoint) { AddPoint(newPoint.getTPoint()); }
	/// Don't use this function. It's back capability.
	void AddPoint(const PointPtr& newPoint) { AddPoint(newPoint->getTPoint()); }

	/// Reserve specified capacity for AddPoint
	void ReservePoints(size_t capacity) { m_pointList.reserve(capacity); }

	/// Destructor
	virtual ~mw3dPolyLine() {}

	/// Get start point iterator
	PointListIt begin()
	{
		return GetPointBegin();
	}
	
	/// Get end point iterator
	PointListIt end() 
	{
		return GetPointEnd();
	}
	
	/// Get const start point iterator
	PointListConstIt begin() const
	{
		return GetPointBegin();
	}
	
	/// Get const end point iterator
	PointListConstIt end() const
	{
		return GetPointEnd();
	}

private:
	PointList m_pointList;
	mutable mw3dBoundingBox<T> m_bbox;
};

/// Swaps content of polylines
template<typename T>
void swap(mw3dPolyLine<T>& lhs, mw3dPolyLine<T>& rhs)
{
	lhs.Swap(rhs);
}

template<typename T>
typename mw3dPolyLine<T>::PointListIt begin(mw3dPolyLine<T>& pl) 
{
	return pl.GetPointBegin();
}

template<typename T>
typename mw3dPolyLine<T>::PointListIt end(mw3dPolyLine<T>& pl) 
{
	return pl.GetPointEnd();
}

template<typename T>
typename mw3dPolyLine<T>::PointListConstIt begin(const mw3dPolyLine<T>& pl) 
{
	return pl.GetPointBegin();
}

template<typename T>
typename mw3dPolyLine<T>::PointListConstIt end(const mw3dPolyLine<T>& pl) 
{
	return pl.GetPointEnd();
}

}  // namespace cadcam
#endif  //	MW_MW3DPOLYLINE_HPP_
