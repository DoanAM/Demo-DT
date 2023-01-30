// (C) 2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWBINSTREAMERGEOMETRY_HPP_
#define MW_MWBINSTREAMERGEOMETRY_HPP_
#include "mwDllImpExpDef.hpp"

namespace cadcam
{
namespace mwBinStreamerGeometry
{
/// Load
///
/// Loads a cadcam Geometry object using an input stream
///	@param inputStream the stream from where to read the data
///	@remark reference to stl stream (ostream, ofstream, iostream, etc.) or misc::mwBinInputStream
/// (and derived classes)
///	@param geo the place where to put the read data
///	@remark reference to a geometry object or reference to an auto pointer to a geometry object
///	@remark object is a class from cadcam::mw2dGeometry or cadcam::mw3dGeometry hierarchy or 
/// cadcam::mwTPoint2d/cadcam::mwTPoint3d
///	@throws mwException if any read value is invalid
template <typename Stream, typename Geometry>
void MW_5AXUTIL_API Load(Stream& inputStream, Geometry& geo);

/// Save
///
/// Saves a cadcam Geometry object using an output stream
///	@param outputStream the stream where to write the data
/// @remark reference to stl stream (istream, ifstream, iostream, etc.) or misc::mwBinOutputStream
/// (and derived classes)
///	@param geo the data to be written
///	@remark reference to a geometry object or reference to an auto pointer to a geometry object
///	@remark object is a class from cadcam::mw2dGeometry or cadcam::mw3dGeometry hierarchy or 
/// cadcam::mwTPoint2d or cadcam::mwTPoint3d
///	@throws mwException if it's not able to write data though the provided stream
template <typename Stream, typename Geometry>
void MW_5AXUTIL_API Save(Stream& outputStream, const Geometry& geo);

}  // namespace mwBinStreamerGeometry
}  // namespace cadcam
#endif  //	MW_MWBINSTREAMERGEOMETRY_HPP_
