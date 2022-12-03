// (C) 2013-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef mwvResettable_h__
#define mwvResettable_h__

#include "mwVerifierDllDefinition.hpp"

#include <mwNull.hpp>

class mwMachSimVerifier;


namespace VerifierUtil
{
/// Registers with a @ref mwMachSimVerifier for notification on destruction and @ref
/// mwMachSimVerifier::Reset().
class MW_VERIFIER_API mwvResettable
{
protected:
	mwMachSimVerifier* const m_pVerifier;

public:
	/// Registers with @p pVerifier
	mwvResettable(mwMachSimVerifier* const pVerifier);
	virtual ~mwvResettable();

	/// Called back on @ref mwMachSimVerifier::Reset().
	virtual void Reset() = 0;

	/// Called back on destruction of the associated @ref mwMachSimVerifier.
	virtual void OnVerifierDestroy();

	/// True if @ref m_pVerifier != nullptr.
	bool VerifierIsValid() { return m_pVerifier != MW_NULL; }

private:
	/// @hidden
	mwvResettable& operator=(mwvResettable&);  // = delete
};
};  // namespace VerifierUtil

#endif  // mwvResettable_h__
