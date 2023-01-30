// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTGeometry3d class

#ifndef MW_MWTGEOMETRY3D_HPP_
#define MW_MWTGEOMETRY3D_HPP_
//#############################################################################
#include "mwTGeometry.hpp"
#include "mwTBaseGeometry3d.hpp"
//#############################################################################
namespace geoDef
{
//=========== Templates declarations.=============
	template <typename T, typename TCoordSystem>	class mwTGeometry3d;
	template <typename T, typename TCoordSystem>	class mwTBox;
	template <typename T, typename TCoordSystem>	class mwTCone;
	template <typename T, typename TCoordSystem>	class mwTCylinder;
	template <typename T, typename TCoordSystem>	class mwTHelix;
	template <typename T, typename TCoordSystem>	class mwTSphere;
	template <typename T, typename TCoordSystem>	class mwTTorus;

	//! Visitor pattern for setting a geometry
	template <typename T,typename TCoordSystem>
	class mwTGeoSetter3dIntf
	{
	private:
		typedef mwTGeoSetter3dIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(mwTGeometry3d<ValueType,CoordSystem>	&tv) const =0;
		virtual void Visit(mwTBox<ValueType,CoordSystem>		&tv) const =0;
		virtual void Visit(mwTCone<ValueType,CoordSystem>		&tv) const =0;
		virtual void Visit(mwTCylinder<ValueType,CoordSystem>	&tv) const =0;
		virtual void Visit(mwTHelix<ValueType,CoordSystem>		&tv) const =0;
		virtual void Visit(mwTSphere<ValueType,CoordSystem>		&tv) const =0;
		virtual void Visit(mwTTorus<ValueType,CoordSystem>		&tv) const =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoSetter3dIntf(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Visitor pattern for getting data from a coordinate system
	template <typename T,typename TCoordSystem>
	class mwTGeoGetter3dIntf
	{
	private:
		typedef mwTGeoGetter3dIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(const mwTGeometry3d<ValueType,CoordSystem>	&tv) =0;
		virtual void Visit(const mwTBox<ValueType,CoordSystem>			&tv) =0;
		virtual void Visit(const mwTCone<ValueType,CoordSystem>			&tv) =0;
		virtual void Visit(const mwTCylinder<ValueType,CoordSystem>		&tv) =0;
		virtual void Visit(const mwTHelix<ValueType,CoordSystem>		&tv) =0;
		virtual void Visit(const mwTSphere<ValueType,CoordSystem>		&tv) =0;
		virtual void Visit(const mwTTorus<ValueType,CoordSystem>		&tv) =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoGetter3dIntf(){};
		//#############################################################################
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};

//#############################################################################
	//! abstract base class for any Geometry3d
#pragma warning(push)
#pragma warning(disable:4251)
	template <class T, class TCoordSystem>
		class MW_5AXUTIL_API mwTGeometry3d : public mwTGeometry<T,TCoordSystem>
	{
	public:
		typedef typename mwTGeometry<T,TCoordSystem>::BaseGeoValueType BaseGeoValueType;
		typedef mwTBaseGeometry3d<T>				BaseGeo;
		typedef TCoordSystem CoordSystem;
		typedef typename mwTGeometry<T,TCoordSystem>::CSValueType CSValueType;
	private:
		typedef mwTGeometry3d<T,CoordSystem>						MySelf;
	public:
		typedef typename misc::mwAutoPointer< MySelf >						Ptr;
		typedef mwTGeoGetter3dIntf <BaseGeoValueType,CoordSystem>	GeoGetter3d;
		typedef mwTGeoSetter3dIntf <BaseGeoValueType,CoordSystem>	GeoSetter3d;
		typedef typename mwTGeometry<T,TCoordSystem>::GeoSetter		GeoSetter;
		typedef typename mwTGeometry<T,TCoordSystem>::GeoGetter		GeoGetter;
		typedef typename mwTGeometry<T,TCoordSystem>::ViewPtr	ViewPtr;
	//#############################################################################
		//! gets base Geometry3d
		/*! 			
				\returns the base Geometry3d
		*/
		virtual const BaseGeo& GetBaseGeometry3d() const=0;
	//#############################################################################
		//! gets base Geometry
		/*! 			
				\returns the base Geometry
		*/
		virtual const typename mwTGeometry<T,TCoordSystem>::BaseGeo& GetBaseGeometry() const
			{return GetBaseGeometry3d();};
	//#############################################################################
		//! implements visitor pattern for setting data in the current geometry
		/*! 
				\param setter the visitor to setting data in the current CS
		*/	
		virtual void AcceptVisitor( const GeoSetter& setter )
		{
			setter.Visit(*this);
		}
	//#############################################################################
		//! implements visitor pattern for getting data from the current geometry
		/*! 
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter& getter )const
		{
			getter.Visit(*this);
		}
	//#############################################################################
		//! implements visitor pattern for setting data in the current geometry
		/*! 
				\param setter the visitor to setting data in the current CS
		*/	
		virtual void AcceptVisitor( const GeoSetter3d& setter )=0;
	//#############################################################################
		//! implements visitor pattern for getting data from the current geometry
		/*! 
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter3d& getter )const=0;
	//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeometry3d(){};
	protected:
	//#############################################################################
		//! helper constructor for derived classes
		/*! 
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		inline mwTGeometry3d(const CoordSystem &cs, const ViewPtr& view=ViewPtr())
			:mwTGeometry<BaseGeoValueType,CoordSystem>(cs,view)
		{};
	protected:
	//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf& ){return *this;};
		mwTGeometry3d(const mwTGeometry3d& other): 
			mwTGeometry<BaseGeoValueType, CoordSystem>(other) {}
	};
#pragma warning(pop)
//#############################################################################
	typedef mwTGeometry3d<float,CS3df > Geo3dfIn3df;
	typedef mwTGeometry3d<double,CS3dd > Geo3ddIn3dd;
}
#endif	//	MW_MWTGEOMETRY3D_HPP_
