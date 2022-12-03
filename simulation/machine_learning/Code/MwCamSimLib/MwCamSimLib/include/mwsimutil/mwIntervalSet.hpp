// (C) 2009-2021 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWINTERVALSET_HPP_
#define MW_MWINTERVALSET_HPP_
#include "mwException.hpp"
#include "mwMathConstants.hpp"
#include <vector>

namespace mathdef
{
/*!  Class for managing interval sets.
	 Intervals represented by closed-opened segments [a, b)
	 So they should have positive length (i.e. greater than used tolerance)
*/
template<typename T, typename V = std::vector<T> >
class MW_5AXUTIL_API mwIntervalSet
{
	typedef V Vector;
public:
	static T Infinity()
	{
		return mathdef::mw_maxvalue(T()) / 2;
	}

	//! Constructor
	/*! Creates empty set
	*/
	mwIntervalSet()
	{
	}

	//! Constructor
	/*! \param begin beginning of interval to init with
		\param end end of an interval
	*/
	mwIntervalSet(const T& begin, const T& end)
	{
		if(begin < end)
		{
			m_nodes.reserve(2);
			m_nodes.push_back(begin);
			m_nodes.push_back(end);
		}
	}

	//! Constructor
	/*! \param begin beginning of interval to init with
		\param end end of an interval
	*/
	template<class Type>
	mwIntervalSet(Type* begin, Type* end)
	{
		Initialize(Vector(begin, end));
	}

	//! Constructor
	/*! \param points are bounds of intervals to create
	*/
	explicit mwIntervalSet(const std::vector<T>& points)
	{
		Initialize(Vector(points));
	}

	void Reserve(const size_t n)
	{
		m_nodes.reserve(n);
	}

	template<class Type>
	void SafeAssign(Type* begin, Type* end)
	{
		Validate(begin, end);
		UnsafeAssign(begin, end);
	}

	template<class Type>
	void UnsafeAssign(Type* begin, Type* end)
	{
		m_nodes.clear();
		for(Type* it = begin; it != end; ++it)
		{
			m_nodes.push_back(*it);
		}
	}

	//! confirms if there are no intervals in the set
	/*! \returns true if the set is empty
	*/
	bool IsEmpty() const
	{
		return m_nodes.empty();
	}

	//! Clear function
	/*! makes interval empty
		\returns void
	*/
	void Clear()
	{
		m_nodes.clear();
	}

	//! \returns the amount of segments in the set
	size_t GetSize() const
	{
		return m_nodes.size() / 2;
	}

	//! \returns total interval's length
	T GetTotalLength() const
	{
		T result = 0;
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			result += m_nodes[i + 1] - m_nodes[i];
		}
		return result;
	}

	const Vector& GetNodes() const
	{
		return m_nodes;
	}

	//! \returns index-th segments as a pair<T, T>
	std::pair<T, T> operator[](const size_t index) const
	{
		return std::make_pair(
			m_nodes[2 * index],
			m_nodes[2 * index + 1]);
	}

	std::pair<T, T> GetFront() const
	{
		return std::make_pair(
			m_nodes[0],
			m_nodes[1]);
	}

	std::pair<T, T> GetBack() const
	{
		const size_t size = m_nodes.size();
		return std::make_pair(
			m_nodes[size-2],
			m_nodes[size-1]);
	}

