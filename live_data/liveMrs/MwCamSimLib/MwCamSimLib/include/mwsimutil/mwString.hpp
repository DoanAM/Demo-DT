// (C) 2005-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTRING_HPP_
#define MW_MWSTRING_HPP_
#include "mwDllImpExpDef.hpp"
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>
#include "mwDefines.hpp"
#include "mwLanguageFeatures.hpp"

#if defined(_WIN32)
#else // linux or macos as it is not windows
#include <unistd.h>
#endif
#include "mwTChar.hpp"

//With gcc, we need at least gcc 9.x to support both 'operator wstring() const' and 'operator wstring&&()&&'.
#ifdef __GNUC__
	#if (__GNUC__ >= 9)
		#define MW_MISC_DETAIL_GCC_SUPPORTS_STRING_REF_QUAL_CONVERSION
	#endif
#else //else: with clang and msvc everything works fine
	#define MW_MISC_DETAIL_GCC_SUPPORTS_STRING_REF_QUAL_CONVERSION
#endif

namespace misc
{
	class MW_5AXUTIL_API mwstring
	{
	public:
		typedef std::wstring::iterator iterator;
		typedef std::wstring::const_iterator const_iterator;
		typedef std::wstring::reverse_iterator reverse_iterator;
		typedef std::wstring::const_reverse_iterator const_reverse_iterator;
		typedef std::wstring::reference reference;
		typedef std::wstring::const_reference const_reference;
		typedef std::wstring::size_type size_type;
		typedef std::wstring::value_type value_type;

		

		inline mwstring(const wchar_t* source);
		inline mwstring(const std::wstring& source);
		inline mwstring(const std::wstring& source, size_t pos, size_t n = npos);
		inline mwstring(const char* source);
		inline mwstring(const std::string& source);
		inline mwstring();
		inline mwstring(size_t n, char c);
		inline mwstring(size_t n, wchar_t c);
		inline mwstring(const wchar_t* s, size_t n);
		inline mwstring(const char* source, size_t n);
		inline mwstring(const mwstring& toCopy);
#ifndef MW_USE_VS2008_COMPATIBILITY
		inline mwstring(mwstring&& src) noexcept;
		inline mwstring(std::wstring&& src) noexcept;
#endif

		template <class InputIterator>
		inline mwstring(InputIterator first, InputIterator last);

		

		// Note: This method tries to decode an std::string as UTF8. In case of a
		// decode error, a misc::mwException is thrown.
		static mwstring FromUTF8(const std::string& utf8encoded);

		

		std::string ToAscii() const;
		std::string ToUTF8() const;
		operator std::string() const;

		//Note: It would be most efficient if we would have both an 'operator const wstring&() const&'
		//and an 'operator wstring&&() &&'. But due to the language rules this would lead to an ambiguity
		//when calling e.g. std::wstring wstr(GetMWString());
		//So we will keep the 'operator std::wstring() const' as it is and just add the rvalue-ref-overload.
		operator std::wstring() const;
#if defined(MW_HAS_CXX11_REF_QUALIFIERS) && defined(MW_MISC_DETAIL_GCC_SUPPORTS_STRING_REF_QUAL_CONVERSION)
		operator std::wstring&&() &&;
#endif

		

		inline iterator begin();
		inline const_iterator begin() const;
		inline iterator end();
		inline const_iterator end() const;
		inline reverse_iterator rbegin();
		inline const_reverse_iterator rbegin() const;
		inline reverse_iterator rend();
		inline const_reverse_iterator rend() const;

		

		inline size_t size() const;
		inline size_t length() const;
		inline size_t max_size() const;
		inline void resize(size_t n);
		inline void resize(size_t n, char c);
		inline void resize(size_t n, wchar_t c);
		inline size_t capacity() const;
		inline void reserve(size_t res = 0);
		inline void clear();
		inline bool empty() const;

		

		inline const_reference operator[](size_t pos) const;

		inline reference operator[](size_t pos);

		inline const_reference at(size_t pos) const;

		inline reference at(size_t pos);

		

		inline mwstring& append(const std::wstring& str);
		inline mwstring& append(const mwstring& str);
		inline mwstring& append(const std::string& str, size_t pos, size_t n);
		inline mwstring& append(const std::wstring& str, size_t pos, size_t n);
		inline mwstring& append(const wchar_t* str, size_t n);
		inline mwstring& append(const wchar_t* str);
		inline mwstring& append(size_t n, wchar_t c);
		template<class InputIterator>
		inline mwstring& append(InputIterator begin, InputIterator end);

		

		inline void push_back(wchar_t c);

		

