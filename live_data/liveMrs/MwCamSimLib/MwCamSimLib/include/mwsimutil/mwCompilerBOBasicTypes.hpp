// (C) 2016-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOMPILERBOBASICTYPES_HPP_
#define MW_MWCOMPILERBOBASICTYPES_HPP_

#include <vector>
#include <list>
#include "mwBinOutputStream.hpp"
#include "mwBinInputStream.hpp"
#include "mwStreamableSpecialTypes.hpp"
#include "mwUTFTypes.hpp"

namespace misc
{
class mwBOBasicTypes;
class mwException;
class mwstring;
class mwIFStream;

//! this class provides the Serialize operators for the c++ basic types
/*! this class alows you to write to a stream the basic c++ types by
	using its << operators
*/
class MW_5AXUTIL_API mwCompilerBOBasicTypes
{
public:
	typedef mwBinInputStream::mwsize_t mwsize_t;
	//! Constructor
	/*!
			\param rOutputStream the output stream to be used for writing
			\param vShrinkData specifies if you are writing shrink data.
			If this param value is true then all the doubles will be cast to
			floats before writing, and all the ints will be cast to
			shorts before writing.
	*/
	mwCompilerBOBasicTypes(mwBinOutputStream& rOutputStream, bool vShrinkData);

	// Basic types

	//! operator<<
	/*!
		\param value of type const double &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const double& value);

	//! operator<<
	/*!
		\param value of type const float &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const float& value);

	//! operator<<
	/*!
		\param value of type const bool &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const bool& value);

	//! operator<<
	/*!
		\param value of type const char &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const char& value);

	//! operator<<
	/*!
		\param value of type const short &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const short& value);

	//! operator<<
	/*!
		\param value of type const int &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const int& value);

	//! operator<<
	/*!
		\param value of type const unsigned char &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const unsigned char& value);

	//! operator<<
	/*!
		\param value of type const unsigned short &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const unsigned short& value);

#ifdef _NATIVE_WCHAR_T_DEFINED
	//! operator<<
	/*!
		\param value of type const unsigned short &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const wchar_t& value);
#endif
	//! operator<<
	/*!
		\param value of type const unsigned int &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const unsigned int& value);

	//! operator<<
	/*!
		\param value of type const long double &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const long double& value);

	//! operator<<
	/*!
		\param value of type const int64_t &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const ::misc::int64_t& value);

	//! operator<<
	/*!
		\param value of type const mwStreamableSize_t &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const mwStreamableSize_t& value);

	//! operator<<
	/*!
		\param value of type const mwStreamableUnsignedInt64 &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const mwStreamableUnsignedInt64& value);

	//! operator<<
	/*!
		\param value of type const misc::mwstring &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const misc::mwstring& value);
	mwBinOutputStream& operator<<(const misc::unicode::utf16_string& value);

	template <typename first_type, typename second_type>
	mwBinOutputStream& operator<<(const std::pair<first_type, second_type>& value)
	{
		(*this) << value.first;
		(*this) << value.second;
		return m_OutputStream;
	}

	//! operator<<
	/*!
		\param value of type const std::vector< vector_type > &
		\return operator<< of type template<class vector_type> mwBinOutputStream&
	*/
	template <typename vector_type>
	mwBinOutputStream& operator<<(const std::vector<vector_type>& value)
	{
		(*this) << mwStreamableSize_t(value.size());
		for (unsigned int i = 0; i < value.size(); i++) (*this) << value[i];

		return m_OutputStream;
	}

	template <typename list_type>
	mwBinOutputStream& operator<<(const std::list<list_type>& value)
	{
		(*this) << mwStreamableSize_t(value.size());
		typename std::list<list_type>::const_iterator it;
		typename std::list<list_type>::const_iterator itEnd = value.end();
		for (it = value.begin(); it != itEnd; ++it)
		{
			(*this) << *it;
		}
		return m_OutputStream;
	}

	//! gets ShrinkData
	/*!
			\return the ShrinkData
	*/
	inline const bool GetShrinkData() const
	{
		return m_ShrinkData;
	}

	//! sets ShrinkData
	/*!
			\param shrinkData the new ShrinkData
	*/
	inline void SetShrinkData(const bool shrinkData)
	{
		m_ShrinkData = shrinkData;
	}

protected:
	bool m_ShrinkData;
	mwBinOutputStream& m_OutputStream;

public:
	mwBinOutputStream& GetOutputStream()
	{
		return m_OutputStream;
	}
	const mwBinOutputStream& GetOutputStream() const
	{
		return m_OutputStream;
	}

private:
	mwCompilerBOBasicTypes& operator=(mwCompilerBOBasicTypes&);

	//! made it private with migration to 64 bytes platform
	/*! If you need to serialize a size_t value (which is 32 bytes on 32 platforms and 64bytes on 64
	   platform) then create an mwStreamableSize_t and use it's operator << which is public. If you
	   need to serialize an uint64_t value (which is 64 bytes on both 32 and 64 platforms)
			then create an mwStreamableUnsignedInt64 and use it's operator << which is public.
		\param value of type const uint64_t &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const ::misc::uint64_t& value);

	friend class misc::mwBOBasicTypes;
};
}  // namespace misc
#endif	//	MW_MWCOMPILERBOBASICTYPES_HPP_
