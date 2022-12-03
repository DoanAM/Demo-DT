// (C) 2010-2021 by ModuleWorks GmbH
// Owner: CutSim

/// @file
/// @hidden

#ifndef MW_MWMATHUTILITIES_HPP_
#define MW_MWMATHUTILITIES_HPP_
#include "mwMatrix.hpp"
#include "mwMatrixTransformationsFactory.hpp"
#include "mwTPoint3d.hpp"
#include "mwTrig.hpp"

#include <cassert>
#include <cmath>


#ifndef MW_GENERATE_DOCUMENTATION
#ifndef MATH_TINY
#define MATH_TINY 10E-6f
#endif
#endif

namespace cadcam
{
typedef mwMatrix<float, 4, 4> mwHomogenousMatrix;
};

namespace mw
{
namespace Verifier
{
namespace math
{
/// @hidden
template <typename Real>
struct TQuaternion;
}  // namespace math
}  // namespace Verifier
}  // namespace mw

namespace MATH
{
/// Implements common operations on quaternions.

/// Note that the quaternion definition in this class is
///
///		quaternion = x + i * y + j * z + k * w, (i,j,k imaginary units)
///
/// while the common definition is
///
///		usualQuaternion = w + i * x + j * y + k * z
///
/// so the rotational axis is related to (y,z,w) instead of (x,y,z).
/// As quaternions form a division algebra, addition and multiplication of elements are defined.
/// Also the inverse element can be computed.
/// Normalized quaternions (length 1) correspond to rotations in 3D space.
template <typename scalarType>
struct Quaternion
{
	typedef ::cadcam::mwTPoint3d<scalarType> point3d;
	scalarType x, y, z, w;

	/// Initialize with zero axis.
	Quaternion(): x(1), y(0), z(0), w(0) {}

	Quaternion(scalarType _x, scalarType _y, scalarType _z, scalarType _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	/// Initialize with given @p angle (in degrees) and rotation axis.
	Quaternion(scalarType angle, const point3d& rotationAxis)
	{
		scalarType si;
		mathdef::SinCos((scalarType)mathdef::MW_PI_2 / 180 * angle, si, x);

		y = rotationAxis.x();
		z = rotationAxis.y();
		w = rotationAxis.z();
		scalarType norm = sqrt(y * y + z * z + w * w);
		if (norm <= MATH_TINY)
		{
			// x = 0 (angle = 180° + n * 360°) or x  = +-1 (angle =  n * 360°)
			if (std::abs(x) >= (scalarType)0.5)
			{
				*this = Quaternion(1, 0, 0, 0);
			}
			else
			{
				*this = Quaternion(0, 1, 0, 0);
			}
			return;
		}
		y *= si / norm;
		z *= si / norm;
		w *= si / norm;
	}

	/// Returns the rotation angle in degrees (0--360)
	scalarType angle() const
	{
		scalarType si = sqrt(y * y + z * z + w * w);
		scalarType angle =
			180 / (scalarType)mathdef::MW_PI_2 * mathdef::ExtATan2<scalarType>(si, (scalarType)x);
		return angle;
	}

	/// Returns the rotation angle in radians (0--2pi)
	scalarType angleRadians() const
	{
		scalarType si = sqrt(y * y + z * z + w * w);
		return 2 * mathdef::ExtATan2<scalarType>(si, (scalarType)x);
	}

	/// Returns the normalized quaternion axis. If the quaternion is zero, it returns the z axis.
	point3d axis() const
	{
		point3d n(y, z, w);
		scalarType si = sqrt(y * y + z * z + w * w);
		if (si == 0)
			return point3d(0, 0, 1);

		n *= 1 / si;
		return n;
	}

	/// Returns true, if quaternion is unit quaternion (with given tolerance)
	bool isIdentity(scalarType eps = MATH_TINY) const
	{
		if (x == 1)
			return true;
		if (x == -1)
			return true;
		if (x > 1 - eps)
			return true;
		if (x < -1 + eps)
			return true;
		return false;
	}

	/// Deprecated. An alternative way to calculate the angle.
	/// @see angle.
	const scalarType getRoll_inDegree() const;

	bool operator==(const Quaternion& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
	}

	bool operator!=(const Quaternion& rhs) const { return !(*this == rhs); }

	Quaternion inverse() const { return Quaternion(this->x, -this->y, -this->z, -this->w); }

	Quaternion operator*(const Quaternion& rhs) const
	{
		const scalarType& s1 = this->x;
		const scalarType& s2 = rhs.x;
		const point3d v1(this->y, this->z, this->w);
		const point3d v2(rhs.y, rhs.z, rhs.w);

		Quaternion q;
		q.x = s1 * s2 - (v1 * v2);
		const point3d v = (s1 * v2) + (s2 * v1) + CROSS(v1, v2);
		q.y = v.x();
		q.z = v.y();
		q.w = v.z();

		scalarType norm = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);

		q.x /= norm;
		q.y /= norm;
		q.z /= norm;
		q.w /= norm;
		return q;
	}

