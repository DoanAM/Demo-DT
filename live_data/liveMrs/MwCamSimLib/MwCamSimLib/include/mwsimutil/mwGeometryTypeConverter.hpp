// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGEOMETRYTYPECONVERTER_HPP_
#define MW_MWGEOMETRYTYPECONVERTER_HPP_
#include "mwCadcamFwdDecl.hpp"
#include "mwDefines.hpp"
#include "mwMiscFwdDecl.hpp"

namespace cadcam
{
namespace mwGeometryTypeConverter
{
template <typename TSrc, typename TDst>
void Convert(const mwTPoint2d<TSrc>& src, mwTPoint2d<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dPoint<TSrc>& src, mw2dPoint<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dLine<TSrc>& src, mw2dLine<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dArc<TSrc>& src, mw2dArc<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dPolyLine<TSrc>& src, mw2dPolyLine<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dContour<TSrc>& src, mw2dContour<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw2dBoundingBox<TSrc>& src, mw2dBoundingBox<TDst>& dst);


template <typename TSrc, typename TDst>
void Convert(const mwTPoint3d<TSrc>& src, mwTPoint3d<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dPoint<TSrc>& src, mw3dPoint<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dLine<TSrc>& src, mw3dLine<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dArc<TSrc>& src, mw3dArc<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dPolyLine<TSrc>& src, mw3dPolyLine<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dContour<TSrc>& src, mw3dContour<TDst>& dst);
template <typename TSrc, typename TDst>
void Convert(const mw3dBoundingBox<TSrc>& src, mw3dBoundingBox<TDst>& dst);

#ifndef MW_USE_VS2008_COMPATIBILITY
template <typename T>
void Convert(T&& src, T& dst)
{
	dst = std::forward<T>(src);
}
#endif

template <typename TSrc, typename TDst>
void ConvertContainer(const TSrc& src, TDst& dst)
{
	dst.resize(src.size());
	typename TDst::iterator to = dst.begin();
	for (typename TSrc::const_iterator from = src.begin(); from != src.end(); ++from, ++to)
	{
		Convert(*from, *to);
	}
}

#ifndef MW_USE_VS2008_COMPATIBILITY
template <typename T>
void ConvertContainer(T&& src, T& dst)
{
	dst = std::forward<T>(src);
}
#endif

}  // namespace mwGeometryTypeConverter

}  // namespace cadcam
#endif  //	MW_MWGEOMETRYTYPECONVERTER_HPP_
