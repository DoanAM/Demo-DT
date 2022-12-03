// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBPOSITIONCONTROLSYSPARAMS_HPP_
#define MW_MWROBPOSITIONCONTROLSYSPARAMS_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwRobVelocityCtrlDefParams.hpp"

//#############################################################################
namespace post
{
class MW_5AXUTIL_API mwPositionControlSystem
{
public:
	mwPositionControlSystem();
	~mwPositionControlSystem();

	enum CollisionAvoindaceMode
	{
		NONE = 0,
		SYSTEM_COLLISION_AVOIDANCE,
		MANIPULATOR_COLLISION_AVOIDANCE,
	};

	void SetTimeStepInSec(const double& value);
	const double GetTimeStepInSec() const;

	void SetCollisionAvoidanceMode(const CollisionAvoindaceMode& newMode);
	const CollisionAvoindaceMode& GetCollisionAvoidanceMode() const;

	const double GetCollisionStoppingThreshold() const;
	void SetCollisionStoppingThreshold(const double& value);

	void SetUsingSinglePass(const bool value);
	bool IsUsingSinglePass() const;

	void SetDefaults();

	const mwPositionControlSystem& operator=(const mwPositionControlSystem& toCopy);

	const bool operator==(const mwPositionControlSystem& toCompare) const;

private:
	void Copy(const mwPositionControlSystem& toCopy);

	double m_timeStepInSec;
	double m_collStoppingThreshold;
	CollisionAvoindaceMode m_collAvoidanceMode;
	bool m_isSinglePassOn;
};

class MW_5AXUTIL_API mwPositionControlSystemProperties
{
public:
	mwPositionControlSystemProperties();

	const mwPositionControlSystemProperties& operator=(
		const mwPositionControlSystemProperties& toCopy);

	const bool operator==(const mwPositionControlSystemProperties& toCompare) const;

	const mwPositionControlSystem& GetPositionControlSystem() const;
	void SetPositionControlSystem(const mwPositionControlSystem& newPositionControlSystem);

	const misc::mwstring& GetActiveVelCtrlDefID() const;
	void SetActiveVelCtrlDefID(const misc::mwstring& newId);

	const mwVelocityCtrlDefContainer& GetVelocityCtrlDefContainer() const;
	void SetVelocityCtrlDefContainer(const mwVelocityCtrlDefContainer& velCtrDefContainer);

	void SetDefaults();

private:
	void Copy(const mwPositionControlSystemProperties& toCopy);

	mwPositionControlSystem m_positionControlSys;
	mwVelocityCtrlDefContainer m_velCtrlDefContainer;
	misc::mwstring m_activeVelCtrlDefID;
};

}  // end namespace post
#endif	//	MW_MWROBPOSITIONCONTROLSYSPARAMS_HPP_
