// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBMOTIONFILTERPARAMS_HPP_
#define MW_MWROBMOTIONFILTERPARAMS_HPP_

#include "mwDllImpExpDef.hpp"
#include <vector>

//#############################################################################
namespace post
{
class mwBaseFilter;
class mwGeneralMotionFilter;
class mwPointMotionFilter;
class mwRotationMotionFilter;
class mwScalarMotionFilter;

class MW_5AXUTIL_API mwBaseFilter
{
public:
	enum VelocityProfileType
	{
		PROPORTIONAL = 0,
		TRAPEZOIDAL = 1,
		THREEHALVES = 2,
		SCURVE = 3
	};

	const double GetSpeedFactor() const;
	void SetSpeedFactor(const double value);

	const double GetExponent() const;
	void SetExponent(const double value);

	void SetUsingVelocityProfileType(const bool value);
	bool IsProfileTypeOn() const;

	void SetVelocityProfileType(const VelocityProfileType& value);
	const VelocityProfileType GetVelocityProfileType() const;

	void SetDefaults();

	const mwBaseFilter& operator=(const mwBaseFilter& toCopy);

	const bool operator==(const mwBaseFilter& toCompare) const;

	mwBaseFilter();

	virtual ~mwBaseFilter();

private:
	void Copy(const mwBaseFilter& toCopy);

	double m_speedFactor;
	double m_exponent;
	bool m_isVelocityProfileOn;
	VelocityProfileType m_velocityProfileType;
};

class MW_5AXUTIL_API mwGeneralMotionFilter : public mwBaseFilter
{
public:
	mwGeneralMotionFilter();

	virtual ~mwGeneralMotionFilter();

	const mwGeneralMotionFilter& operator=(const mwGeneralMotionFilter& toCopy);

	mwGeneralMotionFilter(const mwGeneralMotionFilter& toCopy);

	void Copy(const mwGeneralMotionFilter& toCopy);

	const double GetAngularAccelerationThreshold() const;
	void SetAngularAccelerationThreshold(const double value);

	const double GetLinearAccelerationThreshold() const;
	void SetLinearAccelerationThreshold(const double value);

	const double GetAngularDecelerationThreshold() const;
	void SetAngularDecelerationThreshold(const double value);

	const double GetLinearDecelerationThreshold() const;
	void SetLinearDecelerationThreshold(const double value);

	const double GetAngularJerkThreshold() const;
	void SetAngularJerkThreshold(const double value);

	const double GetLinearJerkThreshold() const;
	void SetLinearJerkThreshold(const double value);

	const double GetAngularVelocityThreshold() const;
	void SetAngularVelocityThreshold(const double value);

	const double GetLinearVelocityThreshold() const;
	void SetLinearVelocityThreshold(const double value);

private:
	double m_angularAccelerationThreshold;
	double m_angularDecelerationThreshold;

	double m_linearAccelerationThreshold;
	double m_linearDecelerationThreshold;

	double m_angularJerkThreshold;
	double m_linearJerkThreshold;

	double m_angularVelocityThreshold;
	double m_linearVelocityThreshold;
};

class MW_5AXUTIL_API mwPointMotionFilter : public mwBaseFilter
{
public:
	mwPointMotionFilter();

	virtual ~mwPointMotionFilter();

	const mwPointMotionFilter& operator=(const mwPointMotionFilter& toCopy);

	mwPointMotionFilter(const mwPointMotionFilter& toCopy);

	void Copy(const mwPointMotionFilter& toCopy);

	const double GetAccelerationThreshold() const;
	void SetAccelerationThreshold(const double value);

	const double GetDecelerationThreshold() const;
	void SetDecelerationThreshold(const double value);

	const double GetJerkThreshold() const;
	void SetJerkThreshold(const double value);

private:
	double m_accelerationThreshold;
	double m_decelerationThreshold;
	double m_jerkThreshold;
};

class MW_5AXUTIL_API mwRotationMotionFilter : public mwBaseFilter
{
public:
	mwRotationMotionFilter();

	virtual ~mwRotationMotionFilter();

	const mwRotationMotionFilter& operator=(const mwRotationMotionFilter& toCopy);

	mwRotationMotionFilter(const mwRotationMotionFilter& toCopy);

	void Copy(const mwRotationMotionFilter& toCopy);

	const double GetAngularAccelerationThreshold() const;
	void SetAngularAccelerationThreshold(const double value);

	const double GetAngularDecelerationThreshold() const;
	void SetAngularDecelerationThreshold(const double value);

	const double GetAngularJerkThreshold() const;
	void SetAngularJerkThreshold(const double value);

	const double GetAngularVelocityThreshold() const;
	void SetAngularVelocityThreshold(const double value);

private:
	double m_angularAccelerationThreshold;
	double m_angularDecelerationThreshold;
	double m_angularJerkThreshold;
	double m_angularVelocityThreshold;
};

class MW_5AXUTIL_API mwScalarMotionFilter : public mwBaseFilter
{
public:
	mwScalarMotionFilter();

	virtual ~mwScalarMotionFilter();

	const mwScalarMotionFilter& operator=(const mwScalarMotionFilter& toCopy);

	mwScalarMotionFilter(const mwScalarMotionFilter& toCopy);

	void Copy(const mwScalarMotionFilter& toCopy);

	const double GetAccelerationThreshold() const;
	void SetAccelerationThreshold(const double value);

	const double GetDecelerationThreshold() const;
	void SetDecelerationThreshold(const double value);

	const double GetJerkThreshold() const;
	void SetJerkThreshold(const double value);

private:
	double m_accelerationThreshold;
	double m_decelerationThreshold;
	double m_jerkThreshold;
};
}  // end namespace post
#endif	//	MW_MWROBMOTIONFILTERPARAMS_HPP_