	point3d operator*(const point3d& p) const
	{
		// Q = (s,v0,v1,v2)
		// re = Q p Q^-1 = 2 * <p,v> v + (s^2 -|v|^2) p + 2 s (v x p)
		const scalarType s = this->x;
		const point3d v(this->y, this->z, this->w);

		return (2 * (v * p)) * v + (s * s - v * v) * p + (2 * s) * CROSS(v, p);
	}

	Quaternion<scalarType> operator*(const scalarType t) const
	{
		Quaternion r;
		r.x = this->x * t;
		r.y = this->y * t;
		r.z = this->z * t;
		r.w = this->w * t;
		return r;
	}

	Quaternion<scalarType> operator/(const scalarType t) const
	{
		Quaternion r;
		r.x = this->x / t;
		r.y = this->y / t;
		r.z = this->z / t;
		r.w = this->w / t;
		return r;
	}

	Quaternion<scalarType> operator+(const Quaternion<scalarType>& q) const
	{
		Quaternion r;
		r.x = this->x + q.x;
		r.y = this->y + q.y;
		r.z = this->z + q.z;
		r.w = this->w + q.w;
		return r;
	}

	Quaternion<scalarType> operator-(const Quaternion<scalarType>& q) const
	{
		Quaternion r;
		r.x = this->x - q.x;
		r.y = this->y - q.y;
		r.z = this->z - q.z;
		r.w = this->w - q.w;
		return r;
	}

	/// Returns the squared quaternion length

	const scalarType Length2() const { return x * x + y * y + z * z + w * w; }

	const scalarType Length() const { return sqrt(Length2()); }

	/// @deprecated Use point3d::operator% instead.
	inline static point3d CROSS(const point3d& x, const point3d& y)  // TODO: remove from API
	{
		return x % y;
	}

	/// @hidden
	template <class Archive>
	void serialize(Archive& ar, const unsigned int /*version*/)
	{
		ar& x;
		ar& y;
		ar& z;
		ar& w;
	};

