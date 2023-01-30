// (C) 2012-2020 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWVKINEMATICUTILS_HPP_
#define MW_MWVKINEMATICUTILS_HPP_
#include "mwVerifierDllDefinition.hpp"

#include <mwAutoPointer.hpp>
#include <mwMathUtilitiesDefinitions.hpp>  // for Frame, mwHomogenousMatrix
#include <mwTPoint3d.hpp>

namespace VerifierUtil
{
class mwvThreadStep;

/// Interpolate thread cuts used in @ref mwMachSimVerifier::ThreadCut() or @ref
/// mwMachSimVerifier::BufferedThreadCut() or for toolpath display.
class MW_VERIFIER_API mwvKinematicUtils
{
public:
	/// Turning spindle axis direction
	enum Axis
	{
		X_AXIS = 0,
		Y_AXIS = 1,
		Z_AXIS = 2
	};

	typedef cadcam::mwHomogenousMatrix mwRotationMatrix;
	typedef cadcam::mwTPoint3d<float> Point;
	typedef Point Vec3;
	typedef MATH::Frame<float> Frame;
	typedef Frame::Quaternion Quaternion;
	typedef misc::mwAutoPointer<Quaternion> QuaternionPtr;

	////////////////////////// MEMBERS ////////////////////////////////////

private:
	/// Maximum tool angle change in the interpolated path.
	const float mMaxToolAngleChangeDeg;
	/// Maximum rotation angle around the stock in the interpolated path.
	const float mMaxStockAngleChangeRad;

	//////////////////////////// C-TOR ////////////////////////////////////////
public:
	mwvKinematicUtils(
		const float maxToolAngleChangeDeg =
			5.0f,  ///< Maximum tool angle change in the interpolated path.
		const float maxStockRotAngleChangeDeg =
			90.0f  ///< Maximum rotation angle around the stock in the interpolated path.
	);

	/////////////////// THREAD - INTERPOLATION ////////////////////////////////

public:
	/// Calculates interpolated steps for thread cutting, based on the limits of tool and stock
	/// angle changes.
	///
	/// @param[in] initialPos, initialOri, initialSpindleRot: initial tool position, orientation and
	/// spindle
	///           rotation
	/// @param[in] targetPos, targetOri, targetSpindleRot: final tool position, orientation and
	/// spindle
	///            rotation
	/// @param[in] spindleAxis: spindle axis direction
	/// @param[out] stepList: interpolated steps
	void InterpolateThread(
		const Vec3& initialPos,
		const Quaternion& initialOri,
		const float initialSpindleRot,
		const Vec3& targetPos,
		const Quaternion& targetOri,
		const float targetSpindleRot,
		const Axis spindleAxis,
		std::vector<mwvThreadStep>& stepList  ///< [out] list of interpolated steps
	);

private:
	/// Calculates interpolated frame and adds it to stepList.
	void CalculateFrames(
		const Vec3& interpolatedPos,
		const Quaternion& interpolatedOri,
		const float interpolatedSpindleRot,
		const Axis spindleAxis,
		std::vector<mwvThreadStep>& stepList);

	/// Checks 'step' for being new step.
	void AddStep(const mwvThreadStep& step, std::vector<mwvThreadStep>& stepList);

	/// Calculates the dot product of two Quaternions.
	float QuaternionDot(const Quaternion& a, const Quaternion& b);

	///////////////////////// CIRCULAR SWEEP CUT /////////////////////////////////
public:
	/// This method is not used. Please use @ref VerifierUtil::mwvArcSweepCutInterpolator.
	///
	/// It calculates parameters needed for applying the CircularSweepCut and its variant that
	/// interpolates the change of the tool along the path.
	///
	/// @note angles are in degree, rotation in x-axis
	void CalculateSweepParams(
		// in
		const Point& from,
		const Vec3& oriFrom,
		const Point& to,
		const Vec3& oriTo,
		const float workpieceRotationDeg,
		// out
		Frame& startFrame,
		float& sweepAngle,
		Point& circleCenter,
		Vec3& circlePlaneNormal,
		float& heightChange,
		float& radiusChange,
		QuaternionPtr& toolEndOrientation);

	/// Calculate a rotation of @p rotAngleDeg degrees around @p rotationAxis as a homogeneous (or
	/// affine) 4x4 matrix
	static mwRotationMatrix GetRotationMatrix(const Axis& rotationAxis, const float rotAngleDeg);

private:
	mwvKinematicUtils& operator=(const mwvKinematicUtils&);  // = delete
};

//////////////////////////////////////////////////////////////////////////

/// Stores interpolated steps for @ref mwvKinematicUtils.
class MW_VERIFIER_API mwvThreadStep
{
public:
	typedef mwvKinematicUtils::Frame Frame;
	typedef mwvKinematicUtils::Axis Axis;

private:
	typedef mwvKinematicUtils::Quaternion Quaternion;
	typedef mwvKinematicUtils::Point Point;
	typedef mwvKinematicUtils::Vec3 Vec3;

#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame mTransformedFrame;
#pragma warning(suppress : 4251)  // needs to have dll-interface to be used by clients of class
	Frame mFrame;
	Axis mSpindleAxis;
	float mSpindleRotationDeg;
	bool mTurning;

public:
	mwvThreadStep(
		const Frame& frame,
		const Axis spindleAxis,
		const float spindleRotation,
		const bool isTurning);

	const Frame& GetFrame() const;

	void SetFrame(const Frame& frame);

	/// Tool frame without spindle rotation applied. Since the verifier assumes a fixed workpiece,
	/// this frame can be forwarded to @ref mwMachSimVerifier::ThreadCut() or @ref
	/// mwMachSimVerifier::BufferedThreadCut().
	const Frame& GetTransformedFrame() const;

	bool IsTurning() const;

	const Axis GetSpindleAxis() const;

	void SetSpindleAxis(const Axis spindleAxis);

	const float GetSpindleRotationRad() const;

	void SetSpindleRotationRad(float const value);

private:
	void SetTransformedFrame(const Frame& frame);
};
}  // namespace VerifierUtil
#endif  //	MW_MWVKINEMATICUTILS_HPP_
