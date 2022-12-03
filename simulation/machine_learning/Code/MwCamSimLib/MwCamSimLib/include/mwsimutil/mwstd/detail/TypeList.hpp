// (C) 2018-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_TYPELIST_HPP_
#define MW_TYPELIST_HPP_
#include <type_traits>

namespace mwstd {
namespace detail {
namespace tl {

template<bool...>
struct bool_list;

template<class... Ts>
using generate_true_for = bool_list<(sizeof(Ts) == sizeof(Ts)) ...>;



/* first_type
Get the first type in a TypeList
Compiler error if empty
*/

template<class ...Ts>
struct first_type;

template<class T, class ...Ts>
struct first_type<T, Ts...>
{
	using type = T;
};

template<class ...Ts>
using first_type_t = typename first_type<Ts...>::type;



/* type_at
type_at<1, int, char, double>::type -> char
*/

template<unsigned Index, class... Ts>
struct type_at;

template<unsigned Index, class T, class... Ts>
struct type_at<Index, T, Ts...>
{
	using type = typename type_at<Index - 1, Ts...>::type;
};

template<class T, class... Ts>
struct type_at<0, T, Ts...>
{
	using type = T;
};

template<unsigned Index, class... Ts>
using type_at_t = typename type_at<Index, Ts...>::type;


/* index_of
First type is the type to get the index for
index_of<char, int, char, double> -> 1
*/

template <class T, class... Ts>
struct index_of;

template <class T>
struct index_of<T> : std::integral_constant<int, -1>
{ };

template <class T, class ...Ts>
struct index_of<T, T, Ts...> : std::integral_constant<int, 0>
{ };

template <class T, class U, class ...Ts>
struct index_of<T, U, Ts...>
{
private:
	enum { temp = index_of<T, Ts...>::value };
public:
	enum { value = (temp == -1 ? -1 : 1 + temp) };
};


/* all_of
Check if the Predicate holds for all types in the TypeList
*/

template<template<class> class Predicate, class... Ts>
struct all_of
	: std::is_same<
		bool_list<Predicate<Ts>::value...>,
		generate_true_for<Ts...>
	>
{};


/* none_of
*/

template<template<class> class Predicate, class... Ts>
struct none_of
	: std::is_same<
		bool_list<!Predicate<Ts>::value...>,
		generate_true_for<Ts...>
	>
{};


/* count
count the number of appearances of a type within the TypeList
count<int, int, char, double>::value == 1
*/

template<class T, class ...Ts>
struct count;

template<class T>
struct count<T> : std::integral_constant<std::size_t, 0> {};

template<class T, class U, class... Ts>
struct count<T, U, Ts...> :
	std::integral_constant<std::size_t,
		(std::is_same<T, U>::value ? 1 : 0) + count<T, Ts...>::value
	>
{};


/* is_unique
Checks if each type in the TypeList occurs only once
*/
template<class... Ts>
struct is_unique;

template<>
struct is_unique<> : std::true_type {};

template<class T, class... Ts>
struct is_unique<T, Ts...> : std::integral_constant<bool,
		count<T, Ts...>::value == 0
		&& is_unique<Ts...>::value
	>
{};

} //namespace detail
} //namespace tl
} //namespace mwstd
#endif	//	MW_TYPELIST_HPP_
