// (C) 2003-2008 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWDISCRETEVALUE_HPP_
#define MW_MWDISCRETEVALUE_HPP_
#include <list>
#include "mwDiscreteValueException.hpp"
#include "mwValueValidator.hpp"

namespace misc
{
	template <class T> class mwDiscreteValue
	{
	public:
		
		typedef typename misc::mwAutoPointer< mwValueValidator<T> > valueValidator;
		
		mwDiscreteValue( )
			:m_value( 0 )
		{};

		//!Default constructor
		/*!
			Constructs a new object without any limitations 
		*/
		mwDiscreteValue( const T &value )
			:m_value( value )
		{};


		mwDiscreteValue( const T& value, const valueValidator& rValueValidator )
			: m_value ( value ),
			m_valueValidator( rValueValidator)
		{

		}

		//!Get value
		/*!
			\returns actual value
		*/
		const T &GetValue() const
		{
			return m_value;
		}
		
		//!Set value
		/*!
			Sets the value if the given value is acceptable
			throws an exception otherwise
		*/
		void SetValue( const T &toSet )
		{
			if ( m_valueValidator.IsNotNull() )
			{
				if( ! m_valueValidator->IsValid( toSet ) )
					throw mwDiscreteValueException<T>();
			}
			m_value = toSet;
		}

		void SetValueValidator( const valueValidator& toSet )
		{
			m_valueValidator = toSet;
		}

		const valueValidator& GetValueValidator() const
		{
			return m_valueValidator;
		}

	protected:
	private:
		
		T					m_value;
		valueValidator		m_valueValidator;
		
	};
};
#endif	//	MW_MWDISCRETEVALUE_HPP_
