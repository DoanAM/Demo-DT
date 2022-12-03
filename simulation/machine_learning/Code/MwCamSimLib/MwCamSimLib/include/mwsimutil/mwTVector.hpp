// (C) 2003-2009 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTVECTOR_HPP_
#define MW_MWTVECTOR_HPP_
#include "mwDllImpExpDef.hpp"

namespace mathdef
{

template <int N, class T>
	class MW_5AXUTIL_API mwTVector
	{
	public:

		typedef T ValueType;
	private:
		typedef mwTVector <N,ValueType> Myself;
	public:
//#############################################################################		
		// construction
		mwTVector ();		
		mwTVector (const Myself& src);
//#############################################################################		
		// assignment
		const Myself& operator= (const Myself& src);
//#############################################################################		
		// comparison
		const bool operator== (const Myself& src) const;
		const bool operator!= (const Myself& src) const;
		const bool operator<  (const Myself& src) const;
		const bool operator<= (const Myself& src) const;
		const bool operator>  (const Myself& src) const;
		const bool operator>= (const Myself& src) const;
//#############################################################################		
		// arithmetic operations
		const Myself operator+ (const Myself& src) const;
		const Myself operator- (const Myself& src) const;
		const Myself operator* (const ValueType& fScalar) const;
		const Myself operator/ (const ValueType& fScalar) const;
		const Myself operator- () const;
//#############################################################################		
		// arithmetic updates
		const Myself& operator+= (const Myself& src);
		const Myself& operator-= (const Myself& src);
		const Myself& operator*= (const ValueType& fScalar);
		const Myself& operator/= (const ValueType& fScalar);
//#############################################################################		
		const T operator~() const;
		// Myself operations
		const ValueType Length () const;
		const ValueType SquaredLength () const;
		const ValueType Dot (const Myself& src) const;
		const Myself GetUnit () const;
		const Myself& Normalize();
//#############################################################################		
		//getter
		const ValueType& operator[] (int i) const;
//#############################################################################
		//setter
		ValueType& operator[] (int i);
	protected:
		// support for comparisons
		int CompareArrays (const Myself& src) const;
//#############################################################################
		//support for normalize
		void Normalize(Myself& toNorm) const;
//#############################################################################
		ValueType mArray[N];
		
	};

template <int N, class T>
	const mwTVector<N,T> operator* (const T& fScalar, const mwTVector<N,T>& src);

}
#endif	//	MW_MWTVECTOR_HPP_
