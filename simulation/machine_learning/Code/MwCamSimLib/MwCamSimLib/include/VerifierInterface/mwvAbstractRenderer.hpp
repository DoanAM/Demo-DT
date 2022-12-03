// (C) 2011-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVABSTRACTRENDERER_HPP_
#define MW_MWVABSTRACTRENDERER_HPP_
#include "mwvAbstractRendererAttributes.hpp"
#include "mwvAbstractRendererBase.hpp"
#include "mwvAbstractRendererPrimitives.hpp"

namespace VerifierUtil
{
/// Specialized interface from mwvAbstractRendererBase to receive stock geometry
/// as triangles and lines.
/// @note See also
/// [Visualizing&nbsp;the&nbsp;Workpiece&nbsp;and&nbsp;Tools](doc/Developer_guide/Cutting_Additive_Simulation/Visualizing_the_workpiece_and_tools.md).
class MW_VERIFIER_API mwvAbstractRenderer : public mwvAbstractRendererBase
{
public:
	typedef mwvAbstractRendererPrimitives::ColorRGBA ColorRGBA;
	typedef mwvAbstractRendererPrimitives::RenderedTriangle mwRenderedTriangle;
	typedef mwvAbstractRendererPrimitives::RenderedLine mwRenderedLine;
	typedef AbstractRendererAttributes::VertexAttributes VertexAttributes;

	virtual ~mwvAbstractRenderer();

	/// Updates a triangle group. See also mwvAbstractRendererBase.
	/// @param groupId          The ID of the group.
	///	@param triangles        Array of triangles as
	///                         mwvAbstractRendererPrimitives::RenderedTriangle.
	/// @param numOfTriangles   The number of triangles in @p triangles.
	/// @param vertexAttributes Requested attributes per vertex, see also
	///                         AbstractRendererAttributes::VertexAttributes and
	///                         VerifierUtil::RenderOptions.
	virtual void DrawTriangles(
		const RenderGroupID groupId,
		const mwRenderedTriangle* triangles,
		const size_t numOfTriangles,
		const VertexAttributes& vertexAttributes)
		MW_VIRTUAL_PURE_DEFINITION(void, groupId, triangles, numOfTriangles, vertexAttributes);

	/// Updates a line group. See also mwvAbstractRendererBase.
	/// @param groupId    The ID of the group.
	///	@param lines      Array of lines as mwvAbstractRendererPrimitives::RenderedLine.
	/// @param numOfLines The number of lines in @p lines.
	virtual void DrawLines(
		const RenderGroupID groupId, const mwRenderedLine* lines, const size_t numOfLines) = 0;

	/// See mwvAbstractRendererBase::SetGroupVisibility().
	virtual void SetGroupVisibility(const RenderGroupID groupId, const bool visible)
		MW_VIRTUAL_PURE_DEFINITION(void, groupId, visible);

	/// See mwvAbstractRendererBase::DeleteGroup().
	virtual void DeleteGroup(const RenderGroupID groupId) = 0;

	/// @hidden
	/// Part of the visitor pattern, used internally and does not have to be changed/overridden.
	inline virtual void AcceptVirtual(mwvAbstractRendererVisitor& visitor)
	{
		visitor.Visit(*this);
	};

	/// @deprecated Deprecated in 2020.12. Please use mwvAbstractRenderer::DrawTriangles()
	MW_DEPRECATED("Deprecated in 2020.12. Please use DrawTriangles(..., vertexAttributes)")
	virtual void DrawTriangles(
		const RenderGroupID groupId,
		const mwRenderedTriangle* triangles,
		const size_t numOfTriangles)
	{
		// Default implemented to be able to use DrawTriangles(..., vertexAttributes) only.
		MW_AVOID_WARNING_UNREFERENCED_PARAM(groupId, triangles, numOfTriangles);
	};
};

}  // namespace VerifierUtil
#endif  //	MW_MWVABSTRACTRENDERER_HPP_
