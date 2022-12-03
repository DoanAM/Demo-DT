// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTGeometry2d class

#ifndef MW_MWTGEOMETRY2D_HPP_
#define MW_MWTGEOMETRY2D_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTGeometry.hpp"
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
//=========== Templates declarations.=============
	template <typename T, typename TCoordSystem>	class mwTGeometry2d;
	template <typename T, typename TCoordSystem>	class mwTArcCircle;
	template <typename T, typename TCoordSystem>	class mwTArcEllipse;
	template <typename T, typename TCoordSystem>	class mwTCircle;
	template <typename T, typename TCoordSystem>	class mwTEllipse;
	template <typename T, typename TCoordSystem>	class mwTRectangle;
	template <typename T, typename TCoordSystem>	class mwTSegment;
	template <typename T, typename TCoordSystem>	class mwTTriangle;

	//! Visitor pattern for setting a geometry
	template <typename T,typename TCoordSystem>
	class mwTGeoSetter2dIntf
	{
	private:
		typedef mwTGeoSetter2dIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(mwTGeometry2d<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTArcCircle<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTArcEllipse<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTCircle<ValueType,CoordSystem>		& tv) const =0;
		virtual void Visit(mwTEllipse<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTRectangle<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTSegment<ValueType,CoordSystem>	& tv) const =0;
		virtual void Visit(mwTTriangle<ValueType,CoordSystem>	& tv) const =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoSetter2dIntf(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Visitor pattern for getting data from a coordinate system
	template <typename T,typename TCoordSystem>
	class mwTGeoGetter2dIntf
	{
	private:
		typedef mwTGeoGetter2dIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(const mwTGeometry2d<ValueType,CoordSystem>	& tv) =0;
		virtual void Visit(const mwTArcCircle<ValueType,CoordSystem>	& tv) =0;
		virtual void Visit(const mwTArcEllipse<ValueType,CoordSystem>	& tv) =0;
		virtual void Visit(const mwTCircle<ValueType,CoordSystem>		& tv) =0;
		virtual void Visit(const mwTEllipse<ValueType,CoordSystem>		& tv) =0;
		virtual void Visit(const mwTRectangle<ValueType,CoordSystem>	& tv) =0;
		virtual void Visit(const mwTSegment<ValueType,CoordSystem>		& tv) =0;
		virtual void Visit(const mwTTriangle<ValueType,CoordSystem>		& tv) =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoGetter2dIntf(){};
		//#############################################################################
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
//#############################################################################
	//! abstract base class for any Geometry2d
#pragma warning(push)
#pragma warning(disable:4251)
	template <typename T, typename TCoordSystem>
		class MW_5AXUTIL_API mwTGeometry2d : public mwTGeometry<T,TCoordSystem>
	{
	public:
		typedef mwTBaseGeometry2d<T> BaseGeo;
		typedef typename mwTGeometry<T,TCoordSystem>::CoordSystem CoordSystem;
		typedef typename mwTGeometry<T,TCoordSystem>::ViewPtr ViewPtr;
	private:
		typedef mwTGeometry2d<T,CoordSystem>		MySelf;
	public:
		typedef typename misc::mwAutoPointer< MySelf >							Ptr;
		typedef typename mwTGeometry<T,TCoordSystem>::BaseGeoValueType BaseGeoValueType;
		typedef typename mwTGeometry<T,TCoordSystem>::GeoSetter GeoSetter; 
		typedef typename mwTGeometry<T,TCoordSystem>::GeoGetter GeoGetter; 
		typedef  mwTGeoGetter2dIntf <BaseGeoValueType,CoordSystem>		GeoGetter2d;
		typedef  mwTGeoSetter2dIntf <BaseGeoValueType,CoordSystem>		GeoSetter2d;
		typedef typename mwTGeometry<T,TCoordSystem>::CSValueType			CSValueType;
	//#############################################################################
		//! gets base Geometry2d
		/*! 			
				\returns the base Geometry2d
		*/
		virtual const BaseGeo& GetBaseGeometry2d() const=0;
	//#############################################################################
		//! gets base Geometry
		/*! 			
				\returns the base Geometry
		*/
		virtual const typename mwTGeometry<T,TCoordSystem>::BaseGeo& GetBaseGeometry() const
			{return GetBaseGeometry2d();};
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
		virtual void AcceptVisitor( const GeoSetter2d& setter )=0;
	//#############################################################################
		//! implements visitor pattern for getting data from the current geometry
		/*! 
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter2d& getter )const=0;
	//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeometry2d(){};
	//#############################################################################
	protected:
	//#############################################################################
		//! helper constructor for derived classes
		/*! 
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		inline mwTGeometry2d(const CoordSystem &cs, const ViewPtr& view=ViewPtr())
			:mwTGeometry<T,TCoordSystem>(cs,view)
		{};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
#pragma warning(pop)
//#############################################################################
	typedef mwTGeometry2d<float,CS2df > Geo2dfIn2df;
	typedef mwTGeometry2d<double,CS2dd > Geo2ddIn2dd;
//#############################################################################
	typedef mwTGeometry2d<float,CS3df > Geo2dfIn3df;
	typedef mwTGeometry2d<double,CS3dd > Geo2ddIn3dd;
}
#endif	//	MW_MWTGEOMETRY2D_HPP_
