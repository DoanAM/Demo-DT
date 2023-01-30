// (C) 2003-2007 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPARAMSTORAGEEXCEPTION_HPP_
#define MW_MWPARAMSTORAGEEXCEPTION_HPP_
#include "mwStringConversions.hpp"
#include <mwException.hpp>
#include "mwDllImpExpDef.hpp"

namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//!mwParamStorageException class
/*!This class represents a mwParamStorageException*/
class MW_5AXUTIL_API mwParamStorageException : public mwException
{
public:
	enum paramStorageExceptionCause
	{
		STORAGE_OPEN_FAILURE,
		STORAGE_READ_FAILURE,
		STORAGE_WRITE_FAILURE,
		STORAGE_DELETE_FAILURE
	};
	
	//! mwParamStorageException function
	/*!
		\param cause of type const paramStorageExceptionCause
		\param addInfo of type const misc::mwstring &
		\returns mwParamStorageException of type 
	*/
	explicit mwParamStorageException( const paramStorageExceptionCause cause, 
		const misc::mwstring &addInfo = _T("") );

	//! &GetAdditionalInfo function
	/*!
		\returns &GetAdditionalInfo of type const misc::mwstring
	*/
	const misc::mwstring &GetAdditionalInfo() const;

	//! &GetCause function
	/*!
		\returns &GetCause of type const paramStorageExceptionCause
	*/
	const paramStorageExceptionCause &GetCause() const;

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;

protected:
private:

	paramStorageExceptionCause mExceptionCause;
	misc::mwstring mAddInfo;
	
};

#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
};
#endif	//	MW_MWPARAMSTORAGEEXCEPTION_HPP_
