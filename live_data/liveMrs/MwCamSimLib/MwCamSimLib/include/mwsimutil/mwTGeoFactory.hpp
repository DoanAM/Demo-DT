// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTGeoFactory class

#ifndef MW_MWTGEOFACTORY_HPP_
#define MW_MWTGEOFACTORY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTCSTranslator.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
	//! abstract base class for any geometry factory
	/*! provides standard typedefs and helper functions
	*/
	template <typename TGeo>
	class MW_5AXUTIL_API mwTGeoFactory
	{
	public:
		typedef TGeo						Geo;
		typedef typename Geo::ViewPtr									ViewPtr;
		typedef typename Geo::BaseGeo									BaseGeo;
		typedef typename Geo::BaseGeoValueType							BaseGeoValueType;
		typedef typename Geo::CoordSystem								CoordSystem;
		typedef typename CoordSystem::PositionVector					PositionVector;
		typedef typename CoordSystem::ValueType							CSValueType;
		//
		typedef mwTAbstractCoordSystem3d<CSValueType>		CoordSystem3d;
		typedef typename CoordSystem3d::PositionVector					PositionVector3d;
		//
		typedef mwTAbstractCoordSystem2d<CSValueType>	CoordSystem2d;
		typedef typename CoordSystem2d::PositionVector					PositionVector2d;
	protected:
	//#############################################################################
		//! creates a geo having the coordinates system origin translated with (offset)
		/*! 
				\param base geometry definition
				\param cs coordinate system to be used
				\param offset the vector to be used in translation of CS origin
				\param view the view to which the cs is relative to
				\returns the created Geo
		*/
		static const Geo CreateTranslatedGeo (const BaseGeo& base,
									   const CoordSystem &cs,
									   const PositionVector& offset,
									   const ViewPtr& view)
		{
			typename CoordSystem::BaseCSPtr newCS=cs.Clone();
			mwTCSTranslator<CSValueType>::Transform(*newCS,offset);
			return Geo(base,*newCS,view);
		}
	//#############################################################################
		//! creates a geo from a custom CS and a virtualCustomOrigin
		/*! creates a geo having the coordinates system origin translated with 
				(origin-virtualCustomOrigin)
				\param base geometry definition
				\param customCS coordinate system to be used
				\param virtualCustomOrigin the the virtual origin for CS origin
				\param view the view to which the cs is relative to
				\returns the created Geo
		*/
		static const Geo CreateUsingVirtualOrigin (const BaseGeo& base,
											 const CoordSystem &customCS,
											 const PositionVector& virtualCustomOrigin,
											 const ViewPtr& view)
		{
			return CreateTranslatedGeo(base,
									   customCS,
									   customCS.GetOrigin()-virtualCustomOrigin,
									   view);
		}
	//#############################################################################
	private:
		//! Constructor - not allowed since it's a static class
		mwTGeoFactory();
	};
}
#endif	//	MW_MWTGEOFACTORY_HPP_
