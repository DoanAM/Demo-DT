// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVSECTIONPLANERENDERER_HPP_
#define MW_MWVSECTIONPLANERENDERER_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvColor.hpp"
#include "mwvMeshHandler.hpp"
#include "mwvUtilDefines.hpp"
#include "mwvUtilityHelper.hpp"

#include <mw3dBoundingBox.hpp>
#include <mwMathConstants.hpp>

namespace VerifierUtil
{
/// Handles the drawing of section cuts in a geometry with the help of two section planes.
/// If you want to draw a representation of the planes use mwvSectionPlaneHandler instead.
class MW_VERIFIER_API mwvSectionPlaneRenderer
{
public:
	typedef cadcam::mw3dBoundingBox<float> BoundingBox3d;

	/// A renderable object
	///
	/// The representation of a renderable object. It draws itself via the Draw() method and is
	/// initialized with a bounding box of the triangles.
	class MW_VERIFIER_API Renderable
	{
	public:
		Renderable(const BoundingBox3d& bbox) : m_bbox(bbox) {}

		virtual ~Renderable() {}

		virtual void Draw() = 0;

		const BoundingBox3d& GetBoundingBox() const { return m_bbox; }

	private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
		const BoundingBox3d m_bbox;
		Renderable& operator=(const Renderable&);  // = delete
	};

	/// A mesh handler to use for drawing
	///
	/// A mesh handler that is used for drawing the triangles. The bounding box is taken from the
	/// mesh directly.
	class MeshHandler : mwvMeshHandler, Renderable
	{
	public:
		MeshHandler(const mwvMeshHandler::MeshPtr pMesh)
			: mwvMeshHandler(pMesh), Renderable(pMesh->GetBoundingBox())
		{
		}

		void Draw() { mwvMeshHandler::Draw(); }
	};

protected:
	/// A section plane representation
	///
	/// The representation of a section plane. A plane is defined by Hesse normal form with a normal
	/// direction and a shift from the origin in normal direction.
	class mwvSectionPlane
	{
	public:
		mwvSectionPlane(const float3d& ortho, float shift, bool enabled)
			: m_OrthoVec(ortho), m_Shift(shift), m_bEnabled(enabled)
		{
		}
		virtual ~mwvSectionPlane() {}
		/// Getter Method for m_OrthoVec Property
		const float3d& GetOrthoVec() const { return m_OrthoVec; }
		/// Setter Method for m_OrthoVec Property. Normalized vectors only!
		void SetOrthoVec(const float3d& val) { m_OrthoVec = val; }
		/// Getter Method for m_bEnabled Property
		bool GetEnabled() const { return m_bEnabled; }
		/// Setter Method for m_bEnabled Property
		void SetEnabled(bool val) { m_bEnabled = val; }
		/// Setter for the shift of the plane according to the hesse normal form of the plane
		void SetShift(float shift) { m_Shift = shift; }
		/// Getter for the shift of the plane according to the hesse normal form of the plane
		float GetShift() const { return m_Shift; }
		/// Setter Method of the shift via a point on the plane
		void SetPointOnPlane(const float3d& val) { m_Shift = val * m_OrthoVec; }
		/// Getter Method of the point on the plane
		float3d GetPointOnPlane() { return m_Shift * m_OrthoVec; }
		/// Tests if the passed point is on the plane
		bool IsPointOnPlane(const float3d& point) const
		{
			return fabs((point * m_OrthoVec) - m_Shift) < mathdef::MW_MATH_TOL_FLOAT;
		}

	protected:
		float3d m_OrthoVec;
		float m_Shift;
		bool m_bEnabled;
	};

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvSectionPlane> m_firstSectionPlane;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvSectionPlane> m_secondSectionPlane;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<Renderable> m_apRenderable;

private:
	struct RenderData
	{
		bool m_useSection;
		bool m_useTwoSections;
		bool m_useTwoSectionAdd;
		bool m_renderBottomWithClipPlane;

		int m_bottomPlaneID;
		int m_plane1ID;
		int m_plane1invID;
		int m_plane2ID;
		int m_plane2invID;

		mwvUtilityHelper::GlStateSaver saver;

		RenderData()
			: m_useSection(false),
			  m_useTwoSections(false),
			  m_useTwoSectionAdd(false),
			  m_renderBottomWithClipPlane(false),
			  m_bottomPlaneID(-1),
			  m_plane1ID(-1),
			  m_plane1invID(-1),
			  m_plane2ID(-1),
			  m_plane2invID(-1)
		{
		}
	};

	VerifierUtil::mwvColor m_firstSectionColor;

	VerifierUtil::mwvColor m_secondSectionColor;

	bool m_fillFirstSection;

	bool m_fillSecondSection;

	bool m_addHalfSpaces;

	bool m_isDepthMaskEnabledWhenBlending;

public:
	/// Creates a renderer with a renderable
	///
	/// Creates a renderer and registers a renderable that will be called to draw the triangles. See
	/// Draw().
	/// @param [in] renderable the callback function that will be called on draw
	mwvSectionPlaneRenderer(misc::mwAutoPointer<Renderable> renderable);

