// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DCONTOUR_HPP_
#define MW_MW3DCONTOUR_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwGeometryCopy.hpp"
#include "mwcadcamException.hpp"

#include <algorithm>
#include <list>


namespace cadcam
{
template <class T>
class mw3dContour;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw3dContour<T>& cnt, unsigned int);

template <class T>
class MW_5AXUTIL_API mw3dContour: public mw3dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw3dContour<Ty>& cnt, unsigned int);

public:
	// Linux specific
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	typedef typename mw3dGeometry<T>::Point Point;
	// Linux specific

	typedef misc::mwAutoPointer<mw3dContour<T>> Ptr;
	typedef mw3dGeometry<T> Item;
	typedef typename misc::mwAutoPointer<Item> ItemPtr;
	typedef typename std::list<ItemPtr> ItemList;
	typedef typename ItemList::iterator ItemListIt;
	typedef typename ItemList::const_iterator ItemListConstIt;

	/// Constructor
	mw3dContour(): m_bBoxDirty(true) {}

	/// Copy constructor
	///
	/// Creates an exact copy of the Contour
	/// @param toCopy Contour to create a copy of
	mw3dContour(const mw3dContour<T>& toCopy)
		: m_bbox(toCopy.m_bbox), m_bBoxDirty(toCopy.m_bBoxDirty)
	{
		for (ItemListConstIt it = toCopy.GetBegin(); it != toCopy.GetEnd(); ++it)
		{
			m_itemList.push_back(mwGeometryCopy::DeepPtr<T, misc::mwAutoPointer>(**it));
		}
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	inline mw3dContour(mw3dContour<T>&& originalContour) noexcept
		: m_itemList(std::move(originalContour.m_itemList)),
		  m_bbox(std::move(originalContour.m_bbox)),
		  m_bBoxDirty(originalContour.m_bBoxDirty)
	{
	}

	mw3dContour<T>& operator=(const mw3dContour<T>& toCopy) = default;
	mw3dContour<T>& operator=(mw3dContour<T>&& toCopy) noexcept = default;
#endif  // MW_USE_VS2008_COMPATIBILITY

	/// Merge geometries and construct a contour
	template <typename IterT>
	mw3dContour(IterT begIt, IterT endIt): m_bBoxDirty(true)
	{
		for (IterT it = begIt; it != endIt; ++it)
		{
			m_itemList.push_back(mwGeometryCopy::DeepPtr<T, misc::mwAutoPointer>(**it));
		}
	}

	/// Add
	///
	/// Adds a new 3d geometry to the contour
	///	@param obj pointer to 3dGeometry object
	void Add(const ItemPtr& obj)
	{
		m_bBoxDirty = true;
		m_itemList.push_back(obj);
	}

	/// Insert object at a specified position.
	///
	/// Inserts a new 3d geometry to the contour
	/// @param pos the position in the list where the element is inserted.
	///	@param obj the pointer to the element being inserted into the list.
	ItemListIt Insert(const ItemListIt& pos, const ItemPtr& obj)
	{
		m_bBoxDirty = true;
		return m_itemList.insert(pos, obj);
	}

	/// Insert contour at a specified position.
	///
	/// Inserts a new 3d geometry to the contour
	/// @param pos the position in the list where the element is inserted.
	///	@param src the source contour.
	void Insert(const mw3dContour<T>& src, const ItemListIt& pos)
	{
		m_bBoxDirty = true;
		if (&src == this)
		{
			const ItemList tmpItemList = m_itemList;
			m_itemList.insert(pos, tmpItemList.begin(), tmpItemList.end());
			return;
		}
		m_itemList.insert(pos, src.m_itemList.begin(), src.m_itemList.end());
	}

	/// Remove
	///
	/// Removes a 3d geometry from the contour
	///	@param pos position of object to remove
	ItemListIt Remove(const ItemListIt& pos)
	{
		m_bBoxDirty = true;
		return m_itemList.erase(pos);
	}

	/// Remove
	///
	/// Removes a range of 3d geometries from the contour
	///	@param pos position of first object to remove
	///	@param end position of first object after removed sequence
	ItemListIt Remove(const ItemListIt& pos, const ItemListIt& end)
	{
		m_bBoxDirty = true;
		return m_itemList.erase(pos, end);
	}


	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }

	/// GetBegin returns first element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	ItemListIt GetBegin() { return m_itemList.begin(); }

	/// GetEnd returns last element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	ItemListIt GetEnd() { return m_itemList.end(); }

	/// GetBegin returns first element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	ItemListConstIt GetBegin() const { return m_itemList.begin(); }

	/// GetEnd returns last element in the contour vector
	///
	/// @returns ItemList::ItemListIt
	ItemListConstIt GetEnd() const { return m_itemList.end(); }

	/// GetStartPoint
	///
	/// Returns the line starting point
	///	@returns const ref to mwTPoint3d
	virtual const TPoint& GetStartPoint() const { return m_itemList.front()->GetStartPoint(); }

	/// GetEndPoint
	///
	/// Returns the line ending point
	///	@returns const ref to mwTPoint3d
	virtual const TPoint& GetEndPoint() const { return m_itemList.back()->GetEndPoint(); }
	/// confirms if there are no elements inside the contour
	///
	///	@returns true if the contour is empty
	const bool IsEmpty() const { return m_itemList.empty(); }

	/// Add contour
	///
	/// Adds specified contour to this
	void operator+=(const mw3dContour<T>& add) { Insert(add, m_itemList.end()); }


	///	IsContinuous
	///
	/// Returns true if the geometric object is continuous
	///	@returns const bool
	virtual bool IsContinuous(const T tolerance = 0) const
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

	///	IsClosed
	///
	/// Tests and returns true if the contour is closed
	///	@returns const bool
	bool IsClosed() const
	{
		if (m_itemList.empty())
			throw mwcadcamException(mwcadcamException::CANNOT_DEFINE_IF_EMPTY_CONTOUR_IS_CLOSED);
		return IsContinuous() && (GetStartPoint() == GetEndPoint());
	}

	/// Returns the length of the contour
	virtual T GetLength() const
	{
		T length = 0.0;
		for (ItemListConstIt itemIt = GetBegin(); itemIt != GetEnd(); ++itemIt)
		{
			length += (*itemIt)->GetLength();
		}
		return length;
	}

	/// Get number of elements in the contour
	size_t GetCount() const { return m_itemList.size(); }

	/// Clear contour
	void Clear()
	{
		m_itemList.clear();
		m_bBoxDirty = true;
	}

	void SetBegin(const ItemListIt& it) { std::rotate(m_itemList.begin(), it, m_itemList.end()); }

	/// GetBoundingBox function
	///
	///	@returns GetBoundingBox of type virtual const mw3dBoundingBox< T >&
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		if (m_bBoxDirty)
		{
			m_bbox = mw3dBoundingBox<T>();
			for (ItemListConstIt itemIt = m_itemList.begin(); itemIt != m_itemList.end(); ++itemIt)
			{
				m_bbox += (*itemIt)->GetBoundingBox();
			}
			m_bBoxDirty = false;
		}

		return m_bbox;
	}

	/// ReverseOnlyItemsOrder
	///
	/// Invert order of geometries in contour
	void ReverseOnlyItemsOrder()
	{
		m_bBoxDirty = true;
		std::reverse(m_itemList.begin(), m_itemList.end());
	}

	/// Reverse
	///
	/// Full reverse - contour items and their inner ordering
	void Reverse()
	{
		// revers item order
		ReverseOnlyItemsOrder();

		for (ItemListIt itemIt = m_itemList.begin(); itemIt != m_itemList.end(); ++itemIt)
		{
			(*itemIt)->Reverse();
		}
	}

	/// ShallowCopy
	///
	/// Shallow copy original contour
	void ShallowCopy(const mw3dContour<T>& src)
	{
		m_itemList = src.m_itemList;
		m_bbox = src.m_bbox;
		m_bBoxDirty = src.m_bBoxDirty;
	}

	virtual ~mw3dContour() {}

private:
	ItemList m_itemList;
	mutable mw3dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
};
}  // namespace cadcam
#endif  //	MW_MW3DCONTOUR_HPP_
