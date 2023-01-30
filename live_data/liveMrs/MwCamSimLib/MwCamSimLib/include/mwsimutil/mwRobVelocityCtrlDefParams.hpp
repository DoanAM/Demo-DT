// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBVELOCITYCTRLDEFPARAMS_HPP_
#define MW_MWROBVELOCITYCTRLDEFPARAMS_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwRobOptimizationsParams.hpp"

#include <vector>
//#############################################################################
namespace post
{
class MW_5AXUTIL_API mwJointRateFilter
{
public:
	mwJointRateFilter();

	void SetApplyAcceleration(const bool& value);
	const bool IsApplyAcceleration() const;

	void SetDefaults();

	const mwJointRateFilter& operator=(const mwJointRateFilter& toCopy);

	const bool operator==(const mwJointRateFilter& toCompare) const;

private:
	void Copy(const mwJointRateFilter& toCopy);

	bool m_isApplyAcceleration;
};

class MW_5AXUTIL_API mwEndEffectorRateFilter
{
public:
	mwEndEffectorRateFilter();

	const mwRobTypes::AxisWeights& GetEndEffectorWeights() const;
	void SetEndEffectorWeights(const mwRobTypes::AxisWeights& endEffectorWeights);

	void SetStopAtAxisLimits(const bool& value);
	const bool IsStopAtAxisLimits() const;

	void SetStopAtCollisions(const bool& value);
	const bool IsStopAtCollisions() const;

	void SetCheckAllCollisions(const bool& value);
	const bool IsCheckAllCollisions() const;

	void SetDefaultWeight(const double& value);
	const double GetDefaultWeight() const;

	void SetThreshold(const double& value);
	const double GetThreshold() const;

	void SetDefaults();

	const mwEndEffectorRateFilter& operator=(const mwEndEffectorRateFilter& toCopy);

	const bool operator==(const mwEndEffectorRateFilter& toCompare) const;

private:
	void Copy(const mwEndEffectorRateFilter& toCopy);

	bool m_stopAtCollisions;
	bool m_stopAtAxisLimits;
	bool m_checkAllCollisions;
	double m_defaultWeight;
	double m_threshold;
	mwRobTypes::AxisWeights m_endEffectorWeights;
};

class MW_5AXUTIL_API mwControlParameters
{
public:
	mwControlParameters();

	const mwRobTypes::AxisLimits& GetAccLimits() const;
	void SetAccLimits(const mwRobTypes::AxisLimits& accLimits);

	const mwRobTypes::AxisLimits& GetDecelerationLimits() const;
	void SetDecelerationLimits(const mwRobTypes::AxisLimits& decelerationLimits);

	const mwRobTypes::AxisLimits& GetVelocityLimits() const;
	void SetVelocityLimits(const mwRobTypes::AxisLimits& velocityLimits);

	const mwRobTypes::AxisLimits& GetJerkLimits() const;
	void SetJerkLimits(const mwRobTypes::AxisLimits& jerkLimits);

	void SetDefaults();

	const mwControlParameters& operator=(const mwControlParameters& toCopy);

	const bool operator==(const mwControlParameters& toCompare) const;

private:
	void Copy(const mwControlParameters& toCopy);

	mwRobTypes::AxisLimits m_accLimits;
	mwRobTypes::AxisLimits m_decelerationLimits;
	mwRobTypes::AxisLimits m_velocityLimits;
	mwRobTypes::AxisLimits m_jerkLimits;
};

class MW_5AXUTIL_API mwSoftConstraint
{
public:
	mwSoftConstraint();

	void SetWeight(const double& value);
	const double GetWeight() const;

	const mwSoftConstraint& operator=(const mwSoftConstraint& toCopy);

	const bool operator==(const mwSoftConstraint& toCompare) const;

	void SetDefaults();

private:
	double m_weight;
};

class MW_5AXUTIL_API mwScalar
{
public:
	mwScalar();

	void SetScalarValue(const double& value);
	const double GetScalarValue() const;

	const mwScalar& operator=(const mwScalar& toCopy);

	const bool operator==(const mwScalar& toCompare) const;

	void SetDefaults();

private:
	double m_scalar;
};

class MW_5AXUTIL_API mwMassMatrix
{
public:
	mwMassMatrix();

	const mwMassMatrix& operator=(const mwMassMatrix& toCopy);

	const mwRobTypes::AxisWeights& GetMassMatrixWeights() const;
	void SetMassMatrixWeights(const mwRobTypes::AxisWeights& massMatrixWeights);

	const bool operator==(const mwMassMatrix& toCompare) const;

	void SetDefaults();

private:
	mwRobTypes::AxisWeights m_massMatrixWeights;
};

class MW_5AXUTIL_API mwGeneralConstraintFilter
{
public:
	mwGeneralConstraintFilter();

	void UseJointLimitAvoidance(const bool& value);
	const bool IsUseJointLimitAvoidance() const;

