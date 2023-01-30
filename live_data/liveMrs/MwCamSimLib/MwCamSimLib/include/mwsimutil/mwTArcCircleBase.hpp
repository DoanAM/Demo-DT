// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTARCCIRCLEBASE_HPP_
#define MW_MWTARCCIRCLEBASE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTArcCircleBase
	/*!
		We define the arc using the followings:
		 - radius : radius of the circle which includes the arc
		 - startAngle (trigonometric sense) range 0 - 2MW_PI
		 - sweepAngle (trigonometric sense) range -2MW_PI - 2MW_PI rel to Start.
	*/
	template <typename T>
		class MW_5AXUTIL_API mwTArcCircleBase : public mwTBaseGeometry2d<T>
	{
	public:
		typedef typename mwTBaseGeometry<T>::ValueType 	ValueType;
		enum Corners
		{
			Left=1,
			Right=2
		};
//#############################################################################
		//! Constrcutor
		/*
		  \param radius specify the radius of the Arc
		  \param startAngle specify the startAngle of the Arc
		  \param sweepAngle specify the sweepAngle of the Arc
		*/
		mwTArcCircleBase(const ValueType& radius,
			const ValueType& startAngle,
			const ValueType& sweepAngle);
//#############################################################################
		//! Set the Radius of the arc
		/*
		 \param radius specify the radius of the arc
		*/
		void SetRadius(const ValueType& radius);
//#############################################################################
		//! Obtain a const value to the Radius of the arc
		/*
		 \return const radius of the arc
		*/
		inline const ValueType& GetRadius() const
		{
			return m_Radius;
		}
//#############################################################################
		//! Set the StartAngle of the arc
		/*
		 \param startAngle specify the startAngle of the arc
		*/
	    void SetStartAngle (const ValueType& StartAngle);
//#############################################################################
		//! Obtain a const value to the StartAngle of the arc
		/*
		 \return const StartAngle of the arc
		*/
		inline const ValueType& GetStartAngle () const
		{
			return m_StartAngle;
		}
//#############################################################################
		//! Set the SweepAngle of the arc
		/*
		 \param sweep specify the startAngle of the arc
		*/
		void SetSweepAngle(const ValueType& SweepAngle);
//#############################################################################
		//! Obtain a const value to the SweepAngle of the arc
		/*
		 \return const SweepAngle of the arc
		*/
		inline const ValueType& GetSweepAngle() const
		{
			return m_SweepAngle;
		}
//#############################################################################
		//! Obtain the area of the _T("sector") defined by the arc
		/*
		 \return area of the _T("sector") defined by the arc
		*/
		const ValueType Area() const;
//#############################################################################
		//! Obtain the length of the arc
		/*
		 \return length of the arc
		*/
		const ValueType Length() const;
//#############################################################################
	protected:
		ValueType m_Radius;
		ValueType m_StartAngle;
		ValueType m_SweepAngle;
	};
}
#endif	//	MW_MWTARCCIRCLEBASE_HPP_
