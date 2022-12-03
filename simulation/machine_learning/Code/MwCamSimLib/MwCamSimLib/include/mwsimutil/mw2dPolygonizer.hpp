// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DPOLYGONIZER_HPP_
#define MW_MW2DPOLYGONIZER_HPP_
#include "mwDllImpExpDef.hpp"

#include <vector>


namespace cadcam
{
template <class T>
class mw2dPolyLine;
template <class T>
class mw2dContour;
template <class T>
class mw2dGeometry;

// don't use this class directly
// instead use functions from mwPolygonizer namespace
template <typename T>
class MW_5AXUTIL_API mw2dPolygonizer
{
public:
	typedef mw2dPolyLine<T> PolyLine2d;
	typedef mw2dContour<T> Contour2d;

	typedef std::vector<PolyLine2d> PolyLine2dVec;
	typedef std::vector<Contour2d> Contour2dVec;

	static void Polygonize(const mw2dGeometry<T>& src, PolyLine2d& dest, const T tolerance = 0.01f);

	static void Polygonize(const Contour2dVec& src, PolyLine2dVec& dst, const T tolerance = 0.01);

	static PolyLine2d Polygonize(const mw2dGeometry<T>& src, const T tolerance = 0.01f);
	static PolyLine2dVec Polygonize(const Contour2dVec& src, const T tolerance = 0.01);

	/// @param src geometry to polygonize
	/// @param dest where to store the result
	/// @param tolerance chordal deviation
	/// @param maxAllowedAngle maximum allowed angle deviation
	static void PolygonizeWithMaxAngle(
		const mw2dGeometry<T>& src, PolyLine2d& dest, const T tolerance, const T maxAllowedAngle);

private:
	/// Constructor not allowed since it's a static class
	mw2dPolygonizer();
};
}  // namespace cadcam
#endif  //	MW_MW2DPOLYGONIZER_HPP_
