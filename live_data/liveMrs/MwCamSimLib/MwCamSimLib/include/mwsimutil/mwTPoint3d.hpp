// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPOINT3D_HPP_
#define MW_MWTPOINT3D_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwLanguageFeatures.hpp"
#include "mwLogger.hpp"
#include "mwMathConstants.hpp"
#include "mwMatrix.hpp"
#include "mwcadcamException.hpp"

#include <cstddef>
#include <functional>

namespace mathdef
{
namespace mwAutodiff
{
template <typename T, int N>
struct ScalarT;
}
}  // namespace mathdef

template <typename T, int N>
mathdef::mwAutodiff::ScalarT<T, N> sqrt(const mathdef::mwAutodiff::ScalarT<T, N>& a);

// MW_FORCEINLINE macro is considered as obsolete; please don't use it without strong need
// #pragma deprecated(MW_FORCEINLINE)
#ifndef MW_FORCEINLINE
#if defined(_WIN32)
#define MW_FORCEINLINE __forceinline
#else
#define MW_FORCEINLINE inline
#endif
#endif

namespace misc
{
template <typename T>
class MW_5AXUTIL_API mwAutoPointer;
class mwstring;
}  // namespace misc

namespace mathdef
{
inline double mw_tol(double);
inline float mw_tol(float);
}  // namespace mathdef

namespace mw
{
namespace Verifier
{
namespace math
{
template <typename Int>
struct TIdx3;
template <typename Real>
struct TVector3;
}  // namespace math
}  // namespace Verifier
}  // namespace mw

namespace cadcam
{
template <class T>
struct mwTPoint3d;
template <class Archive, class T>
void serialize(Archive& archive, ::cadcam::mwTPoint3d<T>& point3d, unsigned int);
template <class Archive, class T>
void serialize(Archive& archive, const ::cadcam::mwTPoint3d<T>& point3d, const unsigned int);

template <class T, int rows, int columns>
struct mwMatrix;

#pragma CACHING_INTERNAL_BEGIN
/// This struct represents a 3d point.
///
/// The 3D point is an array with 3 elements (x,y,z)
template <class T>
struct MW_5AXUTIL_API mwTPoint3d
{
	// ATTENTION: Don't add virtual functions to this class to avoid global performance regressions!
public:
	typedef T ValueType;
	typedef typename misc::mwAutoPointer<mwTPoint3d<T>> Ptr;

	mwTPoint3d();
	mwTPoint3d(const T first, const T second, const T third);

	bool operator==(const mwTPoint3d& tc) const;
	bool operator!=(const mwTPoint3d& tc) const;

	void x(const T newx);
	void y(const T newy);
	void z(const T newz);
	T x() const;
	T y() const;
	T z() const;

	const T& operator[](const size_t index) const;
	T& operator[](const size_t index);
	const T* GetArray() const;
	T* GetArray();

	void operator+=(const mwTPoint3d& ta);
	void operator-=(const mwTPoint3d& ta);
	/// Vector length
	const T operator~() const;
	/// Scalar multiplication
	void operator*=(const T scaleFactor);
	/// Scalar division
	void operator/=(const T scaleFactor);

	/// Get square of a length
	T Length2() const;
	/// IsTolerant function
	///
	///	@param src Point to compare to
	///	@param factor distance
	///	@returns true if points are within factor distance to each other
	bool IsTolerant(const mwTPoint3d& src, const T factor = mathdef::mw_tol(T())) const;
	MW_DEPRECATED("Deprecated since 2016.08, please use IsTolerant()")
	bool is_eq(const mwTPoint3d& toCompare, const T tolerance = mathdef::mw_tol(T())) const;
	