	/// @hidden
	operator mw::Verifier::math::TQuaternion<scalarType>&();
	/// @hidden
	operator const mw::Verifier::math::TQuaternion<scalarType>&() const;
};

// Ai are the columns of the SO3 Matrix A
template <typename scalarType>
void SO3ToQuaternion(
	cadcam::mwTPoint3d<scalarType> A0,
	cadcam::mwTPoint3d<scalarType> A1,
	cadcam::mwTPoint3d<scalarType> A2,
	Quaternion<scalarType>& q)
{
	if (mw_abs(A0.x()) < MATH_TINY)
		A0.x(0);
	if (mw_abs(A0.y()) < MATH_TINY)
		A0.y(0);
	if (mw_abs(A0.z()) < MATH_TINY)
		A0.z(0);

	if (mw_abs(A1.x()) < MATH_TINY)
		A1.x(0);
	if (mw_abs(A1.y()) < MATH_TINY)
		A1.y(0);
	if (mw_abs(A1.z()) < MATH_TINY)
		A1.z(0);

	if (mw_abs(A2.x()) < MATH_TINY)
		A2.x(0);
	if (mw_abs(A2.y()) < MATH_TINY)
		A2.y(0);
	if (mw_abs(A2.z()) < MATH_TINY)
		A2.z(0);
	A0.Normalize();
	A1.Normalize();
	A2.Normalize();

	/*
	Provided A = {Ae0,Ae1,Ae2} is  a ONB of R^3,
	this function computes the quaternionic representation of A.
	Provisions:
	We know for a unit quaternion q = (s,v),s in R, v in R^3 with s^2 + |v|^2 = 1
	the action on R^3 is given by:

	q p q^-1 = 2 * <p,v> v + (s^2 -|v|^2) p + 2 s (v x p) for all p in R^3.
	*/
	scalarType trA = A0.x() + A1.y() + A2.z();

	if (trA > 0)
	{
		q.x = sqrt(1 + trA) / 2;
		scalarType s = 1 / (4 * q.x);

		q.y = s * (A1.z() - A2.y());
		q.z = s * (A2.x() - A0.z());
		q.w = s * (A0.y() - A1.x());
	}
	else
	{
		if (A0.x() >= A1.y() && A0.x() >= A2.z())
		{
			scalarType r = sqrt(1 + A0.x() - A1.y() - A2.z());
			q.y = r / 2;
			scalarType s = 1 / (4 * q.y);
			q.x = s * (A1.z() - A2.y());
			q.z = s * (A0.y() + A1.x());
			q.w = s * (A2.x() + A0.z());
		}
		else if (A1.y() >= A2.z() && A1.y() >= A0.x())
		{
			scalarType r = sqrt(1 - A0.x() + A1.y() - A2.z());
			q.z = r / 2;
			scalarType s = 1 / (4 * q.z);
			q.x = s * (A2.x() - A0.z());
			q.y = s * (A0.y() + A1.x());
			q.w = s * (A1.z() + A2.y());
		}
		else
		{
			scalarType r = sqrt(1 - A0.x() - A1.y() + A2.z());
			q.w = r / 2;
			scalarType s = 1 / (4 * q.w);
			q.x = s * (A0.y() - A1.x());
			q.y = s * (A0.z() + A2.x());
			q.z = s * (A1.z() + A2.y());
		}
	}

	scalarType norm = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	q.x /= norm;
	q.y /= norm;
	q.z /= norm;
	q.w /= norm;
};

// Ai are the columns of the SO3 Matrix A
template <typename scalarType>
void QuaternionToSO3(
	const Quaternion<scalarType>& q,
	cadcam::mwTPoint3d<scalarType>& A0,
	cadcam::mwTPoint3d<scalarType>& A1,
	cadcam::mwTPoint3d<scalarType>& A2)
{
	A0 = q * cadcam::mwTPoint3d<scalarType>(1, 0, 0);
	A1 = q * cadcam::mwTPoint3d<scalarType>(0, 1, 0);
	A2 = q * cadcam::mwTPoint3d<scalarType>(0, 0, 1);
};

template <typename scalarType>
const Quaternion<scalarType> OrientationToQuaternion(
	cadcam::mwTPoint3d<scalarType> orientation, const scalarType roll)
{
	Quaternion<scalarType> toOri;

	if ((orientation.x() != 0) || (orientation.y() != 0))
	{
		const cadcam::mwTPoint3d<scalarType> v(-orientation.y(), orientation.x(), 0);

		const scalarType rotAngle =
			90 / (scalarType)mathdef::MW_PI_2 * mathdef::SnappingAcos(orientation.z());
		toOri = Quaternion<scalarType>(rotAngle, v);
	}
	else if (orientation.z() >= 0)
	{
		// should be z==1
		toOri = Quaternion<scalarType>();
	}
	else
	{
		// should be z==-1
		toOri = Quaternion<scalarType>(0, 1, 0, 0);
	}

	const Quaternion<scalarType> aroundOri(roll, cadcam::mwTPoint3d<scalarType>(0, 0, 1));

	return toOri * aroundOri;
}

template <typename scalarType>
const Quaternion<scalarType> Interpolate_Nlerp(
	const Quaternion<scalarType>& q0, const Quaternion<scalarType>& q1, const scalarType t)
{
	if (q0 == q1)
	{
		return q0;
	}

	Quaternion<scalarType> r = q0 * (1 - t) + q1 * t;

	const scalarType len2 = r.Length2();
	if (len2 == 0)
		return Interpolate_Nlerp(q0, q1, t - 1.0e-5f);

	r = r / sqrt(len2);
	return r;
}

template <typename scalarType>
const Quaternion<scalarType> Interpolate_Slerp(
	const Quaternion<scalarType>& q0,
	Quaternion<scalarType> q1,
	const scalarType t,
	scalarType maxCosForNlerp = (scalarType)0.98481)  // ~10 degrees
{
	if (mathdef::is_lte(t, 0))
		return q0;
	if (mathdef::is_gte(t, 1))
		return q1;

	scalarType c = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;

	if (c < 0)
	{
		q1 = q1 * (scalarType)-1;
		c = -c;
	}

	if (c >= maxCosForNlerp)
		return Interpolate_Nlerp(q0, q1, t);

	scalarType a = mathdef::SnappingAcos(c);
	return (q0 * mathdef::Sin((1 - t) * a) + q1 * mathdef::Sin(t * a)) / mathdef::Sin(a);
}

template <typename scalarType>
scalarType QuaternionDot(const Quaternion<scalarType>& a, const Quaternion<scalarType>& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}


/// Describes a coordinate frame in 3D space, i.e. a position for the origin and a 3D rotation,
/// called orientation.
///
/// A frame can also be interpreted as a transformation between two coordinate frames. Then it
/// corresponds to a homogeneous (or affine) 4x4 matrix, consisting of rotation and translation.
template <typename scalarType>
struct Frame
{
	/// deprecated, @sa point3d
	typedef ::cadcam::mwTPoint3d<scalarType> float3d;
	typedef ::cadcam::mwTPoint3d<scalarType> point3d;
	typedef struct Quaternion<scalarType> Quaternion;

