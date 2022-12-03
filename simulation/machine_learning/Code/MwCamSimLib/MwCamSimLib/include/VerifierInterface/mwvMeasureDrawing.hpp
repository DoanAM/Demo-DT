// (C) 2018-2021 by ModuleWorks GmbH
// Owner: CutSim

/// \file
/// Abstract interface for custom drawing.

#ifndef MW_MWVMEASUREDRAWING_HPP_
#define MW_MWVMEASUREDRAWING_HPP_

#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierMathForward.hpp"
#include "mwvMeasureCommon.hpp"

#include <mw2dGeometryTypedefs.hpp>
#include <mw3dGeometryTypedefs.hpp>
#include <mwTPoint2d.hpp>

namespace VerifierUtil
{
namespace Measure
{
class MW_VERIFIER_API Projection
{
public:
	virtual ~Projection() {}

	virtual const cadcam::mwHomogenousMatrixd& GetModelViewTransform() const = 0;

	virtual const cadcam::mwHomogenousMatrixd& GetProjectionTransform() const = 0;

	/// @return rectangle In window coordinates, origin at the upper-left.
	virtual const cadcam::mw2diBoundingBox& GetViewport() const = 0;

	/// @param [out] posScreen Projected position in window coordinates, origin at the upper-left.
	/// @param [out] projectedZ Z component of projected position in the range [0..1].
	/// @param [in] posWorld Position in world coordinates.
	/// @return false if failed.
	virtual bool Project(
		cadcam::mwPoint2di& posScreen,
		double& projectedZ,
		const cadcam::mwPoint3d& posWorld) const = 0;

	/// @param [out] projectedPos (posScreen, projectedZ)
	/// @param [in] posWorld Position in world coordinates.
	/// @return false if failed.
	virtual bool Project(
		cadcam::mwPoint3d& projectedPos, const cadcam::mwPoint3d& posWorld) const = 0;

	/// @param [out] posWorld Position in world coordinates.
	/// @param [in] posScreen Projected position in window coordinates, origin at the upper-left.
	/// @param [in] projectedZ Z component of projected position in the range [0..1].
	/// @return false if failed.
	virtual bool Unproject(
		cadcam::mwPoint3d& posWorld,
		const cadcam::mwPoint2di& posScreen,
		double projectedZ) const = 0;

	/// @param [out] posWorld Position in world coordinates.
	/// @param [in] projectedPos (posScreen, projectedZ)
	/// @return false if failed.
	virtual bool Unproject(
		cadcam::mwPoint3d& posWorld, const cadcam::mwPoint3d& projectedPos) const = 0;
};

class MW_VERIFIER_API DepthsAndStencilIndices
{
public:
	virtual ~DepthsAndStencilIndices() {}

	virtual int GetDepthBits() const = 0;

	/// @param pos In window coordinates, origin at the upper-left.
	/// @return depth Value in the range [0..1].
	virtual float GetDepth(const cadcam::mwPoint2di& pos) const = 0;

	/// @param pos In view coordinates, origin at the upper-left.
	virtual unsigned GetStencilIdx(const cadcam::mwPoint2di& pos) const = 0;
};

class MW_VERIFIER_API Drawing
{
public:
	virtual ~Drawing() {}


	virtual void InitializeDeviceResources() = 0;

	virtual void ReleaseDeviceResources() = 0;


	virtual void BeginDraw(const cadcam::mwPoint2di& windowSize, const DrawStyle& style) = 0;

	virtual void DrawGeometry(
		const Geometry& geometry, const Frame& transform, bool highlighted) = 0;

	/// intoduced in 2021.08
	virtual void DrawEdgeMidpoint(
		const Edge& /*edge*/, const Frame& /*transform*/, bool /*highlighted*/)
	{
	}

	virtual void DrawArcRadius(const ArcEdge& edge, const Frame& transform, bool highlighted) = 0;

	virtual void DrawCurvature(
		const Curvature& curvature, const Frame& transform, bool highlighted) = 0;

	virtual void DrawThickness(
		const Distance& thickness, const Frame& transform, bool highlighted) = 0;

	virtual void DrawDepth(const Distance& depth, const Frame& transform, bool highlighted) = 0;

	virtual void DrawClearance(const Distance& depth, const Frame& transform, bool highlighted) = 0;

	virtual void DrawCorner(const Corner& corner, const Frame& transform, bool highlighted) = 0;

	virtual void DrawDistance(
		const Distance& distance, const Frame& transform, bool highlighted) = 0;

	virtual void DrawMeasurePoint(
		const cadcam::mwPoint3df& pos, bool primary, bool highlighted) = 0;

	virtual void DrawGeometryPoint(const cadcam::mwPoint3df& pos, bool highlighted) = 0;

	virtual void EndDraw() = 0;


	virtual const Projection& GetProjection() const = 0;

	/// Reads and saves current projection/view/model transformations and viewport.
	/// @return false if failed.
	virtual bool ReadProjection(const cadcam::mwPoint2di& windowSize) = 0;


	virtual const DepthsAndStencilIndices& GetDepthAndStencilIndices() const = 0;

	/// Reads and saves depth- and stencil buffers.
	/// @return false if failed.
	virtual bool ReadDepthsAndStencilIndices(const cadcam::mwPoint2di& windowSize) = 0;
};

/// @return stencil-index for the measured-surface.
inline unsigned GetSurfaceStencilIdx(MeasuredObjectID objectID)
{
	return (((objectID - 1) & 0x3F) << 1) | 1;
}

/// @return stencil-index for the measured-edge.
inline unsigned GetEdgeStencilIdx(MeasuredObjectID objectID)
{
	return GetSurfaceStencilIdx(objectID) | 0x80;
}

/// @return object-id correspoinding to the specified @p stencilIdx.
inline unsigned GetObjectIDsFromStencilIdx(unsigned stencilIdx, int idx = 0)
{
	return (((stencilIdx >> 1) & 0x3F) + 1) + (unsigned)(64 * idx);
}

/// @return whether an edge is marked in the specified @p stencilIdx.
inline bool IsMarkedAsEdgeInStencil(unsigned stencilIdx)
{
	return (stencilIdx & 0x80) != 0;
}

}  // namespace Measure
}  // namespace VerifierUtil

#endif  //	MW_MWVMEASUREDRAWING_HPP_
