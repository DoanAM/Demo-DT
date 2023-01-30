// (C) 2015-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVERIFIERMOVES_HPP_
#define MW_MWVERIFIERMOVES_HPP_
#include "mwVerifierDllDefinition.hpp"
#include "mwVerifierNestedEnums.hpp"

#include <mwMathUtilities.hpp>
#include <mwOverrideFinal.hpp>

namespace boost
{
namespace serialization
{
class access;
}
}  // namespace boost

#pragma warning(push)
#pragma warning(disable : 4251)  // needs to have dll-interface to be used by clients of class

namespace VerifierUtil
{
class mwMoveVisitor;

class MW_VERIFIER_API mwMove
{
public:
	typedef MATH::Frame<float> Frame;
	typedef MATH::Quaternion<float> Quaternion;
	typedef cadcam::mwTPoint3d<float> Vector3d;

	virtual ~mwMove();
	virtual void Accept(mwMoveVisitor& visitor) const;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);
};

/// Defines a linear move/cut. For a detailed explanation see the developer guide
/// at @ref CutSim_Tool_moves.
///
/// To interpolate this move definition in your integration have a look at @ref
/// mwvLinearCutInterpolator.
class MW_VERIFIER_API mwLinearMove : public mwMove
{
public:
	mwLinearMove(const Frame& startFrame = Frame(), const Frame& endFrame = Frame());
	const Frame& GetStartFrame() const;
	const Frame& GetEndFrame() const;
	void SetStartFrame(const Frame& f);
	void SetEndFrame(const Frame& f);
	bool IsValid() const;
	void Accept(mwMoveVisitor& visitor) const MW_OVERRIDE;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);

	Frame m_startFrame;
	Frame m_endFrame;
};

/// Defines a circular sweep move (a.k.a. arc cut). For a detailed explanation see the developer
/// guide at @ref CutSim_Circular_moves.
///
/// To interpolate this move definition in your integration have a look at @ref
/// mwvArcCutInterpolator.
///
/// Internally, circular moves are interpolated using an internally computed error tolerance. To set
/// an upper limit to this tolerance, use @ref mwMachSimVerifier::SetCuttingTolerance().
class MW_VERIFIER_API mwCircularMove : public mwMove
{
public:
	mwCircularMove(
		const Frame& startFrame = Frame(),
		const Frame& endFrame = Frame(),
		const Vector3d& circleCenter = Vector3d(),
		const Vector3d& circlePlaneNormal = Vector3d());
	const Frame& GetStartFrame() const;
	const Frame& GetEndFrame() const;
	const Vector3d& GetCircleCenter() const;
	const Vector3d& GetCirclePlaneNormal() const;
	void SetStartFrame(const Frame& f);
	void SetEndFrame(const Frame& f);
	void SetCircleCenter(const Vector3d& v);
	void SetCirclePlaneNormal(const Vector3d& v);
	bool IsValid() const;
	void Accept(mwMoveVisitor& visitor) const MW_OVERRIDE;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);

	Frame m_startFrame;
	Frame m_endFrame;
	Vector3d m_circleCenter;
	Vector3d m_circlePlaneNormal;
};

/// Like @ref mwCircularMove but defined using a sweep angle instead of two points.
class MW_VERIFIER_API mwCircularSweepMove : public mwMove
{
public:
	mwCircularSweepMove(
		const Frame& startFrame = Frame(),
		const float sweepAngle = 0,
		const Vector3d& circleCenter = Vector3d(),
		const Vector3d& circlePlaneNormal = Vector3d(),
		const float heightChange = 0,
		const float radiusChange = 0);
	const Frame& GetStartFrame() const;
	float GetSweepAngle() const;
	const Vector3d& GetCircleCenter() const;
	const Vector3d& GetCirclePlaneNormal() const;
	float GetHeightChange() const;
	float GetRadiusChange() const;
	void SetStartFrame(const Frame& v);
	void SetSweepAngle(const float v);
	void SetCircleCenter(const Vector3d& v);
	void SetCirclePlaneNormal(const Vector3d& v);
	void SetHeightChange(const float v);
	void SetRadiusChange(const float v);
	void Accept(mwMoveVisitor& visitor) const MW_OVERRIDE;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);

	Frame m_startFrame;
	float m_sweepAngle;
	Vector3d m_circleCenter;
	Vector3d m_circlePlaneNormal;
	float m_heightChange;
	float m_radiusChange;
};

