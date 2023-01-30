// (C) 2015-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVABSTRACTRENDERERATTRIBUTES_HPP_
#define MW_MWVABSTRACTRENDERERATTRIBUTES_HPP_
#include <cstddef>
#include <mwDeprecated.hpp>

namespace VerifierUtil
{
namespace AbstractRendererAttributes
{
/// Special value to indicate invalid (non-computed) deviation.
MW_DEPRECATED(
	"Deprecated in 2020.12. Please do not use this, it does not work. To check if the deviation is "
	"invalid you can use std::isnan(v).")
const float INVALID_DEVIATION = ((float)(1e+300 * 1e+300)) * 0.0f;  // NaN

// undefine OpenMesh macro here
#undef VertexAttributes

/// Stores C-arrays of vertex attributes.

/// The pointers to attributes can be NULL. If they are not, they point to "numVertices" elements.
/// Attributes are only filled if requested via @ref mwMachSimVerifier::SetRenderOptions()
///
/// In mwvIndexedAbstractRenderer implementations the attributes can be accessed like this:
///
/// @snippet mwVerifierDocSamples.cpp VertexAttributes_ARI
///
/// In mwvAbstractRenderer implementations the attributes can be accessed at [triangleIdx * 3 +
/// vertexIdx], where vertexIdx is a number between 0 and 2:
///
/// @snippet mwVerifierDocSamples.cpp VertexAttributes_AR
///
/// @note The attribute pointers are kept alive during the duration of the abstract renderer
/// callback (DrawTriangles). After that the internal data structures they point to are deleted. If
/// you want to store the attributes you'll have to copy the values, not the pointers.
///
struct VertexAttributes
{
	/// Initializes every member to 0 / NULL.
	VertexAttributes()
		: numVertices(0),
		  deviations(NULL),
		  operationIds(NULL),
		  collisions(NULL),
		  chunkIds(NULL),
		  toolIds(NULL),
		  moveIds(NULL){};

	VertexAttributes(
		int numVertices,
		const float* deviations,
		const int* operationIds,
		const bool* collisions,
		const int* chunkIds,
		const int* toolIds,
		const int* moveIds)
		: numVertices(numVertices),
		  deviations(deviations),
		  operationIds(operationIds),
		  collisions(collisions),
		  chunkIds(chunkIds),
		  toolIds(toolIds),
		  moveIds(moveIds){};

	/// The number of vertices for which attributes are stored
	const int numVertices;

	/// Absolute deviation values (NaN if no target is set)
	const float* deviations;

	/// Operation IDs
	const int* operationIds;

	/// True if a collision occurred at a vertex
	const bool* collisions;

	/// Make sure to call @ref mwMachSimVerifier::MarkChunks() to receive up-to-date chunk ids.
	const int* chunkIds;

	/// Tool IDs
	const int* toolIds;

	/// Move IDs
	const int* moveIds;

private:
	VertexAttributes& operator=(const VertexAttributes& other);  // = delete
};
}  // namespace AbstractRendererAttributes
}  // namespace VerifierUtil
#endif  //	MW_MWVABSTRACTRENDERERATTRIBUTES_HPP_
