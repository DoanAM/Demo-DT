// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGEOMETRYCOPY_HPP_
#define MW_MWGEOMETRYCOPY_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwMiscFwdDecl.hpp"


namespace cadcam
{
namespace mwGeometryCopy
{
template <class T>
mw2dPoint<T> Deep(const mw2dPoint<T>& src);
template <class T>
mw2dLine<T> Deep(const mw2dLine<T>& src);
template <class T>
mw2dArc<T> Deep(const mw2dArc<T>& src);
template <class T>
mw2dContour<T> Deep(const mw2dContour<T>& src);
template <class T>
mw2dPolyLine<T> Deep(const mw2dPolyLine<T>& src);
template <class T>
mw2dMultipleClosedContour<T> Deep(const mw2dMultipleClosedContour<T>& src);

template <class T>
mw3dPoint<T> Deep(const mw3dPoint<T>& src);
template <class T>
mw3dLine<T> Deep(const mw3dLine<T>& src);
template <class T>
mw3dArc<T> Deep(const mw3dArc<T>& src);
template <class T>
mw3dContour<T> Deep(const mw3dContour<T>& src);
template <class T>
mw3dPolyLine<T> Deep(const mw3dPolyLine<T>& src);
template <class T>
mw3dHelix<T> Deep(const mw3dHelix<T>& src);

template <class Geometry>
std::vector<Geometry> Deep(const std::vector<Geometry>& src);

template <class T>
misc::mwAutoPointer<mw2dGeometry<T>> Deep(const mw2dGeometry<T>& src);
template <class T>
misc::mwAutoPointer<mw3dGeometry<T>> Deep(const mw3dGeometry<T>& src);

template <class T, template <class> class TPtr>
TPtr<mw2dGeometry<T>> DeepPtr(const mw2dGeometry<T>& src);

template <class T, template <class> class TPtr>
TPtr<mw3dGeometry<T>> DeepPtr(const mw3dGeometry<T>& src);

template <class T, template <class> class TPtr, class Geometry>
TPtr<Geometry> DeepPtr(const Geometry& src)
{
	return TPtr<Geometry>(new Geometry(src));
}
}  // namespace mwGeometryCopy
}  // namespace cadcam
#endif  //	MW_MWGEOMETRYCOPY_HPP_
