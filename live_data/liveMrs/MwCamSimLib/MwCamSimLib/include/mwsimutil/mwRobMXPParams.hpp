// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBPARAM_HPP_
#define MW_MWROBPARAM_HPP_

#include "mwDllImpExpDef.hpp"
#include <mwTPoint3d.hpp>
#include "mwUnitsFactory.hpp"
#include "mwMeasurable.hpp"
#include "mwRobCoordinateSystemTransformation.hpp"
#include "mwRobMotionConstraintsParams.hpp"
#include "mwRobPositionControlSysParams.hpp"

#include <vector>

//#############################################################################
namespace post
{
class MW_5AXUTIL_API mwRobMXPParams
{
public:
	enum MovesBufferMode
	{
		ABORTING = 0,
		BUFFERED,
		BLENDING_NEXT
	};

	enum TransitionMode
	{
		TM_CORNER_DISTANCE
	};

	enum CalculationSpeedMode
	{
		FULL = 0,
		OPTIMIZED,
		FAST
	};

	//#############################################################################
	using Units = measures::mwUnitsFactory::Units;
	using PositionControlSysPropsPtr = misc::mwAutoPointer<mwPositionControlSystemProperties>;
	using EndEfectorPtr = misc::mwAutoPointer<mwEndEffector>;
	using EndEffectorInfo = std::pair<mwEndEffector::MotionConstraintType, EndEfectorPtr>;
	using EndEffectors = std::vector<EndEffectorInfo>;
	using CoordinateSystem = std::pair<misc::mwstring, post::mwRobCoordinateSystemTransformation>;
	using CoordinateSystems = std::vector<CoordinateSystem>;
	using Axisinfo = std::pair<misc::mwstring, double>;
	using StartPosition = std::vector<Axisinfo>;
	//#############################################################################

	mwRobMXPParams(const Units units = measures::mwUnitsFactory::METRIC);

	mwRobMXPParams(const mwRobMXPParams& toCopy);

	const mwRobMXPParams& operator=(const mwRobMXPParams& toCopy);

	const bool operator==(const mwRobMXPParams& toCompare) const;

	void Default();

	void SetAccelerationFactor(const double value);
	const double GetAccelerationFactor() const;

	void SetDecelerationFactor(const double value);
	const double GetDecelerationFactor() const;

	void SetJerkFactor(const double value);
	const double GetJerkFactor() const;

	const double GetSpeedFactor() const;
	void SetSpeedFactor(const double value);

	void SetTransitionParam(const double value);
	const double GetTransitionParam() const;

	void SetMotionConstraintType(const mwEndEffector::MotionConstraintType& prop);
	mwEndEffector::MotionConstraintType GetMotionConstraintType() const;

	void SetBufferMode(const MovesBufferMode& prop);
	mwRobMXPParams::MovesBufferMode GetBufferMode() const;

	void SetCalculationSpeedMode(const CalculationSpeedMode& prop);
	mwRobMXPParams::CalculationSpeedMode GetCalculationSpeedMode() const;

	void SetIntermediaryPositions(const bool value);
	const bool IsIntermediaryPositions() const;

	void SetEnableCollisionChecking(const bool value);
	const bool IsCollisionCheckingOn() const;

	void SetTransitionMode(const TransitionMode& prop);
	mwRobMXPParams::TransitionMode GetTransitionMode() const;

	void SetABOn(const bool value);
	const bool IsABOn() const;

	void SetIsFeedRateInterpolation(const bool value);
	const bool IsFeedRateInterpolation() const;

	void AddEndEffector(
		const mwEndEffector::MotionConstraintType constraintType, EndEfectorPtr value);
	void SetEndEffectors(const post::mwRobMXPParams::EndEffectors& endEffectors);

	const EndEffectors& GetEndEffectors() const;
	void ClearEndEffectors();

	const CoordinateSystems& GetCoordinateSystems() const;
	void SetGetCoordinateSystems(const CoordinateSystems& coordinateSystems);
	void AddCoordinateSystems(
		const misc::mwstring& id,
		const post::mwRobCoordinateSystemTransformation& coordinateSystem);

	const StartPosition& GetStartPosition() const;
	void SetStartPosition(const StartPosition& startPosition);
	void AddStartPosition(const misc::mwstring& id, const double& axisValue);

	void SetShowStartPositions(const bool value);
	const bool IsShowStartPositions() const;

	const PositionControlSysPropsPtr& GetPositionControlSysProps() const;
	void SetPositionControlSysProps(const PositionControlSysPropsPtr& newPositionControlSysProps);

	void DefaultEndEffector();

	void SetIsEulerAngleRelativeOutput(const bool value);
	const bool IsEulerAngleRelativeOutput() const;

private:
#pragma warning(push)
#pragma warning(disable : 4251)
	//#############################################################################
	mwEndEffector::MotionConstraintType m_motionConstraintType;

	PositionControlSysPropsPtr m_positionControlSysPropsPtr;

	MovesBufferMode m_movesBufferMode;

	TransitionMode m_transitionMode;

	CalculationSpeedMode m_calculationSpeedMode;

	double m_speedFactor;
	double m_transitonParam;
	double m_accelerationFactor;
	double m_decelerationFactor;
	double m_jerkFactor;

	bool m_isIntermediaryPositions;
	bool m_isCollisionCheckingOn;
	bool m_isFastestMode;
	bool m_isSimplifyMode;
	bool m_useAB;
	bool m_showStartPositions;
	bool m_isFeedRateInterpolation;
	bool m_isEulerAngleRelativeOutput;

	CoordinateSystems m_coordinateSystems;

	StartPosition m_startPosition;

	EndEffectors m_endEffectors;

	Units m_units;

	//#############################################################################
	void Copy(const mwRobMXPParams& toCopy);
#pragma warning(pop)
	//#############################################################################
};

}  // end namespace post
#endif	//	MW_MWROBPARAM_HPP_
