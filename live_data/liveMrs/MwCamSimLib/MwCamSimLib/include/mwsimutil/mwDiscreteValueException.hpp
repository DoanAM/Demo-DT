// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWDISCRETEVALUEEXCEPTION_HPP_
#define MW_MWDISCRETEVALUEEXCEPTION_HPP_

#include "mwException.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
template <class T> class MW_5AXUTIL_API mwDiscreteValueException : public mwException
{
public:
	mwDiscreteValueException()
		:mwException( 0, _T("Discrete variable doesn't support passed value") )
	{
	}

	//! Throw this exception
	virtual void Throw() const
	{
		throw mwDiscreteValueException(*this);
	}

	//! Clone exception object
	/*!
	\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const
	{
		return new mwDiscreteValueException(*this);
	}
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}
#endif	//	MW_MWDISCRETEVALUEEXCEPTION_HPP_
