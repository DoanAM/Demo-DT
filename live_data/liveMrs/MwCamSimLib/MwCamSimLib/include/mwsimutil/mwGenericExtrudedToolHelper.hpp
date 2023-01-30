// (C) 2009-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWGENERICEXTRUDEDTOOLHELPER_HPP_
#define MW_MWGENERICEXTRUDEDTOOLHELPER_HPP_
#include "mwAngleDegree.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedSolidDefinition.hpp"
#include "mwGenericExtrudedTool.hpp"
#include "mwMeshSolidDefinition.hpp"
#include "mwMiscFwdDecl.hpp"
#include "mwTrig.hpp"
#include "mwTurningToolsFwdDecl.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwGenericExtrudedToolHelper
{
public:
	typedef typename measures::mwUnitsFactory::Units Units;
	typedef mwTPoint2d<T> Point2d;

	enum ExtrusionDirection
	{
		EXTRUDE_TO_NEGATIVE_Y = -1,
		EXTRUDE_TO_POSITIVE_Y = 1
	};

	static misc::mwAutoPointer<mwGenericExtrudedTool> Convert(
		const mwExtrudedTool& tool, const T profileTolerance);

	static misc::mwAutoPointer<mwGenericExtrudedTool> Convert(
		const mwTypedExtrudedTool& tool, const T profileTolerance);

	/// Creates a round shank holder from a cylinder and headProfile
	///
	/// It assumes headContour is placed on the XZ plane. The head must be to the left of the
	/// cylinder, which means the head must have smaller x-values than the cylinder. This is
	/// necessary in order to subtract the wedge on the correct side of the cylinder.
	static misc::mwAutoPointer<mwGenericExtrudedTool::MeshSolidDefinition::meshData>
	CreateRoundShankHolder(
		const mw2ddPolyLine& headProfile,
		const ExtrusionDirection headExtrusion,
		const double cylinderDiameter,
		const double cylinderLength,
		const Point2d& cylinderCenter,
		const cadcam::mwMatrix<double, 3, 3>& finalProfileTransformation,
		const measures::mwMeasurable::Units units,
		const double meshTolerance);

	/// Creates a round shank holder from a cylinder and a single profile.
	///
	/// The entire profile is assumed to be placed on XZ plane, extruded and intersected with
	/// cylinder.
	static misc::mwAutoPointer<mwGenericExtrudedTool::MeshSolidDefinition::meshData>
	CreateRoundShankHolderWithoutHead(
		const mw2ddPolyLine& holderProfile,
		const double cylinderDiameter,
		const double cylinderLength,
		const Point2d& cylinderCenter,
		const cadcam::mwMatrix<double, 3, 3>& finalProfileTransformation,
		const measures::mwMeasurable::Units units,
		const double meshTolerance);

	/// Creates a round shank holder with variable angle
	///
	/// The holder consists of two concentric cylindrical parts (body and head). The head is a
	/// half-cylinder that sits at the end of the body. The body is a cylinder with a wedge cut into
	/// it. The wedge starts at the end where the head is, continuing the shape of the head but
	/// falling off at an angle. The total length of the holder is equal to headLength + bodyLength.
	/// @param bodyRadius Radius of the body.
	/// @param bodyLength Length of the body.
	/// @param headRadius Radius of the head.
	/// @param headLength Length of the head.
	/// @param units Units of the resulting mesh solid.
	/// @param angle Angle of the wedge in range [0;90) in degrees where 0 will leave the body as a
	/// complete cylinder.
	/// @param headCutoffPlane Set where the head is cut. A value of 0 will cut the cylinder exactly
	/// at the center plane, bigger values will leave some space between the end of the head and the
	/// beginning of the wedge of the body. Use this to avoid Z-fighting with cutting parts that sit
	/// on that center plane. Must be in range [0;headRadius).
	/// @param tolerance Maximum deviation from the exact result.
	/// @throw misc::mwException If either length or radius parameter is < 0
	/// @throw misc::mwException If @p angle is either out of range or too big in which case the
	/// wedge would not end before the body does.
	/// @throw misc::mwException If both parts are omitted (by setting length or radius of both
	/// parts to 0).
	/// @note If either radius or length is set to 0 that part of the mesh will be omitted and the
	/// other value will be ignored. At least one part (head or body) must exist.
	static misc::mwAutoPointer<mwGenericExtrudedTool::MeshSolidDefinition::meshData>
	CreateRoundShankHolder(
		double bodyRadius,
		double bodyLength,
		double headRadius,
		double headLength,
		const measures::mwMeasurable::Units units,
		double angle = 45.0,
		double headCutoffPlane = 0.01,
		double tolerance = 0.01);

	/// Creates a round shank holder with variable angle
	///
	/// The holder consists of two concentric cylindrical parts (body and head). The head is a
	/// half-cylinder that sits at the end of the body. The body is a cylinder with a wedge cut into
	/// it. The wedge starts at the end where the head is, continuing the shape of the head but
	/// falling off at an angle. The total length of the holder is equal to bodyLength +
	/// headProfile's size in x direction.
	/// @param bodyRadius Radius of the body.
	/// @param bodyLength Length of the body.
	/// @param headProfile Profile of the head as seen from the side of the holder that has the
	/// wedge cut into it. The x coordinate of the profile points in the direction of the body and y
	/// coordinate of the profile points in the direction of the holder width. The profile will be
	/// centered on the body and must not be wider than the body. diameter. If the profile is empty,
	/// the head is omitted.
	/// @param units Units of the resulting mesh solid.
	/// @param angle Angle of the wedge in range [0;90) in degrees where 0 will leave the body as a
	/// complete cylinder.
	/// @param headCutoffPlane Set where the head is cut. A value of 0 will cut the cylinder exactly
	/// at the center plane, bigger values will leave some space between the end of the head and the
	/// beginning of the wedge of the body. Use this to avoid Z-fighting with cutting parts that sit
	/// on that center plane. Must be in range [0;headRadius).
	/// @param tolerance Maximum deviation from the exact result.
	/// @throw misc::mwException If @p headProfile cannot be closed, has no area or extends further
	/// than bodyRadius.
	/// @throw misc::mwException If @p bodyLength or @p bodyRadius parameter is < 0
	/// @throw misc::mwException If @p angle is either out of range or too big in which case the
	/// wedge would not end before the body does.
	/// @throw misc::mwException If both parts are omitted (by setting length or radius to 0 and
	/// passing an empty profile).
	/// @note If either radius or length is set to 0 that part of the mesh will be omitted and the
	/// other value will be ignored. At least one part (head or body) must exist.
	static misc::mwAutoPointer<mwGenericExtrudedTool::MeshSolidDefinition::meshData>
	CreateRoundShankHolder(
		double bodyRadius,
		double bodyLength,
		const cadcam::mw2ddPolyLine& headProfile,
		const measures::mwMeasurable::Units units,
		double angle = 45.0,
		double headCutoffPlane = 0.01,
		double tolerance = 0.01);

	/// Creates a diamond-shaped geometric contour from standard input parameters.
	///
	///	@param noseRadius is the radius of the diamond's corner inscribed circle. It is allowed to be 0.
	///	@param internalCircumscribedDiameter is the diameter of the internal inscribed circle.
	///	@param noseAngle is the angle of the corner whose radius is the noseRadius parameter.
	///	@param mountAngle is the angle at which the whole polyline is rotated from the oX axis.
	/// @param originOffsetX origin offset in X
	/// @param originOffsetY origin offset in Y
	///	@return the built geometrically closed contour.
	static mw2dContour<T> CreateDiamondShapeContour(
		const T& noseRadius,
		const T& internalCircumscribedDiameter,
		const measures::mwAngleDegree<T>& noseAngle,
		const measures::mwAngleDegree<T>& mountAngle,
		const T originOffsetX,
		const T originOffsetY);

	/// Create a circular-shaped geometric contour from the standard input parameters.
	///
	///	@param diameter is the diameter of the circle.
	///	@return the built geometrically closed contour.
	static mw2dContour<T> CreateCircularShapeContour(const T& diameter);

	/// Create a drill-shaped geometric contour from the standard input parameters.
	///
	///	@param radius is the tool radius.
	///	@param length is the tool length (full length, including tip length).
	///	@param angle is the drill angle of the tip in degrees.
	///	@return the built geometrically closed Contour.
	static mw2dContour<T> CreateDrillShapeContour(
		const T& radius, const T& length, const measures::mwAngleDegree<T>& angle);

private:
	static void ValidateTolerance(const T& tolerance);
	static void ValidateDiamondShapeParameters(
		const T& noseRadius,
		const T& internalCircumscribedDiameter,
		const measures::mwAngleDegree<T>& noseAngle);
	static void ValidateCircularShapeParameters(const T& diameter);
	static void ValidateDrillShapeParameters(
		const T& radius, const T& length, const measures::mwAngleDegree<T>& angle);

	/// Constructor is not allowed because it is a static class.
	mwGenericExtrudedToolHelper();

public:
	static void TransformContour(
		mw2dContour<T>& contour, const T angleInDegree, const T translateX, const T translateY);

	/// Creates a trapezoid with a corner-radius.
	///
	///   4-3
	///  /   \
	///  1---2
	/// 1-2 is aligned to the X-axis.
	/// @param horizontalLength is the length of sides 12 and 34 (including cornerRadius).
	/// @param verticalHeight is the distance from 4 to side 12 (including cornerRadius).
	/// @param sideAngle1 is the angle between side 14 and 12.
	/// @param sideAngle2 is the angle between 23 and 21.
	/// @param cornerRadius is the radius of the corners.
	/// @param mountAngle is the angle by which the trapezoid will be rotated around the origin
	/// (center of arc at 1) in a counter-clockwise direction.
	/// @param originOffsetX is the translation of the origin (after being rotated).
	/// @param originOffsetY is the translation of the origin (after being rotated).
	static mw2dContour<T> CreateTrapezoidContour(
		const T horizontalLength,
		const T verticalHeight,
		const measures::mwAngleDegree<T> sideAngle1,
		const measures::mwAngleDegree<T> sideAngle2,
		const T cornerRadius,
		const measures::mwAngleDegree<T> mountAngle,
		const T originOffsetX,
		const T originOffsetY);
};
}  // namespace cadcam
#endif  //	MW_MWGENERICEXTRUDEDTOOLHELPER_HPP_
