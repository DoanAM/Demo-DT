// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DSHAPELIST_HPP_
#define MW_MW3DSHAPELIST_HPP_
#include "mw3dShape.hpp"

#include <list>


namespace cadcam
{
/// Class holding a list of shapes or geometries (of mw3dObjects) to define a complex object
template <class T>
class MW_5AXUTIL_API mw3dShapeList
{
public:
	typedef misc::mwAutoPointer<mw3dShapeList<T>> Ptr;
	/// This class represents a 3d geometry object.
	typedef mw3dObject<T> Item;
	/// This class represents a 3d geometry pointer.
	typedef misc::mwAutoPointer<Item> ItemPtr;
	/// This class represents a 3d geometry list.
	typedef std::list<ItemPtr> ItemList;
	/// This class represents a 3d geometry list ItemListIt.
	typedef typename ItemList::iterator ItemListIt;
	/// This class represents a 3d geometry list const ItemListIt.
	typedef typename ItemList::const_iterator ItemListConstIt;

public:
	/// Constructor
	mw3dShapeList(){};

	/// Copy constructor
	///
	/// Creates an exact copy of a given shape list
	/// @param toCopy shape list to create a copy of
	mw3dShapeList(const mw3dShapeList<T>& toCopy)
	{
		mItemList.assign(toCopy.GetBegin(), toCopy.GetEnd());
		this->mLength = toCopy.mLength;
		this->mLengthValid = toCopy.mLengthValid;
	}

	/// Destructor
	virtual ~mw3dShapeList(){};

public:
	/// Add
	///
	/// Adds a new 3d shape to the list
	///	@param obj ref to 3dGeometry object
	virtual void Add(ItemPtr obj) { mItemList.push_back(obj); }

	/// Add
	///
	/// Appends another shape list (by adding the other elements to the end)
	/// @param objs ref to other shapes' list
	virtual void Add(const mw3dShapeList& objs)
	{
		mItemList.insert(mItemList.end(), objs.GetBegin(), objs.GetEnd());
	}

	/// Insert object at a specified position.
	///
	/// Inserts a new 3d shape to the list
	///            @param pos the position in the list where the element is inserted.
	///	@param obj the value of the element being inserted into the list.
	virtual ItemListIt Insert(ItemListIt pos, ItemPtr obj)
	{
		ItemListIt res = mItemList.insert(pos, obj);
		return res;
	}


	/// Insert shapes at a specified position.
	///
	/// Inserts a new 3d shapes to the list
	///            @param pos the position in the list where the element is inserted.
	///	@param src the source shapes.
	virtual void Insert(mw3dShapeList<T>& src, ItemListIt pos)
	{
		mItemList.insert(pos, src.mItemList.begin(), src.mItemList.end());
	}

	/// Remove
	///
	/// Removes a 3d shapes from the list
	///	@param pos position of object to remove
	virtual ItemListIt Remove(ItemListIt pos)
	{
		ItemListIt ret = mItemList.erase(pos);
		return ret;
	}

	/// Splice
	///
	/// Inserts source list into this from specified position (by moving the source elements)
	///	@param src list to be incorporated
	///	@param pos item position to insert the elements from source list
	void Splice(mw3dShapeList<T>& src, ItemListIt pos) { mItemList.splice(pos, src.mItemList); }

	/// GetBegin returns first element in the list
	///
	/// @returns ItemList::ItemListIt
	ItemListIt GetBegin() { return mItemList.begin(); }

	/// GetEnd returns last element in the list
	///
	/// @returns ItemList::ItemListIt
	ItemListIt GetEnd() { return mItemList.end(); }

	/// GetBegin returns first element in the list
	///
	/// @returns ItemList::ItemListIt
	ItemListConstIt GetBegin() const { return mItemList.begin(); }

	/// GetEnd returns last element in the list
	///
	/// @returns ItemList::ItemListIt
	ItemListConstIt GetEnd() const { return mItemList.end(); }

	/// Get number of elements in the list
	virtual size_t GetCount() const { return mItemList.size(); }

	/// Clear the list
	virtual void Clear() { mItemList.clear(); }

protected:
	ItemList mItemList;

private:
};
}  // namespace cadcam
#endif  //	MW_MW3DSHAPELIST_HPP_
