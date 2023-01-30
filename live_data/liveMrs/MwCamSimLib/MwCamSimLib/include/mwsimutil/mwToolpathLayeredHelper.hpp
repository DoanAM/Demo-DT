// (C) 2016-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLPATHLAYEREDHELPER_HPP_
#define MW_MWTOOLPATHLAYEREDHELPER_HPP_
#include "mwCadcamEnumDefinitions.hpp"
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// This namespace presents utility functions to get data from new layered toolpath.
namespace mwToolpathLayeredHelper
{
/// Defines supported layer types
enum LayerTypes
{
	LT_TOOL_ORIENTATION = 0,  ///< This layer keeps tool orientation
	LT_MOVE_TYPE,  ///< This layer keeps move type MoveType
	LT_FEEDRATE,  ///< This layer keeps tool feed rate
	LT_COLLISION,  ///< This layer keeps collision information
	LT_TILT_ANGLE,  ///< This layer keeps tool tilt angle relative Z-Axis
	LT_TOOL_TIP_POSITION_X,  ///< This layer keeps tool tip position on X-Axis
	LT_TOOL_TIP_POSITION_Y,  ///< This layer keeps tool tip position on Y-Axis
	LT_TOOL_TIP_POSITION_Z,  ///< This layer keeps tool tip position on Z-Axis
	LT_ARC_MIDDLE_POINT,  ///< This layer keeps tool tip position for arc middle point
	LT_TAG,  ///< This layer keeps tag information
	LT_TOOL_ROTATION_ANGLE  ///< This layer keeps degrees of tool rotation around it's axis
};

/// Defines supported move types
enum MoveType
{
	MT_CONTOUR,  ///< The move belongs to a toolpath contour
	MT_APPROACH_LINK,  ///< The move belongs to an approach link
	MT_LEAD_IN_LINK,  ///< The move belongs to a lead-in link
	MT_CONNECTION_NOT_CLEAREANCE_AREA_LINK,  ///< The move belongs to a connection
	MT_CONNECTION_CLEAREANCE_AREA_LINK,  ///< The move belongs to a connection of clearance area
										 ///< link
	MT_LEAD_OUT_LINK,  ///< The move belongs to a lead-out link
	MT_RETRACT_LINK  ///< The move belongs to a retract link
};

/// Returns tool tip position on given position idx in a toolpath
MW_5AXUTIL_API mwTPoint3d<double> GetMovePos(
	const mwToolpathLayered& toolpath, const std::size_t idx);

/// Returns tool orientation on given position idx in a toolpath
MW_5AXUTIL_API mwTPoint3d<double> GetToolOrientation(
	const mwToolpathLayered& toolpath, const std::size_t idx);

/// Returns tool rotation angle around it's axis on given position idx in a toolpath
MW_5AXUTIL_API double GetToolRotation(const mwToolpathLayered& toolpath, const std::size_t idx);

/// Returns tool feed rate on given position idx in a toolpath
MW_5AXUTIL_API double GetFeedRate(const mwToolpathLayered& toolpath, const std::size_t idx);

/// Converts move type to toolpath link type
MW_5AXUTIL_API mwTPLinkN::Types TPMoveTypeToTPLinkType(MoveType moveType);

/// Converts move type to toolpath link type
MW_5AXUTIL_API MoveType TPLinkTypeToTPMoveType(mwTPLinkN::Types linkType);

/// Returns moves type on given position idx in a toolpath
MW_5AXUTIL_API MoveType GetMoveType(const mwToolpathLayered& toolpath, const std::size_t idx);

/// Returns true if move is part of arc on given position idx in a toolpath, otherwise false;
MW_5AXUTIL_API bool IsArcMove(const mwToolpathLayered& toolpath, const std::size_t idx);

/// Returns arc middle point on given position idx in a toolpath.
/// If move is not an arc, an exception is thrown.
MW_5AXUTIL_API mwTPoint3d<double> GetArcMiddlePoint(
	const mwToolpathLayered& toolpath, const std::size_t idx);
}  // namespace mwToolpathLayeredHelper
}  // namespace cadcam
#endif  //	MW_MWTOOLPATHLAYEREDHELPER_HPP_
