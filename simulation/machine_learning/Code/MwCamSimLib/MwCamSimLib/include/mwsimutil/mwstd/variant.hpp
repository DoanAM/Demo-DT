// (C) 2018-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

// API - Note:
// Before VS2017 (C++17) all entities from namespace mwstd are custom developments from ModuleWorks.
// But from VS2017 (C++17) on, these are just using-declarations of the entities from the C++ Standard Library.
// This implies that users are not allowed to do any forward declarations of these entities as it will give a compiler error when switching to VS2017 (C++17).
// Also note that while an API compatibility is guaranteed, an ABI compatibility is not.


#ifndef MW_VARIANT_HPP_
#define MW_VARIANT_HPP_
#include "mwstd/detail/CompilerConfig.hpp"
#include "mwstd/utility.hpp"

#ifdef MW_STD_DETAIL_HAS_STD_VARIANT

#include <variant>

namespace mwstd
{
using std::bad_variant_access;
using std::get;
using std::get_if;
using std::holds_alternative;
using std::monostate;
using std::variant;
using std::variant_alternative;
using std::variant_alternative_t;
using std::variant_npos;
using std::variant_size;
//using std::variant_size_v; //mwstd does not provide this using-declaration as in its own implementation there is no variant_size_v either.
using std::visit;
}

#else //MW_STD_DETAIL_HAS_STD_VARIANT

#include "mwstd/type_traits.hpp"
#include "mwstd/detail/TypeList.hpp"


#include <cstddef>
#include <exception>
#include <functional>
#include <new>
#include <type_traits>
#include <utility>

namespace mwstd
{

//Forward-declaration of variant<Ts...>
template<class...>
class variant;

namespace detail
{

template<class Variant>
void* get_storage_ptr(Variant& v)
{
	return v.storage_ptr();
}

template<class Variant>
void const* get_storage_ptr(Variant const& v)
{
	return v.storage_ptr();
}


//variant has a converting constructor and assignment operator:
//template<class T> variant(T&& t);
//template<class T> variant& operator=(T&& t)
//Both take a forwarding-reference (T&&) which means, that they are very greedy.
//But they shall only be selected if T is neither:
//1.) variant, 2.) in_place_type_t or 3.) in_place_index_t
//is_valid_type_for_converting_constructor is a type-trait which determines whether T is none of these.

template<class Variant, class Qualified_T> //The second parameter is called Qualified_T because it can be ref-qualified or const/volatile or a combination of those
struct is_valid_type_for_converting_constructor_helper
{
private:
	//First remove all qualifiers and references.
	using T = remove_cvref_t<Qualified_T>;

	struct is_variant_helper : std::is_same<Variant, T> {};

	template<class Type> struct is_in_place_type_t_helper : std::false_type {};
	template<class Type> struct is_in_place_type_t_helper<in_place_type_t<Type>> : std::true_type {};

	template<class Type> struct is_in_place_index_t_helper : std::false_type {};
	template<std::size_t Index> struct is_in_place_index_t_helper<in_place_index_t<Index>> : std::true_type {};

public:
	using type = std::integral_constant<bool, !
		(is_variant_helper::value || is_in_place_type_t_helper<T>::value || is_in_place_index_t_helper<T>::value)
	>;
};


template<class Variant, class Qualified_T>
struct is_valid_type_for_converting_constructor :
	is_valid_type_for_converting_constructor_helper<Variant, Qualified_T>::type
{}; //Using an alias template instead of a new struct for is_valid_type_for_converting_constructor generates an error in VS2013.



//get_matching_alternative_type_and_index is a type-trait for variant::variant(T&&) and variant::operator=(T&&).
//It maps an arbitrary type T to an alternative type in variant.
//This is not the approach as described by the standard. But it is similar to it and has the same result.
//Additionally it is the way, MSVC implements its variant.
//See: https://github.com/microsoft/STL/blob/master/stl/inc/variant#L976

template<class Type, std::size_t Index>
struct type_and_index
{
	using type = Type;
	static const std::size_t index = Index;
};

template<std::size_t Index, class... Ts>
struct build_overload_set_helper;

template<std::size_t Index>
struct build_overload_set_helper<Index>
{};

template<std::size_t Index, class T, class... Ts>
struct build_overload_set_helper<Index, T, Ts...>
	: build_overload_set_helper<Index + 1, Ts...>
{
	using FuncPtr = type_and_index<T, Index>(*)(T);
	operator FuncPtr();
};

template<class UserType, class... Ts>
using get_matching_alternative_type_and_index = decltype(
	std::declval<build_overload_set_helper<0, Ts...>>()(
		std::declval<UserType>()
		)
	);


//Several visitors are used to implement things like the destructor or other SMFs.

struct destruct_visitor
{
	template<class T>
	void operator()(T& t)
	{
#ifdef _MSC_VER
		(t); //Visual Studio < 2017 generates a warning C4100: 't' : unreferenced formal parameters. Adding "(t)" avoids it.
#endif
		t.~T();
	}
};

struct copy_construct_visitor
{
	void* destination;

