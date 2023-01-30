// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
///  this module describes the
/// mwTurningPostUtils class

//#############################################################################

#ifndef MW_MWTURNINGPOSTUTILS_HPP_
#define MW_MWTURNINGPOSTUTILS_HPP_
//#############################################################################
#include "mwDllImpExpDef.hpp"
#include "mwMachDef.hpp"
#include "mwMatrix.hpp"
#include "mwToolPath.hpp"
//#############################################################################
namespace post
{
	//#############################################################################
	class MW_5AXUTIL_API mwTurningPostUtils 
	{
	public:
		//#############################################################################
		typedef cadcam::mwMatrix<double, 4, 4>			mwMatrix4d;
		typedef misc::mwAutoPointer<mwMatrix4d>         mwMatrix4dPtr;
		//############################################################################
		struct TransformationContainer
		{
			mwMatrix4d m_matrix;
			cadcam::mwPoint3d m_direction;
		};
		typedef misc::mwAutoPointer<TransformationContainer> TransformationContainerPtr;
		//############################################################################
		static const bool HasTurret(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		static const bool IsYAxisFake(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		static const post::mwMachDefPtr ExtractMachineDefForTurning(const post::mwMachDefPtr& machDefPtr, const bool extract3axiMachDef);
		//#############################################################################
		static const bool CalculateRotationAngles( 
			const post::mwMachDefPtr& machDefPtr,
			double& angle0,
			double& angle1);
		//#############################################################################
		static const mwMatrix4d GetTransformatrixMatrixFromZToSpindle(
			const post::mwMachDefPtr& machDefPtr, 
			const double cAxisValue,
			const bool disableRotationOfTurretForSpecialCase = false
			); 
		//#############################################################################
		static const mwMatrix4d GetTransformatrixMatrixFromXToSpindle( 
			const post::mwMachDefPtr& machDefPtr,
			const double cAxisValue);
		//#############################################################################
		static const TransformationContainerPtr GetTransformatrixMatrixForTurningPosting(
			const post::mwMachDefPtr& machDefPtr,
			const cadcam::toolpath& toolp,
			const mwMatrix4dPtr& alignMatrix);
		//#############################################################################
		static const mwMatrix4d CreateHolderTranformation(
			const post::mwMachDefPtr& machDefPtr,
			const double toolLengthCompensation,
			const mwMatrix4dPtr& machineHolderTransf = MW_NULL); 
		//#############################################################################
		static const double GetTurretAngle(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		static const mwMatrix4d CombineMatrices(
			mwMatrix4d M1,
			mwMatrix4d M2);
		//#############################################################################
		static const bool CheckTurretDefinition( 
			const post::mwMachDefPtr& machDefPtr, const double precision);
		//#############################################################################
		static const cadcam::mwVector3d GetTurretTableDirection(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		static const mwMatrix4d GetTransformatrixMatrixForRelMove(const post::mwMachDefPtr& machDefPtr);
		//#############################################################################
		static cadcam::mwVector3d GetToolpathDirectionVectorForTurningPosting(
			const post::mwMachDefPtr& machDefPtr,
			const cadcam::toolpath& toolp,
			const mwMatrix4dPtr& alignMatrix);
		//#############################################################################
	private:
		//#############################################################################
		mwTurningPostUtils();//private constructor
		//#############################################################################
		static const bool ValidateTDirection(
			const post::mwMachDefPtr& machDefPtr,
			cadcam::mwVector3d& direction,
			double& angle);
		//#############################################################################
		static const bool ValidateTurningMachine(
			const post::mwMachDefPtr& machDefPtr,
			const cadcam::toolpath& toolp,
			cadcam::mwVector3d& workingDirection,
			cadcam::mwVector3d& tableDirection,
			const mwMatrix4dPtr& alignMatrix);
		//#############################################################################
		static const bool ExtractToolpathDirection(
			const cadcam::toolpath& toolp, 
			const cadcam::mwVector3d& tableDirection,
			cadcam::mwVector3d& toolpathDirection,
			const mwMatrix4dPtr& alignMatrix = MW_NULL);
		//#############################################################################
		static const bool RotateTuret(
			const post::mwMachDefPtr& machDefPtr,
			cadcam::mwVector3d& spindle);
		//#############################################################################
	};//end class mwTurningPostUtils
	//#############################################################################
}// end namespace post
//#############################################################################
#endif	//	MW_MWTURNINGPOSTUTILS_HPP_
