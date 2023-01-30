// (C) 2019-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

// API - Note:
// Before VS2017 (C++17) all entities from namespace mwstd are custom developments from ModuleWorks.
// But from VS2017 (C++17) on, these are just using-declarations of the entities from the C++ Standard Library.
// This implies that users are not allowed to do any forward declarations of these entities as it will give a compiler error when switching to VS2017 (C++17).
// Also note that while an API compatibility is guaranteed, an ABI compatibility is not.


#ifndef MW_OPTIONAL_HPP_
#define MW_OPTIONAL_HPP_
#include "mwstd/detail/CompilerConfig.hpp"
#include "mwstd/utility.hpp"

#ifdef MW_STD_DETAIL_HAS_STD_OPTIONAL

#include <optional>

namespace mwstd
{
using std::bad_optional_access;
using std::optional;
using std::make_optional;
using std::nullopt_t;
using std::nullopt;
}

#else //MW_STD_DETAIL_HAS_STD_OPTIONAL

#include "mwstd/type_traits.hpp"


#include <exception>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace mwstd
{

namespace detail
{

struct nullopt_init
{
	explicit nullopt_init(int) {}
};

}


//https://en.cppreference.com/w/cpp/utility/optional/bad_optional_access

class MWSTD_EXCEPTION_API bad_optional_access : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Bad optional access";
	}
};


//https://en.cppreference.com/w/cpp/utility/optional/nullopt_t

struct nullopt_t
{
	//nullopt_t must not be default-constructible to avoid ambiguity for opt = {}.
	//This constructor is not part of the API and must not be used outside this file.
	explicit nullopt_t(detail::nullopt_init, detail::nullopt_init) {}
};

const nullopt_t nullopt = nullopt_t(detail::nullopt_init(0), detail::nullopt_init(0));


//https://en.cppreference.com/w/cpp/utility/optional

template<class T>
class optional
{
	static_assert(!std::is_same<nullopt_t, std::remove_cv_t<T>>::value, "T shall not be a nullopt_t");
	static_assert(!std::is_same<in_place_t, std::remove_cv_t<T>>::value, "T shall not be an in_place_t");
	static_assert(std::is_object<T>::value, "T must be an object");
	static_assert(!std::is_array<T>::value, "T shall not be an array");

	template<class QualU, class U = remove_cvref_t<QualU>>
	using allow_direct_conversion = std::integral_constant<bool,
		!std::is_same<U, optional>::value && !std::is_same<U, in_place_t>::value
		&& std::is_constructible<T, U>::value>;

public:
	using value_type = T;

	optional() : has_value_(false) {}

	optional(nullopt_t) : has_value_(false) {}

	optional(const optional& other) : has_value_(other.has_value_)
	{
		if (has_value_)
		{
			new(storage_ptr()) T(other.get());
		}
	}

	optional(optional&& other) : has_value_(other.has_value_)
	{
		if (has_value_)
		{
			new(storage_ptr()) T(std::move(other.get()));
		}
	}

	template<class... Args,
		class = std::enable_if_t<std::is_constructible<T, Args...>::value>
	>
	explicit optional(in_place_t, Args&&... args) : has_value_(true)
	{
		new(storage_ptr()) T(std::forward<Args>(args)...);
	}

	template<class U, class... Args,
		class = std::enable_if_t<std::is_constructible<T, std::initializer_list<U>&, Args...>::value>
	>
	explicit optional(in_place_t, std::initializer_list<U> il, Args&&... args) : has_value_(true)
	{
		new(storage_ptr()) T(il, std::forward<Args>(args)...);
	}

	template<class U = T,
		std::enable_if_t<allow_direct_conversion<U>::value && std::is_convertible<U, T>::value, short> = 0
	>
	/*implicit*/ optional(U&& val) : has_value_(true)
	{
		new(storage_ptr()) T(std::forward<U>(val));
	}

	template<class U = T,
		std::enable_if_t<allow_direct_conversion<U>::value && !std::is_convertible<U, T>::value, int> = 0
	>
	explicit optional(U&& val) : has_value_(true)
	{
		new(storage_ptr()) T(std::forward<U>(val));
	}


	//[Missing]:
	//template<class U>
	//explicit(see below) optional(const optional<U>& other);

	//[Missing]:
	//template<class U>
	//explicit optional(optional<U>&& other);

	~optional()
	{
		try_destruct();
	}

	optional& operator=(nullopt_t)
	{
		try_destruct();
		return *this;
	}

