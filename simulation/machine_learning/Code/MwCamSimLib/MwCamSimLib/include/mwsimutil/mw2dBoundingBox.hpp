// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DBOUNDINGBOX_HPP_
#define MW_MW2DBOUNDINGBOX_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwException.hpp"
#include "mwMathConstants.hpp"
#include "mwTPoint2d.hpp"
#include "mwTPointUtils.hpp"


#pragma CACHING_INTERNAL_BEGIN

namespace mw
{
namespace Verifier
{
namespace geom
{
template <typename Real>
struct TAlignedBox2;
}
}  // namespace Verifier
}  // namespace mw

namespace cadcam
{
// serialize
template <class T>
class mw2dBoundingBox;

template <class Archive, typename T>
void serialize(Archive& archive, mw2dBoundingBox<T>& bbox, const unsigned int);
// end serialize

/// @class mw2dBoundingBox
/// Implements 2D axis-aligned bounding box
template <class T>
class MW_5AXUTIL_API mw2dBoundingBox
{
public:
	typedef T ValueType;
	typedef mwTPoint2d<T> TPoint2d;
	MW_DEPRECATED("Deprecated since 2018.12. Please, do not use it.")
	typedef mwTPoint2d<T> bboxCorner;

	/// Constructor
	///
	///	Constructs an uninitialized bounding box
	///	@see IsInitialized
	inline mw2dBoundingBox();
	/// Constructor
	///
	///	This constructor takes two corners as parameters
	///	@param corner1 - first corner
	///	@param corner2 - second corner
	inline mw2dBoundingBox(const TPoint2d& corner1, const TPoint2d& corner2);
	/// Set Bounding Box Corners
	///
	///	@param corner1 - first corner
	///	@param corner2 - second corner
	inline void SetCorners(const TPoint2d& corner1, const TPoint2d& corner2);

	/// Equality operator
	inline bool operator==(const mw2dBoundingBox& toCompare) const;
	/// Inequality operator
	inline bool operator!=(const mw2dBoundingBox& toCompare) const;

	/// Returns the minimum x.
	///
	/// @see GetMin()
	inline T GetMinX() const { return GetMin().x(); }
	/// Returns the minimum y.
	///
	/// @see GetMin()
	inline T GetMinY() const { return GetMin().y(); }

	/// Returns the minimum corner
	///
	/// @return the minimum corner of the bounding box
	/// @note The minimum corner of an uninitialized bounding box is TPoint2d(max_value, max_value).
	///		However it is recommended to check if a bounding box is initialized before calling
	///GetMin
	inline const TPoint2d& GetMin() const { return m_minCorner; }

	/// Returns the maximum x.
	///
	/// @see GetMax()
	inline T GetMaxX() const { return GetMax().x(); }
	/// Returns the maximum y.
	///
	/// @see GetMax()
	inline T GetMaxY() const { return GetMax().y(); }

	/// Returns the maximum corner
	///
	/// @return the maximum corner of the bounding box
	/// @note The maximum corner of an uninitialized bounding box is TPoint2d(-max_value,
	/// -max_value). 	However it is recommended to check if a bounding box is initialized before
	/// calling GetMax
	inline const TPoint2d& GetMax() const { return m_maxCorner; }

	/// Returns the x component of the size.
	///
	/// @see GetSize()
	inline T GetSizeX() const { return GetSize().x(); }
	/// Returns the y component of the size.
	///
	/// @see GetSize()
	inline T GetSizeY() const { return GetSize().y(); }

	/// Returns the size of the bounding box
	///
	/// The size of the bounding box is equivalent to its diagonal
	/// @return the size the bounding box
	/// @throw misc::mwException if the bounding box is uninitialized
	inline TPoint2d GetSize() const;

	/// GetDiagonalLength
	///
	/// @returns the length of the main diagonal of the bounding box
	/// @throw misc::mwException if the bounding box is uninitialized
	inline T GetDiagonalLength() const { return ~GetSize(); }

	/// += Operator
	///
	///	Makes the union of the two bounding boxes
	inline mw2dBoundingBox& operator+=(const mw2dBoundingBox& boxToAdd);
	/// + Operator
	///
	/// @returns the union of the two bounding boxes
	inline mw2dBoundingBox operator+(const mw2dBoundingBox& boxToAdd) const;

