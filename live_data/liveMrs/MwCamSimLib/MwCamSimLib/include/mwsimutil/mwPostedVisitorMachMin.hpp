// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPotedVisitorMachMin class

//#############################################################################

#ifndef MW_MWPOSTEDVISITORMACHMIN_HPP_
#define MW_MWPOSTEDVISITORMACHMIN_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostedVisitorMachMin : public mwPostedVisitor
	{
	public:
		mwPostedVisitorMachMin(std::vector<double>& maxVals);
		//#############################################################################
		//! visits a mwPostedMove
		/*!
			\param mw the move to be visited
		*/
		void Visit( const mwPostedMove &mw ) const;
		//#############################################################################
		//! visits a mwPosted3axMove
		/*!
			\param mw the move to be visited
		*/
		void Visit( const mwPosted3axMove &mw ) const;
		//#############################################################################
		//! visits a mwPosted4axMove
		/*!
			\param mw the move to be visited
		*/
		void Visit( const mwPosted4axMove &mw ) const;
		//#############################################################################
		//! visits a mwPosted5axMove
		/*!
			\param mw the move to be visited
		*/
		void Visit( const mwPosted5axMove &mw ) const;
		//#############################################################################
		//! visits a mwPosted6axMove
		/*!
			\param mw the move to be visited
		*/
		void Visit( const mwPosted6axMove &mw ) const; 
		//#############################################################################
		//! visits a mwPostedNaxMove
		/*!
			\param mw the move to be visited
		*/
		void Visit(const mwPostedNaxMove &mw) const;
		//#############################################################################
	private:
		//#############################################################################
		mwPostedVisitorMachMin& operator=(const mwPostedVisitorMachMin&) { return *this; }		// avoid warning c4512
		//#############################################################################
		std::vector<double>& m_minVals;
		//#############################################################################
	};	
};
//#############################################################################
#endif	//	MW_MWPOSTEDVISITORMACHMIN_HPP_
