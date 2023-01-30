// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWHEADANDTABLEROTATION_HPP_
#define MW_MWHEADANDTABLEROTATION_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwMachDef.hpp"
#include "mwPostedMove.hpp"
#include "mwMXPParam.hpp"
#include <map>

namespace post
{
	class mwHeadAndTableRotation;
	typedef misc::mwAutoPointer<mwHeadAndTableRotation> mwHeadAndTableRotationPtr;

	class MW_5AXUTIL_API mwHeadAndTableRotation
	{
	public:

		typedef mwMachDef::mwMatrix4d     mwMatrix4d;
		typedef mwMachDef::mwMatrix4dPtr  mwMatrix4dPtr;
		typedef std::vector<size_t>       mwHeadAndTableSolutions;//for now there are only 6 possible solutions

		virtual ~mwHeadAndTableRotation();

		virtual const bool IsValide() const;
		
		virtual void SetValide(const bool valide);
		
		virtual bool AdjustMove(mwPostedMove& _move, const double prevPostedAngle = 0,
			const bool recuration = false) const;
		
		void ResetStrategy(const bool resetAlsoOrder = false,
			const bool customDirection = false); // make first strategy to be first m_solutions available
		
		virtual bool ChangeStrategy();
		
		const bool UpdateStrategy();
		
		virtual void ResetStrategyFlag(const mwMachDefPtr& machPtr);
		
		virtual void RemoveMachineStrategy();
		
		const mwHeadAndTableSolutions& GetSolutions() const;
		
		void SetSolutions(const mwHeadAndTableSolutions& solutions);
		
		const size_t GetNrOfSolutions() const;
		
		virtual const size_t GetSolutionBaseOnTransaltionAxis(const std::map<size_t, cadcam::mwPoint3d>& solutionsMap, const mwMXPParam::SolutionForStartTranslation sst);
		
		void SetMachDefPtr(const mwMachDefPtr& machDefPtr);
		
		virtual const cadcam::mwVector3d GetTableDir(const mwPostedMove& _move) const = 0;

		bool UsePrimitiveRotation(mwPostedMove& move, const double prevPostedAngle) const;

		bool UsePrimitiveRotationForConstantTranslation(mwPostedMove& move, const double prevPostedAngle) const;

	protected:
#pragma warning(push)
#pragma warning(disable:4251)
		
		enum Strategy
		{
			UNDEFINED_STR = 0,
			USE_X_AXIS,
			USE_Y_AXIS,
			USE_Z_AXIS
		};
		
		enum Case
		{
			UNDEFINED_CASE = 0,
			CASE_I,
			CASE_II
		};
		
		enum Plane // working plane
		{
			XY = 0,
			XZ,
			YZ
		};
		
		mwHeadAndTableRotation(const mwMachDefPtr& machDef,
			const cadcam::mwPoint3d& partOrigin,
			const double toolLengthCompensationValue,
			const mwMXPParam& mxpParam,
			const mwMatrix4d& alignMatrix = mwMatrix4d(),
			const bool enableCircularLimit = false);
		
		void SetPlane(const cadcam::mwVector3d& tableVector);
		
		const double GetTheAngleBetweenVectors(
			const cadcam::mwVector3d& u,
			const cadcam::mwVector3d& v,
			const cadcam::mwVector3d& direction) const;
		
		virtual const cadcam::mwPoint3d GetBasePoint(const mwPostedMove& _move) const = 0;
		
		virtual void TransformWithTable(const mwPostedMove& _move, cadcam::mwPoint3d& pos, const bool isVector = false) const = 0;
		
		virtual void Compute(mwPostedMove& _move, const cadcam::mwPoint3d& newMovePos, const double newAngle, bool undeterminedSol = false) const = 0;
		
		virtual const cadcam::mwPoint3d Compute(const mwPostedMove& moveRef, const cadcam::mwPoint3d& newMovePos) const = 0;
		
		bool UsePrimitiveRotation(mwPostedMove& move, const bool increase) const;
		
		const Plane& GetPlane() const;
		
		typedef std::map<size_t, mwMachDefPtr> machinesForStrategy;

		bool                    m_valid;
		mwMachDefPtr            m_machPtr;
		Strategy                m_strategy;
		mutable Case            m_case;
		cadcam::mwPoint3d       m_partOrigin;
		double		            m_toolLengthCompensationValue;

		Plane                   m_plane; // only for head
		cadcam::mwVector3d      m_zDirection; // only for head
		mwMatrix4dPtr           m_machineSysInv;

		mutable bool            m_changeStrategy;

		mwHeadAndTableSolutions m_solutions;
		size_t                  m_currentSolution;
		static const size_t     m_nrOfSolutions;

		mutable machinesForStrategy m_machinesForStrategy;

		mwMXPParam              m_mxpParam;

		bool m_isCustomDirection;

		const bool m_enableCircularLimit; 
		
	private:
#pragma warning(pop)

		mwHeadAndTableRotation& operator = (const mwHeadAndTableRotation&) { return *this; }// avoid warning c4512		
	};

	typedef misc::mwAutoPointer<mwHeadAndTableRotation> mwHeadAndTableRotationPtr;

};//end namespace

#endif	//	MW_MWHEADANDTABLEROTATION_HPP_
