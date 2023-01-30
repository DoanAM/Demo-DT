// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTELLIPSE_HPP_
#define MW_MWTELLIPSE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include <mwTEllipseBase.hpp>
#include <mwTGeometry2d.hpp>
//#############################################################################
namespace geoDef
{
	//! Implements a Ellipse
	/*! The Ellipse is build using the followings conventions:
		- has the gravity center in the origin of SC
		- is defined on the xy plane with the center in the origin
	*/
	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTEllipse
		:public mwTGeometry2d < T, TCoordSystem >
	{
	public:
		typedef typename mwTGeometry2d <T, TCoordSystem >::CoordSystem CoordSystem;
		typedef typename mwTGeometry2d <T, TCoordSystem >::BaseGeoValueType BaseGeoValueType;
	private:
		typedef mwTEllipse<BaseGeoValueType,CoordSystem>		MySelf;
	public:
		typedef mwTEllipseBase<BaseGeoValueType>								BaseGeo;
		typedef typename misc::mwAutoPointer< MySelf >					Ptr;
		typedef mwTGeometry2d<BaseGeoValueType,CoordSystem>	GeometryType;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoGetter2d		GeoGetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::GeoSetter2d		GeoSetter2d;
		typedef typename mwTGeometry2d <T, TCoordSystem >::PositionVector PositionVector;
		typedef typename mwTGeometry2d <T, TCoordSystem >::ViewPtr ViewPtr;
		typedef typename mwTGeometry2d <T, TCoordSystem >::CSValueType CSValueType;
//#############################################################################
		//!Constructor
		/*!
				\param base geometry definition
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		mwTEllipse (const BaseGeo& base,const CoordSystem &cs, const ViewPtr& view=ViewPtr());
//#############################################################################
		//! Obtain the Position Vector of a point from the ellipse at a specific angle
		/*
			\param angle the angle
			\return the vector of position
		*/
		const PositionVector GetVector(const BaseGeoValueType& angle) const;
//#############################################################################
		//! gets base Ellipse
		/*!
				\returns the base Ellipse
		*/
		inline const BaseGeo& GetBase() const
			{return m_Base;};
//#############################################################################
		//! sets base Ellipse
		/*!
				\prama base the new base Ellipse
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
	typedef mwTEllipse<float,CS2df  > EllipsefIn2df;
	typedef mwTEllipse<double,CS2dd  > EllipsedIn2dd;

	typedef mwTEllipse<float,CS3df  > EllipsefIn3df;
	typedef mwTEllipse<double,CS3dd  > EllipsedIn3dd;
}
#endif	//	MW_MWTELLIPSE_HPP_