	/// Check if coordinates of a given point are within tolerance to this
	/// @param src point to compare to
	/// @param tolerance max epsilon for deviation
	bool AreCoordinatesEqual(const mwTPoint3d& src, const T tolerance = mathdef::mw_tol(T())) const;
	/// True if it's a null-vector
	bool IsExactlyZero() const;
	/// Normalize this vector
	const mwTPoint3d<T>& Normalize();
	/// Get normalized version of this vector
	///
	///	@throws mwException if it's the null-vector
	mwTPoint3d<T> Normalized() const;
	/// Get normalized version of this vector
	///
	///	@returns normalized vector or null if this is null-vector
	mwTPoint3d<T> NormalizedOrZero() const;

	/// Tolerate point coordinates below threshold to zero
	///
	///	@param tol Threshold to be used as zero
	void TolerateToZero(const T tol);

	/// Get any orthogonal vector to this
	mwTPoint3d<T> Orthogonal() const;

	/// Transform the point using 3x3 matrix + translation vector
	///
	///	@param matrix 3x3 transformation matrix
	///	@param translation Translation 3D vector
	void Transform3d(const mwMatrix<T, 3, 3>& matrix, const mwTPoint3d<T>& translation);
	/// Transform the point using 3x3 matrix
	void Transform(const mwMatrix<T, 3, 3>& matrix3d);
	/// Transform the point using 4x4 matrix
	///
	///	@param homomatrix Homogeneous transformation matrix
	///	@param isVector Is this a vector we try to transform or a point?
	///	If it is the vector, then we don't use the homogeneous coordinate
	void Transform(const mwMatrix<T, 4, 4>& homomatrix, const bool isVector = false);

	/// For internal use only
	misc::mwstring ToString() const;
	misc::mwstring ToString(unsigned short decimalPlaces) const;
	template <class Archive, class TI>
	friend void serialize(Archive& archive, ::cadcam::mwTPoint3d<TI>& point3d, unsigned int);
	template <class Archive, class TI>
	friend void serialize(
		Archive& archive, const cadcam::mwTPoint3d<TI>& point3d, const unsigned int);

