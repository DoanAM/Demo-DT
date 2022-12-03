// (C) 2010-2020 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTINTERVALLIST_HPP_
#define MW_MWTINTERVALLIST_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTInterval.hpp"
#include "mwAutoPointer.hpp"
#include <functional>
#include <list>
#include <algorithm>

namespace mathdef
{

	template< typename T >
	class MW_5AXUTIL_API mwTIntervalList
	{
	public:

		typedef misc::mwAutoPointer<T> IntervalPtr;
		typedef std::list< IntervalPtr > IntervalList;
		typedef typename IntervalList::iterator iterator;
		typedef typename IntervalList::const_iterator const_iterator;
		typedef typename IntervalList::size_type SizeType;

		bool empty() const
		{
			return m_intervals.empty();
		}

		void clear()
		{
			return m_intervals.clear();
		}

		void swap(mwTIntervalList &toSwap)
		{
			return m_intervals.swap(toSwap.m_intervals);
		}

		SizeType size() const
		{
			return m_intervals.size();
		}

		const_iterator begin() const
		{
			return m_intervals.begin();
		}

		const_iterator end() const
		{
			return m_intervals.end();
		}

		iterator begin()
		{
			return m_intervals.begin();
		}

		iterator end()
		{
			return m_intervals.end();
		}

		void Add(const mwTIntervalList< T > &newList)
		{
			const_iterator it(newList.begin());
			for (; it != newList.end(); ++it)
				Add(*it);
		}

		void Add(const T& newInterval)
		{
			Add(IntervalPtr(new T(newInterval)));
		}

		void Add(IntervalPtr newInterval)
		{
			IntervalPtr newitem = new T(*newInterval);

			if (mathdef::is_gt(newitem->GetStart(), newitem->GetEnd()))
				throw misc::mwException(0, _T("Interval compare failed"));

			typename IntervalList::reverse_iterator it = m_intervals.rbegin();
			while (it != m_intervals.rend())
			{
				T &currmember = **it;

				mwTIntervalPublicIntf::CompareResult ck = currmember.CompareWith(*newitem);

				if (ck == mwTIntervalPublicIntf::greater_intersecting
					|| ck == mwTIntervalPublicIntf::smaller_intersecting
					|| ck == mwTIntervalPublicIntf::subset)
				{
					newitem->Merge(currmember);
					typename IntervalList::iterator leftIt = m_intervals.erase(--(it.base()));
					if (leftIt != m_intervals.end())
					{
						++leftIt;
					}
					it = IntervalList::reverse_iterator(leftIt);
					continue;
				}

				else if (ck == mwTIntervalPublicIntf::equal
					|| ck == mwTIntervalPublicIntf::mainset)
				{
					return;
				}

				else if (ck == mwTIntervalPublicIntf::smaller_separate)
				{
					if (it != m_intervals.rbegin())
					{
						m_intervals.insert(it.base(), newitem);
					}
					else
					{
						m_intervals.push_back(newitem);
					}
					return;
				}
				// else if ( ck == mwCollInterval::compareResult::greater_separate )
				// do nothing go on loop

				++it;
			}

			m_intervals.push_back(newitem);
		}

	private:
		IntervalList m_intervals;
	};

};
#endif	//	MW_MWTINTERVALLIST_HPP_
