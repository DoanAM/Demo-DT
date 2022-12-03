// (C) 2006-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWMACHSIMVERIFIER_HPP_
#define MW_MWMACHSIMVERIFIER_HPP_
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif
#include "mwFieldCoordinateScaling.hpp"
#include "mwMachSimVerifierColorScheme.hpp"
#include "mwMachSimVerifierProgressHandler.hpp"
#include "mwMotions.hpp"
#include "mwRefineHelpers.hpp"
#include "mwSetCustomToolParameters.hpp"
#include "mwSetToolParameters.hpp"
#include "mwThreadHandlerInterface.hpp"
#include "mwVerifierMoves.hpp"
#include "mwVerifierNestedClasses.hpp"
#include "mwvInitStockGeometry.hpp"
#include "mwvMoveFinishedHandler.hpp"
#include "mwvResettable.hpp"
#include "mwvStockExportMesh.hpp"

#include <mw2dBoundingBox.hpp>
#include <mw3dArc.hpp>
#include <mw3dBoundingBox.hpp>
#include <mw3dContour.hpp>
#include <mw3dGeometryTypedefs.hpp>
#include <mw3dLine.hpp>
#include <mwAutoPointer.hpp>
#include <mwDeprecated.hpp>
#include <mwIProgressHandler.hpp>
#include <mwMathConstants.hpp>
#include <mwMathUtilities.hpp>
#include <mwMesh.hpp>
#include <mwParamsStorageCustomFactory.hpp>
#include <mwStdInputStream.hpp>
#include <mwStdOutputStream.hpp>
#include <mwString.hpp>
#include <mwTPoint2d.hpp>
#include <mwTool.hpp>
#include <mwToolPartSelector.hpp>
#include <mwWarningPragmas.hpp>
#include <vector>

#ifndef MW_GENERATE_DOCUMENTATION
#ifndef MWMSV_API
#ifdef _WIN32
#define MWMSV_API __stdcall
#elif defined(__linux__) || defined(__APPLE__)
#define MWMSV_API
#endif
#endif

#ifndef MW_STDCALL
#if defined(_WIN32)
#define MW_STDCALL __stdcall
#else
#define MW_STDCALL
#endif
#endif
#endif  // MW_GENERATE_DOCUMENTATION

namespace misc
{
class mwLogger;
}

namespace VerifierUtil
{
class mwCutMaterialTextureHandlerParameters;
class mwvAbstractRendererBase;
typedef mwCutMaterialTextureHandlerParameters mwvTextureHandler;
};  // namespace VerifierUtil
namespace Verifier
{
class mwVerifierTestEngine;
class Engine;
}  // namespace Verifier

/// Verifier Error Codes
///
/// Return Codes to indicate the success of the function call
typedef ::VerifierUtil::MWV_ERRORCODE MWV_ERRORCODE;

/// Function call successful no errors reported
static const MWV_ERRORCODE MWVE_OK = ::VerifierUtil::MWVE_OK;
/// Unknown error reported
static const MWV_ERRORCODE MWVE_UNKNWN = ::VerifierUtil::MWVE_UNKNWN;
/// Function not implemented
static const MWV_ERRORCODE MWVE_NOTIMPL = ::VerifierUtil::MWVE_NOTIMPL;
/// Function need a Target Part
static const MWV_ERRORCODE MWVE_TARGED_MISSING = ::VerifierUtil::MWVE_TARGED_MISSING;

const float g_verifierMinPrecision = 0.0001f;
const float g_verifierMaxPrecision = 10000.0f;

class mwThreadHandlerInterface;
class mwMachSimVerifierProgressHandler;
class mwUnitsFactory;

/// CutSim main interface, also called verifier.
///
/// This interface allows to simulate material removal and addition for a single stock instance.
/// See chapter
/// [example application](doc/Developer_guide/Cutting_Additive_Simulation/Example_application.md) on how to use it.
class mwMachSimVerifier
{
public:
	/// Needed for derived classes
	virtual ~mwMachSimVerifier(){};

	/// @name General type definitions
	typedef misc::mwAutoPointer<mwMachSimVerifier> Ptr;
	typedef cadcam::mwTPoint3d<float> Point;
	typedef cadcam::mwTMesh<float> Mesh;
	typedef misc::mwAutoPointer<Mesh> MeshPtr;
	typedef misc::mwAutoPointer<const Mesh> ConstMeshPtr;
	typedef cadcam::mwTPoint2d<float> float2d;
	typedef cadcam::mwTPoint3d<float> float3d;
	typedef cadcam::mwTPoint3d<int> int3d;
	typedef ::VerifierUtil::Frame Frame;
	typedef cadcam::mw3dBoundingBox<float> BoundingBox3d;
	typedef ::VerifierUtil::Color Color;

#ifndef MW_USE_VS2008_COMPATIBILITY
	static MW_VERIFIER_API std::unique_ptr<mwMachSimVerifier> Create();
	static MW_VERIFIER_API std::unique_ptr<mwMachSimVerifier> CreateWithDebugStream(
		std::wostream& pDebugOutputStream);
#endif

	/// @name Notification and Progress
	/// The methods give you a feedback from the simulation.
	/// @{

	typedef VerifierUtil::NotificationHandler NotificationHandler;

	/// The @p handler allows you to receive warnings that arise during the simulation.
	/// @param [in] handler If a null pointer is passed, the notification is disabled.
	virtual void MWMSV_API
	SetNotificationHandler(const misc::mwAutoPointer<NotificationHandler>& handler) = 0;

	/// @see SetNotificationHandler
	virtual const misc::mwAutoPointer<NotificationHandler>& MWMSV_API
	GetNotificationHandler() const = 0;

	/// The @p handler will be supplied with descriptions of the currently running jobs and can be
	/// used to update progress information in your application. It can be also used to abort the
	/// current job, such as Draw() or CalculateGougeExcess().
	/// @param [in] progressHandler If a null pointer is passed, the progress-handler is disabled.
	virtual void MWMSV_API
	SetProgressHandler(mwMachSimVerifierProgressHandler* progressHandler) = 0;
	/// @}

	/// @name Workpiece Import / Export
	///
	/// These methods control the initialization and export of the workpiece data model.
	/// First you should set the workpiece model, then geometry (like stock, targets), to avoid
	/// multiple initializations.
	///
	/// Currently two data models are available. A third model was available in the past
	/// (MWV_FM_DEXELFIELD), but it is no longer supported.
	/// @{

	typedef ::VerifierUtil::WorkpieceRepresentations WorkpieceRepresentations;

	/// 3-Axis Data Model
	///
	/// This is a specially optimized model for 3 axis milling, which is faster than the more
	/// general 5 axis model. The 3 axis data model does not allow any undercuts, meaning
	/// that everything that is not visible from the top can not be represented. It is usually well
	/// suited for simulating 3 axis mold and die tool paths. This data model does not support
	/// turning, mill turn and wireEDM simulation.
	static const WorkpieceRepresentations MWV_FM_FIELD = ::VerifierUtil::MWV_FM_FIELD;

	/// 5-Axis + Turning Data Model
	///
	/// This is the most general and recommended model. It allows to represent all kind of shapes
	/// and does not have the restriction of the 3-Axis model.
	static const WorkpieceRepresentations MWV_FM_DEXELBLOCK = ::VerifierUtil::MWV_FM_DEXELBLOCK;

	/// Select the desired data model for the stock. There is no auto-detection, so "Force" is a bit
	/// misleading.
	///
	/// See mwMachSimVerifier::MWV_FM_FIELD and mwMachSimVerifier::MWV_FM_DEXELBLOCK for an
	/// explanation of the models.
	virtual MWV_ERRORCODE MWMSV_API ForceDataModel(WorkpieceRepresentations representation) = 0;

	/// This returns the value that was set via @ref ForceDataModel.
	///
	/// @note This is not necessarily the data model of the current stock. For that see @ref
	/// GetCurrentStockDataModel().
	virtual WorkpieceRepresentations MWMSV_API GetDataModel() const = 0;

	/// Returns the data model used while creating the current stock. If there is no stock this
	/// returns the current value of @ref GetDataModel().
	virtual WorkpieceRepresentations MWMSV_API GetCurrentStockDataModel() const = 0;

	/// The precision defines the absolute distance between nails in the nail grid. Details smaller
	/// than the precision may be missed, as they can fall in the space between nails.
	///
	/// Smaller precision values increase the quality of the simulation, but they also slow it down
	/// and increase the memory usage.
	///
	/// If you want to apply the specified precision to the current stock please use
	/// ResimulateStock().
	///
	/// @param [in] precision the absolute distance between two adjacent nails
	/// @sa ResimulateStock
	virtual void MWMSV_API SetPrecision(float precision) = 0;

	/// Returns the precision set via @ref SetPrecision.
	///
	/// @note This is not necessarily the precision of the current stock. For that see @ref
	/// GetCurrentStockPrecision().
	virtual float MWMSV_API GetPrecision() const = 0;

	/// Returns the precision used for creating the current stock. If there is no stock this
	/// returns the current value of @ref GetPrecision().
	virtual float MWMSV_API GetCurrentStockPrecision() const = 0;

	/// The mesh quality is an integer between 1 (for the best quality mesh) and 5 (for the
	/// roughest quality mesh).
	///
	/// This API only affects @ref Draw() and @ref Render(). To change the quality of mesh exporting
	/// use @ref SetMeshExportQuality().
	///
	/// The triangulation quality is reduced by ignoring some of the nails. Only every `(1 <<
	/// (meshQuality-1))^2`'th nail is taken into account. That means for mesh quality 1 every nail
	/// is used, for mesh quality 5 only every 256th nail.
	virtual void MWMSV_API SetMeshQuality(int meshQuality) = 0;

	/// @see SetMeshQuality
	virtual void MWMSV_API GetMeshQuality(int& meshQuality) const = 0;

	/// Like @ref SetMeshQuality, but this value is only used during @ref GetMesh() and @ref
	/// ExportStockMesh(), not during @ref Draw() or @ref Render().
	virtual void MWMSV_API SetMeshExportQuality(int meshQuality) = 0;

	/// @see SetMeshExportQuality()
	virtual int MWMSV_API GetMeshExportQuality() const = 0;