/// Defines a thread move/cut. For a detailed explanation see the developer guide at @ref
/// CutSim_Thread_moves.
///
/// The thread cutting "world" assumes that the tool performs a linear cut along the stock spindle
/// axis, while the stock turns from `startSpindleAngle` to `endSpindleAngle` at the same time.
/// `startFrame` and `endFrame` are defined in the thread cutting world, not in stock world
/// coordinates.
///
/// To interpolate this move definition in your integration have a look at @ref
/// mwvThreadCutInterpolator.
class MW_VERIFIER_API mwThreadMove : public mwLinearMove
{
public:
	/// @param [in] startFrame The start position in world coordinates.
	/// @param [in] endFrame The end position in world coordinates.
	/// @param [in] startSpindleAngle The angular position of the spindle in the start position in
	///             radians.
	/// @param [in] endSpindleAngle The angular position of the spindle in the end position in
	///             radians.
	mwThreadMove(
		const Frame& startFrame = Frame(),
		const Frame& endFrame = Frame(),
		const float startSpindleAngle = 0,
		const float endSpindleAngle = 0);

	float GetStartSpindleAngle() const;
	float GetEndSpindleAngle() const;
	void SetStartSpindleAngle(const float angle);
	void SetEndSpindleAngle(const float angle);

	/// Checks if the move definition is valid. The definition is invalid if there are 180 degree
	/// orientation changes, which make it non-obvious how to interpolate between start and end
	/// position. If this method returns false you can not use it in the simulation. In case that
	/// happens try to pass it in smaller steps.
	bool IsValid(
		const StockSpindleAxis spindleAxis,
		const cadcam::mwTPoint3d<float>& spindlePosition = cadcam::mwTPoint3d<float>(0, 0, 0));

	void Accept(mwMoveVisitor& visitor) const MW_OVERRIDE;

private:
	using mwLinearMove::IsValid;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);

	float m_startSpindleAngle;
	float m_endSpindleAngle;
};

/// Defines a wire quad. For a detailed explanation see the developer guide at @ref
/// CutSim_Wire_moves.
///
/// The Wire quad can be used to simulate wire cutting. It assumes that the wire connects a "low"
/// and a "high" point, which both move linearly and with constant speed.
///
/// The wire sweep is simulated as the quad that connects startPointLow, endPointLow, endPointHigh,
/// startPointHigh (in that order).
///
/// To use this move type you have to assign a special wire tool. It must only define a single @ref
/// cadcam::mwWireSolidDefinition as a cutting part, and may not have any other tool parts (like
/// arbor, holder). The length specified in the tool definition is ignored, only the thickness is
/// used.
///
/// The advantage of this API over mwLinearMove with wire planes is, that it's much more predictable
/// what happens when the stock is rotating. You can't get the "wire cut can't be parallel to the
/// wire plane" exception when using this API.
class MW_VERIFIER_API mwWireQuadMove : public mwMove
{
public:
	mwWireQuadMove();
	mwWireQuadMove(
		const Vector3d& startPointLow,
		const Vector3d& startPointHigh,
		const Vector3d& endPointLow,
		const Vector3d& endPointHigh);

	const Vector3d& GetStartPointLow() const;
	const Vector3d& GetStartPointHigh() const;

	const Vector3d& GetEndPointLow() const;
	const Vector3d& GetEndPointHigh() const;

	void Accept(mwMoveVisitor& visitor) const MW_OVERRIDE;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version);

	Vector3d m_startPointLow;
	Vector3d m_startPointHigh;
	Vector3d m_endPointLow;
	Vector3d m_endPointHigh;
};


/// Part of the visitor pattern, used internally
class mwMoveVisitor
{
public:
	virtual void Visit(const mwMove&) = 0;
	virtual void Visit(const mwLinearMove&) = 0;
	virtual void Visit(const mwCircularMove&) = 0;
	virtual void Visit(const mwCircularSweepMove&) = 0;
	virtual void Visit(const mwThreadMove&) = 0;
	virtual void Visit(const mwWireQuadMove&) = 0;
};

}  // namespace VerifierUtil

#pragma warning(pop)

#endif  //	MW_MWVERIFIERMOVES_HPP_
