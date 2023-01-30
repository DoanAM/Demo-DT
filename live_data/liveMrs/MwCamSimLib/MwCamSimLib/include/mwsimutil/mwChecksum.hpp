// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCHECKSUM_HPP_
#define MW_MWCHECKSUM_HPP_

#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"

namespace misc
{

	//!This class represents a checksum class.
	/*!This is a C++ implementation of the RSA MD5 message digest algorithm. 
	The algorithm calculates a 16 byte checksum for array of bytes.
	Full details of the MD5 algorithm are provided within the code.
	The checksum calculated is returned as a 32 character hexadecimal number held in a string
	*/
	class MW_5AXUTIL_API mwChecksum
	{
	public:
		//!The md5 function for text mode 
		/*!The md5 function
			\param	data	a parameter of type const _TCHAR *
			\param	dataLen	a parameter of type unsigned int
			\return	he checksum calculated as a 32 character hexadecimal number 
		*/
		static misc::mwstring md5Text( const wchar_t *data, unsigned int dataLen );

		//!The md5 function for binary mode 
		/*!The md5 function
		\param	data	a parameter of type const char *
		\param	dataLen	a parameter of type unsigned int
		\return	he checksum calculated as a 32 character hexadecimal number 
		*/
		static std::string md5Binary( const char *data, unsigned int dataLen );

		MW_DEPRECATED("Deprecated since 2020.12. Please use the version where dataLen has type unsigned int")
		static misc::mwstring md5Text(const wchar_t* data, unsigned long dataLen)
		{
			return md5Text(data, (unsigned int)dataLen);
		}

		MW_DEPRECATED("Deprecated since 2020.12. Please use the version where dataLen has type unsigned int")
		static std::string md5Binary(const char* data, unsigned long dataLen)
		{
			return md5Binary(data, (unsigned int)dataLen);
		}

	private:
		//! Constructor not allowed since it's a static class
		mwChecksum();
	};
}

#endif	//	MW_MWCHECKSUM_HPP_
