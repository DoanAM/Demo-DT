// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTArcCircleFactory class

#ifndef MW_MWTARCCIRCLEFACTORY_HPP_
#define MW_MWTARCCIRCLEFACTORY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTArcCircle.hpp>
#include "mwTGeoFactory.hpp"
//#############################################################################
namespace geoDef
{
	//! allows you different modes of creation of a ArcCircle
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTArcCircleFactory : public mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >
	{
	public:
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::Geo Geo;
		typedef typename BaseGeo::Corners			Corners;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::PositionVector		PositionVector;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::ViewPtr				ViewPtr;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::CoordSystem				CoordSystem;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::CoordSystem3d				CoordSystem3d;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::BaseGeoValueType				BaseGeoValueType;
		typedef typename mwTGeoFactory < mwTArcCircle<T,TCoordSystem> >::CSValueType				CSValueType;

//#############################################################################	
		//!Create an ArcCircle from 3 position vectors
		/*!The CS is having only the origin, the i vector and j vector defined
			\param startPoint position vector of the arc start point
			\param inPoint position vector of any point from arc between start and end
			\param endPoint position vector of the arc end point 
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const PositionVector& startPoint,
								const PositionVector& inPoint,
								const PositionVector& endPoint,
								const ViewPtr& view=ViewPtr());
//#############################################################################
		static const Geo Create(const PositionVector &startPoint,
								const PositionVector &endPoint,
								const PositionVector &normalToPlane,
								const T signedBulgeFactor,
								const ViewPtr& view=ViewPtr());
//#############################################################################
		//!Create an ArcCircle from 3 position vectors
		/*!NOTE: this function is deprecated, please use second function without radius parameter.
		If a radius is not equal with distance from start to center then this function will throw an exception.
		The CS is having only the origin, the i vector and j vector defined
			\param startPoint position vector of the arc start point
			\param endPoint position vector of the arc end point 
			\param centerPoint position vector is the center of the arc/helix (in case of helix must be projected on [startPoint, normal plane])
			\param normalToPlane is normal vector to arc/helix
			\param radius defines radius of the arc/helix (can be computed from startPoint and center, is better to be provided from tolerance reasons)
			\param numberOfTurns set the number of rotations. The default value of numberOfTurns parameter is 1. In the general case the arc/helix ends after reaching the end point (TURN - 1) times i.e.
			\360 * (TURN - 1) degrees are added to the arc/helix respective to the default case.
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const PositionVector &startPoint,
								const PositionVector &endPoint,
								const PositionVector &centerPoint,
								const PositionVector &normalToPlane,
								const T radius,
								const unsigned int numberOfTurns = 1,
								const ViewPtr& view=ViewPtr());
		//#############################################################################
		//!Create an ArcCircle from 3 position vectors
		/*!Radius is computed base on distance from start to center.
		The CS is having only the origin, the i vector and j vector defined
			\param startPoint position vector of the arc start point
			\param endPoint position vector of the arc end point
			\param centerPoint position vector is the center of the arc/helix (in case of helix must be projected on [startPoint, normal plane])
			\param normalToPlane is normal vector to arc/helix
			\param numberOfTurns set the number of rotations. The default value of numberOfTurns parameter is 1. In the general case the arc/helix ends after reaching the end point (TURN - 1) times i.e.
			\360 * (TURN - 1) degrees are added to the arc/helix respective to the default case.
			\param view the view to which the cs is relative to
			MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(
			const PositionVector &startPoint,
			const PositionVector &endPoint,
			const PositionVector &centerPoint,
			const PositionVector &normalToPlane,
			const unsigned int numberOfTurns = 1,
			const ViewPtr& view = ViewPtr());
		//#############################################################################
		//!Create a ArcCircle from a ArcCircle base and CS of a corner of the Arc
		/*!
		\param base the ArcCircle definition
		\param corner specify in which corner of the geo the CS is located
		\param cs the system of coordinate in which the ArcCircle is created
		\param view the view to which the cs is relative to
		MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const BaseGeo& base,
								const Corners corner,
								const CoordSystem &cs,
								const ViewPtr& view=ViewPtr());
//#############################################################################	
		//!Create a ArcCircle from a ArcCircle base which have the CS in the center of the arc
		/*!
		\param base the ArcCircle definition
		\param cs the system of coordinate in which the ArcCircle is created
		\param view the view to which the cs is relative to
		MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const BaseGeo& base,
								const CoordSystem &cs,
								const ViewPtr& view=ViewPtr());
//#############################################################################
		static const typename CoordSystem::BaseCSPtr GetArcCS(const PositionVector& relStartVector,
			const PositionVector& relInVector,
			const PositionVector& relEndVector,
			const PositionVector& center,
			const T sweepAngle);
//#############################################################################
		//! gets the center of circle defined by 3 position vectors
		/*!if the points are not defining a circle an exception is thrown
				\param firstPoint position vector of a point from circle
				\param secondPoint position vector of a point from circle
				\param thirdPoint position vector of a point from circle
				\returns the center
		*/
		static const PositionVector GetCenter(
			const PositionVector& firstPoint,
			const PositionVector& secondPoint,
			const PositionVector& thirdPoint);
	private:
//#############################################################################
		//! Constructor - not allowed since it's a static class
		mwTArcCircleFactory();
	};
	typedef mwTArcCircleFactory<float,CS2df > ArcCirclefIn2dfFactory;
	typedef mwTArcCircleFactory<double,CS2dd > ArcCircledIn2ddFactory;
	
	typedef mwTArcCircleFactory<float,CS3df > ArcCirclefIn3dfFactory;
	typedef mwTArcCircleFactory<double,CS3dd > ArcCircledIn3ddFactory;
}
#endif	//	MW_MWTARCCIRCLEFACTORY_HPP_
