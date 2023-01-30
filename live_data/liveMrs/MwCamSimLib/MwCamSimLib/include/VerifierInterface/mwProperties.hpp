// (C) 2009-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWPROPERTIES_HPP_
#define MW_MWPROPERTIES_HPP_
// #if defined(_MSC_VER) && (_MSC_VER >= 1020)
// # pragma once
// #endif

#include <map>

namespace VerifierUtil
{
/// property template
///
///	This class simply encapsulates a std::map and changes its interface
///	towards a Java like property handling.
///
///
/// @code{.cpp}
///	// example:
///
///	#include "StdAfx.h"
/// #include <mwStockManager/src/mwProperties.hpp>
///
/// #include <iostream>
/// #include <string>
///
///	int _tmain(int argc, _TCHAR* argv[])
///	{
///
///
///		mwProperties< std::string, std::string > zylinder;
///
///		zylinder.SetProperty("Radius", "0.12345");
///		zylinder.SetProperty("Height", "30");
///		zylinder.SetProperty("Width", "50");
///
///		std::cout << "Width = " << zylinder.GetProperty("Width") << std::endl;
///		std::cout << "Radius = " << zylinder.GetProperty("Radius") << std::endl;
///		std::cout << "weisnicht = " << zylinder.GetProperty("weisnicht") << std::endl;
///
///		// 'newHeight' will recieve the value from 'Height'
///		zylinder["newHeight"] = zylinder.GetProperty("Height");
///		// insert 'newProperty'
///		zylinder("newProperty", "newValue");
///
///		return 0;
///	}
/// @endcode
///
///
///
///	Remarks:<br>
///	The operator[] on a map will insert a key/value pair if it isn't already there.<br>
///	Therefore you cannot access a const map using operator [].<br>
///	It's not intended to provide any delete operation.<br>
///

template <class Key, class Value>
class mwProperties
{
private:
	std::map<Key, Value> m_properties;

public:
	Value operator()(Key const& key) const
	{
		typename std::map<Key, Value>::const_iterator it = m_properties.find(key);
		if (it == m_properties.end())
			return Value();
		return (*it).second;
	}
	Value operator()(Key const& key, Value const& value)
	{
		if (IsProperty(key))
			m_properties.erase(key);
		std::pair<typename std::map<Key, Value>::iterator, bool> prop;
		prop = m_properties.insert(std::make_pair(key, value));
		return (*prop.first).second;
	}
	Value GetProperty(Key const& key) const
	{
		typename std::map<Key, Value>::const_iterator it = m_properties.find(key);
		if (it == m_properties.end())
			return Value();
		return (*it).second;
	}
	Value SetProperty(Key const& key, Value const& value)
	{
		if (IsProperty(key))
			m_properties.erase(key);
		std::pair<typename std::map<Key, Value>::iterator, bool> prop;
		prop = m_properties.insert(std::make_pair(key, value));
		return (*prop.first).second;
	}
	bool IsProperty(Key const& key) const
	{
		if (m_properties.find(key) == m_properties.end())
			return false;
		return true;
	}
	Value& operator[](Key const& key)
	{
		return (*((m_properties.insert(make_pair(key, Value()))).first)).second;
	}
	/// Get first occurrence of key for value or empty key.
	Key KeyFromValue(Value const& value)
	{
		for (typename std::map<Key, Value>::iterator it = m_properties.begin();
			 it != m_properties.end();
			 it++)
			if ((*it).second == value)
				return (*it).first;

		return Key();
	}
	size_t size() const { return m_properties.size(); }

	virtual const std::map<Key, Value>& GetPropertyMap() { return m_properties; }
};

}  // end namespace VerifierUtil
#endif  //	MW_MWPROPERTIES_HPP_