		inline mwstring& assign(const std::wstring& str);
		inline mwstring& assign(const mwstring& str);
		inline mwstring& assign(const std::wstring& str, size_t pos, size_t n);
		inline mwstring& assign(const mwstring& str, size_t pos, size_t n);
		inline mwstring& assign(const wchar_t* s, size_t n);
		inline mwstring& assign(const wchar_t* s);
		inline mwstring& assign(size_t n, wchar_t c);
		template <class InputIterator>
		inline mwstring& assign(InputIterator first, InputIterator last);

		

		inline mwstring& insert(size_t pos1, const std::wstring& str);
		inline mwstring& insert(size_t pos1, const mwstring& str);
		inline mwstring& insert(size_t pos1, const std::wstring& str, size_t pos2, size_t n);
		inline mwstring& insert(size_t pos1, const mwstring& str, size_t pos2, size_t n);
		inline mwstring& insert(size_t pos1, const wchar_t* str, size_t n);
		inline mwstring& insert(size_t pos1, const wchar_t* str);

		mwstring& insert(size_t pos1, size_t n, wchar_t c);

		iterator insert(iterator p, wchar_t c);

		void insert(iterator p, size_t n, wchar_t c);

		template<class InputIterator>
		void insert(iterator p, InputIterator first, InputIterator last);

		

		mwstring& erase(size_t pos = 0, size_t n = npos);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last);

		

		mwstring& replace(size_t pos, size_t n, const std::wstring& str);

		mwstring& replace(size_t pos, size_t n, const mwstring& str);

		mwstring& replace(iterator i1, iterator i2, const std::wstring& str);

		mwstring& replace(iterator i1, iterator i2, const mwstring& str);

		mwstring& replace(size_t pos1, size_t n1, const std::wstring& str, size_t pos2, size_t n2);

		mwstring& replace(size_t pos1, size_t n1, const mwstring& str, size_t pos2, size_t n2);

		mwstring& replace(size_t pos1, size_t n1, const wchar_t* str, size_t n2);

		mwstring& replace(iterator i1, iterator i2, const wchar_t* str, size_t n2);

		mwstring& replace(size_t pos, size_t n, const wchar_t* str);

		mwstring& replace(iterator i1, iterator i2, const wchar_t* str);

		mwstring& replace(size_t pos1, size_t n1, size_t n2, wchar_t c);

		mwstring& replace(iterator i1, iterator i2, size_t n2, wchar_t c);

		template<class InputIterator>
		mwstring& replace(iterator i1, iterator i2, InputIterator j1, InputIterator j2);

		

		void swap(std::wstring& str);

		void swap(mwstring& str);

		

		const _TCHAR* c_str() const;

		

		const wchar_t* data() const;

		// _MSVC_LANG is defined as 201403L using VS2015 with /std:c++latest flag (otherwise 201402L, notice 03 vs. 02)
		// MSVC has no full c++17 conformance , but provides some functionalty already. 
		// in this case, the non-const data() function of std::wstring is only availabe starting with _MSVC_LANG >= 201403L
#if (__cplusplus >= 201411L && (!defined(__GNUC__) ||  __GNUC__ >= 7 || defined(__clang__))) || ( defined(_MSC_VER) && _MSVC_LANG >= 201403L )
		wchar_t* data()
		{
			// C++17 provides write access to data()
			return m_value.data();
		}
#endif

		

		std::allocator<wchar_t> get_allocator() const;

		

		size_t find(const std::wstring& str, size_t pos = 0) const;

		size_t find(const mwstring& str, size_t pos = 0) const;

		size_t find(const wchar_t* str, size_t pos, size_t n) const;

		size_t find(const wchar_t* str, size_t pos = 0) const;

		size_t find(wchar_t c, size_t pos = 0) const;

		

		size_t rfind(const std::wstring& str, size_t pos = npos) const;

		size_t rfind(const mwstring& str, size_t pos = npos) const;

		size_t rfind(const wchar_t* str, size_t pos, size_t n) const;

		size_t rfind(const wchar_t* str, size_t pos = npos) const;

		size_t rfind(wchar_t c, size_t pos = npos) const;

		

		size_t find_first_of(const std::wstring& str, size_t pos = 0) const;

		size_t find_first_of(const mwstring& str, size_t pos = 0) const;

		size_t find_first_of(const wchar_t* str, size_t pos, size_t n) const;

		size_t find_first_of(const wchar_t* str, size_t pos = 0) const;

		size_t find_first_of(wchar_t c, size_t pos = 0) const;

		

		size_t find_last_of(const std::wstring& str, size_t pos = npos) const;

		size_t find_last_of(const mwstring& str, size_t pos = npos) const;

		size_t find_last_of(const wchar_t* str, size_t pos, size_t n) const;

		size_t find_last_of(const wchar_t* str, size_t pos = npos) const;

		size_t find_last_of(wchar_t c, size_t pos = npos) const;

		

		size_t find_first_not_of(const std::wstring& str, size_t pos = 0) const;

		size_t find_first_not_of(const mwstring& str, size_t pos = 0) const;