	void CopyArray(T dest[], T src[], const size_t size, const bool useForvard)
	{
		if (useForvard)
		{
			for (size_t i = 0; i < size; ++i)
			{
				dest[i] = src[i];
			}
		}
		else
		{
			for (int i = static_cast<int>(size - 1); i >= 0; --i)
			{
				dest[i] = src[i];
			}
		}

	}
	//! unites current set of intervals with new interval [begin, end]
	void Union(T begin, T end, const T tolerance = 0.0)
	{
		if(end <= begin)
			return;
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			const T lo = m_nodes[i];
			const T hi = m_nodes[i + 1];
			if (lo > end + tolerance || hi + tolerance < begin)
			{
				if (lo <= end + tolerance)
					continue;
				m_nodes.resize(m_nodes.size() + 2);
				CopyArray(&(this->m_nodes[i + 2]),
					&(this->m_nodes[i]), (m_nodes.size() - 2 - i), false);
				m_nodes[i] = begin;
				m_nodes[i + 1] = end;
				return;
			}
			if ((begin > lo || end + tolerance >= lo)
				&& begin <= hi + tolerance)
			{
				size_t resultSize = i;
				m_nodes[resultSize++] = (begin > lo) ? lo : begin;
				for (; i < m_nodes.size() && m_nodes[i] <= end; ++i);

				const bool isOdd = (i & 1);
				m_nodes[resultSize++] = isOdd ? m_nodes[i++] : end;
				if (!isOdd && i < m_nodes.size() && m_nodes[i] <= end + tolerance)
				{
					m_nodes[resultSize-1] = m_nodes[++i];
					i++;
				}

				const size_t size = m_nodes.size() - i;
				if (size != 0)
				{
					CopyArray(
						&(this->m_nodes[resultSize]), &(this->m_nodes[i]), size, true);
				}
				this->m_nodes.resize(resultSize + size);
				return;
			}
		}
		m_nodes.resize(m_nodes.size() + 2);
		m_nodes[m_nodes.size() - 2] = begin;
		m_nodes[m_nodes.size() - 1] = end;
	}

	//! Union
	/*!	Unites current set of intervals with the new set of intervals
	*/
	void Union(const mwIntervalSet& ints, const T tolerance = 0.0)
	{
		for(size_t i = 0; i < ints.m_nodes.size(); i += 2)
		{
			Union(ints.m_nodes[i], ints.m_nodes[i + 1], tolerance);
		}
	}

	//! Intersect
	/*!	Makes intersection of the interval set with given interval [begin, end)
		\param const T & begin
		\param const T & end
		\param const T tol
		\returns void
	*/
	void Intersect(const T& begin, const T& end, const T tolerance = 0.0)
	{
		if(end <= begin + tolerance)
		{
			m_nodes.clear();
			return;
		}

		size_t resultSize = 0;
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			if(end < m_nodes[i])
				break;
			if(begin <= m_nodes[i + 1])
			{
				const T lo = mathdef::mw_max(m_nodes[i], begin);
				const T hi = mathdef::mw_min(m_nodes[i + 1], end);
				if(hi > lo + tolerance)
				{
					m_nodes[resultSize++] = lo;
					m_nodes[resultSize++] = hi;
				}
			}
		}
		m_nodes.resize(resultSize);
	}

	bool CheckIntersection(const T& begin, const T& end, const T tolerance = 0.0) const
	{
		if(end <= begin + tolerance)
			return false;

		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			if(end < m_nodes[i])
				break;
			if(begin <= m_nodes[i + 1])
			{
				const T lo = mathdef::mw_max(m_nodes[i], begin);
				const T hi = mathdef::mw_min(m_nodes[i + 1], end);
				if(hi > lo + tolerance)
					return true;
			}
		}
		return false;
	}

	//! Intersect
	/*!	Makes intersection of two sets represented by intervals
		\param const T & begin
		\param const T & end
		\param const T tol
		\returns void
	*/
	void Intersect(const mwIntervalSet& ints, const T tolerance = 0.0)
	{
		if (ints.IsEmpty())
		{
			this->m_nodes.clear();
			return;
		}
		Vector resIntervals(mathdef::mw_max(this->GetSize() * 2, ints.GetSize() * 2) + 2, 0);
		const Vector& currentIntervals = this->m_nodes;
		const Vector& srcIntervals = ints.m_nodes;
		size_t resultSize = 0;
		for (size_t i = 0, j = 0; i < currentIntervals.size() && j < srcIntervals.size();)
		{
			std::pair<T, T> curInterval;
			std::pair<T, T> srcInterval;
			curInterval.first = currentIntervals[i];
			curInterval.second = currentIntervals[i + 1];
			srcInterval.first = srcIntervals[j];
			srcInterval.second = srcIntervals[j + 1];
			if (resultSize + 2 > resIntervals.size())
			{
				resIntervals.resize(currentIntervals.size() - i + srcIntervals.size() - j + resultSize);
			}
			if (srcInterval.second <= srcInterval.first + tolerance)
			{
				j += 2;
				continue;
			}
			if (curInterval.second < srcInterval.first) 
			{
				i += 2;
				continue;
			}
			if (srcInterval.second < curInterval.first)
			{
				j += 2;
				continue;
			}
			if (curInterval.first <= srcInterval.first
				&& curInterval.second >= srcInterval.second )
			{
				if (srcInterval.second > srcInterval.first + tolerance)
				{
					resIntervals[resultSize++] = srcInterval.first;
					resIntervals[resultSize++] = srcInterval.second;
				}
				j += 2;
				continue;
			}
			if (srcInterval.first <= curInterval.first
				&& srcInterval.second >= curInterval.second)
			{
				if (curInterval.second > curInterval.first + tolerance)
				{
					resIntervals[resultSize++] = curInterval.first;
					resIntervals[resultSize++] = curInterval.second;
				}
				i += 2;
				continue;
			}

			if ((curInterval.second >= srcInterval.first)
				&& (curInterval.first <= srcInterval.second))
			{
				const T lo = mathdef::mw_max(curInterval.first, srcInterval.first);
				const T hi = mathdef::mw_min(curInterval.second, srcInterval.second);
				if (hi > lo + tolerance)
				{
					resIntervals[resultSize++] = lo;
					resIntervals[resultSize++] = hi;
				}

				if (curInterval.first >= srcInterval.first
					&& curInterval.first <= srcInterval.second)
				{
					j += 2;
					continue;
				}
				if (srcInterval.first >= curInterval.first
					&& srcInterval.first <= curInterval.second)
				{
					i += 2;
					continue;
				}
			}
		}
		if (resultSize == 0)
		{
			this->m_nodes.clear();
			return;
		}
		this->m_nodes.swap(resIntervals);
		this->m_nodes.resize(resultSize);
	}

	//! Subtract
	/*!	Subtracts one interval [begin, end) from the current set.
		And all remain intervals length will be greater than tolerance
		\param const T & begin
		\param const T & end
		\param const T tol
		\returns void
	*/
	void Subtract(const T& begin, const T& end, const T tolerance = 0.0)
	{
		if(begin >= end)
			return;

		// if [begin, end) is inside of some interval and resulting set size grows
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			if(begin > m_nodes[i] + tolerance
				&& m_nodes[i + 1] > end + tolerance)
			{
				// tempValue is needed to pass vector's element by value into insert()
				// to avoid memory corruption after reallocation.
				const T tempValue = m_nodes[i + 1];
				m_nodes.insert(m_nodes.begin() + i + 2, tempValue);
				m_nodes.insert(m_nodes.begin() + i + 2, end);
				m_nodes[i + 1] = begin;
				return;
			}
		}

		size_t resultSize = 0;
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			if(m_nodes[i + 1] <= begin || end <= m_nodes[i])
			{
				// current interval doesn't have common points with [begin, end)
				m_nodes[resultSize++] = m_nodes[i];
				m_nodes[resultSize++] = m_nodes[i + 1];
			}
			else
			{
				CheckAndAddInterval(m_nodes, resultSize, m_nodes[i], begin, tolerance);
				CheckAndAddInterval(m_nodes, resultSize, end, m_nodes[i + 1], tolerance);
			}
		}
		m_nodes.resize(resultSize);
	}

	//! Subtract
	/*!	Subtracts set of intervals from current one
		\param const mwIntervalSet & ints
		\param const T tolerance
		\returns void
	*/
	void Subtract(const mwIntervalSet& ints, const T tolerance = 0.0)
	{
		for(size_t i = 0; i < ints.m_nodes.size(); i += 2)
		{
			Subtract(ints.m_nodes[i], ints.m_nodes[i + 1], tolerance);
		}
	}

	//! Inverse
	/*!	Inverts current set
		\returns void
	*/
	void Inverse()
	{
		T inf = Infinity();
		if(m_nodes.empty())
		{
			m_nodes.push_back(-inf);
			m_nodes.push_back(inf);
			return;
		}
		if(m_nodes[0] == -inf)
		{
			m_nodes.erase(m_nodes.begin());
		}
		else
		{
			m_nodes.insert(m_nodes.begin(), -inf);
		}
		if(m_nodes.back() == inf)
		{
			m_nodes.pop_back();
		}
		else
		{
			m_nodes.push_back(inf);
		}
	}

	//! Contain
	/*!	Checks if point x is inside one of the intervals [a, b), expanded by tolerance -> [a - tolerance, b + tolerance)
		\param const T & x
		\param const T tolerance
		\returns bool
	*/
	bool Contain(const T& x, const T tolerance = 0.0) const
	{
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			const double& a = m_nodes[i];
			const double& b = m_nodes[i + 1];
			if(a <= x + tolerance && x - tolerance < b)
				return true;
		}
		return false;
	}

	//! Contain
	/*!	Checks if interval [begin, end) is inside one of the intervals [a, b), expanded by tolerance -> [a - tolerance, b + tolerance)
		\param const T st
		\param const T en
		\param const T tol
		\returns bool
	*/
	bool Contain(const T begin, const T end, const T tolerance) const
	{
		for(size_t i = 0; i < m_nodes.size(); i += 2)
		{
			if(mathdef::is_lte(m_nodes[i], begin, tolerance)
				&& mathdef::is_lte(begin, m_nodes[i + 1], tolerance)
				&& mathdef::is_lte(m_nodes[i], end, tolerance)
				&& mathdef::is_lte(end, m_nodes[i + 1], tolerance))
			{
				return true;
			}
		}
		return false;
	}

	bool operator != (const mwIntervalSet& other) const
	{
		return m_nodes != other.m_nodes;
	}

	bool operator == (const mwIntervalSet& other) const
	{
		return m_nodes == other.m_nodes;
	}

