// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVERIFIERNESTEDENUMS_HPP_
#define MW_MWVERIFIERNESTEDENUMS_HPP_

#include <mwDeprecated.hpp>

namespace VerifierUtil
{
/// This is used in @ref mwMachSimVerifier::SetStockSpindleAxis().
enum StockSpindleAxis
{
	STOCK_SPINDLE_X_AXIS = 0,
	STOCK_SPINDLE_Y_AXIS = 1,
	STOCK_SPINDLE_Z_AXIS = 2
};

/// Spindle mode used in mwMachSimVerifier::SetStockSpindleMode()
enum StockSpindleMode
{
	/// The spindle will be _off_ until this setting is changed.
	STOCK_SPINDLE_OFF = 0,

	/// The spindle will be _on_ until this setting is changed.
	STOCK_SPINDLE_ON = 1,

	/// The auto-select mode tries to guess whether the spindle should be on (spinning infinitely
	/// fast) or off. This heuristic is based on the current tool definition and on whether the
	/// stock is rotationally symmetric.
	///
	/// This setting should only be used if the integration doesn't know the status of the spindle
	/// either.
	STOCK_SPINDLE_AUTO_SELECT = 2
};

/// @deprecated Please use enum @ref StockSpindleAxis instead.
enum MW_DEPRECATED("Please use enum StockSpindleAxis instead.") TurningRotaryAxis
{
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2
};

/// @deprecated Please use enum @ref StockSpindleMode instead.
enum MW_DEPRECATED("Please use enum StockSpindleMode instead.") TurningSpindleMode
{
	TURNING_SPINDLE_OFF = 0,
	TURNING_SPINDLE_ON = 1,
	TURNING_SPINDLE_AUTO_SELECT = 2
};

/// This enum is used in @ref mwMachSimVerifier::SetDrawMode() and @ref
/// mwMachSimVerifier::GetColorScheme(). It decides which color scheme is used.
enum WorkpieceDrawModes
{
	/// Colorize everything in the same color
	WDM_SOLID = 0,

	/// Comparison coloration (gradient based on distance between stock and target)
	WDM_DEVIATION,

	/// Use the id of the tool
	WDM_TOOL,

	/// Use the id of the operation
	WDM_OPERATION,

	/// Use the toolpath segment length
	WDM_TOOL_PATH_SEGMENT_LENGTH,

	/// Use the toolpath height change
	WDM_HEIGHT_CHANGE,

	/// Use the toolpath orientation change
	WDM_ORIENTATION_CHANGE,

	/// Coloration schema of workpiece chunks
	WDM_CHUNKS,

	/// Use the texture handler without marking collisions
	WDM_TEXTURE,

	/// Use the texture handler and mark collisions
	WDM_TEXTURE_PLUS_COLLISIONS,

	/// Use the id of the closest target
	WDM_TARGET_ID,

	/// Comparison color simple (3 colors: gouge, in-tolerance, excess)
	WDM_GOUGE_EXCESS,

	/// Color scheme for removed material (2 colors: original material, changed material)
	WDM_REMOVED_MATERIAL,

	/// Comparison coloration considering the target offset
	WDM_DEVIATION_OFFSET,

	/// Use the type of operation (debug color scheme to distinguish additive, grinding, turning,
	/// meshCutting, stamping, other)
	WDM_OPERATION_TYPE,

	/// Use climb & conventional value (2 colors: climb, conventional)
	WDM_CLIMB_AND_CONVENTIONAL,

	/// Use amount of removed volume (only if volume tracking is enabled in the API)
	WDM_REMOVED_VOLUME,

	/// Reserved mode
	WDM_RESERVED1,

	/// Reserved mode
	WDM_RESERVED2,

	/// Placeholder for uninitialized values (behaves like WDM_SOLID if given to the API)
	WDM_NOINITIALIZED,
};

/// Used in @ref mwMachSimVerifier::ForceDataModel().
enum WorkpieceRepresentations
{
	/// Represent the stock using a simple 2d nail field.
	///
	/// This is the legacy model, which is only suited for 3axis/revolved simulations where you want
	/// maximal performance. Only a subset of the API is implemented for this model.
	MWV_FM_FIELD = 1,