	/// Set initial stock geometry as the volume enclosed the given mesh.
	///
	/// If vertex normals are available in the mesh, then they will be used when initializing the
	/// model.
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	/// - This will overwrite the stock spindle and change it to fast-rotating, if
	/// the stock is detected to be rotationally symmetric around the X-, Y- or Z-axis. See
	/// SetStockSpindleAxis() and SetStockSpindleMode().
	///
	/// The given mesh is expected to be closed and free of self-intersection. To set a stock as
	/// the union of several meshes please use @ref SetMeshes() or @ref
	/// VerifierUtil::mwvInitStockMesh.
	///
	/// @param [in] tolerance The generation tolerance of the mesh.
	/// - Decides what error the verifier may make while importing the mesh.
	/// - The value is used in multiple places, for example:
	///	- importing meshes as cylinders (like SetStockCylinder), which allows lots of internal
	///	optimizations
	///	- detecting revolved stocks, which speeds up the initial SetStockSpindleMode(ON).
	/// - If the specified tolerance is negative or mathdef::MW_MAX_FLOAT the verifier will guess a
	/// reasonable value or use the value of SetInitialStockTolerance(), if called before.
	/// - Set this value to >= 0 if you want to increase or decrease the tolerance, compared to the
	/// automatic one.
	///
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetMesh(
		MeshPtr mesh,
		float tolerance = -1,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;

	/// Set initial stock geometry as the union of all given meshes.
	///
	/// If vertex normals are available in the meshes, then they will be used when initializing the
	/// model.
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	/// - This will overwrite the stock spindle and change it to fast-rotating, if
	/// the stock is detected to be rotationally symmetric around the X-, Y- or Z-axis. See
	/// SetStockSpindleAxis() and SetStockSpindleMode().
	///
	/// @param [in] tolerance The generation tolerance of the mesh.
	/// - Decides what error the verifier may make while importing the mesh.
	/// - The value is used in multiple places, for example:
	///	- importing meshes as cylinders (like SetStockCylinder), which allows lots of internal
	///	optimizations
	///	- detecting revolved stocks, which speeds up the initial SetStockSpindleMode(ON).
	/// - If the specified tolerance is negative or mathdef::MW_MAX_FLOAT the verifier will guess a
	/// reasonable value or use the value of SetInitialStockTolerance(), if called before.
	/// - Set this value to >= 0 if you want to increase or decrease the tolerance, compared to the
	/// automatic one.
	///
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetMeshes(
		const std::vector<MeshPtr>& meshes,
		float tolerance = -1,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;

	/// Set a cylindrical stock
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	/// - This will overwrite the stock spindle and change it to fast-rotating with the given axis.
	///
	/// @param [in] height of the cylinder.
	/// @param [in] radius of the cylinder.
	/// @param [in] pos bottom center point or bottom axis of the cylinder.
	/// @param [in] axis (direction) of the cylinder. Must be axis-aligned: +-(0,0,1) or +-(0,1,0)
	/// or +-(1,0,0)
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetStockCylinder(
		float height,
		float radius,
		const float3d& pos,
		const float3d& axis,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;

	/// Set a stock in the form of a cuboid (box).
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	///
	/// The cube must contain material. It may also not be too thin:
	/// (smallest dimension) / (largest dimension) must be larger than 1e-4.
	/// You can use @ref CanSetStock() to check if the box is valid.
	///
	///
	/// To create an empty world (for additive simulation, or to remove the stock) you can call
	/// SetStockEmptyCube().
	///
	/// @param [in] lowerCorner The lower corner of the cube.
	/// @param [in] upperCorner The upper corner of the cube.
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetStockCube(
		const float3d& lowerCorner,
		const float3d& upperCorner,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;

	/// Set up empty work space for an additive simulation.
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	///
	/// The cube defines space that can be used for additive simulation. It may not be too thin:
	/// (smallest dimension) / (largest dimension) must be larger than 1e-4.
	/// You can use @ref CanSetStock() to check if the box is valid.
	///
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetStockEmptyCube(
		const float3d& lowerAdditiveBoxCorner, const float3d& upperAdditiveBoxCorner) = 0;

	typedef ::VerifierUtil::mwvInitStockGeometry mwvInitStockGeometry;
	/// Set up a stock and/or additive work space from a VerifierUtil::mwvInitStockGeometry
	/// specialization:
	///	- see @ref VerifierUtil::mwvInitStockCube / see @ref SetStockCube()
	///	- see @ref VerifierUtil::mwvInitStockEmptyCube / see @ref SetStockEmptyCube()
	///	- see @ref VerifierUtil::mwvInitStockCylinder / see @ref SetStockCylinder()
	///	- see @ref VerifierUtil::mwvInitStockMesh / see @ref SetMesh()
	///	- see @ref VerifierUtil::mwvInitStockRevolved / see @ref SetStockRevolved()
	virtual void MWMSV_API SetStock(const mwvInitStockGeometry& stockGeometry) = 0;

	/// Returns true if a stock has been set.
	virtual bool MWMSV_API HasStock() const = 0;

	/// Removes all material from the stock, but keeps non-stock-dependent simulation data (like
	/// tools) intact.
	///
	/// The world size stays the same, so you can use additive moves and BooleanAdd() to add back
	/// material.
	///
	/// The internal simulation history, non-simulated moves and engagement data is discarded.
	///
	/// To also reset tools and most other simulation state please use Reset().
	virtual void MWMSV_API ClearStock() = 0;

	/// Returns true if a stock can be created with the given size
	virtual bool MWMSV_API
	CanSetStock(const float3d& leftBottom, const float3d& rightTop) const = 0;

	/// Resimulate the current stock.
	///
	/// All pending buffered cuts will be discarded before the re-simulation.
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) if aborted by the
	/// progress handler
	virtual void MWMSV_API ResimulateStock() = 0;

	/// Set if stock should be validated on import
	///
	/// This will have an effect on SetMesh(). If enabled, SetMesh() will take more time
	/// to check if the stock can be imported properly from the mesh. If not, an
	/// exception is thrown. Usually, errors in the mesh like non-matching edges or small gaps are
	/// corrected automatically. The exception is only thrown if this correction fails. This is
	/// usually the case for non-closed meshes with big gaps. This feature is disabled by default to
	/// have maximal performance. @sa GetCheckStock().
	virtual void MWMSV_API SetCheckStock(const bool enabled) = 0;

	/// @sa SetCheckStock()
	virtual bool MWMSV_API GetCheckStock() const = 0;

	/// Trigger repair algorithm for the stock
	///
	/// - Attempts to close all surface holes and other inconsistencies, that could occur e.g.
	/// after a call to SetMesh().
	/// - This method is not needed, if Draw() or Render() are called regularly. Those calls already
	/// trigger the repair algorithm.
	/// - A use case for this method is a console-only integration. Call it just after SetMesh() to
	/// make sure that no false collisions appear due to an inconsistent internal model.
	virtual void MWMSV_API RepairStock() = 0;

	/// Return the size of the stock, excluding all material that was removed before.
	///
	/// - When zoomed in (see IncreaseZoom()), this method will return the bounding box of the
	///   visible stock-part only.
	/// - In contrast to GetWorldBoundingBox(), this method always recomputes the bounding box of
	///   the current material. So it may shrink over time, when the stock is cut, or it may
	///   increase in size if additive simulation is performed.
	/// - If no stock is defined, then this method returns (INF,INF,INF), (-INF,-INF,-INF),
	///   where INF = mathdef::MW_MAX_FLOAT.
	virtual void MWMSV_API
	GetCurrentStockBoundingBox(float3d& leftBottom, float3d& rightTop) const = 0;

	/// Return the size of the stock, excluding all material that was removed before.
	///
	/// - This bounding box takes the spindle state into account.
	/// - When zoomed in (see IncreaseZoom()), this method will return the bounding box of the
	///   visible stock-part only.
	/// - In contrast to GetStockBoundingBox(), this method always recomputes the bounding box of
	///   the current material. So it may shrink over time, when the stock is cut, or it may
	///   increase in size if additive simulation is performed.
	/// - If no stock is defined, then this method returns an uninitialized bounding box (@ref
	///   BoundingBox3d::IsInitialized() returns false).
	virtual BoundingBox3d MWMSV_API GetCurrentStockBoundingBox() const = 0;

	/// Get the bounding box of the initial stock, enlarged by the space allocated for additive
	/// manufacturing.
	///
	/// - This bounding box describes the space taken by the non-spinning stock. To include the size
	///   of the spinning stock as well use @ref GetStockBoundingBox().
	/// - The world size is important for BooleanUnify(), as it does not increase the world size to
	///   make space for both meshes. That is, if you unify with a mesh bigger than the initial
	///   stock, this mesh will not be unified completely (only the volume inside the world).
	/// - When zoomed in (see IncreaseZoom()), this method will return the bounding box of the
	///   visible area. That is, the world size has shrunken to the zoomed-in part.
	/// - If no stock is defined, then this method returns (INF,INF,INF), (-INF,-INF,-INF),
	///   where INF = mathdef::MW_MAX_FLOAT.
	virtual void MWMSV_API GetWorldBoundingBox(float3d& leftBottom, float3d& rightTop) const = 0;

	/// Get the bounding box of the initial stock, enlarged by the space allocated for additive
	/// manufacturing.
	///
	/// - This bounding box describes the space taken by the non-spinning stock. To include the size
	///   of the spinning stock as well use @ref GetStockBoundingBox().
	/// - The world size is important for BooleanUnify(), as it does not increase the world size to
	///   make space for both meshes. That is, if you unify with a mesh bigger than the initial
	///   stock, this mesh will not be unified completely (only the volume inside the world).
	/// - When zoomed in (see IncreaseZoom()), this method will return the bounding box of the
	///   visible area. That is, the world size has shrunken to the zoomed-in part.
	/// - If no stock is defined, then this method returns an uninitialized bounding box (@ref
	///   BoundingBox3d::IsInitialized() returns false).
	virtual BoundingBox3d MWMSV_API GetWorldBoundingBox() const = 0;

	/// Get a coarse bounding box for the stock.
	///
	/// - The bounding box is based on the initial stock geometry, as well as the stock spindle and
	///   it's state. Cutting away material doesn't change it (see also @ref
	///   GetCurrentStockBoundingBox()).
	/// - If the spindle is disabled then this function returns the same value as @ref
	///   GetWorldBoundingBox(). If the spindle is enabled then the bounding box may be larger.
	/// - When zoomed in (see IncreaseZoom()), this method will return the bounding box of the
	///   visible area. That is, the world size has shrunken to the zoomed-in part.
	/// - If no stock is defined, then this method returns an uninitialized bounding box (@ref
	///   BoundingBox3d::IsInitialized() returns false).
	virtual BoundingBox3d MWMSV_API GetStockBoundingBox() const = 0;

	/// The stock will be clipped to this bounding box on initialization and for additive tool
	/// paths.
	virtual void MWMSV_API SetConstrainBox(bool enable, float3d min, float3d max) = 0;

	/// @see SetConstrainBox
	virtual void MWMSV_API GetConstrainBox(bool& enable, float3d& min, float3d& max) const = 0;

	/// Resizes the internal stock model to the given box.
	///
	/// By enlarging the world box you can increase the usable area for additive simulation.
	/// By shrinking the world box to save memory and improve performance, for example after a
	/// SplitOff operation. Nails will be clamped against this box or deleted.
	///
	/// Interaction with Refine:
	/// If you want to use refine after calling ResizeWorldBox you have to make sure that the
	/// simulation is never clipped against the world box. This means:
	/// - the new world box contains the entire current stock
	/// - no additive moves are performed outside or partially outside of the world box.
	///
	/// If the stock is ever clipped you will get visual artifacts during refine.
	virtual void MWMSV_API ResizeWorldBox(const float3d& min, const float3d& max) = 0;

	/// Calculate a mesh from the current stock geometry
	///
	/// The method can be used in two ways depending of your intended usage:
	/// - To receive a mesh in the return value, pass NULL to the filename parameter
	/// - To write a (binary) STL file to disk pass the file name. In this case no in-memory
	///   representation is returned.
	///
	/// If the given tolerance is larger than zero the mesh will be decimated.
	///
	/// If @p exportSTLColors is true, then the current color scheme will be used to colorize the
	/// STL file (using the Materialise Magics format). Note: the tolerance has to be zero to use
	/// this feature. The color is encoded in the two "attribute byte count" bytes with 5 bits per
	/// color: "(b << 10) | (g	<< 5) | r".
	///
	/// You can also use @ref ExportStockMesh() if you want a cleaner API, or if you want mesh
	/// colors for the in-memory representation.
	///
	/// Description of the stl file format: http://en.wikipedia.org/wiki/STL_%28file_format%29.
	virtual MeshPtr MWMSV_API GetMesh(
		const misc::mwstring* filename = MW_NULL,
		float tolerance = 0,
		bool exportSTLColors = false) const = 0;

	/// Calculate a mesh for the current stock geometry, restricted to the space starting at zLevel
	///
	/// Getting a partial mesh is often faster than getting the entire mesh, if only a part of the
	/// mesh is needed.
	virtual MeshPtr MWMSV_API
	GetMeshAboveZLevel(const float zLevel, const float tolerance = 0.0f) const = 0;

	/// Calculate a mesh from the current stock geometry, clipped to the given bounding box
	///
	/// Getting a partial mesh is often faster than getting the entire mesh.
	///
	/// Clipped sides of the stock will not be filled, so the mesh returned is most likely not
	/// closed. The triangles are clipped exactly at the bounding box sides.
	///
	/// This method can be used to obtain mesh slices, or for getting only the triangles above a
	/// certain height. @sa GetMesh
	virtual MeshPtr MWMSV_API GetMeshInBoundingBox(
		const float3d& min, const float3d& max, const float tolerance = 0.0f) const = 0;

	/// Calculate a mesh from the current stock geometry, clipped by two parallel planes
	///
	/// Getting a partial mesh is often faster than getting the entire mesh.
	///
	/// Clipped sides of the stock will not be filled, so the mesh returned is most likely not
	/// closed. The triangles are clipped exactly by the planes.
	///
	/// This method can be used to obtain mesh slices
	/// @sa GetMesh
	virtual MeshPtr MWMSV_API GetMeshBetweenPlanes(
		const float3d& planeNormal, float planeOffset1, float planeOffset2) const = 0;

	/// Calculate a chunk mesh from the current stock geometry
	///
	/// This method returns the chunk mesh for a given chunkId as a mesh of triangles or directly
	/// streams the mesh to disk (STL binary format).
	///
	/// To obtain a valid chunk id you can call GetChunks(), FindChunksAtPositions(),
	/// SelectSurfaceInfo() or SelectSurfaceInfo3d().
	///
	/// You'll receive a mesh object if the filename is NULL, otherwise the mesh is streamed to
	/// disk.
	///
	/// The mesh is decimated using the given tolerance.
	virtual MeshPtr MWMSV_API GetChunkMesh(
		const int chunkId, const misc::mwstring* filename = MW_NULL, float tolerance = 0) const = 0;

	/// Returns a mesh that describes the initial stock mesh. If the initial stock was defined as a
	/// mesh you'll get the given mesh back, otherwise a mesh approximation is created in this
	/// function.
	///
	/// You'll receive a mesh object if the filename is NULL, otherwise the mesh is streamed to
	/// disk.
	///
	/// @note If the initial stock was defined as a mesh but then detected as a cylinder or box,
	/// you'll get back a mesh approximation of the detected shape rather than the original mesh.

	virtual MeshPtr MWMSV_API
	GetOriginalStockMesh(const misc::mwstring* filename = MW_NULL) const = 0;

	typedef VerifierUtil::ExportStockMeshOptions ExportStockMeshOptions;

	/// Calculate a mesh from the current stock geometry.
	///
	/// This method returns the current geometry of the stock as a mesh of triangles. Additional
	/// attributes can be requested via the options parameter.
	virtual misc::mwAutoPointer<VerifierUtil::StockExportMesh> MWMSV_API
	ExportStockMesh(const ExportStockMeshOptions& options = ExportStockMeshOptions()) const = 0;

	/// Write a mesh from the current stock geometry to disk.
	///
	/// This method returns the current geometry of the stock as a mesh of triangles. Additional
	/// attributes can be requested via the options parameter.
	virtual void MWMSV_API ExportStockMesh(
		const misc::mwstring& fileName,
		const VerifierUtil::MeshFileFormat fileFormat = VerifierUtil::MESH_FILE_FORMAT_STL,
		const ExportStockMeshOptions& options = ExportStockMeshOptions()) const = 0;

	/// Set if stock mesh normals shall be smoothed on import
	///
	/// Smoothing the mesh normals will lead to a visually more pleasing result. It has the drawback
	/// of slower import speed. The threshold for introducing an edge, vs. a smooth surface is
	/// currently hard-coded internally.
	virtual void MWMSV_API SetMeshImportSmoothNormals(bool enabled) = 0;

	/// @see SetMeshImportSmoothNormals()
	virtual bool MWMSV_API GetMeshImportSmoothNormals() const = 0;

	/// The primitives cache stores all drawn triangles and edges created by Draw()/Render() inside
	/// the verifier. This avoids a retriangulation when exporting the mesh or in measurement
	/// methods CastRay(), TraceEdge() or TraceSection()
	virtual void MWMSV_API EnablePrimitivesCache(bool enable = true) = 0;

	/// @see EnablePrimitivesCache()
	virtual bool MWMSV_API IsPrimitivesCacheEnabled() const = 0;

	/// @}

	/// @name Tool interface
	/// @anchor CutSim_tool_API
	///
	/// This interface provides methods to add tools to the simulation. For a description on how to
	/// create a tool object and what constraints related to tool shapes exist, see the chapter
	/// [tools](doc/Developer_guide/Cutting_Additive_Simulation/Tools.md).
	///
	/// The typical use case is to:
	///
	/// 1. Add a tool via @ref SetTool(). This tool is now the active tool.
	/// 2. Define, what the active tool should do via @ref SetToolBehavior()
	/// 3. Simulate some moves of the active tool via @ref SimulateMove() or @ref BufferMove()
	///
	/// You can also define multiple active tools, see @ref SetTools().
	///
	/// If the 3d display is realized via a direct OpenGL integration through the @ref Draw() call
	/// the tool can also be displayed using the @ref SetToolVisibility() method through OpenGL
	/// calls. However it is strongly recommended to implement a custom client for tool display.
	/// This allows full control of the look and feel. It is mandatory when using an Abstract
	/// Renderer.
	///
	/// @{

	/// Set one active tool used for the next moves, see [tool interface](@ref CutSim_tool_API).
	///
	/// If your simulation uses multiple tools please consider using @ref SetTools(), as this
	/// provides better performance when switching back to a previous tool.
	///
	/// @note The given tool is regarded as a "new" tool. This means that the tool behavior is reset
	/// to default values. Please call SetToolBehavior() to change it.
	///
	/// @param [in] tool pointer to the tool-representation. The verifier assumes that the given
	///		   tool is constant. Modifying it after it was given to the verifier results in
	///		   undefined behavior.
	/// @param [in] toolId identifier of the tool object. Used to reference the tool later, e.g. in
	///		   @ref VerifierUtil::VerificationResult::ToolId or
	///		   @ref VerifierUtil::GougeReport::toolNumber. It is also used for the color scheme
	///		   @ref VerifierUtil::WDM_TOOL.
	virtual void MWMSV_API SetTool(cadcam::mwConstToolPtr tool, int toolId) = 0;

	typedef VerifierUtil::mwSetToolParameters SetToolParameters;
	typedef std::vector<SetToolParameters> SetToolsParameters;

	/// Set multiple active tools for the next moves, see [tool interface](@ref CutSim_tool_API).
	///
	/// This can be used together with SetCurrentCutTool() to simulate simultaneously cutting tools,
	/// see [Multiple tools](@ref CutSim_Multiple_tools).
	///
	/// @note Calling @ref SetTools() will count all given tools as "new" tools. This means that the
	/// tool behavior is reset to default values, even if some of the tools stay the same. Please
	/// call @ref SetToolBehavior() to change it.
	///
	/// If a subset of the tools stays the same we recommend to re-use the existing tool
	/// auto-pointer. This allows us to keep many internally precomputed tool-specific structures,
	/// which results in better performance and a lower memory footprint. If you just want to add a
	/// tool to the current tool set it is more efficient to call AddTool().
	///
	/// @param [in] tools A vector of tool-definitions. See the parameters of @ref SetTools()
	///		   for restrictions.
	virtual void MWMSV_API SetTools(const SetToolsParameters& tools) = 0;

	/// Add a tool to the existing active tool set, see [tool interface](@ref CutSim_tool_API).
	///
	/// Every time you use @ref SetTools() the tools are copied to an internal map. This is
	/// necessary for features that need the history of moves, like refine or certain color schemes.
	/// If you want to add a tool, while keeping the previous tools available, AddTool() is more
	/// efficient.
	///
	/// The tool is added to the back of the currently active tool vector.
	///
	/// The new tool is not set as the currently active tool. To do that use @ref
	/// SetCurrentCutTool().
	///
	/// @note The given tool is regarded as a "new" tool. This means that the tool behavior is set
	/// to default values. Please call @ref SetToolBehavior() to change it.
	///
	/// See the parameters of @ref SetTools() for restrictions.
	virtual void MWMSV_API AddTool(cadcam::mwConstToolPtr tool, int toolId) = 0;

	/// Sets the color for each tool element.
	///
	/// The color of the tool does NOT affect the color of the material which is cut out of the
	/// stock. These colors are used in the @ref Draw() method to define the appearance of the drawn
	/// tool, if enabled via @ref SetToolVisibility().
	///
	/// Each parameter contains one RGB value (X=R, Y=G, Z=B). These and the parameter @p alpha are
	/// between 0.0f and 1.0f.
	///
	/// @note This method may be deprecated in the future. We recommend implementing tool
	/// visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	virtual void MWMSV_API SetToolColor(
		float3d cuttingColor,
		float3d nonCuttingColor,
		float3d arborColor,
		float3d holderColor,
		float alpha = 1.0f) = 0;

	/// Sets the color of the tool edge only, see @ref SetToolColor().
	///
	/// All parameters @p r, @p g, @p b, @p alpha are in the range of 0.0f to 1.0f.
	virtual void MWMSV_API SetToolColor(float r, float g, float b, float alpha = 1.0f) = 0;

	/// See @ref SetToolColor()
	virtual void MWMSV_API GetToolColor(
		float3d& cuttingColor,
		float3d& nonCuttingColor,
		float3d& arborColor,
		float3d& holderColor,
		float& alpha) const = 0;

	/// Enable tool graphic during draw call.
	///
	/// @note This method may be deprecated in the future. We recommend implementing tool
	/// visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	///
	/// @param [in] bIsToolVisible (true) if the tool should be drawn from the verifier
	virtual void MWMSV_API SetToolVisibility(bool bIsToolVisible) = 0;

	/// @sa SetToolVisibility
	virtual bool MWMSV_API GetToolVisibility() const = 0;

	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	MW_DEPRECATED("Please implement custom tool drawing on the integration side.")
	virtual void MWMSV_API SetCustomToolDrawingPosition(const Frame& DisplayPosition) = 0;

	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	MW_DEPRECATED("Please implement custom tool drawing on the integration side.")
	virtual void MWMSV_API EnableCustomToolDrawingPosition(bool enable) = 0;

	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	MW_DEPRECATED("Please implement custom tool drawing on the integration side.")
	virtual void MWMSV_API SetCustomToolDrawing(cadcam::mwConstToolPtr tool) = 0;

	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	typedef ::VerifierUtil::SetCustomToolParameters SetCustomToolParameters;
	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	typedef ::VerifierUtil::SetCustomToolsParameters SetCustomToolsParameters;

	/// @deprecated Please implement tool visualization on integration side,
	/// see [drawing a tool](@ref doc/Developer_guide/Tools/Drawing_a_tool.md).
	MW_DEPRECATED("Please implement custom tool drawing on the integration side.")
	virtual void MWMSV_API SetCustomTools(const SetCustomToolsParameters& tools) = 0;

	/// @}

	/// @name Move attributes
	/// @anchor cutsim_move_attributes
	///
	/// Methods that set additional attributes for the next moves
	/// defined by @ref BufferMove() or @ref SimulateMove(). The attributes
	/// will apply to all following moves until they are changed again.
	///
	/// Attributes are returned after calling @ref SimulateBufferedCuts(), e.g. in
	/// @ref VerifierUtil::VerificationResult, and can be used on integration side.
	/// To get all attributes use @ref GetSimulatedMoveParameters().
	///
	/// Some attributes can also be retrieved together with the stock mesh returned by
	/// @ref Render(). The attributes can be requested using
	/// @ref VerifierUtil::RenderOptions::RequestAttributes() and are then returned by the abstract
	/// renderer interface in @ref VerifierUtil::AbstractRendererAttributes::VertexAttributes.
	///
	/// @{

	/// Sets a custom move id (see [move attributes](@ref cutsim_move_attributes)) which can be used
	/// on integration side to identify a move when interpreting simulation results e.g. in
	/// VerifierUtil::VerificationResult::MoveID or VerifierUtil::GougeReport::moveId.
	/// A common use case is to store information about intermediate move interpolation steps in it,
	/// e.g. for a time based simulation.
	///
	/// The verifier does not use it for internal computations, it's only stored and returned for
	/// integration purposes.
	virtual void MWMSV_API SetMoveID(float moveID) = 0;
	/// @see SetMoveID()
	virtual float MWMSV_API GetMoveID() const = 0;

	/// @deprecated Please use @ref SetMoveID().
	MW_DEPRECATED("Please use SetMoveID().")
	virtual inline void MWMSV_API SetMoveNumber(int moveNum)
	{
		SetMoveID(static_cast<float>(moveNum));
	}

	/// Sets a textual information for each move, see [move attributes](@ref
	/// cutsim_move_attributes).
	///
	/// The verifier does not use it for internal computations, it's only stored and returned for
	/// integration purposes.
	virtual void MWMSV_API SetMoveDescription(const misc::mwstring& desc) = 0;
	/// @see SetMoveDescription()
	virtual misc::mwstring MWMSV_API GetMoveDescription() const = 0;

	/// This operation id is used for example to color the stock
	/// with the color-scheme VerifierUtil::WDM_OPERATION (see mwMachSimVerifier::GetColorScheme()).
	///
	/// It can also be used for integration purposes, see [move attributes](@ref
	/// cutsim_move_attributes).
	virtual void MWMSV_API SetOperation(int id) = 0;
	/// @sa SetOperation()
	virtual int MWMSV_API GetOperation() const = 0;

	MW_DEPRECATED("Not used anymore, has no effect.")
	virtual MWV_ERRORCODE MWMSV_API SetFeed(float fFeed) = 0;

	MW_DEPRECATED("Not used anymore, has no effect.")
	virtual MWV_ERRORCODE MWMSV_API SetSpindleSpeed(float fSpSpeed) = 0;

	typedef VerifierUtil::MoveParameters MoveParameters;

	/// Get all currently set [move parameters/attributes](@ref cutsim_move_attributes).
	/// Those parameters will be used for the next buffered or simulated moves.
	virtual MoveParameters MWMSV_API GetMoveParameters() const = 0;

	/// Get attributes of the last simulated moves (e.g. using @ref SimulateBufferedCuts()).
	///
	/// This method can be used to easily map the results of a @ref SimulateBufferedCuts() call
	/// to an integration's own data structures.
	///
	/// See also See [move attributes](@ref cutsim_move_attributes).
	///
	/// @param paramsPerMove The size of the vector matches the number of moves that were simulated
	/// in the last SimulateBufferedCuts() call, or 1 if SimulateMove(), Cut() or other similar
	/// methods were called.
	virtual void MWMSV_API
	GetSimulatedMoveParameters(std::vector<MoveParameters>& paramsPerMove) const = 0;

	/// @}

	/// @name Turning simulation
	/// In Turning simulation the stock turns "infinitely" fast. Any tool that touches it will
	/// therefore remove an entire ring of material.
	///
	/// Since the "turning" stock is always rotationally symmetric we can use a two-dimensional
	/// model internally, which is much faster than the non-turning stock.
	///
	/// The stock rotates around an axis-aligned line called the "spindle axis". This can be defined
	/// via @ref SetStockSpindleAxis().
	///
	/// The tool is controlled via the same interface as milling (@ref BufferMove(), @ref
	/// SimulateMove() etc).
	///
	/// If you're using a lathe tool then the 2d contour lies in the XZ plane, where Z is the tool
	/// axis. The tool orientation must be defined accordingly. The XZ plane of the tool doesn't
	/// have to be the XZ direction of the stock though, any rotation around the stock is fine. For
	/// example, to to move the lathe tool on the XY-plane, you will have to rotate it by -90°
	/// around the X-axis, using `Quaternion(-90.0f, float3d(1, 0, 0))`.
	/// @{

	/// Spindle mode used in SetStockSpindleMode()
	typedef ::VerifierUtil::StockSpindleMode StockSpindleMode;

	/// Set the mode of stock-spindle, that is, if the stock rotates at infinite speed or not.
	///
	/// The @p spindleMode may be STOCK_SPINDLE_ON, STOCK_SPINDLE_OFF or STOCK_SPINDLE_AUTO_SELECT.
	/// - STOCK_SPINDLE_ON: the spindle is on and will show the rotationally symmetrically
	/// stock.
	/// - STOCK_SPINDLE_OFF: the spindle is off and will show the milling mode (non
	/// rotationally symmetric).
	/// - STOCK_SPINDLE_AUTO_SELECT: mwMachSimVerifier guesses whether the simulation is a turning
	/// simulation. This depends on the last tool that was used and on whether the stock is
	/// rotationally symmetric. Auto-mode may be slow when frequently switching between milling and
	/// lathe tools, because of frequent switches between the data models. Auto mode is only
	/// supported if the turning axis position is (0, 0, 0), otherwise it defaults to OFF.
	///
	/// STOCK_SPINDLE_AUTO_SELECT mode should only be used if the integration doesn't know whether
	/// the stock is rotating "infinitely" fast. If that fact is known then you should always
	/// explicitly give that information to mwMachSimVerifier.
	///
	/// Note that helical thread cuts cannot be simulated with TURNING_SPINDLE_ON. @sa ThreadCut.
	virtual void MWMSV_API SetStockSpindleMode(const StockSpindleMode spindleMode) = 0;

	/// @sa SetStockSpindleMode()
	virtual StockSpindleMode MWMSV_API GetStockSpindleMode() const = 0;

	/// This method is only useful for integrations that use STOCK_SPINDLE_AUTO_SELECT.
	///
	/// As explained in @ref SetStockSpindleMode, mwMachSimVerifier tries to guess whether the
	/// spindle should currently be ON or OFF. That means, it can decide to leave the spindle
	/// enabled, even though the stock is not rotationally symmetric.
	///
	/// This method "resets" the heuristic, which makes sure that the spindle is only enabled if the
	/// stock really is rotationally symmetric.
	///
	/// - The stock will stay in milling-mode until the first lathe-cut hits the stock.
	/// - This method is called automatically, when OnSimulationEnded() is called.
	virtual void MWMSV_API ResetStockSpindleAutoMode() = 0;

	typedef ::VerifierUtil::StockSpindleAxis StockSpindleAxis;
	static const StockSpindleAxis STOCK_SPINDLE_X_AXIS = ::VerifierUtil::STOCK_SPINDLE_X_AXIS;
	static const StockSpindleAxis STOCK_SPINDLE_Y_AXIS = ::VerifierUtil::STOCK_SPINDLE_Y_AXIS;
	static const StockSpindleAxis STOCK_SPINDLE_Z_AXIS = ::VerifierUtil::STOCK_SPINDLE_Z_AXIS;

	/// Set rotary axis for the stock, which has to be one of the main axes X, Y or Z.
	///
	/// It defines the axis, around which the stock rotates infinitely fast.
	/// Make sure to call this after stock initialization:
	///  SetStockCube()
	///  SetStockCylinder()
	///  SetMesh()).
	/// Those methods will try to detect the rotary axis and overwrite it, if found.
	/// It is usually only required to set the rotation axis if you want to enable the spindle for a
	/// non-revolved stock, or if there are multiple symmetry axes.
	///
	/// By default the stock is revolved around a line through (0, 0, 0). Which point on the axis
	/// you choose makes no difference.
	virtual void MWMSV_API SetStockSpindleAxis(
		const StockSpindleAxis direction, const float3d& position = float3d(0, 0, 0)) = 0;
	/// @sa SetStockSpindleAxis
	virtual StockSpindleAxis MWMSV_API GetStockSpindleAxis() const = 0;
	/// @sa SetStockSpindleAxis
	virtual float3d MWMSV_API GetStockSpindlePosition() const = 0;

	/// @deprecated Please use StockSpindleAxis.
	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	typedef ::VerifierUtil::TurningRotaryAxis TurningRotaryAxis;
	static const TurningRotaryAxis X_AXIS = ::VerifierUtil::X_AXIS;
	static const TurningRotaryAxis Y_AXIS = ::VerifierUtil::Y_AXIS;
	static const TurningRotaryAxis Z_AXIS = ::VerifierUtil::Z_AXIS;

	/// @deprecated Please use SetStockSpindleAxis().
	MW_DEPRECATED("Please use SetStockSpindleAxis() instead.")
	virtual void MWMSV_API SetTurningRotaryAxis(const TurningRotaryAxis newAxis) = 0;

	/// @deprecated Please use GetStockSpindleAxis().
	MW_DEPRECATED("Please use GetStockSpindleAxis() instead.")
	virtual TurningRotaryAxis MWMSV_API GetTurningRotaryAxis() const = 0;

	/// Spindle mode used in SetTurningSpindleMode()
	typedef ::VerifierUtil::TurningSpindleMode TurningSpindleMode;
	static const TurningSpindleMode TURNING_SPINDLE_OFF = ::VerifierUtil::TURNING_SPINDLE_OFF;
	static const TurningSpindleMode TURNING_SPINDLE_ON = ::VerifierUtil::TURNING_SPINDLE_ON;
	static const TurningSpindleMode TURNING_SPINDLE_AUTO_SELECT =
		::VerifierUtil::TURNING_SPINDLE_AUTO_SELECT;

	/// @deprecated Please use SetStockSpindleMode().
	MW_DEPRECATED("Please use SetStockSpindleMode() instead.")
	virtual void MWMSV_API SetTurningSpindleMode(const TurningSpindleMode spindleMode) = 0;

	/// @deprecated Please use GetStockSpindleMode().
	MW_DEPRECATED("Please use GetStockSpindleMode() instead.")
	virtual TurningSpindleMode MWMSV_API GetTurningSpindleMode() const = 0;

	/// @deprecated Please use ResetStockSpindleAutoMode().
	MW_DEPRECATED("Please use ResetStockSpindleAutoMode instead.")
	virtual void MWMSV_API ResetTurningSpindleAutoMode() = 0;
	MW_WARNING_POP

	/// Returns true if the stock is symmetric around the current spindle axis. This check is
	/// usually not fast enough to do it after every cut.
	///
	/// @note
	/// - This check is not exact, there are cases where the stock is reported as "revolved"
	///   even when it's not. This also affects internal usage like spindle-auto-mode and @ref
	///   OnSimulationEnded().
	/// - If the asymmetry is less than the precision set via @ref SetPrecision() then this check
	///   may still return "true".
	/// - If the asymmetry affects only a small amount of nails, then this check may also return
	///   "true".
	/// - Technical details: this check currently ignores nails that are parallel to the stock
	///   spindle direction. That means, for example, if you have a cylindrical stock and "scratch"
	///   the surface of the caps then that could cause the stock to be non-symmetric. Still, this
	///   check will return "true". "Scratch" here means "cutting with a depth less than the
	///   precision".
	virtual bool MWMSV_API GetStockIsRotationalSymmetric() = 0;

	typedef std::list<cadcam::mw2dfPolyLine> PolyLineList;
	typedef misc::mwAutoPointer<PolyLineList> PolyLineListPtr;

	/// Returns a list of polylines describing the profile of the fast rotating stock
	///
	/// - The polyline is defined in (x,y), where y is >.
	/// - The polyline is oriented in mathematical positive sense (counter-clockwise when seen from
	///   +z).
	/// - The polyline is always defined in a local turning system, where the turning axis is x = 0.
	/// - The result contains one polyline for each disconnected part of the stock.
	/// - It also contains multiple polylines if the volume has holes. Polylines describing holes
	///   are currently not marked.
	/// - This function is only supported for the 5axis data model, that is MWV_FM_DEXELBLOCK, see
	///   ForceDataModel().
	///
	/// The polylines are reduced before being returned. Collinear points are eliminated using the
	/// @p reductionTolerance. That is p1p2 and p1p3 are collinear if and only if p2's distance to
	/// p1p2 is smaller than reductionTolerance. For mathdef::MW_MIN_FLOAT this tolerance is
	/// computed automatically based on the stock's size. If reductionTolerance is 0, no reduction
	/// is performed. This may result in polylines with a lot of segments.
	virtual PolyLineListPtr MWMSV_API
	GetRotationalProfileLinearized(const float reductionTolerance = mathdef::MW_MIN_FLOAT) = 0;

	typedef cadcam::mw2dfContour Contour;
	typedef std::list<Contour> ContourList;
	typedef misc::mwAutoPointer<ContourList> ContourListPtr;

	/// Returns a list of contours describing the profile of the fast rotating stock
	///
	/// The contours are generated by fitting arcs into the polylines returned by @ref
	/// GetRotationalProfileLinearized().
	virtual ContourListPtr MWMSV_API
	GetRotationalProfile(const float reductionTolerance = mathdef::MW_MIN_FLOAT) = 0;

	/// Set initial stock geometry for a contour.
	///
	/// - The internally saved list of cuts and tools is freed.
	/// - The last active tools are preserved (see SetTools()).
	///
	/// @param [in] profile the 2d contour of the stock.
	/// @param [in] axis    the axis around which the contour is revolved
	/// @param [in] lowerAdditiveBoxCorner Position of the lower corner of the space for additive
	/// manufacturing.
	/// @param [in] upperAdditiveBoxCorner Position of the upper corner of the space for additive
	/// manufacturing.
	virtual void MWMSV_API SetStockRevolved(
		const cadcam::mw2dfContour& profile,
		StockSpindleAxis axis,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;
	/// @}

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	/// @deprecated Please use SetStockRevolved() instead.
	MW_DEPRECATED("TurningRotaryAxis is deprecated. Please use StockSpindleAxis instead.")
	virtual void MWMSV_API SetStockRevolved(
		const cadcam::mw2dfContour& profile,
		TurningRotaryAxis axis,
		const float3d& lowerAdditiveBoxCorner = float3d(),
		const float3d& upperAdditiveBoxCorner = float3d()) = 0;
	MW_WARNING_POP

	/// @name Target volumes
	/// Targets are meshes that describe the desired shape of the workpiece after the simulation.
	/// mwMachSimVerifier offers deviation color schemes, as well as deviation reports against the
	/// target.
	///
	/// @{

	/// Sets a target mesh for comparison with the current stock.
	///
	/// Since we need to create an internal lookup structure this will kick off an internal thread
	/// which computes it. mwMachSimVerifier blocks when it is first needed, for example when
	/// calling @ref GetGougeList(). Therefore it can be a good idea to set the target even before
	/// it's needed.
	///
	/// Gouge and excess threshold for the given target will be applied based on the current default
	/// thresholds (see SetGougeThreshold and SetExcessThreshold). Overriding them later is
	/// possible; doing so will automatically invalidate the gouge/excess and deviation color
	/// schemes.
	///
	/// @attention The mesh should ideally represent a volume, meaning that the mesh is closed.
	/// The comparison algorithm can handle open meshes to some extend, but often fails to decide if
	/// a point is inside or outside the target volume; gouges may wrongly become excesses and vice
	/// versa.
	///
	/// If @p bTryToCloseBorders is true, then open borders and regions which have overhanging parts
	/// are closed by projecting them down to the minimal z value of the mesh. In effect, only the
	/// top-projection of the mesh is used as a target. This is only supported for the 3-axis data
	/// model (@ref VerifierUtil::MWV_FM_FIELD).
	virtual MWV_ERRORCODE MWMSV_API SetTarget(MeshPtr pMesh, bool bTryToCloseBorders = true) = 0;

	/// @p id is the index in the target vector given via SetTargets().
	/// @see SetTarget, SetTargets
	virtual MeshPtr MWMSV_API GetTarget(const int id = 0) const = 0;

	/// Contains data of a target definition
	typedef ::VerifierUtil::TargetData TargetData;

	/// Sets multiple target meshes.
	///
	/// Like SetTarget(), but sets multiple target meshes. See SetTarget() for more details about
	/// the target meshes.
	///
	/// To determine whether a point is inside or outside we need to know whether the meshes are
	/// overlapping. Set @p expectOverlappingTargets to "true" if they are, otherwise to "false".
	/// When @p expectOverlappingTargets is "false" we can handle gaps in the target meshes a bit
	/// better.
	virtual MWV_ERRORCODE MWMSV_API SetTargets(
		const std::vector<mwMachSimVerifier::TargetData>& targets,
		bool tryToCloseBorders = true,
		bool expectOverlappingTargets = false) = 0;

	virtual void MWMSV_API ClearTargets() = 0;

	/// Decide whether the target mesh(es) should be shown in @ref Draw().
	///
	/// There are independent global and an individual visibility flags. A target will only be
	/// visible if both global and individual target visibility is "true". By default global
	/// visibility is "false", and individual visibility is "true".
	///
	/// @param [in] visible If true, target should be drawn
	/// @param [in] id index in the target vector (-1: change global visibility)
	virtual MWV_ERRORCODE MWMSV_API SetTargetVisibility(bool visible, const int id = -1) = 0;

	/// @see SetTargetVisibility().
	virtual bool MWMSV_API GetTargetVisibility(const int id = -1) const = 0;

	/// Sets the color of the target mesh, the default is red
	///
	/// @param [in] r color red value between 0 and 1.
	/// @param [in] g color green value between 0 and 1.
	/// @param [in] b color blue value between 0 and 1.
	/// @param [in] a color alpha value between 0 and 1.
	/// @param [in] id index in the target vector (-1: change all targets)
	virtual void MWMSV_API
	SetTargetColor(float r, float g, float b, float a, const int id = -1) = 0;

	/// @see SetTargetColor
	virtual Color MWMSV_API GetTargetColor(int id) const = 0;

	virtual size_t MWMSV_API GetTargetCount() const = 0;

	/// Use this function to update the internal model. This is automatically done when they
	/// are needed, during Draw(), GetGougeList() or GetExcessList(), so it's not _required_ to call
	/// this function.
	/// @note May abort via progress handler on user request.
	virtual void MWMSV_API CalculateGougeExcess() = 0;

	/// @sa SetDeviationOffset
	virtual float MWMSV_API GetDeviationOffset() const = 0;

	/// This applies a fixed offset to all deviation values. This has an effect on @ref GetGougeList
	/// and @ref GetExcessList, as well as the WDM_DEVIATION_OFFSET color scheme. It does not affect
	/// the MWV_CS_DEVIATION color scheme.
	///
	/// This has the same effect as offsetting the target mesh would: setting a deviation value > 0
	/// makes the target larger.
	virtual void MWMSV_API SetDeviationOffset(float value) = 0;

	/// @param [in] id index in the target vector (-1: returns default threshold)
	virtual float MWMSV_API GetGougeThreshold(const int id = -1) const = 0;

	/// Only gouges larger than this threshold are returned in @ref GetGougeList().
	///
	/// @param [in] id index in the target vector (-1: change all targets and default threshold)
	virtual void MWMSV_API SetGougeThreshold(float value, const int id = -1) = 0;

	/// @param [in] id index in the target vector (-1: returns default threshold)
	virtual float MWMSV_API GetExcessThreshold(const int id = -1) const = 0;

	/// Only gouges larger than this threshold are returned in @ref GetGougeList().
	///
	/// @param [in] id index in the target vector (-1: change all targets and default threshold)
	virtual void MWMSV_API SetExcessThreshold(float value, const int id = -1) = 0;

	/// Shows/hide gouge labels in @ref Draw().
	virtual void MWMSV_API ShowGougeLabels(bool isShow) = 0;

	/// Shows/hide excess labels in @ref Draw().
	virtual void MWMSV_API ShowExcessLabels(bool isShow) = 0;

	/// @see ShowGougeLabels
	virtual bool MWMSV_API GetShowGougeLabels() = 0;

	/// @see ShowExcessLabels
	virtual bool MWMSV_API GetShowExcessLabels() = 0;

	/// Contains data for gouge or excess reports
	typedef ::VerifierUtil::GougeReport GougeReport;

	/// By default we measure the shortest distance between stock and target. If Z gouges are
	/// enabled, we instead calculate the distance in Z direction.
	///
	/// This is implemented only for the 3-axis model (MWV_FM_FIELD), and it affects both gouge and
	/// excess values.
	virtual void MWMSV_API EnableZGouge(bool enabled) = 0;

	/// @see EnableZGouge().
	virtual bool MWMSV_API IsZGougeEnabled() const = 0;

	/// Sets the maximum number of gouges/excesses that are returned via @ref GetGougeList() or @ref
	/// GetExcessList(). We return the first @p maxSize elements in the sorted list (see @ref
	/// SetGougeReportMode).
	///
	/// By default we return up to 100 gouges/excesses. @p maxSize must be >= 0.
	virtual void MWMSV_API SetMaxGougeExcessReportSize(int maxSize) = 0;

	/// @see SetMaxGougeExcessReportSize
	virtual int MWMSV_API GetMaxGougeExcessReportSize() const = 0;

	/// GougeExcessReportMode used in SetGougeReportMode() and SetExcessReportMode()
	typedef ::VerifierUtil::GougeExcessReportMode GougeExcessReportMode;
	static const GougeExcessReportMode REPORT_BLOCK_NUMBER_INCREASING =
		::VerifierUtil::REPORT_BLOCK_NUMBER_INCREASING;
	static const GougeExcessReportMode REPORT_DEVIATION_INCREASING =
		::VerifierUtil::REPORT_DEVIATION_INCREASING;
	static const GougeExcessReportMode REPORT_DEVIATION_DECREASING =
		::VerifierUtil::REPORT_DEVIATION_DECREASING;
	static const GougeExcessReportMode REPORT_ALL = ::VerifierUtil::REPORT_ALL;

	/// Choose how gouges are sorted.
	///
	/// Keep in mind that only the first N gouges/excesses are reported (see @ref
	/// SetMaxGougeExcessReportSize()).
	///
	/// - REPORT_BLOCK_NUMBER_INCREASING - gouge list includes values starting from the beginning of
	/// a toolpath.
	/// - REPORT_DEVIATION_INCREASING - gouge list includes smallest values from the gouge report.
	/// - REPORT_DEVIATION_DECREASING - gouge list includes biggest values from the gouge report.
	/// - REPORT_ALL - all gouges will be output to the gouge list.
	virtual void MWMSV_API SetGougeReportMode(const GougeExcessReportMode& gougeReportMode) = 0;

	/// @sa SetGougeReportMode
	virtual GougeExcessReportMode MWMSV_API GetGougeReportMode() const = 0;

	/// Choose how excesses are sorted.
	///
	/// Keep in mind that only the first N gouges/excesses are reported (see @ref
	/// SetMaxGougeExcessReportSize()).
	///
	/// - BLOCK_NUMBER_INCREASING - excess list includes values starting from the beginning of a
	/// toolpath.
	/// - DEVIATION_INCREASING - excess list includes smallest values from the excess report.
	/// - DEVIATION_DECREASING - excess list includes biggest values from the excess report.
	/// - ALL - all excesses will be output to the excess list.
	virtual void MWMSV_API SetExcessReportMode(const GougeExcessReportMode& excessReportMode) = 0;

	/// @sa SetExcessReportMode
	virtual GougeExcessReportMode MWMSV_API GetExcessReportMode() const = 0;

	/// @deprecated Please use SetGougeThreshold(float); list = GetGougeList(); instead.
	///
	/// Retrieve a list of gouges from the current stock, with a threshold including the offset.
	///
	/// The value in minIgnoredGouge is meant absolute to the target surface, when an offset is
	/// active the current offset value needs to be set in SetDeviationOffset() and must be added
	/// to the value given (minIgnoredGouge = gougethreshold + deviationoffset)
	///
	/// @deprecated Because of unclear connection between  minIngnoredGouge and global gouge
	/// Threshold. Please use the new GetGougeList() method.
	///
	/// @param [in] minIgnoredGouge all values below that threshold will be reported. This value
	/// also changes the internal gouge value (see SetGougeThreshold)
	MW_DEPRECATED("Use SetGougeThreshold(minIgnoredGouge); list = GetGougeList(); instead.")
	virtual MWV_ERRORCODE MWMSV_API
	GetGougeList(float minIgnoredGouge, std::vector<GougeReport>& list) = 0;

	/// @deprecated Please use SetExcessThreshold(float); list = GetExcessList(); instead.
	///
	/// Retrieve a list of excesses from the current stock, with a threshold including the offset.
	///
	/// The value in maxIgnoredExcess is meant absolute to the target surface, when an offset is
	/// active the current offset value needs to be set in SetDeviationOffset() and must be added
	/// to the value given (minIgnoredGouge = excessthreshold + deviationoffset)
	///
	/// @deprecated Because of unclear connection between maxIgnoredExcess and global excess
	/// threshold. Please use the new GetExcessList() method.
	///
	/// @param [in] maxIgnoredExcess all values bigger will be be reported This value also changes
	/// the internal excess value (see SetExcessThreshold)
	MW_DEPRECATED("Use SetExcessThreshold(maxIgnoredExcess); list = GetExcessList(); instead.")
	virtual MWV_ERRORCODE MWMSV_API
	GetExcessList(float maxIgnoredExcess, std::vector<GougeReport>& list) = 0;

	/// Retrieve a list of gouges from the current stock.
	///
	/// This call uses the values given in SetGougeThreshold() and SetDeviationOffset().
	virtual std::vector<GougeReport> MWMSV_API GetGougeList() = 0;

	/// Retrieve a list of excesses from the current stock.
	///
	/// This call uses the values given in SetExcessThreshold() and SetDeviationOffset().
	virtual std::vector<GougeReport> MWMSV_API GetExcessList() = 0;

	/// @}

	/// @name Chunk Detection
	/// Detection and operations with stock chunks. A chunk is a piece of the stock which is
	/// separated from other chunks by spatial gaps.
	/// @{

	typedef ::VerifierUtil::mwvChunkDetectionHandler mwvChunkDetectionHandler;

	/// Predefined handler for mwMachSimVerifier::EnableIncrementalChunkDetection that removes
	/// non-fixed parts of the stock, i.e. parts that would fall down if cut off.
	///
	/// Usage:
	/// @code
	/// std::vector<float3d> fixturePoints;
	/// fixturePoints.push_back(float3d(1, 2, 3));
	/// const float equalTol = 1.0e-3f;
	/// verifier.EnableIncrementalChunkDetection(
	/// 	new mwvChunkDetectionKeepHandler(fixturePoints, equalTol));
	/// @endcode
	typedef ::VerifierUtil::mwvChunkDetectionKeepHandler mwvChunkDetectionKeepHandler;

	/// @return current number of chunks.
	///
	/// Detects and re-marks the chunks with the ids as an uninterrupted sequence starting with 1.
	/// The first chunk with id 1 is a currently biggest chunk, next chunks are sorted primarily by
	/// size and secondarily by position.
	///
	/// In comparison to GetChunks() disards the previous ids.
	///
	/// # Performance
	///
	/// The first call to this method is computationally expensive, when the
	/// initial chunk detection is run. As long as no complete recompute
	/// is run, subsequent calls are fast and deliver updated or cached results.
	virtual size_t MWMSV_API MarkChunks() = 0;

	/// @return current number of chunks.
	///
	/// Triggers the detection if needed. Tries to keep previos ids of chunks.
	///
	/// Performance: see MarkChunks()
	virtual size_t MWMSV_API GetChunks(std::vector<int>& chunkIds) = 0;

	/// Triggers the detection if needed, see GetChunks()
	virtual size_t MWMSV_API GetNumberOfChunks() = 0;

	/// @return number of chunks found around the given positions.
	///
	/// Triggers the detection if needed, see GetChunks()
	virtual size_t MWMSV_API FindChunksAtPositions(
		const std::vector<float3d>& positions,
		const float tolerance,
		std::vector<int>& foundChunks) = 0;

	/// @return number of deleted chunks (either 0 or 1).
	///
	/// Triggers the detection if needed, see GetChunks(). The ids of other chunks remain unchanged.
	virtual size_t MWMSV_API DeleteChunk(int chunkID) = 0;

	/// @return number of deleted chunks.
	///
	/// Triggers the detection if needed, see GetChunks(). The ids of other chunks remain unchanged.
	virtual size_t MWMSV_API DeleteChunks(const std::vector<int>& chunkIDs) = 0;

	/// @return number of deleted chunks.
	///
	/// @p equalTolerance defines the maximal distance of chunks from @p fixturePoints for which
	/// they are considered touching. That is, the points can be considered as spheres with radius
	/// equalTolerance. Currently the tolerance cannot be lower than precision, see SetPrecision().
	/// If it is smaller, it is set to precision.
	///
	/// Triggers the detection if needed, see GetChunks(). The ids of other chunks remain unchanged.
	virtual size_t MWMSV_API DeleteChunksNotTouching(
		const std::vector<float3d>& fixturePoints, const float equalTolerance) = 0;

	/// @copydoc DeleteChunksNotTouching
	virtual size_t MWMSV_API
	DeleteChunksTouching(const std::vector<float3d>& points, const float equalTolerance) = 0;

	/// Incremental chunks detection is performed automatically during cutting, see GetChunks()
	///
	/// To disable, call DisableIncrementalChunkDetection().
	///
	/// The @p handler is called when the number of chunks changes:
	/// - a cutoff occurred (stock is split into 2 or more parts);
	/// - some part of the stock was milled away completely.
	///
	/// If the given @p handler is a null pointer then incremental chunk detection is disabled.
	/// The @p handler can be used to react on new chunks. See an example
	/// @ref mwMachSimVerifier::mwvChunkDetectionKeepHandler.
	virtual void MWMSV_API
	EnableIncrementalChunkDetection(misc::mwAutoPointer<mwvChunkDetectionHandler> handler) = 0;

	/// @see EnableIncrementalChunkDetection
	virtual void MWMSV_API DisableIncrementalChunkDetection() = 0;

	virtual bool MWMSV_API IsIncrementalChunkDetectionEnabled() const = 0;
	/// @}

	/// @name  Simulation tolerances
	/// Simulation tolerances should be set based on the accuracy of the input data, and based on
	/// the desired simulation accuracy. In most cases you don't want to set the tolerances to a
	/// value smaller than the error in the generated toolpath.
	///
	/// Setting the collision tolerances too small may easily cause collision reports you're not
	/// interested in, either because the collision is introduced by the approximation, or because
	/// it is too small to matter in the real world.
	///
	/// Setting the cutting tolerance too small means that the simulation takes much longer, even
	/// though the increase in quality may not be required.
	///
	/// Simulation tolerances can can be updated at any time. They influence the simulation of all
	/// cuts performed afterwards. Changing the collision tolerance when changing the current tool
	/// (SetCurrentCutTool) is quite cheap. However, using different tolerances for cuts with the
	/// same tool can be expensive, since many tool-specific structures have to be reset.
	/// @{

	/// @sa SetCuttingTolerance
	const virtual float MWMSV_API GetCuttingTolerance() const = 0;

	/// The cutting tolerance defines how close the simulated cuts need to be to the real,
	/// analytical cuts. It is used for all operations with tools, including cutting, adding
	/// and collision checking.
	///
	/// To avoid false collisions, it is recommended to keep the cutting tolerance constant for
	/// consecutive operations working in the same area of a stock (including collision checked
	/// moves).
	///
	/// A tolerance of 0 means that it is disabled and internally an automatic tolerance will be
	/// chosen based on the stock size.
	///
	/// Usually the accuracy is much smaller than the cutting tolerance. Internally it will have
	/// only an effect on some algorithms, including:
	///
	/// - 5axis cutting algorithms
	/// - mesh tool algorithms
	/// - revolved bullnose mills
	/// - revolved tools with arcs in the profile, that are not exactly 90°
	/// - circular moves (e.g. @ref VerifierUtil::mwCircularMove)
	///
	/// For revolved tools and 5-axis moves, it is only used to ensure precise cutting with the tool
	/// tip. If you cut using higher parts of the tool, for example during a swarfing process,
	/// results are usually not within the tolerance. If you need accuracy for these kinds of
	/// operations, you can enable a precise mode using @ref mwvToolBehavior::Set5AxisCuttingToleranceMode().
	///
	/// Note that the simulation accuracy is also limited by the _precision_ (see @ref
	/// SetPrecision()). If the precision is too large you may miss details on the stock because we
	/// didn't use enough sample points. If the cutting tolerance is too large then even the
	/// generated sample points may be too far from the (theoretical) real result. This especially
	/// affects collision checking, gouge & excess reports and point picking.
	virtual void MWMSV_API SetCuttingTolerance(const float tol) = 0;

	/// Used to avoid the creation of very thin features/walls in the simulation process. If a
	/// feature thinner than the tolerance would be created, it will be removed instead. This
	/// tolerance affects all stock changing operations, including @ref SetStock().
	///
	/// The thickness is measured along the main axes X, Y, Z. So to avoid thin diagonal walls, the
	/// tolerance must be enlarged by about sqrt(2) times.
	///
	/// @warning Use with caution! This tolerance may cause speed regressions or unwanted surface
	/// defects, if set too big. It should always stay within a small fraction of the stock
	/// accuracy, see @ref SetPrecision(). Also: It is expected to set this tolerance once before
	/// each simulation (usually the SetStock() call). Changing it over time may have unexpected
	/// results, especially when combined with Refine().
	///
	/// @param tol If set to >= 0, will overwrite the internally computed tolerance. Set to -1 to
	/// deactivate again.
	virtual void MWMSV_API SetThinVolumeTolerance(const float tol) = 0;
	/// See @ref SetThinVolumeTolerance()
	const virtual float MWMSV_API GetThinVolumeTolerance() const = 0;

	/// Set tolerance for non-rapid collision checks, to avoid false collisions.
	/// Internally this usually means, that the tool is shrinked to
	/// ignore collisions with a penetration depth smaller than the tolerance.
	/// This tolerance does not control the accuracy of a collision check,
	/// use @ref SetCuttingTolerance() for that.
	///
	/// - This tolerance is used if the tool behavior is set to "collision-checked", but not to
	/// "rapid".
	/// @sa SetToolBehavior()
	/// @sa SetRapidMode()
	/// - It applies to all tools and is preserved across SetTools() calls.
	/// - The tool may dive into the material by up to this tolerance before a collision is
	/// reported.
	/// - If not set by SetCollisionTolerance(), an automatic value is computed depending on the
	/// stock size. This auto-generated value can be selected explicitly by calling
	/// SetCollisionTolerance(mathdef::MW_MAX_FLOAT).
	/// - Collision tolerances are not supported for mesh solids. Those are always simulated without
	/// tolerances.
	///
	/// @warning Make sure that cuts are not shorter than this tolerance! Otherwise collisions may
	/// get lost.
	/// @warning Make sure, that this tolerance is smaller than radius and height/2 of all
	/// tool elements in use! Otherwise collisions may get lost.
	virtual void MWMSV_API SetCollisionTolerance(const float tol) = 0;
	/// @sa SetCollisionTolerance
	const virtual float MWMSV_API GetCollisionTolerance() const = 0;

	/// Set collision tolerance for just the flute (cutting part). @sa SetCollisionTolerance
	virtual void MWMSV_API SetFluteCollisionTolerance(const float tol) = 0;
	/// @sa SetCollisionTolerance
	const virtual float MWMSV_API GetFluteCollisionTolerance() const = 0;

	/// Set collision tolerance for just the shaft (non-cutting part). @sa SetCollisionTolerance
	virtual void MWMSV_API SetShaftCollisionTolerance(const float tol) = 0;
	/// @sa SetCollisionTolerance
	const virtual float MWMSV_API GetShaftCollisionTolerance() const = 0;

	/// Set collision tolerance for just the arbor. @sa SetCollisionTolerance
	virtual void MWMSV_API SetArborCollisionTolerance(const float tol) = 0;
	/// @sa SetCollisionTolerance
	const virtual float MWMSV_API GetArborCollisionTolerance() const = 0;

	/// Set collision tolerance for just the holder. @sa SetCollisionTolerance
	virtual void MWMSV_API SetHolderCollisionTolerance(const float tol) = 0;
	/// @sa SetCollisionTolerance
	const virtual float MWMSV_API GetHolderCollisionTolerance() const = 0;

	/// Set tolerance for collision checks of rapid moves
	///
	/// - Usually it is not required to change this tolerance, because false rapid collisions are
	/// mainly handled by SetRapidAccelerationTolerance().
	/// - This tolerance is used if the tool behavior is set to "rapid".
	/// @sa SetRapidMode()
	/// - It applies to all tool elements.
	/// - There is one exception, where the collision tolerance (see SetCollisionTolerance()) is
	/// used: Retracting rapid moves of revolved tools. This is to avoid false collisions for
	/// retraction, where the tool touches the material.
	///
	/// @warning Make sure that retractions are not shorter than this tolerance! Otherwise
	/// collisions may get lost.
	/// @warning Make sure, that this tolerance is smaller than radius and height/2 of all
	/// tool elements in use! Otherwise collisions may get lost.
	/// @sa SetRapidMode
	virtual void MWMSV_API SetRapidCollisionTolerance(const float tol) = 0;

	/// @sa SetRapidCollisionTolerance
	const virtual float MWMSV_API GetRapidCollisionTolerance() const = 0;

	/// Set a tolerance for the acceleration phase of rapid moves
	///
	/// @sa SetRapidMode
	/// - If a tool starts moving rapidly, it usually accelerates. In this acceleration phase, the
	/// tool is treated as cutting, that is no collisions are reported. This is to avoid false
	/// collisions.
	/// - If not set, the collisionTolerance is used (but at least a value of 1/10000 of
	/// stock-size).
	virtual void MWMSV_API SetRapidAccelerationTolerance(const float tol) = 0;

	/// @sa SetRapidAccelerationTolerance
	const virtual float MWMSV_API GetRapidAccelerationTolerance() const = 0;

	/// Get tolerance for the initial stock, which may have been given as triangle-mesh.
	///
	/// - It assures, that e.g. turning-simulation can detect rotational symmetric stocks to speed
	/// up turning-simulation, but it is also used for other purposes.
	/// - It has to be bigger than 0.
	///
	/// @deprecated This function is not useful unless the deprecated @ref
	/// SetInitialStockTolerance() is used.
	MW_DEPRECATED(
		"This function is not useful unless the deprecated SetInitialStockTolerance is used.")
	const virtual float MWMSV_API GetInitialStockTolerance() const = 0;

	/// Set tolerance for initial mesh stocks. If not called explicitly, an automatic value based on
	/// the size of the mesh is guessed. To reset to this auto-mode, pass a value of
	/// mathdef::MW_MAX_FLOAT.
	///
	/// @deprecated Please use meshTolerance parameter of @ref SetMesh() instead of this method!
	MW_DEPRECATED("Please set the tolerance via SetMesh/SetMeshes instead.")
	virtual void MWMSV_API SetInitialStockTolerance(const float tol) = 0;

	/// Set safety distance for all tool elements
	///
	/// The safety distance ensures a certain distance between tool elements and workpiece.
	/// - If the distance is not maintained an error code will be reported.
	/// - @ref VerifierUtil::mwvToolElementBehavior::IsSafetyDistanceChecked has to be set to "true"
	///   to enable this check.
	virtual void MWMSV_API SetSafetyDistance(const float tol) = 0;

	/// @see SetSafetyDistance().
	const virtual float MWMSV_API GetSafetyDistance() const = 0;

	/// Set the safety distance for just the flute (cutting part) @sa SetSafetyDistance()
	virtual void MWMSV_API SetFluteSafetyDistance(const float tol) = 0;

	/// @see SetFluteSafetyDistance
	const virtual float MWMSV_API GetFluteSafetyDistance() const = 0;

	/// Set the safety distance for just the shaft (non-cutting part) @sa SetSafetyDistance()
	virtual void MWMSV_API SetShaftSafetyDistance(const float tol) = 0;

	/// @see SetShaftSafetyDistance
	const virtual float MWMSV_API GetShaftSafetyDistance() const = 0;

	/// Set the safety distance for just the arbor @sa SetSafetyDistance()
	virtual void MWMSV_API SetArborSafetyDistance(const float tol) = 0;

	/// @see SetArborSafetyDistance
	const virtual float MWMSV_API GetArborSafetyDistance() const = 0;

	/// Set the safety distance for just the holder @sa SetSafetyDistance()
	virtual void MWMSV_API SetHolderSafetyDistance(const float tol) = 0;

	/// @see SetHolderSafetyDistance
	const virtual float MWMSV_API GetHolderSafetyDistance() const = 0;

	/// @deprecated This method was renamed to @ref GetCuttingTolerance().
	MW_DEPRECATED("Use GetCuttingTolerance() instead")
	const virtual float MWMSV_API GetTargetTolerance() const = 0;

	/// @deprecated This method was renamed to @ref SetCuttingTolerance().
	MW_DEPRECATED("Use SetCuttingTolerance() instead")
	virtual void MWMSV_API SetTargetTolerance(const float tol) = 0;

	/// @}

	/// @name Simulation control
	/// @{

	/// Move the tool tip on a linear path. The tool orientation may change between start and end
	/// frame.
	///
	/// @return true if stock geometry has been changed or hit, false otherwise.
	virtual bool MWMSV_API Cut(const Frame& startFrame, const Frame& endFrame) = 0;

	/// Select one tool by index to be used in Cut(...) and BufferedCut(...). The index points into
	/// the tool vector that was given via the last @ref SetTools() call.
	///
	/// If only one tool was defined in SetTool() or SetTools(), then calling this method is not
	/// necessary. Calling those methods automatically sets the current cut tool index to 0.
	///
	/// @code
	/// verifier.SetTools({tool1, tool2, tool3, tool4});
	/// verifier.SetCurrentCutTool(1);
	/// verifier.Cut(...);  // will cut with tool2
	/// @endcode
	virtual void MWMSV_API SetCurrentCutTool(const size_t indexInArray) = 0;

	/// @see SetCurrentCutTool()
	virtual size_t MWMSV_API GetCurrentCutToolIndex() const = 0;

	/// @see SetCurrentCutTool()
	virtual cadcam::mwConstToolPtr MWMSV_API GetCurrentCutTool() const = 0;

	/// Returns the last end frame of the currently selected cut tool.
	virtual Frame MWMSV_API GetCurrentCutToolPosition() const = 0;

	/// An mwvMoveFinishedHandler is called whenever a verifier move was performed. The given
	/// handler is added to an internal list, so registering multiple handlers is possible.
	///
	/// The handler must stay alive until the verifier is destructed, or until @ref
	/// UnregisterMoveFinishedHandler is called.
	virtual void MWMSV_API
	RegisterMoveFinishedHandler(VerifierUtil::mwvMoveFinishedHandler* moveFinishedHandler) = 0;

	/// @see RegisterMoveFinishedHandler
	virtual void MWMSV_API
	UnregisterMoveFinishedHandler(VerifierUtil::mwvMoveFinishedHandler* moveFinishedHandler) = 0;

	typedef ::VerifierUtil::VerificationCodes VerificationCodes;
	static const VerificationCodes VC_NO_ERROR = ::VerifierUtil::VC_NO_ERROR;
	static const VerificationCodes VC_RAPIDEDGE_CRASH = ::VerifierUtil::VC_RAPIDEDGE_CRASH;
	static const VerificationCodes VC_NCEDGE_CRASH = ::VerifierUtil::VC_NCEDGE_CRASH;
	static const VerificationCodes VC_ARBOR_CRASH = ::VerifierUtil::VC_ARBOR_CRASH;
	static const VerificationCodes VC_HOLDER_CRASH = ::VerifierUtil::VC_HOLDER_CRASH;
	static const VerificationCodes VC_FLUTE_SAFETY_DISTANCE_CRASH =
		::VerifierUtil::VC_FLUTE_SAFETY_DISTANCE_CRASH;
	static const VerificationCodes VC_SHAFT_SAFETY_DISTANCE_CRASH =
		::VerifierUtil::VC_SHAFT_SAFETY_DISTANCE_CRASH;
	static const VerificationCodes VC_ARBOR_SAFETY_DISTANCE_CRASH =
		::VerifierUtil::VC_ARBOR_SAFETY_DISTANCE_CRASH;
	static const VerificationCodes VC_HOLDER_SAFETY_DISTANCE_CRASH =
		::VerifierUtil::VC_HOLDER_SAFETY_DISTANCE_CRASH;

	/// Returns the collision result of the last cut that was performed using the non-buffered API
	/// (@ref Cut(), @ref CircularCut() etc).
	///
	/// The result is a bitwise OR of symbols in @ref VerifierUtil::VerificationCodes.
	///
	/// Note that this code is not updated when using any of the buffered APIs, like @ref
	/// BufferedCut() or @ref BufferedCircularCut().
	///
	/// You can also use GetVerificationResult(VerificationResult&) to get more detailed
	/// information.
	unsigned virtual int MWMSV_API GetVerificationResult() const = 0;

	typedef ::VerifierUtil::VerificationResult VerificationResult;

	/// Returns the collision result of the last cut that was performed using the non-buffered API
	/// (@ref Cut(), @ref CircularCut() etc).
	///
	/// See @ref VerifierUtil::VerificationResult for the results that are included.
	///
	/// Note that this code is not updated when using any of the buffered APIs, like @ref
	/// BufferedCut() or @ref BufferedCircularCut().
	virtual void MWMSV_API GetVerificationResult(VerificationResult& verificationResult) const = 0;

	/// This disables internal optimizations. That makes sure that @ref
	/// VerifierUtil::VerificationResult::DidRemoveMaterial and @ref
	/// VerifierUtil::VerificationResult::DidAddMaterial are filled correctly, but simulation speed
	/// may decrease.
	virtual void MWMSV_API ForceCorrectMaterialRemovalFlag(bool flag) = 0;

	/// @see ForceCorrectMaterialRemovalFlag
	virtual bool MWMSV_API GetForceCorrectMaterialRemovalFlag() const = 0;

	typedef std::vector<VerificationResult> VerificationResultVector;

	/// Like Cut() but does not simulate immediately. Call SimulateBufferedCuts() to actually
	/// simulate it.
	///
	/// @copydoc Cut
	virtual void MWMSV_API BufferedCut(const Frame& startFrame, const Frame& endFrame) = 0;

	/// Simulate all recently buffered cuts.
	///
	/// Purpose: Simulate packages of more than one cut at once, to get better performance. Many
	/// optimizations are enabled by this:
	///
	/// - The verifier can interleave moves, to keep the worker threads busy
	/// - The sweep volumes of adjacent moves can often be joined, since the verifier knows the
	/// next,
	///  connecting move.
	///
	/// This method is blocking and returns a list of verification-results.
	///
	/// It will call progressHandler.SetPos(), if a progress handler is given (see
	/// @ref SetProgressHandler()).
	///
	/// It can be canceled using the progress handler. It will return to a valid state and return
	/// the results for the number of cuts, that were done before the abort. The next call to
	/// @ref SimulateBufferedCuts() will simulate the remaining buffered cuts.
	///
	/// The best overall (fast-forward) simulation time is usually achieved when buffering between
	/// 500 and 5000 moves.
	///
	/// @image html "../dox/SimulateBufferedCut()_size.png"
	///
	/// @param [out] verificationResults vector with the same size as the number of simulated
	/// buffered cuts (cuts buffered since the last call to @ref SimulateBufferedCuts()). If
	/// @ref SimulateBufferedCuts() was aborted using a progress handler (see @ref
	/// SetProgressHandler()), the vector might be smaller. `verificationResults[i]` is the result
	/// for the `i`'th buffered cut (beginning with 0).
	virtual void MWMSV_API SimulateBufferedCuts(VerificationResultVector& verificationResults) = 0;

	/// Discard all buffered cuts that were added since the last @ref SimulateBufferedCuts() call.
	virtual void MWMSV_API DiscardBufferedCuts() = 0;

	/// Disable internal storage of cuts.
	///
	/// Disabling cut storage can reduce memory consumption significantly if a huge number of cuts
	/// are passed. This usually applies to fine interpolated cuts in a time-based simulation, or
	/// to CNC real time simulations. Note: some features will not be available and an exception
	/// will be thrown, if they are used together with NoCutHistory. Affected features are:
	/// - ColorSchemes relying on the cut-history, e.g. move length
	/// - mwMachSimVerifier::IncreaseZoom(), mwMachSimVerifier::IncreaseZoomToBB()
	/// - everything related to stock refinement
	/// - picking move ids from stock, or retrieving the ids in any other way
	/// - EnableEngagementTracking(true) together with the mwvEngagementOptions::ContourBased
	///   algorithm
	virtual void MWMSV_API SetNoCutHistory(const bool b) = 0;

	/// @see SetNoCutHistory().
	virtual bool MWMSV_API GetNoCutHistory() const = 0;

	/// Enable the detection of chunks which collided with the current cut.
	///
	/// - You can get the results by calling GetCollidingChunks() after a cut.
	/// - This feature increases the time needed for tool collision-checking operations.
	virtual void MWMSV_API SetCollidingChunksEnabled(const bool enabled) = 0;

	/// See SetCollidingChunksEnabled().
	virtual bool MWMSV_API GetCollidingChunksEnabled() const = 0;

	typedef std::vector<int> ChunkIdVector;

	/// Lists of chunk-ids for each tool-element. If a chunk's id is e.g. in FluteCollisions, the
	/// flute collided with this chunk. See GetCollidingChunks().
	typedef ::VerifierUtil::ToolChunkCollisions ToolChunkCollisions;

	/// Returns a vector of colliding chunk-ids for each simulated cut.
	///
	/// To use this function, you need to first call SetCollidingChunksEnabled(true).
	///
	/// The @p chunkIdsPerMove vector contains one entry for each move in the last @ref
	/// SimulateBufferedCuts() call. If cuts were Simulated using Cut(), CircularCut() etc.,
	/// @p chunkIdsPerMove will be a vector of size 1.
	///
	/// The ids in chunkIdsPerMove refer to the chunk ids before the cut was performed. That
	/// means, if a cut is colliding, and also splitting a chunk, then the chunk-ids will not
	/// reflect the split.
	virtual void MWMSV_API
	GetCollidingChunks(std::vector<ToolChunkCollisions>& chunkIdsPerMove) = 0;


	typedef VerifierUtil::CollisionPointOptions CollisionPointOptions;

	/// Use this API to enable the generation of additional collision information in
	/// SimulateBufferedCuts().
	virtual void MWMSV_API SetCollisionPointOptions(const CollisionPointOptions& options) = 0;
	virtual void MWMSV_API GetCollisionPointOptions(CollisionPointOptions& options) const = 0;

	/// Signal that simulation has ended, that is, all cuts have been simulated.
	///
	/// - It's main purpose is to free memory, that is otherwise kept for a faster simulation.
	/// - If the simulation is in spindle-auto-mode then this function switches the stock spindle to
	///   ON or OFF, depending on whether the stock is revolved or not. See @ref
	///   GetStockIsRotationalSymmetric() for details.
	/// - It may not be called before all Cuts have been simulated. Especially buffered cuts must
	/// have been simulated by calling SimulateBufferedCuts() first!
	/// - If the simulation is just paused, please use OnSimulationStopped().
	virtual void MWMSV_API OnSimulationEnded() = 0;

	/// Signal that the simulation was paused, but may resume later with more cuts.
	///
	/// - It's main purpose is to free memory, that is otherwise kept for a faster simulation.
	/// - In contrast to @ref OnSimulationEnded(), will not change the stock's spindle state.
	/// - In contrast to @ref OnSimulationEnded(), will keep all internal states to continue
	/// simulation as usual. For example the active tools given by SetTool() or SetTools() will be
	/// kept.
	virtual void MWMSV_API OnSimulationStopped() = 0;

	typedef ::VerifierUtil::mwvToolElementBehavior mwvToolElementBehavior;
	typedef ::VerifierUtil::mwvToolBehavior mwvToolBehavior;

	/// Set simulation behavior for each tool-element.
	///
	/// - The behavior applies to the tools given by SetTools() and SetTool() and describe the way
	///   they are simulated (cutting/non-cutting, collision-checked etc). See mwvToolBehavior for
	///   more detailed infos.
	/// - Usually this call changes the behavior of all tools that were set via @ref SetTools(). If
	///   you only want to change the behavior of the currently selected tool (see @ref
	///   SetCurrentCutTool) you can set @p forCurrentCutToolOnly to true.
	/// - By default only the flute is simulated.
	virtual void MWMSV_API SetToolBehavior(
		const mwvToolBehavior& toolBehavior, const bool forCurrentCutToolOnly = false) = 0;

	/// @see SetToolBehavior().
	virtual void MWMSV_API
	GetToolBehavior(mwvToolBehavior& toolBehavior, const bool forCurrentCutToolOnly = false) = 0;

	/// @deprecated Please use SetToolBehavior(). It has a much clearer interface.
	///
	/// Set collision-mode of move for first three tool-elements.
	///
	/// @sa SetMoveModes(bool, bool, bool, bool)
	MW_DEPRECATED("Please use SetToolBehavior.")
	virtual MWV_ERRORCODE MWMSV_API
	SetMoveModes(bool bCheckEdge, bool bCheckArbor, bool bCheckHolder) = 0;

	// clang-format off
	/// @deprecated Please use SetToolBehavior(). It has a much clearer interface.
	///
	/// Sets collision-mode of move for all tool-elements
	///
	/// Collision-mode determines, if a tool-element is checked for collisions.
	///
	/// This method applies to all tools, currently set by SetTools. To set each tool individually
	/// see SetMoveModesForCutToolOnly.
	///
	/// @return A verifier error code
	///
	/// Table of possible modes for a tool-element:
	///
	/// | SetCuttingPart | SetMoveModes | Effect                                                                                                                                   |
	/// |----------------|--------------|------------------------------------------------------------------------------------------------------------------------------------------|
	/// | 0              | 0            | <b>Not simulated</b>                                                                                                                     |
	/// | 0              | 1            | <b>collision mode:</b><br>cuts material (also for rapid),<br>always returns collision-error-code when cut,<br>material always red        |
	/// | 1              | 0            | <b>silent cutting mode:</b><br>cuts material (also for rapid),<br>no collision-error-code,<br>red material only for rapid-cuts           |
	/// | 1              | 1            | <b>cutting mode:</b><br>cuts material (also for rapid),<br>collision-error-code only for rapid-cuts,<br>red material only for rapid-cuts |
	// clang-format on
	MW_DEPRECATED("Please use SetToolBehavior.")
	virtual MWV_ERRORCODE MWMSV_API
	SetMoveModes(bool bCheckEdge, bool bCheckNCEdge, bool bCheckArbor, bool bCheckHolder) = 0;

	/// @deprecated Please use SetToolBehavior().
	///
	/// Like SetMoveModes but only for the tool selected by SetCurrentCutTool.
	MW_DEPRECATED("Please use SetToolBehavior.")
	virtual void MWMSV_API SetMoveModesForCutToolOnly(
		bool bCheckEdge, bool bCheckNCEdge, bool bCheckArbor, bool bCheckHolder) = 0;

	/// @deprecated Please use SetToolBehavior().
	///
	/// Get collision-mode of each tool-element.
	///
	/// @sa SetMoveModes(bool, bool, bool, bool)
	MW_DEPRECATED("Please use GetToolBehavior.")
	virtual MWV_ERRORCODE MWMSV_API
	GetMoveModes(bool& bCheckEdge, bool& bCheckNCEdge, bool& bCheckArbor, bool& bCheckHolder) = 0;

	/// @deprecated Please use SetToolBehavior().
	///
	/// Overrides, which tool-elements are cutting and non-cutting.
	///
	/// Default cutting-part is the cutting-edge only.
	///
	/// For a complete description see SetMoveModes(bool, bool, bool, bool).
	///
	/// This method applies to all tools, currently set by SetTools. To set each tool individually
	/// see SetCuttingPartForCutToolOnly.
	/// @return A verifier error code
	MW_DEPRECATED("Please use SetToolBehavior.")
	virtual MWV_ERRORCODE MWMSV_API SetCuttingPart(
		bool edgeIsCutting, bool NCEdgeIsCutting, bool arborIsCutting, bool holderIsCutting) = 0;

	/// @deprecated Please use SetToolBehavior().
	///
	/// Like SetCuttingPart but only for the tool selected by SetCurrentCutTool.
	MW_DEPRECATED("Please use SetToolBehavior.")
	virtual void MWMSV_API SetCuttingPartForCutToolOnly(
		bool edgeIsCutting, bool NCEdgeIsCutting, bool arborIsCutting, bool holderIsCutting) = 0;

	/// @deprecated Please use SetToolBehavior()!
	///
	/// Get cutting-mode of each tool-element.
	///
	/// @sa SetCuttingPart
	MW_DEPRECATED("Please use GetToolBehavior.")
	virtual MWV_ERRORCODE MWMSV_API GetCuttingPart(
		bool& edgeIsCutting,
		bool& NCEdgeIsCutting,
		bool& arborIsCutting,
		bool& holderIsCutting) = 0;

	/// Sets the rapid mode for all following moves. In rapid mode the edge ("cutting part") reports
	/// collisions if it touches the stock.
	///
	/// Instead, you can also set the edge's tool behavior to "collision-checked". The main
	/// difference is, that rapid mode uses a different collision tolerance (see @ref
	/// SetRapidAccelerationTolerance(), @ref SetRapidCollisionTolerance()). Rapid moves are more
	/// reliable when performing retractions with a very small collision tolerance.
	virtual MWV_ERRORCODE MWMSV_API SetRapidMode(bool bIsRapid) = 0;

	/// @sa SetRapidMode
	virtual bool MWMSV_API GetRapidMode() const = 0;

	/// Set the two tool planes for wire cutting. The planes are defined by a normal and a distance
	/// from the origin.
	///
	/// A wire is defined as the shortest line that connects two points, where one of the points
	/// lies on plane 1, and the other on plane 2. The wire points are calculated by intersecting
	/// the current wire tool's axis and intersecting it with the wire planes.
	///
	/// The wire is interpolated internally by linearly moving the wire points on their respective
	/// planes, from start to end position.
	///
	/// For a more detailed explanation see our
	/// [developer&nbsp;guide](doc/Developer_guide/Cutting_Additive_Simulation/Simulating_moves.md).
	virtual void MWMSV_API SetWirePlaneInterpolation(
		const float3d planeNormal = float3d(0, 0, 0),
		const float planePos1 = 0.0f,
		const float planePos2 = 0.0f) = 0;

	/// @sa SetWirePlaneInterpolation
	virtual void MWMSV_API
	GetWirePlaneInterpolation(float3d& planeNormal, float& planePos1, float& planePos2) const = 0;

	/// Adds stock material inside the given mesh
	///
	/// The mesh is expected to describe a volume, so it needs to be closed and free of inner or
	/// unconnected surfaces.
	///
	/// Note that the stock will not become bigger than it's initial bounding box. Material that is
	/// outside of the stock's bounding-box will be clipped.
	///
	/// @return true if stock geometry has been changed, false otherwise.
	virtual bool MWMSV_API BooleanUnify(const ConstMeshPtr& pMesh) = 0;

	/// Subtracts all material inside the given mesh
	///
	/// The mesh is expected to describe a volume, so it needs to be closed and free of inner or
	/// unconnected surfaces.
	///
	/// You can also subtract all of the mesh volume, by calling ClearStock().
	///
	/// @return true if stock geometry has been changed, false otherwise.
	virtual bool MWMSV_API BooleanSubtract(const ConstMeshPtr& pMesh) = 0;

	/// Removes all material outside of the given mesh
	///
	/// The mesh is expected to describe a volume, so it needs to be closed and free of inner or
	/// unconnected surfaces.
	///
	/// You can also subtract all of the mesh volume, by calling ClearStock().
	///
	/// @return true if stock geometry has been changed, false otherwise.
	virtual bool MWMSV_API BooleanIntersect(const ConstMeshPtr& pMesh) = 0;

	/// Intersect revolved profile with stock.
	///
	/// @return true if stock geometry has been changed, false otherwise.
	virtual bool MWMSV_API BooleanIntersect(
		const cadcam::mw2dfContour& revolvedProfile, const StockSpindleAxis revolvedAxis) = 0;

	MW_WARNING_PUSH
	MW_WARNING_DISABLE_DEPRECATED
	/// @deprecated Please use BooleanIntersect(const cadcam::mw2dfContour&, const StockSpindleAxis)
	/// instead.
	MW_DEPRECATED("TurningRotaryAxis is deprecated. Please use StockSpindleAxis instead.")
	virtual bool MWMSV_API BooleanIntersect(
		const cadcam::mw2dfContour& revolvedProfile, const TurningRotaryAxis revolvedAxis) = 0;
	MW_WARNING_POP

	/// Cut with the tool on a circular path defined by two points.
	///
	/// The simplest path that can be simulated with this method is a circle on a plane. To do this,
	/// make sure that startFrame, endFrame and circleCenter define points that are on the
	/// same plane. CirclePlaneNormal has to be perpendicular to that plane.
	///
	/// On top of that, this method support more general movements:
	///	- helical cuts, if startFrame and endFrame define positions on different planes
	///	- spiral cuts, if startFrame and endFrame have different distances to the circleCenter
	///
	/// Internally, circular moves are interpolated using an internally computed error
	/// tolerance. To set an upper limit to this tolerance, use
	/// @ref mwMachSimVerifier::SetCuttingTolerance().
	///
	/// @param [in] startFrame   The start position and orientation of the tool.
	/// @param [in] endFrame   The end position and orientation of the tool.
	///	                       If the end orientation is different to the start orientation,
	///	                       the orientation will be interpolated linearly, independent of
	///	                       the tool path and circlePlaneNormal.
	/// @param [in] circleCenter   The position of the circle center. It is usually on the plane
	///	                           of startFrame and endFrame, but can also be shifted along the
	///	                           circlePlaneNormal.
	/// @param [in] circlePlaneNormal   The normal on the plane defined by the circle.
	///	                                The circle movement is around the normal following the
	///	                                right-hand-rule.
	/// @return true if stock geometry has been changed or hit, false otherwise.
	virtual bool MWMSV_API CircularCut(
		const Frame& startFrame,
		const Frame& endFrame,
		const Point& circleCenter,
		const Point& circlePlaneNormal) = 0;

	/// Like CircularCut() but the move is buffered, and will be cut when SimulateBufferedCuts() is
	/// called.
	/// @copydoc CircularCut
	virtual void MWMSV_API BufferedCircularCut(
		const Frame& startFrame,
		const Frame& endFrame,
		const Point& circleCenter,
		const Point& circlePlaneNormal) = 0;

	/// Cut with the tool on a circular path defined by an angle.
	///
	/// This method is an alternative to the CircularCut() using a sweepAngle instead of a second
	/// point. So in this declaration endFrame is not given explicitly.
	///
	/// The move is defined by the startFrame and the sweepAngle between start and end. Advantages
	/// of this method are, that it can define circle with more than 360° and that it is usually a
	/// more stable way to define a circle (avoiding flipping between 0° and 360°).
	///
	/// @param [in] startFrame  The start position and orientation of the tool.
	/// @param [in] sweepAngle  The angle between start and end orientation of the tool (given in
	///                         degrees, can be any number).
	/// @param [in] circleCenter  The position of the circle center. It is usually on the plane
	///	                          of startFrame and endFrame, but can also be shifted along the
	///	                          circlePlaneNormal.
	/// @param [in] circlePlaneNormal  The normal on the plane defined by the circle.
	///	                               The circle movement is around the normal following the
	///	                               right-hand-rule.
	/// @param [in] heightChange  The height difference between start and end positions of the
	///                           tool (set to 0 by default). Height refers to the direction of the
	///                           circlePlaneNormal.
	/// @param [in] radiusChange  The difference of the circle radius at the beginning and the end
	///                           of the move (set to 0 by default).
	/// @return true if stock geometry has been changed or hit, false otherwise.
	virtual bool MWMSV_API CircularSweepCut(
		const Frame& startFrame,
		const float sweepAngle,
		const Point& circleCenter,
		const Point& circlePlaneNormal,
		const float heightChange = 0,
		const float radiusChange = 0) = 0;

	/// Same as CircularSweepCut() but the move is buffered, and will be cut when
	/// SimulateBufferedCuts() is called.
	///
	/// @copydoc CircularSweepCut
	virtual void MWMSV_API BufferedCircularSweepCut(
		const Frame& startFrame,
		const float sweepAngle,
		const Point& circleCenter,
		const Point& circlePlaneNormal,
		const float heightChange = 0,
		const float radiusChange = 0) = 0;

	/// Simulates a thread in turning simulation.
	///
	/// To see real helix thread, make sure that the turning is turned OFF or AUTO, see
	/// SetStockSpindleMode.
	///
	/// @note startFrame and endFrame should be on the same plane which is used for lathe-cutting
	/// (usually XY- or XZ plane)
	///
	/// @param startFrame   The start position and orientation of the tool.
	/// @param endFrame   The end position and orientation of the tool.
	/// @param pitch   The distance between two threads
	///	 - one thread is considered to be the path between 0 to 360 degrees.
	///	 - If endFrame.getOrigin()-startFrame.getOrigin() has length 2 and pitch is 1,
	///    you will get a helix with 2 revolvings.
	///	 - If pitch is positive, the stock is assumed to rotate clockwise around turning-axis
	///    (left hand rule).
	///	 - If it is negative, the stock rotates counter-clockwise.
	/// @param [in] startOffset
	///	 - If 0, this cut will start the thread at startFrame.
	///	 - If also realHelix is false, the first circle will be at startFrame.
	///	 - Otherwise the first circle is shifted along toolpath by startOffset.
	///	 - startOffset = 0 gives the same result as startOffset = pitch or any multiple.
	/// @param [in] realHelix   If true, real helix threads are created. Otherwise they are
	///                         approximated by circles.
	///  - Note that real helix threads are not visible, when the turning spindle is rotating
	///    fast (see SetStockSpindleMode). So make sure that turning-spindle-mode is OFF or AUTO for
	///    threads.
	/// @returns true if stock geometry has been changed (something was cut), false otherwise.
	virtual bool MWMSV_API ThreadCut(
		const Frame& startFrame,
		const Frame& endFrame,
		const float pitch,
		const float startOffset,
		const bool realHelix = false) = 0;

	/// Same as ThreadCut() but the move is buffered, and will be cut when
	/// SimulateBufferedCuts() is called.
	///
	/// @copydoc ThreadCut()
	virtual void MWMSV_API BufferedThreadCut(
		const Frame& startFrame,
		const Frame& endFrame,
		const float pitch,
		const float startOffset,
		const bool realHelix = false) = 0;

	/// Simulates a thread in grinding simulation.
	///
	/// Thread cuts are always considered as helical cuts around the turning spindle, which is
	/// always the X-axis.
	///
	/// @param [in] startFrame  the start position and orientation of the tool.
	/// @param [in] endFrame    the end position and orientation of the tool.
	///
	/// Note, that startFrame and endFrame should be created or interpolated by
	/// @ref VerifierUtil::mwvKinematicUtils.
	/// @return true if stock geometry has been changed (something was cut), false otherwise.
	virtual bool MWMSV_API ThreadCut(const Frame& startFrame, const Frame& endFrame) = 0;

	/// Same as ThreadCut(const Frame&, const Frame&) but move is buffered, and will be cut
	/// when SimulateBufferedCuts() is called.
	///
	/// @copydoc ThreadCut(const Frame&, const Frame&)
	virtual void MWMSV_API BufferedThreadCut(const Frame& startFrame, const Frame& endFrame) = 0;

	/// Add a mesh that will be collision-checked against current stock when calling @ref
	/// CheckCollisionMeshes().
	///
	/// The mesh will be removed if Reset() is called. ResetToInitialStock() will keep the meshes.
	///
	/// @return internal id of the mesh, which is used in related methods like
	/// RemoveCollisionMesh(), MoveCollisionMesh()
	virtual int MWMSV_API AddCollisionMesh(
		const ConstMeshPtr& mesh, const float safetyDistance, const Frame& startPosition) = 0;

	/// @see AddCollisionMesh
	virtual int MWMSV_API AddCollisionMesh(
		const ConstMeshPtr& mesh,
		const std::vector<float>& safetyDistances,
		const Frame& startPosition) = 0;

	/// @see AddCollisionMesh
	virtual void MWMSV_API RemoveCollisionMesh(const int meshId) = 0;

	/// @see AddCollisionMeshes
	virtual void MWMSV_API ClearCollisionMeshes() = 0;

	/// Enable or disable collision checking for a mesh.
	///
	/// Collision meshes are enabled by default
	virtual void MWMSV_API EnableCollisionMesh(const int meshId, const bool enabled) = 0;

	/// Enable or disable all collision meshes.
	///
	/// @sa EnableCollisionMesh
	virtual void MWMSV_API EnableAllCollisionMeshes(const bool enabled) = 0;

	/// Changes the position of a collision mesh.
	virtual void MWMSV_API MoveCollisionMesh(const int meshId, const Frame& position) = 0;

	/// Sets the collision color for a mesh.
	virtual void MWMSV_API SetCollisionMeshColor(
		const int meshId, const float r, const float g, const float b, const float a) = 0;

	/// Sets one or multiple safety distances for a collision mesh.
	///
	/// If any safety distance is violated, then a collision is reported. The largest safety
	/// distance that was violated can be obtained from the MeshCollisionReport.
	///
	///	@sa GetCollidingMeshes
	virtual void MWMSV_API
	SetSafetyDistances(const int meshId, const std::vector<float>& safetyDistances) = 0;

	/// Check all collision meshes against the stock.
	///
	/// @returns true if any mesh collided.
	virtual bool MWMSV_API CheckCollisionMeshes() = 0;

	typedef VerifierUtil::MeshCollisionReport MeshCollisionReport;
	/// Get information about all collisions that were found in the last @ref CheckCollisionMeshes()
	/// call.
	virtual void MWMSV_API GetCollidingMeshes(std::vector<MeshCollisionReport>& reports) = 0;

	/// Get ids of all colliding meshes that were found in the last @ref CheckCollisionMeshes()
	/// call.
	virtual void MWMSV_API GetCollidingMeshes(std::vector<int>& meshIds) = 0;

	/// @see SetDrawCollisionMeshes
	virtual bool MWMSV_API GetDrawCollisionMeshes() const = 0;

	/// Enable or disable drawing of collision meshes in @ref Draw().
	virtual void MWMSV_API SetDrawCollisionMeshes(const bool b) = 0;

	/// Simulate the given move
	///
	/// This interface provides an alternative to Cut(), CircularCut(), CircularSweepCut() and
	/// ThreadCut().
	///
	/// @sa BufferMove()
	/// @returns true if the stock has been changed or hit.
	virtual bool MWMSV_API SimulateMove(const VerifierUtil::mwMove& move) = 0;

	/// Enqueue the given move
	///
	/// This interface provides an alternative to BufferedCut(), BufferedCircularCut(),
	/// BufferedCircularSweepCut() and BufferedThreadCut().
	///
	/// The enqueued moves will be simulated when calling SimulateBufferedCuts(). Using this API
	/// allows more internal parallelization than possible with SimulateMove().
	virtual void MWMSV_API BufferMove(const VerifierUtil::mwMove& move) = 0;

	typedef VerifierUtil::mwSimulateMotionResults SimulateMotionResults;
	typedef VerifierUtil::mwSimulateMotionOptions SimulateMotionOptions;
	typedef VerifierUtil::mwMotions Motions;
	/// Simulate given tool and mesh motions.
	///
	/// @param [in] motions A list of motions, which consist of one or many moves/cuts. Motions
	/// can be for tools (see SetTools()) or meshes (see AddCollisionMesh()).
	/// @param [in] options controls the behavior of the method. E.g. that it stops after first
	/// detected collision
	/// @return true if and collision occurred during motion otherwise false
	virtual bool MWMSV_API SimulateMotion(
		const Motions& motions,
		const SimulateMotionOptions& options,
		SimulateMotionResults& results) = 0;

	/// Computes the time at which the active tool collides
	///
	/// @p equalPositionTolerance is the acceptable deviation from the real collision point.
	///
	/// @return Time at which the active tool collides for given movement
	/// (0 <= t <= 1, t=0 means collision at startPosition, t=1 collision at endPosition).
	/// If no collision found, t is @ref GetInvalidCollisionTime().
	virtual float MWMSV_API FindToolCollisionTime(
		const Frame& startPosition,
		const Frame& endPosition,
		const float equalPositionTolerance) = 0;

	/// @sa FindToolCollisionTime
	virtual float MWMSV_API
	FindToolCollisionTime(const VerifierUtil::mwMove& move, const float equalPositionTolerance) = 0;

	/// Constant for an invalid collision time, see FindToolCollisionTime().
	static inline float GetInvalidCollisionTime() { return mathdef::MW_MAX_FLOAT; };

	/// Reset many of the simulation parameters
	///
	/// Calling Reset() leaves most of the simulation options intact, while resetting the scene
	/// geometry (with a few exceptions). This function is usually called when restarting a
	/// simulation, or when loading a different one.
	///
	/// For legacy reasons it is often non-obvious which options are reset, and which ones are kept.
	/// To reset mwMachSimVerifier to a known state it is often simpler to recreate
	/// mwMachSimVerifier instead of calling Reset(). There is often no large performance gain when
	/// using Reset(); the main benefit is that some internal optimization structures for target
	/// meshes are kept.
	///
	/// # What is cleared?
	///
	/// stock, tools, cutting history (refine), collision meshes, color schemes, restore points,
	/// zooming level, measurements, refine layout, engagement tracking, turning spindle mode, wire
	/// planes, resettables
	///
	/// # What is not cleared?
	///
	/// target meshes, workpiece draw mode, precision, tool behavior, max memory load, tolerances
	/// (cutting, collision checking etc.), collision color mode, mesh quality, render options,
	/// experimental settings, auto refine mode, incremental chunk detection, thread count limit
	///
	/// # Alternatives
	///
	/// - To only remove the stock, while keeping tools and other settings use @ref ClearStock()
	/// - To keep the initial stock, as well as collision meshes and color schemes use @ref
	///   ResetToInitialStock().
	virtual MWV_ERRORCODE MWMSV_API Reset() = 0;

	/// Reset simulation to initial stock
	///
	/// This is mostly the same as @ref Reset(). However, instead of removing the stock it
	/// re-creates it using the original stock geometry. Also, the collision meshes and the color
	/// schemes are kept.
	virtual void MWMSV_API ResetToInitialStock() = 0;
	/// @}

	/// @name Stock display
	/// @{

	///	WorkpieceDrawModes
	typedef ::VerifierUtil::WorkpieceDrawModes WorkpieceDrawModes;
	static const WorkpieceDrawModes WDM_SOLID = ::VerifierUtil::WDM_SOLID;
	static const WorkpieceDrawModes WDM_DEVIATION = ::VerifierUtil::WDM_DEVIATION;
	static const WorkpieceDrawModes WDM_TOOL = ::VerifierUtil::WDM_TOOL;
	static const WorkpieceDrawModes WDM_OPERATION = ::VerifierUtil::WDM_OPERATION;
	static const WorkpieceDrawModes WDM_TOOL_PATH_SEGMENT_LENGTH =
		::VerifierUtil::WDM_TOOL_PATH_SEGMENT_LENGTH;
	static const WorkpieceDrawModes WDM_HEIGHT_CHANGE = ::VerifierUtil::WDM_HEIGHT_CHANGE;
	static const WorkpieceDrawModes WDM_ORIENTATION_CHANGE = ::VerifierUtil::WDM_ORIENTATION_CHANGE;
	static const WorkpieceDrawModes WDM_CHUNKS = ::VerifierUtil::WDM_CHUNKS;
	static const WorkpieceDrawModes WDM_TEXTURE = ::VerifierUtil::WDM_TEXTURE;
	static const WorkpieceDrawModes WDM_TEXTURE_PLUS_COLLISIONS =
		::VerifierUtil::WDM_TEXTURE_PLUS_COLLISIONS;
	static const WorkpieceDrawModes WDM_TARGET_ID = ::VerifierUtil::WDM_TARGET_ID;
	static const WorkpieceDrawModes WDM_GOUGE_EXCESS = ::VerifierUtil::WDM_GOUGE_EXCESS;
	static const WorkpieceDrawModes WDM_REMOVED_MATERIAL = ::VerifierUtil::WDM_REMOVED_MATERIAL;
	static const WorkpieceDrawModes WDM_DEVIATION_OFFSET = ::VerifierUtil::WDM_DEVIATION_OFFSET;
	static const WorkpieceDrawModes WDM_OPERATION_TYPE = ::VerifierUtil::WDM_OPERATION_TYPE;
	static const WorkpieceDrawModes WDM_CLIMB_AND_CONVENTIONAL =
		::VerifierUtil::WDM_CLIMB_AND_CONVENTIONAL;
	static const WorkpieceDrawModes WDM_REMOVED_VOLUME = ::VerifierUtil::WDM_REMOVED_VOLUME;
	static const WorkpieceDrawModes WDM_NOINITIALIZED = ::VerifierUtil::WDM_NOINITIALIZED;

	/// Draws all verifier geometry into the current OpenGL context. The model-view matrix - if
	/// already set outside of this context - remains unchanged.
	///
	/// The camera must be set up by the integration, by setting correct ModelView- and
	/// Projection matrices. Lighting is controlled by the integration as well.
	///
	/// You can customize the Draw() function via:
	/// - SetWorkpieceVisibility()
	/// - SetToolVisibility()
	/// - SetTargetVisibility()
	/// - SetMeasurementVisibility()
	/// - SetDrawMode()
	/// - ShowGougeLabels()
	/// - ShowExcessLabels()
	/// - SetShowColorEdges()
	/// - SetSectionPlane()
	/// - SetSecondarySectionPlane()
	///
	/// Integrations that need more control, or multithreading support, should use the @ref Render()
	/// API instead.
	///
	/// @note This method must not be used together with Render(), because any call to Draw or
	/// Render will reset the internal "triangles-changed-state"!
	///
	/// May abort via progress handler on user request.
	virtual void MWMSV_API Draw() = 0;

	/// SetDrawMode
	///
	/// @param  mode  WorkpieceDrawModes
	virtual void MWMSV_API SetDrawMode(WorkpieceDrawModes mode) = 0;

	/// GetDrawMode
	///
	/// @return the current draw mode
	virtual WorkpieceDrawModes MWMSV_API GetDrawMode() const = 0;

	/// @deprecated Please use SetRenderOptions() instead!
	MW_DEPRECATED("Use SetRenderOptions instead!")
	virtual int MWMSV_API SetMeshRenderMode(int mode) = 0;

	/// If called, next Render()- or Draw() call will regenerate all triangles and lines.
	virtual void MWMSV_API ForceRedraw() = 0;

	/// Set workpiece visibility during Draw().
	///
	/// This visibility setting doesn't affect the triangles generated during Render().
	///
	/// @param [in] bIsWorkpieceVisible TRUE workpiece should be drawn
	/// @return A verifier error code
	virtual MWV_ERRORCODE MWMSV_API SetWorkpieceVisibility(bool bIsWorkpieceVisible) = 0;

	virtual bool MWMSV_API GetWorkpieceVisibility() const = 0;

	/// Sets the initial color of the stock needs to be called before first cut.
	///
	/// @param [in] r color red value between 0 and 1.
	/// @param [in] g color green value between 0 and 1.
	/// @param [in] b color blue value between 0 and 1.
	/// @param [in] a color alpha value between 0 and 1.
	virtual void MWMSV_API SetMeshColor(float r, float g, float b, float a = 1) = 0;
	/// See SetMeshColor()
	virtual void MWMSV_API GetMeshColor(float& r, float& g, float& b, float& a) const = 0;

	/// Sets the color of workpiece parts that collided with non-cutting tool elements.
	///
	/// This color is used in the Draw() method to define the appearance.
	/// @param [in] r color red value between 0 and 1.
	/// @param [in] g color green value between 0 and 1.
	/// @param [in] b color blue value between 0 and 1.
	/// @param [in] alpha the transparency value of the collision default is 1.0f.
	virtual void MWMSV_API SetCollisionColor(float r, float g, float b, float alpha = 1.0f) = 0;

	// See @ref SetCollisionColor
	//
	// @note The color is stored in a compressed format. So the values returned here may not be
	// exactly as you set them.
	virtual void MWMSV_API GetCollisionColor(float& r, float& g, float& b, float& alpha) const = 0;

	/// Gets the parameters (editable) for the colorization of the requested color scheme
	///
	/// @param [in] scheme the color scheme identifier
	/// @return A pointer to color scheme interface
	virtual mwMachSimVerifierColorScheme* MWMSV_API GetColorScheme(WorkpieceDrawModes scheme) = 0;

	/// Gets the parameters (read only) for the colorization of the requested color scheme
	///
	/// @param [in] scheme the color scheme identifier
	/// @return A pointer to color scheme interface
	virtual const mwMachSimVerifierColorScheme* MWMSV_API
	GetColorScheme(WorkpieceDrawModes scheme) const = 0;

	/// Gets the min and max of given color scheme base value
	///
	/// If a color scheme uses a range of values, this function returns the extent
	/// of the values. Otherwise, the range will be zero.
	/// Ranges of values are used for @ref WDM_DEVIATION, @ref WDM_HEIGHT_CHANGE and similar
	/// schemes.
	/// @param [in] mode the color scheme
	/// @param [out] min minimal range value
	/// @param [out] max maximal range value
	virtual void MWMSV_API
	GetColorSchemeExtent(mwMachSimVerifier::WorkpieceDrawModes mode, float& min, float& max) = 0;

	/// Set the color for edge-highlighting on the stock-material.
	///
	/// Only applied when a stock is (re-)initialized. @sa ResetToInitialStock
	///
	/// @param [in] r color red value between 0 and 1.
	/// @param [in] g color green value between 0 and 1.
	/// @param [in] b color blue value between 0 and 1.
	/// @param [in] a alpha transparency value between 0 and 1.
	virtual void MWMSV_API SetSharpEdgeColor(float r, float g, float b, float a) = 0;
	/// @sa SetSharpEdgeColor
	virtual void MWMSV_API GetSharpEdgeColor(float& r, float& g, float& b, float& a) const = 0;

	/// @deprecated Please use SetRenderOptions instead!
	MW_DEPRECATED("Use SetRenderOptions instead!")
	virtual void MWMSV_API SetShowColorEdges(bool colorEdges) = 0;

	/// @deprecated Please use GetRenderOptions instead!
	MW_DEPRECATED("Use GetRenderOptions instead!")
	virtual void MWMSV_API GetShowColorEdges(bool& colorEdges) const = 0;

	/// @deprecated Please use SetCollisionColorMode() Set mode of material-coloring for collision
	/// @param enabled If true, the 3x-model will project the red collision-color down.
	/// That means if the tool collided with material, the red cannot be cut away by following cuts.
	MW_DEPRECATED("Use SetCollisionColorMode instead!")
	virtual void MWMSV_API SetProjectedCollisionColor(bool enabled) = 0;
	/// @deprecated Please use GetCollisionColorMode()
	MW_DEPRECATED("Use GetCollisionColorMode instead!")
	virtual void MWMSV_API GetProjectedCollisionColor(bool& enabled) const = 0;

	/// @deprecated Please use SetCollisionColorMode(). Set, if only colliding tool-elements are
	/// marked red
	///
	/// Refers to the color on stock-surface after a cut/collision-check and only has an effect on
	/// the 5-axis model (@sa MWV_FM_DEXELBLOCK). For the 3-axis model, the whole tool will always
	/// mark the stock red, otherwise collisions can get lost easily.
	MW_DEPRECATED("Use SetCollisionColorMode instead!")
	virtual void MWMSV_API SetMarkCollidingElementsOnly(bool enabled) = 0;
	/// @deprecated Please use GetCollisionColorMode(). @sa SetMarkCollidingElementsOnly
	MW_DEPRECATED("Use GetCollisionColorMode instead!")
	virtual void MWMSV_API GetMarkCollidingElementsOnly(bool& enabled) const = 0;

	typedef ::VerifierUtil::mwvCollisionColorMode mwvCollisionColorMode;

	/// Customize which parts of the tool apply the collision color to the stock.
	virtual void MWMSV_API
	SetCollisionColorMode(const mwvCollisionColorMode& collisionColoring) = 0;

	/// @see SetCollisionColorMode
	virtual void MWMSV_API
	GetCollisionColorMode(mwvCollisionColorMode& collisionColoring) const = 0;

	/// Set the threshold angle for the coloring in Climb and Conventional draw mode.
	///
	/// @param [in] angle the maximal angle between the direction of feed and the machined surface.
	virtual void MWMSV_API SetClimbAndConventionalThreshold(const float angle) = 0;
	/// @see SetClimbAndConventionalThreshold
	virtual float MWMSV_API GetClimbAndConventionalThreshold() const = 0;

	/// Request Owner Draw flag
	///
	///  This flag handles is the implementation can draw the mesh data by itself
	/// @deprecated
	/// @return TRUE id the implementation draws the data
	MW_DEPRECATED("No longer used, always returns true")
	virtual bool MWMSV_API IsOwnerDraw() const = 0;

	/// Set V-Synchronization via WGL_EXT_swap_control.
	///
	/// This enables/disables vertical synchronization of graphics card. Note that V-Synchronization
	/// may limit the verifier performance.
	///
	/// Requires a valid OpenGL context.
	///
	/// @param [in] enabled If true, V-Sync will be enabled, otherwise disabled.
	virtual void MWMSV_API SetVSync(bool enabled) = 0;
	/// @sa SetVSync
	virtual void MWMSV_API GetVSync(bool& enabled) const = 0;
	/// @}

	/// @name Abstract Renderer
	/// @{
	/// The abstract renderer specifies a primitive renderer that is used for customized drawing.
	/// This gives the user the possibility to use a specific graphical environment according to his
	/// needs like OpenGL, Direct3D etc. Note that instead of calling Draw() the API-method Render()
	/// is used.
	///
	/// @sa VerifierUtil::mwvAbstractRenderer or VerifierUtil::mwvIndexedAbstractRenderer.

	/// Draws all verifier data using customized renderer.
	///
	/// @note This method must not be used together with Draw, because any call to Draw or Render
	/// will reset the internal "triangles-changed-state"!
	///
	/// Rendering behavior can be customized using SetRenderOptions().
	///
	/// @param [in] renderer A pointer to the renderer. If it is null, a standard OpenGL renderer is
	/// used.
	virtual void MWMSV_API Render(VerifierUtil::mwvAbstractRendererBase* renderer) = 0;

	typedef ::VerifierUtil::RenderOptions RenderOptions;

	virtual void MWMSV_API SetRenderOptions(const RenderOptions& renderOptions) = 0;
	virtual void MWMSV_API GetRenderOptions(RenderOptions& renderOptions) const = 0;

	/// Apply a texture handler
	///
	/// This method passes on the parameters to the internal texture handler which will be used in
	/// the standard OpenGL renderer if data model is set to MWV_FM_DEXELBLOCK and the draw mode is
	/// set to either WDM_TEXTURE or WDM_TEXTURE_PLUS_COLLISIONS.
	/// 
	/// @param [in] textureParams a pointer to the structure with the texture handler parameters.
	/// If it is null, no texturing will be performed.
	virtual void MWMSV_API
	SetTextureHandler(VerifierUtil::mwCutMaterialTextureHandlerParameters* textureParams) = 0;

	/// Register a resettable
	///
	/// This method saves the passed resettable in a list and calls its Reset() method when a
	/// verifier reset is performed.
	/// @param [in] resettable a pointer to the resettable object.
	virtual void MWMSV_API RegisterResettable(VerifierUtil::mwvResettable* resettable) = 0;

	/// Unregister a resettable
	///
	/// This method removes the passed resettable from the list and does not call its Reset() method
	/// anymore when a verifier reset is performed.
	/// @param [in] resettable a pointer to the resettable object.
	virtual void MWMSV_API UnregisterResettable(VerifierUtil::mwvResettable* resettable) = 0;

	/// @}

	/// @name Sectioned workpiece display
	/// The Draw() call can be configured to display only a section of the workpiece, configurable
	/// by two section planes.
	///
	/// Draw() may throw an exception if too few section planes are available (for example because
	/// the integration uses some): `misc::mwException(0, "SetSectionPlane called with zero length
	/// normal direction vector.")`
	/// @{

	/// Sets the primary section plane to be used in the section display
	///
	/// The plane definition follows the Hesse Normal Form.
	///
	/// @sa http://en.wikipedia.org/wiki/Hesse_normal_form
	///
	/// @param [in] normalDirection	 the plane normal
	/// @param [in] shift	 the shift along the normal
	/// @param [in] displaySection	true if the section shall be enabled
	virtual void MWMSV_API
	SetSectionPlane(float3d normalDirection, float shift, bool displaySection) = 0;

	/// @sa SetSectionPlane
	virtual void MWMSV_API
	GetSectionPlane(float3d& normalDirection, float& shift, bool& displaySection) const = 0;

	/// Sets the secondary section plane to be used if a two sectioned display of the workpiece is
	/// used. Setting a secondary section plane has no effect as long as the primary section plane
	/// is disabled.
	///
	/// The plane definition follows the Hesse Normal Form.
	///
	/// @sa SetSectionPlane
	/// @sa http://en.wikipedia.org/wiki/Hesse_normal_form
	///
	/// @param [in] normalDirection	 the plane normal
	/// @param [in] shift	 the shift along the normal
	/// @param [in] displaySection	true if the section should be displayed
	virtual void MWMSV_API SetSecondarySectionPlane(
		const float3d& normalDirection, const float shift, const bool displaySection) = 0;

	/// @sa SetSecondarySectionPlane
	virtual void MWMSV_API GetSecondarySectionPlane(
		float3d& normalDirection, float& shift, bool& displaySection) const = 0;

	/// These additional parameters apply to both section planes.
	///
	/// @param [in] color	the color of the filled section planes (RGB, 0--1)
	/// @param [in] alpha	the alpha value of the section plane (0--1)
	/// @param [in] filled	decides whether the section planes shall be filled (TRUE) or not
	///                     (FALSE).
	/// @param [in] addsectionHalfspaces  decides whether the boolean union (TRUE) or the boolean
	///                                   intersection (FALSE) of the two sections shall be
	///                                   displayed.
	virtual void MWMSV_API SetSectionParameters(
		const float3d& color,
		const float alpha,
		const bool filled,
		const bool addsectionHalfspaces) = 0;

	/// @sa SetSectionParameters
	virtual void MWMSV_API GetSectionParameters(
		float3d& color, float& alpha, bool& filled, bool& addsectionHalfspaces) const = 0;
	/// @}


	/// @name Stock Refinement
	/// @anchor CutSim_refine_API
	/// @{
	/// Layout for refine methods.
	///
	/// The layout defined what parts of the stock to refine
	///	and when. It is a set of bounding box with a factor and step.
	///	The factor defines, how many times the precision is increased,
	///	the step defines, when it is computed. E.g. step 0 means it is
	///	computed in the first parts, step 1 would be computed when all
	///	step 0 bounding boxes are done and so on.
	typedef VerifierUtil::RefineBox RefineBox;
	typedef VerifierUtil::RefineLayout RefineLayout;

	typedef VerifierUtil::RefineNotifier RefineNotifier;
	/// Set notifier for the refinement process.
	///
	/// The notifier is an object that receives callbacks from the verifier.
	/// Derive from RefineNotifer and implement the methods to define a custom behavior on a
	/// callback. The callbacks are triggered by the refine-operations Refine(), StartRefine() and
	/// StartAutoRefine(). The method aborts and waits until a currently running refinement will be
	/// completely aborted.
	/// @param [in] notifier An instance of a class derived from RefineNotifier. If a null pointer
	/// is passed, notification is disabled.
	virtual void MWMSV_API
	SetRefineNotifier(const misc::mwAutoPointer<RefineNotifier>& notifier) = 0;

	/// Refine in foreground.
	///
	/// Will refine the stock as defined in the layout.
	/// @param [in] layout A layout describing what regions when to refine.
	///	It is recommended to compute this using functions from VerifierUtil::mwRefineHelpers.
	///	See mwMachSimVerifier::RefineLayout for more infos on the layout format.
	virtual void MWMSV_API
	Refine(const RefineLayout& layout = VerifierUtil::mwRefineHelpers::ComputeFeatureLayout()) = 0;

	/// Start refinement process asynchronously in background.
	///
	/// This method triggers the same computation as mwMachSimVerifier::Refine(),
	///	but it returns immediately after starting the computation process in the background.
	///	The progress of the computation can be tracked by using a notifier in
	///	mwMachSimVerifier::SetRefineNotifier(). The process can be stopped using
	///	mwMachSimVerifier::StopRefine().
	///	This call will stop the currently running auto-refinement process.
	/// @param [in] layout A layout describing what regions when to refine.
	///	It is recommended to compute this using functions from VerifierUtil::mwRefineHelpers.
	///	See mwMachSimVerifier::RefineLayout for more infos on the layout format.
	/// @param [in] delayMilliseconds A delay in milliseconds for starting since last API - call.
	virtual void MWMSV_API StartRefine(
		const RefineLayout& layout = VerifierUtil::mwRefineHelpers::ComputeFeatureLayout(),
		const int delayMilliseconds = 500) = 0;

	/// Stop refinement process, running in background.
	///
	/// Resets all accumulated boxes.
	virtual void MWMSV_API StopRefine() = 0;

	/// Determines whether continuous background refinement is running. @sa StartAutoRefine()
	virtual bool MWMSV_API IsAutoRefine() const = 0;

	/// Start continuous background refinement.
	///
	/// In contrast to StartRefine(), this method will restart the refinement
	///	again and again, if the stock changes. It is recommended to use it, because
	///	there are many API calls that change a stock and require a new refinement
	///	computation afterwards.
	///	In contrast to Refine() and StartRefine(), the layout can be changed
	///	dynamically using UpdateAutoRefineLayout().
	/// @param [in] delayMilliseconds The refinement computation will not start
	///	immediately after the stock was changed. It will wait until no changing
	///	API call was made for the given delay (in milliseconds). It is recommended
	///	to use a value bigger than 0 here, such that the computation does not start too often.
	virtual void MWMSV_API StartAutoRefine(
		const int delayMilliseconds,
		const RefineLayout& layout = VerifierUtil::mwRefineHelpers::ComputeFeatureLayout()) = 0;

	/// Update the refinement layout for continuous background refinement.
	///
	/// @param [in] layout describes what regions when to refine. This method is usually used to
	/// update the regions to refine based on the user's current view. It is recommended to use
	/// VerifierUtil::mwRefineHelpers::ViewUpdater::ComputeLayoutFromOpenGLStack() to do this. Like
	/// for Refine() and StartRefine(), the other functions from VerifierUtil::mwRefineHelpers can
	/// be used too.
	virtual void MWMSV_API UpdateAutoRefineLayout(const RefineLayout& layout) = 0;

	/// Stop continuous background refinement.
	virtual void MWMSV_API StopAutoRefine() = 0;
	/// @}


	/// @name Measurements and selection
	/// Measurements and selection methods are used to analyze the current shape of the simulated
	/// workpiece / stock volume. Most of methods require (1) selection of a point (on the screen or
	/// 3d space)
	///
	/// @dot
	/// digraph selection {
	/// {
	///	node [shape=record, fontname=Helvetica, fontsize=10];
	///	mode [ label="Set selection mode (points, distances ...)"  URL="@ref
	/// mwMachSimVerifier::SetSelectionMode", fontname=Helvetica, fontsize=10] ; select [ label="Do
	/// selection"  URL="@ref mwMachSimVerifier::Select", fontname=Helvetica, fontsize=10]; action [
	/// label="Action (zoom, ... )"  URL="@ref mwMachSimVerifier::IncreaseZoom", fontname=Helvetica,
	/// fontsize=10]; delete [ label="Delete items"  URL="@ref
	/// mwMachSimVerifier::ClearMeasurementPoints", fontname=Helvetica, fontsize=10]; mode -> select
	/// ;
	///	select -> select  [ label="1-n"  URL="@ref mwMachSimVerifier::ClearMeasurementPoints",
	/// fontname=Helvetica, fontsize=10]; select -> action ; action -> delete ;
	/// }
	/// }
	/// @enddot
	///
	/// and (2) selection of a proper render scheme to show appropriate text label in the OpenGL
	/// mode.
	///
	/// @dot
	/// digraph selectionrenderscheme {
	/// {
	/// node [shape=record, fontname=Helvetica, fontsize=10];
	/// loop [ label="For every instance of CutSim (work piece) (don't swap buffer here)" ,
	/// fontname=Helvetica, fontsize=10] ; clear [ label="Clear ogl screen", fontname=Helvetica,
	/// fontsize=10]; render [ label="Render only the work piece"  URL="@ref
	/// mwMachSimVerifier::Draw", fontname=Helvetica, fontsize=10]; handle [ label="Handle
	/// result...", fontname=Helvetica, fontsize=10]; end [ label="Re-render the full scene before
	/// showing OpenGL again.", fontname=Helvetica, fontsize=10];
	///
	/// loop -> clear ;
	/// clear -> render ;
	/// render -> handle ;
	/// handle -> loop ;
	/// handle -> end ;
	/// }
	/// }
	/// @enddot
	/// @{
	/// Selection Mode enumeration, list of available selection modes:
	typedef ::VerifierUtil::SelectionMode SelectionMode;
	static const SelectionMode SM_NO_SELECTION = ::VerifierUtil::SM_NO_SELECTION;
	static const SelectionMode SM_POINTS_SELECTION = ::VerifierUtil::SM_POINTS_SELECTION;
	static const SelectionMode SM_DISTANCES_SELECTION = ::VerifierUtil::SM_DISTANCES_SELECTION;
	static const SelectionMode SM_ZOOMBOX_SELECTION = ::VerifierUtil::SM_ZOOMBOX_SELECTION;
	static const SelectionMode SM_CHUNK_KEEP_SELECTION = ::VerifierUtil::SM_CHUNK_KEEP_SELECTION;
	static const SelectionMode SM_CHUNK_DEL_SELECTION = ::VerifierUtil::SM_CHUNK_DEL_SELECTION;
	static const SelectionMode SM_ZOOM_DYN_SELECTION = ::VerifierUtil::SM_ZOOM_DYN_SELECTION;
	static const SelectionMode SM_CHUNK_AUTO_DETECT = ::VerifierUtil::SM_CHUNK_AUTO_DETECT;
	static const SelectionMode SM_CHUNK_DEL_WITH_TEST = ::VerifierUtil::SM_CHUNK_DEL_WITH_TEST;
	static const SelectionMode SM_CHUNK_AUTO_DEL_BASED_ON_VOLUME =
		::VerifierUtil::SM_CHUNK_AUTO_DEL_BASED_ON_VOLUME;
	/// Set selection mode
	///
	/// Sets a selection mode defined by the given enum. After this all the selects will behave
	/// accordingly.
	/// @param [in] selectionMode mwMachSimVerifier::SelectionMode for the selection
	virtual void MWMSV_API SetSelectionMode(SelectionMode selectionMode) = 0;

	/// Get selection mode
	///
	/// Retrieve the active selection mode as mwMachSimVerifier::SelectionMode
	///  @return SelectionMode
	virtual SelectionMode MWMSV_API GetSelectionMode() const = 0;

	/// Select a 3d point on the displayed workpiece using 2d screen coordinates.
	///
	/// Then performs an action depending on what mode was set with SetSelectionMode().
	///
	/// This method only works in combination with mwMachSimVerifier::Draw(). If you are using a
	/// custom renderer and mwMachSimVerifier::Render() you have to unproject the screenpoint to a
	/// 3d point yourself and use the method mwMachSimVerifier::SelectSurfaceInfo3d().
	///
	/// Requires a valid OpenGL context.
	///
	/// Note This method may fail if the stock was drawn with transparency before.
	/// To make it work, you have to make sure that the depth buffer is filled
	/// properly after the previous drawing call. This could be done directly after drawing
	/// by performing a 2nd render pass that only renders into the depth buffer.
	///
	/// @param [in] x x position in screen coordinates
	/// @param [in] y y position in screen coordinates
	/// @param [out] vertex vertex 3d position of the selected surface point
	/// @param [out] deviation current deviation value at this surface point.
	/// @param [out] moveID the id of the move which modified the surface point, -1 if the surface
	/// point was not touched
	/// @param [out] matrix offset and rotation of stock, *this is not needed anymore*
	/// @returns True, if a point on stock-surface was found. False otherwise
	virtual bool MWMSV_API Select(
		int x,
		int y,
		float3d& vertex,
		float& deviation,
		float& moveID,
		const cadcam::mwHomogenousMatrix& matrix) = 0;

	/// Select additional info from a surface-point
	///
	/// In contrast to Select(), this method ignores the selection-mode set by SetSelectionMode().
	/// It has the purpose to retrieve information from the stock's surface.
	///
	/// This method only works in combination with mwMachSimVerifier::Draw(). If you are using a
	/// custom renderer and mwMachSimVerifier::Render() you have to unproject the screenpoint to a
	/// 3d point yourself and use the method mwMachSimVerifier::SelectSurfaceInfo3d().
	///
	/// Requires a valid OpenGL context.
	///
	/// Pointer-arguments may be zero, if the value should not be returned.
	/// @param [in] x x position in screen coordinates
	/// @param [in] y y position in screen coordinates
	/// @param [out] vertex vertex 3d position of the selected surface point
	/// @param [out] normal the surface normal at the selected point
	/// @param [out] moveID The custom moveID, @a SetMoveID. Parameter is not changed, if selected
	/// surface-point is from initial stock (no move (cut) has touched the surface yet).
	/// @param [out] deviation The deviation of the stock's surface to the target-mesh, if this mesh
	/// was set before by SetTarget().
	/// @param [out] partID The partID of the selected surface point. Only available, if
	/// MarkChunks() was called before. If not available, *partID is 0. Valid partsIDs are in the
	/// range [1..MarkChunks()].
	/// @param [out] toolID The toolID of the selected surface point
	/// @param [out] tangent of the tool-surface or zero if is not machined
	/// @param [out] velocity direction of the tool or zero if is not machined
	/// @param [out] orientation of the tool or zero if is not machined
	/// @param [in] matrix offset and rotation of stock, *this is not needed anymore*
	/// @returns True, if a point on stock-surface was found. False otherwise
	virtual bool MWMSV_API SelectSurfaceInfo(
		int x,
		int y,
		const cadcam::mwHomogenousMatrix& matrix,
		float3d* vertex = 0,
		float3d* normal = 0,
		float* moveID = 0,
		float* deviation = 0,
		int* partID = 0,
		int* toolID = 0,
		float3d* tangent = 0,
		float3d* velocity = 0,
		float3d* orientation = 0,
		bool* revolvedSurface = 0) = 0;

	/// Returns surface information at the given 3d point.
	///
	/// In contrast to SelectSurfaceInfo(), this method takes a 3d point in world space to select a
	/// point on the stock's surface. Since SelectSurfaceInfo() can only be used in combination with
	/// @ref Draw(), any Render() integration has to use SelectSurfaceInfo3d() instead.
	///
	/// @warning Some of the values are only filled if the surface was cut at the given position,
	/// and if the cut history was enabled (see @ref SetNoCutHistory()). Otherwise the values will
	/// be set to -1, or left uninitialized. <br> To check whether those values are available you
	/// **have to request `hasValidMove`**. If it is true, then the values can be used. <br> This
	/// affects:
	/// * @p moveID
	/// * @p toolID
	/// * @p colliding
	/// * @p tangent
	/// * @p velocity
	/// * @p orientation
	///
	///	@param [in] position position in world space
	///	@param [out] vertex vertex 3d position of the selected surface point
	///	@param [out] normal the surface normal at the selected point
	///	@param [out] moveID The custom moveID, @a SetMoveID. Parameter is not changed, if selected
	///   surface-point is from initial stock (no move (cut) has touched the surface yet).
	///	@param [out] deviation The deviation of the stock's surface to the target-mesh, if this mesh
	///   was set before by SetTarget().
	///	@param [out] partID The partID of the selected surface point. Only available, if
	///   MarkChunks() was called before. If not available, *partID is 0. Valid partsIDs are in the
	///   range [1..MarkChunks()].
	///	@param [out] toolID The toolID of the selected surface point
	///	@param [out] hasValidMove true if a valid move was selected
	///	@param [out] colliding true if the move is colliding
	///	@param [out] targetID the targetID of the nearest target
	///	@param [out] deviationValid true if the returned deviation is valid
	///	@param [out] partIDValid true if the returned partID is valid
	///	@param [in] maxAllowedDistance If not -infinity, will set constrain, how far the select
	///   point can be from position
	///	@param [out] tangent of the tool-surface or zero if is not machined
	///	@param [out] velocity direction of the tool or zero if is not machined
	///	@param [out] orientation of the tool or zero if is not machined
	virtual bool MWMSV_API SelectSurfaceInfo3d(
		const float3d& position,
		float3d* vertex = 0,
		float3d* normal = 0,
		float* moveID = 0,
		float* deviation = 0,
		int* partID = 0,
		int* toolID = 0,
		bool* hasValidMove = 0,
		bool* colliding = 0,
		int* targetID = 0,
		bool* deviationValid = 0,
		bool* partIDValid = 0,
		float maxAllowedDistance = mathdef::MW_MAX_FLOAT,
		float3d* tangent = 0,
		float3d* velocity = 0,
		float3d* orientation = 0,
		bool* revolvedSurface = 0) = 0;

	/// Increases zoom level on the given workpiece depending on the selection mode.
	///
	/// The selection mode can be changed via SetSelectionMode().
	///
	/// SM_ZOOM_DYN_SELECTION: Choose a bounding box based on the current camera position. The
	/// box will include that part of the stock that is currently visible. This only works if Draw()
	/// has been called before. If you're using Render() in your implementation you have to use
	/// IncreaseZoomToBB instead(). This requires a valid OpenGL context.
	///
	/// SM_ZOOMBOX_SELECTION: This selection mode allows the user to select a zoom box via the
	/// Select() API, by selecting two points in space. This mode will also draw box outlines around
	/// the selected area.
	///
	/// You can also call IncreaseZoomToBB() to zoom to any other box, irregardless of the
	/// current selection mode.
	///
	/// The zoom can be decreased via @sa DecreaseZoom().
	virtual void MWMSV_API IncreaseZoom() = 0;

	/// Decreases zoom level on the given workpiece depending on the selection mode
	///
	/// The zoom boxes are implemented as a stack. After calling DecreaseZoom() you can call
	/// IncreaseZoom() to return to the previous zoom box.
	virtual void MWMSV_API DecreaseZoom() = 0;

	/// IncreaseZoomToBB
	///
	/// Perform dynamic zoom to the volume inside a bounding box defined by two 3d points.
	///	@note The actually used bounding box for zooming may be slightly larger than the passed one.
	///	@param [in] bbMin the bottom corner of the bounding box
	///	@param [in] bbMax the top corner of the bounding box
	virtual void MWMSV_API IncreaseZoomToBB(const float3d& bbMin, const float3d& bbMax) = 0;

	/// ClearMeasurementPoints
	///
	/// Remove specified item from list of points
	///	@param [in] index index of measurement item. -1 to remove all items.
	virtual void MWMSV_API ClearMeasurementPoints(int index = -1) = 0;

	/// AddPartPoint
	///
	/// Add specified point to the list of parts points.
	///	@param [in] point point to add.
	virtual void MWMSV_API AddPartPoint(const float3d& point) = 0;

	/// ClearPartsPoints
	///
	/// Remove specified item from list of points
	///	@param [in] index index of measurement item. -1 to remove all items.
	virtual void MWMSV_API ClearPartsPoints(int index = -1) = 0;

	/// ClearMeasurementDistances
	///
	/// Remove specified item from list of distances
	///	@param [in] index index of measurement item. -1 to remove all items.
	virtual void MWMSV_API ClearMeasurementDistances(int index = -1) = 0;

	/// Sets the back color
	///
	/// @deprecated
	///	Sets the back color of all labels
	///	please use the specialized methods e.q. SetGougeLabelColors()
	virtual void MWMSV_API SetLabelBackColor(const float3d& col) = 0;

	/// Set the text color
	///
	/// @deprecated
	///	Sets the text color of all labels
	///	please use the specialized methods e.q. SetGougeLabelColors()

	virtual void MWMSV_API SetLabelTextColor(const float3d& col) = 0;

	/// Set the transparency value
	///
	/// @deprecated
	///	Sets the transparency value of all labels
	///	please use the specialized methods e.q. SetGougeLabelColors()
	virtual void MWMSV_API SetLabelTransparency(float a) = 0;

	/// Set Gouge Label Colors
	///
	/// Define the mwMachSimVerifier::Color values (r,g,b) and the alpha value for the gouge labels.
	///	The alpha value defines the amount of transparency of the label when
	///	the transparency in the LabelAppearace is enabled.
	/// @param [in] cText mwMachSimVerifier::Color of the text and the label border and pinpoint of
	/// type mwMachSimVerifier::Color
	/// @param [in] cBackground mwMachSimVerifier::Color of the label background of type
	/// mwMachSimVerifier::Color
	virtual void MWMSV_API
	SetGougeLabelColors(mwMachSimVerifier::Color cText, mwMachSimVerifier::Color cBackground) = 0;

	/// Define the mwMachSimVerifier::Color values (r,g,b,a) for the excess labels.
	///
	/// The alpha value defines the amount of transparency of the label when the transparency in
	/// the LabelAppearace is enabled.
	///
	/// @param [in] cText mwMachSimVerifier::Color of the text and the label border and pinpoint of
	/// type mwMachSimVerifier::Color
	/// @param [in] cBackground mwMachSimVerifier::Color of the label background of type
	/// mwMachSimVerifier::Color
	virtual void MWMSV_API
	SetExcessLabelColors(mwMachSimVerifier::Color cText, mwMachSimVerifier::Color cBackground) = 0;

	/// Set Point Label Colors
	///
	/// Define the mwMachSimVerifier::Color values (r,g,b) and the alpha value for the measured
	/// surface point labels. The alpha value defines the amount of transparency of the label when
	/// the transparency in the LabelAppearace is enabled.
	/// @param [in] cText mwMachSimVerifier::Color of the text and the label border and pinpoint of
	/// type mwMachSimVerifier::Color
	/// @param [in] cBackground mwMachSimVerifier::Color of the label background of type
	/// mwMachSimVerifier::Color
	virtual void MWMSV_API
	SetPointLabelColors(mwMachSimVerifier::Color cText, mwMachSimVerifier::Color cBackground) = 0;

	/// Set distance Label Colors
	///
	/// Define the mwMachSimVerifier::Color values (r,g,b) and the alpha value for the distance
	/// labels. The alpha value defines the amount of transparency of the label when the
	/// transparency in the LabelAppearace is enabled.
	/// @param [in] cText mwMachSimVerifier::Color of the text and the label border and pinpoint of
	/// type mwMachSimVerifier::Color
	/// @param [in] cBackground mwMachSimVerifier::Color of the label background of type
	/// mwMachSimVerifier::Color
	virtual void MWMSV_API SetDistanceLabelColors(
		mwMachSimVerifier::Color cText, mwMachSimVerifier::Color cBackground) = 0;

	/// Structure which contains a the texts masks for the labels allowing them do customize or
	/// localize. Used in SetLabelTextMask()
	typedef ::VerifierUtil::mwLabelTextMask LabelTextMask;

	/// Set the label text mask strings
	///
	/// Allows to set a custom string for the text labels, to to be shown on the workpiece.
	/// @throws "mwvDrawLabelsHandler::VerifyForBoostFormat failed!" with aditional information
	/// about the text which failed.
	/// @param [in] mask of strings of LabelTextMask
	virtual void MWMSV_API SetLabelTextMask(const LabelTextMask& mask) = 0;

	/// Structure which contains the data to define the appearance of a label.
	typedef ::VerifierUtil::mwLabelAppearance LabelAppearance;

	/// Set Label Appearance
	///
	/// Define the Appearance for all labels.
	/// @param  [in] appearance a struct which contains the definition of the LabelAppearance
	virtual void MWMSV_API SetLabelAppearance(LabelAppearance appearance) = 0;

	/// Enable the graphic display of  measurement labels
	///
	/// @param [in] bIsMeasurementVisible TRUE measurement labels should be drawn
	/// @return A verifier error code
	virtual MWV_ERRORCODE MWMSV_API SetMeasurementVisibility(bool bIsMeasurementVisible) = 0;

	/// Get the volume of the initial stock piece before any cutting. Should be called after
	/// initializing the stock piece. @sa GetInitialStockVolume
	virtual float MWMSV_API GetInitialStockVolume() const = 0;

	/// Get the current volume of the stock piece
	///
	/// Calling this regularly during cutting is expensive.
	/// @sa GetInitialStockVolume
	virtual float MWMSV_API GetCurrentStockVolume() const = 0;

	/// Get number of triangles drawn
	///
	/// Get the number of triangles drawn in last Draw() or Render() call.
	/// @return The number of triangles that are drawn in last Draw() or Render() call.
	virtual size_t MWMSV_API GetTrianglesDrawn() const = 0;

	/// @sa VerifierUtil::mwPolyLine3dTree
	typedef VerifierUtil::mwPolyLine3dTree PolyLine3dTree;
	/// @sa VerifierUtil::mwPolyLine3dTree
	typedef VerifierUtil::mwPolyLine3dTreeVectorPtr PolyLine3dTreeVectorPtr;

	/// Calculate the intersection of the current stock with a list of given parallel planes
	///
	/// For each plane, a @ref VerifierUtil::mwPolyLine3dTree is returned. It is a tree of closed
	/// polylines, where the top nodes are the outermost polylines. All elements in a subtree are
	/// inside the surrounding polyline. The following elements are omitted:
	/// - single points (e.g. a cube corner),
	/// - all polylines that enclose zero area (e.g. a cube edge),
	/// - all polylines that enclose stock surface elements (e.g. a cube face).
	///
	/// All outer polylines are oriented in counterclockwise direction with respect to any
	/// right-handed coordinate system with the plane normal as positive z axis. All inner polylines
	/// are oriented in clockwise direction.
	///
	/// @param [in] planeNormal: normal vector of all planes. This vector is also used to define
	/// rotational direction for contours.
	/// @param [in] planeOffsets: A list of offset values. For a single value planeOffset, each
	/// point p on the plane satisfies planeNormal * p = planeOffset, where '*' is the scalar
	/// product.
	virtual PolyLine3dTreeVectorPtr MWMSV_API GetIntersectionPlanesStock(
		const float3d& planeNormal, const std::vector<float>& planeOffsets) = 0;

	/// Calculate the remaining stock height relative to a plane on the inside of given polylines.
	///
	/// This procedure takes the current stock and calculates the maximal point of the stock surface
	/// (including edge sharpening) with respect to the given plane normal. The search for a maximum
	/// is restricted to the inside of a given tree of polylines, where counterclockwise orientation
	/// is considered as an outside boundary.
	///
	/// If there is no material, the remaining stock height will be mathdef::MW_MIN_FLOAT, maxPoint
	/// is invalid then.
	/// @param [in] planeNormal: normal vector of the plane. This vector is also used to define
	/// rotational direction for polylines.
	/// @param [in] planeOffset: each point p on the plane satisfies planeNormal * p = planeOffset,
	/// where '*' is the scalar product.
	/// @param [in] polyLines: the polylines, the maximal point has to be inside. Typically, the
	///             output of @ref GetIntersectionPlanesStock().
	/// @param [out] maxPoint: One point, where the maximal remaining stock height is reached.
	virtual float MWMSV_API GetRemainingStockHeight(
		const float3d& planeNormal,
		const float& planeOffset,
		const PolyLine3dTree& polyLines,
		float3d& maxPoint) = 0;

	typedef VerifierUtil::RayCastFace RayCastFace;

	/// Determine intersection of the specified ray with the stock mesh.
	/// @param [out] distance distance to the detected intersection point
	/// @param [out] normal surface normal in the detected intersection point
	/// @param [in] pos ray origin
	/// @param [in] direction ray direction
	/// @param [in] maxDistance maximal casting distance along the ray
	/// @param [in] face specifies the desired face orientation, relative to the ray direction
	/// @return true if succeed.
	///
	/// @note To speed up the operation enable Primitives-Cache EnablePrimitivesCache().
	virtual bool MWMSV_API CastRay(
		float& distance,
		float3d& normal,
		const float3d& pos,
		const float3d& direction,
		float maxDistance,
		RayCastFace face = VerifierUtil::RAYCAST_ANY_FACE) = 0;

	typedef VerifierUtil::TracedEdge TracedEdge;

	/// Trace contour of a closest edge.
	/// @param [in] pos reference position for the search of a closest contour
	/// @param [in] traceBox area of tracing
	/// @param [in] arcFitTolerance tolerance of the arc fitting, if zero, uses default, if
	///		negative, the arc detection will be not performed
	/// @return true if succeed.
	///
	/// @note To speed up the operation enable Primitives-Cache EnablePrimitivesCache().
	virtual bool MWMSV_API TraceEdge(
		TracedEdge& edge,
		const float3d& pos,
		const cadcam::mw3dfOrientedBoundingBox& traceBox,
		float arcFitTolerance = 0) = 0;

	/// @deprecated Use TraceEdge(TracedEdge& edge, ...) instead.
	MW_DEPRECATED("Deprecated in 2021.14, use TraceEdge(TracedEdge& edge, ...) instead")
	virtual bool MWMSV_API TraceEdge(
		cadcam::mw2dfContourPtr& edgeContour,
		cadcam::mwHomogenousMatrix& edgeTransform,
		const float3d& pos,
		const cadcam::mw3dfOrientedBoundingBox& traceBox,
		float arcFitTolerance = 0) = 0;

	/// @hidden
	/// Trace contour on the section-plane, defined by specified position and normal.
	/// @param [out] sectionTransform transformation of traced 2D contour to the stock-coordinaes
	/// @param [in] pos reference position on the section plane for the search of a closest contour
	/// @param [in] normal normal of the section plane
	/// @param [in] maxDistance maximal distance of tracing
	/// @param [in] arcFitTolerance tolerance of the arc fitting, if zero, uses default, if
	///		negative, the arc detection will be not performed
	/// @return true if succeed.
	///
	/// @note To speed up the operation enable Primitives-Cache EnablePrimitivesCache().
	virtual bool MWMSV_API TraceSection(
		cadcam::mw2dfContourPtr& sectionContour,
		cadcam::mwHomogenousMatrix& sectionTransform,
		const float3d& pos,
		const float3d& normal,
		float maxDistance,
		float arcFitTolerance = 0) = 0;
	/// @}

	/// @name Interface Recording
	/// Methods to create a binary log which records all calls to this class, as well as their
	/// parameters. Internally these logs are called "CSB logs".
	///
	/// The resulting binary can be replayed, which is invaluable for debugging. We will usually ask
	/// you to create one of these logs whenever you encounter an issue in your integration. This
	/// allows us to reproduce it and either fix the problem, or to point you to an integration
	/// issue.
	/// @{

	/// Start recording. The file will be placed next to mwVerifier.dll, with a filename that's
	/// based on the current timestamp (verifier[timestamp].csb).
	///
	/// Recording is stopped by calling @ref StopRecord(), or by destructing mwMachSimVerifier.
	virtual void MWMSV_API StartRecord() = 0;

	/// Start recording to @p sRecordPathName. We suggest that you use the file ending ".csb".
	///
	/// Recording is stopped by calling @ref StopRecord(), or by destructing mwMachSimVerifier.
	virtual void MWMSV_API StartRecord(const misc::mwstring sRecordPathName) = 0;

	/// Start recording to a stream
	///
	/// Recording is stopped by calling @ref StopRecord(), or by destructing mwMachSimVerifier.
	virtual void MWMSV_API StartRecord(misc::mwBinOutputStream& stream) = 0;

	/// Flushing disables buffering of the output stream. That makes sures that all calls are
	/// included, even if the application crashes. This is not enabled by default, since it makes
	/// recording slower.
	///
	/// This method must be called before calling @ref StartRecord().
	virtual void MWMSV_API SetRecordFlushing(const bool enabled) = 0;

	/// @see StartRecord()
	virtual void MWMSV_API StopRecord() = 0;

	/// @see StartRecord()
	virtual bool MWMSV_API IsRecording() const = 0;

	/// Load a previously recorded CSB log. The log can be played using @ref
	/// PlayNextStep().
	///
	/// @see StartRecord()
	virtual void MWMSV_API OpenPlayer(const misc::mwstring sRecordPathName) = 0;
	/// @copydoc OpenPlayer
	virtual void MWMSV_API OpenPlayer(misc::mwBinInputStream& stream) = 0;

	/// Returns true if a CSB log was loaded, and if there are steps left to play.
	virtual bool MWMSV_API IsPlaying() const = 0;

	/// Executes the next step in the log
	///
	/// The simplest way to play an entire log is:
	/// @code
	/// verifier.OpenPlayer("log.csb");
	/// while (true) {
	///     misc::mwstring stepDescription = verifier.PlayNextStep();
	///     if (stepDescription == "")
	///         break;
	/// }
	/// @endcode
	///
	/// @return A string that describes the executed step or an empty string if record has ended.
	virtual const misc::mwstring& MWMSV_API PlayNextStep() = 0;

	/// Close player and free resources.
	virtual void MWMSV_API ClosePlayer() = 0;
	/// @}

	/// @name Simulation Store and Restore
	///	The interface allows to store the current simulation state and restore it afterwards.
	///	The stored state includes the stock, targets, parameters, all performed and buffered cuts,
	///	and collision meshes. After the restoring, the verifier obtain exactly the same state it had
	///	before the storing.
	/// @{
	typedef ::VerifierUtil::StaticSimulationData StaticSimulationData;
	/// Static data of the current simulation.
	///
	/// Retrieves the static data of the current simulation in order to use by SaveSimulation() or
	/// SaveStock().
	/// @sa SaveSimulation
	/// @sa SaveStock
	virtual StaticSimulationData MWMSV_API GetStaticSimulationData() const = 0;

	/// Load the simulation.
	///
	/// Restore the current simulation state.
	/// @param [in] pathName the full path to the file
	/// @param [in] externalData the externally stored static data excluded from loaded simulation
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED) when the
	/// specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa LoadStock
	virtual void MWMSV_API LoadSimulation(
		const misc::mwstring& pathName, const StaticSimulationData* externalData = MW_NULL) = 0;
	
	/// Load the simulation.
	///
	/// Restore the current simulation state.
	/// @param [in] stream the input stream
	/// @param [in] externalData the externally stored static data excluded from loaded simulation
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED) when the
	/// specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa LoadStock
	virtual void MWMSV_API LoadSimulation(
		misc::mwBinInputStream& stream, const StaticSimulationData* externalData = MW_NULL) = 0;

	/// Store the current simulation state.
	///
	/// @param [in] pathName the full path to the file
	/// @param [in] externalData the externally stored static data excluded from saving in order to
	/// reduce the size of stored data. The data could be obtained by calling of
	/// GetStaticSimulationData()
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveStock
	virtual void MWMSV_API SaveSimulation(
		const misc::mwstring& pathName, const StaticSimulationData* externalData = MW_NULL) = 0;
	
	/// Store the current simulation state.
	///
	/// @param [in] stream the output stream
	/// @param [in] externalData the externally stored static data excluded from saving in order to
	/// reduce the size of stored data. The data could be obtained by calling of
	/// GetStaticSimulationData()
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveStock
	virtual void MWMSV_API SaveSimulation(
		misc::mwBinOutputStream& stream, const StaticSimulationData* externalData = MW_NULL) = 0;
	/// @}

	/// @name Stock Store and Restore
	///	The interface allows to store the current stock in order to use it afterwards as initial
	///   stock by another simulation.
	/// @{
	/// Load the stock and set it as initial stock.
	///
	/// Can load stocks serialized with the deprecated SerializeCurrentStock() method.
	///
	/// In order to apply the current data model and simulation precision to the loaded stock please
	/// use the ResimulateStock() method.
	///
	/// @param [in] pathName the full path to the file
	/// @param [in] externalData the externally stored static data excluded from loaded simulation
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED)
	///	when the specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa GetCurrentStockDataModel
	/// @sa GetCurrentStockPrecision
	/// @sa ResimulateStock
	/// @sa LoadSimulation
	virtual void MWMSV_API LoadStock(
		const misc::mwstring& pathName, const StaticSimulationData* externalData = MW_NULL) = 0;
	
