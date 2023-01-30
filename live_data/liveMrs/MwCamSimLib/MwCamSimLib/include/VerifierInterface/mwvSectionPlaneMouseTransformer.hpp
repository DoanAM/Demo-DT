// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSECTIONPLANEMOUSETRANSFORMER_HPP_
#define MW_MWVSECTIONPLANEMOUSETRANSFORMER_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvUtilDefines.hpp"

#include <mwMatrix.hpp>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvSectionPlaneMouseTransformer
{
public:
	mutable cadcam::mwHomogenousMatrix m_derivedMat;

	/// Calculates a rotation out of 2d mouse movements
	/// @param [in] mouseDeltaX the mouse movement in x direction #### int?!
	/// @param [in] mouseDeltaY the mouse movement in y direction #### int?!
	/// @return the rotation around the x, y and z axes
	virtual cadcam::mw2dHomogenousMatrix GetRotation(
		float mouseDeltaX, float mouseDeltaY) const = 0;

	/// Calculates a translation out of 2d mouse movements
	/// @param [in] mouseDeltaX the mouse movement in x direction #### int?!
	/// @param [in] mouseDeltaY the mouse movement in y direction #### int?!
	/// @return the translation in x, y and z direction
	virtual float3d GetTranslation(float mouseDeltaX, float mouseDeltaY) const = 0;

	virtual ~mwvSectionPlaneMouseTransformer() {}
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSECTIONPLANEMOUSETRANSFORMER_HPP_
