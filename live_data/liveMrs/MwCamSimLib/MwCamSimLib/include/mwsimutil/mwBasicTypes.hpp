// (C) 2013-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBASICTYPES_HPP_
#define MW_MWBASICTYPES_HPP_

#include "mwDefines.hpp"

#ifndef MW_USE_VS2008_COMPATIBILITY
#include <cstdint>
#endif

namespace misc
{
#ifdef MW_USE_VS2008_COMPATIBILITY
	// older MSVC version do not support C++11 defined types
	typedef signed   __int8 int8_t;
	typedef unsigned __int8 uint8_t;
	typedef          __int16 int16_t;
	typedef unsigned __int16 uint16_t;
	typedef          __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef          __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#else
	// since oldest supported GCC and clang versions as well as MSVC from VS2010
	// are C++11 compliant, use C++11 standard defined types
	using std::int8_t;
	using std::uint8_t;
	using std::int16_t;
	using std::uint16_t;
	using std::int32_t;
	using std::uint32_t;
	using std::int64_t;
	using std::uint64_t;
#endif
}

#endif	//	MW_MWBASICTYPES_HPP_
