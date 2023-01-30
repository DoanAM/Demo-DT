// (C) 2014-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBOBASICTYPESDECL_HPP_
#define MW_MWBOBASICTYPESDECL_HPP_

#include "mwDefines.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwCompilerBOBasicTypes.hpp"

namespace pack
{
class mwSolidArchive;
} 

class mwIFStream;

namespace misc
{
class mwException;
class mwFile;
class mwTempFile;
class mwBinOutputStream;
class mwBinInputStream;
class mwstring;
class mwIFStream;

//! this class provides the Serialize operators for the c++ basic types
/*! this class alows you to write to a stream the basic c++ types by
	using its << operators
*/
class MW_5AXUTIL_API mwBOBasicTypes : public mwCompilerBOBasicTypes
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
	mwBOBasicTypes(mwBinOutputStream& rOutputStream, bool vShrinkData);
	// Basic types

	//! operator<< for writting data from a binary temp file
	/*!
		\param file reference to a temp file where the data is read from
		\return the output stream after writting; usefull for operator concatanation
	*/
	mwBinOutputStream& operator<<(const mwTempFile& file);

	//! operator<< for writting data from a binary file
	/*!
		\param file reference to a file where the data is read from
		\return the output stream after writting; usefull for operator concatanation
	*/
	mwBinOutputStream& operator<<(const mwFile& file);

	//! operator<< for writting data from a file input stream
	/*! The first written thing is the length of the data that will be written
		(a long integer); next the actual data is written
		\param file reference to a file stream where the data is read from
		\return the output stream after writting; usefull for operator concatanation
	*/
	mwBinOutputStream& operator<<(mwIFStream& file);

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
		return mwCompilerBOBasicTypes::operator<<(value);
	}

	//! operator<<
	/*!
		\param value of type const std::vector< vector_type > &
		\return operator<< of type template<class vector_type> mwBinOutputStream&
	*/
	template <typename vector_type>
	mwBinOutputStream& operator<<(const std::vector<vector_type>& value)
	{
		return mwCompilerBOBasicTypes::operator<<(value);
	}

	template <typename list_type>
	mwBinOutputStream& operator<<(const std::list<list_type>& value)
	{
		return mwCompilerBOBasicTypes::operator<<(value);
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	//! Serialization of an enum type
	/*!
		\param value object to be serialized
		\return the stream without the bytes used for the deserialization of the object
	*/
	template <class T, class = typename std::enable_if<std::is_enum<T>::value>::type>
	mwBinOutputStream& operator<<(const T& value)
	{
		using UT = typename std::underlying_type<T>::type;
		return mwCompilerBOBasicTypes::operator<<(static_cast<UT>(value));
	}
#endif	// MW_USE_VS2008_COMPATIBILITY

private:
	mwBOBasicTypes& operator=(mwBOBasicTypes&);
	//! made it private with migration to 64 bytes platform
	/*! If you need to serialize a size_t value (which is 32 bytes on 32 platforms and 64bytes on 64
	   platform) then create an mwStreamableSize_t and use it's operator << which is public. If you
	   need to serialize an uint64_t value (which is 64 bytes on both 32 and 64 platforms)
			then create an mwStreamableUnsignedInt64 and use it's operator << which is public.
		\param value of type const uint64_t &
		\return operator<< of type mwBinOutputStream&
	*/
	mwBinOutputStream& operator<<(const ::misc::uint64_t& value);

	template <typename CHAR_TYPE>
	mwBinOutputStream& operator<<(
		std::basic_istream<CHAR_TYPE, std::char_traits<CHAR_TYPE> >& stream);

	//! Writes a file knowing its size
	/*! Helper function for operator<< misc::mwIFStream
		\param file the input file to read content from
		\param size the size of the read/write file
		\return the reference at the enclosing stream
	*/
	template <typename CHAR_TYPE>
	mwBinOutputStream& WriteFileKnowingSize(
		std::basic_istream<CHAR_TYPE, std::char_traits<CHAR_TYPE> >& file, std::streamsize size);

	friend class pack::mwSolidArchive;
};

}  // namespace misc
#endif	//	MW_MWBOBASICTYPESDECL_HPP_
