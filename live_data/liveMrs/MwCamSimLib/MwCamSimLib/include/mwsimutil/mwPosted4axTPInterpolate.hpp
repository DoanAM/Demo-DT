// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted4axTPInterpolate class

//#############################################################################

#ifndef MW_MWPOSTED4AXTPINTERPOLATE_HPP_
#define MW_MWPOSTED4AXTPINTERPOLATE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTPoint3d.hpp"
#include "mwPosted4axMove.hpp"
#include "mw4axMachDef.hpp"
#include "mwMXPParam.hpp"
#include "mw4axHeadAndTableRotation.hpp"
#include <list>
//#############################################################################
namespace cadcam
{
	class mwCNCMove;
}
//#############################################################################
namespace post
{
	//#############################################################################
	class mwMXPParam;
	//#############################################################################
	class MW_5AXUTIL_API mwPosted4axTPInterpolate  
	{
	public:
		//#############################################################################
		typedef std::list<mwPosted4axMove>         posted4axList;
		typedef misc::mwAutoPointer<posted4axList> posted4axListPtr;
		typedef posted4axList::iterator            iterator;
		typedef posted4axList::const_iterator      const_iterator;
		//#############################################################################
		//! Constructor
		mwPosted4axTPInterpolate(
			const mw4axMachDef& machDef,
			const mwMXPParam& mxpParam,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwMatrix4d& alignMatrix = mwMatrix4d(),
			const bool enableCircularLimits = false,
			const bool isLeadingToolLathe = false);
		//#############################################################################
		const mwPosted4axMove PostMove(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			const mwPostedMove::Types moveType,
			const size_t index,
			const bool addOnPost,
			const double poolAngToolDeg = mathdef::MW_MAX_DOUBLE,/*not used anymore...*/
			const bool createShortList = false,
			const double prevPostedAngle = 0.,
			const bool isCorner = false) const;
		//#############################################################################
		const posted4axListPtr Interpolate(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd) const;
		//#############################################################################
		const mwPosted4axMove LinearInterpolate(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd, 
			const double angle,
			const double poolAngToolDeg,
			const double prevAngle = 0.) const;
		//#############################################################################
		const mwHeadAndTableRotationPtr& GetHeadAndTableRotationPtr() const;
		//#############################################################################
		mwHeadAndTableRotationPtr& GetHeadAndTableRotationPtr();
		//#############################################################################
		mwMXPParam& GetMxpParamRef()
		{
			return m_mxpParam;
		}
		//#############################################################################
		void SetMachDef(const mw4axMachDef& machDef);
		//#############################################################################
	private:
		//#############################################################################
		mwPosted4axTPInterpolate operator = (const mwPosted4axTPInterpolate&);
		//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		mw4axMachDef              m_machDef;
		mwMXPParam                m_mxpParam;
		const cadcam::mwVector3d  m_partOrigin;
		const double              m_toolLengthCompensationValue;
		mwHeadAndTableRotationPtr m_headAndTableRotationPtr;
		const bool                m_isLeadingToolLathe;
#pragma warning(pop)
		//#############################################################################
		const posted4axListPtr CreateListOfPostedMove(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd) const;
		//#############################################################################
		const int ComputeStepsMove(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd) const;
		//#############################################################################
		const int ComputeStepsAngle(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd) const;
		//#############################################################################
		const mwPosted4axMove InterpolateByVector(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd,
			const double poolAngToolDeg,
			const double angle,
			const double contactPointK,
			const double k,
			const double prevPoleAngle) const;
		//#############################################################################
		const mwPosted4axMove IntepolateByMachineAngles(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd,
			const double k,
			const double contactPointK,
			const double prevPoleAngle) const;
		//#############################################################################
		const mwPosted4axMove InterpolateByAxisValues(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd,
			const double k,
			const double contactPointK,
			const double prevPoleAngle) const;
		//#############################################################################
		const mwPosted4axMove Interpolate(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd,
			cadcam::mwPoint3d newAbsMachPos,
			const double k,
			const double contactPointK) const;
		//#############################################################################
		const bool TestResult(
			const mwPosted4axMove& postedStart,
			const mwPosted4axMove& postedEnd,
			const posted4axListPtr& vecTP) const;
		//#############################################################################
		const cadcam::mwVector3d GetSixAxisCuttigDirection(const mwPosted4axMove& move) const;
		//#############################################################################
	};// end class mwPosted4axTPInterpolate
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTED4AXTPINTERPOLATE_HPP_
