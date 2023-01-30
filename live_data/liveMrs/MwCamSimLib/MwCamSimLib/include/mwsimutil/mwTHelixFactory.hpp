// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTHELIXFACTORY_HPP_
#define MW_MWTHELIXFACTORY_HPP_
#include <mwTHelix.hpp>
#include "mwTGeoFactory.hpp"
#include "mwTArcCircle.hpp"
#include "mwTCoordSystem3d.hpp"
#include "mwTiCoordSystem3d.hpp"
#include "mwTijCoordSystem3d.hpp"
#include "mwTijkCoordSystem3d.hpp"
namespace geoDef
{
	//! allows you different modes of creation of a Helix
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTHelixFactory : public mwTGeoFactory < mwTHelix<T,TCoordSystem> >
	{
	public:
		typedef typename mwTGeoFactory < mwTHelix<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTHelix<T,TCoordSystem> >::CoordSystem CoordSystem;
		typedef typename mwTGeoFactory < mwTHelix<T,TCoordSystem> >::ViewPtr ViewPtr;
		typedef typename mwTGeoFactory < mwTHelix<T,TCoordSystem> >::Geo Geo;
		typedef typename mwTGeoFactory < mwTHelix<T,TCoordSystem> >::PositionVector PositionVector;
		typedef mwTArcCircle<T,TCoordSystem>	ArcCircle;
//#############################################################################	
		//!Create a helix from a helix base and Coordinate system
		/*!
			\param base the helix definition
			\param corner specify in which corner of the geo the CS is located
			\param cs the system of coordinate in which the box is created
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const BaseGeo& base,
								const CoordSystem &cs,
								const ViewPtr& view=ViewPtr());
//#############################################################################
		static const Geo Create(const ArcCircle &arcCircle,
								const T helixStep,
								const ViewPtr& view=ViewPtr());
//#############################################################################
	private:
		//! Constructor - not allowed since it's a static class
		mwTHelixFactory();
	};
	typedef mwTHelixFactory<float,CS3df > HelixfIn3dfFactory;
	typedef mwTHelixFactory<double,CS3dd > HelixdIn3ddFactory;
}
#endif	//	MW_MWTHELIXFACTORY_HPP_
