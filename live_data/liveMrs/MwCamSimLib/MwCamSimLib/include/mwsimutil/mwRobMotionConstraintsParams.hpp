// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBMOTIONCONSTRAINTPARAMS_HPP_
#define MW_MWROBMOTIONCONSTRAINTPARAMS_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwRobCoordinateSystemTransformation.hpp"
#include "mwRobMotionFiltersParams.hpp"
#include "mwRobTypes.hpp"

#include <vector>
//#############################################################################
namespace post
{
class mwEndEffector;
class mwFreeSpinInZ;
class mwFrame;
class mwPoint;
class mwLinear;
class mwXY;
class mwGeneralSpatial;
class mwCoordinatedJoint;

class MW_5AXUTIL_API mwConstraintVisitor
{
public:
	mwConstraintVisitor();
	virtual ~mwConstraintVisitor();
	virtual void Visit(const mwEndEffector& visitor);
	virtual void Visit(const mwFreeSpinInZ& visitor);
	virtual void Visit(const mwFrame& visitor);
	virtual void Visit(const mwPoint& visitor);
	virtual void Visit(const mwLinear& visitor);
	virtual void Visit(const mwXY& visitor);
	virtual void Visit(const mwGeneralSpatial& visitor);
	virtual void Visit(const mwCoordinatedJoint& visitor);
	
protected:
	virtual void Default();
};

class MW_5AXUTIL_API mwBaseEndEffector
{
public:
	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const = 0;

	virtual ~mwBaseEndEffector(){};
};

class MW_5AXUTIL_API mwEndEffector : public mwBaseEndEffector
{
public:
	enum MotionConstraintType
	{
		FREE_SPIN_IN_Z_END_EFFECTOR = 0,
		POINT_END_EFFECTOR = 1,
		FRAME_END_EFFECTOR = 2,
		LINEAR_CONSTRAINT_END_EFFECTOR = 3,
		XY_CONSTRAINT_END_EFFECTOR = 4,
		GENERAL_SPATIAL_END_EFFECTOR = 5,
		COORDINATED_JOINT_END_EFFECTOR = 6
	};

	mwEndEffector();

	virtual ~mwEndEffector();

	const mwEndEffector& operator=(const mwEndEffector& toCopy);

	mwEndEffector(const mwEndEffector& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	void Copy(const mwEndEffector& toCopy);

	void SetHardConstraint(const bool value);
	bool IsHardConstraint() const;

	bool IsAllowChangingDesiredPlacement() const;
	void SetAllowChangingDesiredPlacement(const bool value);

	const post::mwRobCoordinateSystemTransformation& GetLockedPlacement() const;
	void SetLockedPlacement(const post::mwRobCoordinateSystemTransformation& value);

	void SetAxisIDRelatedWith(const misc::mwstring value);
	misc::mwstring GetAxisIDRelatedWith() const;

	void SetAxisIDToSyncWith(const misc::mwstring value);
	misc::mwstring GetAxisIDToSyncWith() const;

	void SetCustomCoordSysInfo(const mwRobTypes::CustomCoordSysInfo& value);
	const mwRobTypes::CustomCoordSysInfo& GetCustomCoordSysInfo() const;

private:
	bool m_isHardConstraint;
	bool m_isAllowChangingDesiredPlacement;
	post::mwRobCoordinateSystemTransformation m_lockedPlacement;
	misc::mwstring m_axisId;
	misc::mwstring m_axisToSync;
	mwRobTypes::CustomCoordSysInfo m_customCoordSysInfo;
};

class MW_5AXUTIL_API mwFreeSpinInZ : public mwEndEffector
{
public:
	mwFreeSpinInZ(){};

	virtual ~mwFreeSpinInZ();

	const mwFreeSpinInZ& operator=(const mwFreeSpinInZ& toCopy);

	mwFreeSpinInZ(const mwFreeSpinInZ& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwGeneralMotionFilter& GetMotionFilter() const;

	void SetMotionFilter(const mwGeneralMotionFilter& filter);

private:
	mwGeneralMotionFilter m_generalMotionFilter;
};

class MW_5AXUTIL_API mwFrame : public mwEndEffector
{
public:
	mwFrame(){};

	virtual ~mwFrame();

	const mwFrame& operator=(const mwFrame& toCopy);

