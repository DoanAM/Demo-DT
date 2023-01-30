// (C) 2004-2013 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWPOLYNOMIAL_HPP_
#define MW_MWPOLYNOMIAL_HPP_
#include "mwMathDefException.hpp"
#include <vector>

namespace mathdef
{
	template <class T>
	class MW_5AXUTIL_API mwPolynomial
	{
	public:
//#############################################################################
		//! Default Constructor
		/*! 				
		 \param iDegree represent the degree of the polynomial, all coefficients will be
				initialized with zero
		*/	    
	    mwPolynomial (const size_t iDegree = 0);
//#############################################################################
		//! Copy constructor
		/*! 				
		 \param toCopy the polynomial to be copy 
		*/	    
	    mwPolynomial (const mwPolynomial<T>& toCopy);
//#############################################################################
		//! Default destructor
	    virtual ~mwPolynomial ();
//#############################################################################		
		//! Set the degree of the polynomial
		/*!
		 \param iDegree the new degree of the polynomial
		*/
	    void SetDegree (size_t iDegree, const bool &bResetCoeffs = false);
//#############################################################################		
		//! Get the degree of the polynomial
		/*!
		 \returns the Degree of the polynomial
		*/
	    size_t GetDegree () const;
//#############################################################################	
		//!Indexer operator for coefficients values
		/*!Returns, for a given index, the corresponding coefficient of the polynomial.
			If number of index out of range an exception will be thrown
			\param index position in the polynomial 
			\returns the corresponding coefficient of the polynomial
		*/
//#############################################################################	
	    T operator[] (size_t i) const;
		//!Indexer operator for coefficients values
		/*!Returns, for a given index, the corresponding coefficient of the polynomial.
			If number of index out of range an exception will be thrown
			\param index position in the polynomial 
			\returns the reference of the corresponding coefficient in the polynomial
		*/
	    T& operator[] (size_t i);
//#############################################################################		
   		//!Assigment operator
		/*!Assigns one object to another
		  \param toCopy to copy the information from
		*/
	    mwPolynomial<T>& operator= (const mwPolynomial<T>& toCopy);
//#############################################################################		
		//! Evaluation _T("operator")
		/*! Evaluate the polynomial
		  \param fT the value of ... X variable
		*/	    
	    T operator() (T fT) const;
//#############################################################################		
		// Composition of polynomials
		mwPolynomial<T> operator() (const mwPolynomial<T>& rkPoly) const;
//#############################################################################		
		//! Arithmetic operations 	    
	    mwPolynomial<T> operator+ (const mwPolynomial<T>& rkPoly) const;
	    mwPolynomial<T> operator- (const mwPolynomial<T>& rkPoly) const;
	    mwPolynomial<T> operator* (const mwPolynomial<T>& rkPoly) const;
	    mwPolynomial<T> operator+ (T fScalar) const;  // input is degree 0 poly
	    mwPolynomial<T> operator- (T fScalar) const;  // input is degree 0 poly
	    mwPolynomial<T> operator* (T fScalar) const;
	    mwPolynomial<T> operator/ (T fScalar) const;
	    mwPolynomial<T> operator- () const;
//#############################################################################	
		//! Arithmetic updates	    
	    mwPolynomial<T>& operator += (const mwPolynomial<T>& rkPoly);
	    mwPolynomial<T>& operator -= (const mwPolynomial<T>& rkPoly);
	    mwPolynomial<T>& operator *= (const mwPolynomial<T>& rkPoly);
	    mwPolynomial<T>& operator += (T fScalar);  // input is degree 0 poly
	    mwPolynomial<T>& operator -= (T fScalar);  // input is degree 0 poly
	    mwPolynomial<T>& operator *= (T fScalar);
	    mwPolynomial<T>& operator /= (T fScalar);
//#############################################################################	
		//! Evaluate the polynomial from a given x position
		virtual const T Evaluate( const T pos ) const;
		//! Evaluate the polynomial derivate from a given x position
		virtual const T EvaluateDeriv( const T pos ) const;
		//! Adds a new root to the polynomial. This in fact is a multiplication with the polynomial X - newRoot
		mwPolynomial<T>& AddNewRoot( T newRoot );
		//! Returns the derivative of this polynomial
		mwPolynomial<T> Derivative() const;
	protected:
	    size_t m_iDegree;		
		std::vector<T> m_coef;	    
	};

template <class T>
	mwPolynomial<T> operator* (T fScalar,
    const mwPolynomial<T>& rkPoly);

typedef mwPolynomial<float> mwPolynomialf;
typedef mwPolynomial<double> mwPolynomiald;
}
#endif	//	MW_MWPOLYNOMIAL_HPP_
