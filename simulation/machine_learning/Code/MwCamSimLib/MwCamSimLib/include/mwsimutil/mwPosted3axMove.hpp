// (C) 2007-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted3axMove class

//#############################################################################

#ifndef MW_MWPOSTED3AXMOVE_HPP_
#define MW_MWPOSTED3AXMOVE_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a posted 3 axis move.
	class MW_5AXUTIL_API mwPosted3axMove : public mwPostedMove  
	{
	public:
		//#############################################################################
		//!Default constructor
		mwPosted3axMove(const bool shortPostedMove = false);
		//#############################################################################
		//!Constructor
		/*!Constructs a small posted move 
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
		*/
		mwPosted3axMove(
			const point3d& machPos,
			const point3d &partPos,
			const vector3d &toolOrient,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType);
		//#############################################################################
		//!Constructor
			/*!Constructs a posted 3 axis move tool using the
			parameters given:
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
			\param newPotSurfContPnt potential surface contact point (3d point)
			\param newPotSurfContPntOrient potential surface contact point orientation (3d point)
			\param newPotSurfID means "this point initial was generated because of the presence of surface with this index"
			the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
			\param potSurfacePointPresent potential surface point present ?
			\param indexToPosted5axMove reference to original toolpath - 0 base index representing the position of the move in original toolpath,
			\param addByPost specify if this move was added on POST.
		*/
		//#############################################################################
		// !Virtual destructor
		~mwPosted3axMove();
		//#############################################################################
		mwPosted3axMove(
			const point3d &machPos, 
			const point3d &partPos,
			const vector3d &toolOrient,
			const double &feedr, 
			bool rapidFlag,
			const Types moveType,
			const point3d &newPotSurfContPnt,
			const point3d &newPotSurfContPntOrient, 
			const size_t &newPotSurfID,
			const bool potSurfacePointPresent,
			const size_t &indexToPostedMove,
			const bool addByPost);
		//#############################################################################
		//!Copy constructor
		/*!Creates a exact copy of a given tool 
			\param toCopy tool to create a copy of
		*/
		mwPosted3axMove( const mwPosted3axMove &toCopy );
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwPosted3axMove &operator = ( const mwPosted3axMove &toCopy );
		//#############################################################################
		//! Equality operator
		/*! Are given mwPosted3axMove objects equal?
			\param toCompare mwPosted3axMove object to compare the current object with
			\returns true  if both mwPosted3axMove objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwPosted3axMove& toCompare) const;
		//#############################################################################
		virtual void AcceptVisitor( mwPostedVisitor &visitor ) const;
		//#############################################################################
		const mwPostedMovePtr Clone() const
		{
			return new mwPosted3axMove(*this);
		}
		//#############################################################################
	};
	typedef misc::mwAutoPointer<mwPosted3axMove> mwPosted3axMovePtr;
}
#endif	//	MW_MWPOSTED3AXMOVE_HPP_
