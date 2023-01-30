// (C) 2012-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW6AXMOVE_HPP_
#define MW_MW6AXMOVE_HPP_
#include "mw3axMove.hpp"
#include "mw5axMove.hpp"
#include "mw6Axis.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// This class represents 6 ax move tool
class MW_5AXUTIL_API mw6axMove: public mw5axMove
{
public:
	/// Default constructor
	mw6axMove();

	/// Constructs an 6 ax move tool from a 5ax move tool using the
	///	   parameters given:
	///	   @param newCNCMove new 5 ax move
	///	   @param sixAxisToolDirSide new six ax tool dir side
	mw6axMove(const mw5axMove& newCNCMove, const cadcam::mwPoint3d& sixAxisToolDirSide);

	/// Constructs an 6 ax move tool from a 3ax move tool using the
	///	   parameters given:
	///	   @param newCNCMove new 3 ax move
	///	   @param sixAxisToolDirSide new six ax tool dir side
	mw6axMove(const mw3axMove& newCNCMove, const cadcam::mwPoint3d& sixAxisToolDirSide);

	/// Constructs an 6 ax move tool using the
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
	/// @param newToolDirSideAngle is the angle for the 6th axis, it is  mathdef::MW_MIN_DOUBLE
	/// when they 6th axis it not used

	mw6axMove(
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
		const double newToolDirSideAngle);

	/// Constructs an 6 ax move tool using the
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
	///	   @param parameterizationAgainstOriginalPath see getter/setter documentation for details
	///	   @param sixAxisToolDirSide is new six ax tool dir side
	mw6axMove(
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
		const cadcam::mwPoint3d& sixAxisToolDirSide);

	/// Destructor
	virtual ~mw6axMove();

	/// Get linear combination with given parameters:
	///		@param k1 factor for move1
	///		@param move1 first 6 ax move object
	///		@param k2 factor for move2
	///		@param move2 second 6 ax move object
	///		@returns new constant 6 ax move object
	static const mw6axMove LinCmb(
		const double k1, const mw6axMove& move1, const double k2, const mw6axMove& move2);

	/// Set new position
	///	@param position constant 3d point
	virtual void SetPosition(const point3d& position);

	/// Set new orientation
	///	@param orientation constant 3d vector
	virtual void SetOrientation(const vector3d& orientation);

	/// Gets new ToolDirSideAngle angle
	///	@return the toolDirSideAngle
	double GetToolDirSideAngle() const { return m_toolDirSideAngle; }

	/// Set new ToolDirSideAngle angle
	///	@param val new toolDirSideAngle
	void SetToolDirSideAngle(double val) { m_toolDirSideAngle = val; }

	/// Gets the direction of the 6th axis
	///	@return the direction of the 6th axis
	mwPoint3d GetSixAxisToolDirSide() const
	{
		if (m_toolDirSideAngle == mathdef::MW_MIN_DOUBLE)
		{
			return mwPoint3d(0, 0, 0);  // Exception...
		}

		return mw6Axis::GetSide(GetOrientation(), m_toolDirSideAngle);
	}

	/// Sets the direction of the 6th axis
	void SetSixAxisToolDirSide(const mwPoint3d& toolDirSide)
	{
		m_toolDirSideAngle = mw6Axis::GetAngle(GetOrientation(), toolDirSide);
	}

	/// Are given moves equal?
	///	  @param toCompare tool to compare the current tool with
	///	  @returns <b>true</b> if both tools contain the same parameters,
	///	  <b>false</b> otherwise
	const bool operator==(const mw6axMove& toCompare) const;

	/// Are given tools equal?
	///	  @param toCompare tool to compare the current tool with
	///	  @returns <b>false</b> if both tools contain the same parameters,
	///	  <b>true</b> otherwise
	const bool operator!=(const mw6axMove& toCompare) const;
	/// @name Visitor pattern
	/// @{
	virtual void AcceptVisitor(mwCNCMoveVisitor& visitor) const;
	virtual void AcceptVisitor(mwCNCMoveVisitorSetter& visitor);
	/// @}
private:
	/// angle which stores the 6th axis direction vector as an angle in the x, y plane
	/// the functions for getting the direction vector instead of the angle is called
	/// GetSixAxisToolDirSide()
	double m_toolDirSideAngle;
};
typedef std::vector<mw6axMove> mw6axMoves;
typedef misc::mwAutoPointer<mw6axMove> mw6axMovePtr;
}  // namespace cadcam
#endif  //	MW_MW6AXMOVE_HPP_
