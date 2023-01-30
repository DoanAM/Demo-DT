// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWITERATORCONVERTOR_HPP_
#define MW_MWITERATORCONVERTOR_HPP_

#include <list>
#include <mwAutoPointer.hpp>
#include <mwException.hpp>
#include "mwDeprecated.hpp"

namespace misc
{

template < typename T1, typename T2 > class mwIteratorConvertor;
template < typename T1, typename T2 > class mwConstIteratorConvertor;

//!mwConstIteratorConvertor class
/*!This class represents a mwConstIteratorConvertor*/
template < typename T1, typename T2 >
class MW_DEPRECATED("Deprecated since 2020.12. Do not use it.") mwConstIteratorConvertor
{
public:
	/*! \var typedef typename mwAutoPointer< T1 > Ptr1
		\brief A type redefinition for
			typename mwAutoPointer< T1 >				as Ptr1
	*/
	typedef mwAutoPointer< T1 > Ptr1;

	/*! \var typedef typename mwAutoPointer< T2 > Ptr2
		\brief A type redefinition for
			typename mwAutoPointer< T2 >				as Ptr2
	*/
	typedef mwAutoPointer< T2 > Ptr2;
    
	/*! \var typedef typename std::list< Ptr1 >::const_iterator Iter
		\brief A type redefinition for
			typename std::list< Ptr1 >::const_iterator				as Iter
	*/
	typedef typename std::list< Ptr1 >::const_iterator Iter;
	
	typedef typename std::list< Ptr2 >::iterator::iterator_category iterator_category;
	typedef typename std::list< Ptr2 >::iterator::value_type value_type;
	typedef typename std::list< Ptr2 >::iterator::difference_type difference_type;
	typedef typename std::list< Ptr2 >::pointer pointer;
	typedef typename std::list< Ptr2 >::reference reference;

	mwConstIteratorConvertor ( ) { };
	mwConstIteratorConvertor ( Iter iter ) : _iter( iter ) { }
	mwConstIteratorConvertor ( const mwConstIteratorConvertor<T1,T2> & iter ) : _iter( iter._iter ) { }

	//! operator*
	/*!
		\returns operator* of type Ptr2
	*/
	Ptr2 operator *() const
	{
		Ptr2 result;
		return result.UnsafeAssign( *_iter );
	}

	//! operator=
	/*!
		\param it of type const mwConstIteratorConvertor<T1,T2> &
		\returns operator= of type mwConstIteratorConvertor<T1,T2>
	*/
	mwConstIteratorConvertor<T1,T2> & operator = ( const mwConstIteratorConvertor<T1,T2> & it )
	{
		_iter = it._iter;
		return *this;
	}

	//! operator=
	/*!
		\param it of type const Iter &
		\returns operator= of type mwConstIteratorConvertor<T1,T2>
	*/
	mwConstIteratorConvertor<T1,T2> & operator = ( const Iter & it )
	{
		_iter = it;
		return *this;
	}

	//! Prefix operator++
	/*!
		\returns operator++ of type mwConstIteratorConvertor<T1,T2> reference
	*/
	mwConstIteratorConvertor<T1,T2> & operator ++ ()
	{
		_iter++;
		return *this;
	}

	//! Postfix operator ++
	/*!
		\returns operator ++ of type mwConstIteratorConvertor<T1,T2>
	*/
	mwConstIteratorConvertor<T1,T2> operator ++ ( int )
	{
		mwConstIteratorConvertor<T1,T2> returnValue( *this );
		_iter++;
		return returnValue;
	}

	//! Prefix operator --
	/*!
		\returns operator -- of type mwConstIteratorConvertor<T1,T2> reference
	*/
	mwConstIteratorConvertor<T1,T2> & operator -- ()
	{
		_iter--;
		return *this;
	}

	//! Postfix operator --
	/*!
		\returns operator -- of type mwConstIteratorConvertor<T1,T2>
	*/
	mwConstIteratorConvertor<T1,T2> operator -- ( int )
	{
		mwConstIteratorConvertor<T1,T2> returnValue( *this );
		_iter--;
		return returnValue;
	}

	//! operator ==
	/*!
		\param iter of type mwConstIteratorConvertor<T1,T2> &
		\returns operator == of type bool
	*/
	bool operator == ( const mwConstIteratorConvertor<T1,T2> & iter ) const
	{
		return _iter == iter._iter;
	}

	//! operator !=
	/*!
		\param iter of type mwConstIteratorConvertor<T1,T2> &
		\returns operator != of type bool
	*/
	bool operator != ( const mwConstIteratorConvertor<T1,T2> & iter ) const
	{
		return !( *this == iter );
	}

