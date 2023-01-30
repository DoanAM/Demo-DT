// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DCONTOUR_HPP_
#define MW_MW2DCONTOUR_HPP_
#include "mw2dArc.hpp"
#include "mw2dGeometry.hpp"
#include "mwGeometryCopy.hpp"
#include "mwTPoint2d.hpp"
#include "mwTrig.hpp"
#include "mwVectorUtils.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <list>
#include <vector>


#pragma warning(push)
#pragma warning(disable : 4512)  // assignment operator could not be generated

namespace mathdef
{
inline float mw_tol(float);
inline double mw_tol(double);
}  // namespace mathdef

namespace cadcam
{
template <class T>
class mw2dContour;
template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw2dContour<T>& cnt, const unsigned int);
/// Class holding a contour, an array of mw2dGeometry objects
template <class T>
class MW_5AXUTIL_API mw2dContour: public mw2dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw2dContour<Ty>& cnt, const unsigned int);

public:
	typedef misc::mwAutoPointer<mw2dContour<T>> Ptr;
	typedef mw2dGeometry<T> Item;
	typedef typename misc::mwAutoPointer<Item> ItemPtr;
	typedef typename std::list<ItemPtr> ItemList;
	typedef typename ItemList::iterator ItemListIt;
	typedef typename ItemList::const_iterator ItemListConstIt;
	// Linux specific
	typedef typename mw2dGeometry<T>::TPoint TPoint;
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	typedef typename mw2dGeometry<T>::Point Point;
	// Linux specific

	inline mw2dContour();

	/// Merge contours and construct a new one
	inline explicit mw2dContour(const std::vector<mw2dContour<T>>& src);

	/// Merge geometries and construct a contour
	template <typename IterT>
	inline mw2dContour(IterT begIt, IterT endIt);

	/// Copy constructor
	///
	/// Creates an exact copy of the Contour.
	///	@param originalContour Contour to create a copy of
	///	@note deep copy implemented
	inline mw2dContour(const mw2dContour<T>& originalContour);

#ifndef MW_USE_VS2008_COMPATIBILITY
	inline mw2dContour(mw2dContour<T>&& originalContour) noexcept
		: m_itemList(std::move(originalContour.m_itemList)),
		  m_bbox(std::move(originalContour.m_bbox)),
		  m_bBoxDirty(originalContour.m_bBoxDirty)
	{
	}

	mw2dContour<T>& operator=(const mw2dContour<T>& toCopy) = default;
	mw2dContour<T>& operator=(mw2dContour<T>&& toCopy) noexcept = default;
#endif  // MW_USE_VS2008_COMPATIBILITY
	/// Add
	///
	/// Adds a new 2d geometry to the contour
	///	@param obj pointer to 2dGeometry object
	inline void Add(const ItemPtr& obj);

	/// Insert object at a specified position.
	///
	/// Inserts a new 2d geometry to the contour
	///	@param pos the position in the list where the element is inserted.
	///	@param obj pointer to the element being inserted into the list.
	///	@returns ItemList::ItemListIt iterator to currently inserted item
	inline ItemListIt Insert(const ItemListIt& pos, const ItemPtr& obj);

	/// Remove one item
	///
	/// Removes a 2d geometry from the contour
	///	@param pos position of object to remove
	///	@returns ItemList::ItemListIt iterator to item standing right after
	///	removed one
	inline ItemListIt Remove(const ItemListIt& pos);

	/// Remove a sub-sequence
	///
	/// Removes a range of objects from the contour
	///	@param start start position of a sub-sequence to remove
	/// @param end end position of a sub-sequence to remove
	///	@returns ItemList::ItemListIt iterator to item standing right after removed one
	inline ItemListIt Remove(const ItemListIt& start, const ItemListIt& end);

	/// Reverse
	///
	/// Full reverse - contour items and their inner ordering
	inline void Reverse();

	/// Add contour
	///
	/// Adds specified contour to this
	inline void operator+=(const mw2dContour<T>& add);

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	inline virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const;

	/// AcceptVisitor implements changing visitor pattern
	///
	/// @param visitor ref to changing visitor
	inline virtual void AcceptVisitor(mw2dGeometryVisitor<T>& visitor);

	/// GetBegin returns first element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	inline ItemListIt GetBegin();

	/// GetEnd returns last element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	inline ItemListIt GetEnd();

	/// GetBegin returns first element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	inline ItemListConstIt GetBegin() const;

	/// GetEnd returns last element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	inline ItemListConstIt GetEnd() const;

	/// GetStartPoint
	///
	/// Returns the line starting point
	///	@returns const ref to mwTPoint2d
	inline virtual const TPoint& GetStartPoint() const;

	/// GetEndPoint
	///
	/// Returns the line ending point
	///	@returns const ref to mwTPoint2d
	inline virtual const TPoint& GetEndPoint() const;
	/// confirms if there are no elements inside the contour
	///
	///	@returns true if the contour is empty
	inline bool IsEmpty() const;

	///	IsContinuous
	///
	/// Returns true if the geometric object is continuous
	///	@returns bool
	inline virtual bool IsContinuous(const T tolerance = 0) const;

	inline void TryMakeContinuous(const T tolerance = mathdef::mw_tol(T()));

	///	IsClosed
	///
	/// Tests and returns true if the contour is closed
	///	@returns const bool
	inline virtual bool IsClosed() const;

	///	IsClosedWithTolerance
	///
	/// Tests and returns true if the contour's start and end points are within tolerance
	///	@returns const bool
	inline bool IsClosedWithTolerance(const T tolerance = mathdef::mw_tol(T())) const;

	/// Returns the length of the contour
	inline virtual T GetLength() const;

	/// Get number of elements in the contour
	inline size_t GetCount() const;

	/// Clear contour
	inline void Clear();

	inline void SetBegin(const ItemListIt& it);

	/// Splice
	///
	/// Inserts source contour into this from specified position
	///	@param src contour to insert
	///	@param pos item before which src contour should be inserted
	inline void Splice(mw2dContour<T>& src, ItemListIt pos);

	/// ShallowCopy
	///
	///	Shallow copy of contour
	inline void ShallowCopy(const mw2dContour<T>& src);

	/// GetBoundingBox function
	///
	///	@returns GetBoundingBox of type virtual const mw2dBoundingBox< T >&
	inline virtual const mw2dBoundingBox<T>& GetBoundingBox() const;

	inline virtual ~mw2dContour();

