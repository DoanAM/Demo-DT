// (C) 2014 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWSETCUSTOMTOOLPARAMETERS_HPP_
#define MW_MWSETCUSTOMTOOLPARAMETERS_HPP_
#include "mwSetCustomToolParametersDecl.hpp"

#include <mwTool.hpp>

namespace VerifierUtil
{
inline mwSetCustomToolParameters::mwSetCustomToolParameters(
	const cadcam::mwConstToolPtr& tool, const int toolId, const Frame& position)
	: Tool(tool), ToolId(toolId), toolPosition(position){};
inline mwSetCustomToolParameters::~mwSetCustomToolParameters()
{
}
};  // namespace VerifierUtil
#endif  //	MW_MWSETCUSTOMTOOLPARAMETERS_HPP_
