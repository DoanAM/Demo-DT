// (C) 2014-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWSETCUSTOMTOOLPARAMETERSDECL_HPP_
#define MW_MWSETCUSTOMTOOLPARAMETERSDECL_HPP_
#include <mwAutoPointer.hpp>
#include <mwMathUtilitiesDefinitions.hpp>

namespace cadcam
{
class mwTool;
typedef ::misc::mwAutoPointer<const mwTool> mwConstToolPtr;
};  // namespace cadcam

namespace VerifierUtil
{
struct mwSetCustomToolParameters
{
	/// See parameter tool in SetTool()
	::misc::mwAutoPointer<const ::cadcam::mwTool> Tool;
	/// See parameter toolId in SetTool()
	int ToolId;
	/// Position of the tool as Quaternion
	Frame toolPosition;

	/// Setter for custom tool parameters
	/// @param [in] tool See tool in SetTool()
	/// @param [in] toolId See toolId in SetTool()
	/// @param [in] position position of the too as quaternion FRAME
	inline mwSetCustomToolParameters(
		const ::misc::mwAutoPointer<const ::cadcam::mwTool>& tool,
		const int toolId,
		const Frame& position);
	inline ~mwSetCustomToolParameters();
};
};  // namespace VerifierUtil
#endif  //	MW_MWSETCUSTOMTOOLPARAMETERSDECL_HPP_
