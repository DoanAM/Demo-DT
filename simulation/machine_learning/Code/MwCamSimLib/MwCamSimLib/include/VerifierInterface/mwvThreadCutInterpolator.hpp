// (C) 2012-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVTHREADCUTINTERPOLATOR_HPP_
#define MW_MWVTHREADCUTINTERPOLATOR_HPP_
#include "mwVerifierMoves.hpp"
#include "mwVerifierNestedEnums.hpp"
#include "mwvCutInterpolator.hpp"
#include "mwvUtilDefines.hpp"

#include <mwOverrideFinal.hpp>

namespace mw
{
namespace Verifier
{
class ThreadToolTrace;
class OldThreadToolTrace;
}  // namespace Verifier
}  // namespace mw

namespace VerifierUtil
{
/// Interpolates thread cuts, as defined in @ref VerifierUtil::mwThreadMove, or @ref
/// mwMachSimVerifier::BufferedThreadCut().
///
/// @note “World” in class means the “thread cutting” world system, where the tool performs a
/// linear motion along the axis, and the stock turns by a certain angle. It does *not* refer to
/// the stock's coordinate system.
class MW_VERIFIER_API mwvThreadCutInterpolator : public mwvCutInterpolator
{
public:
	/// Constructs the interpolator based on the mwThreadMove definition. This constructor is fully
	/// general. It allows constructing moves with arbitrary sweep angles (i.e. sweep angles of more
	/// than 180 degrees are supported).
	mwvThreadCutInterpolator(
		const mwThreadMove& move,
		const StockSpindleAxis spindleDirection,
		const float3d& spindlePosition = float3d(0, 0, 0));

	/// Constructs the interpolator based on two frames in the stock's world coordinates. The
	/// thread's angles are derived based on the angles of the start and end position relative to
	/// the stock spindle. The thread has to be passed in angle steps smaller than 180 degrees for
	/// this construction method to work.
	mwvThreadCutInterpolator(
		const Frame& startStockFrame,
		const Frame& endStockFrame,
		const StockSpindleAxis spindleDirection,
		const float3d& spindlePosition = float3d(0, 0, 0));

	/// This constructor exists for internal use.
	mwvThreadCutInterpolator(
		const Frame& startWorldFrame,
		const Frame& endWorldFrame,
		const Frame& startStockFrame,
		const Frame& endStockFrame,
		const bool areSpindleAnglesSpecified,
		const float startSpindleAngle,
		const float endSpindleAngle,
		const StockSpindleAxis spindleDirection,
		const float3d& spindlePosition = float3d(0, 0, 0));

	/// @param t time parameter between 0 and 1
	/// @returns the tool frame in stock coordinates.
	Frame GetFrame(const float t) const MW_FINAL;

	/// @warning unimplemented
	float3d GetVelocity(const float t, const float3d& p) const MW_FINAL;

	float GetLength() const MW_FINAL;

	const Frame& GetStartWorldFrame() const { return m_startWorldFrame; }
	const Frame& GetStartStockFrame() const { return m_startStockFrame; }

	const Frame& GetEndWorldFrame() const { return m_endWorldFrame; }
	const Frame& GetEndStockFrame() const { return m_endStockFrame; }

	const StockSpindleAxis GetSpindleDirection() const { return m_spindleDirection; }
	const float3d& GetSpindlePosition() const { return m_spindlePosition; }

	bool AreSpindleAnglesSpecified() const { return m_areSpindleAnglesSpecified; }

	float GetStartSpindleAngle() const { return m_startSpindleAngle; }
	float GetEndSpindleAngle() const { return m_endSpindleAngle; }

	bool IsValid() const;

private:
	void ComputeWorldFrames();
	void ComputeStockFrames();

	friend class mw::Verifier::ThreadToolTrace;  // for serialization
	friend class mw::Verifier::OldThreadToolTrace;  // for serialization

	Frame m_startStockFrame;
	Frame m_endStockFrame;
	Frame m_startWorldFrame;
	Frame m_endWorldFrame;

	bool m_areSpindleAnglesSpecified;
	float m_startSpindleAngle;  // radians
	float m_endSpindleAngle;  // radians

	float3d m_spindlePosition;
	StockSpindleAxis m_spindleDirection;
};
}  // namespace VerifierUtil
#endif  //	MW_MWVTHREADCUTINTERPOLATOR_HPP_