		size_t find_first_not_of(const wchar_t* str, size_t pos, size_t n) const;

		size_t find_first_not_of(const wchar_t* str, size_t pos = 0) const;

		size_t find_first_not_of(wchar_t c, size_t pos = 0) const;

		

		inline size_t find_last_not_of(const std::wstring& str, size_t pos = npos) const;

		inline size_t find_last_not_of(const mwstring& str, size_t pos = npos) const;

		inline size_t find_last_not_of(const wchar_t* str, size_t pos, size_t n) const;

		inline size_t find_last_not_of(const wchar_t* str, size_t pos = npos) const;

		inline size_t find_last_not_of(wchar_t c, size_t pos = npos) const;

		

		inline mwstring substr(size_t pos = 0, size_t n = npos) const;

		

		inline int compare(const std::wstring& str) const;
		inline int compare(const mwstring& str) const;
		inline int compare(const wchar_t* str) const;
		inline int compare(size_t pos, size_t n, const std::wstring& str) const;

		inline int compare(size_t pos, size_t n, const mwstring& str) const;
		inline int compare(size_t pos, size_t n, const wchar_t* str) const;
		inline int compare(size_t pos1, size_t n1, const std::wstring& str, size_t pos2, size_t n2) const;
		inline int compare(size_t pos1, size_t n1, const mwstring& str, size_t pos2, size_t n2) const;
		inline int compare(size_t pos, size_t n1, const wchar_t* str, size_t n2) const;
		

		inline bool StartsWith(const wchar_t*) const;
		inline bool StartsWith(const misc::mwstring&) const;
		inline bool EndsWith(const wchar_t*) const;
		inline bool EndsWith(const misc::mwstring&) const;

		

		inline mwstring& operator=(const wchar_t* str);
		inline mwstring& operator=(const char* str);
		inline mwstring& operator=(const std::wstring& str);
		inline mwstring& operator=(const mwstring& str);
		inline mwstring& operator=(wchar_t c);
		inline mwstring& operator=(char c);
#ifndef MW_USE_VS2008_COMPATIBILITY
		inline mwstring& operator=(std::wstring&& str) noexcept;
		inline mwstring& operator=(mwstring&& str) noexcept;
#endif

		

		inline mwstring& operator+=(const wchar_t* str);
		inline mwstring& operator+=(wchar_t c);
		inline mwstring& operator+=(const mwstring& str);
		inline mwstring& operator+=(const std::wstring& str);

		
		static const size_t npos = (size_t)-1;
		

		size_t hash_value() const;

	private:
		friend std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& out, const misc::mwstring& str);

	private:
	#pragma warning(push)
	#pragma warning(disable : 4251) // needs to have dll-interface to be used by clients of class
	
	std::wstring ToWide(const char* source, const size_t n = static_cast<size_t>(-1)) const;
		

		std::wstring m_value;
		mutable std::string m_asciiValue;
	
	#pragma warning(pop)
	};

	
	inline mwstring operator+(const mwstring& first, const mwstring& second);
	inline mwstring operator+(const std::wstring& first, const mwstring& second);
	inline mwstring operator+(const mwstring& first, const std::wstring& second);
	inline mwstring operator+(const wchar_t* first, const mwstring& second);
	inline mwstring operator+(const mwstring& first, const wchar_t* second);
	inline mwstring operator+(wchar_t first, const mwstring& second);
	inline mwstring operator+(const mwstring& first, wchar_t second);

	

	inline bool operator==(const mwstring& first, const mwstring& second);
	inline bool operator==(const std::wstring& first, const mwstring& second);
	inline bool operator==(const mwstring& first, const std::wstring& second);
	inline bool operator==(const wchar_t* first, const mwstring& second);
	inline bool operator==(const mwstring& first, const wchar_t* second);

	

	inline bool operator!=(const mwstring& first, const mwstring& second);
	inline bool operator!=(const std::wstring& first, const mwstring& second);
	inline bool operator!=(const mwstring& first, const std::wstring& second);
	inline bool operator!=(const wchar_t* first, const mwstring& second);
	inline bool operator!=(const mwstring& first, const wchar_t* second);

	

	inline bool operator<(const mwstring& first, const mwstring& second);
	inline bool operator<(const std::wstring& first, const mwstring& second);
	inline bool operator<(const mwstring& first, const std::wstring& second);
	inline bool operator<(const wchar_t* first, const mwstring& second);
	inline bool operator<(const mwstring& first, const wchar_t* second);

	

	inline bool operator>(const mwstring& first, const mwstring& second);
	inline bool operator>(const std::wstring& first, const mwstring& second);
	inline bool operator>(const mwstring& first, const std::wstring& second);
	inline bool operator>(const wchar_t* first, const mwstring& second);
	inline bool operator>(const mwstring& first, const wchar_t* second);

	

	inline bool operator<=(const mwstring& first, const mwstring& second);
	inline bool operator<=(const std::wstring& first, const mwstring& second);
	inline bool operator<=(const mwstring& first, const std::wstring& second);
	inline bool operator<=(const wchar_t* first, const mwstring& second);
	inline bool operator<=(const mwstring& first, const wchar_t* second);

	

	inline bool operator>=(const mwstring& first, const mwstring& second);
	inline bool operator>=(const std::wstring& first, const mwstring& second);
	inline bool operator>=(const mwstring& first, const std::wstring& second);
	inline bool operator>=(const wchar_t* first, const mwstring& second);
	inline bool operator>=(const mwstring& first, const wchar_t* second);