	/// Internal interface with Verifier::math
	operator mw::Verifier::math::TIdx3<T>&();
	/// Internal interface with Verifier::math
	operator const mw::Verifier::math::TIdx3<T>&() const;
	/// Internal interface with Verifier::math
	operator mw::Verifier::math::TVector3<T>&();
	/// Internal interface with Verifier::math
	operator const mw::Verifier::math::TVector3<T>&() const;

private:
	T m_elems[3];
};
#pragma CACHING_INTERNAL_END

template <class T>
inline mwTPoint3d<T> operator-(const mwTPoint3d<T>& p);

template <class T>
inline mwTPoint3d<T> operator+(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second);

template <class T>
inline mwTPoint3d<T> operator-(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second);

template <class T>
inline mwTPoint3d<T> operator*(const mwTPoint3d<T>& pt, const T factor);

template <class T>
inline mwTPoint3d<T> operator*(const T factor, const mwTPoint3d<T>& pt);

template <class T>
inline mwTPoint3d<T> operator/(const mwTPoint3d<T>& pt, const T factor);

template <class T>
inline T operator*(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second);

template <class T>
inline mwTPoint3d<T> operator%(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second);

/// Convert to string (with precision of 5 decimal places)
template <class T>
inline misc::mwstring cadcam::mwTPoint3d<T>::ToString() const
{
	return ToString(5u);
}
template <class T>
inline bool cadcam::mwTPoint3d<T>::is_eq(
	const mwTPoint3d& toCompare, const T tolerance /*= mw_tol(T()) */) const
{
	const mwTPoint3d diff(toCompare - *this);
	return mathdef::is_zero(diff.Length2(), tolerance * tolerance);
}
/// Convert to string
template <class T>
inline misc::mwstring cadcam::mwTPoint3d<T>::ToString(unsigned short decimalPlaces) const
{
	misc::mwstring res;
	res += _T("(");
	res += misc::from_value(x(), decimalPlaces) + _T(", ") + misc::from_value(y(), decimalPlaces) +
		_T(", ") + misc::from_value(z(), decimalPlaces);
	res += _T(")");
	return res;
}

template <class T>
inline bool cadcam::mwTPoint3d<T>::AreCoordinatesEqual(
	const mwTPoint3d& tc, const T tolerance /*= mw_tol(T()) */) const
{
#ifdef _WIN64
	return mathdef::is_eq(
			   static_cast<double>(x()),
			   static_cast<double>(tc.x()),
			   static_cast<double>(tolerance)) &&
		mathdef::is_eq(
			   static_cast<double>(y()),
			   static_cast<double>(tc.y()),
			   static_cast<double>(tolerance)) &&
		mathdef::is_eq(
			   static_cast<double>(z()),
			   static_cast<double>(tc.z()),
			   static_cast<double>(tolerance));
#else
	return mathdef::is_eq(x(), tc.x(), tolerance) && mathdef::is_eq(y(), tc.y(), tolerance) &&
		mathdef::is_eq(z(), tc.z(), tolerance);
#endif
}

template <class T>
inline mwTPoint3d<T> cadcam::mwTPoint3d<T>::Orthogonal() const
{
	mwTPoint3d<T> cur(Normalized());
	mwTPoint3d<T> o(mwTPoint3d<T>(cur.y(), cur.z(), cur.x()) % cur);
	if (o.x() == 0 && o.y() == 0 && o.z() == 0)
		return (mwTPoint3d<T>(0, 1, 0) % cur).Normalized();
	else
		return o.Normalized();
}

/// Tolerate point coordinates to zero
template <class T>
inline void cadcam::mwTPoint3d<T>::TolerateToZero(const T tol)
{
	if (mathdef::is_zero(m_elems[0], tol))
	{
		m_elems[0] = 0;
	}
	if (mathdef::is_zero(m_elems[1], tol))
	{
		m_elems[1] = 0;
	}
	if (mathdef::is_zero(m_elems[2], tol))
	{
		m_elems[2] = 0;
	}
}

template <class T>
inline mwTPoint3d<T> cadcam::mwTPoint3d<T>::Normalized() const
{
	mwTPoint3d result(*this);
	result.Normalize();
	return result;
}

/// NormalizedOrZero function
///
/// Return a normalized vector (3d point), and don't throw if the vector is not normalizable
template <class T>
inline mwTPoint3d<T> cadcam::mwTPoint3d<T>::NormalizedOrZero() const
{
	mwTPoint3d result(*this);
	if (!IsExactlyZero())
		result.Normalize();
	return result;
}

/// Normalize function
///
/// Normalize this vector (3d point)
template <class T>
inline const mwTPoint3d<T>& cadcam::mwTPoint3d<T>::Normalize()
{
	const T maxElem = mathdef::mw_max(mathdef::Abs(x()), mathdef::Abs(y()), mathdef::Abs(z()));
	if (maxElem == 0.0)
		throw mwcadcamException(mwcadcamException::CANNOT_NORMALIZE_NULL_VEC);

	// check value is in range [sqrt(FLT_MIN), sqrt(FLT_MAX)/3]
	// to prevent denormalized values
	if (maxElem > 6.1489145076E+18 || maxElem < 1.084202172e-19)
	{
		(*this) /= maxElem;
	}
	(*this) /= ~(*this);
	return *this;
}

/// Divide each 3d component by a factor
///	@param scaleFactor const reference to a factor
template <class T>
inline void cadcam::mwTPoint3d<T>::operator/=(const T scaleFactor)
{
	m_elems[0] /= scaleFactor;
	m_elems[1] /= scaleFactor;
	m_elems[2] /= scaleFactor;
}

/// Multiply each 3d component with a factor
///	@param scaleFactor const reference to a factor
template <class T>
inline void cadcam::mwTPoint3d<T>::operator*=(const T scaleFactor)
{
	m_elems[0] *= scaleFactor;
	m_elems[1] *= scaleFactor;
	m_elems[2] *= scaleFactor;
}

template <class T>
inline bool cadcam::mwTPoint3d<T>::IsExactlyZero() const
{
	return (m_elems[0] == 0 && m_elems[1] == 0 && m_elems[2] == 0);
}

template <class T>
inline bool cadcam::mwTPoint3d<T>::IsTolerant(
	const mwTPoint3d& src, const T factor /*= mathdef::mw_tol(T())*/) const
{
	return mathdef::is_zero((src - *this).Length2(), factor * factor);
}

/// Squared length
///
/// Returns squared length of the vector represented by the 3d point
///	@returns constant length of the vector represented by the 3d point.
template <class T>
inline T cadcam::mwTPoint3d<T>::Length2() const
{
	return (*this) * (*this);  // reuse scalar multiplication
}

/// Subtract each component of a 3d point with another
///	@param ta const reference of a 3d point
template <class T>
inline void cadcam::mwTPoint3d<T>::operator-=(const mwTPoint3d& ta)
{
	m_elems[0] -= ta.m_elems[0];
	m_elems[1] -= ta.m_elems[1];
	m_elems[2] -= ta.m_elems[2];
}

/// Add each component of a 3d point to another
///	@param ta const reference of a 3d point
template <class T>
inline void cadcam::mwTPoint3d<T>::operator+=(const mwTPoint3d& ta)
{
	m_elems[0] += ta.m_elems[0];
	m_elems[1] += ta.m_elems[1];
	m_elems[2] += ta.m_elems[2];
}

/// Get the address of coordinates array
template <class T>
inline T* cadcam::mwTPoint3d<T>::GetArray()
{
	return static_cast<T*>(m_elems);
}

/// Get the address of coordinates array
template <class T>
inline const T* cadcam::mwTPoint3d<T>::GetArray() const
{
	return static_cast<const T*>(m_elems);
}

/// Subscript operator, get coordinate value by index
template <class T>
inline T& cadcam::mwTPoint3d<T>::operator[](const size_t index)
{
	if (index >= 3)
		throw mwcadcamException(mwcadcamException::COORDINATE_INDEX_OUT_OF_BOUNDS);

	return m_elems[index];
}

/// Subscript operator, get coordinate value by index
template <class T>
inline const T& cadcam::mwTPoint3d<T>::operator[](const size_t index) const
{
	if (index >= 3)
		throw mwcadcamException(mwcadcamException::COORDINATE_INDEX_OUT_OF_BOUNDS);

	return m_elems[index];
}

/// Get z-coordinate
///
/// Gets the z-coordinate of the 3d point as a reference.
///	@returns constant reference to the z-coordinate
template <class T>
inline T cadcam::mwTPoint3d<T>::z() const
{
	return m_elems[2];
}

/// Get y-coordinate
///
/// Gets the y-coordinate of the 3d point as a reference.
///	@returns constant reference to the y-coordinate
template <class T>
inline T cadcam::mwTPoint3d<T>::y() const
{
	return m_elems[1];
}

/// Get x-coordinate
///
/// Gets the x-coordinate of the 3d point as a reference.
///	@returns constant reference to the x-coordinate
template <class T>
inline T cadcam::mwTPoint3d<T>::x() const
{
	return m_elems[0];
}

/// Set 3d point
///
/// Sets new z-coordinate of the 3d point.
///	@param newz const z-coordinate of the 3d point
template <class T>
inline void cadcam::mwTPoint3d<T>::z(const T newz)
{
	m_elems[2] = newz;
}

/// Set 3d point
///
/// Sets new y-coordinate of the 3d point.
///	@param newy const y-coordinate of the 3d point
template <class T>
inline void cadcam::mwTPoint3d<T>::y(const T newy)
{
	m_elems[1] = newy;
}

/// Set 3d point
///
/// Sets new x-coordinate of the 3d point.
///	@param newx const x-coordinate of the 3d point
template <class T>
inline void cadcam::mwTPoint3d<T>::x(const T newx)
{
	m_elems[0] = newx;
}

/// Are given points equal?
/// @param tc tool to compare the current tool with
/// @returns <b>false</b> if both tools contain the same parameters,
/// <b>true</b> otherwise
template <class T>
inline bool cadcam::mwTPoint3d<T>::operator!=(const mwTPoint3d& tc) const
{
	return !((*this) == tc);
}

/// Are given points equal?
/// @param tc tool to compare the current tool with
/// @returns <b>true</b> if both tools contain the same parameters,
/// <b>false</b> otherwise
template <class T>
inline bool cadcam::mwTPoint3d<T>::operator==(const mwTPoint3d& tc) const
{
	return (
		m_elems[0] == tc.m_elems[0] && m_elems[1] == tc.m_elems[1] && m_elems[2] == tc.m_elems[2]);
}

/// Set 3d point
///
/// Sets the 3d point to the new position.
///	@param first constant x-coordinate of the 3d point
///	@param second constant y-coordinate of the 3d point
///	@param third constant z-coordinate of the 3d point
template <class T>
inline cadcam::mwTPoint3d<T>::mwTPoint3d(const T first, const T second, const T third)
{
	m_elems[0] = first;
	m_elems[1] = second;
	m_elems[2] = third;
}

/// Sets 3d point to origin.
template <class T>
inline cadcam::mwTPoint3d<T>::mwTPoint3d()
{
	m_elems[0] = 0;
	m_elems[1] = 0;
	m_elems[2] = 0;
}

/// Returns length of the vector represented by the 3d point
///	@returns constant length of the vector represented by the 3d point.
#ifdef _WIN64
template <>
inline const float mwTPoint3d<float>::operator~() const
{
	return static_cast<float>(::sqrt(static_cast<double>(
		m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2])));
}

