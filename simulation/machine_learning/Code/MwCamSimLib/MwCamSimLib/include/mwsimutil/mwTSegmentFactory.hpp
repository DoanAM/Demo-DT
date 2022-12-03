// (C) 2003-2010 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTSegmentFactory class

#ifndef MW_MWTSEGMENTFACTORY_HPP_
#define MW_MWTSEGMENTFACTORY_HPP_
#include "mwDllImpExpDef.hpp"
#include <mwTSegment.hpp>
#include "mwTGeoFactory.hpp"

namespace geoDef
{
	//! allows you different modes of creation of a Segment
	template <class T,class TCoordSystem>
		class MW_5AXUTIL_API mwTSegmentFactory : public mwTGeoFactory < mwTSegment<T,TCoordSystem> >
	{
	public:
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::BaseGeo BaseGeo;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::Geo Geo;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::PositionVector		PositionVector;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::PositionVector3d		PositionVector3d;

		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::ViewPtr				ViewPtr;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::CoordSystem				CoordSystem;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::CoordSystem3d				CoordSystem3d;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::BaseGeoValueType				BaseGeoValueType;
		typedef typename mwTGeoFactory < mwTSegment<T,TCoordSystem> >::CSValueType				CSValueType;

		typedef typename BaseGeo::Corners Corners;
//#############################################################################	
		//!Create a Segment from 2 position vectors
		/*!The CS is having only an origin and the i vector defined
			\param startPoint position vector of the start point
			\param endPoint position vector of the end point
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const PositionVector& startPoint,
								const PositionVector& endPoint,
								const ViewPtr& view=ViewPtr());
//#############################################################################	
		//!Create a Segment from a Segment base and CS of a corner of the Segment
		/*!
			\param base the Segment definition
			\param corner specify in which corner of the geo the CS is located
			\param cs the system of coordinate in which the Segment is created
			\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		static const Geo Create(const BaseGeo& base,
								const Corners corner,
								const CoordSystem &cs,
								const ViewPtr& view=ViewPtr());
//#############################################################################
	private:
		//! Constructor - not allowed since it's a static class
		mwTSegmentFactory();
	};
	typedef mwTSegmentFactory<float,CS2df > SegmentfIn2dfFactory;
	typedef mwTSegmentFactory<double,CS2dd > SegmentdIn2ddFactory;
	
	typedef mwTSegmentFactory<float,CS3df > SegmentfIn3dfFactory;
	typedef mwTSegmentFactory<double,CS3dd > SegmentdIn3ddFactory;
};
#endif	//	MW_MWTSEGMENTFACTORY_HPP_
