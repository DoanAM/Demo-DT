// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTRINGCONVERSIONS_HPP_
#define MW_MWSTRINGCONVERSIONS_HPP_

#include "mwBasicTypes.hpp"
#include "mwException.hpp"
#include <iostream>


namespace misc
{


	//! to_ascii function
	/*!
		\param valueString string to convert
		\param len length of string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::string to_ascii( const wchar_t* valueString ,const int len);

	//! to_ascii function
	/*!
		\param valueString char to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::string to_ascii( const wchar_t valueString);

	//! to_ascii function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::string to_ascii( const mwstring &valueString);

	//! from_ascii function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_ascii( const std::string &valueString);

	//! from_ascii function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_ascii( const char* valueString);

	//! from_ascii function
	/*!
		\param valueChar string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_ascii( const char valueChar);

	//! from_wide function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_wide( const std::wstring &valueString);

	//! from_wide function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_wide( const wchar_t* valueString);

	//! from_wide function
	/*!
		\param valueString string to convert
		\param len length of string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_wide( const wchar_t* valueString, const int len);

	//! from_wide function
	/*!
		\param valueChar string to convert
		\return converted string
	*/
	MW_5AXUTIL_API mwstring from_wide( const wchar_t valueChar);

	//! to_wide function
	/*!
		\param valueString string to convert
		\param len length of string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::wstring to_wide( const char* valueString , const int len);

	//! to_wide function
	/*!
		\param valueString string to convert
		\param len length of string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::wstring to_wide( const wchar_t* valueString , const int len);

	//! to_wide function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::wstring to_wide( const mwstring &valueString);

	MW_5AXUTIL_API misc::mwstring from_size_of( const size_t sizeInBytes );

	// Functions for conversion from numeric format  to string



	//! to_utf8 function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API std::string to_utf8( const mwstring &valueString);

	//! from_utf8 function
	/*!
		\param valueString string to convert
		\return converted string
	*/
	MW_5AXUTIL_API misc::mwstring from_utf8( const std::string &valueString, const bool throwExceptionOnFailure = false);

	//! from_value function
	/*!
		\param value of type const int &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const int &value, const unsigned short prec = 0 );

	//! from_value function
	/*!
		\param value of type const long &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const long &value, const unsigned short prec = 0 );

	//! from_value function
	/*!
		\param value of type const double &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const double &value, const unsigned short prec = 0 );


	//! from_double_value function. cut non-significant zero from right.
	/*!
		\param value of type const double &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_double_value( const double &value, const unsigned short prec = 0);


	//! from_value function
	/*!
		\param value of type const float &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const float &value, const unsigned short prec = 0 );

	//! from_value function
	/*!
		\param value of type const unsigned int &
		\param prec of type unsigned        short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const unsigned int &value, const unsigned short prec = 0 );

	MW_5AXUTIL_API misc::mwstring hex_from_value(const unsigned int &value, const unsigned short prec = 0);

	//! from_value function
	/*!
		\param value of type const unsigned long &
		\param prec of type unsigned       short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const unsigned long &value, const unsigned short prec = 0 );

	//! from_value function
	/*!
		\param value of type const char &
		\param prec of type unsigned short
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const char &value, const unsigned short prec = 0 );



	//! from_value function
	/*!
		\param value of type const short &
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const short &value );


	//! from_value function
	/*!
		\param value of type const unsigned short &
		\return from_value of type inline const misc::mwstring
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const unsigned short &value );

#if defined (_WIN32)
	MW_5AXUTIL_API misc::mwstring from_value( const int64_t &value );
	MW_5AXUTIL_API misc::mwstring from_value( const uint64_t &value );
#elif defined(__linux__) || defined(__APPLE__)
    MW_5AXUTIL_API misc::mwstring from_value( const long long &value );
	MW_5AXUTIL_API misc::mwstring from_value( const unsigned long long &value );
#endif

	//! from_value function
	/*!
		\param value of type const misc::mwstring &
		\return from_value of type inline const misc::mwstring
	*/
	inline misc::mwstring from_value( const misc::mwstring &value )
	{
		return value;
	}


// Functions for conversion from string to numeric format



	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type int &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, int &value);


	//! to_Hex function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type int &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_Hex( const misc::mwstring &valueString, int &value );


	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type long &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, long &value);
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, unsigned long &value);

	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type double &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, double &value );

	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type float &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, float &value );

	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type unsigned int &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, unsigned int &value );

	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type unsigned long &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, unsigned long &value );

		//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type char &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, char &value );

	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type int64_t &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, int64_t &value );

	//! to_value function
	/*!
	\param valueString of type const misc::mwstring &
	\param value of type uint64_t &
	\return to_value of type inline void
	*/
#if defined (_WIN32)
	MW_5AXUTIL_API void to_value(const misc::mwstring &valueString, uint64_t &value);
#elif defined(__linux__) || defined(__APPLE__)
	MW_5AXUTIL_API void to_value(const misc::mwstring& valueString, unsigned long long& value);
#endif


	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type short &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, short &value );


	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type unsigned short &
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, unsigned short &value )
	;


	//! to_value function
	/*!
		\param valueString of type const misc::mwstring &
		\param value of type misc::mwstring &
		\return to_value of type inline void
	*/
	inline void to_value( const misc::mwstring &valueString, misc::mwstring &value )
	{
		value = valueString;
	}


