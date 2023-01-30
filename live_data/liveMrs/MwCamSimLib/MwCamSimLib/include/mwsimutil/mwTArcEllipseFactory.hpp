// (C) 2003-2010 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTArcEllipseFactory class

#ifndef MW_MWTARCELLIPSEFACTORY_HPP_
#define MW_MWTARCELLIPSEFACTORY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTArcEllipse.hpp>
#include "mwTGeoFactory.hpp"
//#############################################################################
namespace geoDef
{
	//! allows you different modes of creation of a ArcEllipse
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTArcEllipseFactory : public mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >
	{
	public:
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::Geo Geo;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::PositionVector		PositionVector;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::ViewPtr				ViewPtr;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::CoordSystem				CoordSystem;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::BaseGeoValueType				BaseGeoValueType;
		typedef typename mwTGeoFactory < mwTArcEllipse<T,TCoordSystem> >::CSValueType				CSValueType;

		enum angleTypes
		{
			RELATIVE_TO_ELLIPSE=1,
			RELATIVE_TO_THE_CIRCLE_FROM_WHICH_ELLIPSE_WAS_CREATED_THROUGH_DEFORMATION=2
		};
//#############################################################################	
		//!Create an ellipse arc from center, majorRadius,minorRadius,startAngle and sweepAngle
		/*!The CS is having only the origin, the i vector and j vector defined
			\param center position vector of the ellipse arc center
			\param majorRadius vector of ellipse arc major radius
			\param minorRadius vector of ellipse arc minor radius
			\param startAngle start angle of the ellipse arc
			\param sweepAngle sweep angle of the ellipse arc
			\param angleType some systems are storring angles in the values relative
					to the circle from which the ellipse was created through deformation(by pressing it).
					For example if in the original circle a point was coresponding to an angle of 45 degrees,
					when the circle is pressed to create the ellipse the point will correspond to an angle, lower
					then 45 degrees. The parameter is specifying if the specifyed angles are in circle coordinates or not.
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const PositionVector&	center,
								const PositionVector&	majorRadius,
								const PositionVector&	minorRadius,
								const BaseGeoValueType& startAngle,
								const BaseGeoValueType& sweepAngle,
								const angleTypes		angleType=RELATIVE_TO_ELLIPSE,
								const ViewPtr& view=ViewPtr());

//#############################################################################
	private:
//#############################################################################
		//! Constructor - not allowed since it's a static class
		mwTArcEllipseFactory();
//#############################################################################
		//! converts circle angle to ellipse angle
		/*! converts an angle relative to the circle from which the ellipse is created to an angle relative to ellipse
			\param angle the angle to conver
			\param majorRadiusLength length of ellipse arc major radius
			\param minorRadiusLength length of ellipse arc minor radius
			\returns converted angle
		*/
		static const BaseGeoValueType CircleAngleToEllipseAngle(
			const BaseGeoValueType angle,
			const BaseGeoValueType majorRadiusLength,
			const BaseGeoValueType minorRadiusLength
			);

	};
	typedef mwTArcEllipseFactory<float,CS2df > ArcEllipsefIn2dfFactory;
	typedef mwTArcEllipseFactory<double,CS2dd > ArcEllipsedIn2ddFactory;
	
	typedef mwTArcEllipseFactory<float,CS3df > ArcEllipsefIn3dfFactory;
	typedef mwTArcEllipseFactory<double,CS3dd > ArcEllipsedIn3ddFactory;
};
#endif	//	MW_MWTARCELLIPSEFACTORY_HPP_