	template<class T>
	void operator()(T const& source)
	{
		new(destination) T(source);
	}
};

struct move_construct_visitor
{
	void* destination;

	template<class T>
	void operator()(T&& source)
	{
		new(destination) T(std::move(source));
	}
};

struct same_type_copy_assign_visitor
{
	void* destination;

	template<class T>
	void operator()(T const& source)
	{
		T& typed_destination = *static_cast<T*>(destination);
		typed_destination = source;
	}
};

struct same_type_move_assign_visitor
{
	void* destination;

	template<class T>
	void operator()(T&& source)
	{
		T& typed_destination = *static_cast<T*>(destination);
		typed_destination = std::move(source);
	}
};

struct same_type_swap_visitor
{
	void* lhs_destination;

	template<class T>
	void operator()(T& rhs_typed)
	{
		T& lhs_typed = *static_cast<T*>(lhs_destination);
		using std::swap;
		swap(lhs_typed, rhs_typed);
	}
};


//Internal visitor for relational operators https://en.cppreference.com/w/cpp/utility/variant/operator_cmp

#define MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(NAME, OP)						\
	struct rel_op_##NAME##_visitor {												\
		void const* lhs_storage;													\
		template<class T>															\
		bool operator()(T const& rhs_typed) {										\
			T const& lhs_typed = *static_cast<T const*>(lhs_storage);				\
			return lhs_typed OP rhs_typed;											\
		}																			\
	};

MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(equal_to, ==)
MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(not_equal_to, !=)
MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(less, <)
MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(greater, >)
MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(less_equal, <=)
MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR(greater_equal, >=)

#undef MW_STD_DETAIL_VARIANT_DEFINE_REL_OPS_VISITOR


struct get_hash_visitor
{
	template<class T>
	std::size_t operator()(T const& t)
	{
		return std::hash<T>()(t);
	}
};

inline std::size_t hash_combine(std::size_t first, std::size_t second)
{
	//Following implementation is copied from boost container_hash.
	//https://www.boost.org/doc/libs/1_73_0/boost/container_hash/hash.hpp

	// Copyright 2005-2014 Daniel James.
	// Distributed under the Boost Software License, Version 1.0. (See accompanying
	// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

	//  Based on Peter Dimov's proposal
	//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
	//  issue 6.18.
	//
	//  This also contains public domain code from MurmurHash. From the
	//  MurmurHash header:

	// MurmurHash3 was written by Austin Appleby, and is placed in the public
	// domain. The author hereby disclaims copyright to this source code.

	return first ^ (second + 0x9e3779b9 + (first << 6) + (first >> 2));
}


//variants alternative types can be CV-qualified. But mwstd does not handle that. So it will be prohibited via this type-trait.
template<class T>
using IsCVQualified = std::integral_constant<bool, std::is_const<T>::value || std::is_volatile<T>::value >;


} //namespace detail


//https://en.cppreference.com/w/cpp/utility/variant/bad_variant_access

class MWSTD_EXCEPTION_API bad_variant_access : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Bad variant access";
	}
};


//https://en.cppreference.com/w/cpp/utility/variant/monostate

struct monostate
{};

inline bool operator<(monostate, monostate)
{
	return false;
}

inline bool operator>(monostate, monostate)
{
	return false;
}

inline bool operator<=(monostate, monostate)
{
	return true;
}

inline bool operator>=(monostate, monostate)
{
	return true;
}

inline bool operator==(monostate, monostate)
{
	return true;
}

inline bool operator!=(monostate, monostate)
{
	return false;
}


//https://en.cppreference.com/w/cpp/utility/variant/variant_alternative

