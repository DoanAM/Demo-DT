// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedVisitorBinOutput class

//#############################################################################

#ifndef MW_MWPOSTEDVISITORBINOUTPUT_HPP_
#define MW_MWPOSTEDVISITORBINOUTPUT_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwBOPostTypes;
	//#############################################################################
	class MW_5AXUTIL_API mwPostedVisitorBinOutput : public mwPostedVisitor
	{
	public:
		//#############################################################################
		mwPostedVisitorBinOutput(mwBOPostTypes& bOPostTypes);
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
		mwPostedVisitorBinOutput& operator=(const mwPostedVisitorBinOutput&) { return *this; }// avoid warning c4512
		//#############################################################################
		mwBOPostTypes& m_bOPostTypes;
		//#############################################################################
	};	
};
//#############################################################################
#endif	//	MW_MWPOSTEDVISITORBINOUTPUT_HPP_
