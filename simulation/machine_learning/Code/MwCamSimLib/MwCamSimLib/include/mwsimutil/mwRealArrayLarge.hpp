// (C) 2006-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWREALARRAYLARGE_HPP_
#define MW_MWREALARRAYLARGE_HPP_
#include <vector>
#include <memory>
#include "mwException.hpp"
#include "mwIdxRangeException.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwBasicTypes.hpp"

//#define OLD_ART_USAGE
//currently Ionut and Nini have switched allocator to plain NEW in order
//to enforce constructor/destructor calling
//prior to this, this class was holding plain floats, who didn't need ctor
//now it's suitable for objects also, so we need ctor/dector calls

namespace misc
{
	template < class T > class mwRealArrayLargeUtils;

	
#ifdef OLD_ART_USAGE
	static const ::misc::uint64_t MW_REAL_ARRAY_LARGE_BLOCK_SIZE = 1048576;
#else
	static const ::misc::uint64_t MW_REAL_ARRAY_LARGE_BLOCK_SIZE = 2097152;//1048576 was for allocator of real bytes
#endif

	
#ifdef OLD_ART_USAGE
	template< class T , class lAlloc = std::allocator<T> >
#else
	template< class T >
#endif
	class MW_5AXUTIL_API mwRealArrayLarge
	{
	public:
		typedef T*						mw_tPtr;
		typedef ::misc::uint64_t		mw_size_t;
		typedef std::vector< mw_tPtr >	mw_tPtrVec;
#ifdef OLD_ART_USAGE
		