inline mwstring& mwstring::operator+=(const mwstring& str)
{
	m_value += str.m_value;
	return *this;
}

inline mwstring& mwstring::operator+=(const std::wstring& str)
{
	m_value += str;
	return *this;
}

inline mwstring& mwstring::operator+=(wchar_t c)
{
	m_value += c;
	return *this;
}

inline mwstring& mwstring::operator+=(const wchar_t* str)
{
	m_value += str;
	return *this;
}

inline mwstring& mwstring::operator=(char c)
{
	assign(1, c);
	return *this;
}

inline mwstring& mwstring::operator=(wchar_t c)
{
	m_value.assign(1, c);
	return *this;
}

inline mwstring& mwstring::operator=(const mwstring& str)
{
	if (this != &str) 
	{
		m_value = str.m_value;
	}
	return *this;
}

inline mwstring& mwstring::operator=(const std::wstring& str)
{
	m_value = str;
	return *this;
}

#ifndef MW_USE_VS2008_COMPATIBILITY
inline mwstring& mwstring::operator=(mwstring&& str) noexcept
{
	if (this != &str) 
	{
		m_value = std::move(str.m_value);
	}
	return *this;
}

inline mwstring& mwstring::operator=(std::wstring&& str) noexcept
{
	m_value = std::move(str);
	return *this;
}
#endif

inline mwstring& mwstring::operator=(const char* str)
{
	assign(str);
	return *this;
}

inline mwstring& mwstring::operator=(const wchar_t* str)
{
	m_value.assign(str);
	return *this;
}

inline int mwstring::compare(size_t pos, size_t n1, const wchar_t* str, size_t n2) const
{
	return m_value.compare(pos, n1, str, n2);
}

inline int mwstring::compare(size_t pos1, size_t n1, const mwstring& str, size_t pos2, size_t n2) const
{
	return m_value.compare(pos1, n1, str.m_value, pos2, n2);
}

inline int mwstring::compare(size_t pos1, size_t n1, const std::wstring& str, size_t pos2, size_t n2) const
{
	return m_value.compare(pos1, n1, str, pos2, n2);
}

inline int mwstring::compare(size_t pos, size_t n, const wchar_t* str) const
{
	return m_value.compare(pos, n, str);
}

inline int mwstring::compare(size_t pos, size_t n, const mwstring& str) const
{
	return m_value.compare(pos, n, str.m_value);
}

inline int mwstring::compare(size_t pos, size_t n, const std::wstring& str) const
{
	return m_value.compare(pos, n, str);
}

inline int mwstring::compare(const wchar_t* str) const
{
	return m_value.compare(str);
}

inline int mwstring::compare(const mwstring& str) const
{
	return m_value.compare(str.m_value);
}

inline int mwstring::compare(const std::wstring& str) const
{
	return m_value.compare(str);
}

inline mwstring mwstring::substr(size_t pos /*= 0*/, size_t n /*= npos*/) const
{
	return m_value.substr(pos, n);
}

inline size_t mwstring::find_last_not_of(wchar_t c, size_t pos /*= npos*/) const
{
	return m_value.find_last_not_of(c, pos);
}

inline size_t mwstring::find_last_not_of(const wchar_t* str, size_t pos /*= npos*/) const
{
	return m_value.find_last_not_of(str, pos);
}

inline size_t mwstring::find_last_not_of(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.find_last_not_of(str, pos, n);
}

inline size_t mwstring::find_last_not_of(const mwstring& str, size_t pos /*= npos*/) const
{
	return m_value.find_last_not_of(str.m_value, pos);
}

inline size_t mwstring::find_last_not_of(const std::wstring& str, size_t pos /*= npos*/) const
{
	return m_value.find_last_not_of(str, pos);
}

inline size_t mwstring::find_first_not_of(wchar_t c, size_t pos /*= 0*/) const
{
	return m_value.find_first_not_of(c, pos);
}

inline size_t mwstring::find_first_not_of(const wchar_t* str, size_t pos /*= 0*/) const
{
	return m_value.find_first_not_of(str, pos);
}

inline size_t mwstring::find_first_not_of(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.find_first_not_of( str, pos, n);
}

