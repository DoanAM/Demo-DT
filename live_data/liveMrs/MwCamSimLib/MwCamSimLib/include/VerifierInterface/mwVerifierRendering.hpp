// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// Utility classes and methods for use with rendering (OpenGL, AbstractRenderer)

#ifndef MW_MWVERIFIERRENDERING_HPP_
#define MW_MWVERIFIERRENDERING_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvAbstractRendererPrimitives.hpp"

#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
class mwvAbstractRendererBase;
class mwvAbstractRenderer;
class mwvIndexedAbstractRenderer;

typedef ::cadcam::mwTPoint3d<float> float3d;
}  // namespace VerifierUtil

namespace VerifierUtil
{
namespace mwRendering
{
class MW_VERIFIER_API mwViewState
{
public:
	mwViewState();
	mwViewState(const float3d& cameraPosition, const float3d& viewDirection);
	void SetViewState(const float3d& cameraPosition, const float3d& viewDirection);
	const float3d& GetCameraPosition() const;
	const float3d& GetViewDirection() const;
	bool operator!=(const mwViewState& other) const;

private:
	float3d m_cameraPosition;
	float3d m_viewDirection;
};

float3d MW_VERIFIER_API GetCameraPositionFromOpenGL();
float3d MW_VERIFIER_API GetViewDirectionFromOpenGL();
mwViewState MW_VERIFIER_API GetViewStateFromOpenGL();

class RenderGroupSorterInternal;

/// Helper class to AbstractRenderer to show transparent/translucent triangles well
//
// Background:
//
// When rendering translucent (partly transparent) triangles, these need to be
// rendered from furthest from camera to closest triangle, to avoid several issues.
//
// The following web-pages give some context:
// * https://www.opengl.org/wiki/Transparency_Sorting
// * http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/
//
// The simplest solution mentioned there is:
// 1. draw opaque triangles first
// 2. draw semi-transparent triangles after that, in the order from back to front
//
// A rough and reasonable fast approximation of the above is achieved by this class,
// which does not order the triangles but rather gives the order of the given render
// groups in respect to the current camera position, sorted from furthest to closest.
//
// Usage:
// Use RenderGroupSorter to create a proxy to a given Abstract-Renderer Implementation.
//
//        // Prepare:
//        MyIndexedAbstractRenderer renderer;
//        mwRendering::RenderGroupSorter groupSorter;
//        groupSorter.SetRenderer(&renderer);
//
//        // On Render:
//        groupSorter.SetViewState(mwRendering::GetViewStateFromOpenGL());
//        verifier.Render(groupSorter.GetProxyRenderer());  // calls DrawTriangles() on the
//        proxy-Abstract Renderer, which forwards calls to renderer
//
//        std::vector<int> groups;
//        if (transparencyEnabled) // sort farthest..closest group for current camera position
//            groupSorter.GetSortedGroupIdList(groups);
//        else
//            groupSorter.GetGroupIdList(groups);
//
//        for(auto groupId : groups)
//            RenderGroup(groupId);
//

class MW_VERIFIER_API RenderGroupSorter
{
public:
	typedef mwvAbstractRendererPrimitives::RenderGroupID RenderGroupID;

	RenderGroupSorter();
	explicit RenderGroupSorter(mwvAbstractRendererBase* renderer);

	//@param renderer can be nullptr
	void SetRenderer(mwvAbstractRendererBase* renderer);

	/// Returns a created proxy (indexed) abstract renderer to be used with
	/// mwMachSimVerifier::Render()
	///
	/// This proxy analyzes the created triangle groups for later sorting and acts as a proxy
	/// for the renderer set via SetRenderer, forwarding all calls to the proxied Abstract Renderer.
	///
	/// The object is generated to automatically match that of the set renderer, either
	/// mwvAbstractRenderer or mwvIndexedAbstractRenderer. If no renderer is set the proxy will be
	/// an mwvIndexedAbstractRenderer.
	///
	/// The proxy becomes invalid if a new renderer is set via SetRenderer().
	mwvAbstractRendererBase* GetRendererProxy() const;

	void DeleteAllGroups();
	void GetSortedGroupIdList(std::vector<RenderGroupID>& listSorted);
	void GetGroupIdList(std::vector<RenderGroupID>& list);
	void SetViewState(const mwViewState& viewState);

private:
	misc::mwAutoPointer<RenderGroupSorterInternal> m_impl;
};

}  // namespace mwRendering
}  // namespace VerifierUtil
#endif  //	MW_MWVERIFIERRENDERING_HPP_
