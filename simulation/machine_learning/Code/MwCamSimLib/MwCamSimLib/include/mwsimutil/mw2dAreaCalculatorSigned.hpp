// (C) 2008-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DAREACALCULATORSIGNED_HPP_
#define MW_MW2DAREACALCULATORSIGNED_HPP_
#include "mwCadcamFwdDecl.hpp"

#include <vector>


namespace cadcam
{
namespace mw2dAreaCalculatorSigned
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
T GetArea(
	const typename mw2dContour<T>::ItemListConstIt& first,
	const typename mw2dContour<T>::ItemListConstIt& last);

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
	return totalArea;
}
}  // namespace mw2dAreaCalculatorSigned
}  // namespace cadcam
#endif  //	MW_MW2DAREACALCULATORSIGNED_HPP_
