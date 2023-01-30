// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Main-class Measure::Tool

#ifndef MW_MWVMEASURETOOL_HPP_
#define MW_MWVMEASURETOOL_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierMathForward.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mw3dGeometryTypedefs.hpp>
#include <mwAutoPointer.hpp>
#include <mwDeprecated.hpp>

class mwMachSimVerifier;

namespace VerifierUtil
{
namespace Measure
{
namespace Internal
{
class ToolDetail;
}

/// Main class of Smart-Measure feature. It lets you:
/// - define and manage the measured objects such as verifier-stocks and meshes
/// - highlight the measure-points and measured geometry
/// - manage the measure-points
/// - access the measurement results
/// - draw the interface.
///
/// The class is not thread-safe and is designed to run completely in UI-thread.
///
/// See also
/// [Smart-Measure](doc/Developer_guide/Cutting_Additive_Simulation/Smart_Measure/_main_.md)
class MW_VERIFIER_API Tool
{
public:
	struct Renderer
	{
		enum Value
		{
#if !defined(NO_GL) && !defined(MW_IGNORE_GL) && !defined(MW_NO_GL)
			openGL,  ///< Native openGL drawing.
			openGLdebug,  ///< Native openGL drawing for debug purposes.
#endif
		};
	};
	/// Constructor for a native drawing-class implementation.
	/// @throws
	///   mwVerifierException(mwVerifierException::CUTTING_SIMULATION_SMART_MEASURE_LICENSE_INVALID)
	///   if there is no license
	explicit Tool(
		Renderer::Value renderer, const misc::mwAutoPointer<WindowCallbacks>& windowCallbacks);

	/// Constructor for a custom drawing-class implementation.
	/// @throws
	///   mwVerifierException(mwVerifierException::CUTTING_SIMULATION_SMART_MEASURE_LICENSE_INVALID)
	///   if there is no license
	explicit Tool(
		const misc::mwAutoPointer<Drawing>& drawing,
		const misc::mwAutoPointer<WindowCallbacks>& windowCallbacks);

	~Tool();


	/// @name Measured objects
	/// All measured objects must be added to the Tool class. There are the following methods:
	/// AddVerifier(), AddMesh() and AddObject(). All methods return an identifier for the added
	/// object. The object-identifier is needed to set a transformation for the object or to remove
	/// it later. The object-identifier also specifies the object in the dimensions.
	///
	/// You can change the transformations of measured-objects by calling
	/// SetMeasuredObjectTransform(). An object initially gets an identity transformation.
	/// @{

	/// Adds a guarded @p verifier stock as a measured object.
	/// @return object id > 0
	///
	/// @note To speed up the measurement operations on the verifier stock it is recommended to
	/// enable Primitives-Cache in verifier @ref mwMachSimVerifier::EnablePrimitivesCache().
	MeasuredObjectID AddVerifier(mwMachSimVerifier& verifier);

	/// @copydoc AddVerifier(mwMachSimVerifier&)
	MeasuredObjectID AddVerifier(const misc::mwAutoPointer<GuardedVerifier>& verifier);

	/// Adds a @p mesh as a measured object. The specified mesh must be a manifold mesh.
	/// @param minEdgeAngle A minimum angle in radians between two normals to create an edge.
	/// @param maxNormalSmoothAngle A maximum angle in radians between two normals to be smoothed.
	///   If zero, smoothing is not performed.
	/// @param posTolerance Tolerance of the positions. If zero, the default is used.
	/// @param arcFitTolerance Tolerance for arc fitting. If zero, the default is used.
	/// @return object id > 0
	MeasuredObjectID AddMesh(
		const misc::mwAutoPointer<const cadcam::mwfMesh>& mesh,
		float minEdgeAngle = 0.4f,
		float maxNormalSmoothAngle = 0.4f,
		float posTolerance = 0,
		float arcFitTolerance = 0);

	/// Adds a @p mesh as a measured object. The specified mesh must be a manifold mesh.
	/// @param edgePoints Pairs of mesh point indices.
	/// @param maxNormalSmoothAngle A maximum angle in radians between two normals to be smoothed.
	///   If zero, smoothing is not performed.
	/// @param posTolerance Tolerance of the positions. If zero, the default is used.
	/// @param arcFitTolerance Tolerance for arc fitting. If zero, the default is used.
	/// @return object id > 0
	MeasuredObjectID AddMesh(
		const misc::mwAutoPointer<const cadcam::mwfMesh>& mesh,
		const std::vector<int>& edgePoints,
		float maxNormalSmoothAngle = 0.4f,
		float posTolerance = 0,
		float arcFitTolerance = 0);