template<std::size_t I, class Variant>
struct variant_alternative;

template<std::size_t I, class... Ts>
struct variant_alternative<I, variant<Ts...>>
{
	using type = detail::tl::type_at_t<I, Ts...>;
};

template<std::size_t I, class Variant>
struct variant_alternative<I, const Variant>
	: std::add_const<typename variant_alternative<I, Variant>::type>
{};

template<std::size_t I, class Variant>
struct variant_alternative<I, volatile Variant>
	: std::add_volatile<typename variant_alternative<I, Variant>::type>
{};

template<std::size_t I, class Variant>
struct variant_alternative<I, const volatile Variant>
	: std::add_cv<typename variant_alternative<I, Variant>::type> 
{};

template<std::size_t I, class Variant>
using variant_alternative_t = typename variant_alternative<I, Variant>::type;

//https://en.cppreference.com/w/cpp/utility/variant/variant_size

template<class Variant>
struct variant_size;

template<class... Ts>
struct variant_size<variant<Ts...>>
	: std::integral_constant<std::size_t, sizeof...(Ts)>
{};

template<class Variant>
struct variant_size<const Variant> : variant_size<Variant>
{};

template<class Variant>
struct variant_size<volatile Variant> : variant_size<Variant>
{};

template<class Variant>
struct variant_size<const volatile Variant> : variant_size<Variant>
{};


//https://en.cppreference.com/w/cpp/utility/variant/variant_npos
const std::size_t variant_npos = static_cast<std::size_t>(-1);


//https://en.cppreference.com/w/cpp/utility/variant

template<class... Ts>
class variant
{
	static_assert(sizeof...(Ts) != 0, "variant must consist of at least one alternative");
	static_assert(detail::tl::none_of<std::is_array, Ts...>::value, "variant can not have an array type as an alternative");
	static_assert(detail::tl::all_of<std::is_object, Ts...>::value, "variant alternatives must be objects");

	static_assert(detail::tl::is_unique<Ts...>::value, "The standard variant allows the same type multiple times within a variants parameter pack. But mwstd does not support it!");
	static_assert(detail::tl::none_of<detail::IsCVQualified, Ts...>::value, "The standard variant allows cv-qualified types. But mwstd does not support it.");
public:
	variant()
		: index_(0U)
	{
		using first_type = detail::tl::first_type_t<Ts...>;
#ifdef _MSC_VER
#pragma warning(suppress: 4345)
#endif
		new(storage_ptr()) first_type();
	}

	variant(const variant& other)
		: index_(other.index_)
	{
		if (!other.valueless_by_exception())
		{
			detail::copy_construct_visitor vis = { storage_ptr() };
			visit(vis, other);
		}
	}

	variant(variant&& other)
		: index_(other.index_)
	{
		if (!other.valueless_by_exception())
		{
			detail::move_construct_visitor vis = { storage_ptr() };
			visit(vis, std::move(other));
		}
	}

	template<class T,
		class = std::enable_if_t<detail::is_valid_type_for_converting_constructor<variant, T>::value>
	>
	variant(T&& t)
	{
		using matching_type_and_index = detail::get_matching_alternative_type_and_index<T, Ts...>;
		using matching_type = typename matching_type_and_index::type;
		new(storage_ptr()) matching_type(std::forward<T>(t));
		index_ = matching_type_and_index::index;
	}

	template<class T, class... Args>
	explicit variant(in_place_type_t<T>, Args&&... args)
	{
		auto const index = detail::tl::index_of<T, Ts...>::value;
		static_assert(index >= 0, "T is not in the list of alternatives for this variant");
		new(storage_ptr()) T(std::forward<Args>(args)...);
		index_ = index;
	}

	template<std::size_t I, class... Args>
	explicit variant(in_place_index_t<I>, Args&&... args)
		: index_(I)
	{
		typedef typename detail::tl::type_at<I, Ts...>::type ith_type;
		new(storage_ptr()) ith_type(std::forward<Args>(args)...);
	}

	~variant()
	{
		if (!valueless_by_exception())
			visit(detail::destruct_visitor(), *this);
	}

