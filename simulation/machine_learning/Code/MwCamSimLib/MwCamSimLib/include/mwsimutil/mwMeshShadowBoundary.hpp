// (C) 2015-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMESHSHADOWBOUNDARY_HPP_
#define MW_MWMESHSHADOWBOUNDARY_HPP_
#include "mw2dPolyLine.hpp"
#include "mwMesh.hpp"

#include <vector>

namespace cadcam
{
namespace mwMeshShadowBoundary
{
//  T stepping - step of grid
//  bool useVerticalWalls - to detect thin vertical walls
//  bool& isOffsetted - if useVerticalWalls is enabled and some vertical walls were detected,
//  then the grid (and resulting shadow) will be offsetted outside a bit; if isOffsetted is true
//  you need to offset in inside with stepping.

template <typename T>
MW_DEPRECATED("Deprecated since 2017.08, please use triax::GetMeshSilhouette")
MW_5AXUTIL_API std::vector<mw2dPolyLine<T>> Calculate(
	const mwTMesh<T>& src,
	const T stepping,
	bool& isOffsetted,
	const bool useVerticalWalls = false);


template <typename T>
MW_DEPRECATED("Deprecated since 2017.08, please use triax::GetMeshSilhouette")
MW_5AXUTIL_API std::vector<mw2dPolyLine<T>> Calculate(
	const mwTMesh<T>& src, const T stepping, const bool useVerticalWalls = false);

template <typename T>
std::vector<mw2dPolyLine<T>> CalculateOld(
	const mwTMesh<T>& src,
	const T stepping,
	bool& isOffsetted,
	const bool useVerticalWalls = false);


template <typename T>
std::vector<mw2dPolyLine<T>> CalculateOld(
	const mwTMesh<T>& src, const T stepping, const bool useVerticalWalls = false);

}  // namespace mwMeshShadowBoundary
}  // namespace cadcam
#endif  //	MW_MWMESHSHADOWBOUNDARY_HPP_
