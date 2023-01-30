// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MW5AXHEADANDTABLEROTATION_HPP_
#define MW_MW5AXHEADANDTABLEROTATION_HPP_

#include "mwHeadAndTableRotation.hpp"
#include "mw5axMachDef.hpp"

namespace post
{
	class MW_5AXUTIL_API mw5axHeadAndTableRotation : public mwHeadAndTableRotation
	{
	public:
		
		mw5axHeadAndTableRotation(
			const mwMachDefPtr& machDef,
			const cadcam::mwPoint3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwMXPParam& mxpParam,
			const cadcam::mwVector3d& moveOrientation,
			const mwMatrix4d& alignMatrix = mwMatrix4d(),
			const bool enableCircularLimits = false);
		
		~mw5axHeadAndTableRotation();
		
		bool AdjustMove(mwPostedMove& _move, const double prevPostedAngle = 0, const bool recuration = false) const;
		
		const mw5axMachDef& GetMachDef() const;
	
	protected:

		const cadcam::mwPoint3d GetBasePoint(const mwPostedMove& _move) const;
		
		const cadcam::mwPoint3d GetTableDir(const mwPostedMove& _move) const;
		
		void TransformWithTable(const mwPostedMove& _move, cadcam::mwPoint3d& pos, const bool isVector = false) const;
		
		void Compute(mwPostedMove& _move, const cadcam::mwPoint3d& newMovePos, const double newAngle, bool undeterminedSol = false) const;
		
		const cadcam::mwPoint3d Compute(const mwPostedMove& moveRef, const cadcam::mwPoint3d& newMovePos) const;
	};
};//end namespace
#endif	//	MW_MW5AXHEADANDTABLEROTATION_HPP_
