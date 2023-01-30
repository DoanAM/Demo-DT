// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTGeometry class

#ifndef MW_MWTGEOMETRY_HPP_
#define MW_MWTGEOMETRY_HPP_
//#############################################################################
#include <mwTSpaceLocation.hpp>
#include "mwTBaseGeometry.hpp"
#include "mwTView.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
//=========== Templates declarations.=============
	template <typename T, typename TCoordSystem>	class MW_5AXUTIL_API mwTGeometry2d;
	template <typename T, typename TCoordSystem>	class MW_5AXUTIL_API mwTGeometry3d;
	template <typename T, typename TCoordSystem>	class MW_5AXUTIL_API mwTGeometry;
	//! Visitor pattern for setting a geometry
	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTGeoSetterIntf
	{
	private:
		typedef mwTGeoSetterIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(mwTGeometry<ValueType,CoordSystem>& tv) const =0;
		virtual void Visit(mwTGeometry2d<ValueType,CoordSystem>& tv) const =0;
		virtual void Visit(mwTGeometry3d<ValueType,CoordSystem>& tv) const =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoSetterIntf(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
	//#############################################################################
	//! Visitor pattern for getting data from a coordinate system
	template <typename T,typename TCoordSystem>
	class MW_5AXUTIL_API mwTGeoGetterIntf
	{
	private:
		typedef mwTGeoGetterIntf<T,TCoordSystem> MySelf;
	public:
		typedef T				ValueType;
		typedef TCoordSystem	CoordSystem;
		//#############################################################################
		virtual void Visit(const mwTGeometry<ValueType,CoordSystem>& tv) =0;
		virtual void Visit(const mwTGeometry2d<ValueType,CoordSystem>& tv) =0;
		virtual void Visit(const mwTGeometry3d<ValueType,CoordSystem>& tv) =0;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeoGetterIntf(){};
		//#############################################################################
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
//#############################################################################
	//! abstract base class for any geometry
	template <class T, class TCoordSystem>
		class MW_5AXUTIL_API mwTGeometry : protected mwTSpaceLocation<TCoordSystem>
	{
	public:
		typedef mwTBaseGeometry<T>		BaseGeo;
		typedef typename BaseGeo::ValueType									BaseGeoValueType;
		typedef typename mwTSpaceLocation<TCoordSystem>::CoordSystem CoordSystem;
		typedef mwTView<CoordSystem>								View;
	protected:
		typedef mwTSpaceLocation<CoordSystem>	SpaceLocation;		
	private:
		typedef mwTGeometry<T,TCoordSystem>						MySelf;
	public:
		typedef typename MySelf::View::Ptr									ViewPtr;
		typedef typename CoordSystem::ValueType								CSValueType;
		typedef typename CoordSystem::PositionVector						PositionVector;
		typedef typename misc::mwAutoPointer< MySelf >						Ptr;

		typedef mwTGeoGetterIntf <BaseGeoValueType,CoordSystem>	GeoGetter;
		typedef mwTGeoSetterIntf <BaseGeoValueType,CoordSystem>	GeoSetter;
	//#############################################################################	
		//! Set the coordinate system of the geometry
		/* 
				\param cs the new coordinate system
		*/
		inline void SetCoordSystem(const CoordSystem &cs)
		{
			SpaceLocation::SetCoordSystem(cs);
		}
	//#############################################################################	
		//! Obtain the coordinate system of the geometry
		/* 
				\returns the coordinate system of the geometry
		*/
		inline const CoordSystem& GetCoordSystem() const
		{
			return SpaceLocation::GetCoordSystem();
		}
	//#############################################################################
		//! gets View
		/*! 			
				\returns the View
		*/
		inline const ViewPtr& GetView() const
			{ return m_view;};
	//#############################################################################
		//! sets View
		/*! 			
				\param rView the new View
		*/
		inline void SetView(const ViewPtr& view)
			{m_view=view;};
	//#############################################################################
		//! confirms if geometry coordinates are relative to a view coordinates
		/*! 			
				\returns true if the geometry is inside of a View
		*/
		inline const bool IsInsideOfAView() const
			{ return m_view.IsNotNull();};
	//#############################################################################
		//! gets base geometry
		/*! 			
				\returns the base geometry
		*/
		virtual const BaseGeo& GetBaseGeometry() const=0;
	//#############################################################################
		//! implements visitor pattern for setting data in the current geometry
		/*! 
				\param setter the visitor to setting data in the current CS
		*/	
		virtual void AcceptVisitor( const GeoSetter& setter )=0;
	//#############################################################################
		//! implements visitor pattern for getting data from the current geometry
		/*! 
			\param getter the visitor to interrogate the current CS
		*/
		virtual void AcceptVisitor(	GeoGetter& getter )const=0;
	//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTGeometry(){};
	//#############################################################################
	protected:
	//#############################################################################
		//! helper constructor for derived classes
		/*! 
				\param cs coordinate system to be used
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		inline mwTGeometry(const CoordSystem &cs, const ViewPtr& view=ViewPtr())
			:SpaceLocation(cs),m_view(view)
		{};
	//#############################################################################
#pragma warning(suppress:4251)
		ViewPtr m_view;

	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	protected:
		mwTGeometry(const mwTGeometry& other)
			: mwTSpaceLocation<CoordSystem>(other) {}
	};
	//#############################################################################
	typedef mwTGeometry<float,CS2df > GeofIn2df;
	typedef mwTGeometry<double,CS2dd > GeodIn2dd;
	//#############################################################################
	typedef mwTGeometry<float,CS3df > GeofIn3df;
	typedef mwTGeometry<double,CS3dd > GeodIn3dd;
}
#endif	//	MW_MWTGEOMETRY_HPP_
