// (C) 2003-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTBOXBASE_HPP_
#define MW_MWTBOXBASE_HPP_
//#############################################################################
#include "mwTBaseGeometry3d.hpp"
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
	//! Implements a mwTBoxBase
	/*!

	*/
	template <typename T>
		class MW_5AXUTIL_API mwTBoxBase : public mwTBaseGeometry3d <T>
	{
	public:
		typedef typename mwTBaseGeometry3d <T>::ValueType ValueType;
//#############################################################################
		enum Corners
		{
			NearBottomLeft=1,
			NearBottomRight=2,
			NearTopRight=3,
			NearTopLeft=4,
			FarBottomLeft=5,
			FarBottomRight=6,
			FarTopRight=7,
			FarTopLeft=8
		};
//#############################################################################
		enum Facets
		{
			Near=1,
			Far=2,
			Bottom=3,
			Top=4,
			Left=5,
			Right=6
		};
//#############################################################################
		//! Constrcutor
		/*
		 \param
		*/
		mwTBoxBase(const ValueType& Width,
			const ValueType& Height,
			const ValueType& Depth);
//#############################################################################
		//! Set the Width of the Box
		/*
		 \param Width is the Width of the Box
		*/
	    void SetWidth (const ValueType& Width);
//#############################################################################
		//! Obtain a const value to the Width  of the Box
		/*
		 \return const Width  of the Box
		*/
	    const ValueType& GetWidth () const;
//#############################################################################
		//! Set the Height of the Box
		/*
		 \param Height is the Height of the Box
		*/
		void SetHeight(const ValueType& Height);
//#############################################################################
		//! Obtain a const value to the Height  of the Box
		/*
		 \return const Height of the Box
		*/
		const ValueType& GetHeight() const ;
//#############################################################################
		//! Set the Depth of the Box
		/*
		 \param Depth is the Depth of the Box
		*/
		void SetDepth(const ValueType& Depth);
//#############################################################################
		//! Obtain a const value to the Depth of the Box
		/*
		 \return const Depth of the Box
		*/
		const ValueType& GetDepth() const;
//#############################################################################
		//! Obtain the area of the Box
		/*
		 \return area of the box
		*/
		const ValueType Area() const;
//#############################################################################
		//! Obtain the Volume of the Box
		/*
		 \return volume of the Box
		*/
		const ValueType Volume() const;
//#############################################################################
	protected:
		ValueType m_Height;
		ValueType m_Width;
		ValueType m_Depth;
	};
}
#endif	//	MW_MWTBOXBASE_HPP_
