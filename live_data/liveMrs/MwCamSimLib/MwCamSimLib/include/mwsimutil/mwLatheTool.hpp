// (C) 2006-2014 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWLATHETOOL_HPP_
#define MW_MWLATHETOOL_HPP_
#include "mwAutoPointer.hpp"
#include "mwGenericExtrudedTool.hpp"


namespace cadcam
{
// mwLatheTool is deprecated. Please, use mwGenericExtrudedTool
typedef cadcam::mwGenericExtrudedTool mwLatheTool;

typedef misc::mwAutoPointer<cadcam::mwLatheTool> mwLatheToolPtr;
}  // namespace cadcam
#endif  //	MW_MWLATHETOOL_HPP_
