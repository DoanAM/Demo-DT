// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTGeometryHelper class

#ifndef MW_MWTGEOMETRYHELPER_HPP_
#define MW_MWTGEOMETRYHELPER_HPP_
//############################################################################
#include "mwTVector2.hpp"
#include "mwTVector3.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
	//! abstract base class for any geometry helper
	/*! provides standard typedefs and helper functions
	*/
	template <typename TBaseGeo,typename TCoordSystem>
	class mwTGeometryHelper
	{
	public:
		typedef TBaseGeo BaseGeo;
		typedef typename BaseGeo::ValueType BaseGeoValueType;
		typedef TCoordSystem CoordSystem;
		typedef typename CoordSystem::PositionVector PositionVector;
		typedef typename CoordSystem::ValueType CSValueType;
	//#############################################################################
		typedef CSValueType Vector1d;
		typedef typename mathdef::mwTVector2<CSValueType> Vector2d;
		typedef typename mathdef::mwTVector3<CSValueType> Vector3d;
	//#############################################################################
	private:
		//! Constructor - not allowed since it's a static class
		mwTGeometryHelper();
//#############################################################################
	};
}
#endif	//	MW_MWTGEOMETRYHELPER_HPP_