	mwFrame(const mwFrame& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwGeneralMotionFilter& GetMotionFilter() const;

	void SetMotionFilter(const mwGeneralMotionFilter& filter);

private:
	mwGeneralMotionFilter m_generalMotionFilter;
};

class MW_5AXUTIL_API mwPoint : public mwEndEffector
{
public:
	mwPoint(){};

	virtual ~mwPoint();

	const mwPoint& operator=(const mwPoint& toCopy);

	mwPoint(const mwPoint& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwPointMotionFilter& GetMotionFilter() const;

	void SetMotionFilter(const mwPointMotionFilter& filter);

private:
	mwPointMotionFilter m_pointMotionFilter;
};

class MW_5AXUTIL_API mwLinear : public mwEndEffector
{
public:
	mwLinear(){};

	virtual ~mwLinear();

	const mwLinear& operator=(const mwLinear& toCopy);

	mwLinear(const mwLinear& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwRobTypes::mwRobTypes::AxisIDs& GetConstrainedAxis() const;
	void SetConstrainedAxis(const mwRobTypes::mwRobTypes::AxisIDs& axisIDs);

	const mwRobTypes::Weights& GetConstrainedAxisWeights() const;
	void SetConstrainedAxisWeights(const mwRobTypes::Weights& constrainedAxisWeights);

	const mwScalarMotionFilter& GetMotionFilter() const;
	void SetMotionFilter(const mwScalarMotionFilter& filter);

private:
	mwRobTypes::mwRobTypes::AxisIDs		m_constrainedAxis;
	mwRobTypes::Weights		m_constrainedAxisWeights;
	mwScalarMotionFilter	m_scalarMotionFilter;
};

class MW_5AXUTIL_API mwXY : public mwEndEffector
{
public:
	mwXY(){};

	virtual ~mwXY();

	const mwXY& operator=(const mwXY& toCopy);

	mwXY(const mwXY& toCopy);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwPointMotionFilter& GetMotionFilter() const;

	void SetMotionFilter(const mwPointMotionFilter& filter);

private:
	mwPointMotionFilter m_pointMotionFilter;
};

class MW_5AXUTIL_API mwGeneralSpatial : public mwEndEffector
{
public:
	using ConstraintFlags = std::vector<bool>;

	mwGeneralSpatial();

	virtual ~mwGeneralSpatial();

	const mwGeneralSpatial& operator=(const mwGeneralSpatial& toCopy);

	mwGeneralSpatial(const mwGeneralSpatial& toCopy);

	bool IsConstraintAvailable();

	void SetConstraintFlags(const ConstraintFlags& value);
	const ConstraintFlags& GetConstraintFlags() const;

	bool IsCoordinateSystemRelativToEndEffector() const;

	void SetCoordinateSystemRelativToEndEffector(const bool value);

	bool IsActualOrDesired() const;

	void SetActualOrDesired(const bool value);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

	const mwGeneralMotionFilter& GetMotionFilter() const;

	void SetMotionFilter(const mwGeneralMotionFilter& filter);

private:

	bool m_isCoordSystemRelativToEE;
	bool m_isActualOrDesired;
	ConstraintFlags m_constraintFlags;
	mwGeneralMotionFilter m_generalMotionFilter;
};

class MW_5AXUTIL_API mwCoordinatedJoint : public mwEndEffector
{
public:

	mwCoordinatedJoint();

	virtual ~mwCoordinatedJoint();

	const mwCoordinatedJoint& operator=(const mwCoordinatedJoint& toCopy);

	mwCoordinatedJoint(const mwCoordinatedJoint& toCopy);

	const mwRobTypes::AxisIDs& GetAxisNames() const;
	void SetAxisNames(const mwRobTypes::AxisIDs& value);

	const mwRobTypes::AxisIDs& GeIndependetAxisNames() const;
	void SetIndependetAxisNames(const mwRobTypes::AxisIDs& value);

	virtual void AcceptVirtual(mwConstraintVisitor& visitor) const;

private:

	mwRobTypes::AxisIDs m_axisNames;
	mwRobTypes::AxisIDs m_independetAxisNames;
};

}  // end namespace post
#endif	//	MW_MWROBMOTIONCONSTRAINTPARAMS_HPP_