		//!Default constructor
		/*! Has only optional parameters
			\param lAl allocator's constructor call, default with no parameters
			\param bLastBlockIsSmall bool value indicating if last block is chopped
				(to minimize memory usage). defaults to true
		*/
		mwRealArrayLarge( const lAlloc& lAl = lAlloc(),
			const bool &bLastBlockIsSmall = true )
		:	m_dataSize( 0 ),
			m_allocator( lAl ),
			m_blockSize( MW_REAL_ARRAY_LARGE_BLOCK_SIZE / sizeof( T ) ),
			m_bLastBlockIsSmall( bLastBlockIsSmall )
		{
		}
#endif
		//Nini: I had to reverse the order of two parameters in the signature
		//of these two constructors, or else "ambiguous call to overloaded function ::_ctor" error gets raised

		
		//!Constructor
		/*!Constructs a real array large using the
		   parameters given:
			\param length of the real array
			\param bLastBlockIsSmall bool value indicating if last block is chopped
				(to minimize memory usage). defaults to true
		*/
		explicit inline mwRealArrayLarge( const mw_size_t &length,
			const bool &bLastBlockIsSmall = true
#ifdef OLD_ART_USAGE
				,const lAlloc& lAl = lAlloc()
#endif
				)
		:	m_dataSize( 0 ),
#ifdef OLD_ART_USAGE
			m_allocator( lAl ),
#endif
			m_blockSize( MW_REAL_ARRAY_LARGE_BLOCK_SIZE / sizeof( T ) ),
			m_bLastBlockIsSmall( bLastBlockIsSmall )
		{
			Allocate( length );
		}

		
		//!Destructor
		~mwRealArrayLarge()
		{
			FreeUp();
		}

		
		//!Copy constructor
		/*!Creates an exact copy of a given real array large
			\param tc array to create a copy of
		*/
		inline mwRealArrayLarge( const mwRealArrayLarge &tc )
		:	m_dataSize( 0 ),
			m_blockSize( tc.m_blockSize )
		{
			Copy( tc );
		};

		
		//! Assignment operator
		/*! 
			\param tc array to create a copy of
		*/
		virtual const mwRealArrayLarge& operator=( const mwRealArrayLarge &tc )
		{
			FreeUp();
			Copy( tc );
			return *this;
		}


		
		//!Resize the real array large
		/*!Resize the real array large by a new given size
			\param newLength new length of the real array large
			\param bKeepData optional boolean value indicates if data should be kept. default false
		*/
		inline void Resize( const mw_size_t &newLength, const bool &bKeepData = false )
		{
			if( !bKeepData )
			{
				FreeUp();
				Allocate( newLength );
				return;
			}

			if( newLength == m_dataSize )
				return;//nothing to be done... phew...

#ifdef _DEBUG
			if( newLength < m_dataSize )
			{
				//shrinking...
				throw misc::mwException( 0, _T("Resize with keep Data on and shrinking? Puah... do it yourself") );
				return;
			}
#endif
			//growing...
			const mw_size_t oldDataSize = m_dataSize;
			const mw_size_t oldiCount = oldDataSize / m_blockSize;
			const mw_size_t newiCount = newLength / m_blockSize;
			const mw_size_t diffiCount = newiCount - oldiCount;
			mw_tPtr savedLastBlockPtr = m_data[ static_cast< typename mw_tPtrVec::size_type>( oldiCount ) ];
#ifdef OLD_ART_USAGE
			const mw_size_t lastBlockAllocatedSize = GetAllocatedSizeByIndex( oldiCount );
#endif
			const mw_size_t lastBlockUsedSize = GetUsedSizeByIndex( oldiCount );
			try
			{
				m_dataSize = newLength;
				if( m_bLastBlockIsSmall )
				{
					m_data[ static_cast< typename mw_tPtrVec::size_type>( oldiCount ) ] =
#ifdef OLD_ART_USAGE
						m_allocator.allocate
							(
								static_cast< lAlloc::size_type >( GetAllocatedSizeByIndex( oldiCount ) ), (void *)0
							);
#else
						new T[static_cast<unsigned int>(GetAllocatedSizeByIndex( oldiCount ))];
#endif
				}
				else
				{
					//nothing to do, memory is already allocated, just don't delete it...
				}
				if( diffiCount > 0 )
				{
					m_data.reserve( static_cast< typename mw_tPtrVec::size_type>( newiCount + 1 ) );
					for( mw_size_t i = oldiCount + 1; i <= newiCount; ++i )
						m_data.push_back
						(
#ifdef OLD_ART_USAGE
							m_allocator.allocate
							(
								static_cast<typename lAlloc::size_type >( GetAllocatedSizeByIndex( i ) ), (void *)0
							)
#else
							new T[static_cast<unsigned int>(GetAllocatedSizeByIndex( i ))]
#endif
						);

				}
			}
			catch( ... )
			{
				FreeUp();
				//ok, deallocated stuff, now throw... up
				throw;
			}

			if( m_bLastBlockIsSmall )
			{
				memcpy( m_data[ static_cast<typename mw_tPtrVec::size_type>( oldiCount ) ], savedLastBlockPtr,
					static_cast< size_t >( sizeof(T) * lastBlockUsedSize ) );
#ifdef OLD_ART_USAGE
				m_allocator.deallocate( savedLastBlockPtr,
					static_cast<typename lAlloc::size_type >( lastBlockAllocatedSize ) );
#else
				delete [] savedLastBlockPtr;
#endif
				savedLastBlockPtr = MW_NULL;
			}
		};


		
		//!Indexer operator for const values
		/*!Returns, for a given index, a reference to a pointer of a real array.
			If number of index out of range an exception will be thrown
			\param index position in a real array
			\returns const reference to a pointer of a real array.
		*/
		inline const T &operator[]( const mw_size_t index ) const
		{
#ifdef _DEBUG
			if( index >= m_dataSize )
				throw mwIdxRangeException< mw_size_t >( m_dataSize - 1, index );
#endif
			return *( m_data[ static_cast<typename mw_tPtrVec::size_type>( index / m_blockSize ) ] + index % m_blockSize );
		};

		
		//!Indexer operator for non-const values
		/*!Returns, for a given index, a reference to a pointer of a real array.
			If number of index > real array length an exception will be thrown
			\param index position in a real array
			\returns reference to a pointer of a real array.
		*/
		inline T &operator[]( const mw_size_t index )
		{
#ifdef _DEBUG
			if( index >= m_dataSize )
				throw mwIdxRangeException< mw_size_t >( m_dataSize - 1, index );
#endif
			return *( m_data[ static_cast<typename mw_tPtrVec::size_type>( index / m_blockSize ) ] + index % m_blockSize );
		};


		
		//!size
		/*! Returns number of elements stored in the array
			\returns number of elements stored in the real array large
		*/
		inline const mw_size_t size() const
		{
			return m_dataSize;
		}