	/// IsSinglePoint
	///
	/// @returns true if the corners are pointing to the same point, otherwise false (even if the
	/// bounding box is uninitialized)
	inline bool IsSinglePoint() const;
	/// IsLine
	///
	/// @returns true if one or more of the dimensions is 0.0, otherwise false (even if the bounding
	/// box is uninitialized)
	/// @note The function return true if IsSinglePoint() == true
	inline bool IsLine() const;
	/// IsOutside
	///
	///	@returns true if point not in the bounding box or on their boundary
	///	@note if the bounding box is not initialized, the behavior is undefined
	inline bool IsOutside(const mwTPoint2d<T>& ta, T tolerance = mathdef::mw_tol(T())) const;
	/// GetCenter
	///
	///	@see GetCenter()
	inline void GetCenter(TPoint2d& p) const;
	/// GetCenter
	///
	/// @returns the center of the bounding box
	/// @throws misc::mwException if the bounding box is uninitialized
	inline TPoint2d GetCenter() const;

	/// Sets the minimum x.
	inline void SetMinX(const T value);
	/// Sets the minimum y.
	inline void SetMinY(const T value);
	/// Sets the maximum x.
	inline void SetMaxX(const T value);
	/// Sets the maximum y.
	inline void SetMaxY(const T value);
	/// Enlarge bbox so that bbox contains specified point.
	///
	/// The point is added to the bounding box, such that the point is contained by the bounding box
	/// afterwards
	/// @note An uninitialized bounding box is initialized by this call.
	inline void EnlargeForPoint(const mwTPoint2d<T>& point);
	/// Tests if the bounding box was initialized
	///
	/// By default, a bounding box is uninitialized. In this state, the bounding box can be
	/// considered to be empty, but unpositioned. Some function are able to handle the uninitialized
	/// state, while others will throw an exception. Please check each functions documentation how
	/// the uninitialized state is handled. A bounding box can be initialized by adding a point to
	/// it, e.g. by calling EnlargeForPoint or SetCorners
	/// @returns false if the bbox is in the uninitialized state, otherwise true
	inline bool IsInitialized() const;
	/// Uninitialize bounding box
	///
	/// @see IsInitialized
	inline void Uninitialize();
	/// Check if point is in bounding box
	///
	/// @returns true if point is in bounding box or on the border
	inline bool Contains(const TPoint2d& p) const;
	/// Inflate bounding box
	///
	/// If one or more of the delta values are negative and would cause one or more sides of the
	/// bounding box to become negative an uninitialized bounding box is returned.
	/// @note If the bounding box is uninitialized it will not be altered and remains uninitialized.
	/// @param dx delta to add to both edges in x direction
	/// @param dy delta to add to both edges in y direction
	inline mw2dBoundingBox<T>& Inflate(const T dx, const T dy);
	/// Inflate bounding box
	///
	/// Inflates the bounding box uniformly
	/// @see @ref Inflate(T,T)
	inline mw2dBoundingBox<T>& Inflate(const T d) { return Inflate(d, d); }

	/// Restricts this bounding box to the Intersection of this and other.
	/// If the bounding boxes do not intersect, the bounding box will be uninitialized.
	/// @see IsIntersecting to test if the bounding boxes intersect.
	inline void Intersect(const mw2dBoundingBox& other);

	/// Tests whether this and other intersect.
	/// @return true if bounding boxes intersect or false otherwise
	/// @note if one of both bounding box is uninitialized the result be false
	inline bool IsIntersecting(const mw2dBoundingBox& other) const;
	/// Get string representation of bounding box
	///
	///	@returns mwstring containing a string representation of the bounding box
	inline misc::mwstring ToString() const;

	template <class Archive, typename T2>
	friend void serialize(Archive& archive, mw2dBoundingBox<T2>& bbox, unsigned int);

	// Internal interface with mw::Verifier::geom
	operator mw::Verifier::geom::TAlignedBox2<T>&();
	operator const mw::Verifier::geom::TAlignedBox2<T>&() const;