	/// Load the stock and set it as initial stock.
	///
	/// Can load stocks serialized with the deprecated SerializeCurrentStock() method.
	///
	/// In order to apply the current data model and simulation precision to the loaded stock please
	/// use the ResimulateStock() method.
	///
	/// @param [in] stream the input stream
	/// @param [in] externalData the externally stored static data excluded from loaded simulation
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED)
	///	when the specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa GetCurrentStockDataModel
	/// @sa GetCurrentStockPrecision
	/// @sa ResimulateStock
	/// @sa LoadSimulation
	virtual void MWMSV_API LoadStock(
		misc::mwBinInputStream& stream, const StaticSimulationData* externalData = MW_NULL) = 0;

	/// Store the current stock in order to use it as initial stock by another simulation.
	///
	/// Writing the stock using a file path will store it using data compression.
	///
	/// Buffered, not-yet-simulated moves will be discarded.
	///
	/// By providing a misc::mwBinOutputStream you can customize how the stock should be stored.
	/// We provide two implementations of this interface: misc::mwMemoryIOStream, which stores
	/// the stock in memory, and mwStdBinaryStream, which writes the stock to disk without
	/// compression. You can provide a custom storage method by deriving from the mwBinOutputStream
	/// interface.
	///
	/// @param [in] pathName the full path to the file
	/// @param [in] externalData the externally stored static data excluded from saving in order to
	/// reduce the size of stored data. The data could be obtained by calling of
	/// GetStaticSimulationData()
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveSimulation
	virtual void MWMSV_API SaveStock(
		const misc::mwstring& pathName, const StaticSimulationData* externalData = MW_NULL) = 0;

	/// Store the current stock in order to use it as initial stock by another simulation.
	///
	/// Writing the stock using a file path will store it using data compression.
	///
	/// Buffered, not-yet-simulated moves will be discarded.
	///
	/// By providing a misc::mwBinOutputStream you can customize how the stock should be stored.
	/// We provide two implementations of this interface: misc::mwMemoryIOStream, which stores
	/// the stock in memory, and mwStdBinaryStream, which writes the stock to disk without
	/// compression. You can provide a custom storage method by deriving from the mwBinOutputStream
	/// interface.
	///
	/// @param [in] stream the output stream
	/// @param [in] externalData the externally stored static data excluded from saving in order to
	/// reduce the size of stored data. The data could be obtained by calling of
	/// GetStaticSimulationData()
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveSimulation
	virtual void MWMSV_API SaveStock(
		misc::mwBinOutputStream& stream, const StaticSimulationData* externalData = MW_NULL) = 0;
	/// @}

	/// @name Diverse serialisation methods
	/// @{
	/// Load simulation parameters.
	virtual void MWMSV_API LoadParameters(const misc::mwstring& pathName) = 0;

	/// Save simulation parameters.
	virtual void MWMSV_API SaveParameters(const misc::mwstring& pathName) = 0;

	/// @deprecated Please use SaveStock() or SaveRestorePoint().
	MW_DEPRECATED("Use SaveStock() or SaveRestorePoint()")
	virtual void MWMSV_API SerializeCurrentStock(const misc::mwstring& pathName) = 0;
	MW_DEPRECATED("Use SaveStock() or SaveRestorePoint()")
	virtual void MWMSV_API SerializeCurrentStock(misc::mwBinOutputStream& stream) = 0;

	/// @deprecated Please use LoadStock() or LoadRestorePoint().
	MW_DEPRECATED("Use LoadStock() or LoadRestorePoint()")
	virtual void MWMSV_API DeserializeCurrentStock(const misc::mwstring& pathName) = 0;
	MW_DEPRECATED("Use LoadStock() or LoadRestorePoint()")
	virtual void MWMSV_API DeserializeCurrentStock(misc::mwBinInputStream& stream) = 0;

	/// @deprecated Please use SaveRestorePoint().
	MW_DEPRECATED("Use SaveRestorePoint()")
	virtual void MWMSV_API SerializeSimulatedMoveList(const misc::mwstring& pathName) = 0;
	MW_DEPRECATED("Use SaveRestorePoint()")
	virtual void MWMSV_API SerializeSimulatedMoveList(misc::mwBinOutputStream& stream) = 0;

	/// @deprecated Please use LoadRestorePoint(const misc::mwstring&).
	MW_DEPRECATED("Use LoadRestorePoint()")
	virtual void MWMSV_API DeserializeSimulatedMoveList(const misc::mwstring& pathName) = 0;
	/// @deprecated Please use LoadRestorePoint(misc::mwBinInputStream&)
	MW_DEPRECATED("Use LoadRestorePoint()")
	virtual void MWMSV_API DeserializeSimulatedMoveList(misc::mwBinInputStream& stream) = 0;
	/// @}

	/// @name Simulation State Management
	///	The following methods allow you to store the simulation state at some point and then be able
	///   to restore it back.
	/// @{
	/// Create restore point for the current simulation state.
	///
	/// Removes all restore-points lie after the currently created.
	/// @return {(new id), true} if a new restore-point has been created or {(previous id), false}
	///	if there is no changes happened since the last restore-point
	virtual std::pair<misc::mwstring, bool> MWMSV_API CreateRestorePoint() = 0;

	/// Restore the simulation state saved by CreateRestorePoint().
	///
	/// @param id restore-point identificator returned by CreateRestorePoint()
	/// @throws mwVerifierException(mwVerifierException::INVALID_RESTORE_POINT) when the specified
	/// restore point is unknown
	virtual void MWMSV_API Restore(const misc::mwstring& id) = 0;

	/// Remove the restore point created by CreateRestorePoint().
	///
	/// Additionally removes all restore-points lie after the last restore-point.
	/// @param id restore-point identificator returned by CreateRestorePoint
	virtual void MWMSV_API RemoveRestorePoint(const misc::mwstring& id) = 0;

	/// Remove all restore points.
	virtual void MWMSV_API RemoveAllRestorePoints() = 0;

	/// Create a new simulation restore point and save it into the specified file or stream.
	///
	/// @param [in] pathName the full path to the file
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveSimulation
	virtual void MWMSV_API SaveRestorePoint(const misc::mwstring& pathName) = 0;

	/// Create a new simulation restore point and save it into the specified file or stream.
	///
	/// @param [in] stream the output stream
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @sa SaveSimulation
	virtual void MWMSV_API SaveRestorePoint(misc::mwBinOutputStream& stream) = 0;

	/// Load simulation restore point.
	///
	/// Restores the simulation state at the specified restore point. The loaded restore point
	///	does not contain the entire simulation. Thus, in order to load the restore point
	///	in a newly created verifier, the corresponding simulation should be loaded first with
	///	LoadSimulation() method.
	/// @param [in] pathName the full path to the file
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED)
	///	when the specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @throws mwVerifierException(mwVerifierException::INVALID_RESTORE_POINT) when the specified
	/// restore point does not belong to the current simulation
	/// @sa LoadSimulation
	virtual void MWMSV_API LoadRestorePoint(const misc::mwstring& pathName) = 0;

	/// Load simulation restore point.
	///
	/// Restores the simulation state at the specified restore point. The loaded restore point
	///	does not contain the entire simulation. Thus, in order to load the restore point
	///	in a newly created verifier, the corresponding simulation should be loaded first with
	///	LoadSimulation() method.
	/// @param [in] stream the input stream
	/// @throws mwmiscException(mwmiscException::THE_REQUESTED_FILE_COULD_NOT_BE_LOADED)
	///	when the specified file was not found
	/// @throws mwmiscException(mwmiscException::UNKNOWN_FILE_FORMAT) when the loading is failed
	/// @throws mwmiscException(mwmiscException::USER_HAS_ABORTED_THE_OPERATION) when was aborted by
	/// progress handler
	/// @throws mwVerifierException(mwVerifierException::INVALID_RESTORE_POINT) when the specified
	/// restore point does not belong to the current simulation
	/// @sa LoadSimulation
	virtual void MWMSV_API LoadRestorePoint(misc::mwBinInputStream& stream) = 0;
	/// @}

	/// @name Stock Splitting Off
	/// @{
	/// Moves the selected chunks to a new verifier object.
	virtual void MWMSV_API SplitOffClampedChunks(
		const std::vector<float3d>&
			clampPoints,  ///< chunks touching these world coordinates are selected
		const float
			clampTouchingTolerance,  ///< maximum allowed distance of a chunk from the clamp points
		mwMachSimVerifier& splitOffTarget  ///< target verifier
		) = 0;

	/// Moves the selected chunks to a new verifier object.
	///
	/// Chunks are selected using their chunk id. The selected chunks are deleted from this object.
	virtual void MWMSV_API
	SplitOffChunksWithIds(const std::vector<int>& chunkIds, mwMachSimVerifier& splitOffTarget) = 0;

	/// Merge chunks from previously split off verifier back to engine.
	///
	/// Current requirements:
	///
	/// 0) Workpiece-type: The workpieces inside verifierToBeMerged and the current verifier
	///    must both be mwvExtFieldWorkpieces.
	///
	/// 1) The stock to be merged must have identical dimensions as the target stock:
	///    - same number of grid-points in each direction (x,y,z)
	///    - exact same distance between grid-points
	///
	///    This is automatically the case if it was created by calling SplitOffClampedChunks or
	///    SplitOffChunksWithIds.
	///
	/// 2) Limited compatibility with:
	///    - stock refinement
	///    - some color schemes etc.
	///    To ensure functionality in regard to these, if you split off a chunk and want to
	///    merge it back later, do not modify it (i.e. cutting, further splitting). If you
	///    do not need this functionality, you are free to modify it.
	///
	/// @param verifierToBeMerged The verifier whose stock will be merged with the current verifier
	virtual void MWMSV_API MergeChunksAfterSplit(mwMachSimVerifier& verifierToBeMerged) = 0;
	/// @}

	/// Limit the number of internal worker threads
	///
	/// The number of threads actually used may be smaller than the number given, but never higher.
	///	A value of zero removes the limit.
	virtual void MWMSV_API LimitThreadCount(int maximumThreadCount) = 0;
	/// @sa LimitThreadCount
	virtual int MWMSV_API GetThreadCountLimit() const = 0;

	/// Specify storage to use instead of Windows registry
	virtual void MWMSV_API
	SetParamsStorageCustomFactory(misc::mwParamsStorageCustomFactory* storage) = 0;
	/// @sa SetParamsStorageCustomFactory
	virtual misc::mwParamsStorageCustomFactory* MWMSV_API GetParamsStorageCustomFactory() const = 0;

	/// @name Deprecated Multi Thread Methods
	/// @deprecated This interface will be removed in future releases, it currently has no longer
	/// any effect.
	/// @{
	/// @deprecated has no effect
	MW_DEPRECATED("Not needed anymore")
	virtual void MWMSV_API ActivateThreads() = 0;

	/// @deprecated has no effect
	MW_DEPRECATED("Not needed anymore")
	virtual void MWMSV_API ActivateThreads(mwThreadHandlerInterface& threadhandler) = 0;

	/// @deprecated has no effect
	MW_DEPRECATED("Not needed anymore")
	virtual void MWMSV_API SuspendThreads() = 0;
	/// @}

	/// @name Cutting Result Interface
	///
	/// Cutting results are incremental changes of the internal stock data model.
	/// They can be used for further analysis, e.g. cutting forces.
	/// See also
	/// [raw&nbsp;cutting&nbsp;results](doc/Developer_guide/Cutting_Additive_Simulation/Cutter_Engagement_Analysis/Raw_cutting_results.md).
	///
	/// @note This API is very low level and should only used for advanced integrations. Usually you
	/// should use the [engagement API](@ref CutSim_engagement_API).
	///
	/// @{

	typedef ::VerifierUtil::mwFieldCoordinateScaling FieldCoordinateScaling;
	typedef ::VerifierUtil::mwCuttingResultEntry CuttingResultEntry;
	typedef std::vector<CuttingResultEntry> CuttingResultVector;
	typedef CuttingResultVector* CuttingResultVectorPtr;
	typedef ::VerifierUtil::CuttingResult_TransformationInfo CuttingResult_TransformationInfo;

	/// Register up to 3 vectors per tool-element to append the amount of removed material, sorted
	/// by MoveNumber. Removed material will be added  when e.g. @ref SimulateBufferedCuts(), @ref
	/// SimulateMove() or any other move/cut simulating method is called.
	///
	/// When the workpiece-representation is not @ref MWV_FM_DEXELBLOCK, only @p pResultsForXYZ will
	/// be filled.
	///
	/// If a pointer is null, cutting-results are deactivated for this vector.
	///
	/// When there is at least one registered vector in use, the simulation might turn off some
	/// speed-optimizations.
	///
	/// When all vectors are overwritten with 0, the simulation turns back to all available
	/// speed-optimizations.
	///
	/// The callback is automatically unregistered, if the workpiece is resized or reinitialized
	/// (for example by calling SetMesh() or Reset()).
	///
	/// The memory for the CuttingResultVectors must be allocated outside of the verifier; it will
	/// not be freed by the verifier.
	///
	/// The CuttingResultVectors are never cleared by the verifier. Results are only appended.
	virtual void MWMSV_API SetCuttingResultCallback_And_GetTransformationInfo(
		CuttingResult_TransformationInfo& transformationInfo,
		const cadcam::mwToolPartSelector toolPartSelector,
		CuttingResultVectorPtr pResultsForXYZ = 0,
		CuttingResultVectorPtr pResultsForZXY = 0,
		CuttingResultVectorPtr pResultsForYZX = 0) = 0;
	/// @}

	/// @name Engagement Tracking API
	/// @anchor CutSim_engagement_API
	///
	/// This API can be used to get information on how much material a tool removed and where it
	/// touched the stock. This can be used to compute e.g. cutting forces or other advanced
	/// analysis features. See also
	/// [Cutter&nsbp;Engagement&nbsp;Analysis](doc/Developer_guide/Cutting_Additive_Simulation/Cutter_Engagement_Analysis/_main_.md).
	///
	/// To get engagement, call the following getter methods after SimulateBufferedCuts(),
	/// SimulateMove(), or Cut*().Make sure to enable it with EnableEngagementTracking(true).
	///
	/// Engagement is only computed for a limited set of tools and simulation modes:
	/// - most revolved tools
	/// - "cutting" tool behavior (no additive/collision checking)
	/// - data model: MWV_FM_DEXELBLOCK
	///
	/// @note In case engagement can't be computed the API currently returns "no engagement". You'll
	/// additionally receive a warning when subscribing to them via @ref SetNotificationHandler().
	/// In an upcoming release we plan to redesign the output of the APIs to properly mark missing
	/// engagement reports.
	/// @{

	/// Enables/disables the engagement tracking for the next move.
	///
	/// Can be switched on/off before individual BufferedCut() calls. Only enables tracking for the
	/// cutting part of the tool.
	virtual void MWMSV_API EnableEngagementTracking(const bool enabled) = 0;

	/// @see EnableEngagementTracking()
	virtual bool MWMSV_API IsEngagementTrackingEnabled() const = 0;

	/// Get engagement areas for all previously simulated cuts.
	///
	/// The engagement area describes the area of the 3d tool surface that is in engagement.
	/// See also
	/// [derived&nbsp;measures](doc/Developer_guide/Cutting_Additive_Simulation/Cutter_Engagement_Analysis/Derived_measures.md).
	///
	/// @note Only works when enabled by @ref EnableEngagementTracking().
	virtual void MWMSV_API GetEngagementAreas(std::vector<float>& areaPerMove) = 0;

	/// Get engagement widths for all previously simulated cuts.
	///
	/// The engagement width is the maximum extension of the engagement patch orthogonal to the tool
	/// axis. So engagement directly in front of the tool axis (looking from feed direction) has
	/// width 0. If the entire tool is in engagement the width is approximately the maximum tool
	/// diameter. See also
	/// [derived&nbsp;measures](doc/Developer_guide/Cutting_Additive_Simulation/Cutter_Engagement_Analysis/Derived_measures.md).
	///
	/// @note Only works when enabled by @ref EnableEngagementTracking().
	virtual void MWMSV_API GetEngagementWidths(std::vector<float>& widthPerMove) = 0;

	/// Get the engagement depths for all previously simulated cuts.
	///
	/// Engagement depth is the highest point of the tool that is in engagement (projected on the
	/// tool axis). The reference point (depth 0) is the tool tip. See also
	/// [derived&nbsp;measures](doc/Developer_guide/Cutting_Additive_Simulation/Cutter_Engagement_Analysis/Derived_measures.md).
	///
	/// @note Only works when enabled by @ref EnableEngagementTracking().
	virtual void MWMSV_API GetEngagementDepths(std::vector<float>& depthPerMove) = 0;

	typedef cadcam::mw2ddPolyLine EngagementProfile;
	typedef misc::mwAutoPointer<const EngagementProfile> EngagementProfilePtr;
	typedef std::pair<float, float> EngagementAngle;
	typedef std::vector<EngagementAngle> EngagementAngleList;
	typedef std::vector<EngagementAngleList> EngagementAngleListList;

	/// Get the engagement angles for all previously simulated cuts.
	///
	/// You can transform the angles to world coordinates using the helper methods in
	/// @ref mwvEngagementHelpers.hpp.
	/// @param toolProfilesPerMove Contains the polygonized profile of the tool for each cut. The
	///       profile is null if a tool is not supported.
	/// @param anglesPerMove Contains angle intervals per
	///       move and profile segment. So anglesPerMove[0][i] would be mapped on
	///       tolProfilesPerMove[0]->GetLineBegin() + i.
	///
	/// @note Only works when enabled by @ref EnableEngagementTracking().
	virtual void MWMSV_API GetEngagementAngles(
		std::vector<EngagementProfilePtr>& toolProfilesPerMove,
		std::vector<EngagementAngleListList>& anglesPerMove) = 0;

	typedef cadcam::mw2dBoundingBox<float> EngagementBox;
	typedef std::vector<std::vector<EngagementBox>> EngagementBoxListList;

	/// Returns the engagement boxes for all previously simulated cuts for which engagement tracking
	/// was enabled.
	///
	/// Like in @ref GetEngagementAngles() you get engagement information per tool slice. However,
	/// while GetEngagementAngles() only gives you [angleLeft, angleLeft] per slice,
	/// GetEngagementBoxes() gives you [angleLeft, angleRight, yBottom, yTop]. This is especially
	/// useful to find the lowest or highest point on the tool that is in engagement.
	///
	/// Y=[0.0 .. 1.0] is the position along the tool profile segment associated with the slice. The
	/// height of the slices can be customized via @ref SetEngagementOptions(). By default it is
	/// derived from the stock precision. There are a few helper methods in @ref
	/// mwvEngagementHelpers.hpp, to transform the boxes from feed system to world system.
	///
	/// You only receive engagement information for moves where engagement tracking was enabled (see
	/// @ref EnableEngagementTracking()), and if the tool is supported by engagement tracking (see
	/// @ref CutSim_engagement_API). Otherwise the move is omitted from the result vectors. To map
	/// the engagement data back to the move index you therefore need to remember for which moves
	/// engagement tracking was enabled.
	///
	/// @param toolProfilesPerMove Contains the polygonized profile of the tool for each cut. The
	///        profile is null if a tool is not supported.
	/// @param boxesPerMove Contains boxes per move and profile segment. So boxesPerMove[0][i]
	///        would be mapped on tolProfilesPerMove[0]->GetLineBegin() + i.
	///	       X describes the angle, between -pi and pi, where 0 points into the move direction.
	///        Y describes the relative height on the profile segment, between 0 and 1.
	virtual void MWMSV_API GetEngagementBoxes(
		std::vector<EngagementProfilePtr>& toolProfilesPerMove,
		std::vector<EngagementBoxListList>& boxesPerMove) = 0;

	typedef VerifierUtil::EngagementTransformations EngagementTransformations;
	/// Get transformations for e.g. angles and boxes from other engagement getters, see
	/// @ref VerifierUtil::EngagementTransformations
	virtual void MWMSV_API GetEngagementTransformations(
		std::vector<EngagementTransformations>& transformationsPerMove) = 0;

	/// Enables/disables the volume tracking.
	/// Starts tracking of volume data per cut. Can be switched on/off before individual
	/// @ref BufferedCut() calls.
	virtual void MWMSV_API EnableVolumeTracking(const bool enabled) = 0;

	/// @see EnableVolumeTracking()
	virtual bool MWMSV_API IsVolumeTrackingEnabled() const = 0;

	/// Fetches the removed volume values for the last (buffered) cuts tracked by the VolumeTracking
	/// feature.
	///
	/// For moves where volume tracking was disabled a value of -1.0 will be inserted.
	virtual void MWMSV_API GetRemovedVolumes(std::vector<float>& volumePerMove) = 0;

	typedef ::VerifierUtil::EngagementOptions EngagementOptions;
	/// Set engagement options to customize some of the engagement behavior. See @ref
	/// VerifierUtil::EngagementOptions.
	virtual void MWMSV_API SetEngagementOptions(const EngagementOptions& options) = 0;
	/// @sa SetEngagementOptions()
	virtual void MWMSV_API GetEngagementOptions(EngagementOptions& options) const = 0;


	/// @name Bottom/Side Engagement API
	///
	/// @deprecated This API is deprecated since 2019.12. Please use
	/// the [new Engagement API](@ref CutSim_engagement_API).
	///
	/// @{

	/// @deprecated Deprecated since 2019.12. Please use new Engagement API, see
	/// EnableEngagementTracking()
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see EnableEngagementTracking()")
	virtual void MWMSV_API StartEngagementTracking(
		const float engagementPrecision = mathdef::MW_MIN_FLOAT,
		const float engagementDexelCutThreshold = 0.0f,
		const float engagementDexelCutThresholdBottomEdge = 0.0f) = 0;

	/// @deprecated
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see EnableEngagementTracking()")
	virtual bool MWMSV_API IsBottomSideEngagementTrackingEnabled() const = 0;

	/// @deprecated
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see EnableEngagementTracking()")
	virtual void MWMSV_API StopEngagementTracking() = 0;

	/// @deprecated
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see EnableEngagementTracking()")
	const virtual float MWMSV_API GetEngagementPrecision() const = 0;


	/// @deprecated Corrected typo: Use GetEngagementAngles() instead
	MW_DEPRECATED("Corrected typo: Use GetEngagementAngles() instead")
	virtual void MWMSV_API GetEngagmentAngles(
		float& removedVolume,
		EngagementAngleListList& heightAngles,
		EngagementAngleListList& radiusAngles) = 0;

	/// @deprecated Deprecated since 2019.12. Please use new Engagement API, see
	/// @ref GetEngagementAngles()
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see "
		"GetEngagementAngles(vector<EngagementProfilePtr>&, vector<EngagementAngleListList>&)")
	virtual void MWMSV_API GetEngagementAngles(
		float& removedVolume,
		EngagementAngleListList& heightAngles,
		EngagementAngleListList& radiusAngles) = 0;

	/// @deprecated Deprecated since 2019.12. Please use new Engagement API, see
	/// @ref GetEngagementAngles()
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see "
		"GetEngagementAngles(vector<EngagementProfilePtr>&, vector<EngagementAngleListList>&)")
	virtual void MWMSV_API GetEngagementAngles(
		std::vector<EngagementAngleListList>& sideAnglesPerMove,
		std::vector<EngagementAngleListList>& bottomAnglesPerMove) = 0;

	/// @deprecated Deprecated since 2019.12. Please use new Engagement API, see
	/// @ref GetEngagementDepths()
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Engagement API, see GetEngagementDepths()")
	virtual float MWMSV_API GetCutterDepth() = 0;

	/// @deprecated Deprecated since 2019.12. Please use new Volume Tracking API, see
	/// @ref EnableVolumeTracking(), @ref GetRemovedVolumes()
	MW_DEPRECATED(
		"Deprecated since 2019.12. Please use new Volume Tracking API, see EnableVolumeTracking(), "
		"GetRemovedVolumes()")
	virtual void MWMSV_API GetEngagementVolumes(std::vector<float>& volumePerMove) = 0;
	/// @}

	/// @name Debugging
	/// @{

	/// Logs some internal debug data
	///
	/// @deprecated This logger doesn't log much interesting information. Use @ref
	/// SetDebugOutputStream to capture a more useful (and much more verbose) log.
	virtual void MWMSV_API SetLogger(const misc::mwAutoPointer<misc::mwLogger>& logger) = 0;

	/// By default mwMachSimVerifier looks for a VerifierEngine.ini file next to the mwVerifier.dll.
	///
	/// In this .ini file you can place lots of flags for debugging, as well as experimental
	/// settings for which we don't have an API yet. Usually our Support will pass these to you if
	/// suitable.
	///
	/// You can also set them directly, via @ref SetDebugIniSetting().
	virtual bool MWMSV_API SetDebugIniName(const misc::mwstring v_path) = 0;

	typedef ::VerifierUtil::DebugCompareStockSettings DebugCompareStockSettings;
	typedef ::VerifierUtil::DebugCompareStockResult DebugCompareStockResult;

	/// Compare stock against another one for debugging
	///
	/// This should not be used in any integration, it is used by ModuleWorks internally only.
	virtual DebugCompareStockResult MWMSV_API DebugCompareStock(
		const misc::mwstring& filename,
		const DebugCompareStockSettings& settings,
		const bool drawInOpenGL = false) = 0;

	/// Compare two serialized stocks against each other for debugging
	///
	/// This should not be used in any integration, it is used by ModuleWorks internally only.
	virtual DebugCompareStockResult MWMSV_API DebugCompareStocks(
		const misc::mwstring& stockFilename1,
		const misc::mwstring& stockFilename2,
		const DebugCompareStockSettings& settings) const = 0;

	/// Put a log-message in internal logging. They will show up in Microsoft's DebugView.exe, or in
	/// the stream given to @ref SetDebugOutputStream().
	///
	/// Not meant to be used in a regular CutSim-integration. Integration team or support might ask
	/// to use this to identify problems.
	virtual void MWMSV_API LogCustomMessage(const misc::mwstring& message) = 0;

	/// Enable or disable floating point exceptions
	///
	/// The verifier overwrites the floating-point-exception state in each relevant interface call
	/// (e.g. Cut()) and restores the previous state when leaving that call.
	///
	/// @param enabled If true, floating point exception throw a c++ exception of type
	/// misc::mwException. Otherwise they are ignored silently.
	virtual void MWMSV_API SetFloatingPointExceptionsEnabled(const bool enabled) = 0;
	/// @see SetFloatingPointExceptionsEnabled()
	virtual bool MWMSV_API GetFloatingPointExceptionEnabled() = 0;

	/// Before doing large allocations the verifier checks the current system memory load. If it is
	/// larger than the memory load given here then an exception is thrown. This is done to avoid
	/// using the system heap, although that can still happen.
	///
	/// @p max is a value between 0 and 1. By default this is 0.95 (95 %).
	virtual void MWMSV_API SetMaxMemoryLoad(const float max) = 0;

	/// @see SetMaxMemoryLoad().
	virtual float MWMSV_API GetMaxMemoryLoad() const = 0;

	/// The refine estimates whether the refined mesh will fit into the memory. By default it
	/// assumes that the size of a rendered triangle on the user side is 132 bytes. You can specify
	/// the real size of your triangle to improve the estimation.
	virtual void MWMSV_API SetRenderedTriangleSize(size_t size) = 0;

	/// @see SetRenderedTriangleSize()
	virtual size_t MWMSV_API GetRenderedTriangleSize() const = 0;

