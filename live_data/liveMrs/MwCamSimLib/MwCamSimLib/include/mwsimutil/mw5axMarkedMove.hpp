// (C) 2017-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW5AXMARKEDMOVE_HPP_
#define MW_MW5AXMARKEDMOVE_HPP_
#include "mw5axMove.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMoveGenericMarker.hpp"

#include <list>

namespace cadcam
{
/// This class represents 5 ax marked move tool
class MW_5AXUTIL_API mw5axMarkedMove: public mw5axMove
{
public:
	typedef misc::mwAutoPointer<mw5axMarkedMove> Ptr;
	typedef std::list<mwMoveGenericMarker::Ptr> mwMoveGenericMarkers;
	typedef misc::mwAutoPointer<mwMoveGenericMarkers> mwMoveGenericMarkersPtr;


	/// Default constructor
	mw5axMarkedMove();

	/// Destructor
	virtual ~mw5axMarkedMove();

	/// Constructor
	///
	/// Constructs a 5 ax marked move tool from a CNC move tool using the
	/// parameters given:
	///	@param newCNCMove move
	explicit mw5axMarkedMove(mwCNCMove& newCNCMove);

	/// Constructor
	///
	/// Constructs a 5 ax marked move tool from a CNC move tool using the
	///   parameters given:
	///   @param newCNCMove move
	///   @param newPotSurfContPnt potentail surface contact point (3d point)
	///   @param newPotSurfContPntOrient potentail surface contact point orientation (3d point)
	///   @param newPotSurfID means "this point initial was generated because of the presence of
	///   surface with this index"
	///						the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///   @param potSurfacePointPresent potentail surface point present ?
	mw5axMarkedMove(
		const mwCNCMove& newCNCMove,
		const point3d& newPotSurfContPnt,
		const point3d& newPotSurfContPntOrient,
		const size_t& newPotSurfID,
		const bool potSurfacePointPresent);

	/// Constructor
	///
	/// Constructs a 5 ax marked move tool using the
	///   parameters given:
	///   @param newPosition position (3d point)
	///   @param newOrientation orientation (3d vector)
	///   @param newPotSurfContPnt potential surface contact point (3d point)
	///   @param newPotSurfContPntOrient potential surface contact point orientation (3d point)
	///   @param newPotSurfID means "this point initial was generated because of the presence of
	///   surface with this index"
	///		the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	///   @param potSurfacePointPresent potential surface point present ?
	///   @param newFeedRate feed rate
	///   @param isRapid is rapid ?
	///   @param newCollState CNC collision state
	///   @param parameterizationAgainstOriginalPath see getter/setter documentation for details
	mw5axMarkedMove(
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

	/// Constructor
	///
	/// Constructs a 5 ax marked move tool using the
	/// parameters given:
	/// @param newPosition position (3d point)
	/// @param newOrientation orientation (3d vector)
	/// @param newPotSurfContPnt potential surface contact point (3d point)
	/// @param newPotSurfContPntOrient potential surface contact point orientation (3d point)
	/// @param newPotSurfID means "this point initial was generated because of the presence of
	/// surface with this index" the ID is 1 base index, 0 means NONDETERMINATE_SURFACE_ID
	/// @param potSurfacePointPresent potential surface point present ?
	/// @param newFeedRate feed rate
	/// @param isRapid is rapid ?
	/// @param newCollState CNC collision state
	/// @param parameterizationAgainstOriginalPath see getter/setter documentation for details
	/// @param moveGenericMarkers a list of generic markers
	mw5axMarkedMove(
		const point3d& newPosition,
		const vector3d& newOrientation,
		const point3d& newPotSurfContPnt,
		const point3d& newPotSurfContPntOrient,
		const size_t& newPotSurfID,
		const bool potSurfacePointPresent,
		const double newFeedRate,
		bool isRapid,
		const mwCNCMove::collState newCollState,
		const double& parameterizationAgainstOriginalPath,
		mwMoveGenericMarkersPtr moveGenericMarkers);


	/// Get linear combination
	///
	/// Get linear combination with given parameters:
	/// @param k1 factor for move1
	/// @param move1 first 5 ax marked move object
	/// @param k2 factor for move2
	/// @param move2 second 5 ax move object
	/// @returns new constant 5 ax marked move object
	static const mw5axMarkedMove LinCmb(
		const double k1,
		const mw5axMarkedMove& move1,
		const double k2,
		const mw5axMarkedMove& move2);


	inline const mwMoveGenericMarkersPtr GetMoveGenericMarkers() const
	{
		return m_moveGenericMarkers;
	}

	/// Get list of generic markers
	///	@returns a list of generic markers
	inline mwMoveGenericMarkersPtr GetMoveGenericMarkers() { return m_moveGenericMarkers; }

	/// Set new generic markers
	///	@param moveGenericMarkers list of generic markers
	inline void SetMoveGenericMarkers(mwMoveGenericMarkersPtr moveGenericMarkers)
	{
		m_moveGenericMarkers = moveGenericMarkers;
	}

	/// implements visitor patter
	///
	/// @param visitor the visition to be accepted
	virtual void AcceptVisitor(mwCNCMoveVisitor& visitor) const;

	/// implements visitor patter
	///
	/// @param visitor the visitor to be accepted
	virtual void AcceptVisitor(mwCNCMoveVisitorSetter& visitor);

protected:
private:
	/// list of generic markers
	mwMoveGenericMarkersPtr m_moveGenericMarkers;
};

typedef std::vector<mw5axMarkedMove> mw5axMarkedMoves;

}  // namespace cadcam
#endif  //	MW_MW5AXMARKEDMOVE_HPP_