	/// Represent the stock using three orthogonal, interlinked 2d nail fields.
	///
	/// This is the recommended model, which implements the entire API.
	MWV_FM_DEXELBLOCK = 3
};

/// This enum indicates what kind of internal operation the verifier is currently working on. Used
/// in @ref mwMachSimVerifierProgressHandler.
enum mwMachSimVerifierProgressHandlerJobType
{
	JobUnknown = 0,
	JobInitializeTarget,
	JobInitializeMesh,
	JobCalcGougesList,
	JobCalcExcessList,
	JobCalcDeviation,
	JobDrawStockMesh,
	JobFreeWorkpiece,
	JobFreeTarget,
	JobSimulateMoveList,
	JobOffsettingMesh,
	JobSaveSimulation,
	JobLoadSimulation
};

/// The selection mode is used to define the behavior of the @ref mwMachSimVerifier::Select() API.
enum SelectionMode
{
	/// Don't perform any action in @ref mwMachSimVerifier::Select().
	SM_NO_SELECTION = 0,

	/// Add a point measurement label at the selected point.
	///
	/// @see mwMachSimVerifier::SetMeasurementVisibility
	/// @see VerifierUtil::mwvLabelHandler
	SM_POINTS_SELECTION = 1,

	/// Add a distance measurement label at the selected point. A full distance measurement label
	/// appears after calling @ref mwMachSimVerifier::Select() two times, at different positions.
	///
	/// @see mwMachSimVerifier::SetMeasurementVisibility()
	/// @see VerifierUtil::mwvLabelHandler
	SM_DISTANCES_SELECTION = 2,

	/// In this mode two successive @ref mwMachSimVerifier::Select() calls define the two opposing
	/// points of the axis-aligned bounding box used in @ref mwMachSimVerifier::IncreaseZoom()
	SM_ZOOMBOX_SELECTION = 3,

	/// Keep only the selected chunk of material, remove all others
	SM_CHUNK_KEEP_SELECTION = 4,

	/// Remove the selected chunk of material
	SM_CHUNK_DEL_SELECTION = 5,

	/// Calling @ref mwMachSimVerifier::Select() in this mode simply triggers a zoom operation based
	/// on the currently visible part of the stock. The point that was selected is irrelevant here.
	///
	/// @see mwMachSimVerifier::IncreaseZoom()
	SM_ZOOM_DYN_SELECTION = 6,

	/// Like SM_POINTS_SELECTION, but the resulting point has to be cleared with
	/// @ref mwMachSimVerifier::ClearPartsPoints(), instead of
	/// @ref mwMachSimVerifier::ClearMeasurementPoints().
	SM_CHUNK_AUTO_DETECT = 7,

	/// Currently unimplemented, behaves the same as SM_NO_SELECTION.
	SM_CHUNK_DEL_WITH_TEST = 8,

	/// Currently unimplemented, behaves the same as SM_NO_SELECTION.
	SM_CHUNK_AUTO_DEL_BASED_ON_VOLUME = 9
};

/// This enum specifies an order in which the gouges are returned. This is especially useful in
/// combination with @ref mwMachSimVerifier::SetMaxGougeExcessReportSize().
enum GougeExcessReportMode
{
	/// gouge list includes values starting from the beginning of a toolpath
	REPORT_BLOCK_NUMBER_INCREASING = 0,

	/// gouge list includes smallest values from the gouge report
	REPORT_DEVIATION_INCREASING = 1,

	/// gouge list includes biggest values from the gouge report
	REPORT_DEVIATION_DECREASING = 2,

	/// all gouges will be output to the gouge list
	REPORT_ALL = 3
};

/// These flags indicate collisions in @ref mwMachSimVerifier::GetVerificationResult().
enum VerificationCodes
{
	/// No collision
	VC_NO_ERROR = 0,

	/// Collision between flute (cutting part) and stock
	VC_RAPIDEDGE_CRASH = 1,

	/// Collision between shaft (non-cutting part) and stock
	VC_NCEDGE_CRASH = 2,

	/// Collision between arbor and stock
	VC_ARBOR_CRASH = 4,

	/// Collision between holder and stock
	VC_HOLDER_CRASH = 8,

	/// Safety distance violation of flute (cutting part)
	VC_FLUTE_SAFETY_DISTANCE_CRASH = 16,

	/// Safety distance violation of shaft (non-cutting part)
	VC_SHAFT_SAFETY_DISTANCE_CRASH = 32,

