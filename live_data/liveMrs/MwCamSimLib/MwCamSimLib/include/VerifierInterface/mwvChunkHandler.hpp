// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVCHUNKHANDLER_HPP_
#define MW_MWVCHUNKHANDLER_HPP_
#include "mwMachSimVerifier.hpp"
#include "mwVerifierDllDefinition.hpp"
#include "mwvUtilDefines.hpp"

namespace VerifierUtil
{
class MW_VERIFIER_API mwvChunkHandler
{
	mwvChunkHandler& operator=(const mwvChunkHandler&);  // = delete
	mwMachSimVerifier* const m_pVerifier;

public:
	mwvChunkHandler(mwMachSimVerifier* const pVerifier);

	void DeleteChunks(float3d vertex, float error, bool keep);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVCHUNKHANDLER_HPP_
