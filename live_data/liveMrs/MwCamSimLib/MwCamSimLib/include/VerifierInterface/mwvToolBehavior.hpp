// (C) 2017-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVTOOLBEHAVIOR_HPP_
#define MW_MWVTOOLBEHAVIOR_HPP_
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
struct mwExperimentalMethods;

/// Simulation settings for one tool-element (flute, shaft, arbor, holder)
struct mwvToolElementBehavior
{
	/// Constructor which sets "don't simulate tool at all", if no parameters passed
	inline mwvToolElementBehavior(
		const bool removesMaterial = false,
		const bool isCollisionChecked = false,
		const bool rapidCollisionReportSuppressed = false,
		const bool simulateHoles = false,
		const bool simulateThicknessInTurning = false,
		const bool isSafetyDistanceChecked = false,
		const bool addMaterial = false,
		const bool paintMaterial = false)
		: RemovesMaterial(removesMaterial),
		  IsCollisionChecked(isCollisionChecked),
		  RapidCollisionReportSuppressed(rapidCollisionReportSuppressed),
		  SimulateHoles(simulateHoles),
		  SimulateThicknessInTurning(simulateThicknessInTurning),
		  IsSafetyDistanceChecked(isSafetyDistanceChecked),
		  AddMaterial(addMaterial),
		  PaintMaterial(paintMaterial)
	{
	}

	/// If true, then the tool-element removes material from the stock.
	bool RemovesMaterial;

	/// If true, then the tool-element signals a collision if it hits the material.
	/// @sa SetCollisionTolerance, VerificationCodes
	bool IsCollisionChecked;

	/// If true, then a rapid collision is no longer reported (but still shown on stock material).
	///
	/// - That means, eg. Cut() won't return the code for rapid-crash anymore.
	bool RapidCollisionReportSuppressed;

	/// Support revolved tools with holes in the middle
	///
	/// - If disabled, revolved tools are closed towards the tool-axis, that is holes in the middle
	///   are closed.
	/// - This is done for performance reasons, because holes prevent some major optimizations. This
	///   bool enables exact simulation of these tools but decreases simulation speed.
	bool SimulateHoles;

	/// If true, thickness of extruded lathe-tools will be considered in cutting and
	/// collision-checking.
	///
	/// ATTENTION: This option will be removed in the future, when using thickness becomes default.
	bool SimulateThicknessInTurning;

	/// If true, then the tool-element signals a collision if it does not keep the safety distance
	/// to the workpiece.
	///
	/// This may slow down simulation-performance, especially for the 3-axis-model.
	bool IsSafetyDistanceChecked;

	/// If true, then the tool-element adds material to the stock.
	///
	/// If AddMaterial and RemovesMaterial are both true, then the tool part will not change any
	/// material.
	bool AddMaterial;

	/// If true, then the tool-element just paints material on the stock.
	///
	/// If AddMaterial or RemovesMaterial is true, then this flag is ignored.
	bool PaintMaterial;

	bool operator==(const mwvToolElementBehavior& other) const
	{
		return RemovesMaterial == other.RemovesMaterial &&
			IsCollisionChecked == other.IsCollisionChecked &&
			RapidCollisionReportSuppressed == other.RapidCollisionReportSuppressed &&
			SimulateHoles == other.SimulateHoles &&
			SimulateThicknessInTurning == other.SimulateThicknessInTurning &&
			IsSafetyDistanceChecked == other.IsSafetyDistanceChecked &&
			AddMaterial == other.AddMaterial && PaintMaterial == other.PaintMaterial;
	}

	bool operator!=(const mwvToolElementBehavior& other) const { return !(*this == other); }
};

struct mwvEccentricToolSpindle
{
	enum EccentricToolSpindleMode
	{
		ECCENTRIC_TOOL_SPINDLE_OFF = 0,
		ECCENTRIC_TOOL_SPINDLE_ON = 1
	};

	mwvEccentricToolSpindle() : mode(ECCENTRIC_TOOL_SPINDLE_OFF) {}

	mwvEccentricToolSpindle(
		const EccentricToolSpindleMode mode,
		const cadcam::mwPoint3df& position,
		const cadcam::mwPoint3df& direction)
		: mode(mode), axisPosition(position), axisDirection(direction)
	{
	}

