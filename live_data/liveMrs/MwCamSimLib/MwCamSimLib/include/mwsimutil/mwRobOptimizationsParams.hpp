// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBOTIMIZATIONSPARAMS_HPP_
#define MW_MWROBOTIMIZATIONSPARAMS_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwRobTypes.hpp"

//#############################################################################
namespace post
{
class MW_5AXUTIL_API mwOptimization
{
public:
	enum InstanceType
	{
		ABSTRACT = 0,
		JOINT_LIMIT_AVOIDANCE = 1,
		COLLISION_AVOIDANCE = 2,
		SINGULARITY_AVOIDANCE = 3,
		JOINT_CONSTRAINT_AVOIDANCE = 4,
	};

	mwOptimization();

	virtual ~mwOptimization();

	virtual const InstanceType GetInstanceType() const;

	void SetWeight(const double& value);
	const double GetWeight() const;

	const mwOptimization& operator=(const mwOptimization& toCopy);

	const bool operator==(const mwOptimization& toCompare) const;

private:
	double m_weight;
};

class MW_5AXUTIL_API mwJointLimitAvoidance : public mwOptimization
{
public:
	mwJointLimitAvoidance();

	virtual ~mwJointLimitAvoidance();

	virtual const InstanceType GetInstanceType() const;

	const mwRobTypes::AvoidanceZones& GetAvoidanceZones() const;
	void SetAvoidanceZones(const mwRobTypes::AvoidanceZones& avoidanceZones);

	const mwRobTypes::AxisIDs& GetExcludedAxis() const;
	void SetExcludedAxis(const mwRobTypes::AxisIDs& excludedAxis);

	void SetAvoidanceZone(const double& value);
	const double GetAvoidanceZone() const;

	void SetExponent(const double& value);
	const double GetExponent() const;

	void SetFractional(const bool& value);
	const bool IsFractional() const;

	void SetMaximum(const double& value);
	const double GetMaximum() const;

	const mwJointLimitAvoidance& operator=(const mwJointLimitAvoidance& toCopy);

	const bool operator==(const mwJointLimitAvoidance& toCompare) const;

	void SetDefaults();

private:
	void Copy(const mwJointLimitAvoidance& toCopy);

	mwRobTypes::AxisIDs m_excludedAxis;
	double m_exponent;
	double m_avoidanceZone;
	double m_maximum;
	bool m_isFractional;
	mwRobTypes::AvoidanceZones m_avoidanceZones;
};

class MW_5AXUTIL_API mwJointConstraintAvoidance : public mwOptimization
{
public:
	mwJointConstraintAvoidance();

	virtual ~mwJointConstraintAvoidance();

	virtual const InstanceType GetInstanceType() const;

	void SetAvoidanceZone(const double& value);
	const double GetAvoidanceZone() const;

	void SetExponent(const double& value);
	const double GetExponent() const;

	void SetMaximum(const double& value);
	const double GetMaximum() const;

	void SetIgnoreDefaultJointConstraints(const bool& value);
	const bool IsIgnoreDefaultJointConstraints() const;

	const mwJointConstraintAvoidance& operator=(const mwJointConstraintAvoidance& toCopy);

	const bool operator==(const mwJointConstraintAvoidance& toCompare) const;

	void SetDefaults();

private:
	void Copy(const mwJointConstraintAvoidance& toCopy);

	double m_exponent;
	double m_maximum;
	double m_avoidanceZone;
	bool m_ignoreDefaultJointConstraints;
};

class MW_5AXUTIL_API mwCollisionAvoidance : public mwOptimization
{
public:
	mwCollisionAvoidance();

	virtual ~mwCollisionAvoidance();

	virtual const InstanceType GetInstanceType() const;

	void SetAvoidanceDistance(const double& value);
	const double GetAvoidanceDistance() const;

	void SetExponent(const double& value);
	const double GetExponent() const;

	void SetBoundaryValue(const double& value);
	const double GeBoundaryValue() const;

	void SetCheckSelfCollision(const bool& value);
	const bool IsCheckSelfCollision() const;

	void SetCheckEnvCollisions(const bool& value);
	const bool IsCheckEnvCollisions() const;

	void SetPerturbationValue(const double& value);
	const double GePerturbationValue() const;

	const double GeMaxSearchDistance() const;
	void SetMaxSearchDistance(const double& value);

	const mwCollisionAvoidance& operator=(const mwCollisionAvoidance& toCopy);

	const bool operator==(const mwCollisionAvoidance& toCompare) const;

	void SetDefaults();

private:
	void Copy(const mwCollisionAvoidance& toCopy);

	double m_avoidanceDistance;
	double m_exponent;
	double m_boundaryValue;
	double m_perturbationValue;
	double m_maxSearchDistance;
	bool m_checkSelfCollision;
	bool m_checkEnvCollisions;
};

class MW_5AXUTIL_API mwSingularityAvoidance : public mwOptimization
{
public:
	mwSingularityAvoidance();

	virtual ~mwSingularityAvoidance();

	virtual const InstanceType GetInstanceType() const;

	void SetAvoidanceZone(const double& value);
	const double GetAvoidanceZone() const;

	void SetExponent(const unsigned int& value);
	const unsigned int GetExponent() const;

	void SetMax(const double& value);
	const double GetMax() const;

	const mwRobTypes::AxisWeights& GetInputWeights() const;
	void SetInputWeights(const mwRobTypes::AxisWeights& inputWeights);

	const mwRobTypes::AxisWeights& GetOutputWeights() const;
	void SetOutputWeights(const mwRobTypes::AxisWeights& outputWeights);




	const mwSingularityAvoidance& operator=(const mwSingularityAvoidance& toCopy);

	const bool operator==(const mwSingularityAvoidance& toCompare) const;

	void SetDefaults();

private:
	void Copy(const mwSingularityAvoidance& toCopy);

	mwRobTypes::AxisWeights m_inputWeights;
	mwRobTypes::AxisWeights m_outputWeights;
	double m_avoidanceZone;
	double m_maxValue;
	unsigned int m_exponent;
};

}  // end namespace post
#endif	//	MW_MWROBOTIMIZATIONSPARAMS_HPP_
