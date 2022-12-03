// (C) 2011-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWLINECONTAINERITERATORCONVERTOR_HPP_
#define MW_MWLINECONTAINERITERATORCONVERTOR_HPP_

#include "mwAutoPointer.hpp"

#include <vector>

namespace cadcam
{
template <class TPoint, class TLine>
class MW_5AXUTIL_API mwLineContainerConstIteratorConvertor
{
public:
	typedef TPoint Point;
	typedef std::vector<Point> Container;
	typedef typename Container::const_iterator CntIt;

	typedef TLine Line;
	typedef misc::mwAutoPointer<Line> LinePtr;
	typedef const misc::mwAutoPointer<const TLine> LineConstPtr;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef TLine value_type;
	typedef std::ptrdiff_t difference_type;
	typedef const TLine* pointer;
	typedef const TLine& reference;

	mwLineContainerConstIteratorConvertor() : m_it(CntIt()), m_isLineBroken(true), m_cont(MW_NULL)
	{
	}

	mwLineContainerConstIteratorConvertor(const Container& cont, const CntIt& it)
		: m_it(it), m_isLineBroken(true), m_cont(&cont)
	{
		if (m_it == cont.end() && !cont.empty())
		{
			--m_it;
		}
	}

	mwLineContainerConstIteratorConvertor(const mwLineContainerConstIteratorConvertor& it)
		: m_it(it.m_it), m_isLineBroken(it.m_isLineBroken), m_line(it.m_line), m_cont(it.m_cont)
	{
	}

	reference operator*() const
	{
		if (m_isLineBroken)
		{
			if (m_cont == MW_NULL || m_cont->end() - m_it <= 1 || m_it - m_cont->begin() < 0)
				MW_EXCEPTION("Dereference of bad pointer");
			CntIt nextIt(m_it);
			++nextIt;
			m_line.SetVertices(*m_it, *nextIt);
			m_isLineBroken = false;
		}
		return m_line;
	}
	pointer operator->() const { return &operator*(); }

	mwLineContainerConstIteratorConvertor<TPoint, TLine>& operator=(
		const mwLineContainerConstIteratorConvertor<TPoint, TLine>& it)
	{
		m_cont = it.m_cont;
		m_it = it.m_it;
		m_isLineBroken = true;
		return *this;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine>& operator++()
	{
		++m_it;
		m_isLineBroken = true;
		return *this;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine> operator++(int)
	{
		mwLineContainerConstIteratorConvertor<TPoint, TLine> returnValue(*this);
		++m_it;
		m_isLineBroken = true;
		return returnValue;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine>& operator--()
	{
		--m_it;
		m_isLineBroken = true;
		return *this;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine> operator--(int)
	{
		mwLineContainerConstIteratorConvertor<TPoint, TLine> returnValue(*this);
		--m_it;
		m_isLineBroken = true;
		return returnValue;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine>& operator+=(const size_t idxShift)
	{
		m_it += idxShift;
		m_isLineBroken = true;
		return *this;
	}

	bool operator==(const mwLineContainerConstIteratorConvertor<TPoint, TLine>& iter) const
	{
		return m_it == iter.m_it;
	}

	bool operator!=(const mwLineContainerConstIteratorConvertor<TPoint, TLine>& iter) const
	{
		return !(*this == iter);
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine> operator+(int idxShift)
	{
		mwLineContainerConstIteratorConvertor<TPoint, TLine> returnValue(*this);
		returnValue += idxShift;
		return returnValue;
	}

	mwLineContainerConstIteratorConvertor<TPoint, TLine> operator-(int idxShift)
	{
		return (*this + (-idxShift));
	}

	difference_type operator-(const mwLineContainerConstIteratorConvertor& other) const
	{
		return m_it - other.m_it;
	}
	bool operator<(const mwLineContainerConstIteratorConvertor& other) { return m_it < other.m_it; }

protected:
	CntIt m_it;
	mutable bool m_isLineBroken;
	mutable Line m_line;
	const Container* m_cont;
};
}  // namespace cadcam
#endif  //	MW_MWLINECONTAINERITERATORCONVERTOR_HPP_
