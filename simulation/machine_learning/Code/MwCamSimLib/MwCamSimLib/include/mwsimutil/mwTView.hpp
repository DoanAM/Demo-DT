// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTView class

#ifndef MW_MWTVIEW_HPP_
#define MW_MWTVIEW_HPP_
//#############################################################################
#include <mwTSpaceLocation.hpp>
#include "mwTAbstractCoordSystem3d.hpp"
#include "mwTAbstractCoordSystem2d.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
	//! implements a view for associating it to a multitude of geos
	template <class TCoordSystem>
		class mwTView : protected mwTSpaceLocation<TCoordSystem>
	{
	public:
		typedef typename mwTSpaceLocation<TCoordSystem>::CoordSystem CoordSystem;
	private:
		typedef mwTView<CoordSystem> MySelf;
	public:
		typedef typename mwTSpaceLocation<TCoordSystem>::PositionVector PositionVector;
		typedef typename misc::mwAutoPointer< MySelf > Ptr;
	protected:
		 typedef mwTSpaceLocation<CoordSystem> SpaceLocation;
		//#############################################################################
		//! constructor
		/*! 
				\param cs coordinate system of the view
				\param view the view to which the cs is relative to
						MW_NULL means the cs is relative to world coordinates
		*/
		inline mwTView(const CoordSystem &cs, const Ptr& view=Ptr())
			:SpaceLocation(cs),m_view(view)
		{};	 
		//#############################################################################	
		//! Set  the coordinate system of the View
		/* 
				\param cs the new coordinate system
		*/
		inline void SetCoordSystem(const CoordSystem &cs)
		{
			SpaceLocation::SetCoordSystem(cs);
		}
		//#############################################################################	
		//! Obtain the coordinate system of the view
		/* 
				\returns the coordinate system of the view
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
		inline const Ptr& GetView() const
			{ return m_view;};
		//#############################################################################
		//! sets View
		/*! 			
				\param view the new View
		*/
		inline void SetView(const Ptr& view)
			{m_view=view;};
		//#############################################################################
		//! confirms if view coordinates are relative to a view coordinates
		/*! 			
				\returns true if the view is inside of a View
		*/
		inline const bool IsInsideOfAView() const
			{ return m_view.IsNotNull();};
		//#############################################################################
		//! Transforms a vector having absolute coordinates to view relative coordinates
		/*! translates and rotates a vector	based on origin  and direction 
			of coordinate systems of all views associated to this view
				\param vector the vector having absolute coordinates
				\returns transformed vector
		*/
		inline const PositionVector TransformToMe(const PositionVector& toConv)
		{
			if (IsInsideOfAView())
			{
				return this->m_CoordSystem->TransformToMe(m_view->TransformToMe(toConv));
			}else
			{
				return this->
m_CoordSystem->TransformToMe(toConv);
			}
		}
		//#############################################################################
		//! Transforms a vector having view relative coordinates to absolute coordinates
		/*! translates and rotates a vector	based on origin  and direction 
			of coordinate systems of all views associated to this view
				\param vector the vector having view relative coordinates
				\returns transformed vector
		*/
		inline const PositionVector TransformFromMe(const PositionVector& toConv)
		{
			if (IsInsideOfAView())
			{
				return m_view->TransformFromMe(this->m_CoordSystem->TransformFromMe(toConv));
			}else
			{
				return this->m_CoordSystem->TransformFromMe(toConv);
			}
		}
	//#############################################################################
	protected:
	//#############################################################################
		Ptr m_view;
	};
	//#############################################################################
	typedef mwTView< CS2df > View2df;
	typedef mwTView< CS2dd > View2dd;

	typedef mwTView< CS3df > View3df;
	typedef mwTView< CS3dd > View3dd;
}
#endif	//	MW_MWTVIEW_HPP_
