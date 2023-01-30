// (C) 2003-2008 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGENERIC2TYPEDTOOLCONVERTER_HPP_
#define MW_MWGENERIC2TYPEDTOOLCONVERTER_HPP_
#include "mw2dContour.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwTypedRevolvedTool.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwGeneric2TypedToolConverter
{
public:
	mwGeneric2TypedToolConverter();
	~mwGeneric2TypedToolConverter();

protected:
	const mw2dContour<T> GetNoneCutPartProfile(
		misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> genericRevolvedToolPtr) const;
	const mw2dContour<T> GetCutPartProfile(
		misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> genericRevolvedToolPtr) const;
	const mw2dContour<T> GetToolProfile(
		misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> genericRevolvedToolPtr) const;

public:
	cadcam::mwTypedRevolvedTool::Ptr Convert(
		misc::mwAutoPointer<cadcam::mwGenericRevolvedTool> genericRevolvedToolPtr);
};


// typedef mwToolConvertor<float> mwToolConvertorF;
typedef mwGeneric2TypedToolConverter<double> mwGeneric2TypedToolConverterD;

}  // namespace cadcam
#endif  //	MW_MWGENERIC2TYPEDTOOLCONVERTER_HPP_
