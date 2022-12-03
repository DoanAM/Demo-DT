// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMATHEXCEPTION_HPP_
#define MW_MWMATHEXCEPTION_HPP_
#include "mwException.hpp"
#include "mwDllImpExpDef.hpp"


namespace misc
{

#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//!This class represents a math exception
class MW_5AXUTIL_API mwMathException :  public mwException
{
public:
	

	//!Types of math exceptions
	/*!Currently seven types are available:
		- division by 0
		- matrix not homogenous
		- incompatible vectors
		- incompatible matrices
		- vector and matrix incompatible
		- invalid matrix parameters
		- invalid vector parameters
		- determinant is zero, cannot find matrix inverse
	*/	
	enum mathExceptionType
	{
		//!Division by zero
		DIVISION_BY_ZERO,
		//!Error calling LoadIdentity
		MATRIX_NOT_HOMOGENOUS,
		//!Incompatible vectors for this operation (addition, etc.)
		INCOMPATIBLE_VECTORS,
		//!Incompatible matrices for this operation (multiply, etc.)
		INCOMPATIBLE_MATRICES,
		//!Incompatible pair of matrix and vector for this operation				
		VECTOR_AND_MATRIX_INCOMPATIBLE,
		//!Invalid matrix creation parameters
		INVALID_MATRIX_PARAMS,
		//!Invalid vector creation parameters
		INVALID_VECTOR_PARAMS,
		//!determinant is zero, cannot find matrix inverse
		DETERMINANT_IS_ZERO,
		//!Incompatible pair of matrices for this operation
		MATRICES_INCOMPATIBLE
	};


	//!Constructor
	/*!Constructs a new math exception
		\param strMsg exception message
		\param type exception type
	*/
	mwMathException( const misc::mwstring& strMsg,
		const enum mathExceptionType type );


	//!Copy constructor
	mwMathException(const mwMathException &src);


	//!Get exception type
	/*!
		\returns exception type (DIVISION_BY_ZERO, etc.)
	*/
	const mathExceptionType &GetExceptionType() const;


	//! Throw this exception
	virtual void Throw() const;


	//! Clone exception object
	/*!
	\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;


	protected:

	private:
	mathExceptionType			mExType;
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}
#endif	//	MW_MWMATHEXCEPTION_HPP_
