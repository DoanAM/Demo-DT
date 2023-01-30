// (C) 2014-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVTOOLRENDERER_HPP_
#define MW_MWVTOOLRENDERER_HPP_
#include "mwvToolHandler.hpp"

#include <mwToolPartSelector.hpp>

namespace VerifierUtil
{
class mwvToolRenderer
{
public:
	static void DrawActualToolMesh(
		const misc::mwAutoPointer<mwvToolHandler>& tool,
		const cadcam::mwToolPartSelector& toolPartSelector);

private:
	static void DrawToolElementMesh(
		const MATH::Frame<float>& position, const misc::mwAutoPointer<mwvMeshHandler> toolElement);

	static void GlTransformToFrame(const MATH::Frame<float>& f);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVTOOLRENDERER_HPP_
