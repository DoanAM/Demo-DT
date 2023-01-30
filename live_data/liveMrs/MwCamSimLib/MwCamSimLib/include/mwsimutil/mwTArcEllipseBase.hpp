// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTARCELLIPSEBASE_HPP_
#define MW_MWTARCELLIPSEBASE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTArcEllipseBase
	/*!

	*/
	template <typename T>
	class MW_5AXUTIL_API mwTArcEllipseBase  : public mwTBaseGeometry2d<T>
	{
	public:
		typedef typename mwTBaseGeometry2d<T>::ValueType	ValueType;
//#############################################################################
		//! Constrcutor
		/*
		*/
		mwTArcEllipseBase(const ValueType& majorRadius,
						  const ValueType& minorRadius,
						  const ValueType& startAngle,
						  const ValueType& sweepAngle);
//#############################################################################
	    void SetMajorRadius (const ValueType &majorRadius);
//#############################################################################
	    const ValueType& GetMajorRadius () const;
//#############################################################################
	    void SetMinorRadius (const ValueType &minorRadius);
//#############################################################################
	    const ValueType& GetMinorRadius () const;
//#############################################################################
		//! Set the StartAngle of the arcEllipse
		/*
		 \param startAngle specify the startAngle of the arc
		*/
	    void SetStartAngle (const ValueType& StartAngle);
//#############################################################################
		//! Obtain a const value to the StartAngle of the arcEllipse
		/*
		 \return const StartAngle of the arc
		*/
	    const ValueType& GetStartAngle () const;
//#############################################################################
		//! Set the SweepAngle of the arcEllipse
		/*
		 \param sweep specify the startAngle of the arc
		*/
		void SetSweepAngle(const ValueType& SweepAngle);
//#############################################################################
		//! Obtain a const value to the SweepAngle of the arcEllipse
		/*
		 \return const SweepAngle of the arc
		*/
		const ValueType& GetSweepAngle() const;
//#############################################################################
	protected:
		ValueType m_majorRadius;
		ValueType m_minorRadius;

		ValueType m_startAngle;
		ValueType m_sweepAngle;
//#############################################################################
	};
}
#endif	//	MW_MWTARCELLIPSEBASE_HPP_
