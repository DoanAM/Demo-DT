// (C) 2003-2010 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTCircleFactory class

#ifndef MW_MWTCIRCLEFACTORY_HPP_
#define MW_MWTCIRCLEFACTORY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTCircle.hpp>
#include "mwTGeoFactory.hpp"
//#############################################################################
namespace geoDef
{
	//! allows you different modes of creation of a Circle
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTCircleFactory : public mwTGeoFactory < mwTCircle<T,TCoordSystem> >
	{
	public:

		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::Geo Geo;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::PositionVector		PositionVector;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::PositionVector3d		PositionVector3d;

		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::CoordSystem				CoordSystem;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::BaseGeoValueType				BaseGeoValueType;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::CSValueType				CSValueType;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::CoordSystem3d CoordSystem3d;
		typedef mwTCircle<BaseGeoValueType, CoordSystem3d >	GeoIn3d;	
		typedef typename GeoIn3d::ViewPtr								View3dPtr;
		typedef typename mwTGeoFactory < mwTCircle<T,TCoordSystem> >::ViewPtr	ViewPtr;
//#############################################################################	
		//!Creates an Circle from 3 position vectors
		/*!The generated CS is having only the origin, the i vector and j vector defined.
			i is between center and first point,
			j is such as first, second and third points to be in counter clockwise order.
			\param firstPoint position vector of first point from circle
			\param secondPoint position vector of second point from circle
			\param thirdPoint position vector of third point from circle
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const PositionVector& firstPoint,
								const PositionVector& secondPoint,
								const PositionVector& thirdPoint,
								const ViewPtr& view=ViewPtr());
//#############################################################################	
		//!Creates an Circle in 3d from center,radius and normal of the  circle plane
		/*!The CS is having only the origin, the i vector and j vector defined.
			i and j are generated based on Gram-Schmidt orthonormalization,
			\param center the center of the circle
			\param radius the radius of the circle
			\param normal the normal of the  circle plane
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const GeoIn3d Create(const PositionVector3d& center,
								const BaseGeoValueType& radius,
								const PositionVector3d& normal,
								const View3dPtr& view=View3dPtr());
//#############################################################################
	private:
		//! Constructor - not allowed since it's a static class
		mwTCircleFactory();
	};
	typedef mwTCircleFactory<float,CS2df > CirclefIn2dfFactory;
	typedef mwTCircleFactory<double,CS2dd > CircledIn2ddFactory;
	
	typedef mwTCircleFactory<float,CS3df > CirclefIn3dfFactory;
	typedef mwTCircleFactory<double,CS3dd > CircledIn3ddFactory;
};
#endif	//	MW_MWTCIRCLEFACTORY_HPP_