	/// &= Operator
	///
	/// Restricts to intersection with the given bounding box.
	/// If the bounding boxes do not overlap the resulting bounding box is reduced to a single
	/// point.
	MW_DEPRECATED("Deprecated since 2018.04, please use Intersect(const mw2dBoundingBox&).")
	inline void operator&=(const mw2dBoundingBox& other);
	MW_DEPRECATED("Deprecated since 2017.12. Use GetMin()")
	inline const TPoint2d& GetBottomLeftCorner() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetMax()")
	inline const TPoint2d& GetTopRightCorner() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetSizeX()")
	inline T GetWidth() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetSizeY()")
	inline T GetHeight() const;

private:
	TPoint2d m_minCorner;
	TPoint2d m_maxCorner;

	inline void ValidateIfBoxIsInitialized() const;
};  // end of mw2dBoundingBox class

template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mw2dBoundingBox<T>& toDump)
{
	os << _T("class cadcam::mw2dBoundingBox\n");
	// public properties from cadcam::mw2dBoundingBox class.
	os << _T("GetBottomLeftCorner = ") << toDump.GetMin() << _T("\n");
	os << _T("GetTopRightCorner   = ") << toDump.GetMax() << _T("\n");
	os << _T("GetWidth            = ") << toDump.GetSizeX() << _T("\n");
	os << _T("GetHeight           = ") << toDump.GetSizeY() << _T("\n");
	os << _T("GetDiagonalLength   = ") << toDump.GetDiagonalLength() << _T("\n");
	// os << _T("IsEmpty             = ") << toDump.IsEmpty            () << _T("\n");
	os << _T("IsLine              = ") << toDump.IsLine() << _T("\n");
	os << _T("GetMinX             = ") << toDump.GetMinX() << _T("\n");
	os << _T("GetMinY             = ") << toDump.GetMinY() << _T("\n");
	os << _T("GetMaxX             = ") << toDump.GetMaxX() << _T("\n");
	os << _T("GetMaxY             = ") << toDump.GetMaxY() << _T("\n");
	os << _T("IsInitialized       = ") << toDump.IsInitialized() << _T("\n");
	return os;
}

template <class T>
inline void mw2dBoundingBox<T>::ValidateIfBoxIsInitialized() const
{
	if (!IsInitialized())
		throw misc::mwException(0, _T("Uninitialized bounding box used"));
}

template <class T>
misc::mwstring cadcam::mw2dBoundingBox<T>::ToString() const
{
	if (!IsInitialized())
	{
		return _T("Not initialized");
	}
	else
	{
		return _T("BLN: ") + GetMin().ToString() + _T(" URF: ") + GetMax().ToString();
	}
}

template <class T>
inline mw2dBoundingBox<T>& mw2dBoundingBox<T>::Inflate(const T dx, const T dy)
{
	if (!IsInitialized())
	{
		return *this;
	}

	const mwTPoint2d<T> offs(dx, dy);
	m_minCorner -= offs;
	m_maxCorner += offs;
	const mwTPoint2d<T> size = m_maxCorner - m_minCorner;
	if (size.x() < 0 || size.y() < 0)
	{
		Uninitialize();
	}
	return *this;
}

template <class T>
inline void mw2dBoundingBox<T>::Uninitialize()
{
	const T maxValueT = mathdef::mw_maxvalue(T());
	m_maxCorner.x(-maxValueT);
	m_maxCorner.y(-maxValueT);
	m_minCorner.x(maxValueT);
	m_minCorner.y(maxValueT);
}

template <class T>
inline bool mw2dBoundingBox<T>::IsInitialized() const
{
	return !(
		m_maxCorner.x() == -mathdef::mw_maxvalue(T()) &&
		m_maxCorner.y() == -mathdef::mw_maxvalue(T()) &&
		m_minCorner.x() == mathdef::mw_maxvalue(T()) &&
		m_minCorner.y() == mathdef::mw_maxvalue(T()));
}