inline size_t mwstring::find_first_not_of(const mwstring& str, size_t pos /*= 0*/) const
{
	return m_value.find_first_not_of(str.m_value, pos);
}

inline size_t mwstring::find_first_not_of(const std::wstring& str, size_t pos /*= 0*/) const
{
	return m_value.find_first_not_of(str, pos);
}

inline size_t mwstring::find_last_of(wchar_t c, size_t pos /*= npos*/) const
{
	return m_value.find_last_of(c, pos);
}

inline size_t mwstring::find_last_of(const wchar_t* str, size_t pos /*= npos*/) const
{
	return m_value.find_last_of(str, pos);
}

inline size_t mwstring::find_last_of(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.find_last_of(str, pos, n);
}

inline size_t mwstring::find_last_of(const mwstring& str, size_t pos /*= npos*/) const
{
	return m_value.find_last_of(str.m_value, pos);
}

inline size_t mwstring::find_last_of(const std::wstring& str, size_t pos /*= npos*/) const
{
	return m_value.find_last_of(str, pos);
}

inline size_t mwstring::find_first_of(wchar_t c, size_t pos /*= 0*/) const
{
	return m_value.find_first_of(c, pos);
}

inline size_t mwstring::find_first_of(const wchar_t* str, size_t pos /*= 0*/) const
{
	return m_value.find_first_of(str, pos);
}

inline size_t mwstring::find_first_of(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.find_first_of(str, pos, n);
}

inline size_t mwstring::find_first_of(const mwstring& str, size_t pos /*= 0*/) const
{
	return m_value.find_first_of(str.m_value, pos);
}

inline size_t mwstring::find_first_of(const std::wstring& str, size_t pos /*= 0*/) const
{
	return m_value.find_first_of(str, pos);
}

inline size_t mwstring::rfind(wchar_t c, size_t pos /*= npos*/) const
{
	return m_value.rfind(c, pos);
}

inline size_t mwstring::rfind(const wchar_t* str, size_t pos /*= npos*/) const
{
	return m_value.rfind(str, pos);
}

inline size_t mwstring::rfind(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.rfind(str, pos, n);
}

inline size_t mwstring::rfind(const mwstring& str, size_t pos /*= npos*/) const
{
	return m_value.rfind(str.m_value, pos);
}

inline size_t mwstring::rfind(const std::wstring& str, size_t pos /*= npos*/) const
{
	return m_value.rfind(str, pos);
}

inline size_t mwstring::find(wchar_t c, size_t pos /*= 0*/) const
{
	return m_value.find(c, pos);
}

inline size_t mwstring::find(const wchar_t* str, size_t pos /*= 0*/) const
{
	return m_value.find(str, pos);
}

inline size_t mwstring::find(const wchar_t* str, size_t pos, size_t n) const
{
	return m_value.find(str, pos, n);
}

inline size_t mwstring::find(const mwstring& str, size_t pos /*= 0*/) const
{
	return m_value.find(str.m_value, pos);
}

inline size_t mwstring::find(const std::wstring& str, size_t pos /*= 0*/) const
{
	return m_value.find(str, pos);
}

inline std::allocator<wchar_t> mwstring::get_allocator() const
{
	return m_value.get_allocator();
}

inline const wchar_t* mwstring::data() const
{
	return m_value.data();
}

inline const _TCHAR* mwstring::c_str() const
{
#if defined UNICODE || defined _UNICODE
	return m_value.c_str();
#else
	m_asciiValue = ToAscii();
	return m_asciiValue.c_str();
#endif
}

inline void mwstring::swap(mwstring& str)
{
	m_value.swap(str.m_value);
}

inline void mwstring::swap(std::wstring& str)
{
	m_value.swap(str);
}

template<class InputIterator>
inline mwstring& mwstring::replace(iterator i1, iterator i2, InputIterator j1, InputIterator j2)
{
	m_value.replace(i1, i2, j1, j2);
	return *this;
}

inline mwstring& mwstring::replace(iterator i1, iterator i2, size_t n2, wchar_t c)
{
	m_value.replace(i1, i2, n2, c);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos1, size_t n1, size_t n2, wchar_t c)
{
	m_value.replace(pos1, n1, n2, c);
	return *this;
}

inline mwstring& mwstring::replace(iterator i1, iterator i2, const wchar_t* str)
{
	m_value.replace(i1, i2, str);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos, size_t n, const wchar_t* str)
{
	m_value.replace(pos, n, str);
	return *this;
}

inline mwstring& mwstring::replace(iterator i1, iterator i2, const wchar_t* str, size_t n2)
{
	m_value.replace(i1, i2, str, n2);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos1, size_t n1, const wchar_t* str, size_t n2)
{
	m_value.replace(pos1, n1, str, n2);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos1, size_t n1, const mwstring& str, size_t pos2, size_t n2)
{
	m_value.replace(pos1, n1, str.m_value, pos2, n2);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos1, size_t n1, const std::wstring& str, size_t pos2, size_t n2)
{
	m_value.replace(pos1, n1, str, pos2, n2);
	return *this;
}

