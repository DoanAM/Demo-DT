// (C) 2012-2021 by ModuleWorks GmbH
// Owner: 5Axis UP & Additive

#ifndef MW_MW6AXIS_HPP_
#define MW_MW6AXIS_HPP_
#include "mwException.hpp"
#include "mwMathConstants.hpp"
#include "mwMatrixTransformationsFactory.hpp"
#include "mwTPoint3d.hpp"
#include "mwTrig.hpp"

namespace cadcam
{
// This class converts a six axis tool orientation given as two vectors
// (up and side) into an angle that stores the side vector in a single
// number and back. This solely serves the purpose of storing the additional
// data as efficiently as possible.
//
// A number of strict rules apply, for this to work correctly:
// - up must be normalized
// - side must be normalized
// - up and side must have right angle
//
// Also, please keep the following in mind:
// - the angle won't have any useful information for you to use outside
//   this class
// - do not, under any circumstances manipulate the angle returned by this
//   code and expect any useful result
// - do not, under any circumstances manipulate the up vector without
//   updating the angle using this class, expecting a useful result
// - when changing any of the data regarding tool orientation, always
//   convert the angle to side, manipulate it, and convert it back to angle
// - "manipulation" includes the conversion between float and double
//
// To help you keep the rules, there are helper functions:
// - AdjustAngle() allows to to change the up vector while adjusting the
//   angle to keep the side vector as close as possible to the old side
//   vector
// - Convert() converts an (up,angle) pair from one type to another safely

template <class T>
class MW_5AXUTIL_API mwT6Axis
{
public:
	static T GetAngle(
		const cadcam::mwTPoint3d<T>& up,
		const cadcam::mwTPoint3d<T>& side,
		const double precision = mathdef::MW_MATH_TOL)
	{
		if (mathdef::is_eq(~side, 0.0))
			return mathdef::MW_MIN_DOUBLE;

		if (mathdef::is_neq(up.Length2(), (T)1))
			throw misc::mwException(0L, _T("up not normalized"));

		if (mathdef::is_neq(side.Length2(), (T)1))
			throw misc::mwException(0L, _T("side not normalized"));

		double upSideDot = up * side;
		if (mathdef::is_not_zero(upSideDot, precision))
			throw misc::mwException(3499, _T("up and side don't have right angle"));

		cadcam::mwTPoint3d<T> rotX((T)0, (T)0, (T)1);
		cadcam::mwTPoint3d<T> rotZ = rotX % up;

		T angle;

		if (rotZ * rotZ > mathdef::mw_tol((T)0))
		{
			rotZ.Normalize();
			cadcam::mwTPoint3d<T> rotY = rotZ % rotX;

			T upAngleFromZ = (T)atan2(up * rotY, up.z());  // up.z() == up * rotX
			T sideAngleFromZ = (T)atan2(side * rotY, side * rotX);
			T sideRotZPart = side * rotZ;
			T sideInPlaneLength =
				mathdef::mw_sqrt(mathdef::mw_square(side * rotX) + mathdef::mw_square(side * rotY));

			sideAngleFromZ -= upAngleFromZ;

			cadcam::mwTPoint3d<T> sideInXYPlane =
				(rotX * (T)mathdef::Cos(sideAngleFromZ) + rotY * (T)mathdef::Sin(sideAngleFromZ)) *
					sideInPlaneLength +
				rotZ * sideRotZPart;

			angle = atan2(sideInXYPlane.y(), sideInXYPlane.x());
		}
		else
		{
			angle = atan2(side.y(), side.x());
		}

		return angle;
	}

