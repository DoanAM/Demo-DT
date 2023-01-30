// (C) 2007-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted6axMove class

//#############################################################################

#ifndef MW_MWPOSTED6AXMOVE_HPP_
#define MW_MWPOSTED6AXMOVE_HPP_
//#############################################################################
#include "mwPostedMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a posted 6 axis move.
	class MW_5AXUTIL_API mwPosted6axMove : public mwPostedMove
	{
	public:
		//#############################################################################
		//!Angles state enumeration
		enum anglesState
		{
			ANGLES_DETERMINED,
			ROT_ANGLES_UNDETERMINED_CASE_EQUAL, // when after rot angles are computed first and third vectors are equal
			ROT_ANGLES_UNDETERMINED_CASE_OPPOSITE, // when after rot angles are computed first and third vectors are in opposite directions
			KEEP_THIS_LAST
		};
		//#############################################################################
		//!Default constructor
		mwPosted6axMove(const bool shortPostedMove = false);
		//#############################################################################
		//!Constructor
		/*!Constructs a small posted move 
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param rot0 const rotation axis values in degrees
			\param rot1 const rotation axis values in degrees
			\param rot2 const rotation axis values in degrees
			\param angState const State of rotation 1 and 2 angles
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
		*/
		mwPosted6axMove(
			const point3d& machPos, 
			const point3d& partPos,
			const vector3d& toolOrient,
			const double rot0, 
			const double rot1,
			const double rot2,
			const anglesState& angState,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType);
		//#############################################################################
		//!Constructor
		/*!Constructs a small posted move 
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param rot0 const rotation axis values in degrees
			\param rot1 const rotation axis values in degrees
			\param rot2 const rotation axis values in degrees
			\param angState const State of rotation 1 and 2 angles
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
			\param sawOrient special param for chain saw machine, by default this is null
		*/
		mwPosted6axMove(
			const point3d& machPos, 
			const point3d& partPos,
			const vector3d& toolOrient,
			const double rot0, 
			const double rot1,
			const double rot2,
			const anglesState& angState,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType,
			const vector3d& sawOrient);
		//#############################################################################
		// !Virtual destructor
		~mwPosted6axMove();
		//#############################################################################
		//!Constructor
		/*!Constructs a posted 6 axis move tool using the parameters given:
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param rot0 const rotation axis values in degrees
			\param rot1 const rotation axis values in degrees
			\param rot2 const rotation axis values in degrees
			\param angState const State of rotation 1 and 2 angles
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
		mwPosted6axMove( 
			const point3d &machPos, 
			const point3d &partPos,
			const vector3d &toolOrient,
			const double &rot0, 
			const double &rot1,
			const double &rot2,
			const anglesState &angState,
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
		//!Constructor
		/*!Constructs a posted 6 axis move tool using the parameters given:
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param rot0 const rotation axis values in degrees
			\param rot1 const rotation axis values in degrees
			\param rot2 const rotation axis values in degrees
			\param angState const State of rotation 1 and 2 angles
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
			\param newPotSurfContPnt potential surface contact point (3d point)
			\param newPotSurfContPntOrient potential surface contact point orientation (3d point)
			\param newPotSurfID means "this point initial was generated because of the presence of surface with this index"
				the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
			\param potSurfacePointPresent potential surface point present ?
			\param indexToPosted5axMove reference to original toolpath - 0 base index representing the position of the move in original toolpath,
			\param addByPost specify if this move was added on POST.	
			\param sawOrient special param for chain saw machine, by default this is null
		*/
		mwPosted6axMove( 
			const point3d &machPos, 
			const point3d &partPos,
			const vector3d &toolOrient,
			const double &rot0, 
			const double &rot1,
			const double &rot2,
			const anglesState &angState,
			const double &feedr, 
			bool rapidFlag,
			const Types moveType,
			const point3d &newPotSurfContPnt,
			const point3d &newPotSurfContPntOrient, 
			const size_t &newPotSurfID,
			const bool potSurfacePointPresent,
			const size_t &indexToPostedMove,
			const bool addByPost,
			const vector3d& sawOrient);
		//#############################################################################
		//!Copy constructor
		/*!Creates a exact copy of a given tool 
			\param toCopy tool to create a copy of
		*/
		mwPosted6axMove( const mwPosted6axMove &toCopy );
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwPosted6axMove &operator = (const mwPosted6axMove &toCopy);
		//#############################################################################
		//!Get rotation axis value in degrees
		/*!Get rotation axis value in degrees with given index
			\param idx const index of rotation axis value in degrees array
			\returns const rotation axis value in degrees
		*/
		const double &GetRotVal(const short idx) const;
		//#############################################################################
		//!Set rotation axis value in degrees
		/*!Set rotation axis value in degrees with given index
			\param const rotation axis value in degrees
			\param idx const index of rotation axis value in degrees array			
		*/
		void SetRotVal(const double val,const int idx);
		//#############################################################################
		//!Get angle state of rotation
		/*!Get angle state of rotation
			\returns const angle state
		*/
		const anglesState &GetAnglesState() const;
		//#############################################################################
		//!Set angle state of rotation
		/*!Set angle state of rotation
			\param const angle state
		*/
		void SetAngleState(const anglesState AnglesState);
		//#############################################################################
		//!Get maximum agle changes
		/*!Get maximum agle changes
			\param move const posted 6 axis move
			\returns const maximum agle changes
		*/
		const double GetMaxAngleChange( const mwPosted6axMove &move ) const;
		//#############################################################################
		//!Add winding rotation angle 
		/*!Add winding rotation angle
			\param windingCountRotAng0 winding count rotation angle
		*/
		const void AddWindingRotAng0( int windingCountRotAng0 );
		//#############################################################################
		//!Add winding rotation angle 
		/*!Add winding rotation angle
			\param windingCountRotAng1 winding count rotation angle
		*/
		const void AddWindingRotAng1( int windingCountRotAng1 );
		//#############################################################################
		//!Add winding rotation angle 
		/*!Add winding rotation angle
			\param windingCountRotAng2 winding count rotation angle
		*/
		const void AddWindingRotAng2( int windingCountRotAng2 );
		//#############################################################################
		const bool IsSawOrientValid() const;
		//#############################################################################
		const vector3d& GetSawOrient() const;
		//#############################################################################
		void SetSawOrient(const vector3d& value);
		//#############################################################################
		//! Equality operator
		/*! Are given posted5axTPVec objects equal?
			\param toCompare posted5axTPVec object to compare the current object with
			\returns true  if both posted5axTPVec objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwPosted6axMove& toCompare) const;
		//#############################################################################
		virtual void AcceptVisitor( mwPostedVisitor &visitor ) const;
		//#############################################################################
		const mwPostedMovePtr Clone() const
		{
			return new mwPosted6axMove(*this);
		}
		//#############################################################################
		protected:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################
		void Copy(const mwPosted6axMove &toCopy);
		//#############################################################################
		double			m_rot[3];	    // 3 rotation axis values in degrees
		anglesState		m_anglesState;	// State of rotation 1 and 2 angles
		misc::mwAutoPointer<vector3d> m_sawOrient;  //the default value is null
		//#############################################################################
#pragma warning(pop)
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwPosted6axMove> mwPosted6axMovePtr;
};
//#############################################################################
#endif	//	MW_MWPOSTED6AXMOVE_HPP_