inline mwstring& mwstring::replace(iterator i1, iterator i2, const mwstring& str)
{
	m_value.replace(i1, i2, str.m_value);
	return *this;
}

inline mwstring& mwstring::replace(iterator i1, iterator i2, const std::wstring& str)
{
	m_value.replace(i1, i2, str);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos, size_t n, const mwstring& str)
{
	m_value.replace(pos, n, str.m_value);
	return *this;
}

inline mwstring& mwstring::replace(size_t pos, size_t n, const std::wstring& str)
{
	m_value.replace(pos, n, str);
	return *this;
}

inline mwstring::iterator mwstring::erase(iterator first, iterator last)
{
	return m_value.erase(first, last);
}

inline mwstring::iterator mwstring::erase(iterator position)
{
	return m_value.erase(position);
}

inline mwstring& mwstring::erase(size_t pos /*= 0*/, size_t n /*= npos*/)
{
	m_value.erase(pos, n);
	return *this;
}

template<class InputIterator>
inline void mwstring::insert(iterator p, InputIterator first, InputIterator last)
{
	m_value.insert(p, first, last);
}

inline void mwstring::insert(iterator p, size_t n, wchar_t c)
{
	m_value.insert(p, n, c);
}

inline mwstring::iterator mwstring::insert(iterator p, wchar_t c)
{
	return m_value.insert(p, c);
}

inline mwstring& mwstring::insert(size_t pos1, size_t n, wchar_t c)
{
	m_value.insert(pos1, n, c);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const wchar_t* str)
{
	m_value.insert(pos1, str);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const wchar_t* str, size_t n)
{
	m_value.insert(pos1, str, n);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const mwstring& str, size_t pos2, size_t n)
{
	m_value.insert(pos1, str.m_value, pos2, n);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const std::wstring& str, size_t pos2, size_t n)
{
	m_value.insert(pos1, str, pos2, n);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const mwstring& str)
{
	m_value.insert(pos1, str.m_value);
	return *this;
}

inline mwstring& mwstring::insert(size_t pos1, const std::wstring& str)
{
	m_value.insert(pos1, str);
	return *this;
}

template <class InputIterator>
inline mwstring& mwstring::assign(InputIterator first, InputIterator last)
{
	m_value.assign(first, last);
	return *this;
}

inline mwstring& mwstring::assign(size_t n, wchar_t c)
{
	m_value.assign(n, c);
	return *this;
}

inline mwstring& mwstring::assign(const wchar_t* s)
{
	m_value.assign(s);
	return *this;
}

inline mwstring& mwstring::assign(const wchar_t* s, size_t n)
{
	m_value.assign(s, n);
	return *this;
}

inline mwstring& mwstring::assign(const mwstring& str, size_t pos, size_t n)
{
	m_value.assign(str.m_value, pos, n);
	return *this;
}

inline mwstring& mwstring::assign(const std::wstring& str, size_t pos, size_t n)
{
	m_value.assign(str, pos, n);
	return *this;
}

inline mwstring& mwstring::assign(const mwstring& str)
{
	m_value.assign(str.m_value);
	return *this;
}

inline mwstring& mwstring::assign(const std::wstring& str)
{
	m_value.assign(str);
	return *this;
}

inline void mwstring::push_back(wchar_t c)
{
	m_value.push_back(c);
}

template<class InputIterator>
inline mwstring& mwstring::append(InputIterator begin, InputIterator end)
{
	m_value.append(begin, end);
	return *this;
}

inline mwstring& mwstring::append(size_t n, wchar_t c)
{
	m_value.append(n, c);
	return *this;
}

inline mwstring& mwstring::append(const wchar_t* str)
{
	m_value.append(str);
	return *this;
}

inline mwstring& mwstring::append(const wchar_t* str, size_t n)
{
	m_value.append(str, n);
	return *this;
}

inline mwstring& mwstring::append(const std::wstring& str, size_t pos, size_t n)
{
	m_value.append(str, pos, n);
	return *this;
}

inline mwstring& mwstring::append(const std::string& str, size_t pos, size_t n)
{
	m_value.append(str.begin() + pos, str.begin() + pos + n);
	return *this;
}

inline mwstring& mwstring::append(const mwstring& str)
{
	m_value.append(str.m_value);
	return *this;
}

inline mwstring& mwstring::append(const std::wstring& str)
{
	m_value.append(str);
	return *this;
}

inline mwstring::reference mwstring::at(size_t pos)
{
	return m_value.at(pos);
}

inline mwstring::const_reference mwstring::at(size_t pos) const
{
	return m_value.at(pos);
}

inline mwstring::reference mwstring::operator[](size_t pos)
{
	return m_value[pos];
}

