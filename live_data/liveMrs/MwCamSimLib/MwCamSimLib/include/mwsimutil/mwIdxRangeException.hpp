// (C) 2003-2016 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWIDXRANGEEXCEPTION_HPP_
#define MW_MWIDXRANGEEXCEPTION_HPP_
#include "mwException.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwStringConversions.hpp"
#include "mwAutoPointer.hpp"


namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//!This class represents a index out of range exception.
template<class T>
class MW_5AXUTIL_API mwIdxRangeException : public mwException
{
public:
	//!Constructor
	/*!Constructs an exception object with given parameters:
		\param maxIndex const max index
		\param givenIndex const given index
	*/
	mwIdxRangeException(const T& maxIndex, const T& givenIndex)
		: mwException(0, _T("Unknown exception")), m_maxIndex(maxIndex), m_givenIndex(givenIndex)
	{
		misc::mwstring errorMsg = _T("Index out of bounds. Max index accepted: ");
		errorMsg += misc::from_value(m_maxIndex);
		errorMsg += _T(", index given: ");
		errorMsg += misc::from_value(m_givenIndex);
		errorMsg += _T(".");
		SetErrorMessage(errorMsg);
	}

	//!The GetMaxIndex function
	/*!The GetMaxIndex function
		\return	const ref to a T
	*/
	const T& GetMaxIndex() const
	{
		return m_maxIndex;
	}

	//!The GetGivenIndex function
	/*!The GetGivenIndex function
		\return	const ref to a T
	*/
	const T& GetGivenIndex() const
	{
		return m_givenIndex;
	}

	//! Throw this exception
	virtual void Throw() const
	{
		throw mwIdxRangeException(*this);
	}

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const
	{
		return new mwIdxRangeException(*this);
	}

private:
	T m_maxIndex;
	T m_givenIndex;
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}  // namespace misc
#endif	//	MW_MWIDXRANGEEXCEPTION_HPP_
