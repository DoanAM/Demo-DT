// (C) 2016-2021 by ModuleWorks GmbH
// Owner: 5Axis Rotary & Multiblade

#ifndef MW_MWMESHDECIMATOR_HPP_
#define MW_MWMESHDECIMATOR_HPP_
#include "mwMesh.hpp"
#include "mwSimUtilDllImpExpDef.hpp"

namespace meshtools
{
namespace mwMeshDecimator
{
//! Reduce triangles of a mesh for given tolerance
/** @param mesh The triangle mesh is decimated in place.
	Copy it before, if you want to keep the original mesh.
	@param tolerance Defines the maximal error for the decimation.
    The new mesh will have a maximal distance to the original mesh smaller than this error.
	@param fastDecimation Enables a fast version, which will therefore reduces less triangles. 
	@param decimateBoundaries Enables decimation along mesh boundaries.
	*/
MW_SIMUTIL_API void Decimate(
	cadcam::mwTMesh<double>& mesh,
	const double tolerance,
	const bool fastDecimation = false,
	const bool decimateBoundaries = false);
	
/** @copydoc Decimate */
MW_SIMUTIL_API void Decimate(
	cadcam::mwTMesh<float>& mesh,
	const float tolerance,
	const bool fastDecimation = false,
	const bool decimateBoundaries = false);
}  // namespace mwMeshDecimator
}  // namespace meshtools
#endif	//	MW_MWMESHDECIMATOR_HPP_
