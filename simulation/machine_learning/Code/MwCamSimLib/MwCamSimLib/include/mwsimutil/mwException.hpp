// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWEXCEPTION_HPP_
#define MW_MWEXCEPTION_HPP_
#include <vector>
#include "mwDefines.hpp"
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"

#if defined(__GNUC__) && __GNUC__ >= 4
#define MW_EXCEPTION(errorText) throw misc::mwException(0,\
	misc::mwstring(__func__) + _T(": ") + misc::mwstring(errorText))
#else
#define MW_EXCEPTION(errorText) throw misc::mwException(0,\
	misc::mwstring(_T(__FUNCTION__)) + _T(": ") + misc::mwstring(errorText))
#endif

#define MW_EXCEPTION_IF_TRUE(condition, errorText)\
	if (condition) MW_EXCEPTION(errorText)

#define MW_EXCEPTION_IF_FALSE(condition, errorText)\
	if (!(condition)) MW_EXCEPTION(errorText)

#define MW_EXCEPTION_IF_THROW(tryCode, errorText)\
	try{ tryCode; } catch(...) { MW_EXCEPTION(errorText); }

namespace misc
{
template <typename T> class mwAutoPointer;
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//!Common exception class
/*!This class provides common exception functionality
	with stack of exception history
*/
class MW_5AXUTIL_API mwException
{

public:

	/*! \var typedef std::vector< std::pair< unsigned long, misc::mwstring > > exceptionStack
		\brief A type redefinition for
			std::vector< std::pair< unsigned long, misc::mwstring > >				as exceptionStack
	*/
	typedef std::vector< std::pair< unsigned long, misc::mwstring > > exceptionStack;
	typedef misc::mwAutoPointer< mwException > Ptr;

	//!Default constructor
	/*!\param errCode error code of the exception. 
		The default value of 0 is an unknown error
		\param errMsg default error message (english) for the given error 
		code
		\param prevLevel exception catched from the previous level. 
		MW_NULL if this is the first level of no exception history should be 
		provided
	*/
	explicit mwException( unsigned long errCode, 
		const misc::mwstring &errMsg = _T("Unknown error."),
		const mwException *prevLevel = 0 );

#ifdef MW_USE_VS2008_COMPATIBILITY
	//!Destructor
	virtual ~mwException() {}
#else
	mwException(const mwException& other) = default;
	mwException(mwException&& other) = default;
	mwException& operator=(const mwException& other) = default;
	mwException& operator=(mwException&& other) = default;
	virtual ~mwException() = default;
#endif

	//!Equality operator
	/*!Are exceptions equal
		\param toCompare exception to compare the current exception with
		\returns true if exceptions are equal
	*/
	bool operator==( const mwException &toCompare ) const;

	//!Inequality operator
	/*!Are exceptions equal
		\param toCompare exception to compare the current exception with
		\returns true if exceptions are not equal
	*/
	bool operator!=( const mwException &toCompare ) const;

	//!Get error message
	/*!Get the default error message of this exception
		\returns reference to a string containing the error message
	*/
	const misc::mwstring &GetErrorMessage() const;

	//!Get error messages from the entire exception stack
	/*!
		\returns a complete error message
	*/
	const misc::mwstring GetCompleteErrorMessage() const;

	//!Get error code
	/*!Get error code of the exception. The error code can be e.g. used to 
		provide a language dependent information about the error occured
		\returns error code
	*/
	long GetErrorCode() const;

	//!Get exception stack
	/*!Returns the array of the exceptions occured on the lower level
		\returns array of exceptions
	*/
	const exceptionStack &GetExceptionStack() const;

	//!Set error message
	/*!Set the default error message of this exception
		\param errorMessage the new error message to set
	*/
	void SetErrorMessage( const misc::mwstring &errorMessage );

	//!Set error code
	/*!Set error code of the exception. The error code can be e.g. used to 
		provide a language dependent information about the error occured
		\param newErrorCode the new error code to set
	*/
	void SetErrorCode( const unsigned long newErrorCode );

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const;

	//! Checks for the given error code in exception and call stack
	/*! Checks if the received error code is the code of the 
			exception itself or one from exception stack
		\param errorCodeToSearchFor the error code to search for in exception and call stack
		\returns true if the given error code was found, false otherwise
	*/
	bool IsOrContainsErrorCode(unsigned long errorCodeToSearchFor) const;
private:
#pragma warning(suppress : 4251)
	misc::mwstring		m_defErrMsg;
	unsigned long		m_errCode;
#pragma warning(suppress : 4251)
	exceptionStack		m_exStack;
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}
#endif	//	MW_MWEXCEPTION_HPP_
