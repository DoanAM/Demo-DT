// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTBOX_HPP_
#define MW_MWTBOX_HPP_
//#############################################################################
#include <mwTBoxBase.hpp>
#include <mwTGeometry3d.hpp>
//#############################################################################
namespace geoDef
{
	//! Implements a Box
	/*! The Box is build using the followings conventions:

		- has the gravity center in the origin of SC
	*/

	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTBox
		:public mwTGeometry3d < T, TCoordSystem >
	{
	public:
		typedef typename mwTGeometry3d < T, TCoordSystem >::BaseGeoValueType BaseGeoValueType;
		typedef typename mwTGeometry3d < T, TCoordSystem >::CoordSystem CoordSystem;
		typedef typename mwTGeometry3d < T, TCoordSystem >::ViewPtr ViewPtr;
		typedef typename mwTGeometry3d < T, TCoordSystem >::PositionVector PositionVector;
		typedef typename mwTGeometry3d < T, TCoordSystem >::GeoSetter3d GeoSetter3d;
		typedef typename mwTGeometry3d < T, TCoordSystem >::GeoGetter3d GeoGetter3d;
	private:
		typedef mwTBox<BaseGeoValueType,CoordSystem>			MySelf;
	public:
		typedef mwTBoxBase<BaseGeoValueType>					BaseGeo;
		typedef typename misc::mwAutoPointer< MySelf >					Ptr;
		typedef typename BaseGeo::Corners								Corners;
		typedef typename BaseGeo::Facets								Facets;
		typedef mwTGeometry3d<BaseGeoValueType,CoordSystem>	GeometryType;
//#############################################################################
		//!Constructor
		/*!
				\param base geometry definition
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		mwTBox (const BaseGeo& base,const CoordSystem &cs, const ViewPtr& view=ViewPtr());
//#############################################################################
		//! Gets a corner position
		/*!
			\param corner desired corner position
			\returns the position vector
		*/
		const PositionVector GetVector(const Corners corner) const;
//#############################################################################
		//! Gets the gravity center position of a facet of the box
		/*!
			\param facet the facet of which gravity center is desired
			\returns the position vector
		*/
		const PositionVector GetVector(const Facets facet) const;
//#############################################################################
		//! gets base Box
		/*!
				\returns the base Box
		*/
		inline const BaseGeo& GetBase() const
			{return m_Base;};
//#############################################################################
		//! sets base Box
		/*!
				\prama base the new base Box
		*/
		inline void SetBase(const BaseGeo& base)
			{m_Base=base;};
//#############################################################################
		//! gets base Geometry3d
		/*!
				\returns the base Geometry3d
		*/
		virtual const typename GeometryType::BaseGeo& GetBaseGeometry3d() const
			{return GetBase();};
//#############################################################################
		//! implements visitor pattern for setting data in the current 3d geometry
		/*!
				\param setter the visitor to setting data in the current CS
		*/
		virtual void AcceptVisitor( const GeoSetter3d& setter );
//#############################################################################
		//! implements visitor pattern for getting data from the current 3d geometry
		/*!
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter3d& getter )const;
//#############################################################################
	private:
		BaseGeo m_Base;
	};
	typedef mwTBox<float,CS3df > BoxfIn3df;
	typedef mwTBox<double,CS3dd > BoxdIn3d;
}
#endif	//	MW_MWTBOX_HPP_
