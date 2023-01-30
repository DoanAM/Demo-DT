// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCNCMOVE_HPP_
#define MW_MWCNCMOVE_HPP_
#include "mwAutoPointer.hpp"
#include "mwCachingInternalDefs.hpp"
#include "mwCadcamEnumDefinitions.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"

#include <vector>

namespace cadcam
{
class mwCNCMove;
class mwTurningMove;
class mw3axMove;
class mw5axMove;
class mw5axMarkedMove;
class mw6axMove;

/// @class mwCNCMoveVisitor
/// Class implementing visitor scheme for move types inheriting from mwCNCMove
class MW_5AXUTIL_API mwCNCMoveVisitor
{
public:
	virtual ~mwCNCMoveVisitor() {}
	/// Visits an mwCNCMove
	virtual void Visit(const mwCNCMove& mw);
	/// visits an mwTurningMove
	virtual void Visit(const mwTurningMove& mw);
	/// Visits an mw3axMove
	virtual void Visit(const mw3axMove& mw);
	/// Visits an mw5axMove
	virtual void Visit(const mw5axMove& mw);
	/// Visits an mw5axMarkedMove
	virtual void Visit(const mw5axMarkedMove& mw);
	/// Visits an mw6axMove
	virtual void Visit(const mw6axMove& mw);

private:
	/// Override this virtual method in a derived class to set up the default behavior for Visit
	/// methods. By default, the exception "Visitor's method 'Visit' is not implemented" is thrown
	/// for non-overridden Visit methods.
	virtual void Default();
};

/// This class represents a visitor setter for mwCNCMove and its derived classes.
class MW_5AXUTIL_API mwCNCMoveVisitorSetter
{
public:
	virtual ~mwCNCMoveVisitorSetter() {}
	/// Visits an mwCNCMove
	virtual void Visit(mwCNCMove& mw);
	/// visits an mwTurningMove
	virtual void Visit(mwTurningMove& mw);
	/// Visits an mw3axMove
	virtual void Visit(mw3axMove& mw);
	/// Visits an mw5axMove
	virtual void Visit(mw5axMove& mw);
	/// Visits an mw5axMarkedMove
	virtual void Visit(mw5axMarkedMove& mw);
	/// Visits an mw6axMove
	virtual void Visit(mw6axMove& mw);

private:
	/// Override this virtual method in a derived class to set up the default behavior for Visit
	/// methods. By default, the exception "Visitor's method 'Visit' is not implemented" is thrown
	/// for non-overridden Visit methods.
	virtual void Default();
};

/// This class represents a CNC move
#pragma CACHING_INTERNAL_BEGIN
class MW_5AXUTIL_API mwCNCMove
{
public:
	typedef misc::mwAutoPointer<mwCNCMove> Ptr;
	typedef mwTPoint3d<double> point3d;
	typedef mwTPoint3d<double> vector3d;
	typedef point3d positionType;
	typedef vector3d orientationType;

	/// CNC collision states
	typedef mwCNCMoveN::collState collState;

	static const collState COLLISION_NOT_CHECKED = mwCNCMoveN::COLLISION_NOT_CHECKED;
	static const collState COLLISION_FREE = mwCNCMoveN::COLLISION_FREE;
	static const collState COLLISION_LEFT = mwCNCMoveN::COLLISION_LEFT;

	enum moveType
	{
		MOVE_INVALID,
		MOVE_NORMAL,
		MOVE_COMPENSATION,
		MOVE_OFFSET
	};

	enum compensationType
	{
		MW_CC_COMPUTER = 0,
		MW_CC_CONTROL = 1,
		MW_CC_WEAR = 2,
		MW_CC_REVERSE_WEAR = 3,
		MW_CC_OFF = 4
	};

	enum compensationDirection
	{
		MW_CC_LEFT = 0,
		MW_CC_RIGHT = 1
	};

	mwCNCMove();

	/// Constructor
	///
	/// Constructs a CNC move using the given parameters.
	/// @param newPosition is the new position (3d point).
	/// @param newOrientation is the orientation (3d vector).
	/// @param newFeedrate is the feed-rate of the constructed tool.
	/// @param isRapid determines a rapid move.
	/// @param cs is the CNC collision state.
	/// @param parameterizationAgainstOriginalPath
	/// see mwCNCMove::SetParameterizationAgainstOriginalPath for details
	mwCNCMove(
		const point3d& newPosition,
		const vector3d& newOrientation,
		const double newFeedrate,
		const bool isRapid,
		const collState cs,
		const double& parameterizationAgainstOriginalPath);

