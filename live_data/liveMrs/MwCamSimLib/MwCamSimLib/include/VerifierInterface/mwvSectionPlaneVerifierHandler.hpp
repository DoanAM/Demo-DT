// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @warning EXPERIMENTAL, NOT A STABLE INTERFACE YET

#ifndef MW_MWVSECTIONPLANEVERIFIERHANDLER_HPP_
#define MW_MWVSECTIONPLANEVERIFIERHANDLER_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwvResettable.hpp"
#include "mwvSectionPlaneHandler.hpp"
#include "mwvUtilDefines.hpp"

namespace VerifierUtil
{
/// Handles the synchronization with the verifier.
class MW_VERIFIER_API mwvSectionPlaneVerifierHandler : public mwvResettable
{
	mwvSectionPlaneHandler* const m_sectionPlaneHandler;

public:
	mwvSectionPlaneVerifierHandler(
		mwvSectionPlaneHandler* const sectionPlaneHandler, mwMachSimVerifier* const pVerifier);

	void Reset();
};
}  // namespace VerifierUtil
#endif  //	MW_MWVSECTIONPLANEVERIFIERHANDLER_HPP_