// avoid ambiguous call for long (VS 2008, Release Unicode x64)
template <>
inline const long mwTPoint3d<long>::operator~() const
{
	return static_cast<long>(::sqrt(static_cast<double>(
		m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2])));
}

// avoid ambiguous call for int (VS 2008, Release Unicode x64)
template <>
inline const int mwTPoint3d<int>::operator~() const
{
	return static_cast<int>(::sqrt(static_cast<double>(
		m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2])));
}
#endif

template <class T>
inline const T mwTPoint3d<T>::operator~() const
{
	return static_cast<T>(::sqrt(
		// for the generic implementation don't cast to double
		// since this might be used with types that can't be
		// recovered from double (eg mwAutodiff::ScalarT)
		m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1] + m_elems[2] * m_elems[2]));
}

template <class T>
inline mwTPoint3d<T>::operator mw::Verifier::math::TIdx3<T>&()
{
	return *static_cast<mw::Verifier::math::TIdx3<T>*>(static_cast<void*>(this));
}
template <class T>
inline mwTPoint3d<T>::operator const mw::Verifier::math::TIdx3<T>&() const
{
	return *static_cast<const mw::Verifier::math::TIdx3<T>*>(static_cast<const void*>(this));
}

template <class T>
inline mwTPoint3d<T>::operator mw::Verifier::math::TVector3<T>&()
{
	return *static_cast<mw::Verifier::math::TVector3<T>*>(static_cast<void*>(this));
}
template <class T>
inline mwTPoint3d<T>::operator const mw::Verifier::math::TVector3<T>&() const
{
	return *static_cast<const mw::Verifier::math::TVector3<T>*>(static_cast<const void*>(this));
}


