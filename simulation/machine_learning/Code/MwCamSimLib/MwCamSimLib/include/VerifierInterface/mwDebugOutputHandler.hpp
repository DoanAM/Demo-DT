// (C) 2014-2017 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWDEBUGOUTPUTHANDLER_HPP_
#define MW_MWDEBUGOUTPUTHANDLER_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <ostream>

namespace VerifierUtil
{
class MW_VERIFIER_API mwDebugOutputHandler
{
public:
	mwDebugOutputHandler();
	mwDebugOutputHandler(const mwDebugOutputHandler&);
	const mwDebugOutputHandler& operator=(const mwDebugOutputHandler&);
	std::wostream& GetDebugOutputStream();
	const std::wostream& GetDebugOutputStream() const;
	void SetDebugOutputStream(std::wostream&);
	void Output(const char*) const;
	void Output(const wchar_t*) const;

private:
	static std::wostream* GetDefaultOutputStream();
	std::wostream* m_pDebugOutputStream;
};
};  // namespace VerifierUtil
#endif  //	MW_MWDEBUGOUTPUTHANDLER_HPP_
