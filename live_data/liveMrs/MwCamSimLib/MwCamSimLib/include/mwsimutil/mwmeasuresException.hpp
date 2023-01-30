// (C) 2008 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWMEASURESEXCEPTION_HPP_
#define MW_MWMEASURESEXCEPTION_HPP_
#include "mwException.hpp"

#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
class MW_5AXUTIL_API mwmeasuresException : public misc::mwException
{
public:
	enum errorIDD
	{
		UNKNOWN_UNITS=2141,
		UNDEFINED_SCALEFACTOR=2146
	};

	mwmeasuresException(errorIDD errorCode,const misc::mwException *prevLevel=0);

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	virtual void GetCopy(Ptr &dst) const;
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
#endif	//	MW_MWMEASURESEXCEPTION_HPP_