	/// Adds a @p mesh as a measured object. The specified mesh must be a manifold mesh.
	/// @param minEdgeAngle A minimum angle in radians between two normals to create an edge.
	/// @param maxNormalSmoothAngle A maximum angle in radians between two normals to be smoothed.
	///   If zero, smoothing is not performed.
	/// @param posTolerance Tolerance of the positions. If zero, the default is used.
	/// @param arcFitTolerance Tolerance for arc fitting. If zero, the default is used.
	/// @return object id > 0
	MeasuredObjectID AddMesh(
		const std::vector<misc::mwAutoPointer<const cadcam::mwfMesh>>& submeshes,
		float minEdgeAngle = 0.4f,
		float maxNormalSmoothAngle = 0.4f,
		float posTolerance = 0,
		float arcFitTolerance = 0);

	/// @copydoc AddMesh(const std::vector<misc::mwAutoPointer<const cadcam::mwfMesh>>&, float, float, float, float)
	MeasuredObjectID AddMesh(
		const std::vector<misc::mwAutoPointer<cadcam::mwfMesh>>& submeshes,
		float minEdgeAngle = 0.4f,
		float maxNormalSmoothAngle = 0.4f,
		float posTolerance = 0,
		float arcFitTolerance = 0);

	/// Adds a @p mesh as a measured object. The specified mesh must be a manifold mesh.
	/// @param maxNormalSmoothAngle A maximum angle in radians between two normals to be smoothed.
	///   If zero, smoothing is not performed.
	/// @param posTolerance Tolerance of the positions. If zero, the default is used.
	/// @param arcFitTolerance Tolerance for arc fitting. If zero, the default is used.
	/// @return object id > 0
	MeasuredObjectID AddMesh(
		const std::vector<MeshWithEdges>& submeshes,
		float maxNormalSmoothAngle = 0.4f,
		float posTolerance = 0,
		float arcFitTolerance = 0);

	/// The returned mesh is different from the original mesh specified in AddMesh(). The mesh has
	/// a counter-clockwise orientation.
	/// @return null if @p id is not valid.
	misc::mwAutoPointer<cadcam::mwfMesh> GetMesh(MeasuredObjectID id) const;

	/// The edges are stored as pairs of points. Each pair contains indices of the mesh points
	/// returned by GetMesh().
	/// @return null if @p id is not valid.
	misc::mwAutoPointer<std::vector<int>> GetMeshEdges(MeasuredObjectID id) const;

	// Adds a custom measured @p object.
	/// @return object id > 0
	MeasuredObjectID AddObject(const misc::mwAutoPointer<MeasuredObjectInterface>& object);

	void ShowMeasuredObject(MeasuredObjectID id, bool show = true);

	bool IsMeasuredObjectVisible(MeasuredObjectID id) const;

	/// This method automatically updates the computed dimensions.
	///
	/// Performance: @ref CutSim_SmartMeasure_Highlighting
	void SetMeasuredObjectTransform(MeasuredObjectID id, const Frame& transform);

	Frame GetMeasuredObjectTransform(MeasuredObjectID id) const;

	/// If an invalid @p id is specified, nothing is performed.
	void RemoveMeasuredObject(MeasuredObjectID id);

	void RemoveAllMeasuredObjects();
	/// @}


	/// @name Selection
	/// To perform measurement, you must set the measure-points. Setting or changing the
	/// measure-points automatically updates the dimensions.
	///
	/// You can use the highlighting to highlight the measure-points and display geometrical
	/// features under the cursor.
	///
	/// You can reset the highlight and measure-points with the DiscardMeasurement() method.
	///
	/// @note Camera movement or transformation of objects a force
	/// WindowCallbacks::RenderToStencil() call every time highlighting is used. If the change
	/// is continuous, as in an animation, it may affect the smoothness of the visualization. In
	/// this case it can make sense to skip highlighting until the change is complete.
	/// @{

	void SetSelectionOptions(const SelectionOptions& options);

	const SelectionOptions& GetSelectionOptions() const;

