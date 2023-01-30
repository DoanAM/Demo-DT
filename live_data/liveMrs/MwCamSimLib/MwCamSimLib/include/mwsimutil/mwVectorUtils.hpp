// (C) 2004-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWVECTORUTILS_HPP_
#define MW_MWVECTORUTILS_HPP_
#include "mwDllImpExpDef.hpp"

#include <mwTPoint2d.hpp>
#include <mwTPoint3d.hpp>


namespace cadcam
{
/// This class represents a vector util.
template <class T>
class MW_5AXUTIL_API mwVectorUtils
{
	typedef typename cadcam::mwTPoint2d<T> vector2d;
	typedef typename cadcam::mwTPoint3d<T> vector3d;

public:
	/// Get shortest angle in radians
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@returns constant shortest angle in radians
	static T GetShortestAngInRad(const vector2d& a, const vector2d& b);

	/// Get angle in radians
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@returns constant angle in radians
	static T GetAngInRad(const vector2d& a, const vector2d& b);

	/// Get angle in radians
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@param normal constant normal
	///	@returns constant angle in radians
	static T GetAngInRad(const vector3d& a, const vector3d& b, const vector3d& normal);

	/// GetAngleFromXAxisDegree
	///
	///	Returns angle in degrees from OX to vector in counterclockwise direction
	///	@param v source vector
	///	@returns boost::T
	static T GetAngleFromXAxisDegree(const vector2d& v);

	/// Get angle between vectors
	///
	/// Returns angle (in degrees) between vectors; from first given clockwise to second given
	///	@param p1 first vector
	///	@param p2 second vector
	static T GetAngleClockwiseDegree(const vector2d& p1, const vector2d& p2);


	/// Get shortest angle in radians
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@returns constant and shortest angle in radians
	static T GetShortestAngInRad(const vector3d& a, const vector3d& b);

	/// Get angle in radians
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@returns constant shortest angle in radians
	static T GetAngInRad(const vector3d& a, const vector3d& b);

	/// The GetAxialProjection function
	///
	///	@param point constant vector to project
	///	@param projDir constant vector projection axis
	///	@returns projected vector
	static vector3d GetAxialProjection(const vector3d& point, const vector3d& projDir);

	/// The GetPlanarProjection function
	///
	///	@param point constant vector to project
	///	@param projDir constant vector projection direction normal to the projection plane
	///	@returns projected vector
	static vector3d GetPlanarProjection(const vector3d& point, const vector3d& projDir);

	/// The AreParallel function
	///
	///	@param a constant first vector
	///	@param b constant second vector
	/// @param tol tolerance to use for test
	///	@returns if parallel
	static bool AreParallel(
		const vector3d& a, const vector3d& b, const T tol = mathdef::MW_MATH_TOL_SQR);
	static bool AreParallel(const vector2d& a, const vector2d& b);

	/// The AreAntiParallel function
	///
	///	@param a constant first vector
	///	@param b constant second vector
	///	@returns if antiparallel
	static bool AreAntiParallel(const vector3d& a, const vector3d& b);

	static vector3d StableNormalize(const vector3d& src);

	static vector3d Stabilize(const vector3d& src, const T prec);

	static vector3d GetRotated(
		const vector3d& e1, const vector3d& e2, const T angle, const T length);

	static vector3d RotateClockAroundX(const vector3d& src, const T angle);
	static vector3d RotateClockAroundY(const vector3d& src, const T angle);
	static vector3d RotateClockAroundZ(const vector3d& src, const T angle);

	/// Rotate a provided vector with a provided angle in a plane given by the normal to it
	///
	/// It is checking the exception cases; the rotation will be performed from the vector to be
	/// rotated to the vector in rotation plane
	///	@param vectToRotate vector to be rotated
	///	@param planeNormal in the normal to the rotation plane
	///	@param angle is the angle with which we rotate the vector
	///	@returns const vector3d is the rotated vector
	static vector3d GetRotatedVectorUsingPlaneNormal(
		const vector3d& vectToRotate, const vector3d& planeNormal, const T& angle);


	/// Rotate a provided vector with a provided angle in a plane given by the normal to it. It
	/// supports a free and arbitrary origin base for the vectors
	///
	/// It is checking the exception cases; the rotation will be performed from the vector to be
	/// rotated to the vector in rotation plane
	///	@param vectToRotate vector to be rotated
	///	@param planeNormal in the normal to the rotation plane
	///	@param angle is the angle with which we rotate the vector
	/// @param baseOrigin point on the plane
	///	@returns const vector3d is the rotated vector
	static vector3d GetRotatedVectorUsingPlaneNormalWithOrigin(
		const vector3d& vectToRotate,
		const vector3d& planeNormal,
		const T& angle,
		const vector3d& baseOrigin = vector3d(0., 0., 0.));


	/// Get precision normal from 2 vectors
	///	@param firstVector - first vector to get Normal
	///	@param secondVector - second vector to get Normal
	///	@returns precision normal, as result of firstvector%secondVector,
	///	or (0,0,0) if inputvectors are parallel
	static vector3d GetPreciseNormal(const vector3d& firstVector, const vector3d& secondVector);


	/// Rotate a provided vector with a provided angle in a plane formed with provided reference
	/// vector
	///
	/// It is checking the exception cases; the rotation will be performed from the vector to be
	/// rotated to the vector in rotation plane
	///	@param vectToRotate vector to be rotated
	///	@param vectorInRotationPlane is the reference vector for making the plane
	///	@param angleRad is the angle with which we rotate the vector
	///	@returns const vector3d is the rotated vector
	static vector3d GetRotatedVectorUsingAPlaneVector(
		const vector3d& vectToRotate, const vector3d& vectorInRotationPlane, const T& angleRad);
	static vector3d ProjectPointToPlane(
		const vector3d& srcPoint, const vector3d& normalToPlane, const T constantPlane);


	/// Get any not degenerated normal to vector
	static vector3d GetNotDegeneratedNormal(const vector3d& srcVect);

	/// Convert angles to vector
	static void ConvertAnglesToVector(const T angleInXY, const T angleFromZ, vector3d& vect);

	/// Convert vector to angles
	static void ConvertVectorToAngles(vector3d vect, T& angleInXY, T& angleFromZ);
	static void ConvertNormalizedVectorToAngles(const vector3d& vect, T& angleInXY, T& angleFromZ);

	/// It tests that the orientations are within tolerances
	///
	/// Is cheeking if the orientation vectors differ not more than minCos angle
	///	@param firstOrientation first orientation
	///	@param secondOrientation second orientation
	///	@param minCos tolerance to be used
	///	@return true if the orientations are within tolerance
	static bool ExactCompareOrientation(
		const vector3d& firstOrientation, const vector3d& secondOrientation, const T minCos);


private:
	/// Rotate a provided vector with a provided angle in a plane formed with provided reference
	/// vector
	///
	/// It not checking the exception cases; the rotation will be performed from the vector to be
	/// rotated to the vector in rotation plane
	///	@param vectToRotate vector to be rotated
	///	@param vectorInRotationPlane is the reference vector for making the plane
	///	@param angle is the angle with which we rotate the vector
	///	@returns const vector3d is the rotated vector
	static vector3d GetUnsafeRotateUsingAPlaneVector(
		const vector3d& vectToRotate, const vector3d& vectorInRotationPlane, const T& angle);

	static float StabilizeSmallValue(const float val, const float prec);

	static double StabilizeSmallValue(const double val, const double prec);

	/// Constructor not allowed since it's a static class
	mwVectorUtils();
};
}  // namespace cadcam
#endif  //	MW_MWVECTORUTILS_HPP_
