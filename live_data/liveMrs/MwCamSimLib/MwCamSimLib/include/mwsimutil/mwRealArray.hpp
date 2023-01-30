// (C) 2003-2016 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWREALARRAY_HPP_
#define MW_MWREALARRAY_HPP_
#include "mwIdxRangeException.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwAvoid_Warnings.hpp"

namespace misc
{
	//!This class represents a real array.
	template < class T > class MW_5AXUTIL_API mwRealArray
	{
	public:
		typedef	size_t				mw_size_t;

		//!Default constructor
		inline mwRealArray()
		:	mData( MW_NULL ),
			mDataSize( 0 )
		{
		};

		//!Constructor
		/*!Constructs a real array using the
		   parameters given:
		   \param length of the real array
		*/
		explicit inline mwRealArray( const mw_size_t &length )
		:	mData( new T[length] ),
			mDataSize( length )
		{
		};
		
		//!Copy constructor
		/*!Creates an exact copy of a given tool 
		   \param tc tool to create a copy of
		*/
		inline mwRealArray( const mwRealArray &tc )
		{
			mData = new T[tc.mDataSize];
			mDataSize = tc.mDataSize;

			memcpy( mData, tc.mData, sizeof( T )*tc.mDataSize );
		};

		//!Destructor
		inline ~mwRealArray()
		{
			if( mData )
				delete [] mData;
		};

		//!Resize the real array
		/*!Resize the real array with a given parameter.
			\param newLength new legth of the real array
		*/
		inline void Resize( const mw_size_t &newLength )
		{
			if( mData )
				delete [] mData;

			mData = new T[newLength];
			mDataSize = newLength;
		};

		//!Assigment operator
		/*!Assigns one object to another
		  \param tc to copy the information from
		*/
		inline void operator=( const mwRealArray &tc )
		{
			if( mData )
				delete [] mData;

			mData = new T[tc.mDataSize];
			mDataSize = tc.mDataSize;

			memcpy( mData, tc.mData, sizeof( T )*tc.mDataSize );
		};

		//!Indexer operator for const values
		/*!
			\param index position of an element
			\returns const reference to that element
		*/
		inline const T &operator[]( const mw_size_t &index ) const
		{
			if( index >= mDataSize )
				throw mwIdxRangeException< mw_size_t >( mDataSize - 1, index );

			return mData[index];
		};

		//!Indexer operator for non-const values
		/*!
			\param index position of an element
			\returns reference to that element
		*/
		inline T &operator[]( const mw_size_t &index )
		{
			if( index >= mDataSize )
				throw mwIdxRangeException< mw_size_t >( mDataSize - 1, index );

			return mData[index];
		};
		
		//!Get real array
		/*!Get real array pointer.
			\returns pointer to the array
		*/
		inline T *getArray()
		{
			return mData;
		};

		//! UNSAFE Assignment  ATTENTION: this class will delete the data when it's lifetime end
		/*!Assigns one object to another
		  \param data to copy the information from
		  \param newLength new length of data
		*/
		inline void UnsafeAssign( T* data, const mw_size_t &newLength )
		{
			if( mData )
				delete [] mData;
			mData = data;
			mDataSize = newLength;
		};

		//!Get real array
		/*!Get real array pointer.
			\returns const pointer to the array
		*/
		inline const T *getArray() const
		{
			return mData;
		};

		//!Get number of elements in the real array
		/*!Get number of elements in the real array
			\returns number of elements in the real array.
		*/
		inline const mw_size_t &GetNumberOfElements() const
		{
			return mDataSize;
		};

	protected:
	private:
		T				*mData;
		mw_size_t		mDataSize;
	};
}
#endif	//	MW_MWREALARRAY_HPP_
