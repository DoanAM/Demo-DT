// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTCIRCLE_HPP_
#define MW_MWTCIRCLE_HPP_
//#############################################################################

#include "mwDllImpExpDef.hpp"
#include <mwTCircleBase.hpp>
#include <mwTGeometry2d.hpp>
//#############################################################################
namespace geoDef
{
	//! Implements a Circle
	/*! The Circle is build using the followings conventions:

		- has the center in the origin of SC
		- angle is CCW

		The Circle is parameterized by X = C + R*(cos(A)*U + sin(A)*V) where
		A is an angle in [-360 +360).

		The Circle is define using vectors u and v (XY plane)
	*/

	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTCircle
		:public mwTGeometry2d < T, TCoordSystem >
	{
	public:
		typedef typename mwTGeometry2d <T, TCoordSystem >::CoordSystem CoordSystem;
		typedef typename mwTGeometry2d <T, TCoordSystem >::BaseGeoValueType BaseGeoValueType;
	private:
		typedef mwTCircle<BaseGeoValueType,CoordSystem>		MySelf;

	public:
		typedef typename mwTGeometry2d <T, TCoordSystem >::PositionVector PositionVector;
		typedef typename mwTGeometry2d <T, TCoordSystem >::ViewPtr ViewPtr;
		typedef mwTCircleBase<BaseGeoValueType>								BaseGeo;
		typedef typename misc::mwAutoPointer< MySelf >					Ptr;
		typedef mwTGeometry2d<BaseGeoValueType,CoordSystem>	GeometryType;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoGetter2d		GeoGetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoSetter2d		GeoSetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::CSValueType CSValueType;
//#############################################################################
		//!Constructor
		/*!
				\param base geometry definition
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		mwTCircle (const BaseGeo& base,const CoordSystem &cs, const ViewPtr& view=ViewPtr());
//#############################################################################
		//! Obtain the Position Vector of a point from the cricle at a specific angle
		/*
			\param angle the angle
			\return the vector of position
		*/
		const PositionVector GetVector(const BaseGeoValueType& angle) const;
//#############################################################################
		//! gets base Circle
		/*!
				\returns the base Circle
		*/
		inline const BaseGeo& GetBase() const
			{return m_Base;};
//#############################################################################
		//! sets base Circle
		/*!
				\prama base the new base Circle
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
	typedef mwTCircle<float,CS2df  > CirclefIn2df;
	typedef mwTCircle<double,CS2dd  > CircledIn2dd;

	typedef mwTCircle<float,CS3df  > CirclefIn3df;
	typedef mwTCircle<double,CS3dd  > CircledIn3dd;
}
#endif	//	MW_MWTCIRCLE_HPP_