	virtual ~mwvSectionPlaneRenderer();

	/// Renders the mesh
	///
	/// Renders the mesh with the missing part according to the section planes
	virtual void Render();

	/// Sets the first section plane
	///
	/// Sets the first section plane in Hesse normal form. The default first section plane is:
	/// normalDirection=(0,1,0); shift=0.
	/// @param [in] normalDirection the plane normal
	/// @param [in] shift the offset from the origin in normal direction
	virtual void SetFirstSectionPlane(const float3d& normalDirection, const float shift);

	/// Gets the first section plane
	///
	/// Gets the first section plane in Hesse normal form.
	/// @param [out] normalDirection the plane normal
	/// @param [out] shift the offset from the origin in normal direction
	virtual void GetFirstSectionPlane(float3d& normalDirection, float& shift);

	/// Sets the second section plane
	///
	/// Sets the second section plane in Hesse normal form.  The default second section plane is:
	/// normalDirection=(0,0,1); shift=0.
	/// @param [in] normalDirection  the plane normal
	/// @param [in] shift  the offset from the origin in normal direction
	virtual void SetSecondSectionPlane(const float3d& normalDirection, const float shift);

	/// Gets the second section plane
	///
	/// Gets the second section plane in Hesse normal form.
	/// @param [out] normalDirection the plane normal
	/// @param [out] shift the offset from the origin in normal direction
	virtual void GetSecondSectionPlane(float3d& normalDirection, float& shift);

	/// Sets a new renderable object
	///
	/// Sets a new renderable object to draw the triangles.
	/// @param [in] renderable an instance to draw the triangles
	virtual void SetRenderable(misc::mwAutoPointer<Renderable> renderable);

	void SetFirstSectionPlaneEnabled(bool enabled) { m_firstSectionPlane->SetEnabled(enabled); }

	bool GetFirstSectionPlaneEnabled() { return m_firstSectionPlane->GetEnabled(); }

	void SetSecondSectionPlaneEnabled(bool enabled) { m_secondSectionPlane->SetEnabled(enabled); }

	bool GetSecondSectionPlaneEnabled() { return m_secondSectionPlane->GetEnabled(); }

	void SetFirstSectionColor(const mwvColor& color) { m_firstSectionColor = color; }

	const mwvColor& GetFirstSectionColor() { return m_firstSectionColor; }

	void SetSecondSectionColor(const mwvColor& color) { m_secondSectionColor = color; }

	const mwvColor& GetSecondSectionColor() { return m_secondSectionColor; }

	void SetFillFirstSection(bool fillSection) { m_fillFirstSection = fillSection; }

	bool GetFillFirstSection() { return m_fillFirstSection; }

	void SetFillSecondSection(bool fillSection) { m_fillSecondSection = fillSection; }

	bool GetFillSecondSection() { return m_fillSecondSection; }

	void SetAddHalfSpaces(bool addHalfSpaces) { m_addHalfSpaces = addHalfSpaces; }

	bool GetAddHalfSpaces() { return m_addHalfSpaces; }

	/// Determines whether the depth buffer will be filled when drawing with blending.
	///
	/// When GL_BLEND is enabled this option is checked when filling the section planes or
	/// drawing the mesh. The depth buffer will then only be filled if this option is set to true.
	///
	/// @param[in] enabled True to enable filling of the depth buffer, false otherwise.
	/// @note By default this option is set to false.
	void SetIsDepthMaskEnabledWhenBlending(bool enabled)
	{
		m_isDepthMaskEnabledWhenBlending = enabled;
	}

	/// Determines whether the depth buffer will be filled when drawing with blending.
	///
	/// For more information see SetIsDepthMaskEnabledWhenBlending.
	/// @return True if filling of the depth buffer is enabled, false otherwise.
	/// @note By default this option is set to false.
	bool GetIsDepthMaskEnabledWhenBlending() const { return m_isDepthMaskEnabledWhenBlending; }

private:
	void DrawMesh();

	void ResetPlanePositions();

	void DrawMesh(RenderData& data);

	void InitializeDraw(RenderData& data);

	void DrawMeshWithDeepSides(RenderData& data);

	void DrawBottomSection(RenderData& data, bool firstSection);

	void DrawInvisibleMesh(RenderData& data, bool firstClip);

	void DrawSectionPlane(
		misc::mwAutoPointer<mwvSectionPlane> sectionPlane,
		const mwvColor& color,
		const bool filled);

	void DrawSectionSide(RenderData& data, bool firstSection);

	unsigned GetNextClipPlaneIDOfNotEnabledPlane();

	void glDisableIfSet(const unsigned int v) const;

	void glEnableIfSet(const unsigned int v) const;

	bool InitializeData(RenderData& data);

	void ReleaseData(RenderData& data);

	mwvSectionPlaneRenderer& operator=(const mwvSectionPlaneRenderer&);  // = delete
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSECTIONPLANERENDERER_HPP_
