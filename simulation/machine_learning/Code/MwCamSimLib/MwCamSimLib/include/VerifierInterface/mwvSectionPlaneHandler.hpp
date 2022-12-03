// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVSECTIONPLANEHANDLER_HPP_
#define MW_MWVSECTIONPLANEHANDLER_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvColor.hpp"
#include "mwvResettable.hpp"
#include "mwvSectionPlaneMouseTransformer.hpp"
#include "mwvSectionPlaneRenderer.hpp"
#include "mwvUtilDefines.hpp"

#include <list>
#include <mwMatrix.hpp>

namespace VerifierUtil
{
/// Handles the drawing of section cuts in a
/// geometry, some helping representation of the
/// section planes and the possibility of
/// transforming the planes (e.g. with a mouse).
class MW_VERIFIER_API mwvSectionPlaneHandler : public mwvSectionPlaneRenderer
{
	VerifierUtil::mwvColor m_firstSectionPlaneColor;

	VerifierUtil::mwvColor m_secondSectionPlaneColor;

	float3d m_firstFixedRotationPoint;

	float3d m_secondFixedRotationPoint;

	bool m_firstSectionPlaneVisible;

	bool m_secondSectionPlaneVisible;

	class mwvSectionPlane : public mwvSectionPlaneRenderer::mwvSectionPlane
	{
	public:
		mwvSectionPlane(const float3d& ortho, float shift, bool enabled)
			: mwvSectionPlaneRenderer::mwvSectionPlane(ortho, shift, enabled),
			  m_Span(ortho.Orthogonal())
		{
		}

		/// Setter for the span vector which is needed for the orientation of the helping plane
		void SetSpan(const float3d& span) { m_Span = span; }
		/// Getter for the span vector which is needed for the orientation of the helping plane
		const float3d& GetSpan() const { return m_Span; }

	private:
		float3d m_Span;
	};

protected:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvSectionPlaneMouseTransformer> m_transformer;

public:
	/// Creates a handler
	///
	/// Creates a section plane handler based on the passed renderable.
	/// @param [in] renderable a renderable object to draw the mesh
	mwvSectionPlaneHandler(misc::mwAutoPointer<mwvSectionPlaneRenderer::Renderable> renderable);

	void Init();

	/// Sets the first section plane
	///
	/// Sets the first section plane in Hesse normal form. The default first section plane is:
	/// normalDirection=(0,1,0); shift=0. *	The helper representation of the plane might be moved if
	/// the current position does not fit the new plane definition. @param [in] normalDirection the
	/// plane normal @param [in] shift the offset from the origin in normal direction
	virtual void SetFirstSectionPlane(const float3d& normalDirection, const float shift);

	/// Gets the second section plane
	///
	/// Gets the second section plane in Hesse normal form. The default first section plane is:
	/// normalDirection=(0,0,1); shift=0. *	The helper representation of the plane might be moved if
	/// the current position does not fit the new plane definition. @param [out] normalDirection the
	/// plane normal @param [out] shift the offset from the origin in normal direction
	virtual void SetSecondSectionPlane(const float3d& normalDirection, const float shift);

	/// Resets the point and distance labels
	///
	/// All point and distance labels are deleted. Gouge and Excess labels are kept.
	void Reset();

	/// Draws the section planes
	///
	/// Draws a helping representation of the two section planes. The workpiece still needs to be
	/// drawn via mwvSectionPlaneRenderer::RenderWorkpiece().
	void DrawSectionPlanes();

	/// Registers a callback function that draws the triangles
	///
	/// Registers a callback function that will be called to draw the triangles. See Draw().
	/// @param [in] renderable the callback function that will be called on draw
	void SetRenderable(misc::mwAutoPointer<Renderable> renderable);

	/// Translates the specified plane
	///
	/// Translates the specified plane along the normal direction. The shift is added to the current
	/// plane definition. @param [in] shift the shift in normal direction @param [in] firstPlane
	/// specifies the first or second plane
	void Translate(const float shift, bool firstPlane);

	/// Rotates the specified plane
	///
	/// Rotates the specified plane normal with the help of a 2d homogeneous rotation matrix.
	/// @param [in] transform a 2d homogeneous rotation matrix
	/// @param [in] firstPlane specifies the first or second plane
	void Rotate(const cadcam::mw2dHomogenousMatrix& transform, bool firstPlane);

	void SetFirstSectionPlaneColor(const VerifierUtil::mwvColor& color)
	{
		m_firstSectionPlaneColor = color;
	}

	const VerifierUtil::mwvColor& GetFirstSectionPlaneColor() { return m_firstSectionPlaneColor; }

	void SetSecondSectionPlaneColor(const VerifierUtil::mwvColor& color)
	{
		m_secondSectionPlaneColor = color;
	}

	const VerifierUtil::mwvColor& GetSecondSectionPlaneColor() { return m_secondSectionPlaneColor; }

	void SetFirstSectionPlaneVisible(bool visible) { m_firstSectionPlaneVisible = visible; }

	bool GetFirstSectionPlaneVisible() { return m_firstSectionPlaneVisible; }

	void SetSecondSectionPlaneVisible(bool visible) { m_secondSectionPlaneVisible = visible; }

	bool GetSecondSectionPlaneVisible() { return m_secondSectionPlaneVisible; }

private:
	void DrawSectionPlane(
		const mwvSectionPlane* sectionPlane,
		const VerifierUtil::mwvColor& color,
		float3d rotationPoint);

	void Translate(const float shift, mwvSectionPlane*, float3d& rotationPoint);
	void Rotate(
		const cadcam::mw2dHomogenousMatrix& transform, mwvSectionPlane*, float3d rotationPoint);

	cadcam::mwVector<float, 3> ConvertVector(float3d vector);
	float3d ConvertVector(cadcam::mwVector<float, 3> vector);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSECTIONPLANEHANDLER_HPP_
