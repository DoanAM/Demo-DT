// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPostedMove class

//#############################################################################

#ifndef MW_MWEXTENDEDPOSTEDMOVE_HPP_
#define MW_MWEXTENDEDPOSTEDMOVE_HPP_
//#############################################################################
#include <memory>
#include <vector>
#include "mwTPoint3d.hpp"
#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	//!This class represents a extended posted move.
	class MW_5AXUTIL_API mwExtendedPostedMove
	{
	public:
		//#############################################################################
		typedef cadcam::mwTPoint3d<double>			point3d;
		typedef cadcam::mwTPoint3d<double>			vector3d;
		//#############################################################################
		//!Default constructor
		mwExtendedPostedMove();
		//#############################################################################
		//!Constructor
		mwExtendedPostedMove(
			//const Types moveType,
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
		mwExtendedPostedMove(const mwExtendedPostedMove& toCopy);
		//#############################################################################
		//!Assigment oeprator
		/*!Assigns one tool object to another
			\param toCopy tool to copy the information from
			\returns current tool with copied information
		*/
		const mwExtendedPostedMove& operator = (const mwExtendedPostedMove& toCopy);
		//#############################################################################
		//! Equality operator
		/*! Are given mwPostedMove objects equal?
			\param toCompare mwPostedMove object to compare the current object with
			\returns true  if both mwPostedMove objects contain the same parameters,
			false otherwise
		*/
		bool operator == (const mwExtendedPostedMove& toCompare) const;
		//#############################################################################
		//!Get has potential surface contact point
		/*!Get has potential surface contact point 
			\returns constant bool (potential surface contact point present)
		*/
		const bool HasPotentialSurfContactPoint() const;
		//#############################################################################
		//!Set potential surface contact point
		/*!Get potential surface contact point
			@param potSurfContPointPresent set true if potential surface contact point is present
		*/

		void SetPotentialSurfContactPoint(const bool potSurfContPointPresent);
		//#############################################################################
		const size_t GetNondeterminateSurfaceId() const;
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
		const size_t GetReferenceToOriginalToolpath() const;
		//#############################################################################
		//! Sets reference to original mwPostedMove unchanged by the post process
		void SetReferenceToOriginalToolpath(const size_t indexToPosted5axMove);
		//#############################################################################
		//! Gets if is or not add by post
		const bool GetWasAddOnPost() const;
		//#############################################################################
		//! Sets if is or not add by post
		void SetWasAddOnPost(const bool addByPost);
		//#############################################################################
		static const size_t NONDETERMINATE_SURFACE_ID = 0;
		//#############################################################################
	private:
		//! potential surface contact point position
		point3d	            m_potSurfContPoint;
		//! potential surface contact point orientation
		point3d	            m_potSurfContPointOrient;
		//!	 the ID is 1 base index, 0 means unknown surface ID
		//!  means "this point initial was generated because of the presence of surface with this index"
		size_t              m_potSurfID;
		//! reference to original mwPostedMove unchanged by post process 
		size_t              m_indexToPostedMove;
		//! The type of CNC move
		//unsigned char       m_moveType;
		//! has setup surface contact point?
		bool	            m_potSurfContPointPresent;
		//! is or not posted
		bool                m_addByPost;
		//#############################################################################
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwExtendedPostedMove>       mwExtendedPostedMovePtr;
	//#############################################################################
};
#endif	//	MW_MWEXTENDEDPOSTEDMOVE_HPP_
