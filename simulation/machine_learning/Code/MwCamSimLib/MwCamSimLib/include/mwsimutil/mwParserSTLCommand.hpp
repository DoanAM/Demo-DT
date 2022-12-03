// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPARSERSTLCOMMAND_HPP_
#define MW_MWPARSERSTLCOMMAND_HPP_
#include "mwParserCommand.hpp"
#include "mwSTLFile.hpp"
#include "mwSTLParserException.hpp"
#include "mwStringTokenizer.hpp"


namespace cadcam
{
/// This file contains classes that are responsable for handling keywords from
///
/// an .stl ascii file.
/// Each class handles a specific keyword.


/// This class handles 'solid' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdSolid: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdSolid<T>> Ptr;

	/// Constructor
	///
	/// Constructs a class for handling keyword 'solid' from an  .stl ascii file
	mwParserCmdSolid() {}

	/// Parse
	///
	/// Parse parameters specific for 'solid' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	  stores data readed from an .stl ascii file
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& /*word*/,
		const unsigned int& /*linePos*/)
	{
		data->Keyword_Solid();
	}

protected:
private:
};  // mwParserCmdSolid


/// This class handles 'facet' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdFacet: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdFacet<T>> Ptr;

	/// Constructor
	///
	/// Constructs a class for handling keyword 'facet' from an  .stl ascii file
	mwParserCmdFacet() {}

	/// Parse
	///
	/// Parse parameters specific for 'facet' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'facet' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;
		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);
		if (tokenizer.GetSize() != 5)
			throw mwSTLParserException(mwSTLParserException::UNKNOWN_FACET_PARAMETERS);


		double value[3];
		for (int i = 2; i < 5; ++i)
		{
			misc::to_value(tokenizer[i], value[i - 2]);
		}

		typename mwSTLFile<T>::dPoint3D crtPoint(
			static_cast<T>(value[0]), static_cast<T>(value[1]), static_cast<T>(value[2]));
		data->Keyword_Facet(crtPoint);
	}
};  // mwParserCmdFacet


/// This class handles 'outer' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdOuter: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdOuter<T>> Ptr;

	/// Constructs a class for handling keyword 'outer' from an  .stl ascii file
	mwParserCmdOuter() {}

	/// Parse parameters specific for 'outer' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'outer' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;
		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);

		if (tokenizer.GetSize() == 2)
		{
			misc::mwstring strLoop(_T("loop"));
			if (tokenizer[1].compare(strLoop) != 0)
				throw mwSTLParserException(mwSTLParserException::UNKNOWN_OUTER_PARAMETERS);
		}
		data->Keyword_Outer();
	}
};  // mwParserCmdOuter


/// This class handles 'vertex' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdVertex: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdVertex<T>> Ptr;

	/// Constructs a class for handling keyword 'vertex' from an  .stl ascii file
	mwParserCmdVertex() {}

	/// Parse
	///
	/// Parse parameters specific for 'vertex' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	  stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'vertex' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;

		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);
		if (tokenizer.GetSize() != 4)
			throw mwSTLParserException(mwSTLParserException::UNKNOWN_VERTEX_PARAMETERS);

		double value[3];  // coordinates (x,y,z) of the current vertex
		for (int i = 1; i < 4; ++i)
		{
			misc::to_value(tokenizer[i], value[i - 1]);
		}

		typename mwSTLFile<T>::dPoint3D crtPoint(
			static_cast<T>(value[0]), static_cast<T>(value[1]), static_cast<T>(value[2]));
		data->Keyword_Vertex(crtPoint);
	}
};  // mwParserCmdVertex


/// This class handles 'endloop' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdEndLoop: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdEndLoop<T>> Ptr;

	/// Constructs a class for handling keyword 'endloop' from an  .stl ascii file
	mwParserCmdEndLoop() {}

	/// Parse
	///
	/// Parse parameters specific for 'endloop' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'endloop' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;
		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);

		if (tokenizer.GetSize() > 1)
			throw mwSTLParserException(mwSTLParserException::UNKNOWN_ENDLOOP_PARAMETERS);

		data->Keyword_EndLoop();
	}
};  // mwParserCmdEndLoop


/// This class handles 'endfacet' keyword from an .stl ascii file

template <typename T>
class MW_5AXUTIL_API mwParserCmdEndFacet: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdEndFacet<T>> Ptr;

	/// Constructs a class for handling keyword 'endfacet' from an  .stl ascii file
	mwParserCmdEndFacet() {}

	/// Parse
	///
	/// Parse parameters specific for 'endfacet' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'endfacet' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;
		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);

		// could be 'end facet' or 'endfacet 0'
		if (tokenizer.GetSize() > 1)
		{
			if (tokenizer[0] != _T("endfacet"))
				throw mwSTLParserException(mwSTLParserException::UNKNOWN_ENDFACET_PARAMETERS);
		}


		data->Keyword_EndFacet();
	}
};  // mwParserCmdEndFacet


/// This class handles 'endsolid' keyword from an .stl ascii file

template <typename T>
class MW_5AXUTIL_API mwParserCmdEndSolid: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdEndSolid<T>> Ptr;

	/// Constructs a class for handling keyword 'endsolid' from an  .stl ascii file
	mwParserCmdEndSolid() {}

	/// Parse
	///
	/// Parse parameters specific for 'endsolid' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& /*word*/,
		const unsigned int& /*linePos*/)
	{
		data->Keyword_EndSolid();
	}

protected:
private:
};  // mwParserCmdEndSolid


/// This class handles 'end' keyword from an .stl ascii file
template <typename T>
class MW_5AXUTIL_API mwParserCmdEndBlock: public misc::mwParserCommand<mwSTLFile<T>>
{
public:
	typedef misc::mwAutoPointer<mwParserCmdEndBlock<T>> Ptr;

	/// Constructs a class for handling keyword 'end' from an  .stl ascii file
	mwParserCmdEndBlock() {}

	/// Parse
	///
	/// Parse parameters specific for 'end' keyword
	///	@param data reference to an autopointer to a cadcam::mwSTLFile class that
	///	 stores data readed from an .stl ascii file
	///	@param word a line of text from .stl ascii file, starting with 'end' keyword
	virtual void Parse(
		typename mwSTLFile<T>::Ptr& data,
		const misc::mwstring& word,
		const unsigned int& /*linePos*/)
	{
		misc::mwStringTokenizer tokenizer;
		tokenizer.SetCharDelimiters(_T(" \t"));
		tokenizer.Parse(word);

		if (tokenizer.GetSize() >= 2)  // keyword is like : 'end loop' , 'end facet', 'end solid'
		{
			misc::mwstring strLoop(_T("LOOP"));
			misc::mwstring strFacet(_T("FACET"));
			misc::mwstring strSolid(_T("SOLID"));

			misc::mwstring strSecond = tokenizer[1];

			mwSTLFile<T>::StringTrimAndToUpper(strSecond);

			if (strSecond.compare(strLoop) == 0)  // keyword is 'end loop'
				data->Keyword_EndLoop();
			else if (strSecond.compare(strFacet) == 0)  // keyword is 'end facet'
				data->Keyword_EndFacet();
			else if (strSecond.compare(strSolid) == 0)  // keyword is 'end solid'
				data->Keyword_EndSolid();
			else
				throw mwSTLParserException(mwSTLParserException::UNKNOWN_END_PARAMETERS);
		}
	}
};  // mwParserCmdEndBlock

}  // namespace cadcam
#endif  //	MW_MWPARSERSTLCOMMAND_HPP_
