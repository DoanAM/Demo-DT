// (C) 2014-2018 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSECTIONPLANEDEFAULTMOUSETRANSFORMER_HPP_
#define MW_MWVSECTIONPLANEDEFAULTMOUSETRANSFORMER_HPP_
#include "mwvSectionPlaneMouseTransformer.hpp"
#include "mwvUtilDefines.hpp"

namespace VerifierUtil
{
class MW_VERIFIER_API mwvSectionPlaneDefaultMouseTransformer
	: public mwvSectionPlaneMouseTransformer
{
	mwvSectionPlaneDefaultMouseTransformer& operator=(
		const mwvSectionPlaneDefaultMouseTransformer&);  // = delete
	float m_translationSensitivity;
	float m_rotationSensitivity;

	const int m_count;
	mutable int m_currentCount;

	mutable float m_deltaX;
	mutable float m_deltaY;

public:
	mwvSectionPlaneDefaultMouseTransformer(
		float translationSensitivity = 1, float rotationSensitivity = 1);

	float3d GetTranslation(float mouseDeltaX, float mouseDeltaY) const;

	cadcam::mw2dHomogenousMatrix GetRotation(float mouseDeltaX, float mouseDeltaY) const;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSECTIONPLANEDEFAULTMOUSETRANSFORMER_HPP_
