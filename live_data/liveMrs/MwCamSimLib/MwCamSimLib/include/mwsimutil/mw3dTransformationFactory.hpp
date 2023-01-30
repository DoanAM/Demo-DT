// (C) 2009-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DTRANSFORMATIONFACTORY_HPP_
#define MW_MW3DTRANSFORMATIONFACTORY_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
namespace mw3dTransformationFactory
{
template <typename T>
MW_5AXUTIL_API mwTPoint3d<T> Transform(const mwTPoint3d<T>& point, const mwMatrix<T, 4, 4>& matrix);

template <typename T>
MW_5AXUTIL_API mw3dLine<T> Transform(const mw3dLine<T>& line, const mwMatrix<T, 4, 4>& matrix);

template <typename T>
MW_5AXUTIL_API mw3dArc<T> Transform(const mw3dArc<T>& arc, const mwMatrix<T, 4, 4>& matrix);

template <typename T>
MW_5AXUTIL_API mw3dHelix<T> Transform(const mw3dHelix<T>& helix, const mwMatrix<T, 4, 4>& matrix);

template <typename T>
MW_5AXUTIL_API mw3dPolyLine<T> Transform(
	const mw3dPolyLine<T>& polyLine, const mwMatrix<T, 4, 4>& matrix);

template <typename T>
MW_5AXUTIL_API mw3dContour<T> Transform(
	const mw3dContour<T>& contour, const mwMatrix<T, 4, 4>& matrix);

}  // namespace mw3dTransformationFactory
}  // namespace cadcam
#endif  //	MW_MW3DTRANSFORMATIONFACTORY_HPP_
