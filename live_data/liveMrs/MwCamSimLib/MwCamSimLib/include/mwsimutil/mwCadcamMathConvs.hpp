// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCADCAMMATHCONVS_HPP_
#define MW_MWCADCAMMATHCONVS_HPP_

#include "mw2dPoint.hpp"
#include "mw3dPoint.hpp"
#include "mwTVector2.hpp"
#include "mwTVector3.hpp"


/// provide functions to convert from cadcam to mathdef and viceversa
namespace cadcam
{
/// convert from mathdef to cadcam a vector3d
///
///	@param vector to convert
///	@return converted object
template <typename T>
static inline cadcam::mwTPoint3d<T> to_cadcam(const mathdef::mwTVector3<T>& vector)
{
	return cadcam::mwTPoint3d<T>(vector.x(), vector.y(), vector.z());
}

/// convert from mathdef to cadcam a vector2d
///
///	@param vector to convert
///	@return converted object
template <typename T>
static inline cadcam::mwTPoint2d<T> to_cadcam(const mathdef::mwTVector2<T>& vector)
{
	return cadcam::mwTPoint2d<T>(vector.x(), vector.y());
}

/// convert from cadcam to mathdef a vector3d
///
///	@param point object to be converted
///	@return converted object
template <typename T>
static inline mathdef::mwTVector3<T> from_cadcam(const cadcam::mwTPoint3d<T>& point)
{
	return mathdef::mwTVector3<T>(point.x(), point.y(), point.z());
}

/// convert from mathdef to cadcam a vector3d
///
///	@param point object to be converted
///	@return converted object
template <typename T>
static inline mathdef::mwTVector3<T> from_cadcam(const cadcam::mw3dPoint<T>& point)
{
	return mathdef::mwTVector3<T>(point.x(), point.y(), point.z());
}

/// convert from cadcam to mathdef a vector2d
///
///	@param point object to be converted
///	@return converted object
template <typename T>
static inline mathdef::mwTVector2<T> from_cadcam(const cadcam::mwTPoint2d<T>& point)
{
	return mathdef::mwTVector2<T>(point.x(), point.y());
}

/// convert from cadcam to mathdef a vector2d
///
///	@param point object to be converted
///	@return converted object
template <typename T>
static inline mathdef::mwTVector2<T> from_cadcam(const cadcam::mw2dPoint<T>& point)
{
	return mathdef::mwTVector2<T>(point.x(), point.y());
}
}  // namespace cadcam
#endif  //	MW_MWCADCAMMATHCONVS_HPP_
