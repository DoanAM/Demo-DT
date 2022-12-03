// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwPosted5axTPInterpolate class

//#############################################################################

#ifndef MW_MWPOSTED5AXTPINTERPOLATE_HPP_
#define MW_MWPOSTED5AXTPINTERPOLATE_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"
#include "mwMirrorAngle.hpp"
#include "mw5axMachDef.hpp"
#include "mwMXPParam.hpp"
#include "mwCTheta.hpp"
#include "mwToolpathAlignment.hpp"
#include "mwPostCommonDefinitions.hpp"
#include "mwHeadAndTableRotation.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class mwMXPParam;
	//#############################################################################
	class MW_5AXUTIL_API mwPosted5axTPInterpolate  
	{
	public:
		//#############################################################################
		typedef std::list<mwPosted5axMove>         posted5axList;
		typedef misc::mwAutoPointer<posted5axList> posted5axListPtr;
		typedef posted5axList::iterator            iterator;
		typedef posted5axList::const_iterator      const_iterator;
		//#############################################################################
		//! Constructor
		mwPosted5axTPInterpolate(
			const mw5axMachDef& machDef,
			const mwMXPParam& mxpParam,
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue,
			const bool enableCircularLimits = false,
			const bool isLeadingToolLathe = false);
		//#############################################################################
		const posted5axMoveMirror PostMove(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			const mwPostedMove::Types moveType,
			const size_t index,
			const bool addOnPost,
			const double poolAngToolDeg = mathdef::MW_MAX_DOUBLE,
			const bool createShortList = false,
			const double prevPoleAngle = 0.,
			const bool smartSelect = false,
			const bool isCorner = false) const;
		//#############################################################################
		const posted5axListPtr Interpolate(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			mwValidSolutionsListPtr& solutionsListPtr,
			const bool isSixAxisMove = false,
			const bool lastIntSolution = false) const;
		//#############################################################################
		const posted5axListPtr Interpolate(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const bool half = false,
			const double poolAngToolDeg = mathdef::MW_MAX_DOUBLE,
			const bool isSixAxisMove = false) const;
		//#############################################################################
		void DetermineRotAngles(
			const mwPosted5axMove& validMove,
			mwPosted5axMove& moveToFix) const;
		//#############################################################################
		const mwPosted5axMove SelectPostedMove(
			const mwPosted5axMove& prevPostedMove,
			const posted5axMoveMirror& moveMirror,
			post::mwValidSolutions& valid) const;
		//#############################################################################
		mwMXPParam& GetMxpParamRef()
		{
			return m_mxpParam;
		}
		//#############################################################################
		const mwHeadAndTableRotationPtr& GetHeadAndTableRotationPtr() const;
		//#############################################################################
		mwHeadAndTableRotationPtr& GetHeadAndTableRotationPtr();
		//#############################################################################
		void SetNextMoveDirection(const cadcam::mwVector3d& nextMoveDirection);
		//#############################################################################
		const cadcam::mwVector3d& GetNextMoveDirection() const;
		//#############################################################################
		void ProvideRotationAngle(posted5axMoveMirror& postedPair) const;
		//#############################################################################
		void ProvideRotationAngle(posted5axMovePair& postedPair) const;
		//#############################################################################
		void SetMachDef(const mw5axMachDef& machDef);
		//#############################################################################
		const mwPosted5axMove RePost(const mwPosted5axMove& move, const mwPosted5axMove& prev) const;
		//#############################################################################
		const void FindSolutionInMachineLimits(posted5axMoveMirror& pair) const;
		//#############################################################################
		void SetKinfeGrindingMachineCompatible(const bool /*toSet*/) {}; // DEPRECATED, will be removed in the future
		//#############################################################################
	private:
		//#############################################################################
		typedef std::list<bool> poleMovesList;
		//#############################################################################
		mwPosted5axTPInterpolate operator = (const mwPosted5axTPInterpolate&);
		//#############################################################################
#pragma warning(push)
#pragma warning(disable:4251)
		mw5axMachDef               m_machDef;
		mutable mwMXPParam         m_mxpParam;
		const cadcam::mwVector3d   m_partOrigin;
		const double               m_toolLengthCompensationValue;
		mwCThetaPtr                m_mwCThetaPtr;
		mwHeadAndTableRotationPtr  m_headAndTableRotationPtr;
		mutable cadcam::mwVector3d m_nextMoveDirection;
		const bool                 m_enableCircularLimits;
		const bool                 m_isLeadingToolLathe;
#pragma warning(pop)
		//#############################################################################
		const posted5axListPtr InterpolatePriv(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const bool half,
			const double poolAngToolDeg,
			mwValidSolutionsListPtr& solutionsListPtr,
			const bool isSixAxisMove,
			const bool lastIntSolution = false) const;
		//#############################################################################
		const posted5axListPtr CreateListOfPostedMove(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const bool half,
			const double poolAngToolDeg,
			mwValidSolutionsListPtr& solutionsListPtr,
			poleMovesList& poleArea,
			const bool enableAngleFlag = false,
			const bool isSixAxisMove = false,
			const bool lastIntSolution = false) const;
		//#############################################################################
		void FixAngles(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			mwPosted5axMove& move) const;
		//#############################################################################
		const mwPosted5axMove InterpolateByVector(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const mwPosted5axMove& postedTest,
			const double poolAngToolDeg,
			const double angle,
			const double contactPointK,
			const double k,
			mwValidSolutionsListPtr& solutionsListPtr,
			poleMovesList& isPoleArea,
			const bool isSixAxisMove = false) const;
		//#############################################################################
		const mwPosted5axMove IntepolateByMachineAngles(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const double k,
			const double contactPointK,
			const double prevPoleAngle,
			const bool enableAngleFlag) const;
		//#############################################################################
		const mwPosted5axMove InterpolateByAxisValues(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const double k,
			const double contactPointK, 
			const double prevPoleAngle) const;
		//#############################################################################
		const mwPosted5axMove SelectASolution(
			const mwPosted5axMove& postedMove,
			const posted5axMoveMirror& moveMirror) const;
		//#############################################################################
		const bool TestResult(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const posted5axListPtr& vecTP,
			const double maxInitAng) const;
		//#############################################################################
		const double GetMaxAngleForValidAngles(
			const mwPosted5axMove& posted1,
			const mwPosted5axMove& posted2) const;
		//#############################################################################
		const bool IsAngleAndDistanceOverStepAndDis(
			const mwPosted5axMove& posted1,
			const mwPosted5axMove& posted2) const;
		//#############################################################################
		const bool IsToolpathInLimits(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const posted5axListPtr& vecTP) const;
		//#############################################################################
		bool DetectPoleIssue(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd, 
			const double poolAngToolDeg) const;
		//#############################################################################
		void RejectDuplicateMoves(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			posted5axListPtr& vecTP) const;
		//#############################################################################
		void PostMoveVectShort(
			const misc::mwAutoPointer<cadcam::mwCNCMove>& move,
			const double poolAngToolDeg,
			const double prevPoleAngle,
			post::mwMirrorPosted5AxMove& mpm,
			const bool smartSelect) const;
		//#############################################################################
		const double GetMaxAngle(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const posted5axListPtr& vecTP) const;
		//#############################################################################
		void AddInterAtCornerForLaserMach(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd, 
			const bool half,
			const double poolAngToolDeg, 
			mwValidSolutionsListPtr& solutionsListPtr,
			posted5axListPtr& vecTP) const;
		//#############################################################################
		const bool CheckAngleDiff(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const posted5axListPtr& vecTP) const;
		//#############################################################################
		const bool CheckAngleDiff(
			const mwPosted5axMove& posted1,
			const mwPosted5axMove& posted2,
			const bool isRapid) const;
		//#############################################################################
		const bool IsPostedMoveUndetermined(const mwPosted5axMove& move) const;
		//#############################################################################
		const void SwitchInterpolationInPoleArea(
			posted5axListPtr& vecTP,
			const poleMovesList& poleArea,
			const double poolAngToolDeg,
			mwValidSolutionsListPtr& solutionsListPtr) const;
		//#############################################################################
		const cadcam::mwVector3d InterpolateSixAxisCuttigDirection(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			const double k) const;
		//#############################################################################
		const bool IsMoveOutOfLimits(const mwPosted5axMove& move) const;
		//#############################################################################
		const int ComputeStepsAngle(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd) const;
		//#############################################################################
		const int ComputeStepsMove(
			const mwPostedMove& postedStart,
			const mwPostedMove& postedEnd) const;
		//#############################################################################
		const mwPosted5axMove Interpolate(
			const mwPosted5axMove& postedStart,
			const mwPosted5axMove& postedEnd,
			cadcam::mwPoint3d newAbsMachPos,
			const double k,
			const double contactPointK,
			const bool enableAngleFlag) const;
		//#############################################################################
		const cadcam::mwPoint3d RotatePartPostAroundContSurfPoint(
			const mwPosted5axMove& move,
			const double angle) const;
		//#############################################################################
		void FindSolutionInMachineLimits(
			mwPosted5axMove& move,
			const cadcam::mwPoint3d& prevAbsMachPos = cadcam::mwPoint3d(0,0,0)) const;
		//#############################################################################
		const cadcam::mwVector3d GetSixAxisCuttigDirection(const mwPosted5axMove& move) const;
		//#############################################################################
	};// end class mwPosted5axTPInterpolate
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWPOSTED5AXTPINTERPOLATE_HPP_