	optional& operator=(const optional& other)
	{
		if (!has_value_ && !other.has_value_)
			; //Nothing to do
		else if (has_value_ && !other.has_value_)
			destruct();
		else if (has_value_ && other.has_value_)
			get() = other.get();
		else
			construct(other.get());
		return *this;
	}

	optional& operator=(optional&& other)
	{
		if (!has_value_ && !other.has_value_)
			; //Nothing to do
		else if (has_value_ && !other.has_value_)
			destruct();
		else if (has_value_ && other.has_value_)
			get() = std::move(other.get());
		else
			construct(std::move(other.get()));
		return *this;
	}

	template<class U = T>
	std::enable_if_t<
		!std::is_same<optional, remove_cvref_t<U>>::value &&
		!(std::is_scalar<T>::value && std::is_same<T, std::decay_t<U>>::value) &&
		std::is_constructible<T, U>::value && std::is_assignable<T&, U>::value
		, optional&
	> operator=(U&& val)
	{
		if (has_value_)
			get() = std::forward<U>(val);
		else
			construct(std::forward<U>(val));
		return *this;
	}

	//[Missing]:
	//template<class U>
	//optional& operator=(const optional<U>& other);

	//[Missing]:
	//template<class U>
	//optional& operator=(optional<U>&& other);

	T* operator->()
	{
		return get_ptr();
	}

	const T* operator->() const
	{
		return get_ptr();
	}

	T& operator*()
	{
		return get();
	}

	const T& operator*() const
	{
		return get();
	}

	explicit operator bool() const
	{
		return has_value_;
	}

	bool has_value() const
	{
		return has_value_;
	}

	T& value()
	{
		if (has_value_)
		{
			return get();
		}
		throw bad_optional_access();
	}

	const T& value() const
	{
		if (has_value_)
		{
			return get();
		}
		throw bad_optional_access();
	}

	template<class U>
	T value_or(U&& default_value) const
	{
		return has_value_ ? get() : static_cast<T>(std::forward<U>(default_value));
	}

	void reset()
	{
		try_destruct();
	}

	void swap(optional& other)
	{
		if (!has_value_ && !other.has_value_)
			; //Both are empty, no effect.
		else if (has_value_ && !other.has_value_) //Only this has value
		{
			other.construct(std::move(**this));
			destruct();
		}
		else if (!has_value_ && other.has_value_) //Only other has value
		{
			construct(std::move(*other));
			other.destruct();
		}
		else //Both have a value
		{
			using std::swap;
			swap(**this, *other);
		}
	}

	template<class... Args, class = std::enable_if_t<std::is_constructible<value_type, Args...>::value>>
	T& emplace(Args&&... args)
	{
		try_destruct();
		return construct(std::forward<Args>(args)...);
	}

	template<class U, class... Args, class = std::enable_if_t<std::is_constructible<value_type, std::initializer_list<U>&, Args...>::value>>
	T& emplace(std::initializer_list<U> ilist, Args&&... args)
	{
		try_destruct();
		return construct(ilist, std::forward<Args>(args)...);
	}

private:
	using storage_type = std::aligned_storage_t<sizeof(T), std::alignment_of<T>::value>;
	storage_type storage_;
	bool has_value_;

	void* storage_ptr()
	{
		return &storage_;
	}

	void const* storage_ptr() const
	{
		return &storage_;
	}

	T* get_ptr()
	{
		return static_cast<T*>(storage_ptr());
	}

	T const* get_ptr() const
	{
		return static_cast<T const*>(storage_ptr());
	}

	T& get()
	{
		return *get_ptr();
	}

	T const& get() const
	{
		return *get_ptr();
	}

	template<class... Args>
	T& construct(Args&&... args)
	{
		T& result = *new(storage_ptr()) T(std::forward<Args>(args)...);
		has_value_ = true;
		return result;
	}

	void try_destruct()
	{
		if (has_value_)
		{
			destruct();
		}
	}

	void destruct()
	{
		get().~T();
		has_value_ = false;
	}
};


//https://en.cppreference.com/w/cpp/utility/optional/operator_cmp

// relational operators
template<class T, class U>
inline bool operator==(const optional<T>& lhs, const optional<U>& rhs)
{
	if (lhs.has_value() != rhs.has_value())
		return false;
	else if (!lhs.has_value())
		return true;
	else
		return *lhs == *rhs;
}

template<class T, class U>
inline bool operator!=(const optional<T>& lhs, const optional<U>& rhs)
{
	if (lhs.has_value() != rhs.has_value())
		return true;
	else if (!lhs.has_value())
		return false;
	else
		return *lhs != *rhs;
}

