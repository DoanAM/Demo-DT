// (C) 2015-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCADCAMENUMDEFINITIONS_HPP_
#define MW_MWCADCAMENUMDEFINITIONS_HPP_
namespace cadcam
{
namespace mwTPLinkN
{
enum Types
{
	APPROACH_LINK,
	LEAD_IN_LINK,
	CONNECTION_NOT_CLEAREANCE_ARREA_LINK,
	CONNECTION_CLEAREANCE_ARREA_LINK,
	LEAD_OUT_LINK,
	RETRACT_LINK
};
}

namespace mwCNCMoveN
{
/// Collision state of a move
enum collState
{
	COLLISION_NOT_CHECKED,  ///< Collision not checked
	COLLISION_FREE,  ///< Move is not in collision
	COLLISION_LEFT  ///< Move in collision
};
}  // namespace mwCNCMoveN

namespace mwMoveGenericMarkerN
{
enum StatusAttribute
{
	UNCHANGED = 1,
	MODIFIED,
	REMOVED,
	MW_GENERATED
};
}

}  // namespace cadcam


namespace mwEnrichedPostedMoveN
{
enum Types
{
	TYPE_UNDEFINED = 0,
	APPROACH_MOVE = 1,
	ENTRY_MACRO_MOVE = 2,
	CONNECTION_NOT_CLEAREANCE_ARREA_MOVE = 3,
	CONNECTION_CLEAREANCE_ARREA_MOVE = 4,
	EXIT_MACRO_MOVE = 5,
	RETRACT_MOVE = 6,
	CONTOUR_MOVE = 7,
	REWIND_RETRACT_MOVE = 9,
	REWIND_MOVE = 10,
	REWIND_APPROACH_MOVE = 11,
	DWELL_MOVE = 12,
	TOOL_CHANGE_MOVE = 13,
	KEEP_THIS_LAST_TYPES = 8
};
}
#endif  //	MW_MWCADCAMENUMDEFINITIONS_HPP_