inline mwstring::const_reference mwstring::operator[](size_t pos) const
{
	return m_value[pos];
}

inline bool mwstring::empty() const
{
	return m_value.empty();
}

inline void mwstring::clear()
{
	m_value.clear();
}

inline void mwstring::reserve(size_t res /* = 0 */)
{
	m_value.reserve(res);
}

inline size_t mwstring::capacity() const
{
	return m_value.capacity();
}

inline void mwstring::resize(size_t n, wchar_t c)
{
	m_value.resize(n, c);
}

inline void mwstring::resize(size_t n, char c)
{
	m_value.resize(n, c);
}

inline void mwstring::resize(size_t n)
{
	m_value.resize(n);
}

inline size_t mwstring::max_size() const
{
	return m_value.max_size();
}

inline size_t mwstring::length() const
{
	return m_value.length();
}

inline size_t mwstring::size() const
{
	return m_value.size();
}

inline mwstring::const_reverse_iterator mwstring::rend() const
{
	return m_value.rend();
}

inline mwstring::reverse_iterator mwstring::rend()
{
	return m_value.rend();
}

inline mwstring::const_reverse_iterator mwstring::rbegin() const
{
	return m_value.rbegin();
}

inline mwstring::reverse_iterator mwstring::rbegin()
{
	return m_value.rbegin();
}

inline mwstring::const_iterator mwstring::end() const
{
	return m_value.end();
}

inline mwstring::iterator mwstring::end()
{
	return m_value.end();
}

inline mwstring::const_iterator mwstring::begin() const
{
	return m_value.begin();
}

inline mwstring::iterator mwstring::begin()
{
	return m_value.begin();
}

inline mwstring::operator std::wstring() const
{
	return m_value;
}

inline mwstring::operator std::string() const
{
	return ToAscii();
}

#if defined(MW_HAS_CXX11_REF_QUALIFIERS) && defined(MW_MISC_DETAIL_GCC_SUPPORTS_STRING_REF_QUAL_CONVERSION)
inline mwstring::operator std::wstring && ()&&
{
	return std::move(m_value);
}
#endif

#ifndef MW_USE_VS2008_COMPATIBILITY
inline mwstring::mwstring(mwstring&& src) noexcept
	: m_value(std::move(src.m_value))  // do not copy the ASCII version
{}

inline mwstring::mwstring(std::wstring&& src) noexcept
	: m_value(std::move(src))
{}
#endif

inline mwstring::mwstring(const mwstring& toCopy) 
	: m_value(toCopy.m_value)  // do not copy the ASCII version
{
}

inline mwstring::mwstring(const char* source, size_t n)
{
	m_value = ToWide(source, n);
}

inline mwstring::mwstring(const wchar_t* s, size_t n) :
m_value(s, n)
{
}

inline mwstring::mwstring(size_t n, wchar_t c) :
m_value(n, c)
{
}

inline mwstring::mwstring(size_t n, char c) :
m_value(n, wchar_t(c))
{
}

inline mwstring::mwstring()
{
}

inline mwstring::mwstring(const std::string& source)
{
	m_value = ToWide(source.c_str(), source.length());
}

inline mwstring::mwstring(const char* source)
{
	m_value = ToWide(source);
}

inline mwstring::mwstring(const std::wstring& source, size_t pos, size_t n /*= npos*/) :
m_value(source, pos, n)
{
}

inline mwstring::mwstring(const std::wstring& source) :
m_value(source)
{
}

#pragma warning(suppress : 4702)  // warning C4702: unreachable code
inline mwstring::mwstring(const wchar_t* source) : m_value(source)
{
}

template <class InputIterator>
inline mwstring::mwstring(InputIterator first, InputIterator last)
	: m_value(first, last)
{
}


inline mwstring operator+(const mwstring& first, const mwstring& second)
{
	mwstring result(first);
	return result.append(second);
}

inline mwstring operator+(const std::wstring& first, const mwstring& second)
{
	mwstring result(first);
	return result.append(second);
}

inline mwstring operator+(const mwstring& first, const std::wstring& second)
{
	mwstring result(first);
	return result.append(second);
}

inline mwstring operator+(const wchar_t* first, const mwstring& second)
{
	mwstring result(first);
	return result.append(second);
}

inline mwstring operator+(const mwstring& first, const wchar_t* second)
{
	mwstring result(first);
	return result.append(second);
}

inline mwstring operator+(wchar_t first, const mwstring& second)
{
	mwstring result(1, first);
	return result.append(second);
}

inline mwstring operator+(const mwstring& first, wchar_t second)
{
	mwstring result(first);
	return result.append(1, second);
}



inline bool operator==(const mwstring& first, const mwstring& second)
{
	return first.compare(second) == 0;
}

inline bool operator==(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) == 0;
}

inline bool operator==(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) == 0;
}