#ifdef _WIN32
	/// @hidden
	virtual int MWMSV_API DrawDebugOverlay(HWND window) = 0;

	/// @hidden
	virtual LRESULT MWMSV_API IterateDebugOverlay(UINT message, WPARAM wParam, LPARAM lParam) = 0;
#endif  // _WIN32

	typedef ::VerifierUtil::mwvExperimentalSettings mwvExperimentalSettings;

	/// @see SetExperimentalSettings
	virtual void MWMSV_API GetExperimentalSettings(mwvExperimentalSettings& expSettings) const = 0;

	/// Experimental settings are either for features in development, settings that come with large
	/// caveats, or that have limited use. They should not be used unless advised otherwise, and
	/// they can be removed/changed any time.
	virtual void MWMSV_API SetExperimentalSettings(const mwvExperimentalSettings& expSettings) = 0;

	/// Set debug flags available in VerifierEngine.ini. Should not be used unless advised
	/// otherwise. Can be removed/changed any time!
	///
	/// Global: Effects all verifiers!
	virtual void MWMSV_API
	SetDebugIniSetting(const misc::mwstring& name, const misc::mwstring& value) = 0;

	/// Reset debug flag to default value.
	///
	/// Global: Effects all verifiers!
	virtual void MWMSV_API ResetDebugIniSetting(const misc::mwstring& name) = 0;

	/// Get debug flags available in VerifierEngine.ini. Should not be used unless advised
	/// otherwise. Can be removed/changed anytime!
	///
	/// See also SetDebugIniSetting(), ResetDebugIniSetting().
	virtual misc::mwstring MWMSV_API GetDebugIniSetting(const misc::mwstring& name) const = 0;

	typedef VerifierUtil::mwExperimentalMethods mwvExperimentalMethods;
	/// Experimental methods are either for features in development, features that come with large
	/// caveats, or that have limited use. They should not be used unless advised otherwise, and
	/// they can be removed/changed any time.
	virtual mwvExperimentalMethods& MWMSV_API GetExperimentalMethods() = 0;

	/// Set the stream used by this instance of the verifier for dumping Unicode debug messages. The
	/// default stream on Windows is OutputDebugStringW(), on linux it is std::wclog.
	///
	/// The given stream must live for at least as long as the verifier object.
	///
	/// To get more detailed messages you can set ShowDebugMessages to 1 in
	/// [VerifierEngine.ini](@ref SetDebugIniName) or @ref SetDebugIniSetting.
	virtual void MWMSV_API SetDebugOutputStream(std::wostream& debugStream) = 0;

	/// Set the stream used by default for dumping Unicode debug messages. Affects all verifier
	/// instances within the process. It is used as a fallback when the specific stream was not set,
	/// or in some cases where it does not work (usually parallelized regions).
	///
	/// The given object must live until the last verifier object is destructed, or until @ref
	/// ResetDefaultDebugOutputStream is called.
	virtual void MWMSV_API SetDefaultDebugOutputStream(std::wostream& debugStream) = 0;

	/// Reset the stream used by default for dumping Unicode debug messages. Affects all verifier
	/// instances within the process.
	virtual void MWMSV_API ResetDefaultDebugOutputStream() = 0;

	/// @}

	/// @name Cut interpolation
	/// @{

	/// @deprecated Please use VerifierUtil::mwvLinearCutStepInterpolator.
	MW_DEPRECATED("Please use VerifierUtil::mwvLinearCutStepInterpolator.")
	virtual size_t MWMSV_API
	InterpolateCut(const float maxLength, const Frame& start, const Frame& end) = 0;

	/// @deprecated Please use VerifierUtil::mwvArcCutStepInterpolator.
	MW_DEPRECATED("Please use VerifierUtil::mwvArcCutStepInterpolator.")
	virtual size_t MWMSV_API InterpolateCircularCut(
		const float maxLength,
		const Frame& start,
		const Frame& end,
		const Point& circleCenter,
		const Point& circlePlaneNormal,
		const float toolPathTolerance) = 0;

	/// @deprecated Please use VerifierUtil::mwvLinearCutStepInterpolator or
	/// VerifierUtil::mwvArcCutStepInterpolator.
	MW_DEPRECATED("Please see InterpolateCut(), InterpolateCircularCut().")
	virtual bool MWMSV_API GetNextInterpolatedCutStep(Frame& pos1, Frame& pos2) = 0;

	/// @}
};

inline void VerifierUtil::mwvChunkDetectionKeepHandler::OnChunksChanged(
	mwMachSimVerifier& verifier, size_t, size_t)
{
	verifier.DeleteChunksNotTouching(m_fixturePoints, m_equalTolerance);
}

/// These functions are deprecated: the mwVerifier.dll is now linked via
/// a .lib file, instead of using LoadLibrary().
MW_DEPRECATED("Please use mwMachSimVerifier::Create() instead!")
typedef mwMachSimVerifier*(MW_STDCALL* mwMachSimVerifierCreateProc)();
MW_DEPRECATED("Please use mwMachSimVerifier::CreateWithDebugStream(...) instead!")
typedef mwMachSimVerifier*(MW_STDCALL* mwMachSimVerifierCreateDebugProc)(std::wostream*);
MW_DEPRECATED("Please use mwMachSimVerifier::Create() instead!")
typedef void(MW_STDCALL* mwMachSimVerifierFreeProc)(mwMachSimVerifier* verifier);

#endif