	/// Safety distance violation of arbor
	VC_ARBOR_SAFETY_DISTANCE_CRASH = 64,

	/// Safety distance violation of holder
	VC_HOLDER_SAFETY_DISTANCE_CRASH = 128
};

/// Verifier Error Codes
///
/// Return Codes to indicate the success of the function call
enum MWV_ERRORCODE
{
	/// Function call was successful, no errors reported
	MWVE_OK = 0,

	/// Unknown error reported
	MWVE_UNKNWN = 1,

	/// Function not implemented
	MWVE_NOTIMPL = 2,

	/// Function need a Target Part
	MWVE_TARGED_MISSING = 3
};

/// External data mask used in VerifierUtil::mwExternalDataManager::SaveSimulation
enum ExternalDataMask
{
	/// Store the initial stock meshes in external data, instead of serializing them
	EXTERNAL_DATA_INITIAL_MESH = 0x00000001,

	/// Store the target meshes in external data, instead of serializing them
	EXTERNAL_DATA_TARGET_MESHES = 0x00000002,
};

/// Notification codes for NotificationHandler
enum NotificationCode
{
	/// A notification that didn't get it's own warning code yet. Usually indicates an integration
	/// error.
	CUSTOM_NOTIFICATION = 0,

	/// This warning can appear in refine, when the refinement does not have enough memory to
	/// continue.
	OUT_OF_MEMORY = 3325,

	/// This warning can appear in refine. It is triggered in the situation where a chunk was
	/// disconnected in the data model, but in the higher-precision refine data model we see that it
	/// actually _was_ connected. If this chunk was removed in the main model we try to remove it in
	/// the refined model as well, but that may look bad. This warning indicates that this situation
	/// occurred.
	REMOVED_CHUNK_COULD_HAVE_BEEN_STILL_ATTACHED_WARNING = 3327,

	/// This warning may occur in simulations that define tool elements as "cutting and
	/// collision-checked". If the move length is smaller than the collision tolerance then the tool
	/// can (in theory) slowly move into the stock, without ever generating a collision report,
	/// because the colliding material is always removed by the previous move.
	///
	/// To avoid this situation we "delay" collision cuts. That means, we do the collision checking,
	/// but the material removal is done in one of the next moves. This may look like too much
	/// material remains, but the final stock will look correct. We try to fill in the values in
	/// @ref VerifierUtil::VerificationResult as good as possible.
	///
	/// This warning is triggered when delaying cuts is not possible, because the final stock is
	/// needed at an intermediate step in the simulation. For example when calling @ref
	/// mwMachSimVerifier::CreateRestorePoint() or mwMachSimVerifier::SerializeCurrentStock().
	NEXT_COLLISION_MAY_BE_LOST_WARNING = 3328,

	/// This warning can be triggered in SetTools(). If the given tool has solids that overlap on
	/// the tool axis we have to split them. Internally we can only simulate the solids in some
	/// order, not at the same time. The order we decide for is important: if for example the
	/// cutting solid is _behind_ the holder (in move direction) then it could cut away material
	/// that the holder should collide with.
	///
	/// The splitting operation can fail. This usually happens when the tool contains a mesh solid
	/// that is not well-defined (i.e. it has gaps or inner faces). Simulation will still work, but
	/// it is more likely that collision results are incorrect in cases where the simulation order
	/// of tool elements is important.
	PROCESSING_SOLID_DEFINITION_FAILED = 3329
};

/// File types for exporting a stock mesh
enum MeshFileFormat
{
	/// Binary STL format
	MESH_FILE_FORMAT_STL = 0
};

/// Used in @ref mwMachSimVerifier::CastRay().
enum RayCastFace
{
	RAYCAST_FRONT_FACE = -1,  ///< only select faces that point towards the ray
	RAYCAST_ANY_FACE = 0,  ///< any face is fine
	RAYCAST_BACK_FACE = +1,  ///< only select faces that point away from the ray
};

namespace Experimental
{
static const WorkpieceDrawModes WDM_BOTTOM_FLANK = WDM_RESERVED1;
static const WorkpieceDrawModes WDM_LAST_CUT = WDM_RESERVED2;
}  // namespace Experimental

};  // namespace VerifierUtil
#endif  //	MW_MWVERIFIERNESTEDENUMS_HPP_