//conversions using locale settings

	//! to_value function
	/*!
		\param valueString string to be converted into a number
		\param value long value address to receive the resulting converted number
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, long &value, const misc::mwstring &localeLanguage );
	//! to_value function
	/*!
		\param valueString string to be converted into a number
		\param value unsigned long value address to receive the resulting converted number
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, unsigned long &value, const misc::mwstring &localeLanguage );
	//! to_value function
	/*!
		\param valueString string to be converted into a number
		\param value double value address to receive the resulting converted number
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, double &value, const misc::mwstring &localeLanguage );
	//! to_value function
	/*!
		\param valueString string to be converted into a number
		\param value long double value address to receive the resulting converted number
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, long double &value, const misc::mwstring &localeLanguage );
	//! to_value function
	/*!
		\param valueString string to be converted into a number
		\param value bool value address to receive the resulting converted value (e.g. "1" -> true)
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\return to_value of type inline void
	*/
	MW_5AXUTIL_API void to_value( const misc::mwstring &valueString, bool &value, const misc::mwstring &localeLanguage );
	//! from_value function
	/*!
		\param value long number to be converted into a string
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\param flags formats the resulting string
		\param mask formats the resulting string
		\return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const long value, const misc::mwstring &localeLanguage,
		const std::ios_base::fmtflags flags = std::ios_base::dec, const std::ios_base::fmtflags mask = std::ios_base::basefield);
	//! from_value function
	/*!
		\param value unsigned long number to be converted into a string
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\param flags formats the resulting string
		\param mask formats the resulting string
		\return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const unsigned long value, const misc::mwstring &localeLanguage,
		const std::ios_base::fmtflags flags = std::ios_base::dec, const std::ios_base::fmtflags mask = std::ios_base::basefield);

	MW_5AXUTIL_API misc::mwstring from_value( const unsigned long long value, const misc::mwstring &localeLanguage,
		const std::ios_base::fmtflags flags = std::ios_base::dec, const std::ios_base::fmtflags mask = std::ios_base::basefield);

	//! from_value function
	/*!
		\param value double number to be converted into a string
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\param precision the desired floating precision
		\param flags formats the resulting string
		\param mask formats the resulting string
		\return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const double value, const misc::mwstring &localeLanguage,
		const std::streamsize precision = 16, const std::ios_base::fmtflags flags = std::ios_base::fixed,
		const std::ios_base::fmtflags mask = std::ios_base::floatfield);
	//! from_value function
	/*!
		\param value long double number to be converted into a string
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\param precision the desired floating precision
		\param flags formats the resulting string
		\param mask formats the resulting string
		\return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const long double value, const misc::mwstring &localeLanguage,
		const std::streamsize precision = 16, const std::ios_base::fmtflags flags = std::ios_base::fixed,
		const std::ios_base::fmtflags mask = std::ios_base::floatfield);
	//! from_value function
	/*!
		\param value bool value to be converted into a string (e.g. true -> "1")
		\param localeLanguage the current user account locale language (see MSDN: Table of Language Identifiers )
		\param flags formats the resulting string (e.g. std::ios_base::boolalpha converts true -> "true")
		\return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value( const bool value, const misc::mwstring &localeLanguage,
		const std::ios_base::fmtflags flags = std::ios_base::dec);

	//! from_value_cosmetize function
	/*
		/param numVal is the number to be converted into a string
		/param prec is the desired precision used
		/param removeTrailingZeros specifies if the result will have trailing zeros or not
		/return formated string
	*/
	MW_5AXUTIL_API misc::mwstring from_value_cosmetize(const double& numVal, const unsigned short prec = 16, const bool removeTrailingZeros = true);
	MW_5AXUTIL_API misc::mwstring from_value_cosmetize(const float& numVal, const unsigned short prec = 16, const bool removeTrailingZeros = true);
	MW_5AXUTIL_API misc::mwstring from_value_cosmetize(const unsigned int& numVal, const size_t numberOfDigits);



	//! ConvertBoostFormatedString function
	/* Replaces boost specific place holders with the variables provided as variadic arguments
	   e.g. ConvertBoostFormatedString ("An error occurred at operation %1$s and move %2$s.", "5", "201")
		returns "An error occurred at operation 5 and move 201."
		/param formatString a string containing the boost specific place holders to be replaced by variables
		/param variable number of strings to be used instead of place holders in resulting string
		/return the string with all format place holders replaced by the received arguments
	*/
	MW_5AXUTIL_API misc::mwstring ConvertBoostFormatedString(const char* formatString, ...);


	//! ConvertBoostFormatedString function
	/* Replaces boost specific place holders with the variables provided as variadic arguments
	   e.g. ConvertBoostFormatedString ("An error occurred at operation %1$s and move %2$s.", "5", "201")
		returns "An error occurred at operation 5 and move 201."
		/param formatString a string containing the boost specific place holders to be replaced by variables
		/param variable number of strings to be used instead of place holders in resulting string
		/return the string with all format place holders replaced by the received arguments
	*/
	MW_5AXUTIL_API misc::mwstring ConvertBoostFormatedString(const wchar_t* formatString, ...);


	unsigned short GetDecimalsNumber(double first, double second);
}
#endif	//	MW_MWSTRINGCONVERSIONS_HPP_
