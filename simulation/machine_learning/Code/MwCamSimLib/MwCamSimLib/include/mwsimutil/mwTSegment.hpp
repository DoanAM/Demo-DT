// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTSEGMENT_HPP_
#define MW_MWTSEGMENT_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTSegmentBase.hpp>
#include <mwTGeometry2d.hpp>
//#############################################################################


namespace geoDef
{
	//! Implements a Segment
	/*! The Segment is build using the followings conventions:
		- origin of SC is in the middle of the segment
		- first and second corner are along OX axis (u vector)
	*/
	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTSegment
		:public mwTGeometry2d < T, TCoordSystem >
	{
	public:
		typedef typename mwTGeometry2d <T, TCoordSystem >::CoordSystem CoordSystem;
		typedef typename mwTGeometry2d <T, TCoordSystem >::BaseGeoValueType BaseGeoValueType;

	private:
		typedef mwTSegment<BaseGeoValueType,CoordSystem>		MySelf;
	public:
		typedef mwTSegmentBase<BaseGeoValueType>				BaseGeo;
		typedef typename misc::mwAutoPointer< MySelf >					Ptr;
		typedef typename BaseGeo::Corners								Corners;
		typedef mwTGeometry2d<BaseGeoValueType,CoordSystem>	GeometryType;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoGetter2d		GeoGetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoSetter2d		GeoSetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::PositionVector PositionVector;
		typedef typename mwTGeometry2d <T, TCoordSystem >::ViewPtr ViewPtr;

//#############################################################################
		//!Constructor
		/*!
				\param base geometry definition
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		mwTSegment (const BaseGeo& base,const CoordSystem &cs, const ViewPtr& view=ViewPtr());
//#############################################################################
		//! Gets a corner position
		/*!
			\param corner desired corner position
			\returns the position vector
		*/
		const PositionVector GetVector(const Corners corner) const;
//#############################################################################
		//! gets base Segment
		/*!
				\returns the base Segment
		*/
		inline const BaseGeo& GetBase() const
			{return m_Base;};
//#############################################################################
		//! sets base Segment
		/*!
				\prama base the new base Segment
		*/
		inline void SetBase(const BaseGeo& base)
			{m_Base=base;};
//#############################################################################
		//! gets base Geometry2d
		/*!
				\returns the base Geometry2d
		*/
		virtual const typename GeometryType::BaseGeo& GetBaseGeometry2d() const
			{return GetBase();};
//#############################################################################
		//! implements visitor pattern for setting data in the current 2d geometry
		/*!
				\param setter the visitor to setting data in the current CS
		*/
		virtual void AcceptVisitor( const GeoSetter2d& setter );
//#############################################################################
		//! implements visitor pattern for getting data from the current 2d geometry
		/*!
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter2d& getter )const;
//#############################################################################
	private:
		BaseGeo m_Base;
	};
	typedef mwTSegment<float,CS2df  > SegmentfIn2df;
	typedef mwTSegment<double,CS2dd  > SegmentdIn2dd;

	typedef mwTSegment<float,CS3df > SegmentfIn3df;
	typedef mwTSegment<double,CS3dd  > SegmentdIn3dd;
}
#endif	//	MW_MWTSEGMENT_HPP_
