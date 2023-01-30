// (C) 2014-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERSDECL_HPP_
#define MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERSDECL_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mwString.hpp>

namespace VerifierUtil
{
class MW_VERIFIER_API mwCutMaterialTextureHandlerParameters
{
public:
	mwCutMaterialTextureHandlerParameters(
		const misc::mwstring& cutTextureFileName,
		const float cutTextureWidth,
		const float cutTextureHeight,
		const misc::mwstring& uncutTextureFileName,
		const float uncutTextureWidth,
		const float uncutTextureHeight);
	mwCutMaterialTextureHandlerParameters(const mwCutMaterialTextureHandlerParameters&);
	~mwCutMaterialTextureHandlerParameters();
	float GetCutTextureWidth() const;
	float GetCutTextureHeight() const;
	float GetUncutTextureWidth() const;
	float GetUncutTextureHeight() const;
	const misc::mwstring& GetCutTexFileName() const;
	const misc::mwstring& GetUncutTexFileName() const;

private:
	mwCutMaterialTextureHandlerParameters& operator=(const mwCutMaterialTextureHandlerParameters&);
	const float m_cutTextureWidth;
	const float m_cutTextureHeight;
	const float m_uncutTextureWidth;
	const float m_uncutTextureHeight;
	const misc::mwstring m_cutTexFileName;
	const misc::mwstring m_uncutTexFileName;
};
};  // namespace VerifierUtil
#endif  //	MW_MWCUTMATERIALTEXTUREHANDLERPARAMETERSDECL_HPP_