private:
	void Validate(const Vector& points)
	{
		if(points.size() % 2 != 0)
			throw misc::mwException(0, _T("Can't create IntervalSet from odd number of points."));
		for(size_t i = 1; i < points.size(); ++i)
		{
			if(points[i] <= points[i - 1])
				throw misc::mwException(0, _T("Can't create IntervalSet from not asceding list of points."));
		}
	}

	template<class Type>
	void Validate(Type* begin, Type* end)
	{
		const size_t size = end - begin;
		if(size % 2 != 0)
			throw misc::mwException(0, _T("Can't create IntervalSet from odd number of points."));
		for(size_t i = 1; i < size; ++i)
		{
			if(begin[i] <= begin[i - 1])
				throw misc::mwException(0, _T("Can't create IntervalSet from not asceding list of points."));
		}
	}

	//! Initialize
	/*!	Validates points and fills m_nodes with points.
		\param const Vector & points
		\returns void
	*/
	void Initialize(const Vector& points)
	{
		Validate(points);
		m_nodes = points;
	}

	//! CheckAndAddInterval
	/*!	Adds interval to existing vector.
		\param Vector & nodes
		\param T begin
		\param T end
		\param T tolerance
		\returns void
	*/
	void CheckAndAddInterval(
		Vector& nodes,
		T begin,
		T end,
		T tolerance)
	{
		if(end > begin + tolerance)
		{
			nodes.push_back(begin);
			nodes.push_back(end);
		}
	}

	//! CheckAndAddInterval
	/*!	Adds interval to existing vector.
		For optimization we use nodesSize and assume that vector has enough space
		\param Vector& nodes
		\param size_t & nodesSize
		\param T begin
		\param T end
		\param T tolerance
		\returns void
	*/
	void CheckAndAddInterval(
		Vector& nodes,
		size_t& nodesSize,
		T begin,
		T end,
		T tolerance)
	{
		if(end > begin + tolerance)
		{
			nodes[nodesSize++] = begin;
			nodes[nodesSize++] = end;
		}
	}

private:
	//! [m_nodes[2 * i], m_nodes[2 * i + 1]) is interval
	Vector m_nodes;
};
}  // namespace mathdef
#endif	//	MW_MWINTERVALSET_HPP_
