// (C) 2006-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMATRIXTRANSFORMATIONSFACTORY_HPP_
#define MW_MWMATRIXTRANSFORMATIONSFACTORY_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwMatrix.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPoint3d.hpp"


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwMatrixTransformationsFactory
{
public:
	typedef mwTPoint2d<T> point2d;
	typedef mwTPoint2d<T> vector2d;
	typedef mwTPoint3d<T> point3d;
	typedef mwTPoint3d<T> vector3d;
	typedef mwMatrix<T, 3, 3> mwMatrix3d;
	typedef mwMatrix<T, 4, 4> mwMatrix4d;

	/// Create3dRotation
	///
	/// Creates a 3d rotation matrix
	///	@param axis specifies the rotation axis
	///	@param angle gives the rotation angle in degrees
	static const mwMatrix4d Create3dRotation(const vector3d& axis, const double angle);

	/// Create3dRotation given an axis and the axis base point
	///
	/// Creates a 3d rotation matrix
	///	@param axis specifies the rotation axis
	///	@param axisBasePoint specifies the rotation axis base point
	///	@param angle gives the rotation angle in degrees
	static const mwMatrix4d Create3dRotation(
		const vector3d& axis, const point3d& axisBasePoint, const T angle);

	/// Create3dRotation from vector u to vector v and add translation component
	///
	/// Creates a 3d rotation matrix that rotates v onto u and moves the origin to translationVector
	///	@param endOrientation The end orientation for the rotation
	///	@param startOrientation The start orientation for the rotation
	///	@param translationVector
	static const mwMatrix4d Create3dRotation(
		const vector3d& endOrientation,
		const vector3d& startOrientation,
		const point3d& translationVector);


	/// Create transformation matrices to switch between global and local coordinate systems
	/// @param coordinateSystemOrigin - origin of local CS
	/// @param coordinateSystemI - I vector of local CS
	/// @param coordinateSystemJ - J vector of local CS
	/// @param coordinateSystemK - K vector of local CS
	/// @param moveMatrix - matrix for move transformation
	/// @param rotateMatrix - matrix for rotate transformation
	/// @param fromGlobalToCs - select direction "from global to local" CS or "from local to
	/// global".
	static void CreateTransformationMatricesForOrtogonalCoordinateSystem(
		const vector3d& coordinateSystemOrigin,
		const vector3d& coordinateSystemI,
		const vector3d& coordinateSystemJ,
		const vector3d& coordinateSystemK,
		mwMatrix4d& moveMatrix,
		mwMatrix4d& rotateMatrix,
		const bool fromGlobalToCs);

	/// Create2dRotation
	///
	/// Creates a 2d rotation matrix
	///	@param angle gives the rotation angle in degrees
	static const mwMatrix3d Create2dRotation(const T angle);

	/// Create2dRotation
	///
	/// Creates a 2d rotation matrix
	/// @param axisBasePoint specifies the rotation base point
	/// @param angle gives the rotation angle in degrees
	static const mwMatrix3d Create2dRotation(const point2d& axisBasePoint, const T angle);

	/// Create 3D rotation matrix around X by angle
	static const mwMatrix3d Create3dXRotation(const T angle);

	/// Create 3D rotation matrix around Y by angle
	static const mwMatrix3d Create3dYRotation(const T angle);

	/// Create 3D rotation matrix around Z by angle
	static const mwMatrix3d Create3dZRotation(const T angle);

	/// Create2dTranslation
	///
	/// Creates a 2d translation matrix
	///	@param translationVector gives the translation vector
	static const mwMatrix3d Create2dTranslation(const point2d& translationVector);

	/// Create3dTranslation
	///
	/// Creates a 3d translation matrix
	///	@param translationVector gives the translation vector
	static const mwMatrix4d Create3dTranslation(const point3d& translationVector);

	/// Translates a 3D point along a translation vector
	///
	///	@param toTranslate is point to be translated
	///	@param translUnitVec is unit translation vector (normalized)
	///	@param value amount to be shifted along shift vector
	static void Translate3dPoint(
		point3d& toTranslate, const vector3d& translUnitVec, const double value);

	/// Creates a set of intermediary transformation matrices
	///
	/// @param initialState initial transformation matrix
	/// @param endState final transformation matrix
	/// @param steps specifies how many intermediary matrices will be generated
	static std::vector<mwMatrix4d> CreateIntermediaryTransforms(
		const mwMatrix4d& initialState, const mwMatrix4d& endState, const unsigned int steps);

	/// Creates a set forward and backward rotation matrices to vertical
	///
	/// @param[in] srcDirection - machining direction
	///	@param[out] forwardTransform - forward rotation matrix
	///	@param[out] inverseTransform - backward rotation matrix
	static void CreateRotationToVertical(
		const point3d& srcDirection, mwMatrix4d& forwardTransform, mwMatrix4d& inverseTransform);

	/// Creates a rotation matrix for the given axis and angle.
	static mwMatrix3d GetRotationMatrix(const vector3d& axis, const double angle);

	/// Create2dMirroring across a line
	///
	/// Creates a 2d mirroring matrix
	/// Mirroring line passes through origin
	/// @param lineNormal specifies mirroring line normal unit
	static const mwMatrix3d Create2dMirroring(const vector2d& lineNormal);

	/// Create2dMirroring across a line
	///
	/// Creates a 2d mirroring matrix
	/// @param lineNormal specifies mirroring line normal unit
	/// @param linePoint specifies a point on the line (base point)
	static const mwMatrix3d Create2dMirroring(const vector2d& lineNormal, const point2d& linePoint);

	/// Create3dMirroring across a plane
	///
	/// Creates a 3d mirroring matrix
	///	Mirroring plane passes through origin
	///	@param planeNormal specifies mirroring plane normal unit
	static const mwMatrix4d Create3dMirroring(const vector3d& planeNormal);

	/// Create3dMirroring across a plane
	///
	/// Creates a 3d mirroring matrix
	///	@param planeNormal specifies mirroring plane normal unit
	///	@param planePoint specifies a point on the plane (base point)
	static const mwMatrix4d Create3dMirroring(
		const vector3d& planeNormal, const point3d& planePoint);

	/// DecomposeRotations from matrix
	///
	/// Extract rotation around X, Y and Z from 4x4 matrix
	///	@param transform is input transformation 4x4 matrix to be used
	///	@param x is rotation around vector (1,0,0)
	///	@param y is rotation around vector (0,1,0)
	///	@param z is rotation around vector (0,0,1)
	static void DecomposeRotations(const mwMatrix4d& transform, T& x, T& y, T& z);

	/// ComposeMatrix
	///
	/// Create 4x4 transformation matrix from rotation around X, Y and Z and from a translation 3D
	///	@param rotX is rotation around vector (1,0,0)
	///	@param rotY is rotation around vector (0,1,0)
	///	@param rotZ is rotation around vector (0,0,1)
	///	@param shiftX is translation along vector (1,0,0)
	///	@param shiftY is translation along vector (0,1,0)
	///	@param shiftZ is translation along vector (0,0,1)
	/// @param digits round to this number of digits after decimal point
	///	@return 4x4 transformation matrix
	static const mwMatrix4d ComposeMatrix(
		const T rotX,
		const T rotY,
		const T rotZ,
		const T shiftX,
		const T shiftY,
		const T shiftZ,
		const short digits = 2);

	/// CreateMapMatrix
	///
	/// Create 3x3 transformation matrix such that point p1,p2,p3 map to o1,o2,o3
	static const mwMatrix3d CreateMapMatrix(
		const point2d& p1,
		const point2d& p2,
		const point2d& p3,
		const point2d& o1,
		const point2d& o2,
		const point2d& o3);

private:
	static point3d CreateIntermediaryPoint(
		const point3d& startPoint, const point3d& endPoint, const double intermediaryPosition);

	/// Constructor not allowed since it's a static class
	mwMatrixTransformationsFactory();
};

}  // namespace cadcam
#endif  //	MW_MWMATRIXTRANSFORMATIONSFACTORY_HPP_