	variant& operator=(const variant& rhs)
	{
		if (valueless_by_exception() && rhs.valueless_by_exception())
			; //both empty => do nothing
		else
			if (rhs.valueless_by_exception())
			{
				//rhs is empty, so also make this empty
				destroy();
			}
			else //rhs isn't empty
			{
				if (index_ == rhs.index_) //both contain the same alternative
				{
					detail::same_type_copy_assign_visitor vis = { storage_ptr() };
					visit(vis, rhs);
				}
				else //this and rhs contain different alternatives and this might be empty
				{
					if (!valueless_by_exception()) //destroy current alternative of this
						destroy();
					//copy rhs alternative into this
					detail::copy_construct_visitor vis = { storage_ptr() };
					visit(vis, rhs);
					index_ = rhs.index_;
				}
			}

		return *this;
	}

	variant& operator=(variant&& rhs)
	{
		if (valueless_by_exception() && rhs.valueless_by_exception())
			; //both empty => do nothing
		else
			if (rhs.valueless_by_exception())
			{
				//rhs is empty, so also make this empty
				destroy();
			}
			else //rhs isn't empty
			{
				if (index_ == rhs.index_) //both contain the same alternative
				{
					detail::same_type_move_assign_visitor vis = { storage_ptr() };
					visit(vis, std::move(rhs));
				}
				else //this and rhs contain different alternatives and this might be empty
				{
					if (!valueless_by_exception()) //destroy current alternative of this
						destroy();
					//move rhs alternative into this
					detail::move_construct_visitor vis = { storage_ptr() };
					visit(vis, std::move(rhs));
					index_ = rhs.index_;
				}
			}

		return *this;
	}

	template<class T>
	std::enable_if_t<detail::is_valid_type_for_converting_constructor<variant, T>::value,
		variant&> operator=(T&& t)
	{
		using matching_type_and_index = detail::get_matching_alternative_type_and_index<T, Ts...>;
		const auto matching_index = matching_type_and_index::index;
		using matching_type = typename matching_type_and_index::type;

		if (index() == matching_index)
			*static_cast<matching_type*>(storage_ptr()) = std::forward<T>(t);
		else
		{
			if (!valueless_by_exception())
				destroy();

			new(storage_ptr()) matching_type(std::forward<T>(t));
			index_ = matching_index;
		}
		return *this;
	}


	template<class T, class... Args>
	T& emplace(Args&&... args)
	{
		auto const index = detail::tl::index_of<T, Ts...>::value;
		static_assert(index >= 0, "T is not in list of alternatives");
		return emplace<index>(std::forward<Args>(args)...);
	}

	template<std::size_t I, class... Args>
	typename variant_alternative<I, variant>::type& emplace(Args&&... args)
	{
		if (!valueless_by_exception())
			destroy();

		using ith_type = detail::tl::type_at_t<I, Ts...>;
		auto* ptr = new(storage_ptr()) ith_type(std::forward<Args>(args)...);
		index_ = I;
		return *ptr;
	}

	void swap(variant& rhs)
	{
		if (valueless_by_exception() && rhs.valueless_by_exception())
			; //do nothing
		else if (index() == rhs.index())
		{
			detail::same_type_swap_visitor vis = { storage_ptr() };
			visit(vis, rhs);
		}
		else
		{
			auto temp = std::move(*this);
			*this = std::move(rhs);
			rhs = std::move(temp);
		}
	}

	std::size_t index() const
	{
		return index_;
	}

	bool valueless_by_exception() const
	{
		return index() == variant_npos;
	}

private:
	using storage_type = std::aligned_union_t<0, Ts...>;

	std::size_t index_;
	storage_type storage_;

	void* storage_ptr()
	{
		return &storage_;
	}

	void const* storage_ptr() const
	{
		return &storage_;
	}

	void destroy()
	{
		visit(detail::destruct_visitor(), *this);
		index_ = variant_npos;
	}

	template<class Variant>
	friend void* detail::get_storage_ptr(Variant& v);

	template<class Variant>
	friend void const* detail::get_storage_ptr(Variant const& v);
};


template<class... Ts>
inline void swap(variant<Ts...>& lhs, variant<Ts...>& rhs)
{
	lhs.swap(rhs);
}


//https://en.cppreference.com/w/cpp/utility/variant/holds_alternative

template<class T, class... Ts>
inline bool holds_alternative(const variant<Ts...>& v)
{
	static_assert(detail::tl::count<T, Ts...>::value == 1, "T must appear exactly once in Types...");
	auto const alternativeIndex = detail::tl::index_of<T, Ts...>::value;
	return v.index() == alternativeIndex;
}


