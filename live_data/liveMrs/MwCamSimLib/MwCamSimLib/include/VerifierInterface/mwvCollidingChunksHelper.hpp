// (C) 2013-2015 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVCOLLIDINGCHUNKSHELPER_HPP_
#define MW_MWVCOLLIDINGCHUNKSHELPER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwVerifierDllDefinition.hpp"

#include <mwString.hpp>

namespace VerifierUtil
{
namespace mwvCollidingChunksHelper
{
MW_VERIFIER_API void Sort(mwMachSimVerifier::ToolChunkCollisions& collisions);
MW_VERIFIER_API void Sort(std::vector<mwMachSimVerifier::ToolChunkCollisions>& collisions);
MW_VERIFIER_API misc::mwstring ToText(const mwMachSimVerifier::ToolChunkCollisions& collisions);

}  // namespace mwvCollidingChunksHelper
}  // namespace VerifierUtil
#endif  //	MW_MWVCOLLIDINGCHUNKSHELPER_HPP_
