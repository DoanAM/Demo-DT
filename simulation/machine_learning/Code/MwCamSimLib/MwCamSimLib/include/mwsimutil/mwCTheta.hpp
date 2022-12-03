// (C) 2003-2019 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///             this module describe the mwCTheta
/// class : use rotation around Table-axis to eliminate translation
/// limits.

//#############################################################################

#ifndef MW_MWCTHETA_HPP_
#define MW_MWCTHETA_HPP_
//#############################################################################
#include "mw5axMachDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"
#include "mwDllImpExpDef.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwCTheta
	{
	public:
		//#############################################################################
		mwCTheta(
			const mw5axMachDef& machDef, 
			const cadcam::mwVector3d& partOrigin,
			const double toolLengthCompensationValue);
		//#############################################################################
		const bool Compute(
			const cadcam::mwPoint3d& partPos,
			const double prevPoleAngle,
			cadcam::mwPoint3d& absMachPos, 
			double& angle) const;
		//#############################################################################
	private:
		//#############################################################################
		mwCTheta& operator = (const mwCTheta&) { return *this; }// avoid warning c4512
		//#############################################################################
		enum LimitType
		{
			LIMIT_AXIS_X = 0,
			LIMIT_AXIS_Y,
			LIMIT_AXIS_Z
		};
		//#############################################################################
		const mw5axMachDef&       m_machDef;
		const cadcam::mwVector3d& m_partOrigin;
		const double              m_toolLengthCompensationValue;
		bool                      m_validateMachine;
		//#############################################################################
		const bool Validate(const cadcam::mwPoint3d& absMachPos) const;
		//#############################################################################
		// u and v must be normalized.
		const bool AreVectorsParallel(
			const cadcam::mwPoint3d& u,
			const cadcam::mwPoint3d& v) const;
		//#############################################################################
		const bool IsOutOfLimits(const cadcam::mwPoint3d& absMachPos) const;
		//#############################################################################
		const bool CTheta(
			const cadcam::mwPoint3d& partPos,
			const double prevPoleAngle,
			cadcam::mwPoint3d& absMachPos, 
			double& angle) const;
		//#############################################################################
		const bool GetMove(
			const cadcam::mwPoint3d& partPos,
			double angleA, 
			double angleB,
			LimitType lt,
			const double limit,
			cadcam::mwPoint3d& absMachPos, 
			double& angle) const;
		//#############################################################################
		const bool TestLimit(
			LimitType lt, 
			const double limit,
			const cadcam::mwPoint3d& absMachPos1,
			const cadcam::mwPoint3d& absMachPos2) const;
		//#############################################################################
		const double GetAngle(double a1, double a2) const;
		//#############################################################################
		bool TryFastAdjust(
			cadcam::mwPoint3d& absPos,
			double& angle) const;
		//#############################################################################
		bool Rotate(
			double& lX,
			double& lY,
			double& angle) const;
		//#############################################################################
		double AngleInDegree(
			const cadcam::mwPoint2d& v1, 
			const cadcam::mwPoint2d& v2, 
			const cadcam::mwPoint3d& vect) const;
		//#############################################################################
	};
	//#############################################################################
	typedef misc::mwAutoPointer<mwCTheta> mwCThetaPtr;
	//#############################################################################
}//end namespace post
//#############################################################################
#endif	//	MW_MWCTHETA_HPP_
