// (C) 2012-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DGEOMETRYTYPEDEFS_HPP_
#define MW_MW3DGEOMETRYTYPEDEFS_HPP_
#include "mwDllImpExpDef.hpp"

namespace misc
{
template <class T>
class mwAutoPointer;
}
namespace cadcam
{
// Forward declarations.
template <class T>
class MW_5AXUTIL_API mw3dArc;
template <class T>
class MW_5AXUTIL_API mw3dBoundingBox;
template <class T>
class MW_5AXUTIL_API mw3dClosedContour;
template <class T>
class MW_5AXUTIL_API mw3dContour;
template <class T>
class MW_5AXUTIL_API mw3dLine;
template <class T>
class mw3dOrientedBoundingBox;
template <class T>
class MW_5AXUTIL_API mw3dPoint;
template <class T>
class MW_5AXUTIL_API mw3dPolyLine;
template <class T>
class MW_5AXUTIL_API mw3dHelix;
template <class T>
struct MW_5AXUTIL_API mwTPlane3d;
template <class T>
struct MW_5AXUTIL_API mwTPoint3d;
template <class T>
class MW_5AXUTIL_API mw3dGeometryConstVisitor;
template <class T>
class MW_5AXUTIL_API mw3dGeometryVisitor;
template <class T>
class MW_5AXUTIL_API mwTMesh;
template <typename, int, int>
struct MW_5AXUTIL_API mwMatrix;

// int Geometry
typedef mw3dBoundingBox<int> mw3diBoundingBox;
typedef mwTPoint3d<int> mwPoint3di;

// float Geometry
typedef mw3dPoint<float> mw3dfPoint;
typedef mw3dLine<float> mw3dfLine;
typedef mw3dArc<float> mw3dfArc;
typedef mw3dBoundingBox<float> mw3dfBoundingBox;
typedef mw3dOrientedBoundingBox<float> mw3dfOrientedBoundingBox;
typedef mw3dContour<float> mw3dfContour;
typedef mw3dPolyLine<float> mw3dfPolyLine;
typedef mw3dClosedContour<float> mw3dfClosedContour;
typedef mw3dHelix<float> mw3dfHelix;
typedef mw3dGeometryConstVisitor<float> mw3dfGeometryConstVisitor;
typedef mw3dGeometryVisitor<float> mw3dfGeometryVisitor;
typedef mwTMesh<float> mwfMesh;
typedef mwTPlane3d<float> mwPlane3df;
typedef mwTPoint3d<float> mwPoint3df;
typedef mwMatrix<float, 4, 4> mwHomogenousMatrix;

typedef misc::mwAutoPointer<mw3dfPoint> mw3dfPointPtr;
typedef misc::mwAutoPointer<mw3dfLine> mw3dfLinePtr;
typedef misc::mwAutoPointer<mw3dfArc> mw3dfArcPtr;
typedef misc::mwAutoPointer<mw3dfContour> mw3dfContourPtr;
typedef misc::mwAutoPointer<mw3dfPolyLine> mw3dfPolyLinePtr;
typedef misc::mwAutoPointer<mw3dfClosedContour> mw3dfClosedContourPtr;
typedef misc::mwAutoPointer<mw3dfHelix> mw3dfHelixPtr;
typedef misc::mwAutoPointer<mwfMesh> mwfMeshPtr;

// double field
typedef mw3dPoint<double> mw3ddPoint;
typedef mw3dLine<double> mw3ddLine;
typedef mw3dArc<double> mw3ddArc;
typedef mw3dBoundingBox<double> mw3ddBoundingBox;
typedef mw3dOrientedBoundingBox<double> mw3ddOrientedBoundingBox;
typedef mw3dContour<double> mw3ddContour;
typedef mw3dPolyLine<double> mw3ddPolyLine;
typedef mw3dClosedContour<double> mw3ddClosedContour;
typedef mw3dHelix<double> mw3ddHelix;
typedef mw3dGeometryConstVisitor<double> mw3ddGeometryConstVisitor;
typedef mw3dGeometryVisitor<double> mw3ddGeometryVisitor;
typedef mwTMesh<double> mwdMesh;
typedef mwTPlane3d<double> mwPlane3d;
typedef mwTPoint3d<double> mwPoint3d;
typedef mwMatrix<double, 4, 4> mwHomogenousMatrixd;

typedef misc::mwAutoPointer<mw3ddPoint> mw3ddPointPtr;
typedef misc::mwAutoPointer<mw3ddLine> mw3ddLinePtr;
typedef misc::mwAutoPointer<mw3ddArc> mw3ddArcPtr;
typedef misc::mwAutoPointer<mw3ddContour> mw3ddContourPtr;
typedef misc::mwAutoPointer<mw3ddPolyLine> mw3ddPolyLinePtr;
typedef misc::mwAutoPointer<mw3ddClosedContour> mw3ddClosedContourPtr;
typedef misc::mwAutoPointer<mw3ddHelix> mw3ddHelixPtr;
typedef misc::mwAutoPointer<mwdMesh> mwdMeshPtr;
}  // namespace cadcam
#endif  //	MW_MW3DGEOMETRYTYPEDEFS_HPP_
