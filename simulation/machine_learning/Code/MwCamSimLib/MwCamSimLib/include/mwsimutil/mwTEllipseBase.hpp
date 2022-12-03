// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTELLIPSEBASE_HPP_
#define MW_MWTELLIPSEBASE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTEllipseBase
	/*!

	*/
	template <typename T>
	class MW_5AXUTIL_API mwTEllipseBase  : public mwTBaseGeometry2d<T>
	{
	public:
		typedef typename mwTBaseGeometry2d<T>::ValueType ValueType;
//#############################################################################
		//! Constrcutor
		/*
		*/
		mwTEllipseBase(const ValueType &majorRadius,
					   const ValueType &minorRadius);
//#############################################################################
	    void SetMajorRadius (const ValueType &majorRadius);
//#############################################################################
	    const ValueType& GetMajorRadius () const;
//#############################################################################
	    void SetMinorRadius (const ValueType &minorRadius);
//#############################################################################
	    const ValueType& GetMinorRadius () const;
//#############################################################################
		//! Obtain the area of the ellipse
		/*
		 \return area of the ellipse
		*/
		const ValueType Area() const;
//#############################################################################
		//! Obtain the length of the ellipse
		/*
		 \return length of the ellipse
		*/
		const ValueType Length() const;
//#############################################################################
	protected:
		ValueType m_majorRadius;
		ValueType m_minorRadius;
	};
}
#endif	//	MW_MWTELLIPSEBASE_HPP_