//https://en.cppreference.com/w/cpp/utility/variant/get

template<std::size_t I, class... Ts>
inline variant_alternative_t<I, variant<Ts...>>& get(variant<Ts...>& v)
{
	if (v.index() != I)
		throw bad_variant_access();
	using result_value_type = variant_alternative_t<I, variant<Ts...>>;
	auto const storage_ptr = detail::get_storage_ptr(v);
	return *static_cast<result_value_type*>(storage_ptr);
}

template <std::size_t I, class... Ts>
inline variant_alternative_t<I, variant<Ts...>>&& get(variant<Ts...>&& v)
{
	return std::move(get<I>(v));
}

template<std::size_t I, class... Ts>
inline variant_alternative_t<I, variant<Ts...>> const& get(const variant<Ts...>& v)
{
	if (v.index() != I)
		throw bad_variant_access();
	using result_value_type = variant_alternative_t<I, variant<Ts...>>;
	auto const storage_ptr = detail::get_storage_ptr(v);
	return *static_cast<const result_value_type*>(storage_ptr);
}

template <std::size_t I, class... Ts>
inline variant_alternative_t<I, variant<Ts...>> const&& get(const variant<Ts...>&& v)
{
	return std::move(get<I>(v));
}

template<class T, class... Ts>
inline T& get(variant<Ts...>& v)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T should occur for exactly once in alternatives");
	static_assert(detail::tl::count<T, Ts...>::value <= 1, "T appears more than once in type list");
	return get<index>(v);
}

template<class T, class... Ts>
inline const T& get(const variant<Ts...>& v)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T should occur for exactly once in alternatives");
	static_assert(detail::tl::count<T, Ts...>::value <= 1, "T appears more than once in type list");
	return get<index>(v);
}

template<class T, class... Ts>
inline T&& get(variant<Ts...>&& v)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T should occur for exactly once in alternatives");
	static_assert(detail::tl::count<T, Ts...>::value <= 1, "T appears more than once in type list");
	return get<index>(std::move(v));
}

template<class T, class... Ts>
inline T const&& get(const variant<Ts...>&& v)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T should occur for exactly once in alternatives");
	static_assert(detail::tl::count<T, Ts...>::value <= 1, "T appears more than once in type list");
	return get<index>(std::move(v));
}

//https://en.cppreference.com/w/cpp/utility/variant/get_if


template<std::size_t I, class... Ts>
inline std::add_pointer_t<
	variant_alternative_t<I, variant<Ts...>>
> get_if(variant<Ts...>* pv)
{
	if (pv != nullptr && pv->index() == I)
		return std::addressof(get<I>(*pv));
	else
		return nullptr;
}

template<std::size_t I, class... Ts>
inline std::add_pointer_t<
	variant_alternative_t<I, variant<Ts...>> const
> get_if(variant<Ts...> const* pv)
{
	if (pv != nullptr && pv->index() == I)
		return std::addressof(get<I>(*pv));
	else
		return nullptr;
}

template<class T, class... Ts>
inline std::add_pointer_t<T> get_if(variant<Ts...>* pv)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T must occur in alternatives of variant");
	return get_if<index>(pv);
}

template<class T, class... Ts>
inline std::add_pointer_t<T const> get_if(variant<Ts...> const* pv)
{
	auto const index = detail::tl::index_of<T, Ts...>::value;
	static_assert(index >= 0, "T must occur in alternatives of variant");
	return get_if<index>(pv);
}


//https://en.cppreference.com/w/cpp/utility/variant/visit

//Implement the Visit-helpers here as they need access to get<I>(v) and v.index().
namespace detail
{

template<bool IsValid, class ReturnType>
struct Dispatcher;

template<class ReturnType>
struct Dispatcher<false, ReturnType>
{
	template<std::size_t I, class Visitor, class Variant>
	static ReturnType case_(Visitor&&, Variant&&)
	{
		throw;
	}

	template<std::size_t B, class Visitor, class Variant>
	static ReturnType switch_(Visitor&&, Variant&&)
	{
		throw;
	}
};

template<class ReturnType>
struct Dispatcher<true, ReturnType>
{
	template<std::size_t I, class Visitor, class Variant>
	static ReturnType case_(Visitor&& vis, Variant&& var)
	{
		using ActualReturnType = decltype(std::forward<Visitor>(vis)(get<I>(std::forward<Variant>(var))));
		static_assert(std::is_same<ActualReturnType, ReturnType>::value, "Return-types for visit have to be of the same type");
		return std::forward<Visitor>(vis)(get<I>(std::forward<Variant>(var)));
	}

