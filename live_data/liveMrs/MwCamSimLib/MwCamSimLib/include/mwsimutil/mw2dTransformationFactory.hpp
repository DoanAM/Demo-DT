// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DTRANSFORMATIONFACTORY_HPP_
#define MW_MW2DTRANSFORMATIONFACTORY_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
/// @namespace mw2dTransformationFactory
/// This implements 2D affine transformations on geometric objects
namespace mw2dTransformationFactory
{
/// Transform 2D line
template <typename T>
MW_5AXUTIL_API mw2dLine<T> Transform(const mw2dLine<T>& line, const mwMatrix<T, 3, 3>& matrix);
/// Transform 2D arc
template <typename T>
MW_5AXUTIL_API mw2dArc<T> Transform(const mw2dArc<T>& arc, const mwMatrix<T, 3, 3>& matrix);
/// Transform 2D point
template <typename T>
MW_5AXUTIL_API mwTPoint2d<T> Transform(const mwTPoint2d<T>& point, const mwMatrix<T, 3, 3>& matrix);
/// Transform 2D point
template <typename T>
MW_5AXUTIL_API mw2dPoint<T> Transform(const mw2dPoint<T>& point, const mwMatrix<T, 3, 3>& matrix);
/// Transform 2D contour
template <typename T>
MW_5AXUTIL_API mw2dContour<T> Transform(
	const mw2dContour<T>& contour, const mwMatrix<T, 3, 3>& matrix);
/// Transform 2D polyline
template <typename T>
MW_5AXUTIL_API mw2dPolyLine<T> Transform(
	const mw2dPolyLine<T>& polyLine, const mwMatrix<T, 3, 3>& matrix);
template <typename TCont, typename TMatrix>
MW_5AXUTIL_API TCont Transform(const TCont& src, const TMatrix& matrix)
{
	TCont res;
	for (typename TCont::const_iterator it = src.begin(); it != src.end(); ++it)
	{
		res.push_back(Transform(*it, matrix));
	}
	return res;
}
}  // namespace mw2dTransformationFactory
}  // namespace cadcam
#endif  //	MW_MW2DTRANSFORMATIONFACTORY_HPP_
