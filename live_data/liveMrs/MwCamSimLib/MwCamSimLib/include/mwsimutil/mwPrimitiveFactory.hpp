// (C) 2016-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWPRIMITIVEFACTORY_HPP_
#define MW_MWPRIMITIVEFACTORY_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMesh.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwPrimitiveFactory
{
public:
	static cadcam::mwTMesh<double>::Ptr CreateSolid(
		size_t nfaces,
		size_t nloops[],
		size_t nverts[],
		size_t indices[],
		cadcam::mwTMesh<double>::point3d verts[],
		int normal_indices[],
		cadcam::mwTMesh<double>::point3d normals[],
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC,
		double coplanarityTolerance = mathdef::mw_tol(double()));

	static cadcam::mwTMesh<float>::Ptr CreateSolid(
		size_t nfaces,
		size_t nloops[],
		size_t nverts[],
		size_t indices[],
		cadcam::mwTMesh<float>::point3d verts[],
		int normal_indices[],
		cadcam::mwTMesh<float>::point3d normals[],
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC,
		float coplanarityTolerance = mathdef::mw_tol(float()));

	static cadcam::mwTMesh<double>::Ptr CreateMesh(
		const std::vector<std::vector<cadcam::mwTMesh<double>::point3d>>& verts,
		cadcam::mwTMesh<double>::point3d normal,
		double offset,
		double maxPlaneDist = mathdef::mw_tol(double()),
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC,
		bool doReduction = true);

	static cadcam::mwTMesh<float>::Ptr CreateMesh(
		const std::vector<std::vector<cadcam::mwTMesh<float>::point3d>>& verts,
		cadcam::mwTMesh<float>::point3d normal,
		float offset,
		float maxPlaneDist = mathdef::mw_tol(float()),
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC,
		bool doReduction = true);

	static cadcam::mwTMesh<double>::Ptr CreateExtrudedMesh(
		const std::vector<std::vector<cadcam::mwTMesh<double>::point3d>>& verts,
		cadcam::mwTMesh<double>::point3d normal,
		double minOffset,
		double maxOffset,
		double maxPlaneDist = mathdef::mw_tol(double()),
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC);

	static cadcam::mwTMesh<float>::Ptr CreateExtrudedMesh(
		const std::vector<std::vector<cadcam::mwTMesh<float>::point3d>>& verts,
		cadcam::mwTMesh<float>::point3d normal,
		float minOffset,
		float maxOffset,
		float maxPlaneDist = mathdef::mw_tol(float()),
		measures::mwMeasurable::Units units = measures::mwUnitsFactory::METRIC);

private:
	mwPrimitiveFactory(){};
};
}  // namespace cadcam
#endif  //	MW_MWPRIMITIVEFACTORY_HPP_
