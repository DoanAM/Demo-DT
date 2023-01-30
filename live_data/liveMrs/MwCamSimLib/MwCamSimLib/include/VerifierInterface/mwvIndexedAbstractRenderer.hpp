// (C) 2013-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVINDEXEDABSTRACTRENDERER_HPP_
#define MW_MWVINDEXEDABSTRACTRENDERER_HPP_
#include "mwvAbstractRendererAttributes.hpp"
#include "mwvAbstractRendererBase.hpp"
#include "mwvAbstractRendererPrimitives.hpp"


namespace VerifierUtil
{
/// Specialized interface from mwvAbstractRendererBase to receive stock geometry
/// as indexed triangles and lines.
/// @note See also
/// [Visualizing&nbsp;the&nbsp;Workpiece&nbsp;and&nbsp;Tools](doc/Developer_guide/Cutting_Additive_Simulation/Visualizing_the_workpiece_and_tools.md).
class MW_VERIFIER_API mwvIndexedAbstractRenderer : public mwvAbstractRendererBase
{
public:
	typedef unsigned Index;
	typedef mwvAbstractRendererPrimitives::ColorRGBA ColorRGBA;
	typedef mwvAbstractRendererPrimitives::LineVertex LineVertex;
	typedef mwvAbstractRendererPrimitives::TriangleVertex TriangleVertex;
	typedef AbstractRendererAttributes::VertexAttributes VertexAttributes;

	virtual ~mwvIndexedAbstractRenderer();

	/// Updates a triangle group. See also mwvAbstractRendererBase.
	/// @param groupId          The ID of the group.
	/// @param vertices         Array of vertices as mwvAbstractRendererPrimitives::TriangleVertex.
	/// @param numOfVertices    Number of vertices in @p vertices.
	/// @param indicesValid     True, if @p indices are available. When false, @p vertices contains
	///                         numOfVertices/3 triangles.
	/// @param indices          Array of indices for the @p vertices array. Each triple of
	///                         consecutive indices defines a triangle.
	/// @param numOfIndices     Number of indices in @p indices. Undefined when @p indicesValid is
	///                         false.
	/// @param vertexAttributes Requested attributes per vertex. The @p indices also apply for this
	///                         array. See also
	///                         AbstractRendererAttributes::VertexAttributes and
	///                         VerifierUtil::RenderOptions.
	virtual void DrawTriangles(
		const RenderGroupID groupId,
		const TriangleVertex* vertices,
		const size_t numOfVertices,
		const bool indicesValid,
		const Index* indices,
		const size_t numOfIndices,
		const VertexAttributes& vertexAttributes)
		MW_VIRTUAL_PURE_DEFINITION(
			void,
			groupId,
			vertices,
			numOfVertices,
			indicesValid,
			indices,
			numOfIndices,
			vertexAttributes);

	/// Updates a line group. See also mwvAbstractRendererBase.
	/// @param groupId       The ID of the group.
	/// @param vertices      Array of vertices as mwvAbstractRendererPrimitives::LineVertex.
	/// @param numOfVertices Number of vertices in @p vertices.
	/// @param indicesValid  True, if @p indices are available. When false @p vertices contains
	///                      numOfVertices/2 lines.
	/// @param indices       Array of indices for the @p vertices array. Each pair of
	///                      consecutive indices defines a line.
	/// @param numOfIndices  Number of indices in @p indices.
	///                      Undefined when @p indicesValid is false.
	virtual void DrawLines(
		const RenderGroupID groupId,
		const LineVertex* vertices,
		const size_t numOfVertices,
		const bool indicesValid,
		const Index* indices,
		const size_t numOfIndices) = 0;

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

	/// @deprecated Deprecated in 2020.12. Please use @ref
	/// mwvIndexedAbstractRenderer::DrawTriangles()
	MW_DEPRECATED("Deprecated in 2020.12. Please use DrawTriangles(..., vertexAttributes)")
	virtual inline void DrawTriangles(
		const RenderGroupID groupId,
		const TriangleVertex* vertices,
		const size_t numOfVertices,
		const bool indicesValid,
		const Index* indices,
		const size_t numOfIndices)
	{
		// Default implemented to be able to use DrawTriangles(..., vertexAttributes) only.
		MW_AVOID_WARNING_UNREFERENCED_PARAM(
			groupId, vertices, numOfVertices, indicesValid, indices, numOfIndices);
	};
};

}  // namespace VerifierUtil
#endif  //	MW_MWVINDEXEDABSTRACTRENDERER_HPP_
