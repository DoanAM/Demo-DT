// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBIBASICTYPES_HPP_
#define MW_MWBIBASICTYPES_HPP_

#include "mwDefines.hpp"
#include "mwFileStream.hpp"
#include "mwCompilerBIBasicTypes.hpp"
#include <type_traits>

namespace pack
{
class mwSolidArchive;
}

namespace misc
{

class mwException;
class mwFile;
class mwTempFile;

//! this class provides the Deserialize operators for the c++ basic types
/*! this class allows you to read from a stream the basic c++ types by
	using its >> operators
*/
class MW_5AXUTIL_API mwBIBasicTypes : public mwCompilerBIBasicTypes
{
public:
	//! Constructor
	/*!
			\param rInputStream the input stream to be used for reading
			\param vShrinkData specifies if you are reading shrink data.
				If this param value is true then all the doubles will be readed as
				they have the size of a float, and all the ints will be readed as
				they have the size of a short.
			\param isUnicode specifies if you are reading unicode data.
			\param is64bBin specifies if you are reading data write by a 64b OS.

	*/
	mwBIBasicTypes(
		mwBinInputStream& rInputStream,
		bool vShrinkData,
		bool isUnicode = false,
		bool is64bBin = false);
	
	// Basic types

	//! operator>> for reading a binary temp file
	/*!
		\param file reference to a temp file where the read data is written
		\return the input stream after reading; usefull for operator concatanation
	*/
	mwBinInputStream& operator>>(mwTempFile& file);

	//! operator>> for reading a binary file
	/*!
		\param file reference to a file where the read data is written
		\return the input stream after reading; usefull for operator concatanation
	*/
	mwBinInputStream& operator>>(mwFile& file);

	//! operator>> for reading into an output file stream
	/*! The first read thing is the length of the data to be read (a long integer)
		next the actual data is read
		\param file reference to a file stream where the read data is written
		\return the input stream after reading; usefull for operator concatanation
	*/
#ifdef _WIN32
	mwBinInputStream& operator>>(mwOFStream& file);
#else
	mwBinInputStream& operator>>(std::ostream& file);
#endif
	//! operator>>
	/*!
		\param value of type double &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(double& value);

	//! operator>>
	/*!
		\param value of type float &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(float& value);

	//! operator>>
	/*!
		\param value of type bool &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(bool& value);

	//! operator>>
	/*!
		\param value of type char &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(char& value);

	//! operator>>
	/*!
		\param value of type short &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(short& value);

	//! operator>>
	/*!
		\param value of type int &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(int& value);

	//! operator>>
	/*!
		\param value of type unsigned char &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(unsigned char& value);

	//! operator>>
	/*!
		\param value of type unsigned short &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(unsigned short& value);

#ifdef _NATIVE_WCHAR_T_DEFINED
	//! operator>>
	/*!
		\param value of type unsigned short &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(wchar_t& value);
#endif
	//! operator>>
	/*!
		\param value of type unsigned int &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(unsigned int& value);

	//! operator>>
	/*!
		\param value of type long double &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(long double& value);

	//! operator>>
	/*!
		\param value of type int64_t &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(::misc::int64_t& value);

	//! operator>>
	/*!
		\param value of type mwStreamableSize_t &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(mwStreamableSize_t& value);

	//! operator>>
	/*!
		\param value of type mwStreamableUnsignedInt64 &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(mwStreamableUnsignedInt64& value);

	//! operator>>
	/*!
		\param value of type misc::mwstring &
		\return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(misc::mwstring& value);
	virtual mwBinInputStream& operator>>(misc::unicode::utf16_string& value);
	

	//! allows deserializing of a std::pair object
	/*!
		\param value object to be deserialize
		\return the stream without the bytes used for deserializing the object
	*/
	template <class T1, class T2>
	mwBinInputStream& operator>>(std::pair<T1, T2>& value)
	{
		return mwCompilerBIBasicTypes::operator>>(value);
	}
	
	//! allows deserializing of a std::vector object
	/*!
		\param value object to be deserialize
		\return the stream without the bytes used for deserializing the object
	*/
	template <class T>
	mwBinInputStream& operator>>(std::vector<T>& value)
	{
		return mwCompilerBIBasicTypes::operator>>(value);
	}
	
	//! allows deserializing of a std::list object
	/*!
		\param value object to be deserialize
		\return the stream without the bytes used for deserializing the object
	*/
	template <class T>
	mwBinInputStream& operator>>(std::list<T>& value)
	{
		return mwCompilerBIBasicTypes::operator>>(value);
	}
	
#ifndef MW_USE_VS2008_COMPATIBILITY
	//! Deserialization of an enum type
	/*!
		\param value object to be deserialize
		\return the stream without the bytes used for deserializing the object
	*/

	template <class T, class = typename std::enable_if<std::is_enum<T>::value>::type>
	mwBinInputStream& operator>>(T& value)
	{
		using UT = typename std::underlying_type<T>::type;
		UT uv = UT();
		auto& stream = mwCompilerBIBasicTypes::operator>>(uv);
		value = static_cast<T>(uv);
		return stream;
	}
#endif  // MW_USE_VS2008_COMPATIBILITY

private:	
	mwBIBasicTypes& operator=(mwBIBasicTypes&);

	//! made it private with migration to 64 bytes platform
	/*! If you need to deserialize a size_t value (which is 32 bytes on 32 platforms and 64bytes on
	   64 platform) then use helper function GetSize_t or create an mwStreamableSize_t and use it's
	   operator >> which is public. If you need to deserialize an uint64_t value (which is
	   64 bytes on both 32 and 64 platforms) then use the helper function GetUnsignedInt64 or create
	   an mwStreamableUnsignedInt64 and use it's operator >> which is public . \param value of type
	   uint64_t & \return operator>> of type virtual mwBinInputStream&
	*/
	virtual mwBinInputStream& operator>>(::misc::uint64_t& value);

	//! Reads a file knowing its size
	/*! Helper function for operator>> misc::mwOFStream
		\param file the output file where to write the read content
		\param size the size of the read/write file
		\return the reference at the enclosing stream
	*/
#ifdef _WIN32
	mwBinInputStream& ReadFileKnowingSize(misc::mwOFStream& file, size_t size);

#endif

	//! access ReadFileKnowingSize private function
	friend class pack::mwSolidArchive;
};
}  // namespace misc
#endif	//	MW_MWBIBASICTYPES_HPP_