	template<std::size_t B, class Visitor, class Variant>
	static ReturnType switch_(Visitor&& vis, Variant&& var)
	{
		const auto size = variant_size<std::remove_reference_t<Variant>>::value;
		switch (var.index())
		{
		case B + 0: return Dispatcher<(B + 0 < size), ReturnType>::template case_<B + 0>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 1: return Dispatcher<(B + 1 < size), ReturnType>::template case_<B + 1>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 2: return Dispatcher<(B + 2 < size), ReturnType>::template case_<B + 2>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 3: return Dispatcher<(B + 3 < size), ReturnType>::template case_<B + 3>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 4: return Dispatcher<(B + 4 < size), ReturnType>::template case_<B + 4>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 5: return Dispatcher<(B + 5 < size), ReturnType>::template case_<B + 5>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 6: return Dispatcher<(B + 6 < size), ReturnType>::template case_<B + 6>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 7: return Dispatcher<(B + 7 < size), ReturnType>::template case_<B + 7>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 8: return Dispatcher<(B + 8 < size), ReturnType>::template case_<B + 8>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		case B + 9: return Dispatcher<(B + 9 < size), ReturnType>::template case_<B + 9>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		default: return Dispatcher<(B + 10 < size), ReturnType>::template switch_<B + 10>(std::forward<Visitor>(vis), std::forward<Variant>(var));
		};
	}
};


template<bool IsValid, class ReturnType>
struct Dispatcher2;

template<class ReturnType>
struct Dispatcher2<false, ReturnType>
{
	template<std::size_t I, class Visitor, class Variant1, class Variant2>
	static ReturnType case_(Visitor&&, Variant1&&, Variant2&&)
	{
		throw;
	}

	template<std::size_t B, class Visitor, class Variant1, class Variant2>
	static ReturnType switch_(Visitor&&, Variant1&&, Variant2&&)
	{
		throw;
	}
};

template<class ReturnType>
struct Dispatcher2<true, ReturnType>
{
	template<std::size_t I, class Visitor, class Variant1, class Variant2>
	static ReturnType case_(Visitor&& vis, Variant1&& var1, Variant2&& var2)
	{
		const auto size2 = variant_size<std::remove_reference_t<Variant2>>::value;
		//I == var1.index() * size2 + var2.index();
		const auto VI1 = I / size2;
		const auto VI2 = I % size2;

		using ActualReturnType = decltype(std::forward<Visitor>(vis)(get<VI1>(std::forward<Variant1>(var1)), get<VI2>(std::forward<Variant2>(var2))));
		static_assert(std::is_same<ActualReturnType, ReturnType>::value, "Return-types for visit have to be of the same type");
		return std::forward<Visitor>(vis)(get<VI1>(std::forward<Variant1>(var1)), get<VI2>(std::forward<Variant2>(var2)));
	}

