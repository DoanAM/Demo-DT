// (C) 2019-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

// API - Note:
// Before VS2017 (C++17) all entities from namespace mwstd are custom developments from ModuleWorks.
// But from VS2017 (C++17) on, these are just using-declarations of the entities from the C++ Standard Library.
// This implies that users are not allowed to do any forward declarations of these entities as it will give a compiler error when switching to VS2017 (C++17).
// Also note that while an API compatibility is guaranteed, an ABI compatibility is not.
// Note that this header (span.hpp) is a backport for std::span, which is part of the C++ Standard Library since C++20.


#ifndef MW_SPAN_HPP_
#define MW_SPAN_HPP_
#include "mwstd/detail/CompilerConfig.hpp"

#ifdef MW_STD_DETAIL_HAS_STD_SPAN

#include <span>

namespace mwstd {
using std::dynamic_extent;
using std::span;
//using std::as_bytes; //We don't using-declare them because mwstd does not provide them either.
//using std::as_writable_bytes; //We don't using-declare them because mwstd does not provide them either.
}

#else //MW_STD_DETAIL_HAS_STD_SPAN

#include "mwstd/type_traits.hpp"

#include <array>
#include <cstddef>
#include <iterator>
#include <type_traits>

namespace mwstd
{

//https://en.cppreference.com/w/cpp/container/span/dynamic_extent
const std::size_t dynamic_extent = static_cast<std::size_t>(-1);

//https://en.cppreference.com/w/cpp/container/span
template<class T, std::size_t Extent = dynamic_extent>
class span; //[Missing]: span with static extent is not implemented yet


namespace detail
{

template <class T>
struct is_span : std::false_type
{};

template <class T, std::size_t Extent>
struct is_span<span<T, Extent>> : std::true_type
{};

template <class _Tp>
struct is_std_array : std::false_type
{};

template <class T, std::size_t Size>
struct is_std_array<std::array<T, Size>> : std::true_type
{};

template<class R, class ElementType>
using is_span_compatible_container = std::integral_constant<bool,
	!is_span<R>::value &&
	!is_std_array<R>::value &&
	!std::is_array<R>::value &&
	std::is_convertible<
		remove_cvref_t<decltype(*(std::declval<R&>().data()))>(*)[], ElementType(*)[] //Is R::value_type at most a qualification conversion to ElementType
	>::value
>;

} //namespace detail


template<class T>
class span<T>
{
	//https://eel.is/c++draft/span.cons#3.2
	template<class U>
	using enable_if_at_most_qualification_conversion = std::enable_if_t<std::is_convertible<U(*)[], T(*)[]>::value>;

	template<class R>
	using enable_if_span_compatible_container = std::enable_if_t<detail::is_span_compatible_container<R, T>::value>;

public:
	using element_type = T;
	using value_type = std::remove_cv_t<T>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = element_type*;
	using reverse_iterator = std::reverse_iterator<iterator>;

	static const std::size_t extent = dynamic_extent;

	//Constructor: https://en.cppreference.com/w/cpp/container/span/span

	span() : data_(nullptr), size_(0U) {}

	//[Different]: Constructor (2) takes any contiguous_iterator, but we don't have support for that yet so we just take a pointer.
	template<class U,
		class = enable_if_at_most_qualification_conversion<U>
	>
	span(U* ptr, size_type count) : data_(ptr), size_(count) {}

	//[Different]: Constructor (3) takes any contiguous_iterator and any sized_senital_for for the iterator but we don't have support for those yet so we just take two pointers.
	template<class U,
		class = enable_if_at_most_qualification_conversion<U>
	>
	span(U* first, U* last) : data_(first), size_(static_cast<std::size_t>(last - first)) {}

	//[Missing]
	/*template<std::size_t N>
	span(element_type(&arr)[N]) : data_(arr), size_(N) {}*/

	template<class U, std::size_t N,
		class = enable_if_at_most_qualification_conversion<U>
	>
	span(std::array<U, N>& arr) : data_(arr.data()), size_(N) {}

	template<class U, std::size_t N,
		class = enable_if_at_most_qualification_conversion<const U>
	>
	span(const std::array<U, N>& arr) : data_(arr.data()), size_(N) {}

	//[Different]: Constructor (7) takes a certain range. As C++17 does not have ranges yet, this constructor is a simplified version.
	//It only allows a sub-set of what std::span would accept.
	template<class R,
		class = enable_if_span_compatible_container<remove_cvref_t<R>>
	>
	span(R&& r) : data_(r.data()), size_(r.size()) {}

	//[Missing]: Constructor (8) is missing.
	//template<class U, std::size_t N>
	//span(const std::span<U, N>& s);

	span(const span& other) = default;

	//https://en.cppreference.com/w/cpp/container/span/operator%3D
	span& operator=(const span& other) = default;

	//Iterator support
	iterator begin() const
	{
		return data();
	}

	iterator end() const
	{
		return data() + size();
	}

	reverse_iterator rbegin() const
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(begin());
	}

	//Element access
	reference front() const
	{
		return data()[0];
	}

	reference back() const
	{
		return data()[size() - 1];
	}

	reference operator[](size_type idx) const
	{
		return data()[idx];
	}

	pointer data() const
	{
		return data_;
	}

	//Observers
	std::size_t size() const
	{
		return size_;
	}

	std::size_t size_bytes() const
	{
		return size() * sizeof(element_type);
	}

	bool empty() const
	{
		return size() == 0U;
	}

	//Subviews

	//[Missing]: first<Count> is missing as static span is missing
	/*template< std::size_t Count >
	constexpr std::span<element_type, Count> first() const;*/

	span<element_type> first(size_type count) const
	{
		return { data(), count };
	}

	//[Missing]: last<Count> is missing as static span is missing
	/*template< std::size_t Count >
	constexpr std::span<element_type, Count> last() const;*/

	span<element_type> last(size_type count) const
	{
		return { data() + (size() - count), count };
	}

	//[Missing]: subspan<Offset, Count> is missing as static span is missing
	/*template< std::size_t Offset, std::size_t Count = std::dynamic_extent >
		constexpr std::span<element_type, E> subspan() const;*/

	span<element_type> subspan(size_type offset, size_type count = dynamic_extent) const
	{
		size_type newCount = (count == dynamic_extent) ? (size() - offset) : count;
		return { data() + offset, newCount };
	}

private:
	element_type* data_;
	std::size_t size_;
};


//https://en.cppreference.com/w/cpp/container/span/as_bytes
//[Missing]: as_bytes and as_writable_bytes is missing as std::byte is missing.

//https://en.cppreference.com/w/cpp/ranges/borrowed_range
//[Missing]: enable_borrowed_range is not enabled as ranges are missing.

} //namespace mwstd

#endif //MW_STD_DETAIL_HAS_STD_SPAN
#endif	//	MW_SPAN_HPP_
