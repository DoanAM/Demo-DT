// (C) 2013-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWUTFTYPES_HPP_
#define MW_MWUTFTYPES_HPP_
#include <string>
#include "mwBasicTypes.hpp"


namespace misc
{
	namespace unicode
	{
		typedef uint8_t byte;
		typedef uint8_t utf8;
		typedef uint16_t utf16;
		typedef uint32_t utf32;
		typedef std::basic_string<utf8> utf8_string;
		typedef std::basic_string<utf16> utf16_string;
		typedef std::basic_string<utf32> utf32_string;
		enum encoding
		{
			UTF8=0,
			UTF16LE=1,
			UTF16BE=2,
			UTF32LE=3,
			UTF32BE=4
		};
	}
}
#endif	//	MW_MWUTFTYPES_HPP_