template <class T>
inline void mw2dBoundingBox<T>::EnlargeForPoint(const mwTPoint2d<T>& point)
{
	if (point.x() < m_minCorner.x())
		m_minCorner.x(point.x());
	if (point.y() < m_minCorner.y())
		m_minCorner.y(point.y());

	if (point.x() > m_maxCorner.x())
		m_maxCorner.x(point.x());
	if (point.y() > m_maxCorner.y())
		m_maxCorner.y(point.y());
}

template <class T>
inline void mw2dBoundingBox<T>::SetMaxY(const T value)
{
	if (value < GetMinY())
		throw misc::mwException(0, _T("Maximum y is less than minimum y!"));
	m_maxCorner.y(value);
}

template <class T>
inline void mw2dBoundingBox<T>::SetMaxX(const T value)
{
	if (value < GetMinX())
		throw misc::mwException(0, _T("Maximum x is less than minimum x!"));
	m_maxCorner.x(value);
}

template <class T>
inline void mw2dBoundingBox<T>::SetMinY(const T value)
{
	if (value > GetMaxY())
		throw misc::mwException(0, _T("Minimum y is more than maximum y!"));
	m_minCorner.y(value);
}

template <class T>
inline void mw2dBoundingBox<T>::SetMinX(const T value)
{
	if (value > GetMaxX())
		throw misc::mwException(0, _T("Minimum x is more than maximum x!"));
	m_minCorner.x(value);
}

template <class T>
inline typename mw2dBoundingBox<T>::TPoint2d mw2dBoundingBox<T>::GetCenter() const
{
	TPoint2d p;
	GetCenter(p);
	return p;
}

template <class T>
inline void mw2dBoundingBox<T>::GetCenter(TPoint2d& p) const
{
	ValidateIfBoxIsInitialized();
	p = (m_maxCorner + m_minCorner) * static_cast<T>(0.5);
}

template <class T>
inline bool mw2dBoundingBox<T>::IsOutside(const mwTPoint2d<T>& ta, T tolerance) const
{
	return (
		mathdef::is_lt(ta.x(), m_minCorner.x(), tolerance) ||
		mathdef::is_lt(ta.y(), m_minCorner.y(), tolerance) ||
		mathdef::is_gt(ta.x(), m_maxCorner.x(), tolerance) ||
		mathdef::is_gt(ta.y(), m_maxCorner.y(), tolerance));
}

template <class T>
inline bool mw2dBoundingBox<T>::Contains(const TPoint2d& p) const
{
	return p == mwTPointUtils<TPoint2d>::GetMaxPoint(p, m_minCorner) &&
		p == mwTPointUtils<TPoint2d>::GetMinPoint(p, m_maxCorner);
}

template <class T>
inline bool mw2dBoundingBox<T>::IsLine() const
{
	return IsInitialized() && (GetSizeX() == 0.0 || GetSizeY() == 0.0);
}

template <class T>
inline bool mw2dBoundingBox<T>::IsSinglePoint() const
{
	return m_maxCorner == m_minCorner;
}

template <class T>
inline void mw2dBoundingBox<T>::Intersect(const mw2dBoundingBox& other)
{
	TPoint2d newMaxCorner = mwTPointUtils<TPoint2d>::GetMinPoint(m_maxCorner, other.m_maxCorner);
	TPoint2d newMinCorner = mwTPointUtils<TPoint2d>::GetMaxPoint(m_minCorner, other.m_minCorner);

	// check if bounding box is valid
	if (mwTPointUtils<TPoint2d>::GetMinPoint(newMaxCorner, newMinCorner) == newMinCorner)
	{
		m_maxCorner = newMaxCorner;
		m_minCorner = newMinCorner;
	}
	else
	{
		Uninitialize();
	}
}

template <class T>
inline bool mw2dBoundingBox<T>::IsIntersecting(const mw2dBoundingBox& other) const
{
	return !(
		m_maxCorner.x() < other.m_minCorner.x() || m_maxCorner.y() < other.m_minCorner.y() ||
		m_minCorner.x() > other.m_maxCorner.x() || m_minCorner.y() > other.m_maxCorner.y());
}

