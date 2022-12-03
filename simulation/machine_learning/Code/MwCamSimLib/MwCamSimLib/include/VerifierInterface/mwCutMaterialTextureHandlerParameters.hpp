// (C) 2014-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERS_HPP_
#define MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERS_HPP_
#include "mwCutMaterialTextureHandlerParametersDecl.hpp"

namespace VerifierUtil
{
inline float mwCutMaterialTextureHandlerParameters::GetCutTextureWidth() const
{
	return m_cutTextureWidth;
}

inline float mwCutMaterialTextureHandlerParameters::GetCutTextureHeight() const
{
	return m_cutTextureHeight;
}

inline float mwCutMaterialTextureHandlerParameters::GetUncutTextureWidth() const
{
	return m_uncutTextureWidth;
}

inline float mwCutMaterialTextureHandlerParameters::GetUncutTextureHeight() const
{
	return m_uncutTextureHeight;
}

inline const misc::mwstring& mwCutMaterialTextureHandlerParameters::GetCutTexFileName() const
{
	return m_cutTexFileName;
}

inline const misc::mwstring& mwCutMaterialTextureHandlerParameters::GetUncutTexFileName() const
{
	return m_uncutTexFileName;
}
};  // namespace VerifierUtil
#endif  //	MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERS_HPP_
