// (C) 2003-2014 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWMATHDEFEXCEPTION_HPP_
#define MW_MWMATHDEFEXCEPTION_HPP_
//#############################################################################
#include "mwException.hpp"
//#############################################################################
//!extends mwException implements mwMathDefException specific exception
/*!
*/
namespace mathdef
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
class MW_5AXUTIL_API mwMathDefException : public misc::mwException
{
public:
//#############################################################################
	enum Code
	{
		UNKNOWN=0,
		INDEX_OUT_OF_RANGE,
		NEGATIVE_POLYNOM_DEGREE,
		DIVISION_BY_ZERO=7050,
		DIFFERENT_DIMMENSIONS,
		INCOMPATIBLE_MATRICES=7104,
		NEW_VALUE_GREATER_THAN_PREVIOUS=7213,
		SECOND_VALUE_GREATER_THAN_FIRST=7214,
		DEGREE_TO_BIG=7215
	};
//#############################################################################
//!Default constructor
/*!
		\param errCode error code of the exception. 
		The default value is an unknown error
		\param prevLevel exception catched from the previous level. 
		MW_NULL if this is the first level of no exception history should be 
		provided
*/
	mwMathDefException(const misc::mwstring& strMsg,const Code vExcpID=UNKNOWN);
//#############################################################################
	//! Throw this exception
	virtual void Throw() const;

//#############################################################################
	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;

};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}
#endif	//	MW_MWMATHDEFEXCEPTION_HPP_