inline bool operator==(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) == 0;
}

inline bool operator==(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) == 0;
}



inline bool operator!=(const mwstring& first, const mwstring& second)
{
	return first.compare(second) != 0;
}

inline bool operator!=(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) != 0;
}

inline bool operator!=(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) != 0;
}

inline bool operator!=(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) != 0;
}

inline bool operator!=(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) != 0;
}



inline bool operator<(const mwstring& first, const mwstring& second)
{
	return first.compare(second) < 0;
}

inline bool operator<(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) > 0;
}

inline bool operator<(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) < 0;
}

inline bool operator<(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) > 0;
}

inline bool operator<(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) < 0;
}



inline bool operator>(const mwstring& first, const mwstring& second)
{
	return first.compare(second) > 0;
}

inline bool operator>(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) < 0;
}

inline bool operator>(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) > 0;
}

inline bool operator>(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) < 0;
}

inline bool operator>(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) > 0;
}



inline bool operator<=(const mwstring& first, const mwstring& second)
{
	return first.compare(second) <= 0;
}

inline bool operator<=(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) >= 0;
}

inline bool operator<=(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) <= 0;
}

inline bool operator<=(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) >=0;
}

inline bool operator<=(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) <= 0;
}



inline bool operator>=(const mwstring& first, const mwstring& second)
{
	return first.compare(second) >= 0;
}

inline bool operator>=(const std::wstring& first, const mwstring& second)
{
	return second.compare(first) <= 0;
}

inline bool operator>=(const mwstring& first, const std::wstring& second)
{
	return first.compare(second) >= 0;
}

inline bool operator>=(const wchar_t* first, const mwstring& second)
{
	return second.compare(first) <= 0;
}

inline bool operator>=(const mwstring& first, const wchar_t* second)
{
	return first.compare(second) >= 0;
}
//--------------------------------------------------------------------------------------------------
template<typename CharT>
inline std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& out, const misc::mwstring& str)
{
	out << std::basic_string<CharT>(str);
	return out;
}
inline std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& out, const misc::mwstring& str)
{
	return out << str.m_value;
}
//--------------------------------------------------------------------------------------------------
template<typename CharT>
inline std::basic_istream<CharT>& operator>>(std::basic_istream<CharT>& in, misc::mwstring& str)
{
	std::basic_string<CharT> tmp;
	in >> tmp;
	str = tmp;
	return in;
}

//! allow hashing over mwstring
inline size_t hash_value(const mwstring& str)
{
	return str.hash_value();
}

}  // namespace misc
//--------------------------------------------------------------------------------------------------
template<typename CharT>
inline std::basic_istream<CharT>& getline(std::basic_istream<CharT>& in, misc::mwstring& str)
{
	std::basic_string<CharT> tmp;
	getline(in, tmp);
	str = tmp;
	return in;
}
//--------------------------------------------------------------------------------------------------
template<typename CharT>
inline std::basic_istream<CharT>& getline(std::basic_istream<CharT>& in, misc::mwstring& str, const CharT delim)
{
	std::basic_string<CharT> tmp;
	getline(in, tmp, delim);
	str = tmp;
	return in;
}
//--------------------------------------------------------------------------------------------------
inline bool misc::mwstring::StartsWith(const wchar_t* begining) const
{
	const wchar_t* sIt = m_value.c_str();
	const wchar_t* sEndIt = sIt + m_value.size();
	for (const wchar_t* bIt = begining; (*bIt) != 0; ++bIt, ++sIt)
	{
		if (sIt == sEndIt)
		{ return false; }
		const wchar_t& s = (*sIt);
		const wchar_t& bS = (*bIt);
		if (s != bS)
		{ return false; }
	}
	return true;
}
//--------------------------------------------------------------------------------------------------
inline bool misc::mwstring::EndsWith(const wchar_t* ending) const
{
	const size_t eSize = wcslen(ending);
	const size_t size = m_value.size();
	if (eSize == 0)
	{ return true; }
	if (eSize > size)
	{ return false; }
	const wchar_t* sEnding = m_value.data() + size - eSize;
	return wcscmp(ending, sEnding) == 0;
}
//--------------------------------------------------------------------------------------------------
inline bool misc::mwstring::StartsWith(const misc::mwstring& begining) const
{
	return StartsWith(begining.data());
}
//--------------------------------------------------------------------------------------------------
inline bool misc::mwstring::EndsWith(const misc::mwstring& ending) const
{
	return EndsWith(ending.data());
}

#ifndef MW_USE_VS2008_COMPATIBILITY
namespace std
{
	//! Specialize std::hash for misc::mwstring
	template<> struct hash<misc::mwstring>
	{
		std::size_t operator()(misc::mwstring const& str) const
		{
			return str.hash_value();
		}
	};
}
#endif
#endif	//	MW_MWSTRING_HPP_
