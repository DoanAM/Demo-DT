// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPARSERSTL_HPP_
#define MW_MWPARSERSTL_HPP_
#include "mwAvoid_Warnings.hpp"
#include "mwParser.hpp"
#include "mwParserSTLCommand.hpp"
#include "mwSTLFile.hpp"
#include "mwStringConversions.hpp"
#include "mwStringTokenizer.hpp"


namespace cadcam
{
/// This class is a parser for an Stereolithography ASCII (.stl) file
template <typename T>
class MW_5AXUTIL_API mwParserSTL: public misc::mwParser<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserSTL<T>> Ptr;
	typedef typename misc::mwParser<mwSTLFile<T>>::ParserKeysIt ParserKeysIt;

	/// Default constructor
	///
	/// Constructs a parser for an .stl ascii file
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class
	///	that implements a .stl ascii file
	mwParserSTL(const typename mwSTLFile<T>::Ptr& data): misc::mwParser<mwSTLFile<T>>(data) {}

	/// OnBeginParse called before starting file parsing
	///
	/// Constructs a class for each keyword that is contained in an .stl ascii file.
	///  Each constructed class handles corresponding keyword
	virtual void OnBeginParse()
	{
		this->m_keywords[_T("solid")] = new mwParserCmdSolid<T>();
		this->m_keywords[_T("facet")] = new mwParserCmdFacet<T>();
		this->m_keywords[_T("outer")] = new mwParserCmdOuter<T>();
		this->m_keywords[_T("outerloop")] = new mwParserCmdOuter<T>();
		this->m_keywords[_T("vertex")] = new mwParserCmdVertex<T>();
		this->m_keywords[_T("endloop")] = new mwParserCmdEndLoop<T>();
		this->m_keywords[_T("endfacet")] = new mwParserCmdEndFacet<T>();
		this->m_keywords[_T("endsolid")] = new mwParserCmdEndSolid<T>();
		this->m_keywords[_T("end")] = new mwParserCmdEndBlock<T>();
	}

	/// OnEndParse called after finishing file parsing
	virtual void OnEndParse() {}

	virtual void ParseLine(misc::mwstring ts, int lineNum)
	{
		misc::string_down(ts);  // keywords are all down
		misc::mwParser<mwSTLFile<T>>::ParseLine(ts, lineNum);
	}

	virtual void AfterParseLine(misc::mwIStream& in)
	{
		if (this->m_data->IsDefinitionComplete())
		{
			/*
			Use case:
			(a) stl ascii information with multiple "solid name" sections
			(b) misc::mwIStream is created from a *.stl file or *.sim file or other supported files
			(*.cl not tested)
				- *.sim file parsing mesh of tool part definition (e.g. lathe holder)
				- *.stl file parsing machine element (e.g. fixture.slt)
			*/

			std::streampos pos;

			try
			{
				// preserve stream current position
				pos = in.tellg();
			}
			catch (std::ios::failure)
			{
				return;
			}

			// if another "solid name" section follows then continue parsing.
			static const size_t MAX_LINE = 4096;
			wchar_t buf[MAX_LINE];
			misc::mwstring ts;
			while (in.getline(buf, MAX_LINE))
			{
				if (buf[0] == 0)
					continue;
				ts = buf;
				// trim starting spaces
				ts.erase(0, ts.find_first_not_of(_T(" ")));
				ts.erase(0, ts.find_first_not_of(_T("\t")));
				if (ts.empty())
					continue;

				// lookup "solid" keyword
				size_t firstDelimiterPos = ts.find_first_of(_T(" "));
				misc::mwstring curMsgAction = ts.substr(0, firstDelimiterPos);

				ParserKeysIt it = this->m_keywords.find(curMsgAction);

				if (it != this->m_keywords.end() && it->first == _T("solid"))
				{
					this->m_continueParsing = true;
				}
				else
				{
					this->m_continueParsing = false;
				}

				// restore position
				in.seekg(pos);
				break;
			}  // while
		}  // if

	}  // AfterParseLine

protected:
private:
};

}  // namespace cadcam
#endif  //	MW_MWPARSERSTL_HPP_
