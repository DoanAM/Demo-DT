// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPARSEREXCEPTION_HPP_
#define MW_MWPARSEREXCEPTION_HPP_

#include "mwException.hpp"
#include "mwStringConversions.hpp"
#include "mwAutoPointer.hpp"

#include "mwDllImpExpDef.hpp"
namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif

class MW_5AXUTIL_API mwParserException : public mwException
{
public:

	enum Code
	{		
		UNKNOWN = 0,
		PARSER_NOT_IMPLEMENTED=6250,
		UNKNOWN_KEYWORD=6251
	};

	//!Default constructor
	/*!
			\param vExcpID error code of the exception. 
			\param pPrevLevel exception caught from the previous level. 
			MW_NULL if this is the first level of no exception history should be 
			provided
	*/
	mwParserException(const Code vExcpID, 
		const mwException *pPrevLevel = 0,
		const misc::mwstring& additionalInfo = _T("") ) 
		: mwException(vExcpID,
		_T("Unknown exception !"),
		pPrevLevel)
	{
	
		misc::mwstring errMsg;
		switch(vExcpID) 
		{
			case UNKNOWN:
				errMsg = _T("Unknown exception");
			break;

			case PARSER_NOT_IMPLEMENTED:
				errMsg=_T("Parser not implemented");
			break;
			
			case UNKNOWN_KEYWORD:
				if( !additionalInfo.empty() )
				{
					errMsg = additionalInfo;
					errMsg += _T(" - ");
				}
				errMsg +=_T("Unknown keyword!");
			break;

			default:
				errMsg=_T("Unknown exception.");
			break;
		}

		SetErrorMessage( errMsg );
		
	};

	mwParserException( unsigned long errCode, 
			const misc::mwstring& errMsg = _T("Unknown error."),
			const mwException*prevLevel = 0 )
			: mwException( errCode, errMsg, prevLevel )

	{

	}

	//! Throw this exception
	virtual void Throw() const
	{
		throw mwParserException(*this);
	}

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const
	{
		return new mwParserException(*this);
	}

};

#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
};	// namespace misc
#endif	//	MW_MWPARSEREXCEPTION_HPP_
