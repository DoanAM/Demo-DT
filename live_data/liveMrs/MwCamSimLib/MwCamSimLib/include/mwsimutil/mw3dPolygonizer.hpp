// (C) 2003-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DPOLYGONIZER_HPP_
#define MW_MW3DPOLYGONIZER_HPP_
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
template <class T>
class mw3dPolyLine;
template <class T>
class mw3dContour;
template <class T>
class mw3dGeometry;

// don't use this class directly
// instead use functions from mwPolygonizer namespace
template <typename T>
class MW_5AXUTIL_API mw3dPolygonizer
{
public:
	static void Polygonize(
		const mw3dGeometry<T>& src, mw3dPolyLine<T>& dest, const T tolerance = 0.01f);

	static void Polygonize(
		const std::vector<mw3dContour<T>>& src,
		std::vector<mw3dPolyLine<T>>& dest,
		const T tolerance = 0.01f);

private:
	/// Constructor not allowed since it's a static class
	mw3dPolygonizer();
};
}  // namespace cadcam
#endif  //	MW_MW3DPOLYGONIZER_HPP_
