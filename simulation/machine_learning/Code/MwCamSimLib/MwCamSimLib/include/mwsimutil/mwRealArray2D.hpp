// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWREALARRAY2D_HPP_
#define MW_MWREALARRAY2D_HPP_
#include "mwAvoid_Warnings.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwIdxRangeException.hpp"
#include <cstring>

namespace misc
{
//!This class represents a real array row.
template < class T > class MW_5AXUTIL_API mwRealArrayRow
{
public:
	//!Constructs a real array row using raw array and its length
	mwRealArrayRow(T* rowAddress, const size_t length)
	:	rowData( rowAddress ),
		rowLength( length )
	{
	}

	//! Subscript operator for const values	
	const T& operator[](const size_t& index) const
	{
		if( index >= rowLength )
			throw mwIdxRangeException<size_t>( rowLength - 1, index );

		return rowData[index];
	}

	//! Subscript operator for non-const values
	T& operator[](const size_t& index)
	{
		if( index >= rowLength )
			throw mwIdxRangeException<size_t>( rowLength - 1, index );

		return rowData[index];
	}

	//!Get real array
	T* getPtr()
	{
		return rowData;
	}

	//!Get real array
	const T* getPtr() const
	{
		return rowData;
	}

	//! Get length of a row
	size_t GetRowLength() const
	{
		return rowLength;
	}

private:
	mwRealArrayRow& operator=(mwRealArrayRow&);

	T* rowData;
	const size_t rowLength;
};

//!This class represents a 2d real array.
template < class T > class MW_5AXUTIL_API mwRealArray2D
{
public:
	typedef	size_t				mw_size_t;
		
	typedef mwRealArrayRow<T>	ra2dRow;
		
	//!Default constructor
	inline mwRealArray2D()
	:mData( MW_NULL ), mRows( 0 ), mColumns( 0 )
	{
	}

	//!Constructor
	/*!Constructs a 2d real array using the
		parameters given:
		\param rows of the 2d real array
		\param columns of the 2d real array
	*/
	inline mwRealArray2D( const mw_size_t &rows, const mw_size_t &columns )
	:mRows( rows ), mColumns( columns )
	{
		mData =new T[rows*columns];
	}

	//!Copy constructor
	/*!Creates a exact copy of a given tool 
		\param tc tool to create a copy of
	*/
	inline mwRealArray2D( const mwRealArray2D &tc )
		:mData( 0 )
	{
		mData = new T[tc.mRows*tc.mColumns];
		mRows = tc.mRows;
		mColumns = tc.mColumns;
		memcpy( mData, tc.mData, sizeof( T )*tc.mRows*tc.mColumns );
	}

	//!Destructor
	inline ~mwRealArray2D()
	{
		if( mData )
			delete [] mData;
	}

	//!Resize the 2d real array
	/*!Resize the 2d real array with a given parameter.
		\param newRows new number rows of the 2d real array
		\param newColumns new number columns of the 2d real array
	*/
	inline void Resize( const mw_size_t &newRows,
		const mw_size_t &newColumns )
	{
		if( mData )
			delete [] mData;

		mData = new T[newRows*newColumns];
		mRows = newRows;
		mColumns = newColumns;
	}

	//!Assignment operator
	/*!Assigns one object to another
		\param tc to copy the information from
	*/
	inline void operator=( const mwRealArray2D &tc )
	{
		if( mData )
			delete [] mData;

		mData = new T[tc.mRows*tc.mColumns];
		memcpy( mData, tc.mData, sizeof( T ) * tc.mRows * tc.mColumns );

		mRows = tc.mRows;
		mColumns = tc.mColumns;
	}

	//!Indexer operator for const values
	/*!Returns, for a given index, a const 2d real array row.
		If number of index out of range an exception will be thrown
		\param index row position in a 2d real array
		\returns a const 2d real array row.
	*/
	inline const ra2dRow operator[]( const mw_size_t &index ) const
	{
		if( index >= mRows )
			throw mwIdxRangeException< mw_size_t >( mRows - 1, index );
		return ra2dRow( mData + index * mColumns, mColumns );
	}

	//!Indexer operator for non-const values
	/*!Returns, for a given index, a 2d real array row.
		If number of index out of range an exception will be thrown
		\param index row position in a 2d real array
		\returns a 2d real array row.
	*/
	inline ra2dRow operator[]( const mw_size_t &index )
	{
		if( index >= mRows )
			throw mwIdxRangeException< mw_size_t >( mRows - 1, index );
		return ra2dRow( mData + index * mColumns, mColumns );
	}

	//!Get 2d real array
	/*!Get 2d real array pointer.
		\returns pointer to the array
	*/
	inline T* getPtr()
	{
		return mData;
	}

	//!Get 2d real array
	/*!Get 2d real array pointer.
		\returns const pointer to the array
	*/
	inline const T* getPtr() const
	{
		return mData;
	}

	//!Get number of rows in the 2d real array
	/*!Get number of rows in the 2d real array
		\returns number of rows in the 2d real array.
	*/
	inline const mw_size_t &GetNumberOfRows() const
	{
		return mRows;
	}

	//!Get number of columns in the 2d real array
	/*!Get number of columns in the 2d real array
		\returns number of columns in the 2d real array.
	*/
	const mw_size_t &GetNumberOfColumns() const
	{
		return mColumns;
	}

protected:
private:
	T				*mData;
	mw_size_t	mRows;
	mw_size_t	mColumns;
};

//!This class represents a real array row with templetized length.
template < class T, int length > class MW_5AXUTIL_API mwRealArrayRowl
{
public:
	typedef	size_t				mw_size_t;
	//!Default constructor
	/*!Constructs a real array row using the parameter given:
		\param rowAddress pointer of the real array row
	*/
	inline mwRealArrayRowl( T *rowAddress )
	:rowData( rowAddress )
	{
	}

	//!Indexer operator for const values
	/*!
		\param index position of an element in a real array row
		\returns reference to that element
	*/
	inline const T &operator[]( const mw_size_t &index ) const
	{
		return rowData[index];
	}

	//!Indexer operator for non-const values
	/*!
		\param index position of an element in a real array row
		\returns reference to that element
	*/
	inline T &operator[]( const mw_size_t &index )
	{
		return rowData[index];
	}

	//!Get real array
	/*!Get real array pointer.
		\returns pointer to the array
	*/
	inline T* getPtr()
	{
		return rowData;
	}

	//!Get real array
	/*!Get real array pointer.
		\returns const pointer to the array
	*/
	inline const T* getPtr() const
	{
		return rowData;
	}

	inline mw_size_t GetRowLength()const
	{
		return length;
	}

protected:
private:
	T* rowData;
};

//!This class represents a 2d real array with templetized number of rows and columns
template < class T, int rows, int columns > class MW_5AXUTIL_API mwRealArray2Drc
{
public:
	typedef	size_t				mw_size_t;
		
	typedef mwRealArrayRowl<T, columns>	ra2dRowl;
		
	//!Default constructor
	mwRealArray2Drc()
		: mData(new T[rows*columns])
	{
		memset(mData, 0, rows*columns*sizeof(T));
	}

	//!Copy constructor
	/*!Creates a exact copy of a given tool 
		\param tc tool to create a copy of
	*/
	mwRealArray2Drc( const mwRealArray2Drc &tc )
		:mData( new T[rows*columns] )
	{
		memcpy( mData, tc.mData, sizeof( T )*rows*columns );
	}

	//!Destructor
	~mwRealArray2Drc()
	{
		delete [] mData;
	}

	//!Resize the 2d real array
	/*!Resize the 2d real array with a given parameter.
		\param newRows new number rows of the 2d real array
		\param newColumns new number columns of the 2d real array
	*/
	void Resize()
	{
		delete [] mData;
		mData = new T[rows*columns];
	}

	//!Assignment operator
	/*!Assigns one object to another
		\param tc to copy the information from
	*/
	inline void operator=( const mwRealArray2Drc &tc )
	{
		if( mData )
			delete [] mData;

		mData = new T[rows*columns];
		memcpy( mData, tc.mData, sizeof( T )*rows*columns );
	}

	//!Indexer operator for const values
	/*!Returns, for a given index, a const 2d real array row.
		If number of index out of range an exception will be thrown
		\param index row position in a 2d real array
		\returns a const 2d real array row.
	*/
	inline const ra2dRowl operator[]( const mw_size_t &index ) const
	{
		return ra2dRowl( mData + index * columns );
	}

	//!Indexer operator for non-const values
	/*!Returns, for a given index, a 2d real array row.
		If number of index out of range an exception will be thrown
		\param index row position in a 2d real array
		\returns a 2d real array row.
	*/
	inline ra2dRowl operator[]( const mw_size_t &index )
	{
		return ra2dRowl( mData + index * columns );
	}

	//!Get 2d real array
	/*!Get 2d real array pointer.
		\returns pointer to the array
	*/
	inline T* getPtr()
	{
		return mData;
	}

	//!Get 2d real array
	/*!Get 2d real array pointer.
		\returns const pointer to the array
	*/
	inline const T* getPtr() const
	{
		return mData;
	}

	//!Get number of rows in the 2d real array
	/*!Get number of rows in the 2d real array
		\returns number of rows in the 2d real array.
	*/
	inline mw_size_t GetNumberOfRows() const
	{
		return rows;
	}

	//!Get number of columns in the 2d real array
	/*!Get number of columns in the 2d real array
		\returns number of columns in the 2d real array.
	*/
	inline mw_size_t GetNumberOfColumns() const
	{
		return columns;
	}

protected:
private:
	T*	mData;
};

}  // namespace misc
#endif	//	MW_MWREALARRAY2D_HPP_
