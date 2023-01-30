// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPARSER_HPP_
#define MW_MWPARSER_HPP_

#include "mwAutoPointer.hpp"
#include "mwStringTokenizer.hpp"
#include "mwParserCommand.hpp"
#include "mwParserException.hpp"
#include "mwStringConversions.hpp"
#include <map>
#include "mwFileStream.hpp"
#include "mwStream.hpp"

namespace misc
{
template <typename T>
class MW_5AXUTIL_API mwParser
{
public:
	typedef typename misc::mwAutoPointer<mwParser<T> > Ptr;

	typedef std::map<misc::mwstring, typename mwParserCommand<T>::Ptr> ParserKeys;
	typedef typename ParserKeys::iterator ParserKeysIt;

	mwParser(const typename T::Ptr& data) : m_data(data), m_continueParsing(true)

	{
	}

	virtual void OnBeginParse()
	{
		throw mwParserException(mwParserException::PARSER_NOT_IMPLEMENTED);
	}


	virtual void OnParse(misc::mwIStream& /*in*/)
	{
	}

	virtual void Parse(misc::mwIStream& in)
	{
		OnParse(in);

		static const size_t MAX_LINE = 4096;

		wchar_t buf[MAX_LINE];
		misc::mwstring ts;
		OnBeginParse();
		unsigned int crtLineNr = 0;
		while (in.getline(buf, MAX_LINE))
		{
			OnParseLine();

			crtLineNr++;
			if (buf[0] == 0 || buf[0] == '(')
				continue;
			ts = buf;
			// trim starting spaces
			ts.erase(0, ts.find_first_not_of(_T(" ")));
			ts.erase(0, ts.find_first_not_of(_T("\t")));
			if (ts.empty())
				continue;

			ParseLine(ts, crtLineNr);

			AfterParseLine(in);

			if (!m_continueParsing)	 // for refactoring please see also case mw27851 and file
									 // cadcam::mwSTLFile.hpp
				break;
		}
		OnEndParse();
	}

	virtual void ParseLine(misc::mwstring ts, int lineNum)
	{
		size_t firstDelimiterPos = ts.find_first_of(_T(" \t"));

		misc::mwstring curMsgAction = ts.substr(0, firstDelimiterPos);
		ParserKeysIt it = m_keywords.find(curMsgAction);

		if (it != m_keywords.end())
		{
			(it->second)->Parse(m_data, ts, lineNum);
		}
		else
		{
			OnNoKeyword(ts, lineNum);
		}
	}

	virtual void OnNoKeyword(const misc::mwstring& line, const unsigned int& /*lineNr*/)
	{
		throw mwParserException(mwParserException::UNKNOWN_KEYWORD, MW_NULL, line);
	}

	virtual void OnEndParse()
	{
	}

	virtual void OnParseLine()
	{
	}

	virtual void AfterParseLine(misc::mwIStream& /*in*/)
	{
	}

protected:
	typename T::Ptr m_data;
	misc::mwstring m_filename;
	ParserKeys m_keywords;
	bool m_continueParsing;

private:
};

}  // namespace misc
#endif	//	MW_MWPARSER_HPP_
