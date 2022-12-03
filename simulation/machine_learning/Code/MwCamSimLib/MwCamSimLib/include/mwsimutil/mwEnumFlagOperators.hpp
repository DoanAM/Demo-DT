// (C) 2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

//  WARNING: Although this header is exposed via the ModuleWorks SDK, it is not considered as API.
//  It might be removed or modified at any time. Use at your own risk.

#ifndef MW_MWENUMFLAGOPERATORS_HPP_
#define MW_MWENUMFLAGOPERATORS_HPP_

#include <type_traits>

//  Do not use this macro driectly. Use the .._INNER and .._OUTER macros instead.
#define MW_DETAIL_ENUM_FLAG_OPERATORS(EnumType, Scope) \
	Scope constexpr EnumType operator|(EnumType a, EnumType b)                          \
	{                                                                                   \
		using ut = std::underlying_type_t<EnumType>;                                    \
		return static_cast<EnumType>(static_cast<ut>(a) | static_cast<ut>(b));          \
	}                                                                                   \
	Scope constexpr EnumType operator&(EnumType a, EnumType b)                          \
	{                                                                                   \
		using ut = std::underlying_type_t<EnumType>;                                    \
		return static_cast<EnumType>(static_cast<ut>(a) & static_cast<ut>(b));          \
	}                                                                                   \
	Scope constexpr EnumType operator^(EnumType a, EnumType b)                          \
	{                                                                                   \
		using ut = std::underlying_type_t<EnumType>;                                    \
		return static_cast<EnumType>(static_cast<ut>(a) ^ static_cast<ut>(b));          \
	}                                                                                   \
	Scope constexpr EnumType& operator|=(EnumType& a, EnumType b) { return a = a | b; } \
	Scope constexpr EnumType& operator&=(EnumType& a, EnumType b) { return a = a & b; } \
	Scope constexpr EnumType& operator^=(EnumType& a, EnumType b) { return a = a ^ b; }

// Defines all bitwise operators for an enum class so it can be used as regular flags.
// Used for class member enums.
// Example:
//  class Text
//  {
//  //...
//  enum class Style
//  {
//      bold = 1 << 0,
//      italic = 1 << 1,
//  };
//  MW_ENUM_FLAG_OPERATORS_INNER(Style)
//  //...
//  };
#define MW_ENUM_FLAG_OPERATORS_INNER(EnumType) MW_DETAIL_ENUM_FLAG_OPERATORS(EnumType, friend)

// Defines all bitwise operators for an enum class so it can be used as regular flags.
// Used for enums at namespace-scope.
// Example:
//  namespace Text
//  {
//  //...
//  enum class Style
//  {
//      bold = 1 << 0,
//      italic = 1 << 1,
//  };
//  MW_ENUM_FLAG_OPERATORS_OUTER(Style)
//  //...
//  };
#define MW_ENUM_FLAG_OPERATORS_OUTER(EnumType) MW_DETAIL_ENUM_FLAG_OPERATORS(EnumType, inline)

namespace mwEnumFlags
{
// returns true if all the flags that are set to 1 in rhs, are also set to 1 in lhs
// Example:
//  HasAll(1101, 1101) == true
//  HasAll(1101, 0001) == true
//  HasAll(1101, 0011) == false
template <typename EnumType, std::enable_if_t<std::is_enum<EnumType>::value, int> = 0>
inline bool HasAll(EnumType lhs, EnumType rhs)
{
	return (lhs & rhs) == rhs;
}

// returns true if any of the flags that are set to 1 in rhs, are also set to 1 in lhs
// Example:
//  HasAny(1101, 1101) == true
//  HasAny(1101, 0001) == true
//  HasAny(1101, 0011) == true
//  HasAny(1101, 0010) == false
template <typename EnumType, std::enable_if_t<std::is_enum<EnumType>::value, int> = 0>
inline bool HasAny(EnumType lhs, EnumType rhs)
{
	return (lhs & rhs) != static_cast<EnumType>(0);
}
}

#endif	// MW_MWENUMFLAGOPERATORS_HPP_