	virtual ~mwCNCMove();

	const bool operator==(const mwCNCMove& toCompare) const;
	const bool operator!=(const mwCNCMove& toCompare) const;

	/// Sets the new position.
	///
	/// @param position is a constant 3D point.
	virtual void SetPosition(const point3d& position);

	/// Sets the new orientation
	///
	/// @param orientation is the constant 3D vector.
	virtual void SetOrientation(const vector3d& orientation);

	/// Sets the feed rate of the tool.
	///
	/// @param newFeedRate is the feed rate.
	void SetFeedRate(const double newFeedRate);

	/// Sets the move type.
	///
	/// @param newMoveType is used for the cutter compensation to distinguish the tool path types.
	void SetMoveType(moveType newMoveType);

	/// Sets the rapid move.
	///
	/// @param isRapid Use this parameter to turn the rapid move on/off, default = true.
	void SetRapidMove(const bool isRapid = true);

	/// Sets the collision state of the tool.
	///
	/// @param newCollState is the collision state.
	void SetCollisionState(const collState newCollState);

	/// Sets the parametrization against original toolpath
	///
	/// This parameter allows you to set a value for each move, for example, the index in the
	/// toolpath, which allows you to find the position of the move in the original toolpath before you passed
	/// it for conversion. <br>
	/// For example, if you have a toolpath with moves [A, B, C, D, E] then for
	/// the first move A you can set 1, for B you can set 2 and so on. The parameter is used for
	/// converting a 3-axis toolpath to a 5-axis toolpath, where a new move is added to create an
	/// approximation between the moves. <br>
	/// The conversion passes back something similar to:<br>
	/// [A,B,C,C',C'',E] with values like [1,2,3,3.1,3.5,5] (if two new moves were added and one was
	/// removed).<br>
	/// This value is requested by the class constructors of @ref cadcam::mw5axMove and @ref cadcam::mw3axMove.
	/// You can pass 0 if you are not interested in finding the location of moves in the original
	/// toolpath after a toolpath conversion.
	/// @param newParameterizationAgainstOriginalPath is the the parameter value
	void SetParameterizationAgainstOriginalPath(
		const double newParameterizationAgainstOriginalPath);

	/// Gets tool tip point position at the end of the move
	///
	/// @returns tip point position in 3D
	virtual const point3d& GetPosition() const;

	/// Gets tool orientation at the end of the move
	///
	/// @returns A constant 3D vector.
	virtual const vector3d& GetOrientation() const;

	/// Gets feed rate of the tool.
	///
	/// @returns The feed rate of the tool.
	const double GetFeedRate() const;

	/// Gets the cutter compensation.
	///
	/// @returns The cutter compensation of the current move.
	const moveType GetMoveType() const;

	/// Is this a rapid move?
	///
	/// @returns \b true if the move is rapid
	const bool IsRapidMove() const;

	/// Gets he collision state of the tool
	///
	/// @returns The collision state of the tool.
	const collState GetCollisionState() const;

	/// Gets the parametrization against original toolpath
	/// See @ref SetParameterizationAgainstOriginalPath for reference
	const double GetParameterizationAgainstOriginalPath() const;

	/// Gets the linear combination of 2 moves
	///
	/// @param k1 is the k1 factor for move1.
	/// @param move1 is the first move.
	/// @param k2 is the k2 factor for move2.
	/// @param move2 is the second move.
	/// @returns A new constant move object
	static const mwCNCMove LinCmb(
		const double k1, const mwCNCMove& move1, const double k2, const mwCNCMove& move2);

	/// Allows visitors to interact with this class
	///
	/// @param visitor is the visitor
	virtual void AcceptVisitor(mwCNCMoveVisitor& visitor) const;

	/// Allows visitors to interact with the mwCNCMoveVisitorSetter class.
	/// @param visitor is the visitor.
	virtual void AcceptVisitor(mwCNCMoveVisitorSetter& visitor);

protected:
	/// position
	point3d m_position;
	/// orientation
	vector3d m_orientation;
	/// Cutter compensation
	moveType m_curMoveType;
	/// Collision status for this move.
	collState m_curCollState;
	/// FeedRate
	double m_feedRate;
	/// Parameter
	double m_parameterizationAgainstOriginalPath;
	/// Is this a rapid move?
	bool m_isRapidMove;
};
#pragma CACHING_INTERNAL_END
typedef std::vector<mwCNCMove> mwCNCMoves;
typedef misc::mwAutoPointer<mwCNCMove> movePtr;
}  // namespace cadcam
#endif  //	MW_MWCNCMOVE_HPP_
