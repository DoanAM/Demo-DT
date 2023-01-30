// (C) 2007-2021 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedMove class

//#############################################################################

#ifndef MW_MWPOSTEDMOVE_HPP_
#define MW_MWPOSTEDMOVE_HPP_
//#############################################################################
#include "mwExtendedPostedMove.hpp"
#include "mwPostedArcMove.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwPostedMoveCaster;
	class mwPostedMove;
	class mwPosted3axMove;
	class mwPosted4axMove;
	class mwPosted5axMove;
	class mwPosted6axMove;
	class mwPostedNaxMove;
	//#############################################################################
	// This visitor uses const functions
	class MW_5AXUTIL_API mwPostedVisitor
	{
	public:
		//#############################################################################
		//! visits a mwPostedMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPostedMove &mw) const = 0;
		//#############################################################################
		//! visits a mwPosted3axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted3axMove &mw) const = 0;
		//#############################################################################
		//! visits a mwPosted4axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted4axMove &mw) const = 0;
		//#############################################################################
		//! visits a mwPosted5axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted5axMove &mw) const = 0;
		//! visits a mwPosted6axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted6axMove &mw) const = 0;
		//#############################################################################

		virtual void Visit(const mwPostedNaxMove &mw) const = 0;
	};
	//#############################################################################
	// This visitor uses non-const functions
	class MW_5AXUTIL_API mwPostedMoveVisitor
	{
	public:
		//#############################################################################
		//! visits a mwPostedMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPostedMove &mw) = 0;
		//#############################################################################
		//! visits a mwPosted3axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted3axMove &mw) = 0;
		//#############################################################################
		//! visits a mwPosted4axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted4axMove &mw) = 0;
		//#############################################################################
		//! visits a mwPosted5axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted5axMove &mw) = 0;
		//! visits a mwPosted6axMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPosted6axMove &mw) = 0;
				//! visits a mwPostedNaxMove
		/*!
			\param mw the move to be visited
		*/
		virtual void Visit(const mwPostedNaxMove &mw) = 0;
		//#############################################################################
	};
	//#############################################################################
	//!This class represents a posted move.
	class MW_5AXUTIL_API mwPostedMove // Abstract class
	{
	public:
		//#############################################################################
		typedef cadcam::mwTPoint3d<double>			point3d;
		typedef cadcam::mwTPoint3d<double>			vector3d;
		//#############################################################################
		enum Types
		{
			APPROACH_MOVE, //!  the part of the link that connect a link to a contour area, but does not include the lead.
			ENTRY_MACRO_MOVE, //! start area from initial link to a contour area
			CONNECTION_NOT_CLEAREANCE_ARREA_MOVE, //! connection part of the link, clearance are is a safety link area define by the user, can be plane,  cylinder or sphere, where the tool is retracted.
			CONNECTION_CLEAREANCE_ARREA_MOVE, //! connection part of the link, if there is a connection in clearance area
			EXIT_MACRO_MOVE, //! exit area from a contour to a link
			RETRACT_MOVE, //! a retract move from contour to a link, but does not include the lead out area
			CONTOUR_MOVE, //! contour area, the area where the tool is in contact with the workpiece
			REWIND_RETRACT_MOVE, //! first move added by post that is not in contour area
			REWIND_MOVE, //! intermediary move added by rewind algorithm
			REWIND_APPROACH_MOVE, //!  the last move added by rewind algorithm, this is not in contour area
			DWELL_MOVE, //! are special flag added by Machsim CL file parser 
			TOOL_CHANGE_MOVE, //! are special flag added by Machsim CL file parser 
			KEEP_THIS_LAST_TYPES
		};
		//#############################################################################
		//! Equality operator
		/*! Are given mwPostedMove objects equal?
			\param toCompare mwPostedMove object to compare the current object with
			\returns true  if both mwPostedMove objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwPostedMove& toCompare) const;
		//#############################################################################
		// !Virtual destructor
		virtual ~mwPostedMove();
		//#############################################################################
		//!Get absolute machine position
		/*!Get absolute machine position
			\returns const absolute machine position (3d point)
		*/
		const point3d& GetAbsMachPos() const;
		//#############################################################################
		//!Set absolute machine position
		/*!Set absolute machine position
			\param const absolute machine position (3d point)
		*/
		void SetAbsMachPos(const point3d& absmachpos);
		//#############################################################################
		//!Get has potential surface contact point
		/*!Get has potential surface contact point 
			\returns constant bool (potential surface contact point present)
		*/
		const bool HasPotentialSurfContactPoint() const;
		//#############################################################################
		//!Set potential surface contact point
		/*!Set potential surface contact point
			\sets (potential surface contact point present)
		*/
		void SetPotentialSurfContactPoint(const bool potSurfContPointPresent);
		//#############################################################################
		const size_t GetNondeterminateSurfaceId() const;//without set 
		//#############################################################################
		//! gets PotentialSurfaceID
		/*!  means "this point initial was generated because of the presence of surface with this index"
			the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
			\return the PotentialSurfaceID
		*/
		const size_t GetPotentialSurfaceID() const;
		//#############################################################################
		//! sets PotentialSurfaceID
		/*!  means "this point initial was generated because of the presence of surface with this index"
			the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
			\param newPotSurfID the new PotentialSurfaceID
		*/
		void SetPotentialSurfaceID(const size_t newPotSurfID);
		//#############################################################################
		/*!Get potentail surface contact point (3d point) 
			\returns constant 3d point
		*/
		const point3d& GetPotentialSurfaceCP() const;
		//#############################################################################
		//!Set new potentail surface contact point
		/*!Set new potentail surface contact point,
			and potential surface contact point present is true.
			\param potCP constant 3d point
		*/
		void SetPotentialSurfaceCP(const point3d& potCP);
		//#############################################################################
		//!Get potentail surface contact point orientation
		/*!Get potentail surface contact point orientation (3d point) 
			\returns constant 3d point
		*/
		const point3d& GetPotentialSurfaceCPOrient() const;
		//#############################################################################
		//!Set new potentail surface contact point orientation
		/*!Set new potentail surface contact point orientation
			\param potCPOrient constant 3d point
		*/
		void SetPotentialSurfaceCPOrient(const point3d& potCPOrient);
		//#############################################################################
		//!Get feed rate of the move
		/*!Get feed rate of the move
			\returns const feed rate of the move
		*/
		const double GetFeedrate() const;
		//#############################################################################
		//!Set feed rate of the move
		/*!Set feed rate of the move
			\param const feed rate of the move
		*/
		void SetFeedrate(const double FeedRate);
		//#############################################################################
		//!Get tool orientation
		/*!Get tool orientation
			\returns const tool orientation (3d point)
		*/
		const point3d& GetOrientation() const;
		//#############################################################################
		//!Set tool orientation
		/*!Set tool orientation
			\param const tool orientation (3d point)
		*/
		void SetOrientation(const point3d& ToolOrient);
		//#############################################################################
		//!Get relative part position
		/*!Get relative part position
			\returns const relative part position (3d point)
		*/
		const point3d& GetPartPos() const;
		//#############################################################################
		//!Set relative part position
		/*!Set relative part position
			\param const relative part position (3d point)
		*/
		void SetPartPos(const point3d& PartPos);
		//#############################################################################
		//!Get flag for rapid moves
		/*!Get flag for rapid moves
			\returns const reference of a flag for rapid moves
		*/
		const bool IsRapid() const;
		//#############################################################################
		//!Get potentail surface contact point
		//!Set flag for rapid moves
		/*!Set flag for rapid moves
			\param const bool of a flag for rapid moves
		*/
		void SetRapid(const bool RapidMove);
		//#############################################################################
		double GetTime() const;
		//#############################################################################
		void SetTime(const double timeSincePrevMove);
		//#############################################################################
		//!Gets the move type
		const Types GetMoveType() const;
		//#############################################################################
		//!Sets the move type
		void SetMoveType(const Types moveType);
		//#############################################################################
		//!Gets the move spindle speed
		float GetSpindleSpeed() const;
		//!Sets the move spindle speed
		void SetSpindleSpeed(const float value);
		//#############################################################################
		//! Gets the reference to original mwPostedMove unchanged by the post process
		/*!	So, if you have 3 motions (mw5axMove) in the TP lets call them M1,M2 and M3, the you post this pass and get,
			let's say 5 new motions as result of adding one posted motion between M1 and M2 and one between M2 and M3.   
			You will have:
			PM1- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=0 //original M1 move
			PM2- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=1 //added on post move
			PM3- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=1 //original M2 move
			PM4- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=2//added on post move 
			PM5- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=2 //original M3 move
		*/
		const size_t GetReferenceToOriginalToolpath() const;
		//#############################################################################
		//! Sets reference to original mwPostedMove unchanged by the post process
		/*!	So, if you have 3 motions (mw5axMove) in the TP lets call them M1,M2 and M3, the you post this pass and get,
			let's say 5 new motions as result of adding one posted motion between M1 and M2 and one between M2 and M3.   
			You will have:
			PM1- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=0 //original M1 move
			PM2- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=1 //added on post move
			PM3- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=1 //original M2 move
			PM4- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=2//added on post move 
			PM5- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=2 //original M3 move
		*/
		void SetReferenceToOriginalToolpath(const size_t indexToPosted5axMove);
		//#############################################################################
		//! Gets if is or not add by post
		/*!	So, if you have 3 motions (mw5axMove) in the TP lets call them M1,M2 and M3, the you post this pass and get,
			let's say 5 new motions as result of adding one posted motion between M1 and M2 and one between M2 and M3.   
			You will have:
			PM1- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=0 //original M1 move
			PM2- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=1 //added on post move
			PM3- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=1 //original M2 move
			PM4- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=2//added on post move 
			PM5- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=2 //original M3 move
		*/
		const bool GetWasAddOnPost() const;
		//#############################################################################
		//! Sets if is or not add by post
		/*!	So, if you have 3 motions (mw5axMove) in the TP lets call them M1,M2 and M3, the you post this pass and get,
			let's say 5 new motions as result of adding one posted motion between M1 and M2 and one between M2 and M3.   
			You will have:
			PM1- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=0 //original M1 move
			PM2- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=1 //added on post move
			PM3- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=1 //original M2 move
			PM4- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=2//added on post move 
			PM5- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=2 //original M3 move
		*/
		void SetWasAddOnPost(const bool addByPost);
		//#############################################################################
		virtual void AcceptVisitor(mwPostedVisitor &visitor) const;
		//#############################################################################
		virtual void AcceptVisitor(mwPostedMoveVisitor &visitor) const;
		//#############################################################################
		const mwExtendedPostedMove& GetExtendedPostedMove() const;
		//#############################################################################
		const bool IsShortPostedMove() const;
		//#############################################################################
		void SetShortPostedMove(const bool b);
		//#############################################################################
		const mwPostedArcMovePtr GetArcPtr() const;
		//#############################################################################
		mwPostedArcMovePtr& GetArcPtr();
		//#############################################################################
		void SetArcPtr(const mwPostedArcMovePtr& arcPtr);
		//#############################################################################
		const bool IsArcMove() const;
		//#############################################################################
		virtual const misc::mwAutoPointer<mwPostedMove> Clone() const = 0;
		//#############################################################################
		//!Check if this move is a part of a corner in posted toolpath
		/*
			\return value for flag which tells if this move is part of a corner in toolpath
		*/
		const bool IsCorner() const;
		//#############################################################################
		//!Set the flag which tells if move is part of a corner in posted toolpath
		/*
			\param toSet is flag for marking if this move is part of a corner in toolpath
		*/
		void SetCorner(const bool toSet);
		//#############################################################################
		const bool HasReport() const;
		//#############################################################################
		void SetReport(const bool toSet);
		//#############################################################################
	protected:
		//#############################################################################
		//!Default constructor
		mwPostedMove(const bool shortPostedMove = false);
		//#############################################################################
		//!Constructor
		/*!Constructs a small posted move 
			\param machPos const absolute machine position
			\param partPos relative part position
			\param toolOrient const tool orientation
			\param feedr const feed rate of the move
			\param rapidFlag flag for rapid moves
		*/
		mwPostedMove(
			const point3d& machPos,
			const point3d& partPos,
			const vector3d& toolOrient,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType);
		//#############################################################################
		//!Constructor
		/*!Constructs a posted move tool using the parameters given:
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
			\param indexToPostedMove reference to original toolpath - 0 base index representing the position of the move in original toolpath,
			or the index of previous original move it depend on:
			So, if you have 3 motions (mw5axMove) in the TP lets call them M1,M2 and M3, the you post this pass and get,
			let's say 5 new motions as result of adding one posted motion between M1 and M2 and one between M2 and M3.
			You will have:
			PM1- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=0 //original M1 move
			PM2- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=1 //added on post move
			PM3- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=1 //original M2 move
			PM4- GetWasAddOnPost=true and GetReferenceToOriginalToolpath=2//added on post move 
			PM5- GetWasAddOnPost=false and GetReferenceToOriginalToolpath=2 //original M3 move
			\param addByPost specify if this move was added on POST.
		*/
		mwPostedMove( 
			const point3d& machPos, 
			const point3d& partPos,
			const vector3d& toolOrient,
			const double feedr, 
			const bool rapidFlag,
			const Types moveType,
			const point3d& newPotSurfContPnt,
			const point3d& newPotSurfContPntOrient, 
			const size_t newPotSurfID,
			const bool potSurfacePointPresent,
			const size_t indexToPostedMove,
			const bool addByPost);
		//#############################################################################
		//!Copy constructor
		/*!Creates a exact copy of a given tool 
			\param toCopy tool to create a copy of
		*/
		mwPostedMove(const mwPostedMove& toCopy);
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwPostedMove& operator = (const mwPostedMove& toCopy);
		//#############################################################################
		
	//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		//! The type of CNC move
		Types                 m_moveType;
		//! Absolute machine position
		point3d		          m_absMachPos;
		//! Relative part position
		point3d		          m_partPos;
		//! Tool orientation
		point3d		          m_toolOrient;
		//! rest of params 
		mwExtendedPostedMove* m_extendedPostedMovePtr;
		
		//! Feed rate of the move
		double			      m_feedRate;
		//!	 spindle speed
		float                 m_spindleSpeed;
		//
		double	              m_timeSincePrevMove;
		//! Information for for Arc/Helix move
		mwPostedArcMovePtr    m_arcPtr;

		std::vector<double>	  m_axisValues;
#pragma warning(pop)
		//#############################################################################
	private:
#pragma warning(push)
#pragma warning(disable:4251)
		//#############################################################################
		union PostedMoveFlags
		{//Created this union in order to add "corner" extra flag to a move without increasing memory storage space for this class
			char storageSpace;//all flags from struct below will be stored here (extra flags may be added in the future)
			struct { 
				bool RAPID_MOVE_FLG  : 1;
				bool CORNER_MOVE_FLG : 1;
				bool REPORT_FLG : 1;
			} bitFields;
		};

		//! Move info flags
		PostedMoveFlags	  m_flags;

#pragma warning(pop)
		//#############################################################################
		void Verifier() const;
		//#############################################################################
		void Copy(const mwPostedMove& toCopy);
		//#############################################################################
		friend mwPostedMoveCaster;
	};//end class mwPostedMove 
	//#############################################################################
	typedef misc::mwAutoPointer<mwPostedMove>                      mwPostedMovePtr;
	//#############################################################################
}//end namespace post
#endif	//	MW_MWPOSTEDMOVE_HPP_
