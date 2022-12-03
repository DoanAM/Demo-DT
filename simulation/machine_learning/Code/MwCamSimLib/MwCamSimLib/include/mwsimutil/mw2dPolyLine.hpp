// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYLINE_HPP_
#define MW_MW2DPOLYLINE_HPP_
#include "mw2dLine.hpp"
#include "mwDefines.hpp"
#include "mwLineContainerIteratorConvertor.hpp"

#include <algorithm>
#include <utility>
#include <vector>


namespace cadcam
{
// serialize
template <class T>
class mw2dPolyLine;
template <class Archive, class T>
void serialize(Archive& archive, mw2dPolyLine<T>& polyline, unsigned int);
// end serialize

/// @class mw2dPolyLine
/// Implements 2D polyline.
template <class T>
class MW_5AXUTIL_API mw2dPolyLine: public mw2dGeometry<T>
{
	// serialize
	template <class Archive, class T2>
	friend void cadcam::serialize(Archive& ar, mw2dPolyLine<T2>& polyline, unsigned int);
	// end serialize

public:
	typedef typename mw2dGeometry<T>::Point Point;
	typedef typename mw2dGeometry<T>::TPoint TPoint;
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	typedef typename misc::mwAutoPointer<mw2dPolyLine<T>> Ptr;
	typedef typename std::vector<TPoint> PointList;
	typedef typename PointList::iterator PointListIt;
	typedef typename PointList::const_iterator PointListConstIt;
	typedef typename PointList::const_reverse_iterator PointListConstReverseIt;

	typedef mw2dLine<T> Line;
	typedef cadcam::mwLineContainerConstIteratorConvertor<TPoint, Line> LineListConstIt;
	typedef mw2dBoundingBox<T> BoundingBox;

	/// Default constructor
	mw2dPolyLine() {}

	/// Copy constructor
	mw2dPolyLine(const mw2dPolyLine<T>& toCopy): m_pointList(toCopy.m_pointList) {}

