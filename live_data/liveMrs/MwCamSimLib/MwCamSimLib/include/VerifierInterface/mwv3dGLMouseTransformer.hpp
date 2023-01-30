// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWV3DGLMOUSETRANSFORMER_HPP_
#define MW_MWV3DGLMOUSETRANSFORMER_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvSectionPlaneMouseTransformer.hpp"

namespace VerifierUtil
{
class MW_VERIFIER_API mwv3dGLMouseTransformer
{
public:
	mwv3dGLMouseTransformer();
	~mwv3dGLMouseTransformer();

	/// Call this method in your draw cycle. This method will grab the GL_MODELVIEW_MATRIX.
	void SaveView();

	cadcam::mwHomogenousMatrix GetViewMatrix();

	/// Registers a transformer for mouse movements
	///
	/// Registers a transformer for mouse movements to calculate translation and rotation of the
	/// section planes. See mwvSectionPlaneDefaultMouseTransformer for a default implementation.
	///
	/// @param [in] transformer the implementation of the transformer
	void RegisterMouseTransformer(misc::mwAutoPointer<mwvSectionPlaneMouseTransformer> transformer);

	/// You have to register a mouse transformer to use this
	cadcam::mw2dHomogenousMatrix Rotate(float mouseDeltaX, float mouseDeltaY);

	/// You have to register a mouse transformer to use this
	float3d Translate(float mouseDeltaX, float mouseDeltaY);

	cadcam::mwHomogenousMatrix m_derivedMat;

private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<mwvSectionPlaneMouseTransformer> m_transformer;
	float m_viewMatrix[16];
};
}  // namespace VerifierUtil
#endif  //	MW_MWV3DGLMOUSETRANSFORMER_HPP_
