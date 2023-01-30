// (C) 2012-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DGEOMETRYTYPEDEFS_HPP_
#define MW_MW2DGEOMETRYTYPEDEFS_HPP_
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
class MW_5AXUTIL_API mw2dArc;
template <class T>
class MW_5AXUTIL_API mw2dCurve;
template <class T>
class MW_5AXUTIL_API mw2dClosedContour;
template <class T>
class MW_5AXUTIL_API mw2dContour;
template <class T>
class MW_5AXUTIL_API mw2dGeometry;
template <class T>
class MW_5AXUTIL_API mw2dLine;
template <class T>
class MW_5AXUTIL_API mw2dPoint;
template <class T>
class MW_5AXUTIL_API mw2dPolyLine;
template <class T>
class MW_5AXUTIL_API mw2dBoundingBox;
template <class T>
struct MW_5AXUTIL_API mwTPoint2d;
template <class T>
class MW_5AXUTIL_API mw2dGeometryConstVisitor;
template <class T>
class MW_5AXUTIL_API mw2dGeometryVisitor;
template <typename, int, int>
struct MW_5AXUTIL_API mwMatrix;

// int Geometry
typedef mw2dBoundingBox<int> mw2diBoundingBox;
typedef mwTPoint2d<int> mwPoint2di;

// float Geometry
typedef mw2dGeometry<float> mw2dfGeometry;
typedef mw2dPoint<float> mw2dfPoint;
typedef mw2dLine<float> mw2dfLine;
typedef mw2dArc<float> mw2dfArc;
typedef mw2dContour<float> mw2dfContour;
typedef mw2dPolyLine<float> mw2dfPolyLine;
typedef mw2dBoundingBox<float> mw2dfBoundingBox;
typedef mw2dClosedContour<float> mw2dfClosedContour;
typedef mw2dCurve<float> mw2dfCurve;
typedef mw2dGeometryConstVisitor<float> mw2dfGeometryConstVisitor;
typedef mw2dGeometryVisitor<float> mw2dfGeometryVisitor;
typedef mwTPoint2d<float> mwPoint2df;
typedef mwMatrix<float, 3, 3> mw2dHomogenousMatrix;

typedef misc::mwAutoPointer<mw2dfGeometry> mw2dfGeometryPtr;
typedef misc::mwAutoPointer<mw2dfPoint> mw2dfPointPtr;
typedef misc::mwAutoPointer<mw2dfLine> mw2dfLinePtr;
typedef misc::mwAutoPointer<mw2dfArc> mw2dfArcPtr;
typedef misc::mwAutoPointer<mw2dfContour> mw2dfContourPtr;
typedef misc::mwAutoPointer<mw2dfPolyLine> mw2dfPolyLinePtr;
typedef misc::mwAutoPointer<mw2dfBoundingBox> mw2dfBoundingBoxPtr;
typedef misc::mwAutoPointer<mw2dfClosedContour> mw2dfClosedContourPtr;
typedef misc::mwAutoPointer<mw2dfCurve> mw2dfCurvePtr;

// double Geometry
typedef mw2dGeometry<double> mw2ddGeometry;
typedef mw2dPoint<double> mw2ddPoint;
typedef mw2dLine<double> mw2ddLine;
typedef mw2dArc<double> mw2ddArc;
typedef mw2dContour<double> mw2ddContour;
typedef mw2dPolyLine<double> mw2ddPolyLine;
typedef mw2dBoundingBox<double> mw2ddBoundingBox;
typedef mw2dClosedContour<double> mw2ddClosedContour;
typedef mw2dCurve<double> mw2ddCurve;
typedef mw2dGeometryConstVisitor<double> mw2ddGeometryConstVisitor;
typedef mw2dGeometryVisitor<double> mw2ddGeometryVisitor;
typedef mwTPoint2d<double> mwPoint2d;
typedef mwMatrix<double, 3, 3> mw2dHomogenousMatrixd;

typedef misc::mwAutoPointer<mw2ddGeometry> mw2ddGeometryPtr;
typedef misc::mwAutoPointer<mw2ddPoint> mw2ddPointPtr;
typedef misc::mwAutoPointer<mw2ddLine> mw2ddLinePtr;
typedef misc::mwAutoPointer<mw2ddArc> mw2ddArcPtr;
typedef misc::mwAutoPointer<mw2ddContour> mw2ddContourPtr;
typedef misc::mwAutoPointer<mw2ddPolyLine> mw2ddPolyLinePtr;
typedef misc::mwAutoPointer<mw2ddBoundingBox> mw2ddBoundingBoxPtr;
typedef misc::mwAutoPointer<mw2ddClosedContour> mw2ddClosedContourPtr;
typedef misc::mwAutoPointer<mw2ddCurve> mw2ddCurvePtr;
}  // namespace cadcam
#endif  // MW_MW2DGEOMETRYTYPEDEFS_HPP_