	//! operator ==
	/*!
		\param iter of type Iter &
		\returns operator == of type bool
	*/
	bool operator == ( const Iter & iter ) const
	{
		return _iter == iter;
	}

	//! operator !=
	/*!
		\param iter of type Iter &
		\returns operator != of type bool
	*/
	bool operator != ( const Iter & iter ) const
	{
		return !( *this == iter );
	}

	//! GetStdIterator
	/*!
		\returns GetStdIterator of type Iter&
	*/
	Iter& GetStdIterator()
	{
		return this->_iter;
	}

	//! GetStdIterator
	/*!
		\returns GetStdIterator of type const Iter&
	*/
	const Iter& GetStdIterator() const
	{
		return this->_iter;
	}

protected :
	Iter _iter;
};

/**
 * This template using for convertion one iterator
 * of std::list< mwAutoPointer< T1 > > , to iterator
 * std::list< mwAutoPointer< T2 > >.
 */
template < typename T1, typename T2 >
class MW_DEPRECATED("Deprecated since 2020.12. Do not use it.") mwIteratorConvertor : public mwConstIteratorConvertor<T1,T2>
{
public:
	/*! \var typedef typename std::list< Ptr1 >::iterator Iter
		\brief A type redefinition for
			typename std::list< Ptr1 >::iterator				as Iter
	*/
	typedef typename mwConstIteratorConvertor<T1,T2>::Ptr1	Ptr1;
	typedef typename mwConstIteratorConvertor<T1,T2>::Ptr2	Ptr2;
	typedef typename std::list< Ptr1 >::iterator Iter;
	
	mwIteratorConvertor () {};
	mwIteratorConvertor ( Iter iter ) : mwConstIteratorConvertor<T1,T2>(iter) { }

	//! operator*
	/*!
		\returns operator* of type Ptr2
	*/
	Ptr2 operator*()
	{
		Ptr2 result;
		return result.UnsafeAssign( *this->_iter );
	}

	//! operator=
	/*!
		\param it of type const mwIteratorConvertor<T1,T2> &
		\returns operator= of type mwIteratorConvertor<T1,T2>
	*/
	mwIteratorConvertor<T1,T2> & operator= ( const mwIteratorConvertor<T1,T2> & it )
	{
		this->_iter = it._iter;
		return *this;
	}

	//! operator=
	/*!
		\param it of type const Iter &
		\returns operator= of type mwIteratorConvertor<T1,T2>
	*/
	mwIteratorConvertor<T1,T2> & operator= ( const Iter & it )
	{
		this->_iter = it;
		return *this;
	}

	//! Prefix operator++
	/*!
		\returns operator++ of type mwIteratorConvertor<T1,T2> reference
	*/
	mwIteratorConvertor<T1,T2> & operator++ ()
	{
		this->_iter++;
		return *this;
	}

	//! Postfix operator ++
	/*!
		\returns operator ++ of type mwIteratorConvertor<T1,T2>
	*/
	mwIteratorConvertor<T1,T2> operator++ ( int )
	{
		mwIteratorConvertor<T1,T2> returnValue( *this );
		this->_iter++;
		return returnValue;
	}

	//! Prefix operator --
	/*!
		\returns operator -- of type mwIteratorConvertor<T1,T2> reference
	*/
	mwIteratorConvertor<T1,T2> & operator-- ()
	{
		this->_iter--;
		return *this;
	}

	//! Postfix operator --
	/*!
		\returns operator -- of type mwIteratorConvertor<T1,T2>
	*/
	mwIteratorConvertor<T1,T2> operator-- ( int )
	{
		mwIteratorConvertor<T1,T2> returnValue( *this );
		this->_iter--;
		return returnValue;
	}

	//! operator ==
	/*!
		\param iter of type mwIteratorConvertor<T1,T2> &
		\returns operator == of type bool
	*/
	bool operator== ( mwIteratorConvertor<T1,T2> & iter ) const
	{
		return this->_iter == iter._iter;
	}

	//! operator !=
	/*!
		\param iter of type mwIteratorConvertor<T1,T2> &
		\returns operator != of type bool
	*/
	bool operator!= ( mwIteratorConvertor<T1,T2> & iter ) const
	{
		return !( *this == iter );
	}

	//! operator ==
	/*!
		\param iter of type Iter &
		\returns operator == of type bool
	*/
	bool operator== ( Iter & iter ) const
	{
		return this->_iter == iter;
	}

	//! operator !=
	/*!
		\param iter of type Iter &
		\returns operator != of type bool
	*/
	bool operator!= ( Iter & iter ) const
	{
		return !( *this == this->iter );
	}
};

}; // namespace misc
#endif	//	MW_MWITERATORCONVERTOR_HPP_