	static cadcam::mwTPoint3d<T> GetSide(const cadcam::mwTPoint3d<T>& up, const T& angle)
	{
		if (mathdef::is_neq(up.Length2(), (T)1))
			throw misc::mwException(0L, _T("up not normalized"));

		if (mathdef::is_lt(angle, (T)-mathdef::MW_PI))
			throw misc::mwException(0L, _T("angle smaller than -pi"));

		if (mathdef::is_gt(angle, (T)mathdef::MW_PI))
			throw misc::mwException(0L, _T("angle bigger than pi"));

		cadcam::mwTPoint3d<T> rotX((T)0, (T)0, (T)1);
		cadcam::mwTPoint3d<T> rotZ = rotX % up;

		cadcam::mwTPoint3d<T> side((T)mathdef::Cos(angle), (T)mathdef::Sin(angle), (T)0);

		if (rotZ * rotZ > mathdef::mw_tol((T)0))
		{
			rotZ.Normalize();
			cadcam::mwTPoint3d<T> rotY = rotZ % rotX;

			T upAngleFromZ = (T)atan2(up * rotY, up.z());  // up.z() == up * rotX
			T sideAngleFromZ = (T)atan2(side * rotY, side * rotX);
			T sideRotZPart = side * rotZ;
			T sideInPlaneLength =
				mathdef::mw_sqrt(mathdef::mw_square(side * rotX) + mathdef::mw_square(side * rotY));

			sideAngleFromZ += upAngleFromZ;

			side =
				(rotX * (T)mathdef::Cos(sideAngleFromZ) + rotY * (T)mathdef::Sin(sideAngleFromZ)) *
					sideInPlaneLength +
				rotZ * sideRotZPart;
		}

		side = ((up % side) % up).Normalized();

		return side;
	}

	static T AdjustAngle(
		const cadcam::mwTPoint3d<T>& oldUp, const T& oldAngle, const cadcam::mwTPoint3d<T>& newUp)
	{
		if (oldUp == newUp)
			return oldAngle;

		const auto xAxis = GetSide(oldUp, oldAngle);
		const double xComponent = newUp * xAxis;
		if (xComponent == 0.0)
			return oldAngle;

		const auto yAxis = (oldUp % xAxis).Normalized();
		const double rotationAxisAngleRad =
			mathdef::SafeAtan2(newUp * yAxis, xComponent) + mathdef::MW_PI_2;
		auto rotationAxis =
			mathdef::Cos(rotationAxisAngleRad) * xAxis + mathdef::Sin(rotationAxisAngleRad) * yAxis;
		const auto sideParallel2Rot = rotationAxis * (xAxis * rotationAxis);
		auto sidePerp2Rot = xAxis - sideParallel2Rot;
		const auto rotatedSidePerp =
			(yAxis * rotationAxis > 0.0 ? rotationAxis % newUp : newUp % rotationAxis).Normalized();
		const auto newSide = (sideParallel2Rot + rotatedSidePerp * ~sidePerp2Rot).Normalized();

		T newAngle = GetAngle(newUp, newSide);
		return newAngle;
	}

	template <class U>
	static void Convert(
		const cadcam::mwTPoint3d<T>& fromUp,
		const T& fromAngle,
		cadcam::mwTPoint3d<U>& toUp,
		U& toAngle)
	{
		cadcam::mwTPoint3d<T> fromSide = GetSide(fromUp, fromAngle);

		toUp = cadcam::mwTPoint3d<U>((U)fromUp.x(), (U)fromUp.y(), (U)fromUp.z());

		cadcam::mwTPoint3d<U> toSide((U)fromSide.x(), (U)fromSide.y(), (U)fromSide.z());

		toAngle = mwT6Axis<U>::GetAngle(toUp, toSide);
	}

	static inline cadcam::mwTPoint3d<T> LinearCombination(
		const cadcam::mwTPoint3d<T>& side1,
		const cadcam::mwTPoint3d<T>& side2,
		const cadcam::mwTPoint3d<T>& up,
		const double paramT)
	{
		auto newSide = side1 * (1.0 - paramT) + side2 * paramT;
		return (up % (newSide % up)).Normalized();
	}
};

typedef mwT6Axis<double> mw6Axis;
}  // namespace cadcam
#endif  //	MW_MW6AXIS_HPP_
