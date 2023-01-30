// (C) 2010-2018 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWTINTERVAL_HPP_
#define MW_MWTINTERVAL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwException.hpp"
#include "mwMathConstants.hpp"

namespace mathdef
{

	class mwTIntervalPublicIntf
	{
	public:
		enum CompareResult { equal, greater_separate, greater_intersecting, smaller_separate, smaller_intersecting, subset, mainset };
	};

	template< typename U >
	class MW_5AXUTIL_API mwTInterval
	{
	public:
		typedef U										MyType;

		//#############################################################################
		mwTInterval( const U& start, const U& end )
		{
			if( is_gt(start, end) )
			{
				m_start = end;
				m_end = start;
			}
			else
			{
				m_start = start;
				m_end = end;
			}
		}

		//#############################################################################
		mwTInterval( const mwTInterval& toCopy )
		{
			Copy( toCopy );
		}

		//#############################################################################
		~mwTInterval()
		{
		}

		//#############################################################################
		const mwTInterval& operator =(const mwTInterval &toCopy)
		{
			if(&toCopy == this)
				return *this;

			Copy(toCopy);

			return *this;
		}

		//#############################################################################
		bool operator==( const mwTInterval &toCompare ) const
		{
			if( &toCompare == this )
				return true;

			return mathdef::is_eq( m_start, toCompare.m_start ) && mathdef::is_eq( m_end, toCompare.m_end );
		}	

		//#############################################################################
		//operators cannot be overridden so we need to call an overridable method
		bool operator<(const mwTInterval& other) const 
		{
			return ( m_start < other.m_start ) && IsReallyLessThan(); 
		}

		//#############################################################################
		virtual bool IsReallyLessThan()
		{
			return true;
		}

		//#############################################################################
		virtual void SetStart( const U& start )
		{
			if( is_lte(start, m_end) )
			{
				m_start = start;
			}
			else
			{
				m_start = m_end;
				m_end = start;
			}
		}

		//#############################################################################
		virtual void SetEnd( const U& end )
		{
			if( is_gt(end, m_start) )
			{
				m_end = end;
			}
			else
			{
				m_end = m_start;
				m_start = end;
			}
		}

		//#############################################################################
		virtual const U& GetStart() const
		{
			return m_start;
		}

		//#############################################################################
		virtual const U& GetEnd() const
		{
			return m_end;
		}

		//#############################################################################
		virtual mwTIntervalPublicIntf::CompareResult CompareWith( const mwTInterval &comp ) const
		{
			if ( mathdef::is_lt(m_start , comp.m_start) &&
				 mathdef::is_lt(m_end , comp.m_start) )
			{
				// this is smaller and separate than comp
				return mwTIntervalPublicIntf::smaller_separate;
			}

			if ( mathdef::is_gt(m_start , comp.m_end) && 
				 mathdef::is_gt(m_end , comp.m_end) )
			{
				// this is greater and separate than comp
				return mwTIntervalPublicIntf::greater_separate;
			}

			if ( mathdef::is_lt(m_start , comp.m_start) && 
				mathdef::is_gte(m_end , comp.m_start) &&
				mathdef::is_lte(m_end , comp.m_end) )
			{
				// this is intersecting with comp and smaller
				return mwTIntervalPublicIntf::smaller_intersecting;
			}

			if ( mathdef::is_gt(m_end , comp.m_end) && 
				mathdef::is_lte(m_start , comp.m_end) &&
				mathdef::is_gte(m_start , comp.m_start) )
			{
				// this is intersecting with comp and greater
				return mwTIntervalPublicIntf::greater_intersecting;
			}

			if ( (*this) == comp )
			{
				// this is equal to comp
				return mwTIntervalPublicIntf::equal;
			}

			if ( mathdef::is_gte(m_start , comp.m_start) &&
				 mathdef::is_lte(m_end , comp.m_end) )
			{
				// this is subset of comp
				return mwTIntervalPublicIntf::subset;
			}

			if ( mathdef::is_lte(m_start , comp.m_start) && 
				 mathdef::is_gte(m_end , comp.m_end) )
			{
				// comp is subset of this
				return mwTIntervalPublicIntf::mainset;
			}

			// exception
 			throw misc::mwException( 0, _T("Interval compare failed") );
		}

		void Merge( const mwTInterval &mergeitem )
		{
			if( is_lt(mergeitem.m_start, m_start) )
				m_start = mergeitem.m_start;

			if( is_gt(mergeitem.m_end, m_end) )
				m_end = mergeitem.m_end;
		}

	private:
		//#############################################################################
		void Copy( const mwTInterval &toCopy )
		{
			m_start = toCopy.m_start;
			m_end = toCopy.m_end;
		}

		U		m_start;
		U		m_end;
	};

	//#############################################################################
	template < typename U >
	class mwTIntervalFunctor
	{
		public:
		bool operator( )(misc::mwAutoPointer< mwTInterval< U > > obj1, 
			misc::mwAutoPointer< mwTInterval< U > > obj2) const
		{
			return( (*obj1) < (*obj2) );
		}
	};

};
#endif	//	MW_MWTINTERVAL_HPP_
