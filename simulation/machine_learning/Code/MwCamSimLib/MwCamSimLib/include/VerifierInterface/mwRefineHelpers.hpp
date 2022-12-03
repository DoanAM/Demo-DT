// (C) 2015-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWREFINEHELPERS_HPP_
#define MW_MWREFINEHELPERS_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mw2dBoundingBox.hpp>
#include <mw2dGeometryTypedefs.hpp>
#include <mw3dBoundingBox.hpp>
#include <mwMatrix.hpp>


namespace VerifierUtil
{
struct RefineBox;
class RedrawNotifier;

namespace mwRefineHelpers
{
struct MW_VERIFIER_API DepthBufferContent
{
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	std::vector<float> depthBuffer;
	int width;
	int height;
	int depthBits;
	cadcam::mwHomogenousMatrix projection;
	cadcam::mwHomogenousMatrix view;

	DepthBufferContent() : width(0), height(0), depthBits(0) {}
};

/// An abstract interface for a draw method.
struct MW_VERIFIER_API DrawCallback
{
	virtual ~DrawCallback(){};
	virtual void Draw() = 0;
};

/// Render with OpenGL to obtain the depth values of the visible surface.
///
/// This method has to be called inside a valid OpenGL context and with the right
/// modelview and projection matrices set up. This method is restoring the original state,
/// such that it can be called in between any other rendering.
///	@param [in] drawCallback should render the scene into the depth buffer, but nothing more.
MW_VERIFIER_API void GetDepthBufferFromOpenGLStack(
	DepthBufferContent& result, DrawCallback& drawCallback);


/// Computes an axis aligned bounding box around the visible surface.
///
/// @param [in] depthBufferContent A description of the visible surface, which
///	can be extracted out of OpenGL using GetDepthBufferFromOpenGLStack().
MW_VERIFIER_API cadcam::mw3dBoundingBox<float> ComputeVisibleSurfaceAABB(
	const DepthBufferContent& depthBufferContent, int threadCount = -1);


typedef std::vector<RefineBox> RefineLayout;

/// Computes a refine layout based on the visible surface.
///
/// The layout is computed such that surface parts close to the viewer are refined
/// with better quality than the farer ones; also they will be computed before the farer ones.
/// Additionally detected features will be refined, but only after the visible regions are done.
/// @param [in] depthBufferContent A description of the visible surface, which
///	can be extracted out of OpenGL using GetDepthBufferFromOpenGLStack().
/// @param [in] stockPrecision The precision of the stock that should be refined, see
/// mwMachSimVerifier::GetPrecision().
MW_VERIFIER_API RefineLayout
ComputeViewLayout(const DepthBufferContent& depthBufferContent, float stockPrecision);

/// Compute layout to refine inside a bounding box.
///
/// You can combine the results into one common layout and refine it at once. By overlapping
/// areas it will be taken the highest refine factor.
/// @param [in] regionBox A bounding box around the region that should be refined.
/// @param [in] refineFactor The factor describing how many times the precision
///	will be increased. Has to be greater than 1 to have an effect. Only when the refineFactor
///	is greater than already presented, the area will be refined.
MW_VERIFIER_API RefineLayout
ComputeRegionLayout(const cadcam::mw3dBoundingBox<float>& regionBox, int refineFactor);

/// Compute refine layout for all detected features.
///
/// Will refine the stock on regions, where interesting
/// features are detected.This can for example be a sharp edge,
/// a thin drill hole or a small chamfer.
MW_VERIFIER_API RefineLayout ComputeFeatureLayout();

/// Compute refine layout for all detected features.
///
/// @sa ComputeFeatureLayout with adaptive detailing. ComputeAdaptiveFeatureLayout is similar
/// to ComputeFeatureLayout. It means that the refine factor will be detected automatically.
/// The difference is that after all features will be refined, it starts to increase the
/// refine factor step-by-step for the area where new details are appearing.
/// @param [in] maxRefineFactor The maximal reachable refine factor.
MW_VERIFIER_API RefineLayout ComputeAdaptiveFeatureLayout(int maxRefineFactor = 32);


/// Used by ViewUpdater::ComputeLayout
struct MW_VERIFIER_API ViewParameters
{
	cadcam::mwHomogenousMatrix modelViewTransform;
	cadcam::mwHomogenousMatrix projectionTransform;
	cadcam::mw2diBoundingBox viewport;

	inline ViewParameters() {}

