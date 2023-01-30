// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVMESHHANDLER_HPP_
#define MW_MWVMESHHANDLER_HPP_
#include "mwvColor.hpp"

#include <mwMesh.hpp>

namespace VerifierUtil
{
/// Draws a mwTMesh<float> using OpenGL
class MW_VERIFIER_API mwvMeshHandler
{
public:
	typedef misc::mwAutoPointer<cadcam::mwTMesh<float>> MeshPtr;

private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	const MeshPtr m_pMesh;
	bool m_visible;
	bool m_showNormals;
	bool m_normalizedNormals;
	float m_normalizedNormalsCoefficient;
	bool m_wireFrame;
	mwvColor m_color;
	mutable int m_displayListId;

public:
	/// Creates a meshhandler based on the mesh and the passed color
	///
	/// @param [in] pMesh the pointer to the mesh
	/// @param [in] color the color of the mesh
	mwvMeshHandler(
		const MeshPtr pMesh,
		const mwvColor& color = VerifierUtil::mwvColor(1.0f, 0.5f, 0.5f, 1.0f));

	/// Destructor. Please supply a valid OpenGL context.
	~mwvMeshHandler();

	/// Draws the mesh.
	///
	/// Please supply a valid OpenGL context.
	void Draw() const;

	/// Releases the internal OpenGL resources.
	///
	/// Will delete the internal OpenGL resources. They are automatically recreated if necessary on
	/// the next Draw() call. Normally calling this function should not be necessary, as it is also
	/// called by the destructor. You should call it manually if you intend to switch the OpenGL
	/// context without reconstructing this class.
	void Release();

	void SetVisibility(bool visible) { m_visible = visible; }
	bool GetVisibility() { return m_visible; }

	void SetColor(const mwvColor& color) { m_color = color; }
	const mwvColor& GetColor() { return m_color; }

	/// Show triangle normals as lines originating at the centers of the triangles
	void SetShowNormals(bool showNormals) { m_showNormals = showNormals; }
	bool GetShowNormals() { return m_showNormals; }

	/// Specify whether the normals in the mesh should be normalized (default: true)
	///
	/// This only affects the "ShowNormals" feature. Setting this to "false" allows you to also see
	/// the length of the normals set in the mesh, not just the direction.
	void SetNormalizedNormals(bool normalizedNormals) { m_normalizedNormals = normalizedNormals; }
	bool GetNormalizedNormals() { return m_normalizedNormals; }

	/// Specify a length multiplier for mesh normals (default: 1).
	///
	/// This only affects the "ShowNormals" feature. You can use this value to scale the normals'
	/// lengths.
	void SetNormalizedNormalsCoefficient(float normalizedNormalsCoefficient)
	{
		m_normalizedNormalsCoefficient = normalizedNormalsCoefficient;
	}
	float GetNormalizedNormalsCoefficient() { return m_normalizedNormalsCoefficient; }

	/// Render mesh as wireframe, instead of as a solid
	void SetWireFrame(bool wireFrame) { m_wireFrame = wireFrame; }
	bool GetWireFrame() { return m_wireFrame; }

private:
	void InitialDraw() const;

	virtual void Redraw(unsigned int iMeshId, const mwvColor& elementColor) const;

	void Render(const Mesh& mesh) const;

private:
	void SetState() const;
	mwvMeshHandler& operator=(const mwvMeshHandler&);  // = delete
};
}  // namespace VerifierUtil
#endif  //	MW_MWVMESHHANDLER_HPP_
