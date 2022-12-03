// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSTLPARSEREXCEPTION_HPP_
#define MW_MWSTLPARSEREXCEPTION_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwException.hpp"
#include "mwParserException.hpp"


namespace cadcam
{

#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif

/// This class implements exceptions that could occur when parsing an
/// .stl ascii file
class MW_5AXUTIL_API mwSTLParserException: public misc::mwParserException
{
public:
	enum Code
	{

		FILE_NOT_FOUND = 2255,
		INVALID_FILE_FORMAT = 3501,  // invalid .stl file format

		UNKNOWN_FACET_PARAMETERS = 3502,  // not detected something like 'facet normal x y z'
		UNKNOWN_OUTER_PARAMETERS = 3503,  // not detected 'outer loop'
		UNKNOWN_VERTEX_PARAMETERS = 3504,  // //not detected something like 'vertex x y z'
		UNKNOWN_ENDLOOP_PARAMETERS = 3505,  // keyword 'endloop' bad string format
		UNKNOWN_ENDFACET_PARAMETERS = 3506,  //// keyword 'endfacet' bad string format
		UNKNOWN_END_PARAMETERS = 3507,  // found 'end' but next token is not 'solid' ,'loop' 'facet'

		FILE_OPEN_ERROR = 3508,  // error opening input file
		INVALID_TRIANGLE = 3509,  // inavalid triangle readed
		INVALID_SYNTAX = 3510,  // invalid stl syntax
		INVALID_NUMBER_OF_TRIANGLES = 3511,
		UNEXPECTED_END_OF_STREAM = 2148,
		FILE_EMPTY,
		PARSER_NOT_IMPLEMENTED = misc::mwParserException::PARSER_NOT_IMPLEMENTED,
		UNKNOWN_KEYWORD = misc::mwParserException::UNKNOWN_KEYWORD,
	};

	/// Default constructor
	///
	///	@param vExcpID exception Code
	///	@param pPrevLevel exception catched from the previous level.
	///	MW_NULL if this is the first level of no exception history should be
	///	provided
	mwSTLParserException(const Code vExcpID, const misc::mwException* pPrevLevel = 0);

	/// Throw this exception
	virtual void Throw() const;

	/// Clone exception object
	///
	/// @param[out] dst pointer to this exception object
	const Ptr GetCopy() const;
};

#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}  // namespace cadcam
#endif  //	MW_MWSTLPARSEREXCEPTION_HPP_
