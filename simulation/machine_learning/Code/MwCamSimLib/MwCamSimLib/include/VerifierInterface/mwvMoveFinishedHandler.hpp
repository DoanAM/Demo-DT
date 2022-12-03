// (C) 2014-2018 by ModuleWorks GmbH
// Owner: CutSim

#ifndef mwvMoveFinishedHandler_h__
#define mwvMoveFinishedHandler_h__

#include "mwVerifierDllDefinition.hpp"

#include <mwNull.hpp>


class mwMachSimVerifier;

namespace VerifierUtil
{
class MW_VERIFIER_API mwvMoveFinishedHandler
{
	mwvMoveFinishedHandler& operator=(const mwvMoveFinishedHandler&);  // = delete
protected:
	mwMachSimVerifier* const m_pVerifier;

public:
	mwvMoveFinishedHandler(mwMachSimVerifier* const pVerifier);

	virtual ~mwvMoveFinishedHandler();

	virtual void MoveFinished() = 0;

	virtual void OnVerifierDestroy();

	bool VerifierIsValid() { return m_pVerifier != MW_NULL; }
};
}  // namespace VerifierUtil

#endif  // mwvMoveFinishedHandler_h__