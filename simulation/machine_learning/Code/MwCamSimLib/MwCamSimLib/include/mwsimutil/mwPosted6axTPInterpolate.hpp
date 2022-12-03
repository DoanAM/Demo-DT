// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted6axTPInterpolate class

//#############################################################################

#ifndef MW_MWPOSTED6AXTPINTERPOLATE_HPP_
#define MW_MWPOSTED6AXTPINTERPOLATE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"
#include "mwMirrorAngle.hpp"
#include "mw6axCSMachDef.hpp"
#include "mwMXPParam.hpp"
#include "mwCTheta.hpp"
#include "mwToolpathAlignment.hpp"
#include "mwPostCommonDefinitions.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwMXPParam;
	//#############################################################################
	class MW_5AXUTIL_API mwPosted6axTPInterpolate  
	{
	public:
		//#############################################################################
		typedef std::list<mwPosted6axMove>         posted6axList;
		typedef misc::mwAutoPointer<posted6axList> posted6axListPtr;
		typedef posted6axList::iterator            iterator;
		typedef posted6axList::const_iterator      const_iterator;
		//#############################################################################
		//! Constructor
		mwPosted6axTPInterpolate(
			const mw6axCSMachDef& machDef,
			const mwMXPParam& mxpParam,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const bool enableCircularLimits = false);
		//#############################################################################
		const posted6axMoveMirror PostMove(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			const mwPostedMove::Types moveType,
			const size_t index,
			const bool addOnPost,
			const bool createShortList = false,
			const bool smartSelect = false,
			const bool isCorner = false) const;
		//#############################################################################
		const posted6axListPtr Interpolate(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			mwValidSolutionsListPtr& solutionsListPtr,
			double angleVariation0 = 0,
			double angleVariation1 = 0,
			double angleVariation2 = 0) const;
		//#############################################################################
		const posted6axListPtr Interpolate(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const bool half = false,
			double angleVariation0 = 0,
			double angleVariation1 = 0,
			double angleVariation2 = 0) const;
		//#############################################################################
		const mwPosted6axMove SelectPostedMove(
			const mwPosted6axMove& prevPostedMove,
			const posted6axMoveMirror& moveMirror,
			post::mwValidSolutions& valid) const;
		//#############################################################################
		mwMXPParam& GetMxpParamRef()
		{
			return m_mxpParam;
		}
		//#############################################################################
		void DetermineRotAngles(
			const mwPosted6axMove& validMove,
			mwPosted6axMove& moveToFix,
			double angleVariation0 = 0,
			double angleVariation1 = 0,
			double angleVariation2 = 0) const;
		//#############################################################################
		void SetMachDef(const mw6axCSMachDef& machDef);
		//#############################################################################
		void ProvideRotationAngle(posted6axMoveMirror& moveMirror) const;
		//#############################################################################
		void ProvideRotationAngle(posted6axMovePair& postedPair) const;
		//#############################################################################
	private:
		//#############################################################################
		mwPosted6axTPInterpolate operator = (const mwPosted6axTPInterpolate&);
		//#############################################################################
		mw6axCSMachDef            m_machDef;
		mwMXPParam                m_mxpParam;
		const cadcam::mwVector3d  m_partOrigin;
		const double              m_toolLengthCompensationValue;
		const bool                m_enableCircularLimits;
		//#############################################################################
		const posted6axListPtr InterpolatePriv(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const bool half,
			mwValidSolutionsListPtr& solutionsListPtr,
			double angleVariation0,
			double angleVariation1,
			double angleVariation2) const;
		//#############################################################################
		const posted6axListPtr CreateListOfPostedMove(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const bool half,
			mwValidSolutionsListPtr& solutionsListPtr,
			double angleVariation0,
			double angleVariation1,
			double angleVariation2) const;
		//#############################################################################
		const int ComputeStepsMove(
			const mwPostedMove& postedStart,
			const mwPostedMove& postedEnd) const;
		//#############################################################################
		const int ComputeStepsAngle(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd) const;
		//#############################################################################
		const mwPosted6axMove InterpolateByVector(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const mwPosted6axMove& postedTest,
			const double angle,
			const double angleCP,
			const double sawAngle,
			const double k,
			mwValidSolutionsListPtr& solutionsListPtr,
			double angleVariation0,
			double angleVariation1,
			double angleVariation2) const;
		//#############################################################################
		const mwPosted6axMove IntepolateByMachineAngles(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const double k,
			const double contactPointK) const;
		//#############################################################################
		const mwPosted6axMove InterpolateByAxisValues(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const double k,
			const double contactPointK) const;
		//#############################################################################
		const mwPosted6axMove Interpolate(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			cadcam::mwPoint3d newAbsMachPos,
			const double k,
			const double contactPointK) const;
		//#############################################################################
		const mwPosted6axMove GetMoveWithShortestAngle(
			const mwPosted6axMove& postedMove,
			const posted6axMoveMirror& moveMirror) const;
		//#############################################################################
		const bool TestResult(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const posted6axListPtr& vecTP) const;
		//#############################################################################
		const double GetMaxAngle(
			const mwPosted6axMove& posted1,
			const mwPosted6axMove& posted2) const;
		//#############################################################################
		const bool IsAngleAndDistanceOverStepAndDis(
			const mwPosted6axMove& posted1,
			const mwPosted6axMove& posted2) const;
		//#############################################################################
		const bool IsToolpathInLimits(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const posted6axListPtr& vecTP) const;
		//#############################################################################
		void RejectDuplicateMoves(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			posted6axListPtr& vecTP) const;
		//#############################################################################
		void PostMoveVectShort(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			post::mwMirrorPosted6AxMove& mpm,
			const bool smartSelect) const;
		//#############################################################################
		const double GetMaxAngle(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd,
			const posted6axListPtr& vecTP) const;
		//#############################################################################
		void AddInterAtCornerForLaserMach(
			const mwPosted6axMove& postedStart,
			const mwPosted6axMove& postedEnd, 
			const bool half,
			const double poolAngToolDeg, 
			mwValidSolutionsListPtr& solutionsListPtr,
			posted6axListPtr& vecTP) const;
		//#############################################################################
	};// end class mwPosted6axTPInterpolate
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTED6AXTPINTERPOLATE_HPP_
