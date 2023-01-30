// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW5AXMOVE_HPP_
#define MW_MW5AXMOVE_HPP_
#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// This class represents 5 ax move tool
class MW_5AXUTIL_API mw5axMove: public mwCNCMove
{
public:
	/// Default constructor
	mw5axMove();

	/// Destructor
	virtual ~mw5axMove();

	/// Constructor
	///
	/// Constructs an 5 ax move tool from a CNC move tool using the
	///	parameters given:
	///		@param newCNCMove move
	explicit mw5axMove(mwCNCMove& newCNCMove);

	/// Constructor
	///
	/// Constructs an 5 ax move tool from a CNC move tool using the
	///	   parameters given:
	///	   @param newCNCMove move
	///	   @param newPotSurfContPnt potential surface contact point (3d point)
	///	   @param newPotSurfContPntOrient potential surface contact point orientation (3d point)
	///	   @param newPotSurfID means "this point initial was generated because of the presence of
	///surface with this index" 							the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///	   @param potSurfacePointPresent potential surface point present ?
	mw5axMove(
		const mwCNCMove& newCNCMove,
		const point3d& newPotSurfContPnt,
		const point3d& newPotSurfContPntOrient,
		const size_t& newPotSurfID,
		const bool potSurfacePointPresent);

	/// Constructor
	///
	/// Constructs an 5 ax move tool using the
	///	   parameters given:
	///	   @param newPosition position (3d point)
	///	   @param newOrientation orientation (3d vector)
	///	   @param newPotSurfContPnt potential surface contact point (3d point)
	///	   @param newPotSurfContPntOrient potential surface contact point orientation (3d point)
	///	   @param newPotSurfID means "this point initial was generated because of the presence of
	///surface with this index" 			the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///	   @param potSurfacePointPresent potential surface point present ?
	///	   @param newFeedRate feed rate
	///	   @param isRapid is rapid ?
	///	   @param newCollState CNC collision state
	///	   @param parameterizationAgainstOriginalPath
	///	see mwCNCMove::SetParameterizationAgainstOriginalPath for details
	mw5axMove(
		const point3d& newPosition,
		const vector3d& newOrientation,
		const point3d& newPotSurfContPnt,
		const point3d& newPotSurfContPntOrient,
		const size_t& newPotSurfID,
		const bool potSurfacePointPresent,
		const double newFeedRate,
		bool isRapid,
		const mwCNCMove::collState newCollState,
		const double& parameterizationAgainstOriginalPath);

	/// Get linear combination
	///
	/// Get linear combination with given parameters:
	///		@param k1 factor for move1
	///		@param move1 first 5 ax move object
	///		@param k2 factor for move2
	///		@param move2 second 5 ax move object
	///		@returns new constant 5 ax move object
	static const mw5axMove LinCmb(
		const double k1, const mw5axMove& move1, const double k2, const mw5axMove& move2);

	static const size_t GetNondeterminateSurfaceId();

	/// Get potential surface contact point
	///
	/// Get potential surface contact point (3d point)
	///		@returns constant 3d point
	const point3d& GetPotentialSurfaceCP() const;

	/// Get potential surface contact point orientation
	///
	/// Get potential surface contact point orientation (3d point)
	///		@returns constant 3d point
	const point3d& GetPotentialSurfaceCPOrient() const;

	/// Get has potential surface contact point
	///		@returns constant bool (potential surface contact point present)
	const bool HasPotentialSurfContactPoint() const;

	inline void SetHasPotentialSurfContactPoint(const bool newValue)
	{
		m_potSurfContPointPresent = newValue;
	}

	/// Set new potential surface contact point
	///
	/// Set new potential surface contact point,
	///		and potential surface contact point present is true.
	///		@param potCP constant 3d point
	void SetPotentialSurfaceCP(const point3d& potCP);

	/// Set new potential surface contact point orientation
	///		@param potCPOrient constant 3d point
	void SetPotentialSurfaceCPOrient(const point3d& potCPOrient);

	/// Get PotentialSurfaceID
	///
	/// The surface contact point and orientation were generated because of the presence of the
	/// surface with this index
	///		the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///		@return the PotentialSurfaceID
	inline const size_t GetPotentialSurfaceID() const { return m_potSurfID; }

	/// Set PotentialSurfaceID
	///
	/// The surface contact point and orientation were generated because of the presence of the
	/// surface with this index
	///	the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///		@param newPotSurfID the new PotentialSurfaceID
	inline void SetPotentialSurfaceID(const size_t newPotSurfID) { m_potSurfID = newPotSurfID; }

	/// Equality operator
	///
	/// Are given tools equal?
	///	  @param toCompare tool to compare the current tool with
	///	  @returns <b>true</b> if both tools contain the same parameters,
	///	  <b>false</b> otherwise
	const bool operator==(const mw5axMove& toCompare) const;

	/// Inequality operator
	///
	/// Are given tools equal?
	///	  @param toCompare tool to compare the current tool with
	///	  @returns <b>false</b> if both tools contain the same parameters,
	///	  <b>true</b> otherwise
	const bool operator!=(const mw5axMove& toCompare) const;

	/// implements visitor patter
	///
	///	@param visitor the visition to be accepted
	virtual void AcceptVisitor(mwCNCMoveVisitor& visitor) const;

	/// implements visitor patter
	///
	///	@param visitor the visitor to be accepted
	virtual void AcceptVisitor(mwCNCMoveVisitorSetter& visitor);

private:
	static const size_t NONDETERMINATE_SURFACE_ID;
	/// potential surface contact point position
	point3d m_potSurfContPoint;
	/// potential surface contact point orientation
	point3d m_potSurfContPointOrient;
	///  The surface contact point and orientation were generated because of the presence of surface
	///  with this index
	///	 the ID is 1 base index, 0 means unknown surface ID
	size_t m_potSurfID;
	/// has setup surface contact point?
	bool m_potSurfContPointPresent;
};

typedef std::vector<mw5axMove> mw5axMoves;

}  // namespace cadcam
#endif  //	MW_MW5AXMOVE_HPP_
