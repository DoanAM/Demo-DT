// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedVisitorBinInput class

//#############################################################################

#ifndef MW_MWPOSTEDVISITORBININPUT_HPP_
#define MW_MWPOSTEDVISITORBININPUT_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwBIPostTypes;
	//#############################################################################
	class MW_5AXUTIL_API mwPostedVisitorBinInput : public mwPostedVisitor
	{
	public:
		//#############################################################################
		mwPostedVisitorBinInput(
			mwBIPostTypes& bIPostTypes,
			mwPostedMovePtr& postedMove);
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
		mwPostedVisitorBinInput& operator=(const mwPostedVisitorBinInput&) { return *this; }// avoid warning c4512
		//#############################################################################
		mwBIPostTypes& m_bIPostTypes;
		mwPostedMovePtr& m_postedMove;
		//#############################################################################
	};	
};
//#############################################################################
#endif	//	MW_MWPOSTEDVISITORBININPUT_HPP_