typedef cadcam::mwTPoint3d<double> mwPoint3d;
typedef cadcam::mwTPoint3d<double> mwVector3d;
typedef cadcam::mwTPoint3d<float> mwPoint3df;
typedef cadcam::mwTPoint3d<float> mwVector3df;

/// Change sign of each 3d point component to opposite
/// @param p const reference of a 3d point
/// @returns negated const 3d point
template <class T>
inline mwTPoint3d<T> operator-(const mwTPoint3d<T>& p)
{
	return mwTPoint3d<T>(-p.x(), -p.y(), -p.z());
}

/// Add each component of a 3d point to another
/// @param first const reference of a 3d point
/// @param second const reference of a 3d point
/// @returns added const 3d point
template <class T>
inline mwTPoint3d<T> operator+(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
{
	return mwTPoint3d<T>(first.x() + second.x(), first.y() + second.y(), first.z() + second.z());
}

/// Subtract each 3d point component from another
/// @param first const reference of a 3d point
/// @param second const reference of a 3d point
/// @returns subtracted const 3d point
template <class T>
inline mwTPoint3d<T> operator-(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
{
	return mwTPoint3d<T>(first.x() - second.x(), first.y() - second.y(), first.z() - second.z());
}

/// Multiply each 3d component with a factor.
/// @param pt const reference to a 3d point
/// @param factor const reference to a factor to multiply with
/// @returns new 3d point object
template <class T>
inline mwTPoint3d<T> operator*(const mwTPoint3d<T>& pt, const T factor)
{
	return mwTPoint3d<T>(pt.x() * factor, pt.y() * factor, pt.z() * factor);
}

/// Multiply each 3d component with a factor.
/// @param factor const reference to a factor to multiply with
/// @param pt const reference to a 3d point
/// @returns new 3d point object
template <class T>
inline mwTPoint3d<T> operator*(const T factor, const mwTPoint3d<T>& pt)
{
	return mwTPoint3d<T>(pt.x() * factor, pt.y() * factor, pt.z() * factor);
}

/// Divide each 3d component with a factor.
/// @param pt const reference to a 3d point
/// @param factor const reference to a factor to divide with
/// @returns new 3d point object
template <class T>
inline mwTPoint3d<T> operator/(const mwTPoint3d<T>& pt, const T factor)
{
	return mwTPoint3d<T>(pt.x() / factor, pt.y() / factor, pt.z() / factor);
}

/// Scalar product of to 3d points.
/// @param first const reference to a 3d point
/// @param second const reference to a 3d point
/// @returns const scalar
template <class T>
inline T operator*(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
{
	return first.x() * second.x() + first.y() * second.y() + first.z() * second.z();
}

/// Cross (vector) product of to 3d points
/// @param first const reference to a 3d point
/// @param second const reference to a 3d point
/// @returns const 3d point
template <class T>
inline mwTPoint3d<T> operator%(const mwTPoint3d<T>& first, const mwTPoint3d<T>& second)
{
	return mwTPoint3d<T>(
		first.y() * second.z() - first.z() * second.y(),
		first.z() * second.x() - first.x() * second.z(),
		first.x() * second.y() - first.y() * second.x());
}


template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const mwTPoint3d<T>& toDump)
{
	os << _T("class cadcam::mwTPoint3d\n");
	// public properties from cadcam::mwTPoint3d class.
	os << _T("x                  = ") << toDump.x() << _T("\n");
	os << _T("y                  = ") << toDump.y() << _T("\n");
	os << _T("z                  = ") << toDump.z() << _T("\n");
	return os;
}

#define mwTVector3d mwTPoint3d
}  // namespace cadcam

#ifndef MW_USE_VS2008_COMPATIBILITY
/// With this you can create std::unordered_map or std::unordered_set of cadcam::mwTPoint3d
template <class T>
struct MW_5AXUTIL_API std::hash<cadcam::mwTPoint3d<T>>
{
	size_t operator()(const cadcam::mwTPoint3d<T>& p) const noexcept
	{
		size_t x = std::hash<T>{}(p.x());
		size_t y = std::hash<T>{}(p.y());
		size_t z = std::hash<T>{}(p.z());
		return x ^ (y << 1) ^ (z << 2);
	}
};
#endif

#endif  // MW_MWTPOINT3D_HPP_
