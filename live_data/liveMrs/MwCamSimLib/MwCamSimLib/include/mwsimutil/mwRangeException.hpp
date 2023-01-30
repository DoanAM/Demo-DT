// (C) 2003-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWRANGEEXCEPTION_HPP_
#define MW_MWRANGEEXCEPTION_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwException.hpp"
#include "mwStringConversions.hpp"
#include "mwAutoPointer.hpp"


namespace misc
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif

/// mwBaseRangeException class
/// This is the base class for al mwRangeException classes
class MW_5AXUTIL_API mwBaseRangeException : public mwException
{
public:
	
	enum exceptionType
	{
		VALUE_OVERFLOW,
		VALUE_UNDERFLOW,
		EXCEPTION_ERROR
	};

	//! Constructor function
	/*!
		\ see the base class (mwException) constructor parameters
		\param errCode error code of the exception. 
		The default value of 0 is an unknown error
		\param errMsg default error message (english) for the given error 
		code
		\param prevLevel exception catched from the previous level. 
		MW_NULL if this is the first level of no exception history should be 
		provided
		
	*/
	inline mwBaseRangeException( unsigned long errCode, 
		const misc::mwstring &errMsg = _T("Unknown error."),
		const mwException *prevLevel = 0 )
		:mwException( errCode, errMsg, prevLevel )
	{
		mExcType = EXCEPTION_ERROR;
	};

	
	virtual ~mwBaseRangeException(){};

	//! &GetType function
	/*!
		\return &GetType of type inline const exceptionType
	*/
	inline const exceptionType &GetType() const
	{
		return mExcType;
	};

	//! Throw this exception
	virtual void Throw() const
	{
		throw mwBaseRangeException(*this);
	}

	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const
	{
		return new mwBaseRangeException(*this);
	}

protected:

	exceptionType		mExcType;
};





//!mwRangeException class
/*!This class represents a mwRangeException*/
template < class T > class MW_5AXUTIL_API mwRangeException : public mwBaseRangeException
{
public:
	
	//! mwRangeException function
	/*!
		\param minValue of type const T &
		\param maxValue of type const T &
		\param currentValue of type const T &
		\param prec precision used for formating the values
		\return mwRangeException of type inline
	*/
	inline mwRangeException( const T &minValue, const T &maxValue,
		const T &currentValue , unsigned short prec = 0 )
		:mwBaseRangeException(0), mMinValue( minValue ), 
		mMaxValue( maxValue ), mCurrValue( currentValue )
	{
		misc::mwstring errMsg;
		
		errMsg = _T("Given value (");
		errMsg += misc::from_value( currentValue , prec);
		errMsg += _T(") is out of range (");
		errMsg += misc::from_value( minValue , prec);
		errMsg += _T(" , ");
		errMsg += misc::from_value( maxValue , prec);
		errMsg += _T(")");

		if( currentValue < minValue )
		{
			mExcType = VALUE_UNDERFLOW;
			errMsg = _T("Given value (");
			errMsg += misc::from_value( currentValue , prec);
			errMsg += _T(") is less than allowed min value (");
			errMsg += misc::from_value( minValue , prec);
			errMsg += _T(")");
		}
		else if( currentValue > maxValue )
		{
			mExcType = VALUE_OVERFLOW;
			errMsg = _T("Given value (");
			errMsg += misc::from_value( currentValue , prec);
			errMsg += _T(") is greater than allowed max value (");
			errMsg += misc::from_value( maxValue , prec);
			errMsg += _T(")");
		}
		else
		{
			mExcType = EXCEPTION_ERROR;
		}
		SetErrorMessage( errMsg );
	};
	
	//! &GetMinValue function
	/*!
		\return &GetMinValue of type inline const T
	*/
	inline const T &GetMinValue() const
	{
		return mMinValue;
	};
	
	//! &GetMaxValue function
	/*!
		\return &GetMaxValue of type inline const T
	*/
	inline const T &GetMaxValue() const
	{
		return mMaxValue;
	};
	
	//! &GetValue function
	/*!
		\return &GetValue of type inline const T
	*/
	inline const T &GetValue() const
	{
		return mCurrValue;
	};

	//! Throw this exception
	virtual void Throw() const
	{
		throw mwRangeException(*this);
	}

	//! Clone exception object
	/*!
	\param[out] dst pointer to this exception object
	*/
	virtual const Ptr GetCopy() const
	{
		return new mwRangeException(*this);
	}


protected:
private:

	T					mMinValue;
	T					mMaxValue;
	T					mCurrValue;
};

#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}
#endif	//	MW_MWRANGEEXCEPTION_HPP_
