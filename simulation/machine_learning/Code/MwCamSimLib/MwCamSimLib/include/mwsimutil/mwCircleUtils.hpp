// (C) 2005-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCIRCLEUTILS_HPP_
#define MW_MWCIRCLEUTILS_HPP_
#include "mw2dPoint.hpp"
#include "mw3dPoint.hpp"
#include "mwDllImpExpDef.hpp"


namespace cadcam
{
enum mwDistanceType
{
	DISTANCE_RADIANS,
	DISTANCE_DEGREES,
	DISTANCE_LENGTH
};

template <class T, class TPoint>
/// The mwCircleUtils class
///
/// This class represents a mwCircleUtils:
class MW_5AXUTIL_API mwCircleUtils
{
public:
	typedef TPoint point;
	typedef TPoint direction;


	/// The Points2Circle function
	///
	/// Finds the circle passing through three points P1, P2, P3
	///	@param P1 of type ref to point - in
	///	@param P2 of type ref to point - in
	///	@param P3 of type ref to point - in
	///	@param center of type ref to point - out
	///	@param radius of type ref to T out
	///	@returns Points2Circle of type static const bool
	static const bool Points2Circle(
		const point& P1, const point& P2, const point& P3, point& center, T& radius);

	/// The CircularExtrapolation function
	///
	/// Finds the next logical point in the sequence P1, P2, P3,
	/// on the circle determined by them, at a given distance
	///	@param P1 of type ref to point - in
	///	@param P2 of type ref to point - in
	///	@param P3 of type ref to point - in
	///	@param extraPoint of type ref to point - out
	///	@param distance of type const T - in
	///	@param distType of type const mwDistanceType - in
	static void CircularExtrapolation(
		const point& P1,
		const point& P2,
		const point& P3,
		point& extraPoint,
		const T distance,
		const mwDistanceType distType = DISTANCE_LENGTH);

	/// The LinearExtrapolation function
	///
	/// Finds the next logical point in the sequence P1, P2, P3,
	/// on the line determined by them, at a given distance
	///	@param P1 of type ref to point - in
	///	@param P2 of type ref to point - in
	///	@param P3 of type ref to point - in
	///	@param extraPoint of type ref to point
	static void LinearExtrapolation(
		const point& P1, const point& P2, const point& P3, point& extraPoint);

	/// The MoveExtrapolation function
	///
	///	@param P1 of type ref to point - in
	///	@param D1 of type ref to direction - in
	///	@param P2 of type ref to point - in
	///	@param D2 of type ref to direction - in
	///	@param P3 of type ref to point - in
	///	@param D3 of type ref to direction - in
	///	@param extraPoint of type ref to point
	///	@param extraDirection of type ref to direction
	///	@param distance of type const T
	///	@param distType of type const mwDistanceType
	static void VectorCircularExtrapolation(
		const point& P1,
		const direction& D1,
		const point& P2,
		const direction& D2,
		const point& P3,
		const direction& D3,
		point& extraPoint,
		point& extraDirection,
		const T distance,
		const mwDistanceType distType = DISTANCE_LENGTH);

	/// The GetRayTracingParam function
	///
	///	@param center circle's/sphere/s center
	///	@param radius circle's/sphere/s radius
	///	@param raySource ray's source
	///	@param rayDirection ray's direction
	///	@param param the parameter on the ray
	///	@returns true if cast
	static const bool GetRayTracingParam(
		const point& center,
		const T radius,
		const point& raySource,
		const point& rayDirection,
		T& param);


	/// The GetAngleForArcToChordDeviation function
	///
	///	@param tolerance the tolerance used for approximation of polyline
	///	@param radius arc radius
	///	@returns the angle for which the distance between arc and its chord is less than tolerance
	static T GetAngleForChordalDeviationInTol(T tolerance, T radius);


	/// The CompileNumberOfSamplesForPolygonization function
	///
	///	@param tolerance the tolerance used for approximation of polyline
	///	@param radius arc radius
	///	@param sweepAngle sweep angle of the arc (in degree)
	///	@returns the number of points of the polyline
	static size_t CompileNumberOfSamplesForPolygonization(T tolerance, T radius, T sweepAngle);

	/// The CompileNumberOfSamplesForPolygonization function
	///
	/// @param tolerance	allowed deviation (absolute distance)
	/// @param maxAngle		maximum allowed angle (in degree)
	/// @param radius		arc radius
	/// @param sweepAngle	sweep angle of the arc (in degree)
	/// @returns the number of points of the polyline
	static size_t CompileNumberOfSamplesForPolygonization(
		T tolerance, T maxAngle, T radius, T sweepAngle);

private:
	/// The GetLen function
	///
	/// Needed for compatibility between mw2dPoint and mw3dPoint cross products
	///	@param scalar of type const ref to T
	///	@returns the size of scalar of type static const T
	static const T GetLen(const T& scalar);

	/// The GetLen function
	///
	/// Needed for compatibility between mw2dPoint and mw3dPoint cross products
	///	@param vec of type ref to point
	///	@returns the length of vec of type static const T
	static const T GetLen(const point& vec);

	/// The GetArcLenghts function
	///
	///	@param P1 of type ref to point - in
	///	@param P2 of type ref to point - in
	///	@param P3 of type ref to point - in
	///	@param P4 of type ref to point - in
	///	@param len1 of type ref to T out
	///	@param len2 of type ref to T out
	///	@param len3 of type ref to T out
	static void GetArcLenghts(
		const point& P1,
		const point& P2,
		const point& P3,
		const point& P4,
		T& len1,
		T& len2,
		T& len3);

	/// Constructor not allowed since it's a static class
	mwCircleUtils();
};


typedef mwCircleUtils<float, mwTPoint2d<float>> mw2dfCircleUtils;
typedef mwCircleUtils<double, mwTPoint2d<double>> mw2ddCircleUtils;

typedef mwCircleUtils<float, mwTPoint3d<float>> mw3dfCircleUtils;
typedef mwCircleUtils<double, mwTPoint3d<double>> mw3ddCircleUtils;
}  // namespace cadcam
#endif  //	MW_MWCIRCLEUTILS_HPP_
