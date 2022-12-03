// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTSPHEREBASE_HPP_
#define MW_MWTSPHEREBASE_HPP_
//#############################################################################
#include "mwTBaseGeometry3d.hpp"
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTSphereBase
	/*!
		Contain the radius of the sphere
	*/
	template <typename T>
	class MW_5AXUTIL_API mwTSphereBase : public mwTBaseGeometry3d <T>
	{
	public:
		typedef typename mwTBaseGeometry<T>::ValueType ValueType;
//#############################################################################
		//! Constrcutor
		/*
		 \param radius of the sphere
		*/
		mwTSphereBase(const ValueType& radius);
//#############################################################################
		//! Set the Radius of the sphere
		/*
		 \param the radius of the sphere
		*/
	    void SetRadius (const ValueType& radius);
//#############################################################################
		//! Obtain a const value to the Radius of the sphere
		/*
		 \return const radius of the sphere
		*/
	    const ValueType& GetRadius () const;
//#############################################################################
		//! Obtain the area of the sphere
		/*
		 \return area of the sphere
		*/
		const ValueType Area() const;
//#############################################################################
		//! Obtain the volume of the sphere
		/*
		 \return length of the sphere
		*/
		const ValueType Volume() const;
//#############################################################################
	protected:
		ValueType m_Radius;
	};
}
#endif	//	MW_MWTSPHEREBASE_HPP_