	point3d m_origin;
	Quaternion m_orientation;

	/// Initialize with zero origin position and identity orientation.
	Frame() {}

	/// Initialize with given position and orientation.
	Frame(const point3d& origin, const Quaternion& orientation)
		: m_origin(origin), m_orientation(orientation)
	{
	}

	/// Initialize with a homogeneous (or affine) matrix.
	///
	/// The upper-left 3x3 matrix initializes the orientation.
	/// The last column gives the position and scaling.
	Frame(const cadcam::mwMatrix<scalarType, 4, 4>& m)
	{
		scalarType scaleFactor(m[3][3]);

		// translation
		m_origin = point3d(m[0][3], m[1][3], m[2][3]);
		m_origin /= scaleFactor;

		// orientation (rotation)
		point3d A0(m[0][0], m[1][0], m[2][0]);
		point3d A1(m[0][1], m[1][1], m[2][1]);
		point3d A2(m[0][2], m[1][2], m[2][2]);
		A0 /= scaleFactor;
		A1 /= scaleFactor;
		A2 /= scaleFactor;
		MATH::SO3ToQuaternion<scalarType>(A0, A1, A2, m_orientation);
	}

	inline const point3d& getOrigin() const { return this->m_origin; }

	inline void setOrigin(const point3d& origin) { this->m_origin = origin; }

	inline const Quaternion& getOrientation() const { return this->m_orientation; }

	inline void SetOrientation(const Quaternion& orientation) { this->m_orientation = orientation; }

	/// @sa rotate
	inline point3d getAxis(const point3d& z = point3d(0, 0, 1)) const
	{
		return this->m_orientation * z;
	}

	/// Returns getAxis({0, 0, 1})
	/// @sa rotate
	inline point3d getDefaultAxis() const
	{
		// Equal to getAxis(point3d(0,0,1))
		const scalarType x = m_orientation.x;
		const scalarType y = m_orientation.y;
		const scalarType z = m_orientation.z;
		const scalarType w = m_orientation.w;
		return point3d(
			static_cast<scalarType>(2.0) * (x * z + w * y),
			static_cast<scalarType>(2.0) * (w * z - x * y),
			x * x - y * y - z * z + w * w);
	}

	bool operator==(const Frame& rhs) const
	{
		return this->m_origin.IsTolerant(rhs.m_origin) && this->m_orientation == rhs.m_orientation;
	}

	bool operator!=(const Frame& rhs) const { return !(*this == rhs); }

