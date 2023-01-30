// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWVALUEVALIDATOR_HPP_
#define MW_MWVALUEVALIDATOR_HPP_

#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
	template < typename  T > class mwListBasedDiscreteValueValidator;
	template < typename  T > class mwSteppingBasedDiscreteValueValidator;
	template < typename T > class mwValueValidatorVisitor;

	template <class T> class MW_5AXUTIL_API mwValueValidator
	{
		public:
			//!Check if the value is allowed
			virtual const bool IsValid( const T &toCheck ) const = 0;
			//!This function is used in the visitor scheme
			void virtual AcceptVirtual( const mwValueValidatorVisitor<T>& virtualVisitor ) const = 0;
			virtual misc::mwAutoPointer<misc::mwValueValidator<T> > Clone() = 0 ;
			virtual ~mwValueValidator(){}
	};

	template < class T > class MW_5AXUTIL_API mwValueValidatorVisitor
	{
	public:
		//! Destructor
		virtual ~mwValueValidatorVisitor() {};

		//! Visit const mwTool
		virtual void Visit( const mwValueValidator<T>& visitor ) const = 0;             
		//! Visit const mwRevolvedTool
		virtual void Visit( const mwListBasedDiscreteValueValidator<T>& visitor ) const = 0;

		virtual void Visit( const mwSteppingBasedDiscreteValueValidator<T>& visitor ) const = 0;
	};
}; // misc namespace
#endif	//	MW_MWVALUEVALIDATOR_HPP_
