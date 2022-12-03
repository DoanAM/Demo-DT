// (C) 2013-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVSPARKLEREMOVER_HPP_
#define MW_MWVSPARKLEREMOVER_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mwAutoPointer.hpp>

namespace VerifierUtil
{
class MW_VERIFIER_API mwvSparkleRemover
{
public:
	mwvSparkleRemover();
	~mwvSparkleRemover();
	void RemoveSparkles(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

private:
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	misc::mwAutoPointer<unsigned int> m_buffer;
	int m_bufferSize;
};
};  // namespace VerifierUtil
#endif  //	MW_MWVSPARKLEREMOVER_HPP_