	const mwGeneralConstraintFilter& operator=(const mwGeneralConstraintFilter& toCopy);

	const bool operator==(const mwGeneralConstraintFilter& toCompare) const;

	void SetDefaults();

private:
	bool m_useJointLimitAvoidance;
};

class MW_5AXUTIL_API mwVelocityControlDefinition
{
public:
	using ID = misc::mwstring;
	using OptimizationPtr =  misc::mwAutoPointer<mwOptimization>;
	using Optimizations =  std::vector<OptimizationPtr>;

	mwVelocityControlDefinition();

	void SetID(const ID& newID);
	const ID& GetID() const;

	const mwJointRateFilter& GetJointRateFilter() const;
	void SetJointRateFilter(const mwJointRateFilter& newJointRateFilter);

	const mwEndEffectorRateFilter& GetEndEffectorRateFilter() const;
	void SetEndEffectorRateFilter(const mwEndEffectorRateFilter& newEndEffectorRateFilter);

	const mwControlParameters& GetControlParameters() const;
	void SetControlParameters(const mwControlParameters& newControlParameters);

	const mwSoftConstraint& GetSoftConstraint() const;
	void SetSoftConstraint(const mwSoftConstraint& newSoftConstraint);

	const mwGeneralConstraintFilter& GetGeneralConstraintFilter() const;
	void SetGeneralConstraintFilter(const mwGeneralConstraintFilter& newGeneralConstraintFilter);

	const mwMassMatrix& GetMassMatrix() const;
	void SetMassMatrix(const mwMassMatrix& newMassMatrix);

	const mwScalar& GetScalar() const;
	void SetScalar(const mwScalar& scalar);

	const Optimizations& GetOptimizations() const;
	void SetOptimizations(const mwVelocityControlDefinition::Optimizations& newOptimizations);

	void AddOptimization(OptimizationPtr optimization);

	void SetDefaults();

	const mwVelocityControlDefinition& operator=(const mwVelocityControlDefinition& toCopy);

	const bool operator==(const mwVelocityControlDefinition& toCompare) const;

private:
	void Copy(const mwVelocityControlDefinition& toCopy);

	Optimizations m_optimizations;
	mwJointRateFilter m_jointRateFilter;
	mwEndEffectorRateFilter m_endEffectorRateFilter;
	mwControlParameters m_controlParameters;
	mwSoftConstraint m_softConstraint;
	mwVelocityControlDefinition::ID m_id;
	mwMassMatrix m_massMatrix;
	mwGeneralConstraintFilter m_generalConstraintFilter;
	mwScalar m_scalar;
};

class MW_5AXUTIL_API mwVelocityCtrlDefContainer
{
public:
	using IDs = std::vector<mwVelocityControlDefinition::ID>;
	using VelCtrlDefPtr = misc::mwAutoPointer<mwVelocityControlDefinition>;
	using VelCtrlDefsPtr = std::vector<VelCtrlDefPtr>;

	mwVelocityCtrlDefContainer(){};

	mwVelocityCtrlDefContainer(const VelCtrlDefsPtr& velCtrlDefs);

	mwVelocityCtrlDefContainer(const VelCtrlDefPtr& velCtrlDef);

	mwVelocityCtrlDefContainer(const mwVelocityCtrlDefContainer& toCopy);

	const mwVelocityCtrlDefContainer& operator=(const mwVelocityCtrlDefContainer& toCopy);

	const bool operator==(const mwVelocityCtrlDefContainer& toCompare) const;

	const bool operator!=(const mwVelocityCtrlDefContainer& toCompare) const;

	const VelCtrlDefPtr& GetVelocityCtrlDef(const mwVelocityControlDefinition::ID& id) const;

	VelCtrlDefPtr& GetVelocityCtrlDef(const mwVelocityControlDefinition::ID& id);

	void AddVelocityCtrlDef(const VelCtrlDefPtr& velCtrlDesc);

	void RemoveVelocityCtrlDefs(const mwVelocityControlDefinition::ID& id);

	void RemoveAllVelocityCtrlDefs();

	void ChangeVelocityCtrlDef(
		const mwVelocityControlDefinition::ID& id, const VelCtrlDefPtr& velCtrlDef);

	const VelCtrlDefsPtr& GetVelocityCtrlDefs() const;

	VelCtrlDefsPtr& GetVelocityCtrlDefs();

	void SetVelocityCtrlDefs(const VelCtrlDefsPtr& velCtrlDefs);

	const IDs GetAvailableVelocityCtrlDefsIDs() const;

	const size_t GetSize() const;

private:
#pragma warning(push)
#pragma warning(disable : 4251)

	VelCtrlDefsPtr m_velCtrlDefs;

	void Copy(const mwVelocityCtrlDefContainer& toCopy);

#pragma warning(pop)
};

}  // end namespace post
#endif	//	MW_MWROBVELOCITYCTRLDEFPARAMS_HPP_