	/// @return whether a measure-point or geometry is currently highlighted.
	bool IsHighlighted() const;

	/// Highlights a measure-point or geometry in @p pos. Resets the current highlight.
	/// @param pos in pixels.
	/// @param maxDistance in pixels.
	/// @param adjustToPrimaryPoint The position on the highlighted geometry will be adjusted to the
	/// primary measure-point. Similar to the option SelectionOptions::adjustToPrimaryPoint for
	/// AddMeasurePoint().
	/// @return true if successful.
	///
	/// Performance: @ref CutSim_SmartMeasure_Highlighting
	bool Highlight(
		const cadcam::mwPoint2di& pos, int maxDistance, bool adjustToPrimaryPoint = false);

	/// Highlights the measure-point in @p pos. Resets the current highlight.
	/// @param pos in pixels.
	/// @param maxDistance in pixels.
	/// @return true if successful.
	bool HighlightMeasurePoint(const cadcam::mwPoint2di& pos, int maxDistance);

	/// Highlights the specified measure-point. Resets the current highlight.
	void HighlightMeasurePoint(MeasurePointIdx idx);

	/// @return -1 if it is not highlighted.
	MeasurePointIdx GetHighlightedMeasurePoint() const;

	/// @return null if it is not highlighted.
	const Geometry* GetHightlightedGeometry() const;

	void ResetHighlight();

	bool HasMeasurePoints() const;

	int GetMeasurePointCount() const;

	/// A primary measure-point is the point that was first added or remained unchanged for the
	/// longest. If you have two measure-points, all measurements will be taken from it to the
	/// secondary point.
	/// @return -1 if there are no measure-points.
	MeasurePointIdx GetPrimaryMeasurePoint() const;

	/// If two points are already set, the secondary point will be replaced.
	/// @param pos in pixels.
	/// @param maxDistance in pixels.
	/// @return -1 if it has not been added.
	MeasurePointIdx AddMeasurePoint(const cadcam::mwPoint2di& pos, int maxDistance);

	/// Changes the @p pos of the existing measure-point. If there are two measure-points, the
	/// changed measure-point becomes the second point.
	/// @param pos in pixels.
	/// @param maxDistance in pixels.
	/// @return true if the specified point has been moved.
	bool SetMeasurePoint(MeasurePointIdx idx, const cadcam::mwPoint2di& pos, int maxDistance);

	/// @return false if the point cannot be projected.
	/// @param pos in pixels.
	bool GetMeasurePointPos(cadcam::mwPoint2di& pos, MeasurePointIdx idx) const;

	/// @return geometry under the measure-point.
	const Geometry& GetMeasurePointGeometry(MeasurePointIdx idx) const;

	/// Determines the index of an existing measure-point at the specified position.
	/// @param pos in pixels.
	/// @param maxDistance in pixels.
	/// @return -1 if not found.
	MeasurePointIdx FindMeasurePoint(const cadcam::mwPoint2di& pos, int maxDistance) const;

	/// Tries to switch the specified measure-point to an alternative position. For example for an
	/// arc-edge the measure-point jumps to the center of the arc.
	/// @return true if successful.
	bool SwitchMeasurePoint(MeasurePointIdx idx);

	void RemoveMeasurePoint(MeasurePointIdx idx);

	void RemoveAllMeasurePoints();
	/// @}


	/// @name Measurement
	/// It is possible to save the performed measurement and restore it later. If you want to
	/// display multiple measurements at once, you can use Draw(const DrawnMeasurements&) to display
	/// the saved measurements.
	/// @{

	/// Resets the highlight and removes the measure-points.
	void DiscardMeasurement();

	/// @return null if the is no measure-points.
	misc::mwAutoPointer<Measurement> GetMeasurement() const;

	/// Recomputes the stored dimensions.
	/// @return
	/// - null if any of the affected measured object does not exist anymore.
	/// - @p measurement if nothing to update.
	misc::mwAutoPointer<Measurement> UpdateMeasurement(
		const misc::mwAutoPointer<Measurement>& measurement);

	void RestoreMeasurePoints(const Measurement& measurement);

	void SetDistanceMode(DistanceMode::Value mode);

	DistanceMode::Value GetDistanceMode() const;
	/// @}


