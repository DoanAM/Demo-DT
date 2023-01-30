// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

//#############################################################################

#ifndef MW_MWPOSTEDMOVEVERIFIER_HPP_
#define MW_MWPOSTEDMOVEVERIFIER_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include <mwTPoint3d.hpp>
#include "mwPostedMove.hpp"
#include "mwMachDef.hpp"
#include "mwPostLimitType.hpp"
 //#############################################################################
namespace post
{
	//#############################################################################
	//! this class verifies the limits of the toolpath
	class MW_5AXUTIL_API mwPostedMoveVerifier
	{
	private:
		//#############################################################################
		mwPostedMoveVerifier(){};
		//#############################################################################
	public:
		//#############################################################################
		static const bool IsExceedingCircularLimit(//rotational(circular) for 4 axis 
			const mwPosted4axMove& postedMove,
			const mw4axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingCircularLimit(//rotational(circular) for 5 axis
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingAnyCircularLimit(//rotational(circular) for 5 axis
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg);
		//#############################################################################
		static const bool IsExceedingCircularLimit(//rotational(circular) for 6 axis
			const mwPosted6axMove& postedMove,
			const mw6axCSMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingAnyCircularLimit(//rotational(circular) for 6 axis
			const mwPosted6axMove& postedMove,
			const mw6axCSMachDef& machDef,
			const double angleTolInDeg);
		//#############################################################################
		static const bool IsExceedingAnyLimit(//rotational and translational for 4 axis ||
			const mwPosted4axMove& postedMove,
			const mw4axMachDef& machDef,
			const double angleTolInDeg,
			const bool cyrcularLimits = false,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const bool IsExceedingLimit(//rotational and translational for 4 axis &&
			const mwPosted4axMove& postedMove,
			const mw4axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType,
			const bool cyrcularLimits = false,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const bool IsExceedingAnyLimit(//rotational and translational for 5 axis ||
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg,
			const bool cyrcularLimits = false,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const bool IsExceedingLimit(//rotational and translational for 5 axis &&
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType,
			const bool cyrcularLimits = false,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const bool IsExceedingLimit(//rotational and translational for 5 axis &&
			const mwPosted6axMove& postedMove,
			const mw6axCSMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType,
			const bool cyrcularLimits = false,
			const double tolerance = mathdef::MW_MATH_TOL);
		//#############################################################################
		static const bool IsExceedingAnyRotationalLimit(//rotational for 4 axis ||
			const mwPosted4axMove& postedMove,
			const mw4axMachDef& machDef,
			const double angleTolInDeg);
		//#############################################################################
		static const bool IsExceedingRotationalLimit(//rotational for 4 axis &&
			const mwPosted4axMove& postedMove,
			const mw4axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingAnyRotationalLimit(//rotational for 5 axis ||
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg);
		//#############################################################################
		static const bool IsExceedingAnyRotationalLimit(//rotational for 6 axis ||
			const mwPosted6axMove& postedMove,
			const mw6axCSMachDef& machDef,
			const double angleTolInDeg);
		//#############################################################################
		static const bool IsExceedingRotationalLimit(//rotational for 5 axis &&
			const mwPosted5axMove& postedMove,
			const mw5axMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingRotationalLimit(//rotational for 6 axis &&
			const mwPosted6axMove& postedMove,
			const mw6axCSMachDef& machDef,
			const double angleTolInDeg,
			mwPostLimitType& limitType);
		//#############################################################################
		static const bool IsExceedingAnyTranslationLimit(//translational for 3,4,5 axis ||
			const mwPostedMove& mw,
			const mwMachDef& machDef,
			const double tolerance = mathdef::MW_MATH_TOL,
			const bool cyrcularLimits = false);
		//#############################################################################
		static const bool IsExceedingTranslationLimit(//translational for 3,4,5 axis &&
			const mwPostedMove& mw,
			const mwMachDef& machDef,
			mwPostLimitType& limitType,
			const double tolerance = mathdef::MW_MATH_TOL,
			const bool cyrcularLimits = false);
		//#############################################################################
	};// end class mwPostedMoveVerifier
	//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWPOSTEDMOVEVERIFIER_HPP_
