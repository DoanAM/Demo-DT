// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTBaseGeometry2d class

#ifndef MW_MWTBASEGEOMETRY2D_HPP_
#define MW_MWTBASEGEOMETRY2D_HPP_
//#############################################################################
#include "mwTBaseGeometry.hpp"
//#############################################################################
namespace geoDef
{
	//#############################################################################
	//! abstract base class for any 2d base geometry
	template <typename T>
		class MW_5AXUTIL_API mwTBaseGeometry2d : public mwTBaseGeometry <T>
	{
	private:
		typedef mwTBaseGeometry2d<T> MySelf;  		
	public:
		typedef typename mwTBaseGeometry<T>::ValueType ValueType;
		//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTBaseGeometry2d(){};
	protected:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf& /*rToCopy*/){return *this;};
	};
	//#############################################################################
	typedef mwTBaseGeometry2d< float > BaseGeo2df;
	typedef mwTBaseGeometry2d< double > BaseGeo2dd;
}
#endif	//	MW_MWTBASEGEOMETRY2D_HPP_