	/// @name Drawing
	/// To display the measurement, call the Draw() method from your application. You must also
	/// call InitializeGraphicsResources() and ReleaseGraphicsResources() after the graphics device
	/// has been initialized and before it is released.  The functions initialize and release
	/// internal resources managed by your graphics device. ReadDepthsAndStencilIndices() explicitly
	/// reads the current depth and stencil buffers after drawing in
	/// WindowCallbacks::RenderToStencil().
	///
	/// You can define your own drawing methods. To do this, use the Measure::Drawing class to
	/// define an abstract interface.
	/// @{

	WindowCallbacks& GetWindowCallbacks() const;

	Drawing& GetDrawing() const;

	DrawStyle& GetDrawStyle() const;

	/// In comparison to DrawStyle::draw* affects only the drawing of the current measurement and
	/// has no effect on the additional measurements specified in Draw(const DrawnMeasurements&)
	void SetDisplayedDimensions(const DisplayedDimensions& dimensions);

	const DisplayedDimensions& GetDisplayedDimensions() const;

	/// Initializes device-dependent internal graphics resources. Must be called after the rendering
	/// device has been initialized.
	///
	/// Calls @ref Drawing::InitializeDeviceResources()
	void InitializeGraphicsResources();

	/// Releases device-dependent internal graphics resources. Must be called before the rendering
	/// device is released.
	///
	/// Calls @ref Drawing::ReleaseDeviceResources()
	void ReleaseGraphicsResources();

	/// Draws highlighting, measure-points and dimensions. The drawing class reads the current
	/// projection and model-view transformations. The model transformation is considered to be a
	/// world-transformation.
	void Draw();

	/// @copydoc Draw()
	/// @param measurements Additional measurements to draw.
	void Draw(const DrawnMeasurements& measurements);

	/// Reads and saves depth and stencil buffers. Must be called from
	/// WindowCallbacks::RenderToStencil. The drawing-class implementation you use may require the
	/// viewport to be set.
	void ReadDepthsAndStencilIndices();
	/// @}


	/// @deprecated Use DiscardMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use DiscardMeasurement() instead")
	void DiscardMeasurements();

	/// @deprecated Use UpdateMeasurement(const misc::mwAutoPointer<Measurement>&) instead.
	MW_DEPRECATED(
		"Deprecated in 2021.04, use UpdateMeasurement(const misc::mwAutoPointer<Measurement>&) "
		"instead")
	misc::mwAutoPointer<Measurement> UpdateMeasurement(const Measurement& measurement);

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Distance* GetThickness() const;

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Distance* GetDepth() const;

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Distance* GetClearance() const;

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Corner* GetCorner() const;

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Curvature* GetCurvature() const;

	/// @deprecated Use GetMeasurement() instead.
	MW_DEPRECATED("Deprecated in 2020.12, use GetMeasurement() instead")
	const Distance* GetDistance() const;

private:
	misc::mwAutoPointer<Internal::ToolDetail> m_detail;

private:
	Tool(const Tool&);
	void operator=(const Tool&);
};

struct WindowCallbacks
{
	virtual ~WindowCallbacks() {}

	/// @return the size of the window's client part.
	virtual cadcam::mwPoint2di GetWindowSize() = 0;

	/// Invalidates window to force redrawing. This function only informs the application of the
	/// need to update the window. The application should not perform rendering immediately.
	virtual void InvalidateWindow() = 0;

	/// Renders the scene by marking the measured objects in the stencil buffer.
	/// @return false if not supported.
	///
	/// - Use GetSurfaceStencilIdx and GetEdgeStencilIdx to compute the corresponding
	/// stencil-indices for the measured objects.
	/// - If you use the verifier for drawing, you must set the obtained measure-id in the current
	/// VerifierUtil::RenderOptions (SetRenderOptions). The verifier then automatically writes the
	/// required value to the stencil-buffer.
	/// - To read both buffers, call Tool::ReadDepthsAndStencilIndices when drawing is finished. If
	/// the method is not called explicitely, it will be called implicitly immediately after the
	/// callback call.
	/// - Depending on the implementation of the drawing-class, ReadDepthsAndStencilIndices may
	/// require the viewport to be set.
	/// - Drawing the measure-tool will be prevented.
	/// - It might be useful not to draw some of the helpers which can affect the selection.
	/// - The color-buffer is not required and can be disabled.
	virtual bool RenderToStencil() = 0;
};

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASURETOOL_HPP_
