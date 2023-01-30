// (C) 2011-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCADCAMFWDDECL_HPP_
#define MW_MWCADCAMFWDDECL_HPP_
#include "mwMiscFwdDecl.hpp"
#include "mwDllImpExpDef.hpp"

#include <vector>

namespace cadcam
{
class mw2dPolygon;
class mwGenericRevolvedTool;
class mwIContactNormalFinder;
class mwRevolvedTool;
class mwBarrelTangentMill;
class mwBarrelTangentMillConicalShaft;
class mwTool;
class mwParamPolyline;
class mwParamPolylineSample;

class mwToolPath;
class mwTPContour;
class mwTPHelixFit;
class mwTPLink;
class mwTPPolyLineFit;
class mwTPSection;
class mwTPSectionFit;
class mwCNCMove;
class mwToolpathLayered;
class mwToolpathInt;
class mwMeshWithStockRemainSet;

class mwTypedRevolvedTool;
class mwTypedExtrudedTool;

template <
	int Style,
	typename Key,
	typename Mapped /*= void */,
	typename Transform /*= void */,
	typename TransformedKey /*= void */>
class mwContainer;

template <typename T, int rows, int columns>
struct MW_5AXUTIL_API mwMatrix;
template <typename T>
class MW_5AXUTIL_API mw2dArc;
template <typename T>
class MW_5AXUTIL_API mw2dBoundingBox;
template <typename T>
class MW_5AXUTIL_API mw2dContour;
template <typename T>
class mw2dDistCalcPolyLine;
template <typename T>
class MW_5AXUTIL_API mw2dGeometry;
template <typename T>
class MW_5AXUTIL_API mw2dLine;
template <typename T>
class MW_5AXUTIL_API mw2dMultipleClosedContour;
template <typename T>
class MW_5AXUTIL_API mw2dMultipleClosedPolyLine;
template <typename T>
class MW_5AXUTIL_API mw2dPoint;
template <typename T>
class MW_5AXUTIL_API mw2dPolyLine;
template <typename T>
class MW_5AXUTIL_API mw3dArc;
template <typename T>
class MW_5AXUTIL_API mw3dBoundingBox;
template <typename T>
class MW_5AXUTIL_API mw3dContour;
template <typename T>
class MW_5AXUTIL_API mw3dGeometry;
template <typename T>
class MW_5AXUTIL_API mw3dLine;
template <typename T>
class MW_5AXUTIL_API mw3dPoint;
template <typename T>
class MW_5AXUTIL_API mw3dPolyLine;
template <typename T>
class MW_5AXUTIL_API mw3dHelix;
template <typename T>
class mwPolygonsWithBoundingBoxesTree;
template <typename T>
class mwPolyLine2ContourConverter;
template <typename T>
class MW_5AXUTIL_API mwTMesh;
template <typename T>
class MW_5AXUTIL_API mw3dPolygonizer;
template <typename T>
struct MW_5AXUTIL_API mwTPoint2d;
template <typename T>
struct MW_5AXUTIL_API mwTPoint3d;

template <typename T>
class mwTriangle;
template <typename T>
class mwSphere;
template <typename T>
class MW_5AXUTIL_API mwTruncatedCone;
template <typename T>
class MW_5AXUTIL_API mwCylinder;
template <typename T>
class MW_5AXUTIL_API mwHolderDefinition;

template <typename T, typename Handle>
class mwQuadtree;

typedef mw2dGeometry<double> Geometry2D;
typedef misc::mwAutoPointer<Geometry2D> Geometry2DPtr;
typedef std::vector<Geometry2D> Geometry2DVec;
typedef std::vector<Geometry2DPtr> Geometry2DPtrVec;

typedef mw2dGeometry<float> Geometry2F;
typedef misc::mwAutoPointer<Geometry2F> Geometry2FPtr;
typedef std::vector<Geometry2F> Geometry2FVec;
typedef std::vector<Geometry2FPtr> Geometry2FPtrVec;

typedef mw3dGeometry<double> Geometry3D;
typedef misc::mwAutoPointer<Geometry3D> Geometry3DPtr;
typedef std::vector<Geometry3D> Geometry3DVec;
typedef std::vector<Geometry3DPtr> Geometry3DPtrVec;

typedef mw3dGeometry<float> Geometry3F;
typedef misc::mwAutoPointer<Geometry3F> Geometry3FPtr;
typedef std::vector<Geometry3F> Geometry3FVec;
typedef std::vector<Geometry3FPtr> Geometry3FPtrVec;

typedef mwTPoint2d<double> Point2D;
typedef std::vector<Point2D> Point2DVec;
typedef std::vector<Point2DVec> Point2DVecVec;

typedef mwTPoint2d<float> Point2F;
typedef std::vector<Point2F> Point2FVec;
typedef std::vector<Point2FVec> Point2FVecVec;

typedef mwTPoint3d<double> Point3D;
typedef std::vector<Point3D> Point3DVec;
typedef std::vector<Point3DVec> Point3DVecVec;

typedef Point3D Vector3D;
typedef std::vector<Vector3D> Vector3DVec;
typedef std::vector<Vector3DVec> Vector3DVecVec;

typedef mwTPoint3d<float> Point3F;
typedef std::vector<Point3F> Point3FVec;
typedef std::vector<Point3FVec> Point3FVecVec;

typedef mw2dLine<double> Line2D;
typedef misc::mwAutoPointer<Line2D> Line2DPtr;
typedef std::vector<Line2D> Line2DVec;
typedef std::vector<Line2DPtr> Line2DPtrVec;

typedef mw2dLine<float> Line2F;
typedef misc::mwAutoPointer<Line2F> Line2FPtr;
typedef std::vector<Line2F> Line2FVec;
typedef std::vector<Line2FPtr> Line2FPtrVec;

typedef mw3dLine<double> Line3D;
typedef misc::mwAutoPointer<Line3D> Line3DPtr;
typedef std::vector<Line3D> Line3DVec;
typedef std::vector<Line3DPtr> Line3DPtrVec;

typedef mw3dLine<float> Line3F;
typedef misc::mwAutoPointer<Line3F> Line3FPtr;
typedef std::vector<Line3F> Line3FVec;
typedef std::vector<Line3FPtr> Line3FPtrVec;

typedef mw2dArc<double> Arc2D;
typedef misc::mwAutoPointer<Arc2D> Arc2DPtr;
typedef std::vector<Arc2D> Arc2DVec;
typedef std::vector<Arc2DPtr> Arc2DPtrVec;

typedef mw2dArc<float> Arc2F;
typedef misc::mwAutoPointer<Arc2F> Arc2FPtr;
typedef std::vector<Arc2F> Arc2FVec;
typedef std::vector<Arc2FPtr> Arc2FPtrVec;

typedef mw3dArc<double> Arc3D;
typedef misc::mwAutoPointer<Arc3D> Arc3DPtr;
typedef std::vector<Arc3D> Arc3DVec;
typedef std::vector<Arc3DPtr> Arc3DPtrVec;

typedef mw3dArc<float> Arc3F;
typedef misc::mwAutoPointer<Arc3F> Arc3FPtr;
typedef std::vector<Arc3F> Arc3FVec;
typedef std::vector<Arc3FPtr> Arc3FPtrVec;

typedef mw2dPolyLine<double> Polyline2D;
typedef misc::mwAutoPointer<Polyline2D> Polyline2DPtr;
typedef std::vector<Polyline2D> Polyline2DVec;
typedef std::vector<Polyline2DVec> Polyline2DVecVec;
typedef std::vector<Polyline2DPtr> Polyline2DPtrVec;

typedef mw2dPolyLine<float> Polyline2F;
typedef misc::mwAutoPointer<Polyline2F> Polyline2FPtr;
typedef std::vector<Polyline2F> Polyline2FVec;
typedef std::vector<Polyline2FPtr> Polyline2FPtrVec;

typedef mw3dPolyLine<double> Polyline3D;
typedef misc::mwAutoPointer<Polyline3D> Polyline3DPtr;
typedef std::vector<Polyline3D> Polyline3DVec;
typedef std::vector<Polyline3DVec> Polyline3DVecVec;
typedef std::vector<Polyline3DPtr> Polyline3DPtrVec;

typedef mw3dPolyLine<float> Polyline3F;
typedef misc::mwAutoPointer<Polyline3F> Polyline3FPtr;
typedef std::vector<Polyline3F> Polyline3FVec;
typedef std::vector<Polyline3FPtr> Polyline3FPtrVec;

typedef mwTMesh<double> MeshD;
typedef misc::mwAutoPointer<MeshD> MeshDPtr;
typedef std::vector<MeshD> MeshDVec;
typedef std::vector<MeshDPtr> MeshDPtrVec;

typedef mwTMesh<float> MeshF;
typedef misc::mwAutoPointer<MeshF> MeshFPtr;
typedef std::vector<MeshF> MeshFVec;
typedef std::vector<MeshFPtr> MeshFPtrVec;

typedef mw2dBoundingBox<double> Box2D;
typedef misc::mwAutoPointer<Box2D> Box2DPtr;
typedef std::vector<Box2D> Box2DVec;
typedef std::vector<Box2DPtr> Box2DPtrVec;

typedef mw2dBoundingBox<float> Box2F;
typedef misc::mwAutoPointer<Box2F> Box2FPtr;
typedef std::vector<Box2F> Box2FVec;
typedef std::vector<Box2FPtr> Box2FPtrVec;

typedef mw3dBoundingBox<double> Box3D;
typedef misc::mwAutoPointer<Box3D> Box3DPtr;
typedef std::vector<Box3D> Box3DVec;
typedef std::vector<Box3DPtr> Box3DPtrVec;

typedef mw3dBoundingBox<float> Box3F;
typedef misc::mwAutoPointer<Box3F> Box3FPtr;
typedef std::vector<Box3F> Box3FVec;
typedef std::vector<Box3FPtr> Box3FPtrVec;

typedef mw2dContour<double> Contour2D;
typedef misc::mwAutoPointer<Contour2D> Contour2DPtr;
typedef std::vector<Contour2D> Contour2DVec;
typedef std::vector<Contour2DPtr> Contour2DPtrVec;

typedef mw2dContour<float> Contour2F;
typedef misc::mwAutoPointer<Contour2F> Contour2FPtr;
typedef std::vector<Contour2F> Contour2FVec;
typedef std::vector<Contour2FPtr> Contour2FPtrVec;

typedef mw3dContour<double> Contour3D;
typedef misc::mwAutoPointer<Contour3D> Contour3DPtr;
typedef std::vector<Contour3D> Contour3DVec;
typedef std::vector<Contour3DPtr> Contour3DPtrVec;

typedef mw3dContour<float> Contour3F;
typedef misc::mwAutoPointer<Contour3F> Contour3FPtr;
typedef std::vector<Contour3F> Contour3FVec;
typedef std::vector<Contour3FPtr> Contour3FPtrVec;

typedef mw2dMultipleClosedContour<double> MultiContour2D;
typedef misc::mwAutoPointer<MultiContour2D> MultiContour2DPtr;
typedef std::vector<MultiContour2D> MultiContour2DVec;
typedef std::vector<MultiContour2DPtr> MultiContour2DPtrVec;

typedef mw2dMultipleClosedContour<float> MultiContour2F;
typedef misc::mwAutoPointer<MultiContour2F> MultiContour2FPtr;
typedef std::vector<MultiContour2F> MultiContour2FVec;
typedef std::vector<MultiContour2FPtr> MultiContour2FPtrVec;

typedef mw2dMultipleClosedPolyLine<double> MultiPolyline2D;
typedef misc::mwAutoPointer<MultiPolyline2D> MultiPolyline2DPtr;
typedef std::vector<MultiPolyline2D> MultiPolyline2DVec;
typedef std::vector<MultiPolyline2DPtr> MultiPolyline2DPtrVec;

typedef mw2dMultipleClosedPolyLine<float> MultiPolyline2F;
typedef misc::mwAutoPointer<MultiPolyline2F> MultiPolyline2FPtr;
typedef std::vector<MultiPolyline2F> MultiPolyline2FVec;
typedef std::vector<MultiPolyline2FPtr> MultiPolyline2FPtrVec;

typedef mw3dHelix<double> Helix3D;
typedef misc::mwAutoPointer<Helix3D> Helix3DPtr;
typedef std::vector<Helix3D> Helix3DVec;
typedef std::vector<Helix3DPtr> Helix3DPtrVec;

typedef mw3dHelix<float> Helix3F;
typedef misc::mwAutoPointer<Helix3F> Helix3FPtr;
typedef std::vector<Helix3F> Helix3FVec;
typedef std::vector<Helix3FPtr> Helix3FPtrVec;

typedef mwMatrix<double, 3, 3> Matrix3D;
typedef misc::mwAutoPointer<Matrix3D> Matrix3DPtr;
typedef std::vector<Matrix3D> Matrix3DVec;
typedef std::vector<Matrix3DPtr> Matrix3DPtrVec;

typedef mwMatrix<float, 3, 3> Matrix3F;
typedef misc::mwAutoPointer<Matrix3F> Matrix3FPtr;
typedef std::vector<Matrix3F> Matrix3FVec;
typedef std::vector<Matrix3FPtr> Matrix3FPtrVec;

typedef mwMatrix<double, 4, 4> Matrix4D;
typedef misc::mwAutoPointer<Matrix4D> Matrix4DPtr;
typedef std::vector<Matrix4D> Matrix4DVec;
typedef std::vector<Matrix4DPtr> Matrix4DPtrVec;

typedef mwMatrix<float, 4, 4> Matrix4F;
typedef misc::mwAutoPointer<Matrix4F> Matrix4FPtr;
typedef std::vector<Matrix4F> Matrix4FVec;
typedef std::vector<Matrix4FPtr> Matrix4FPtrVec;

typedef misc::mwAutoPointer<mwToolPath> ToolPathPtr;
typedef std::vector<mwToolPath> ToolPathVec;
typedef std::vector<ToolPathPtr> ToolPathPtrVec;

/// @deprecated	The type aliases in GenericNames namespace are deprecated.
/// Please use the type aliases above instead, which are directly in the cadcam
/// namespace.
namespace GenericNames
{
typedef mw2dGeometry<double> Geometry2d;
typedef mw3dGeometry<double> Geometry3d;
typedef mw2dArc<double> Arc2d;
typedef mw2dBoundingBox<double> Box2d;
typedef mw2dContour<double> Contour2d;
typedef mw2dLine<double> Line2d;
typedef mw2dMultipleClosedContour<double> MultiContour2d;
typedef mw2dMultipleClosedPolyLine<double> MultiPolyline2d;
typedef mw2dPolyLine<double> Polyline2d;
typedef mw3dArc<double> Arc3d;
typedef mw3dHelix<double> Helix3d;
typedef mw3dBoundingBox<double> Box3d;
typedef mw3dContour<double> Contour3d;
typedef mw3dLine<double> Line3d;
typedef mw3dPolyLine<double> Polyline3d;
typedef mwTPoint2d<double> Point2d;
typedef mwTPoint3d<double> Point3d;
typedef mwTMesh<double> Mesh;

typedef misc::mwAutoPointer<Geometry2d> Geometry2dPtr;

typedef std::vector<Point3d> Point3dVec;
typedef std::vector<Point3dVec> Point3dVecVec;
typedef std::vector<Box2d> Box2dVec;
typedef std::vector<Box3d> Box3dVec;
typedef std::vector<Contour2d> Contour2dVec;
typedef std::vector<Contour2dVec> Contour2dVecVec;
typedef std::vector<Contour3d> Contour3dVec;
typedef std::vector<Contour3dVec> Contour3dVecVec;
typedef std::vector<Line2d> Line2dVec;
typedef std::vector<Line2dVec> Line2dVecVec;
typedef std::vector<Line3d> Line3dVec;
typedef std::vector<Arc2d> Arc2dVec;
typedef std::vector<Arc3d> Arc3dVec;
typedef std::vector<MultiContour2d> MultiContour2dVec;
typedef std::vector<MultiPolyline2d> MultiPolyline2dVec;
typedef std::vector<Point2d> Point2dVec;
typedef std::vector<Point2dVec> Point2dVec2;
typedef std::vector<Point2dVec2> Point2dVec3;
typedef std::vector<Polyline2d> Polyline2dVec;
typedef std::vector<Polyline2dVec> Polyline2dVecVec;
typedef std::vector<Polyline3d> Polyline3dVec;
typedef std::vector<Polyline3dVec> Polyline3dVecVec;
typedef std::vector<Polyline3dVecVec> Polyline3dVecVecVec;
typedef std::vector<Geometry2dPtr> Geometry2dPtrVec;
typedef std::vector<Mesh> MeshVec;

typedef mwMatrix<double, 3, 3> Matrix3d;
typedef mwMatrix<double, 4, 4> Matrix4d;
typedef std::vector<mwToolPath> mwToolPathVec;
}  // namespace GenericNames
}  // namespace cadcam
#endif  // MW_MWCADCAMFWDDECL_HPP_