	explicit ViewParameters(
		const cadcam::mwHomogenousMatrix& modelViewTransform,
		const cadcam::mwHomogenousMatrix& projectionTransform,
		const cadcam::mw2diBoundingBox& viewport);
};

/// Used by ViewUpdater::ComputeLayout
struct RenderCallback
{
	virtual ~RenderCallback() {}

	/// The application has to render *only* refined stocks to the depth-buffer and read it to @p
	/// depths.
	/// @param [out] depths
	/// @param [out] depthBits Number of bits per pixel.
	/// @return false if failed.
	///
	/// - The populated @p depths has to contain only surface of refined stock. This is required to
	/// find the visible surfaces of the stocks properly.
	/// - The color-buffer is not required and can be disabled.
	/// - If you use the depth-buffer for other purposes, you need to restore it afterwards.
	virtual bool RenderStockAndReadDepths(std::vector<float>& depths, int& depthBits) = 0;
};

/// Computes layouts for mwMachSimVerifier::UpdateAutoRefineLayout() on view changes
///
///	This class helps to integrate the refine feature of mwMachSimVerifier
/// for view dependent refinement. More exactly: This class detects, when the user did
/// kept the view unchanged for some delay. Then it computes the visible regions
/// of the stock, that can be passes to the refinement process of mwMachSimVerifier.
/// A typical usage is to Start() the feature at the beginning of a simulation and
/// pass the result of ComputeLayoutFromOpenGLStack() to mwMachSimVerifier inside the integrators
/// OpenGL draw method. IsLayoutUpdateNeeded() Should be used to not call
/// ComputeLayoutFromOpenGLStack() too often.
class MW_VERIFIER_API ViewUpdater
{
public:
	typedef misc::mwAutoPointer<ViewUpdater> Ptr;

	ViewUpdater();

	~ViewUpdater();

	void Start(const int updateDelayMilliseconds);

	void Stop();

	/// Pass a redraw notifier, that is implemented to trigger Draw event
	///
	/// This is necessary, if the integration does not call it's Draw function
	/// regularly. For example, if the user stops moving the view, this notifier will
	/// be called as soon as the update delay has passed.
	void SetRedrawNotifier(const misc::mwAutoPointer<RedrawNotifier>& notifier);

	/// Return the update delay in milliseconds that was passed in the last Start() call
	int GetUpdateDelay() const;

	/// Returns true, if the layout has to be updated using ComputeLayoutFromOpenGLStack().
	///
	/// This result of this function should be checked before calling
	/// ComputeLayoutFromOpenGLStack() to prevent runtime performance slowdowns.
	/// It has to be called inside the integrations Draw() method, because it needs the OpenGL
	/// stack.
	bool IsLayoutUpdateNeeded() const;

	/// Computes a new layout, if the user view has changed
	///
	/// This method has to be called inside the integrations Draw() method. The result is usually
	/// passed to mwMachSimVerifier::UpdateAutoRefineLayout().
	///	@param renderCallback @see RenderCallback
	/// @param stockPrecision The precision of the stock that should be refined, @see
	/// mwMachSimVerifier::GetPrecision().
	const std::vector<RefineBox>& ComputeLayout(
		RenderCallback& renderCallback, const ViewParameters& viewParameters, float stockPrecision);

	/// Computes a new layout, if the user view has changed
	///
	/// This method has to be called inside the integrations Draw() method. It will
	/// extract information out of the OpenGL stack by calling of GetDepthBufferFromOpenGLStack
	/// and restore the original state afterwards. The result is usually passed to
	/// mwMachSimVerifier::UpdateAutoRefineLayout().
	///	@param [in] stockDrawCallback This object is a integration specific implementation. It
	/// should render the stock (or multiple stocks) into the depth buffer, but nothing more. This
	/// is required to find the visible surfaces of the stocks properly.
	/// @param [in] stockPrecision The precision of the stock that should be refined, see
	/// mwMachSimVerifier::GetPrecision().
	const std::vector<RefineBox>& ComputeLayoutFromOpenGLStack(
		DrawCallback& stockDrawCallback, const float stockPrecision);

private:
	struct Impl;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<Impl> m_pImpl;

	ViewUpdater(const ViewUpdater&);
	void operator=(const ViewUpdater&);
};

}  // namespace mwRefineHelpers
}  // namespace VerifierUtil
#endif  //	MW_MWREFINEHELPERS_HPP_