template<class T, class U>
inline bool operator<(const optional<T>& lhs, const optional<U>& rhs)
{
	if (!rhs.has_value())
		return false;
	else if (!lhs.has_value())
		return true;
	else
		return *lhs < *rhs;
}

template<class T, class U>
inline bool operator>(const optional<T>& lhs, const optional<U>& rhs)
{
	if (!lhs.has_value())
		return false;
	else if (!rhs.has_value())
		return true;
	else
		return *lhs > * rhs;
}

template<class T, class U>
inline bool operator<=(const optional<T>& lhs, const optional<U>& rhs)
{
	if (!lhs.has_value())
		return true;
	else if (!rhs.has_value())
		return false;
	else
		return *lhs <= *rhs;
}

template<class T, class U>
inline bool operator>=(const optional<T>& lhs, const optional<U>& rhs)
{
	if (!rhs.has_value())
		return true;
	else if (!lhs.has_value())
		return false;
	else
		return *lhs >= *rhs;
}


// comparison with nullopt
template <class T> inline bool operator==(const optional<T>& opt, nullopt_t)
{
	return !opt.has_value();
}

template <class T> inline bool operator==(nullopt_t, const optional<T>& opt)
{
	return !opt.has_value();
}

template <class T> inline bool operator!=(const optional<T>& opt, nullopt_t)
{
	return opt.has_value();
}

template <class T> inline bool operator!=(nullopt_t, const optional<T>& opt)
{
	return opt.has_value();
}

template <class T> inline bool operator<(const optional<T>&, nullopt_t)
{
	return false;
}

template <class T> inline bool operator<(nullopt_t, const optional<T>& opt)
{
	return opt.has_value();
}

template <class T> inline bool operator<=(const optional<T>& opt, nullopt_t)
{
	return !opt.has_value();
}

template <class T> inline bool operator<=(nullopt_t, const optional<T>&)
{
	return true;
}

template <class T> inline bool operator>(const optional<T>& opt, nullopt_t)
{
	return opt.has_value();
}

template <class T> inline bool operator>(nullopt_t, const optional<T>&)
{
	return false;
}

template <class T> inline bool operator>=(const optional<T>&, nullopt_t)
{
	return true;
}

template <class T> inline bool operator>=(nullopt_t, const optional<T>& opt)
{
	return !opt.has_value();
}

// comparison with T
template <class T, class U> inline bool operator==(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt == val : false;
}

template <class T, class U> inline bool operator==(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val == *opt : false;
}

template <class T, class U> inline bool operator!=(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt != val : true;
}

template <class T, class U> inline bool operator!=(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val != *opt : true;
}

template <class T, class U> inline bool operator<(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt < val : true;
}

template <class T, class U> inline bool operator<(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val < *opt : false;
}

template <class T, class U> inline bool operator<=(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt <= val : true;
}

template <class T, class U> inline bool operator<=(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val <= *opt : false;
}

template <class T, class U> inline bool operator>(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt > val : false;
}

template <class T, class U> inline bool operator>(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val > * opt : true;
}

template <class T, class U> inline bool operator>=(const optional<T>& opt, const U& val)
{
	return opt.has_value() ? *opt >= val : false;
}

template <class T, class U> inline bool operator>=(const T& val, const optional<U>& opt)
{
	return opt.has_value() ? val >= *opt : true;
}


//https://en.cppreference.com/w/cpp/utility/optional/swap2

template<class T>
inline void swap(optional<T>& lhs, optional<T>& rhs)
{
	lhs.swap(rhs);
}


//https://en.cppreference.com/w/cpp/utility/optional/make_optional

template<class T>
inline optional<std::decay_t<T>> make_optional(T&& value)
{
	return optional<std::decay_t<T>>(std::forward<T>(value));
}

template<class T, class... Args>
inline optional<T> make_optional(Args&&... args)
{
	return optional<T>(in_place, std::forward<Args>(args)...);
}

template<class T, class U, class... Args>
inline optional<T> make_optional(std::initializer_list<U> il, Args&&... args)
{
	return optional<T>(in_place, il, std::forward<Args>(args)...);
}


} //namespace mwstd

namespace std {

template<class T>
struct hash< ::mwstd::optional<T>>
{
	size_t operator()(const ::mwstd::optional<T>& opt) const
	{
		return opt.has_value() ? hash<remove_const_t<T>>()(*opt) : 0;
	}
};

} //namespace std

#endif //MW_STD_DETAIL_HAS_STD_OPTIONAL
#endif	//	MW_OPTIONAL_HPP_
