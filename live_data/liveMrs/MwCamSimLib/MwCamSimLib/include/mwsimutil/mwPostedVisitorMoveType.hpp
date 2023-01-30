// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedVisitorMoveType class

//#############################################################################

#ifndef MW_MWPOSTEDVISITORMOVETYPE_HPP_
#define MW_MWPOSTEDVISITORMOVETYPE_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwPostedVisitorMoveType : public mwPostedVisitor
	{
	public:
		//#############################################################################
		enum Types
		{
			_3AXIS = 0,
			_4AXIS = 1,
			_5AXIS = 2,
			_6AXIS = 3,
			_NAXIS = 4
		};
		mwPostedVisitorMoveType(Types& types);
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
		operator int() // conversion operator
		{ 
			return m_types; 
		}  
		//#############################################################################
		Types& m_types;
		//#############################################################################
	private:
		//#############################################################################
		mwPostedVisitorMoveType& operator = (const mwPostedVisitorMoveType&) { return *this; }// avoid warning c4512
		//#############################################################################
	};	
};
//#############################################################################
#endif	//	MW_MWPOSTEDVISITORMOVETYPE_HPP_
