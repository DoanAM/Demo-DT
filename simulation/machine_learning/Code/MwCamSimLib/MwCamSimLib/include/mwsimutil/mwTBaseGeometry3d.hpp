// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTBaseGeometry3d class

#ifndef MW_MWTBASEGEOMETRY3D_HPP_
#define MW_MWTBASEGEOMETRY3D_HPP_
//#############################################################################
#include "mwTBaseGeometry.hpp"
//#############################################################################
namespace geoDef
{
	//#############################################################################
	//! abstract base class for any 3d base geometry
	template <typename T>
		class MW_5AXUTIL_API mwTBaseGeometry3d : public mwTBaseGeometry <T>
	{
	private:
		typedef mwTBaseGeometry3d<T> MySelf;
	public:
		typedef typename mwTBaseGeometry<T>::ValueType ValueType;
		//#############################################################################
		mwTBaseGeometry3d() {}
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTBaseGeometry3d(){};
	protected:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf& /*rToCopy*/){return *this;};
		mwTBaseGeometry3d(const MySelf& other)
			: mwTBaseGeometry<T>(other){}
	};
	//#############################################################################
	typedef mwTBaseGeometry3d< float > BaseGeo3df;
	typedef mwTBaseGeometry3d< double > BaseGeo3dd;
}
#endif	//	MW_MWTBASEGEOMETRY3D_HPP_
