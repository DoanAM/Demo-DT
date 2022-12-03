// (C) 2014-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSHORTESTPATHROTATIONATTRIBUTE_HPP_
#define MW_MWSHORTESTPATHROTATIONATTRIBUTE_HPP_
#include "mwEnrichedPostedMove.hpp"

/// mwArcAttribute
/// There are 2 possible mods to simulate a difference of angles between two moves: "Shortest path"
/// and "Longest path". (The long path is the math path, for eg. -179, -178, -177..0,1,2,...,178,179)
/// By default ModuleWorks MachSim Simulator will simulate using longest path. This simulation
/// strategy has an effect only if Process Integrator’s Moves + Intermediary Positions is used
/// (CollisionDetectionMode=3 in ini). When an EnrichedMove contains an
/// mwShortestPathRotationAttribute attribute, MachSim will interpolate using shortest path for that
/// move and for the axis specified. If you want to let Machsim process all axes automatically use
/// the constructor with the bool set to true. If you want to control which axes are processed use
/// the constructor that requires target axes. If you want to disable all shortest path processing
/// construct with the bool as false or with an empty target axes list.
class MW_5AXUTIL_API mwShortestPathRotationAttribute: public mwExtendedMoveAttribute
{
public:
	typedef std::vector<misc::mwstring> AxisNames;

public:
	/// mwArcAttribute constructor
	/// @param autoTargetAllAxes If true all rotational axes will be enabled. If false then the set
	/// target axes will be considered
	mwShortestPathRotationAttribute(const bool autoTargetAllAxes = true);


	/// mwArcAttribute constructor
	/// @param targetAxes vector of axis names
	mwShortestPathRotationAttribute(AxisNames& targetAxes);


	/// mwArcAttribute destructor
	virtual ~mwShortestPathRotationAttribute();


	/// mwArcAttribute equal operator
	const bool operator==(const mwShortestPathRotationAttribute& tc) const;


	/// mwArcAttribute different operator
	const bool operator!=(const mwShortestPathRotationAttribute& tc) const;


	/// Returns the target axes names
	const AxisNames& GetTargetAxes() const;


	/// Sets the target axes names
	void SetTargetAxes(const AxisNames& toSet);

	/// Returns the value of the automatic processing flag
	const bool GetAutomaticTargetingOfAllAxes() const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Accept mwExtendedMoveAttributeVisitor visitor const
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;

private:
	AxisNames m_targetAxes;
	bool m_autoTargetAllAxes;
};
#endif  //	MW_MWSHORTESTPATHROTATIONATTRIBUTE_HPP_
