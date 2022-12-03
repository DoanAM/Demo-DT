// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MachSim

/// \file
/// this module describe the mwTCoordSystem class

#ifndef MW_MWTCOORDSYSTEM_HPP_
#define MW_MWTCOORDSYSTEM_HPP_
//#############################################################################
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace geoDef
{
//#############################################################################
	//! Base class for any system of coordinates
	template <typename TPositionVector>
	class MW_5AXUTIL_API mwTCoordSystem
	{
	public:
		typedef TPositionVector				PositionVector;
		typedef typename TPositionVector::ValueType		ValueType;
	private:
		typedef mwTCoordSystem<PositionVector>	MySelf;
	public:
//#############################################################################
		//! Transforms a vector having absolute coordinates to CS relative coordinates
		/*! translates and rotates a vector	based on origin  and direction 
			of current coordinate system
				\param vector the vector having absolute coordinates
				\returns transformed vector
		*/
		virtual const PositionVector TransformToMe(const PositionVector &vector) const=0;
//#############################################################################
		//! Transforms a vector having CS relative coordinates to absolute coordinates
		/*! translates and rotates a vector	based on origin  and direction 
			of current coordinate system
				\param vector the vector having CS relative coordinates
				\returns transformed vector
		*/
		virtual const PositionVector TransformFromMe(const PositionVector &vector) const=0;
//#############################################################################
		//! Virtual Pure destructor since it's an abstract class
		virtual ~mwTCoordSystem(){};
	private:
		//#############################################################################
		//! Assignment operator not allowed since it's an abstract class
		inline const MySelf& operator=(const MySelf&){return *this;};
	};
}
#endif	//	MW_MWTCOORDSYSTEM_HPP_