	bool operator==(const mwvEccentricToolSpindle& other) const
	{
		return mode == other.mode && axisPosition == other.axisPosition &&
			axisDirection == other.axisDirection;
	}

	bool operator!=(const mwvEccentricToolSpindle& other) const { return !(*this == other); }


	EccentricToolSpindleMode mode;
	cadcam::mwPoint3df axisPosition;
	cadcam::mwPoint3df axisDirection;
};

/// Simulation behavior for a tool, including 4 tool-element-types.
struct mwvToolBehavior
{
	/// Behavior for the flute / cutting-edge.
	mwvToolElementBehavior Flute;
	/// Behavior for the shaft / non-cutting-edge.
	mwvToolElementBehavior Shaft;
	/// Behavior for the arbor.
	mwvToolElementBehavior Arbor;
	/// Behavior for the holder.
	mwvToolElementBehavior Holder;

	/// Setting an eccentric tool spindle switches the tool to "eccentric turning" mode. All moves
	/// for this tool are interpreted as if the tool moves normally, but the stock rotates
	/// infinitely fast around the given axis. The stock is shown in the opposite perspective
	/// though, where the stock is static and the tool rotates infinitely fast.
	inline void SetEccentricToolSpindle(const mwvEccentricToolSpindle& spindle)
	{
		m_spindle = spindle;
	}

	/// @see SetEccentricToolSpindle
	inline const mwvEccentricToolSpindle& GetEccentricToolSpindle() const { return m_spindle; }

	enum FiveAxisCuttingToleranceMode
	{
		CUTTING_TOLERANCE_ONLY_FOR_TOOL_TIP = 1,
		CUTTING_TOLERANCE_FOR_FULL_TOOL = 2
	};
	/// This will change the way how the cutting tolerance is used @sa
	/// mwMachSimVerifier::SetCuttingTolerance()
	///
	/// Usually the cutting tolerance is only applied to the tip of the tool for speed reasons.
	/// CUTTING_TOLERANCE_FOR_FULL_TOOL will make sure that it is applied to the whole tool. This
	/// may slow down the simulation when the tool is moving closely to the material. For speed
	/// reasons it is off by default.
	void Set5AxisCuttingToleranceMode(const FiveAxisCuttingToleranceMode mode)
	{
		m_5AxisCuttingToleranceMode = mode;
	}

	/// @see Set5AxisCuttingToleranceMode()
	FiveAxisCuttingToleranceMode Get5AxisCuttingToleranceMode() const
	{
		return m_5AxisCuttingToleranceMode;
	}

	/// If PaintMaterial is enabled, this determines the direction of paint application to the
	/// surface.
	///
	/// If zero, the paint is applied to all surfaces intersected by the tool. Otherwise surfaces
	/// that are occluded when looking in the paint direction will not get painted.
	void SetPaintDirection(const cadcam::mwPoint3df& direction) { m_paintDirection = direction; }

	/// @see SetPaintDirection()
	inline const cadcam::mwPoint3df& GetPaintDirection() const { return m_paintDirection; }

	inline mwvToolBehavior()
		: m_5AxisCuttingToleranceMode(CUTTING_TOLERANCE_ONLY_FOR_TOOL_TIP),
		  m_paintDirection(cadcam::mwPoint3df(0, 0, -1)){};

	bool operator==(const mwvToolBehavior& other) const
	{
		return Flute == other.Flute && Shaft == other.Shaft && Arbor == other.Arbor &&
			Holder == other.Holder &&
			m_5AxisCuttingToleranceMode == other.m_5AxisCuttingToleranceMode &&
			m_spindle == other.m_spindle && m_paintDirection == other.m_paintDirection;
	}

	inline bool operator!=(const mwvToolBehavior& other) const { return !(*this == other); }

private:
	FiveAxisCuttingToleranceMode m_5AxisCuttingToleranceMode;
	mwvEccentricToolSpindle m_spindle;
	cadcam::mwPoint3df m_paintDirection;
};

}  // namespace VerifierUtil
#endif  //	MW_MWVTOOLBEHAVIOR_HPP_