template <class T>
inline void mw2dBoundingBox<T>::operator&=(const mw2dBoundingBox& other)
{
	TPoint2d newMaxCorner = mwTPointUtils<TPoint2d>::GetMinPoint(m_maxCorner, other.m_maxCorner);
	TPoint2d newMinCorner = mwTPointUtils<TPoint2d>::GetMaxPoint(m_minCorner, other.m_minCorner);
	// need to check if intersection is empty
	if (mwTPointUtils<TPoint2d>::GetMinPoint(newMaxCorner, newMinCorner) == newMinCorner)
	{
		m_maxCorner = newMaxCorner;
		m_minCorner = newMinCorner;
	}
	else
	{
		m_maxCorner = m_minCorner;
	}
}

template <class T>
inline mw2dBoundingBox<T>& mw2dBoundingBox<T>::operator+=(const mw2dBoundingBox& boxToAdd)
{
	m_maxCorner = mwTPointUtils<TPoint2d>::GetMaxPoint(m_maxCorner, boxToAdd.m_maxCorner);
	m_minCorner = mwTPointUtils<TPoint2d>::GetMinPoint(m_minCorner, boxToAdd.m_minCorner);
	return *this;
}

template <class T>
inline mw2dBoundingBox<T> mw2dBoundingBox<T>::operator+(const mw2dBoundingBox& boxToAdd) const
{
	mw2dBoundingBox<T> ret = *this;
	ret += boxToAdd;
	return ret;
}

template <class T>
inline typename mw2dBoundingBox<T>::TPoint2d cadcam::mw2dBoundingBox<T>::GetSize() const
{
	ValidateIfBoxIsInitialized();
	return GetMax() - GetMin();
}

/// deprecated functions
template <class T>
inline T mw2dBoundingBox<T>::GetHeight() const
{
	return GetSizeY();
}
template <class T>
inline T mw2dBoundingBox<T>::GetWidth() const
{
	return GetSizeX();
}
template <class T>
inline const typename mw2dBoundingBox<T>::TPoint2d& mw2dBoundingBox<T>::GetTopRightCorner() const
{
	return m_maxCorner;
}
template <class T>
inline const typename mw2dBoundingBox<T>::TPoint2d& mw2dBoundingBox<T>::GetBottomLeftCorner() const
{
	return m_minCorner;
}

template <class T>
inline bool mw2dBoundingBox<T>::operator!=(const mw2dBoundingBox& toCompare) const
{
	return !operator==(toCompare);
}

template <class T>
inline bool mw2dBoundingBox<T>::operator==(const mw2dBoundingBox& toCompare) const
{
	return m_minCorner == toCompare.m_minCorner && m_maxCorner == toCompare.m_maxCorner;
}

template <class T>
inline void mw2dBoundingBox<T>::SetCorners(const TPoint2d& corner1, const TPoint2d& corner2)
{
	m_maxCorner = mwTPointUtils<TPoint2d>::GetMaxPoint(corner1, corner2);
	m_minCorner = mwTPointUtils<TPoint2d>::GetMinPoint(corner1, corner2);
}

template <class T>
inline mw2dBoundingBox<T>::mw2dBoundingBox(const TPoint2d& corner1, const TPoint2d& corner2)
{
	SetCorners(corner1, corner2);
}

template <class T>
inline mw2dBoundingBox<T>::mw2dBoundingBox()
	: m_minCorner(mathdef::mw_maxvalue(T()), mathdef::mw_maxvalue(T())),
	  m_maxCorner(-mathdef::mw_maxvalue(T()), -mathdef::mw_maxvalue(T()))
{
}

// Internal interface with mw::Verifier::geom
template <class T>
inline mw2dBoundingBox<T>::operator mw::Verifier::geom::TAlignedBox2<T>&()
{
	return *static_cast<mw::Verifier::geom::TAlignedBox2<T>*>(static_cast<void*>(this));
}
template <class T>
inline mw2dBoundingBox<T>::operator const mw::Verifier::geom::TAlignedBox2<T>&() const
{
	return *static_cast<const mw::Verifier::geom::TAlignedBox2<T>*>(static_cast<const void*>(this));
}

}  // namespace cadcam

#pragma CACHING_INTERNAL_END
#endif  //	MW_MW2DBOUNDINGBOX_HPP_