	private:
#pragma warning(push)
#pragma warning(disable : 4251)

		
		void FreeUp()
		{
			//const mw_size_t iCount = m_dataSize / m_blockSize;
			typename mw_tPtrVec::reverse_iterator it( m_data.rbegin() );
			typename mw_tPtrVec::reverse_iterator ite( m_data.rend() );
			for( mw_size_t i = 0; it != ite; ++i, ++it )
			{
#ifdef OLD_ART_USAGE
				m_allocator.deallocate( *it, static_cast<typename lAlloc::size_type >( GetAllocatedSizeByIndex( i ) ) );
#else
				delete [] *it;
#endif
				*it = MW_NULL;
			}
			m_data.clear();
			m_dataSize = 0;
		}

		
		void Allocate( const mw_size_t &length )
		{
#ifdef _DEBUG
			if( m_dataSize != 0 )
				throw misc::mwException( 0, _T("Already allocated memory...") );
#endif
			m_dataSize = length;
			if( m_dataSize == 0 )
				return;
			try
			{
				const mw_size_t iCount = length / m_blockSize;
				m_data.reserve( static_cast<typename mw_tPtrVec::size_type>( iCount + 1 ) );
				for( mw_size_t i = 0; i <= iCount; ++i )
					m_data.push_back
					(
#ifdef OLD_ART_USAGE	
						m_allocator.allocate
							(
								static_cast<typename lAlloc::size_type >( GetAllocatedSizeByIndex( i ) ), (void *)0
							)
#else
						new T[ static_cast< unsigned int > ( GetAllocatedSizeByIndex( i ) ) ]
#endif
					);
			}
			catch( ... )
			{
				//failure in one allocation oops
				//so we need to deallocate successful allocations...

				FreeUp();

				//ok, deallocated stuff, now throw... up
				throw;
			}
		}

		
		const inline mw_size_t GetAllocatedSizeByIndexInternal( const mw_size_t &index,
			const bool &bUsageDecision )
		{
			const mw_size_t iCount = m_dataSize / m_blockSize;
#ifdef _DEBUG
			if( index > iCount )
				throw misc::mwException( 0, _T("Out of bounds") );
#endif
			if( !bUsageDecision || index < iCount )
				return m_blockSize;
			return m_dataSize % m_blockSize;
		}

		
		const inline mw_size_t GetAllocatedSizeByIndex( const mw_size_t &index )
		{
			return GetAllocatedSizeByIndexInternal( index, m_bLastBlockIsSmall );
		}

		
		const mw_size_t GetUsedSizeByIndex( const mw_size_t &index )
		{
			return GetAllocatedSizeByIndexInternal( index, true );
		}

		
		//! Internal helper function
		/*!
			Used for copy constructor and assignment operator
			\param toCopy 'copy from' object
		*/
		virtual void Copy( const mwRealArrayLarge& toCopy )
		{
			m_bLastBlockIsSmall = toCopy.m_bLastBlockIsSmall;
#ifdef OLD_ART_USAGE
			m_allocator = toCopy.m_allocator;
#endif
			Allocate( toCopy.m_dataSize );
			for( typename mw_tPtrVec::size_type i = 0; i < toCopy.m_data.size(); ++i )
				memcpy( m_data[i], toCopy.m_data[i],
							static_cast< size_t >( sizeof(T) * GetUsedSizeByIndex( i ) ) );//efficient for last block if m_bLastBlockIsSmall is true!!!
																							//so last memcpy does not copy bogus data at the end of last block
																							//so it's faster
		}

		mw_tPtrVec					m_data;
		mw_size_t					m_dataSize;
#ifdef OLD_ART_USAGE
		lAlloc						m_allocator;
#endif
		const mw_size_t				m_blockSize;
		bool						m_bLastBlockIsSmall;

		friend class 	mwRealArrayLargeUtils<T>;
#pragma warning(pop)
	};
};
#endif	//	MW_MWREALARRAYLARGE_HPP_
