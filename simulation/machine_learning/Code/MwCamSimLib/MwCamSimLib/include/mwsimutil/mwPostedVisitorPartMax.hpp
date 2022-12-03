// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedVisitorPartMax class

//#############################################################################

#ifndef MW_MWPOSTEDVISITORPARTMAX_HPP_
#define MW_MWPOSTEDVISITORPARTMAX_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostedVisitorPartMax : public mwPostedVisitor
	{
	public:
		mwPostedVisitorPartMax(std::vector<double>& maxVals);
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
		//! visits a mwPosted6axMove
		/*!
			\param mw the move to be visited
		*/
		void Visit(const mwPostedNaxMove &mw) const;
		//#############################################################################
	private:
		//#############################################################################
		mwPostedVisitorPartMax& operator=(const mwPostedVisitorPartMax&) { return *this; }// avoid warning c4512
		//#############################################################################
		std::vector<double>& m_maxVals;
		//#############################################################################
	};	
};
//#############################################################################
#endif	//	MW_MWPOSTEDVISITORPARTMAX_HPP_
