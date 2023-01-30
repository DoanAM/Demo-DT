// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3AXMOVE_HPP_
#define MW_MW3AXMOVE_HPP_

#include "mwCNCMove.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// This class represents 3 ax move tool
class MW_5AXUTIL_API mw3axMove: public mwCNCMove
{
public:
	mw3axMove();

	virtual ~mw3axMove();

	mw3axMove(const mwCNCMove& src);

	/// Constructor
	///
	/// Constructs an 3 ax move tool using the parameters given:
	///	@param newPosition position (3d point)
	///	@param newOrientation orientation (3d vector)
	///	@param newFeedRate feed rate
	///	@param isRapid is rapid ?
	///	@param newCollState CNC collision state
	///	@param parameterizationAgainstOriginalPath 
	/// see mwCNCMove::SetParameterizationAgainstOriginalPath for details
	mw3axMove(
		const point3d& newPosition,
		const vector3d& newOrientation,
		const double newFeedRate,
		bool isRapid,
		const mwCNCMove::collState newCollState,
		const double& parameterizationAgainstOriginalPath);

	/// Get linear combination
	///
	/// Get linear combination with given parameters:
	///	@param k1 factor for move1
	///	@param move1 first 3 ax move object
	///	@param k2 factor for move2
	///	@param move2 second 3 ax move object
	///	@return new constant 3 ax move object
	static const mw3axMove LinCmb(
		const double k1, const mw3axMove& move1, const double k2, const mw3axMove& move2);

	/// Equality operator
	///
	/// Are given tools equal?
	///	@param toCompare tool to compare the current tool with
	///	@return <b>true</b> if both tools contain the same parameters,
	///	  <b>false</b> otherwise
	const bool operator==(const mw3axMove& toCompare) const;

	/// Inequality operator
	///
	/// Are given tools equal?
	///	@param toCompare tool to compare the current tool with
	///	@return <b>false</b> if both tools contain the same parameters,
	///	<b>true</b> otherwise
	const bool operator!=(const mw3axMove& toCompare) const;

	/// @name Visitor pattern
	/// @{
	virtual void AcceptVisitor(mwCNCMoveVisitor& visitor) const;
	virtual void AcceptVisitor(mwCNCMoveVisitorSetter& visitor);
	/// @}
};

/// renames the vector of 3ax moves
typedef std::vector<mw3axMove> mw3axMoves;

}  // namespace cadcam
#endif  //	MW_MW3AXMOVE_HPP_
