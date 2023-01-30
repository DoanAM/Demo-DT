// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTCIRCLEBASE_HPP_
#define MW_MWTCIRCLEBASE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTCircleBase
	/*!
		Contain the radius of the circle
	*/
	template <typename T>
	class MW_5AXUTIL_API mwTCircleBase : public mwTBaseGeometry2d<T>
	{
	public:
		typedef typename mwTBaseGeometry2d<T>::ValueType ValueType;
//#############################################################################
		//! Constrcutor
		/*
		 \param radius of the circle
		*/
		mwTCircleBase(const ValueType& radius);
//#############################################################################
		//! Set the Radius of the circle
		/*
		 \param the radius of the circle
		*/
	    void SetRadius (const ValueType& radius);
//#############################################################################
		//! Obtain a const value to the Radius of the circle
		/*
		 \return const radius of the circle
		*/
	    const ValueType& GetRadius () const;
//#############################################################################
		//! Obtain the area of the circle
		/*
		 \return area of the circle
		*/
		const ValueType Area() const;
//#############################################################################
		//! Obtain the length of the circle
		/*
		 \return length of the circle
		*/
		const ValueType Length() const;
//#############################################################################
	protected:
		ValueType m_radius;
	};
}
#endif	//	MW_MWTCIRCLEBASE_HPP_
