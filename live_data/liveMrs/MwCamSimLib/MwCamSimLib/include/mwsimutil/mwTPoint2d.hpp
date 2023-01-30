// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef __MWTPOINT2DIMPL_HPP__
#define __MWTPOINT2DIMPL_HPP__

#include "mwCachingInternalDefs.hpp"
#include "mwLogger.hpp"
#include "mwMathConstants.hpp"
#include "mwStringConversions.hpp"
#include "mwcadcamException.hpp"

#include <cmath>
#include <cstddef>
#include <functional>

namespace misc
{
template <typename T>
class MW_5AXUTIL_API mwAutoPointer;
}

namespace mathdef
{
inline double mw_tol(double);
}

namespace mw
{
namespace Verifier
{
namespace math
{
template <typename Int>
struct TIdx2;
template <typename Real>
struct TVector2;
}  // namespace math
}  // namespace Verifier
}  // namespace mw

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

namespace cadcam
{
template <class T>
struct mwTPoint2d;
template <class Archive, class T>
void serialize(Archive& archive, ::cadcam::mwTPoint2d<T>& point3d, unsigned int);
template <class Archive, class T>
void serialize(Archive& archive, const ::cadcam::mwTPoint2d<T>& point3d, const unsigned int);
/// This struct represents a 2d point.
///
/// The 2d point is an array with 2 dimension components (x,y).
#pragma CACHING_INTERNAL_BEGIN
template <class T>
struct MW_5AXUTIL_API mwTPoint2d
{
public:
	// DEFAULT PUBLIC NON-VIRTUAL DESTRUCTOR IS USED IN THIS CLASS, DO NOT
	// ADD ANY VIRTUAL FUNCTIONS. SHOULD NOT BE USED AS A BASE CLASS
	typedef T ValueType;
	typedef typename misc::mwAutoPointer<mwTPoint2d<T>> Ptr;

	mwTPoint2d();
	mwTPoint2d(const T first, const T second);
	bool operator==(const mwTPoint2d& tc) const;
	bool operator!=(const mwTPoint2d& tc) const;
	void x(const T newx);
	void y(const T newy);
	const T x() const;
	const T y() const;
	void operator+=(const mwTPoint2d& ta);
	void operator-=(const mwTPoint2d& ta);
	const T operator~() const;
	void operator*=(const T scalingFactor);
	void operator/=(const T scalingFactor);
	/// Subscript operator, get coordinate value by index
	const T& operator[](const size_t index) const;
	/// Subscript operator, get coordinate value by index
	T& operator[](const size_t index);
	/// Get the address of coordinates array
	const T* GetArray() const;
	/// Get the address of coordinates array
	T* GetArray();
	/// Get squared length
	const T Length2() const;
	/// Tolerate point coordinates below threshold to zero
	///
	///	@param tol Threshold to be used as zero
	void TolerateToZero(const T tol);
	/// Check if the distance between this and given point is within factor
	bool IsTolerant(const mwTPoint2d& src, const T factor = mathdef::mw_tol(T())) const;
	/// Normalize function
	///
	/// Normalize this vector (2d point)
	/// True if it's a null-vector
	bool IsExactlyZero() const;
	const mwTPoint2d<T> Normalize();
	/// Normalized function
	///
	/// Return a normalized vector (2d point)
	const mwTPoint2d<T> Normalized() const;
	/// Get normalized version of this vector
	///
	///	@returns normalized vector or null if this is null-vector
	mwTPoint2d<T> NormalizedOrZero() const;
	/// Convert to string
	misc::mwstring ToString(const unsigned short precision = 5) const;
	// Internal interface with mw::Verifier::math
	operator mw::Verifier::math::TIdx2<T>&();
	operator const mw::Verifier::math::TIdx2<T>&() const;
	operator mw::Verifier::math::TVector2<T>&();
	operator const mw::Verifier::math::TVector2<T>&() const;

	template <class Archive, class TI>
	friend void serialize(Archive&, mwTPoint2d<TI>&, unsigned int);
	template <class Archive, class TI>
	friend void serialize(
		Archive& archive, const cadcam::mwTPoint2d<TI>& point3d, const unsigned int);

private:
	T m_elems[2];
};

template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mwTPoint2d<T>& toDump)
{
	os << _T("class cadcam::mwTPoint2d\n");
	// public properties from cadcam::mwTPoint2d class.
	os << _T("x                  = ") << toDump.x() << _T("\n");
	os << _T("y                  = ") << toDump.y() << _T("\n");
	return os;
}

