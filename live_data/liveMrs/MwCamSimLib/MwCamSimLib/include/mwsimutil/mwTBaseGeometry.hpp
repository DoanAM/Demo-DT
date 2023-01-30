// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTBaseGeometry class

#ifndef MW_MWTBASEGEOMETRY_HPP_
#define MW_MWTBASEGEOMETRY_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
	//#############################################################################
		//! abstract base class for any base geometry
	template <typename T>
	class MW_5AXUTIL_API mwTBaseGeometry  
	{
	private:
		typedef mwTBaseGeometry<T> MySelf;
	public:
		typedef T ValueType;
	//#############################################################################
		mwTBaseGeometry() {}
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTBaseGeometry(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	protected:
		mwTBaseGeometry(const MySelf&) {}
	};
	//#############################################################################
	typedef mwTBaseGeometry< float > BaseGeof;
	typedef mwTBaseGeometry< double > BaseGeod;
}
#endif	//	MW_MWTBASEGEOMETRY_HPP_
