// (C) 2013-2019 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVGOUGEREPORTHANDLER_HPP_
#define MW_MWVGOUGEREPORTHANDLER_HPP_
#include "mwvGougeReport.hpp"
#include "mwvResettable.hpp"
#include "mwvUtilDefines.hpp"

#include <vector>

namespace VerifierUtil
{
class mwvGougeReportHandler
{
public:
	std::vector<mwvGougeReport> m_selectedGouges;

	mwvGougeReportHandler(mwMachSimVerifier* const pVerifier);
	void Clear();

private:
	mwMachSimVerifier* const m_pVerifier;

	mwvGougeReportHandler& operator=(const mwvGougeReportHandler&);  // = delete
};
}  // namespace VerifierUtil
#endif  //	MW_MWVGOUGEREPORTHANDLER_HPP_
