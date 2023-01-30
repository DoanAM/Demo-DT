// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWLOGGER_HPP_
#define MW_MWLOGGER_HPP_
#include "mwAutoPointer.hpp"
#include "mwDefines.hpp"
#include "mwStream.hpp"
#include "mwTxtOutputStream.hpp"

#include <list>
#include <vector>

namespace misc
{
class MW_5AXUTIL_API mwWarningMessage
{
public:
	mwWarningMessage()
		:m_id(0)
	{}
	mwWarningMessage(size_t id, misc::mwstring string)
	{
		m_id = id;
		m_stringMsg = string;
	}
	size_t GetID() const
	{
		return m_id;
	}
	const misc::mwstring& GetMessage() const
	{
		return m_stringMsg;
	}
	bool operator==(const mwWarningMessage& toCmp) const
	{
		return (m_id == toCmp.m_id) && (m_stringMsg == toCmp.m_stringMsg);
	}

private:
	size_t m_id;
	misc::mwstring m_stringMsg;
};


// a very simple import only API macro. the dllexport is handled via auto generated .def file
#if defined(_WIN32) && defined(MW_misc_IS_SHARED_LIB) && !defined(misc_EXPORTS) && !defined(MW_SIMUTIL_EXPORTS)
#define MW_MISC_STATIC_MEMBER_IMPORT __declspec(dllimport)
#else
#define MW_MISC_STATIC_MEMBER_IMPORT
#endif

class MW_5AXUTIL_API mwLogger
{
private:
#pragma warning(push)
#pragma warning(disable : 4251)
	mwAutoPointer<mwTxtOutputStream> os;
#pragma warning(pop)

public:
	mwLogger(const mwAutoPointer<misc::mwTxtOutputStream>& oStream);
	mwLogger(mwOStream& oStream = mwCout);

	~mwLogger();

	MW_MISC_STATIC_MEMBER_IMPORT static const mwstring NewLine;

	mwLogger& operator<<(const mwWarningMessage& t);
	mwLogger& operator<<(const bool& t);
	mwLogger& operator<<(const long& t);
	mwLogger& operator<<(const int& t);
	mwLogger& operator<<(const short& t);
	mwLogger& operator<<(const char& t);
	mwLogger& operator<<(const unsigned long& t);
	mwLogger& operator<<(const unsigned int& t);
	mwLogger& operator<<(const unsigned short& t);
#ifdef _WIN64  // VC++ 8.0
	mwLogger& operator<<(const size_t& t);
#endif
	mwLogger& operator<<(const unsigned char& t);
	mwLogger& operator<<(const char* t);
	mwLogger& operator<<(const wchar_t* t);
	mwLogger& operator<<(const double& t);
	mwLogger& operator<<(const float& t);
	mwLogger& operator<<(const mwstring& t);

	template <typename T>
	mwLogger& operator<<(mwAutoPointer<T> ap)
	{
		if (ap.IsNull())
			return (*this) << _T("MW_NULL");
		return (*this) << *ap;
	}

	template <typename T>
	mwLogger& operator<<(std::list<T>& l)
	{
		(*this) << _T("List size = ") << l.size() << mwLogger::NewLine;
		typename std::list<T>::iterator it = l.begin();
		for (int i = 0; it != l.end(); it++, i++)
			(*this) << _T("Item #") << i << _T(" = ") << *it << mwLogger::NewLine;
		return (*this);
	}

	template <typename T>
	mwLogger& operator<<(const std::list<T>& l)
	{
		(*this) << _T("List size = ") << l.size() << mwLogger::NewLine;
		typename std::list<T>::const_iterator it = l.begin();
		for (int i = 0; it != l.end(); it++, i++)
			(*this) << _T("Item #") << i << _T(" = ") << *it << mwLogger::NewLine;
		return (*this);
	}

	template <typename T>
	mwLogger& operator<<(std::vector<T>& v)
	{
		(*this) << _T("Vector size = ") << v.size() << mwLogger::NewLine;
		typename std::vector<T>::iterator it = v.begin();
		for (int i = 0; it != v.end(); it++, i++)
			(*this) << _T("Item #") << i << _T(" = ") << *it << mwLogger::NewLine;
		return (*this);
	}

	template <typename T>
	mwLogger& operator<<(const std::vector<T>& v)
	{
		(*this) << _T("Vector size = ") << v.size() << mwLogger::NewLine;
		typename std::vector<T>::const_iterator it = v.begin();
		for (int i = 0; it != v.end(); it++, i++)
			(*this) << _T("Item #") << i << _T(" = ") << *it << mwLogger::NewLine;
		return (*this);
	}

private:
	mwLogger& operator=(mwLogger&);
};
}  // namespace misc
#endif  //	MW_MWLOGGER_HPP_
