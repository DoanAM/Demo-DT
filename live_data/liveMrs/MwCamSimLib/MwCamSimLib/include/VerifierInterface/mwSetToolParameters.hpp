// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWSETTOOLPARAMETERS_HPP_
#define MW_MWSETTOOLPARAMETERS_HPP_

#include <mwAutoPointer.hpp>
#include <mwMathUtilitiesDefinitions.hpp>
#include <mwTool.hpp>

namespace VerifierUtil
{
/// Parameters for one tool, used in @ref mwMachSimVerifier::SetTools()
///
/// Members are identical to the parameters in mwMachSimVerifier::SetTool().
struct mwSetToolParameters
{
	// See @ref mwMachSimVerifier::SetTool()
	cadcam::mwConstToolPtr Tool;
	// See @ref mwMachSimVerifier::SetTool()
	int ToolId;

	inline mwSetToolParameters(const cadcam::mwConstToolPtr& tool, const int toolId)
		: Tool(tool), ToolId(toolId){};
	inline ~mwSetToolParameters(){};
};
};  // namespace VerifierUtil
#endif  //	MW_MWSETTOOLPARAMETERS_HPP_