protected:
	ItemList m_itemList;
	mutable mw2dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
};

/// Add operator
///
/// Adds to contours
///	@returns contour where first contour's elements are followed by second ones
template <typename T>
mw2dContour<T> operator+(const mw2dContour<T>& first, const mw2dContour<T>& second);
}  // namespace cadcam

namespace cadcam
{
template <class T>
inline mw2dContour<T>::mw2dContour(): m_bBoxDirty(true)
{
}

template <class T>
inline mw2dContour<T>::mw2dContour(const mw2dContour<T>& toCopy)
	: m_bbox(toCopy.m_bbox), m_bBoxDirty(toCopy.m_bBoxDirty)
{
	for (ItemListConstIt it = toCopy.GetBegin(); it != toCopy.GetEnd(); ++it)
	{
		m_itemList.push_back(mwGeometryCopy::DeepPtr<T, misc::mwAutoPointer>(**it));
	}
}

template <class T>
inline mw2dContour<T>::mw2dContour(const std::vector<mw2dContour<T>>& src): m_bBoxDirty(true)
{
	// Linux specific
	for (typename std::vector<mw2dContour<T>>::const_iterator cont = src.begin(); cont != src.end();
		 ++cont)
	{
		for (ItemListConstIt it = cont->m_itemList.begin(); it != cont->m_itemList.end(); ++it)
		{
			m_itemList.push_back(mwGeometryCopy::DeepPtr<T, misc::mwAutoPointer>(**it));
		}
	}
}

template <class T>
template <typename Iter>
inline mw2dContour<T>::mw2dContour(Iter begIt, Iter endIt): m_bBoxDirty(true)
{
	for (Iter it = begIt; it != endIt; ++it)
	{
		m_itemList.push_back(mwGeometryCopy::DeepPtr<T, misc::mwAutoPointer>(**it));
	}
}

template <class T>
inline void mw2dContour<T>::Add(const ItemPtr& obj)
{
	m_itemList.push_back(obj);
	m_bBoxDirty = true;
}

template <class T>
inline typename mw2dContour<T>::ItemListIt mw2dContour<T>::Insert(
	const ItemListIt& pos, const ItemPtr& obj)
{
	m_bBoxDirty = true;
	return m_itemList.insert(pos, obj);
}

template <class T>
inline typename mw2dContour<T>::ItemListIt mw2dContour<T>::Remove(const ItemListIt& pos)
{
	m_bBoxDirty = true;
	return m_itemList.erase(pos);
}

template <class T>
inline typename mw2dContour<T>::ItemListIt mw2dContour<T>::Remove(
	const ItemListIt& start, const ItemListIt& end)
{
	m_bBoxDirty = true;
	return m_itemList.erase(start, end);
}

template <class T>
inline void mw2dContour<T>::Reverse()
{
	if (m_itemList.empty())
		return;

	m_bBoxDirty = true;
	// revers item order
	std::reverse(m_itemList.begin(), m_itemList.end());

	for (ItemListIt itemIt = m_itemList.begin(); itemIt != m_itemList.end(); ++itemIt)
	{
		(*itemIt)->Reverse();
	}
}

template <class T>
inline void mw2dContour<T>::operator+=(const mw2dContour<T>& add)
{
	m_bBoxDirty = true;
	if (&add == this)
	{
		const ItemList tmpItemList = m_itemList;
		m_itemList.insert(m_itemList.end(), tmpItemList.begin(), tmpItemList.end());
		return;
	}
	m_itemList.insert(m_itemList.end(), add.m_itemList.begin(), add.m_itemList.end());
}

template <class T>
inline void mw2dContour<T>::AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const
{
	visitor.Visit(*this);
}

template <class T>
inline void mw2dContour<T>::AcceptVisitor(mw2dGeometryVisitor<T>& visitor)
{
	visitor.Visit(*this);
}

template <class T>
inline typename mw2dContour<T>::ItemListIt mw2dContour<T>::GetBegin()
{
	return m_itemList.begin();
}

template <class T>
inline typename mw2dContour<T>::ItemListIt mw2dContour<T>::GetEnd()
{
	return m_itemList.end();
}

template <class T>
inline typename mw2dContour<T>::ItemListConstIt mw2dContour<T>::GetBegin() const
{
	return m_itemList.begin();
}

template <class T>
inline typename mw2dContour<T>::ItemListConstIt mw2dContour<T>::GetEnd() const
{
	return m_itemList.end();
}

template <class T>
inline const typename mw2dContour<T>::TPoint& mw2dContour<T>::GetStartPoint() const
{
	if (m_itemList.empty())
		throw mwcadcamException(mwcadcamException::EMPTY_CONTOUR_DOESNT_HAVE_STARTENDPOINTS);

	return m_itemList.front()->GetStartPoint();
}

template <class T>
inline const typename mw2dContour<T>::TPoint& mw2dContour<T>::GetEndPoint() const
{
	if (m_itemList.empty())
		throw mwcadcamException(mwcadcamException::EMPTY_CONTOUR_DOESNT_HAVE_STARTENDPOINTS);

	return m_itemList.back()->GetEndPoint();
}

template <class T>
inline bool mw2dContour<T>::IsEmpty() const
{
	return m_itemList.empty();
}

template <class T>
inline bool mw2dContour<T>::IsContinuous(const T tolerance /*= 0*/) const
{
	if (IsEmpty())
		return false;

	if (!(*GetBegin())->IsContinuous(tolerance))
		return false;
	for (ItemListConstIt it1 = m_itemList.begin(), it2 = ++m_itemList.begin();
		 it2 != m_itemList.end();
		 it1 = it2, ++it2)
	{
		if (!(*it2)->IsContinuous(tolerance))
			return false;
		const TPoint& s = (*it2)->GetStartPoint();
		const TPoint& e = (*it1)->GetEndPoint();
		if (tolerance == 0)
		{
			if (s != e)
				return false;
		}
		else
		{
			if (!s.IsTolerant(e, tolerance))
				return false;
		}
	}
	return true;
}

template <class T>
inline void mw2dContour<T>::TryMakeContinuous(const T tolerance /*= mathdef::mw_tol(T())*/)
{
	if (!IsContinuous(tolerance))
	{
		for (ItemListIt it = m_itemList.begin(); it != m_itemList.end(); ++it)
		{
			ItemPtr theBaseItem = *it;
			const TPoint& endPnt = theBaseItem->GetEndPoint();
			const TPoint& begPnt = theBaseItem->GetStartPoint();

			ItemListIt itCmp = it;
			for (++itCmp; itCmp != m_itemList.end(); ++itCmp)
			{
				// look if they are ordered!
				ItemPtr theItem = *itCmp;
				TPoint chkBegPnt = theItem->GetStartPoint();
				TPoint chkEndPnt = theItem->GetEndPoint();

				bool bMoveIt = false;
				if (endPnt.IsTolerant(chkBegPnt, tolerance))
				{
					bMoveIt = true;
				}
				else if (endPnt.IsTolerant(chkEndPnt, tolerance))
				{
					theItem->Reverse();
					bMoveIt = true;
				}
				else if (begPnt.IsTolerant(chkBegPnt, tolerance))
				{
					theBaseItem->Reverse();
					bMoveIt = true;
				}
				else if (begPnt.IsTolerant(chkEndPnt, tolerance))
				{
					theBaseItem->Reverse();
					theItem->Reverse();
					bMoveIt = true;
				}

				if (bMoveIt)
				{
					ItemListIt itCmpPrev = itCmp;
					--itCmpPrev;

					if (itCmpPrev == it)
						break;
					else
					{
						ItemListIt itNext = it;
						++itNext;

						Insert(itNext, theItem);
						Remove(itCmp);
						it = GetBegin();
						break;
					}
				}
			}
		}
	}
}

template <class T>
inline bool mw2dContour<T>::IsClosed() const
{
	if (m_itemList.empty())
		throw mwcadcamException(mwcadcamException::CANNOT_DEFINE_IF_EMPTY_CONTOUR_IS_CLOSED);
	return IsContinuous() && (GetStartPoint() == GetEndPoint());
}

template <class T>
inline bool mw2dContour<T>::IsClosedWithTolerance(const T tolerance) const
{
	if (m_itemList.empty())
		throw mwcadcamException(mwcadcamException::CANNOT_DEFINE_IF_EMPTY_CONTOUR_IS_CLOSED);
	return IsContinuous(tolerance) && (GetStartPoint().IsTolerant(GetEndPoint(), tolerance));
}

template <class T>
inline T mw2dContour<T>::GetLength() const
{
	T length = 0.0;
	for (ItemListConstIt it = m_itemList.begin(); it != m_itemList.end(); ++it)
	{
		length += (*it)->GetLength();
	}
	return length;
}

template <class T>
inline size_t mw2dContour<T>::GetCount() const
{
	return m_itemList.size();
}

template <class T>
inline void mw2dContour<T>::Clear()
{
	m_itemList.clear();
	m_bBoxDirty = true;
}

template <class T>
inline void mw2dContour<T>::SetBegin(const ItemListIt& it)
{
	std::rotate(m_itemList.begin(), it, m_itemList.end());
}

template <class T>
inline const mw2dBoundingBox<T>& mw2dContour<T>::GetBoundingBox() const
{
	if (m_bBoxDirty)
	{
		m_bbox = mw2dBoundingBox<T>();
		for (ItemListConstIt itemIt = m_itemList.begin(); itemIt != m_itemList.end(); ++itemIt)
		{
			m_bbox += (*itemIt)->GetBoundingBox();
		}
		m_bBoxDirty = false;
	}

	return m_bbox;
}

template <typename T>
inline void mw2dContour<T>::Splice(mw2dContour<T>& src, ItemListIt pos)
{
	m_itemList.splice(pos, src.m_itemList);
}

template <typename T>
inline void mw2dContour<T>::ShallowCopy(const mw2dContour<T>& src)
{
	m_itemList = src.m_itemList;
	m_bbox = src.m_bbox;
	m_bBoxDirty = src.m_bBoxDirty;
}

template <typename T>
inline mw2dContour<T> operator+(const mw2dContour<T>& first, const mw2dContour<T>& second)
{
	mw2dContour<T> res = first;
	mw2dContour<T> secondCopy = mwGeometryCopy::Deep(second);
	res.Splice(secondCopy, res.GetEnd());
	return res;
}

template <class T>
inline mw2dContour<T>::~mw2dContour()
{
}

template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mw2dContour<T>& toDump)
{
	class LoggerVisitor: public cadcam::mw2dGeometryConstVisitor<T>
	{
	public:
		LoggerVisitor(misc::mwLogger& os): m_os(os) {}

		virtual void Visit(const mw2dPoint<T>& /*tv*/)
		{
			m_os << _T("mw2dPoint (not implemented)");
		}

		virtual void Visit(const mw2dLine<T>& tv) { m_os << tv; }
		virtual void Visit(const mw2dArc<T>& tv) { m_os << tv; }
		virtual void Visit(const mw2dContour<T>& tv) { m_os << tv; }
		virtual void Visit(const mw2dPolyLine<T>& /*tv*/)
		{
			m_os << _T("mw2dPolyLine (not implemented)");
		}
		virtual void Visit(const mw2dCurve<T>& /*tv*/)
		{
			m_os << _T("mw2dCurve (not implemented)");
		}

	private:
		misc::mwLogger& m_os;
	};

	os << _T("class cadcam::mw2dContour\n");

	typename cadcam::mw2dContour<T>::ItemListConstIt it = toDump.GetBegin();
	typename cadcam::mw2dContour<T>::ItemListConstIt itEnd = toDump.GetEnd();
	for (; it != itEnd; ++it)
	{
		LoggerVisitor loggerVisitor(os);
		(*it)->AcceptVisitor(loggerVisitor);
	}

	os << _T("class cadcam::mw2dContour end\n");
	return os;
}
}  // namespace cadcam

#pragma warning(pop)

#endif  //	MW_MW2DCONTOUR_HPP_