	/// Assignment operator
	mw2dPolyLine<T>& operator=(const mw2dPolyLine<T>& toCopy)
	{
		m_pointList = toCopy.m_pointList;

		return *this;
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	/// Initializer list constructor
	mw2dPolyLine(std::initializer_list<cadcam::mwTPoint2d<T>> points)
		: mw2dPolyLine(points.begin(), points.end())
	{
	}

	/// Move constructor
	mw2dPolyLine(mw2dPolyLine<T>&& toMove) noexcept: m_pointList(std::move(toMove.m_pointList)) {}

	/// Move assignment operator
	mw2dPolyLine<T>& operator=(mw2dPolyLine<T>&& toMove) noexcept
	{
		m_pointList = std::move(toMove.m_pointList);

		return *this;
	}
#endif  // MW_USE_VS2008_COMPATIBILITY

private:
	template <typename Vector, typename Itr>
	static void reserve(Vector& vector, Itr begin, Itr end, std::forward_iterator_tag)
	{
		vector.reserve(vector.size() + std::distance(begin, end));
	}

	template <typename Vector, typename Itr>
	static void reserve(Vector&, Itr, Itr, std::input_iterator_tag)
	{
	}

public:
	template <typename InputIterator>
	mw2dPolyLine(const InputIterator& begIt, const InputIterator& endIt)
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

	///	Add point
	void AddPoint(const TPoint& newPoint)
	{
		if (!m_pointList.empty() && m_pointList.back().IsTolerant(newPoint))
			return;
		m_pointList.push_back(newPoint);
	}

	///	Add point
	void AddPoint(const T x, const T y) { AddPoint(TPoint(x, y)); }

	/// Insert point into position specified by iterator
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


	/// Insert point into position specified by index
	size_t InsertPoint(const TPoint& newPoint, const size_t pointPositionIdx)
	{
		if (pointPositionIdx >= m_pointList.size())
			MW_EXCEPTION("Index of point to insert is out of range");
		PointListIt curInserted = InsertPoint(newPoint, GetPointBegin() + pointPositionIdx);
		return curInserted - GetPointBegin();
	}

	/// Appends points at the end of the polyline
	template <typename InputIterator>
	void Append(const InputIterator& begIt, const InputIterator& endIt)
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

	///	Remove by iterator
	PointListIt RemovePoint(const PointListIt& it)
	{
		if (it == m_pointList.end())
			MW_EXCEPTION("End point can't be removed");
		PointListIt ret(m_pointList.erase(it));
		return ret;
	}

	/// Remove point by index
	size_t RemovePoint(const size_t pointIdx)
	{
		if (pointIdx >= m_pointList.size())
			MW_EXCEPTION("Index of point to remove is out of range");
		PointListIt nextIt = RemovePoint(GetPointBegin() + pointIdx);
		return nextIt - GetPointBegin();
	}

	///	Add segment
	void AddLine(const Line& line)
	{
		AddPoint(line.GetStartPoint());
		AddPoint(line.GetEndPoint());
	}

	/// Set begin point to specified iterator
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

	///	Is it continuous?
	bool IsContinuous(const T) const { return !IsEmpty(); }

	///	Get length
	T GetLength() const
	{
		T length(0.0);
		for (LineListConstIt it = GetLineBegin(); it != GetLineEnd(); ++it)
		{
			length += it->GetLength();
		}
		return length;
	}

	/// Get number of points
	size_t GetPointCount() const { return m_pointList.size(); }

	/// Get number of segments
	size_t GetSegmentsCount() const { return m_pointList.size() < 2 ? 0 : m_pointList.size() - 1; }

	/// Get start point iterator
	PointListIt GetPointBegin() { return m_pointList.begin(); }

	/// Get end point iterator
	PointListIt GetPointEnd() { return m_pointList.end(); }

	/// Get start point iterator
	PointListConstIt GetPointBegin() const { return m_pointList.begin(); }

	/// Get end point iterator
	PointListConstIt GetPointEnd() const { return m_pointList.end(); }

	/// Get start point iterator of reversed polyline
	PointListConstReverseIt GetReversePointBegin() const { return m_pointList.rbegin(); }

	/// Get end point iterator of reversed polyline
	PointListConstReverseIt GetReversePointEnd() const { return m_pointList.rend(); }

	/// Get iterator pointing to the first segment
	LineListConstIt GetLineBegin() const
	{
		return LineListConstIt(m_pointList, m_pointList.begin());
	}

	/// Get iterator pointing to the last segment
	LineListConstIt GetLineEnd() const { return LineListConstIt(m_pointList, m_pointList.end()); }

	/// Clear polyline
	void Clear() { m_pointList.clear(); }

	/// Does polyline have any points?
	const bool IsEmpty() const { return m_pointList.empty(); }

	/// Get start point
	virtual const TPoint& GetStartPoint() const
	{
		if (m_pointList.empty())
			throw mwcadcamException(mwcadcamException::EMPTY_POLYLINE_DOESNT_HAVE_STARTENDPOINTS);
		return m_pointList.front();
	}

	/// Get end point
	virtual const TPoint& GetEndPoint() const
	{
		if (m_pointList.empty())
			throw mwcadcamException(mwcadcamException::EMPTY_POLYLINE_DOESNT_HAVE_STARTENDPOINTS);
		return m_pointList.back();
	}

	/// Get point by index
	TPoint& operator[](const size_t pntIndex) { return m_pointList.at(pntIndex); }

	/// Get point by index
	const TPoint& operator[](const size_t pntIndex) const { return m_pointList.at(pntIndex); }

	/// Add src polyline to the end of this
	void operator+=(const mw2dPolyLine<T>& src)
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

	/// Get polyline bounding box
	virtual const mw2dBoundingBox<T>& GetBoundingBox() const
	{
		using std::swap;
		cadcam::mw2dBoundingBox<T> curBox;
		for (size_t i = 0; i < m_pointList.size(); ++i)
		{
			curBox.EnlargeForPoint(m_pointList[i]);
		}
		swap(m_bbox, curBox);
		return m_bbox;
	}

	/// Compare this polyline with given precisely
	bool operator==(const mw2dPolyLine<T>& other) const
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

	/// Swaps content of polylines
	void Swap(mw2dPolyLine<T>& other)
	{
		using std::swap;

		swap(m_pointList, other.m_pointList);
		swap(m_bbox, other.m_bbox);
	}

	/// Compare this polyline with given precisely
	bool operator!=(const mw2dPolyLine<T>& other) const { return !(*this == other); }

	/// Get segment from point iterator
	LineListConstIt GetLineIt(const PointListConstIt& src) const
	{
		if (*src == GetStartPoint())
			return GetLineBegin();
		return LineListConstIt(m_pointList, src);
	}

	///	Returns true if the polyline is closed
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

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

	/// AcceptVisitor implements changing visitor pattern
	///
	/// @param visitor ref to changing visitor
	void AcceptVisitor(mw2dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	/// This is deprecated, please avoid using it
	void AddPoint(const Point& newPoint) { AddPoint(newPoint.getTPoint()); }
	/// This is deprecated, please avoid using it
	void AddPoint(const PointPtr& newPoint) { AddPoint(newPoint->getTPoint()); }

	/// Reserve specified capacity for AddPoint
	void ReservePoints(size_t capacity) { m_pointList.reserve(capacity); }
	
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
	mutable mw2dBoundingBox<T> m_bbox;
};

/// Swaps content of polylines
template <typename T>
void swap(mw2dPolyLine<T>& lhs, mw2dPolyLine<T>& rhs)
{
	lhs.Swap(rhs);
}

template<typename T>
typename mw2dPolyLine<T>::PointListIt begin(mw2dPolyLine<T>& pl) 
{
	return pl.GetPointBegin();
}

template<typename T>
typename mw2dPolyLine<T>::PointListIt end(mw2dPolyLine<T>& pl) 
{
	return pl.GetPointEnd();
}

template<typename T>
typename mw2dPolyLine<T>::PointListConstIt begin(const mw2dPolyLine<T>& pl) 
{
	return pl.GetPointBegin();
}

template<typename T>
typename mw2dPolyLine<T>::PointListConstIt end(const mw2dPolyLine<T>& pl) 
{
	return pl.GetPointEnd();
}

}  // namespace cadcam
#endif  //	MW_MW2DPOLYLINE_HPP_
