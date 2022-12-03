// (C) 2008-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DAREACALCULATORUNSIGNED_HPP_
#define MW_MW2DAREACALCULATORUNSIGNED_HPP_
#include "mwCadcamFwdDecl.hpp"

#include <cmath>
#include <vector>

namespace cadcam
{
namespace mw2dAreaCalculatorUnsigned
{
template <typename T>
T GetTriangleArea(const mwTPoint2d<T>& p1, const mwTPoint2d<T>& p2, const mwTPoint2d<T>& p3);

template <typename T>
T GetSectorArea(const mw2dArc<T>& arc);

template <typename T>
T GetSegmentArea(const mw2dArc<T>& arc);

template <typename T>
T GetArea(const mw2dContour<T>& src);

template <typename T>
T GetArea(const mw2dPolyLine<T>& src);

template <typename T>
T GetArea(const mw2dMultipleClosedPolyLine<T>& src);

template <typename TContour>
typename TContour::ValueType GetArea(const std::vector<TContour>& src)
{
	typename TContour::ValueType totalArea = typename TContour::ValueType(0);
	for (size_t i = 0; i < src.size(); ++i)
	{
		totalArea += GetArea<typename TContour::ValueType>(src[i]);
	}
	return std::fabs(totalArea);
}

template <typename T>
class MW_5AXUTIL_API IsLess
{
public:
	IsLess() {}

	bool operator()(const mw2dPolyLine<T>& p1, const mw2dPolyLine<T>& p2) const
	{
		return GetArea(p1) < GetArea(p2);
	}
};
}  // namespace mw2dAreaCalculatorUnsigned
}  // namespace cadcam
#endif  //	MW_MW2DAREACALCULATORUNSIGNED_HPP_