typedef mwTPoint2d<double> mwPoint2d;
typedef mwTPoint2d<double> mwVector2d;
typedef mwTPoint2d<float> mwPoint2df;
typedef mwTPoint2d<float> mwVector2df;

template <class T>
mwTPoint2d<T> operator-(const mwTPoint2d<T>& p);
template <class T>
mwTPoint2d<T> operator+(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second);
template <class T>
mwTPoint2d<T> operator-(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second);
template <class T>
mwTPoint2d<T> operator*(const mwTPoint2d<T>& pt, const T factor);
template <class T>
mwTPoint2d<T> operator*(const T factor, const mwTPoint2d<T>& pt);
template <class T>
mwTPoint2d<T> operator/(const mwTPoint2d<T>& pt, const T factor);
template <class T>
T operator*(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second);
template <class T>
T operator%(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second);

template <class T>
misc::mwstring mwTPoint2d<T>::ToString(const unsigned short precision) const
{
	misc::mwstring res;
	res += _T("(");
	res += misc::from_value(x(), precision) + _T(", ") + misc::from_value(y(), precision);
	res += _T(")");
	return res;
}

/// Tolerate point coordinates to zero
template <class T>
inline void cadcam::mwTPoint2d<T>::TolerateToZero(const T tol)
{
	if (mathdef::is_zero(m_elems[0], tol))
	{
		m_elems[0] = 0;
	}
	if (mathdef::is_zero(m_elems[1], tol))
	{
		m_elems[1] = 0;
	}
}

template <class T>
const mwTPoint2d<T> mwTPoint2d<T>::Normalized() const
{
	return mwTPoint2d(*this).Normalize();
}

/// NormalizedOrZero function
///
/// Return a normalized vector (2d point), and don't throw if the vector is not normalizable
template <class T>
inline mwTPoint2d<T> cadcam::mwTPoint2d<T>::NormalizedOrZero() const
{
	mwTPoint2d result(*this);
	if (!IsExactlyZero())
		result.Normalize();
	return result;
}

template <class T>
const mwTPoint2d<T> mwTPoint2d<T>::Normalize()
{
	if (m_elems[0] == 0. && m_elems[1] == 0.)
		throw mwcadcamException(mwcadcamException::CANNOT_NORMALIZE_NULL_VEC);
	(*this) /= ~(*this);
	return *this;
}
template <class T>
bool mwTPoint2d<T>::IsTolerant(
	const mwTPoint2d& src, const T factor /*= mathdef::mw_tol(T())*/) const
{
	return mathdef::is_zero((src - *this).Length2(), factor * factor);
}
template <class T>
inline bool cadcam::mwTPoint2d<T>::IsExactlyZero() const
{
	return (m_elems[0] == 0 && m_elems[1] == 0);
}
template <class T>
const T mwTPoint2d<T>::Length2() const
{
	return (*this) * (*this);  // reuse scalar multiplication
}
template <class T>
T* mwTPoint2d<T>::GetArray()
{
	return static_cast<T*>(m_elems);
}
template <class T>
const T* mwTPoint2d<T>::GetArray() const
{
	return static_cast<const T*>(m_elems);
}
template <class T>
T& mwTPoint2d<T>::operator[](const size_t index)
{
	if (index >= 2)
	{
		throw mwcadcamException(mwcadcamException::COORDINATE_INDEX_OUT_OF_BOUNDS);
	}
	return m_elems[index];
}
template <class T>
const T& mwTPoint2d<T>::operator[](const size_t index) const
{
	if (index >= 2)
	{
		throw mwcadcamException(mwcadcamException::COORDINATE_INDEX_OUT_OF_BOUNDS);
	}
	return m_elems[index];
}
template <class T>
void mwTPoint2d<T>::operator/=(const T scalingFactor)
{
	m_elems[0] /= scalingFactor;
	m_elems[1] /= scalingFactor;
}
template <class T>
void mwTPoint2d<T>::operator*=(const T scalingFactor)
{
	m_elems[0] *= scalingFactor;
	m_elems[1] *= scalingFactor;
}
template <class T>
const T mwTPoint2d<T>::operator~() const
{
	return ::sqrt(m_elems[0] * m_elems[0] + m_elems[1] * m_elems[1]);
}
template <class T>
void mwTPoint2d<T>::operator-=(const mwTPoint2d& ta)
{
	m_elems[0] -= ta.m_elems[0];
	m_elems[1] -= ta.m_elems[1];
}
template <class T>
void mwTPoint2d<T>::operator+=(const mwTPoint2d& ta)
{
	m_elems[0] += ta.m_elems[0];
	m_elems[1] += ta.m_elems[1];
}
template <class T>
const T mwTPoint2d<T>::y() const
{
	return m_elems[1];
}
template <class T>
const T mwTPoint2d<T>::x() const
{
	return m_elems[0];
}
template <class T>
void mwTPoint2d<T>::y(const T newy)
{
	m_elems[1] = newy;
}
template <class T>
void mwTPoint2d<T>::x(const T newx)
{
	m_elems[0] = newx;
}
template <class T>
bool mwTPoint2d<T>::operator!=(const mwTPoint2d& tc) const
{
	return !((*this) == tc);
}
template <class T>
bool mwTPoint2d<T>::operator==(const mwTPoint2d& tc) const
{
	return m_elems[0] == tc.m_elems[0] && m_elems[1] == tc.m_elems[1];
}