	template<std::size_t B, class Visitor, class Variant1, class Variant2>
	static ReturnType switch_(Visitor&& vis, Variant1&& var1, Variant2&& var2)
	{
		const auto size1 = variant_size<std::remove_reference_t<Variant1>>::value;
		const auto size2 = variant_size<std::remove_reference_t<Variant2>>::value;
		const auto size = size1 * size2;
		const auto index = var1.index() * size2 + var2.index();

		switch (index)
		{
		case B + 0: return Dispatcher2 < (B + 0 < size), ReturnType > ::template case_<B + 0>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 1: return Dispatcher2 < (B + 1 < size), ReturnType > ::template case_<B + 1>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 2: return Dispatcher2 < (B + 2 < size), ReturnType > ::template case_<B + 2>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 3: return Dispatcher2 < (B + 3 < size), ReturnType > ::template case_<B + 3>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 4: return Dispatcher2 < (B + 4 < size), ReturnType > ::template case_<B + 4>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 5: return Dispatcher2 < (B + 5 < size), ReturnType > ::template case_<B + 5>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 6: return Dispatcher2 < (B + 6 < size), ReturnType > ::template case_<B + 6>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 7: return Dispatcher2 < (B + 7 < size), ReturnType > ::template case_<B + 7>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 8: return Dispatcher2 < (B + 8 < size), ReturnType > ::template case_<B + 8>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		case B + 9: return Dispatcher2 < (B + 9 < size), ReturnType > ::template case_<B + 9>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		default: return Dispatcher2 < (B + 10 < size), ReturnType > ::template switch_<B + 10>(std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
		};
	}
};


} //namespace detail


template<class Visitor, class Variant>
inline auto visit(Visitor&& vis, Variant&& var)
-> decltype(std::forward<Visitor>(vis)(get<0>(std::forward<Variant>(var))))
{
	if (var.valueless_by_exception())
		throw bad_variant_access();

	using visit_result_type = decltype(std::forward<Visitor>(vis)(get<0>(std::forward<Variant>(var))));

	return detail::Dispatcher<true, visit_result_type>::template switch_<0>(
		std::forward<Visitor>(vis), std::forward<Variant>(var));
}

template<class Visitor, class Variant1, class Variant2>
inline auto visit(Visitor&& vis, Variant1&& var1, Variant2&& var2)
-> decltype(
	std::forward<Visitor>(vis)(
		get<0>(std::forward<Variant1>(var1)),
		get<0>(std::forward<Variant2>(var2))
		)
	)
{
	if (var1.valueless_by_exception() || var2.valueless_by_exception())
		throw bad_variant_access();

	using visit_result_type =
		decltype(std::forward<Visitor>(vis)(
			get<0>(std::forward<Variant1>(var1)),
			get<0>(std::forward<Variant2>(var2))
			)
		);

	return detail::Dispatcher2<true, visit_result_type>::template switch_<0>(
		std::forward<Visitor>(vis), std::forward<Variant1>(var1), std::forward<Variant2>(var2));
}


//https://en.cppreference.com/w/cpp/utility/variant/operator_cmp

template<class... Ts>
inline bool operator==(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (v.index() != w.index())
		return false;
	if (v.valueless_by_exception())
		return true;
	detail::rel_op_equal_to_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}

template<class... Ts>
inline bool operator!=(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (v.index() != w.index())
		return true;
	if (v.valueless_by_exception())
		return false;
	detail::rel_op_not_equal_to_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}

template<class... Ts>
inline bool operator<(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (w.valueless_by_exception())
		return false;
	if (v.valueless_by_exception())
		return true;
	if (v.index() < w.index())
		return true;
	if (v.index() > w.index())
		return false;
	detail::rel_op_less_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}

template<class... Ts>
inline bool operator>(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (v.valueless_by_exception())
		return false;
	if (w.valueless_by_exception())
		return true;
	if (v.index() > w.index())
		return true;
	if (v.index() < w.index())
		return false;
	detail::rel_op_greater_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}

template<class... Ts>
inline bool operator<=(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (v.valueless_by_exception())
		return true;
	if (w.valueless_by_exception())
		return false;
	if (v.index() < w.index())
		return true;
	if (v.index() > w.index())
		return false;
	detail::rel_op_less_equal_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}

template<class... Ts>
inline bool operator>=(variant<Ts...> const& v, variant<Ts...> const& w)
{
	if (w.valueless_by_exception())
		return true;
	if (v.valueless_by_exception())
		return false;
	if (v.index() > w.index())
		return true;
	if (v.index() < w.index())
		return false;
	detail::rel_op_greater_equal_visitor vis;
	vis.lhs_storage = detail::get_storage_ptr(v);
	return visit(vis, w);
}


} //namespace mwstd


namespace std {

template<class... Ts>
struct hash< ::mwstd::variant<Ts...>>
{
	size_t operator()(const ::mwstd::variant<Ts...>& v) const
	{
		if (v.valueless_by_exception())
			return 0;

		auto const index_hash = hash<size_t>()(v.index());
		auto const alternative_hash = ::mwstd::visit(::mwstd::detail::get_hash_visitor(), v);
		return ::mwstd::detail::hash_combine(index_hash, alternative_hash);
	}
};

template<>
struct hash< ::mwstd::monostate>
{
	size_t operator()(const ::mwstd::monostate&) const
	{
		return 48; //All monostate objects are equal, so just return anything.
		//48 is the smallest number with 10 divisors.
	}
};

} //namespace std

#endif //MW_STD_DETAIL_HAS_STD_VARIANT
#endif	//	MW_VARIANT_HPP_
