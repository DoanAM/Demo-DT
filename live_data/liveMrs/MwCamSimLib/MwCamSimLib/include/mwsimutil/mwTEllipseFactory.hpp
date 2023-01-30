// (C) 2003-2010 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTEllipseFactory class

#ifndef MW_MWTELLIPSEFACTORY_HPP_
#define MW_MWTELLIPSEFACTORY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTEllipse.hpp>
#include "mwTGeoFactory.hpp"
//#############################################################################
namespace geoDef
{
	//! allows you different modes of creation of a Ellipse
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTEllipseFactory : public mwTGeoFactory < mwTEllipse<T,TCoordSystem> >
	{
	public:
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::Geo Geo;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::PositionVector		PositionVector;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::PositionVector3d		PositionVector3d;

		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::ViewPtr				ViewPtr;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::CoordSystem				CoordSystem;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::CoordSystem3d				CoordSystem3d;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::BaseGeoValueType				BaseGeoValueType;
		typedef typename mwTGeoFactory < mwTEllipse<T,TCoordSystem> >::CSValueType				CSValueType;


		typedef mwTEllipse<BaseGeoValueType, CoordSystem3d >	GeoIn3d;
		typedef typename GeoIn3d::ViewPtr								View3dPtr;
//#############################################################################	
		//!Create an Ellipse from center, majorRadius,minorMajorRation,normal
		/*!The CS is having only the origin, the i vector and j vector defined
			\param center position vector of the ellipse center
			\param majorRadius vector of ellipse major radius
			\param minorMajorRatio equal with minorRadius/majorRadius
			\param normal the normal of the  ellipse plane
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const GeoIn3d Create(const PositionVector3d&	center,
									const PositionVector3d&	majorRadius,
									const CSValueType&		minorMajorRatio,
									const PositionVector3d&	normal,
									const View3dPtr& view=ViewPtr());
//#############################################################################
	private:
//#############################################################################
		//! Constructor - not allowed since it's a static class
		mwTEllipseFactory();
	};
	typedef mwTEllipseFactory<float,CS2df > EllipsefIn2dfFactory;
	typedef mwTEllipseFactory<double,CS2dd > EllipsedIn2ddFactory;
	
	typedef mwTEllipseFactory<float,CS3df > EllipsefIn3dfFactory;
	typedef mwTEllipseFactory<double,CS3dd > EllipsedIn3ddFactory;
};
#endif	//	MW_MWTELLIPSEFACTORY_HPP_