template <class T>
mwTPoint2d<T>::mwTPoint2d(const T first, const T second)
{
	m_elems[0] = first;
	m_elems[1] = second;
}
template <class T>
mwTPoint2d<T>::mwTPoint2d()
{
	m_elems[0] = 0;
	m_elems[1] = 0;
}

template <class T>
mwTPoint2d<T>::operator mw::Verifier::math::TIdx2<T>&()
{
	return *static_cast<mw::Verifier::math::TIdx2<T>*>(static_cast<void*>(this));
}
template <class T>
mwTPoint2d<T>::operator const mw::Verifier::math::TIdx2<T>&() const
{
	return *static_cast<const mw::Verifier::math::TIdx2<T>*>(static_cast<const void*>(this));
}

template <class T>
mwTPoint2d<T>::operator mw::Verifier::math::TVector2<T>&()
{
	return *static_cast<mw::Verifier::math::TVector2<T>*>(static_cast<void*>(this));
}
template <class T>
mwTPoint2d<T>::operator const mw::Verifier::math::TVector2<T>&() const
{
	return *static_cast<const mw::Verifier::math::TVector2<T>*>(static_cast<const void*>(this));
}
template <class T>
mwTPoint2d<T> operator-(const mwTPoint2d<T>& p)
{
	return mwTPoint2d<T>(-p.x(), -p.y());
}
template <class T>
mwTPoint2d<T> operator+(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
{
	return mwTPoint2d<T>(first.x() + second.x(), first.y() + second.y());
}
template <class T>
mwTPoint2d<T> operator-(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
{
	return mwTPoint2d<T>(first.x() - second.x(), first.y() - second.y());
}
template <class T>
mwTPoint2d<T> operator*(const mwTPoint2d<T>& pt, const T factor)
{
	return mwTPoint2d<T>(pt.x() * factor, pt.y() * factor);
}
template <class T>
mwTPoint2d<T> operator*(const T factor, const mwTPoint2d<T>& pt)
{
	return mwTPoint2d<T>(pt.x() * factor, pt.y() * factor);
}
template <class T>
mwTPoint2d<T> operator/(const mwTPoint2d<T>& pt, const T factor)
{
	return mwTPoint2d<T>(pt.x() / factor, pt.y() / factor);
}
template <class T>
T operator*(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
{
	return first.x() * second.x() + first.y() * second.y();
}
/// Cross (vector) product of two 2d points (= determinant)
template <class T>
T operator%(const mwTPoint2d<T>& first, const mwTPoint2d<T>& second)
{
	return first.x() * second.y() - second.x() * first.y();
}
#pragma CACHING_INTERNAL_END
}  // namespace cadcam

#ifndef MW_USE_VS2008_COMPATIBILITY
// With this you can create std::unordered_map or std::unordered_set of cadcam::mwTPoint2d
template <class T>
struct std::hash<cadcam::mwTPoint2d<T>>
{
	size_t operator()(const cadcam::mwTPoint2d<T>& p) const noexcept
	{
		size_t x = std::hash<T>{}(p.x());
		size_t y = std::hash<T>{}(p.y());
		return x ^ (y << 1);
	}
};
#endif

#endif  // __MWTPOINT2DIMPL_HPP__
