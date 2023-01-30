// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTARCCIRCLE_HPP_
#define MW_MWTARCCIRCLE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTGeometry2d.hpp>
#include <mwTArcCircleBase.hpp>
//#############################################################################
namespace geoDef
{
	//! Implements a Arc
	/*! The Arc is build using the followings conventions:

		- has the center in the origin of SC
		- angle is CCW

		The Arc is parameterized by X = C + R*(cos(A)*i + sin(A)*j) where
		A is an angle in [0,2MW_PI).

		The Arc is define using vectors i and j (XY plane)
	*/
	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTArcCircle
		:public mwTGeometry2d <T, TCoordSystem >
	{
	public:
		typedef typename mwTGeometry2d <T, TCoordSystem >::BaseGeoValueType BaseGeoValueType;
		typedef typename mwTGeometry2d <T, TCoordSystem >::CoordSystem CoordSystem;
		typedef typename mwTGeometry2d <T, TCoordSystem >::ViewPtr ViewPtr;
		typedef typename mwTGeometry2d <T, TCoordSystem >::PositionVector PositionVector;

	private:
		typedef mwTArcCircle<BaseGeoValueType,CoordSystem>			MySelf;
	public:
		typedef mwTArcCircleBase<BaseGeoValueType>					BaseGeo;
		typedef typename BaseGeo::Corners								Corners;
		typedef typename misc::mwAutoPointer< MySelf >					Ptr;
		typedef mwTGeometry2d<BaseGeoValueType,CoordSystem>	GeometryType;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoGetter2d		GeoGetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoSetter2d		GeoSetter2d;

//#############################################################################
		//!Constructor
		/*!
				\param base geometry definition
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		mwTArcCircle (const BaseGeo& base,const CoordSystem &cs, const ViewPtr& view=ViewPtr());
//#############################################################################
		//! Obtain the Position Vector of a point from the arc at a specific angle
		/*
				\param angle the angle
				\return the vector of position
		*/
		const PositionVector GetVector(const BaseGeoValueType& angle) const;
//#############################################################################
		//! Obtain the Position Vector of a point from the arc at a specific corner
		/*
				\param corner the corner
				\return the vector of position
		*/
		const PositionVector GetVector(const Corners& corner) const;
//#############################################################################
		//! Obtain the length of the arc for a specific sweep angle
		/*
				\param angle the angle
				\return length of the arc
		*/
		const BaseGeoValueType GetLength(const BaseGeoValueType& angle) const;
//#############################################################################
		//! gets base Arc
		/*!
				\returns the base Arc
		*/
		inline const BaseGeo& GetBase() const
			{return m_Base;};
//#############################################################################
		//! sets base Arc
		/*!
				\prama base the new base Arc
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
	typedef mwTArcCircle<float, CS2df  > ArcCirclefIn2df;
	typedef mwTArcCircle<double, CS2dd  > ArcCircledIn2dd;

	typedef mwTArcCircle<float, CS3df  > ArcCirclefIn3df;
	typedef mwTArcCircle<double, CS3dd  > ArcCircledIn3dd;
}
#endif	//	MW_MWTARCCIRCLE_HPP_
