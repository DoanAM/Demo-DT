// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTSEGMENTBASE_HPP_
#define MW_MWTSEGMENTBASE_HPP_
#include "mwDllImpExpDef.hpp"
//#############################################################################
#include "mwTBaseGeometry2d.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTSegmentBase
	/*!
	*/
	template <typename T>
	class MW_5AXUTIL_API mwTSegmentBase : public mwTBaseGeometry2d<T>
	{
	public:
		typedef typename mwTBaseGeometry2d<T>::ValueType ValueType;
//#############################################################################
		enum Corners
		{
			Left=1,
			Right=2
		};
//#############################################################################
		//! Constrcutor
		/*
		 \param radius of the circle
		*/
		mwTSegmentBase(const ValueType& length);
//#############################################################################
		//! Set the Radius of the circle
		/*
		 \param the radius of the circle
		*/
	    void SetLength (const ValueType& length);
//#############################################################################
		//! Obtain a const value to the Radius of the circle
		/*
		 \return const radius of the circle
		*/
	    const ValueType& GetLength () const;
//#############################################################################
	protected:
		ValueType m_Length;
	};
}
#endif	//	MW_MWTSEGMENTBASE_HPP_
