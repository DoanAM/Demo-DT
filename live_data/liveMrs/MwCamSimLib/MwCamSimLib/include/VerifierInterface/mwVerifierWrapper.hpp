// (C) 2009-2021 by ModuleWorks GmbH
// Owner: CutSim

#pragma once

#include "mwMachSimVerifier.hpp"
#include "mwVerifierDllDefinition.hpp"

#include <mwException.hpp>
#include <mwString.hpp>
#include <mwWarningPragmas.hpp>

#ifndef MW_STDCALL
#if defined(_WIN32)
#define MW_STDCALL __stdcall
#else
#define MW_STDCALL
#endif
#endif

namespace misc
{
class mwstring;
};

/// Class to load the CutSim verifier dll
///
/// This class help to load the interface dll. This avoid loading the dll via loading of the c
/// interface to instantiate the interface object. To Load the DLL an retrieve an Object which
/// represents the interface instantiate the mwVerifierWrapper itself then call Initialize the
/// correct filename an location of the dll on the disc.
class MW_VERIFIER_API mwVerifierWrapper
{
public:
	inline mwVerifierWrapper();
	inline ~mwVerifierWrapper();

	/// Deletes verifier instance if initialized
	void DeleteVerifier();

	/// Initializes the verifier Dll
	void InitializeVerifier(std::wostream* debugOutputStream = 0);

	MW_DEPRECATED(
		"The dll file name is ignored, since the integration now links directly against "
		"mwVerifier.dll")
	void InitializeVerifier(
		const misc::mwstring& /*sDllName*/, std::wostream* debugOutputStream = 0)
	{
		InitializeVerifier(debugOutputStream);
	}

	/// Make sure that InitializeVerifier was called before. Otherwise the returned pointer is zero.
	///
	/// The pointer may also be zero if constructing the verifier failed. This can happen if the
	/// license is invalid.
	inline mwMachSimVerifier* GetVerifier();
	inline const mwMachSimVerifier* GetVerifier() const;

	/// No longer useful (always returns true)
	static bool IsVersionValid(int /*version*/) { return true; }

	/// Should only be used for ModuleWorks internal testing applications.
	void SetTestMode(bool enabled) { m_testMode = enabled; }

private:
	bool m_testMode;

	/// Pointer to the Verifier object
	mwMachSimVerifier* m_verifier;
};

inline mwVerifierWrapper::mwVerifierWrapper() : m_testMode(false), m_verifier(MW_NULL)
{
}

inline mwVerifierWrapper::~mwVerifierWrapper()
{
	DeleteVerifier();
}

inline mwMachSimVerifier* mwVerifierWrapper::GetVerifier()
{
	return m_verifier;
}

inline const mwMachSimVerifier* mwVerifierWrapper::GetVerifier() const
{
	return m_verifier;
}
