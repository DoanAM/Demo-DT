// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTCSTranslator class

#ifndef MW_MWTCSTRANSLATOR_HPP_
#define MW_MWTCSTRANSLATOR_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
	template < typename T >		class mwTAbstractCoordSystem2d;
	template < typename T >		class mwTAbstractCoordSystem3d;
//#############################################################################
	//! allows translation of the coordinate systems
	template <typename T>
		class MW_5AXUTIL_API mwTCSTranslator 
	{
	public:
		typedef T							ValueType;
		typedef mwTAbstractCoordSystem2d<ValueType>		CS2d;
		typedef mwTAbstractCoordSystem3d<ValueType>		CS3d;
		typedef typename CS2d::PositionVector						CS2dPositionVector;
		typedef typename CS3d::PositionVector						CS3dPositionVector;
		//#############################################################################	
		//! translated a 2d CS with passed offset
		/*! 
				\param toTransform the CS to be translated
				\param offset the vector to be translated with
		*/
		static void Transform(CS2d& toTransform, const CS2dPositionVector& offset);
		//#############################################################################
		//! translated a 2d CS with passed offset
		/*! 
				\param toTransform the CS to be translated
				\param offset the vector to be translated with
		*/
		static void Transform(CS3d& toTransform, const CS3dPositionVector& offset);
		//#############################################################################	
	private:
		//! Constructor - not allowed since it's a static class
		mwTCSTranslator();
	};
}
#endif	//	MW_MWTCSTRANSLATOR_HPP_
