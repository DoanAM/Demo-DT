// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted4axMove class

//#############################################################################

#ifndef MW_MWPOSTED4AXMOVE_HPP_
#define MW_MWPOSTED4AXMOVE_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a posted 4 axis move.
	class MW_5AXUTIL_API mwPosted4axMove : public mwPostedMove  
	{
	public:
		//#############################################################################
		//!Default constructor
		mwPosted4axMove(const bool shortPostedMove = false);
		//#############################################################################
		//!Constructor
		/*!Constructs a small posted move 
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
			\param rot const rotation axis values in degrees
		*/
		mwPosted4axMove(
			const point3d& machPos,
			const point3d &partPos,
			const vector3d &toolOrient,
			const double rot,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType);
		//#############################################################################
		//!Constructor
		/*!Constructs a posted 4 axis move tool using the
		parameters given:
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param rot const rotation axis values in degrees
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
			\param newPotSurfContPnt potential surface contact point (3d point)
			\param newPotSurfContPntOrient potential surface contact point orientation (3d point)
			\param newPotSurfID means "this point initial was generated because of the presence of surface with this index"
			the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
			\param potSurfacePointPresent potential surface point present ?
			\param indexToPosted5axMove reference to original toolpath 
			\param addByPost specify if this move was added on POST.
		*/
		//#############################################################################
		// !Virtual destructor
		~mwPosted4axMove();
		//#############################################################################
		mwPosted4axMove(
			const point3d &machPos, 
			const point3d &partPos,
			const vector3d &toolOrient,
			const double &rot, 
			const double &feedr, 
			bool rapidFlag,
			const Types moveType,
			const point3d &newPotSurfContPnt,
			const point3d &newPotSurfContPntOrient, 
			const size_t &newPotSurfID,
			const bool potSurfacePointPresent,
			const size_t &indexToPosted5axMove,
			const bool addByPost);
		//#############################################################################
		//!Copy constructor
		/*!Creates a exact copy of a given tool 
			\param toCopy tool to create a copy of
		*/
		mwPosted4axMove( const mwPosted4axMove &toCopy );
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwPosted4axMove &operator = ( const mwPosted4axMove &toCopy );
		//#############################################################################
		//!Get rotation axis value in degrees 
		/* !Get rotation axis value in degrees    
			\returns const rotation axis value in degrees
		*/
		const double &GetRotVal() const;
		//#############################################################################
		//!Set rotation axis value in degrees
		/*!Set rotation axis value in degrees 
			\param val rotation axis value in degrees
		*/
		void SetRotVal(const double val);
		//#############################################################################
		//!Get maximum agle changes
		/*!Get maximum agle changes
			\param move const posted 4 axis move
			\returns const maximum agle changes
		*/
		const double GetMaxAngleChange( const mwPosted4axMove &move ) const;
		//#############################################################################
		const void AddWindingRotAng( int windingCountRotAng );
		//#############################################################################
		//! Equality operator
		/*! Are given mwPosted4axMove objects equal?
			\param toCompare mwPosted4axMove object to compare the current object with
			\returns true  if both mwPosted4axMove objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwPosted4axMove& toCompare) const;
		//#############################################################################
		virtual void AcceptVisitor( mwPostedVisitor &visitor ) const;
		//#############################################################################
		const mwPostedMovePtr Clone() const
		{
			return new mwPosted4axMove(*this);
		}
		//#############################################################################
	protected:
		//#############################################################################
		double m_rot;// rotation axis values in degrees
		//#############################################################################
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwPosted4axMove> mwPosted4axMovePtr;
}
#endif	//	MW_MWPOSTED4AXMOVE_HPP_
