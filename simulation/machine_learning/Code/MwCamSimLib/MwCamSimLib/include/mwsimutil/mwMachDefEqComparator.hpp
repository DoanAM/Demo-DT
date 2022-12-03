// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWMACHDEFEQCOMPARATOR_HPP_
#define MW_MWMACHDEFEQCOMPARATOR_HPP_
//#############################################################################
#include "mwMachDef.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwPostException.hpp"
#include "mwMachDefUtils.hpp"
//#############################################################################
namespace post
{
	class MW_5AXUTIL_API mwMachDefEqComparator 
		
	{
	public:
		
		static const bool Compare(const mwMachDefPtr& machDef1, const mwMachDefPtr &machDef2);

		class mwMachDefComparatorVisitor : public mwMachineVisitor
		{
		public:
			mwMachDefComparatorVisitor(const mwMachDefPtr &machDef)
				: m_machDef(machDef)
				, m_equal(false)
			{
			}
			//#############################################################################
			~mwMachDefComparatorVisitor()
			{
			}
			//#############################################################################
			//! visits a mwMachDef
			/*!
				\param mw the move to be visited
			*/
			void Visit( const mwMachDef &/*mw*/ ) const
			{
				throw mwPostException(mwPostException::ABSTARCT_FUNCTION_CALLED);
			}
			//#############################################################################
			//! visits a mw3axMachDef
			/*!
				\param mw the move to be visited
			*/
			void Visit( const mw3axMachDef &mw ) const
			{
				if(m_machDef->GetNumberOfAxes() != mwMachDef::MACHINE_3AXIS)
					m_equal = false;
				else
					m_equal = mwMachDefUtils::SafeCast3ax(*m_machDef) == mw;
			}
			//#############################################################################
			//! visits a mw4axMachDef
			/*!
				\param mw the move to be visited
			*/
			void Visit( const mw4axMachDef &mw ) const
			{
				if(m_machDef->GetNumberOfAxes() != mwMachDef::MACHINE_4AXIS)
					m_equal = false;
				else
					m_equal = mwMachDefUtils::SafeCast4ax(*m_machDef) == mw;
			}
			//#############################################################################
			//! visits a mw5axMachDef
			/*!
				\param mw the move to be visited
			*/
			//#############################################################################
			void Visit( const mw5axMachDef &mw ) const
			{
				if(m_machDef->GetNumberOfAxes() != mwMachDef::MACHINE_5AXIS)
					m_equal = false;
				else
					m_equal = mwMachDefUtils::SafeCast5ax(*m_machDef) == mw;
			}
			//#############################################################################
			//! visits a mw6axMachDef
			/*!
				\param mw the move to be visited
			*/
			void Visit( const mw6axMachDef &mw ) const
			{
				if(m_machDef->GetNumberOfAxes() != mwMachDef::MACHINE_6AXIS)
					m_equal = false;
				else
					m_equal = mwMachDefUtils::SafeCast6ax(*m_machDef) == mw;
			}
			//#############################################################################
			//! visits a mw6axCSMachDef
			/*!
				\param mw the move to be visited
			*/
			void Visit( const mw6axCSMachDef &mw ) const
			{
				if(m_machDef->GetNumberOfAxes() != mwMachDef::MACHINE_6AXIS_CONTOUR)
					m_equal = false;
				else
					m_equal = mwMachDefUtils::SafeCast6axCS(*m_machDef) == mw;
			}
			//#############################################################################
			const bool Equal() const
			{
				return m_equal;
			}
			//#############################################################################
		private:

			mwMachDefComparatorVisitor& operator=(const mwMachDefComparatorVisitor&) { return *this; }// avoid warning c4512
			
			const mwMachDefPtr &m_machDef;
			mutable bool	    m_equal;
		};

	private:
		mwMachDefEqComparator(){};
	};
}
#endif	//	MW_MWMACHDEFEQCOMPARATOR_HPP_
