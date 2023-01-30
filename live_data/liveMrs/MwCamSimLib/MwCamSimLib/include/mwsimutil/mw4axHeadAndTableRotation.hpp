// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW4AXHEADANDTABLEROTATION_HPP_
#define MW_MW4AXHEADANDTABLEROTATION_HPP_

#include "mwHeadAndTableRotation.hpp"
#include "mw4axMachDef.hpp"
#include "mw5axMachDef.hpp"
#include "mw6axCSMachDef.hpp"
#include "mwTPoint2d.hpp"
#include "mwPosted5axMove.hpp"

namespace post
{

	class MW_5AXUTIL_API mw4axHeadAndTableRotation : public mwHeadAndTableRotation
	{
	public:

		mw4axHeadAndTableRotation(
			const mwMachDefPtr& machDef,
			const cadcam::mwPoint3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwMXPParam& mxpParam,
			const mwMatrix4d& alignMatrix = mwMatrix4d(),
			const bool enableCircularLimits = false);

		~mw4axHeadAndTableRotation();

		static const bool IsPossible4axHeadAndTableRotation(const mw5axMachDef& machDef, const cadcam::mwVector3d& moveOrient);

		static const mw4axMachDef Extract4axMachDef(const mw5axMachDef& machDef, const cadcam::mwVector3d& moveOrient);

		static const mw4axMachDef Extract4axMachDef(const mw6axCSMachDef& machDef);

		static const bool IsAngleUndetermined(
			const mw5axMachDef& machDef,
			const cadcam::mwVector3d& moveOrient,
			double& determinedAngle,
			mwPosted5axMove::anglesState& angsState);

		bool AdjustMove(mwPostedMove& _move, const double prevPostedAngle = 0, const bool recuration = false) const;

		const mw4axMachDef& GetMachDef() const;

	protected:

		bool AdjustMoveForHead(mwPostedMove& _move, const double prevPostedAngle) const;

		const cadcam::mwPoint3d GetBasePoint(const mwPostedMove& _move) const;

		const cadcam::mwPoint3d GetTableDir(const mwPostedMove& _move) const;
		
		void TransformWithTable(const mwPostedMove& _move, cadcam::mwPoint3d& pos, const bool isVector = false) const;
		
		void Compute(mwPostedMove& _move, const cadcam::mwPoint3d& newMovePos, const double newAngle, bool undeterminedSol = false) const;
		
		const cadcam::mwPoint3d Compute(const mwPostedMove& moveRef, const cadcam::mwPoint3d& newMovePos) const;
		
		const bool CheckSol(double u, double v) const;
		
		const cadcam::mwPoint2d RotatePointIn2D( 
			const cadcam::mwPoint2d& P,		
			const double alpha) const;
		
	};
	
};//end namespace

#endif	//	MW_MW4AXHEADANDTABLEROTATION_HPP_