	/// Returns inverse Frame
	/// i.e. frame * inverse = identity frame
	Frame inverse() const
	{
		Quaternion inv = this->m_orientation.inverse();
		return Frame(-(inv * this->m_origin), inv);
	}

	/// Returns the frame equal to successive application of this frame and rhs
	Frame operator*(const Frame& rhs) const
	{
		return Frame(
			(this->m_orientation * rhs.m_origin) + this->m_origin,
			this->m_orientation * rhs.m_orientation);
	}

	/// Returns point after transformation from frame coordinate system to world coordinates.
	point3d transform(const point3d& point) const
	{
		return (this->m_orientation * point) + this->m_origin;
	}

	/// Rotates the given axis with the quaternion, which is equivalent to transforming from the
	/// frame coordinate system to world coordinates.
	point3d rotate(const point3d& aVector) const { return (this->m_orientation * aVector); }

	/// @hidden
	template <class Archive>
	void serialize(Archive& ar, const unsigned int /*version*/)
	{
		ar& m_origin;
		ar& m_orientation;
	}
};

// Computes a 4x4 transformation Matrix for a given Frame
template <typename scalarType>
void FrameToMatrix4x4(const Frame<scalarType>& f, cadcam::mwMatrix<scalarType, 4, 4>& m)
{
	cadcam::mwMatrix<scalarType, 4, 4> translation =
		cadcam::mwMatrixTransformationsFactory<scalarType>::Create3dTranslation(f.getOrigin());

	const MATH::Quaternion<scalarType> orientation = f.getOrientation();

	cadcam::mwTPoint3d<scalarType> oriRotCol[3];
	MATH::QuaternionToSO3<scalarType>(orientation, oriRotCol[0], oriRotCol[1], oriRotCol[2]);

	cadcam::mwMatrix<scalarType, 4, 4> rotation;
	for (int i_col = 0; i_col < 3; ++i_col)
	{
		rotation[0][i_col] = oriRotCol[i_col].x();
		rotation[1][i_col] = oriRotCol[i_col].y();
		rotation[2][i_col] = oriRotCol[i_col].z();
		rotation[3][i_col] = 0;
	}
	rotation[0][3] = 0;
	rotation[1][3] = 0;
	rotation[2][3] = 0;
	rotation[3][3] = 1;

	m = translation * rotation;
};

template <typename scalarType>
const Frame<scalarType> Interpolate_Slerp(
	const Frame<scalarType>& q0,
	const Frame<scalarType>& q1,
	const scalarType t,
	scalarType maxCosForNlerp = (scalarType)0.98481)  // ~10 degrees
{
	return Frame<scalarType>(
		q0.m_origin + t * (q1.m_origin - q0.m_origin),
		Interpolate_Slerp(q0.m_orientation, q1.m_orientation, t, maxCosForNlerp));
}

template <typename scalarType>
const scalarType MATH::Quaternion<scalarType>::getRoll_inDegree() const
{
	typedef point3d Pnt;
	const Quaternion rollOnly =
		(OrientationToQuaternion((*this) * Pnt(0, 0, 1), (scalarType)0).inverse()) * (*this);
	const Pnt rolledX = rollOnly * Pnt(1, 0, 0);
	double cosRoll = (double)rolledX.x();
	double sinRoll = (double)rolledX.y();
	const scalarType rollAngle =
		static_cast<scalarType>(mathdef::ExtATan2(sinRoll, cosRoll) / mathdef::MW_PI * 180);
	return rollAngle;
}

template <typename scalarType>
inline Quaternion<scalarType>::operator mw::Verifier::math::TQuaternion<scalarType>&()
{
	return *static_cast<mw::Verifier::math::TQuaternion<scalarType>*>(static_cast<void*>(this));
}
template <typename scalarType>
inline Quaternion<scalarType>::operator const mw::Verifier::math::TQuaternion<scalarType>&() const
{
	return *static_cast<const mw::Verifier::math::TQuaternion<scalarType>*>(
		static_cast<const void*>(this));
}
};  // namespace MATH

namespace VerifierUtil
{
typedef MATH::Quaternion<float> Quaternion;
typedef MATH::Frame<float> Frame;
};  // namespace VerifierUtil

#endif  //	MW_MWMATHUTILITIES_HPP_
