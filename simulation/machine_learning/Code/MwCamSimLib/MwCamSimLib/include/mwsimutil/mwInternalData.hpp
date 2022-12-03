// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWINTERNALDATA_HPP_
#define MW_MWINTERNALDATA_HPP_
#include "mwString.hpp"
#include <vector>

namespace misc
{
// Class used internally by MW only, keeps some internal data
class MW_5AXUTIL_API mwInternalDataElement
{
public:
	mwInternalDataElement() : m_dataID(_T("")), m_dataPtr(NULL)
	{
	}

	mwInternalDataElement(const misc::mwstring& dataID, void* dataPtr)
		: m_dataID(dataID), m_dataPtr(dataPtr)
	{
	}

	const misc::mwstring& GetDataID() const
	{
		return m_dataID;
	}

	void SetDataID(const misc::mwstring& toSet)
	{
		m_dataID = toSet;
	}

	void* GetDataPtr() const
	{
		return m_dataPtr;
	}

	void SetDataPtr(void* toSet)
	{
		m_dataPtr = toSet;
	}

private:
	misc::mwstring m_dataID;
	void* m_dataPtr;
};

// Class used internally by MW only, keeps some internal data
// It is a vector of DataElement objects
class MW_5AXUTIL_API mwInternalData : public std::vector<mwInternalDataElement>
{
public:
	//! Checks if an element with a given ID exists in internal data container
	bool HasElementWithID(const misc::mwstring& elementID) const
	{
		return GetElementWithID(elementID) != end();
	}

	// Gets const_iterator to element with  a given ID from internal data container
	/*
		\returns end() if element with given ID is not present in container
	*/
	const_iterator GetElementWithID(const misc::mwstring& elementID) const
	{
		for (const_iterator it = begin(); it != end(); ++it)
		{
			if (it->GetDataID() == elementID)
				return it;
		}
		return end();
	}

	iterator GetElementWithID(const misc::mwstring& elementID)
	{
		for (iterator it = begin(); it != end(); ++it)
		{
			if (it->GetDataID() == elementID)
				return it;
		}
		return end();
	}

	template <typename T>
	T* GetDataPtr(const misc::mwstring& elementID) const
	{
		const_iterator it = GetElementWithID(elementID);
		return it == end() ? NULL : static_cast<T*>(it->GetDataPtr());
	}

	template <typename T>
	T* GetDataPtr() const
	{
		return GetDataPtr<T>(T::GetInternalDataID());
	}

	template <typename T>
	void SetDataPtr(T* data, const misc::mwstring& elementID)
	{
		iterator it = GetElementWithID(elementID);
		if (it == end())
		{
			push_back(mwInternalDataElement(elementID, data));
		}
		else
		{
			it->SetDataPtr(data);
		}
	}

	template <typename T>
	void SetDataPtr(T* data)
	{
		SetDataPtr(data, T::GetInternalDataID());
	}

};	// mwInternalData

};		// namespace misc
#endif	//	MW_MWINTERNALDATA_HPP_
