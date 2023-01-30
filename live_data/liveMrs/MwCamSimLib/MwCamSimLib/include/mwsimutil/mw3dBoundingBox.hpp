// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DBOUNDINGBOX_HPP_
#define MW_MW3DBOUNDINGBOX_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwMathConstants.hpp"
#include "mwMatrix.hpp"
#include "mwString.hpp"
#include "mwTPoint3d.hpp"
#include "mwTPointUtils.hpp"


namespace mw
{
namespace Verifier
{
namespace geom
{
template <typename Real>
struct TAlignedBox3;
}
}  // namespace Verifier
}  // namespace mw

namespace cadcam
{
template <class T>
class mw3dBoundingBox;
template <class Archive, class T>
void serialize(Archive& ar, ::cadcam::mw3dBoundingBox<T>& t, const unsigned int file_version);

#pragma CACHING_INTERNAL_BEGIN
/// @class mw3dBoundingBox
/// Implements 3D axis-aligned bounding box
template <class T>
class MW_5AXUTIL_API mw3dBoundingBox
{
public:
	typedef T ValueType;
	typedef mwTPoint3d<T> TPoint3d;
	MW_DEPRECATED("Deprecated since 2018.12. Please, do not use it.")
	typedef mwTPoint3d<T> bboxCorner;
	typedef misc::mwAutoPointer<mw3dBoundingBox<T>> Ptr;

	/// Constructor
	///
	///	Constructs an uninitialized bounding box
	///	@see IsInitialized
	inline mw3dBoundingBox();
	/// Set Bounding Box Corners
	///
	/// @param corner1 - first corner
	/// @param corner2 - second corner
	inline void SetCorners(const mwTPoint3d<T>& corner1, const mwTPoint3d<T>& corner2);
	/// Constructor
	///
	///	This constructor takes two corners as parameters
	///	@param corner1 - first corner
	///	@param corner2 - second corner
	/// @param checkCorners - true to order corners
	inline mw3dBoundingBox(
		const mwTPoint3d<T>& corner1, const mwTPoint3d<T>& corner2, bool checkCorners = true);
	/// Constructor
	///
	///	Constructs a bounding box around a center point
	///	@param bboxCenter Center of the bounding box
	///	@param cubeSize Edge length of the bounding box
	inline mw3dBoundingBox(const mwTPoint3d<T>& bboxCenter, const T& cubeSize);

	/// Equality operator
	inline bool operator==(const mw3dBoundingBox& toCompare) const;
	/// Inequality operator
	inline bool operator!=(const mw3dBoundingBox& toCompare) const;

	/// Returns the minimum x.
	///
	/// @see GetMin()
	inline T GetMinX() const { return GetMin().x(); }
	/// Returns the minimum y.
	///
	/// @see GetMin()
	inline T GetMinY() const { return GetMin().y(); }
	/// Returns the minimum z.
	///
	/// @see GetMin()
	inline T GetMinZ() const { return GetMin().z(); }

	/// Returns the minimum corner
	///
	/// @return the minimum corner of the bounding box
	/// @note The minimum corner of an uninitialized bounding box is TPoint3d(max_value, max_value,
	/// max_value)
	///		However it is recommended to check if a bounding box is initialized before calling
	///GetMin
	inline const TPoint3d& GetMin() const { return m_minCorner; }

	/// Returns the maximum x.
	///
	/// @see GetMax()
	inline T GetMaxX() const { return GetMax().x(); }
	/// Returns the maximum y.
	///
	/// @see GetMax()
	inline T GetMaxY() const { return GetMax().y(); }
	/// Returns the maximum z.
	///
	/// @see GetMax()
	inline T GetMaxZ() const { return GetMax().z(); }

	/// Returns the maximum corner
	///
	/// @return the maximum corner of the bounding box
	/// @note The maximum corner of an uninitialized bounding box is TPoint3d(-max_value,
	/// -max_value, -max_value)
	///	However it is recommended to check if a bounding box is initialized before calling GetMax
	inline const TPoint3d& GetMax() const { return m_maxCorner; }

	/// Returns the x component of the size.
	///
	/// @see GetSize()
	inline T GetSizeX() const { return GetSize().x(); }
	/// Returns the y component of the size.
	///
	/// @see GetSize()
	inline T GetSizeY() const { return GetSize().y(); }
	/// Returns the z component of the size.
	///
	/// @see GetSize()
	inline T GetSizeZ() const { return GetSize().z(); }

	/// Returns the size of the bounding box
	///
	/// The size of the bounding box is equivalent to its diagonal
	/// @returns the size the bounding box
	/// @throw misc::mwException if the bounding box is uninitialized
	inline TPoint3d GetSize() const;

	/// GetVolume
	///
	/// @returns the volume of the bounding box
	/// @throw misc::mwException if the bounding box is uninitialized
	inline T GetVolume() const;

	/// GetSurfaceArea
	///
	/// @returns the area of the bounding box surface
	/// @throw misc::mwException if the bounding box is uninitialized
	inline T GetSurfaceArea() const;

	/// GetDiagonalLength
	///
	/// @returns the length of the main diagonal of the bounding box
	/// @throw misc::mwException if the bounding box is uninitialized
	inline T GetDiagonalLength() const { return ~GetSize(); }

	/// += Operator
	///
	///	Makes the union of the two bounding boxes
	inline mw3dBoundingBox& operator+=(const mw3dBoundingBox& boxToAdd);

	/// + Operator
	///
	/// @returns the union of the two bounding boxes
	inline mw3dBoundingBox operator+(const mw3dBoundingBox& boxToAdd) const;

	/// IsSinglePoint
	///
	/// @returns true if the corners are pointing to the same point, otherwise false (even if the
	/// bounding box is uninitialized)
	inline bool IsSinglePoint() const;
	/// IsPlane
	///
	/// @returns true if one or more of the dimensions is 0.0, otherwise false (even if the bounding
	/// box is uninitialized)
	/// @note The function return true if IsSinglePoint() == true
	inline bool IsPlane() const;
	/// GetCenter
	///
	///	@returns the center of the bounding box
	///	@throws misc::mwException if the bounding box is uninitialized
	inline mwTPoint3d<T> GetCenter() const;
	/// Transform
	///
	///	@note If the bounding box is uninitialized it will not be altered and remains uninitialized.
	///	@param m const ref to a transformation matrix
	inline void Transform(const mwMatrix<T, 4, 4>& m);
	/// Enlarge bbox so that bbox contains specified point.
	///
	/// The point is added to the bounding box, such that the point is contained by the bounding box
	/// afterwards
	/// @note An uninitialized bounding box is initialized by this call.
	inline void EnlargeForPoint(const mwTPoint3d<T>& point);
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
	///	@returns true if point is in bounding box or on the border
	inline bool Contains(const TPoint3d& p) const;

	/// Inflate bounding box
	///
	/// If one or more of the delta values are negative and would cause one or more sides of the
	/// bounding box to become negative an uninitialized bounding box is returned.
	/// @note If the bounding box is uninitialized it will not be altered and remains uninitialized.
	/// @param dx delta to add to both edges in x direction
	/// @param dy delta to add to both edges in y direction
	/// @param dz delta to add to both edges in z direction
	inline mw3dBoundingBox<T>& Inflate(const T dx, const T dy, const T dz);
	/// Inflate bounding box
	///
	/// Inflates the bounding box uniformly
	/// @see Inflate(T,T,T)
	inline mw3dBoundingBox<T>& Inflate(const T d) { return Inflate(d, d, d); }

	/// Restricts this bounding box to the Intersection of this and other.		/// If the bounding
	/// boxes do not intersect, the bounding box will be uninitialized.
	/// @see IsIntersecting to test if the bounding boxes intersect.
	inline void Intersect(const mw3dBoundingBox& other);

	/// Tests whether this bounding box intersects with other.
	/// @return true if bounding boxes intersect or false otherwise
	/// @note if one of both bounding box is uninitialized the result be false
	inline bool IsIntersecting(const mw3dBoundingBox& other) const;
	/// Get string representation of bounding box
	///
	///	@returns mwstring containing a string representation of the bounding box
	inline misc::mwstring ToString() const;

	class Iterator
	{
	public:
		inline Iterator(const mw3dBoundingBox<T>* bb, int idx);
		inline Iterator();

		inline Iterator& operator++();
		inline bool operator!=(const Iterator& i) const;
		inline TPoint3d operator*() const;

	private:
		const mw3dBoundingBox<T>* m_bb;
		int m_idx;
	};  // end of class Iterator
	inline Iterator Begin() const;
	inline Iterator End() const;

	template <class Archive, class TI>
	friend void serialize(Archive& ar, mw3dBoundingBox<TI>& t, const unsigned int file_version);

	// Internal interface with mw::Verifier::geom
	operator mw::Verifier::geom::TAlignedBox3<T>&();
	operator const mw::Verifier::geom::TAlignedBox3<T>&() const;


	/// &= Operator
	///
	/// Restricts to intersection with the given bounding box.
	/// If the bounding boxes do not overlap the resulting bounding box is reduced to a single
	/// point, setting its volume to zero.
	MW_DEPRECATED("Deprecated since 2018.04, please use Intersect(const mw3dBoundingBox&).")
	inline void operator&=(const mw3dBoundingBox& other);
	MW_DEPRECATED("Deprecated since 2018.04, please use IsIntersecting(const mw3dBoundingBox&).")
	inline bool IsOverlap(const mw3dBoundingBox& ta) const { return IsIntersecting(ta); }
	MW_DEPRECATED("Deprecated since 2017.12. Use GetMin()")
	inline const TPoint3d& GetBottomLeftNearCorner() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetMax()")
	inline const TPoint3d& GetUpperRightFarCorner() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetSizeX()")
	inline T GetWidth() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetSizeY()")
	inline T GetHeight() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetSizeZ()")
	inline T GetDepth() const;

private:
	TPoint3d m_minCorner;
	TPoint3d m_maxCorner;

	inline void ValidateIfBoxIsInitialized() const;
};  // end of mw3dBoundingBox class

template <class T>
cadcam::mw3dBoundingBox<T>::mw3dBoundingBox(const mwTPoint3d<T>& bboxCenter, const T& cubeSize)
	: m_minCorner(bboxCenter), m_maxCorner(bboxCenter)
{
	Inflate(cubeSize * static_cast<T>(0.5));
}

template <class T>
misc::mwstring cadcam::mw3dBoundingBox<T>::ToString() const
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
inline void mw3dBoundingBox<T>::ValidateIfBoxIsInitialized() const
{
	if (!IsInitialized())
		throw misc::mwException(0, _T("Uninitialized bounding box used"));
}

template <class T>
inline typename mw3dBoundingBox<T>::Iterator mw3dBoundingBox<T>::End() const
{
	return Iterator(this, 8);
}

template <class T>
inline typename mw3dBoundingBox<T>::Iterator mw3dBoundingBox<T>::Begin() const
{
	return Iterator(this, 0);
}

template <class T>
inline mw3dBoundingBox<T>& mw3dBoundingBox<T>::Inflate(const T dx, const T dy, const T dz)
{
	if (!IsInitialized())
	{
		return *this;
	}

	const mwTPoint3d<T> offs(dx, dy, dz);
	m_minCorner -= offs;
	m_maxCorner += offs;
	const mwTPoint3d<T> size = m_maxCorner - m_minCorner;
	if (size.x() < 0 || size.y() < 0 || size.z() < 0)
	{
		Uninitialize();
	}
	return *this;
}

template <class T>
inline bool mw3dBoundingBox<T>::Contains(const TPoint3d& p) const
{
	return p == mwTPointUtils<TPoint3d>::GetMaxPoint(p, m_minCorner) &&
		p == mwTPointUtils<TPoint3d>::GetMinPoint(p, m_maxCorner);
}

template <class T>
inline void mw3dBoundingBox<T>::Uninitialize()
{
	m_maxCorner = TPoint3d(
		-mathdef::mw_maxvalue(T()), -mathdef::mw_maxvalue(T()), -mathdef::mw_maxvalue(T()));

	m_minCorner =
		TPoint3d(mathdef::mw_maxvalue(T()), mathdef::mw_maxvalue(T()), mathdef::mw_maxvalue(T()));
}
//-----------------------------------------------------------------
template <class T>
inline bool mw3dBoundingBox<T>::IsInitialized() const
{
	return !(
		m_maxCorner.x() == -mathdef::mw_maxvalue(T()) &&
		m_maxCorner.y() == -mathdef::mw_maxvalue(T()) &&
		m_maxCorner.z() == -mathdef::mw_maxvalue(T()) &&
		m_minCorner.x() == mathdef::mw_maxvalue(T()) &&
		m_minCorner.y() == mathdef::mw_maxvalue(T()) &&
		m_minCorner.z() == mathdef::mw_maxvalue(T()));
}

template <class T>
inline void mw3dBoundingBox<T>::EnlargeForPoint(const mwTPoint3d<T>& point)
{
	m_minCorner = mwTPointUtils<TPoint3d>::GetMinPoint(m_minCorner, point);
	m_maxCorner = mwTPointUtils<TPoint3d>::GetMaxPoint(m_maxCorner, point);
}

template <class T>
inline void mw3dBoundingBox<T>::Transform(const mwMatrix<T, 4, 4>& m)
{
	if (!IsInitialized())
	{
		return;
	}

	TPoint3d c[8];
	c[0] = m_minCorner;
	c[1] = m_maxCorner;
	c[2] = TPoint3d(m_minCorner.x(), m_minCorner.y(), m_maxCorner.z());
	c[3] = TPoint3d(m_minCorner.x(), m_maxCorner.y(), m_maxCorner.z());
	c[4] = TPoint3d(m_maxCorner.x(), m_minCorner.y(), m_maxCorner.z());
	c[5] = TPoint3d(m_minCorner.x(), m_maxCorner.y(), m_minCorner.z());
	c[6] = TPoint3d(m_maxCorner.x(), m_minCorner.y(), m_minCorner.z());
	c[7] = TPoint3d(m_maxCorner.x(), m_maxCorner.y(), m_minCorner.z());
	for (int i = 0; i < 8; ++i)
	{
		c[i].Transform(m);
	}
	SetCorners(c[0], c[1]);
	for (int j = 2; j < 8; ++j)
	{
		EnlargeForPoint(c[j]);
	}
}

template <class T>
inline mwTPoint3d<T> mw3dBoundingBox<T>::GetCenter() const
{
	ValidateIfBoxIsInitialized();
	return (m_minCorner + m_maxCorner) * static_cast<T>(0.5);
}

template <class T>
inline bool mw3dBoundingBox<T>::IsPlane() const
{
	return IsInitialized() && (GetSizeX() == 0.0 || GetSizeY() == 0.0 || GetSizeZ() == 0.0);
}

template <class T>
inline bool mw3dBoundingBox<T>::IsSinglePoint() const
{
	return m_minCorner == m_maxCorner;
}

template <class T>
inline void mw3dBoundingBox<T>::Intersect(const mw3dBoundingBox& other)
{
	TPoint3d newMaxCorner = mwTPointUtils<TPoint3d>::GetMinPoint(m_maxCorner, other.m_maxCorner);
	TPoint3d newMinCorner = mwTPointUtils<TPoint3d>::GetMaxPoint(m_minCorner, other.m_minCorner);

	// need to check if intersection is empty
	if (mwTPointUtils<TPoint3d>::GetMinPoint(newMaxCorner, newMinCorner) == newMinCorner)
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
inline bool mw3dBoundingBox<T>::IsIntersecting(const mw3dBoundingBox& other) const
{
	return !(
		m_maxCorner.x() < other.m_minCorner.x() || m_maxCorner.y() < other.m_minCorner.y() ||
		m_maxCorner.z() < other.m_minCorner.z() || m_minCorner.x() > other.m_maxCorner.x() ||
		m_minCorner.y() > other.m_maxCorner.y() || m_minCorner.z() > other.m_maxCorner.z());
}

template <class T>
inline void mw3dBoundingBox<T>::operator&=(const mw3dBoundingBox& other)
{
	TPoint3d newMaxCorner = mwTPointUtils<TPoint3d>::GetMinPoint(m_maxCorner, other.m_maxCorner);
	TPoint3d newMinCorner = mwTPointUtils<TPoint3d>::GetMaxPoint(m_minCorner, other.m_minCorner);
	// need to check if intersection is empty
	if (mwTPointUtils<TPoint3d>::GetMinPoint(newMaxCorner, newMinCorner) == newMinCorner)
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
inline mw3dBoundingBox<T>& mw3dBoundingBox<T>::operator+=(const mw3dBoundingBox& boxToAdd)
{
	m_maxCorner = mwTPointUtils<TPoint3d>::GetMaxPoint(m_maxCorner, boxToAdd.m_maxCorner);
	m_minCorner = mwTPointUtils<TPoint3d>::GetMinPoint(m_minCorner, boxToAdd.m_minCorner);
	return *this;
}

template <class T>
inline mw3dBoundingBox<T> mw3dBoundingBox<T>::operator+(const mw3dBoundingBox& boxToAdd) const
{
	mw3dBoundingBox<T> ret = *this;
	ret += boxToAdd;
	return ret;
}

template <class T>
inline T mw3dBoundingBox<T>::GetSurfaceArea() const
{
	const TPoint3d& size = GetSize();
	return 2 * (size.x() * size.y() + size.y() * size.z() + size.x() * size.z());
}

template <class T>
inline T mw3dBoundingBox<T>::GetVolume() const
{
	const TPoint3d& size = GetSize();
	return size.x() * size.y() * size.z();
}

template <class T>
inline typename mw3dBoundingBox<T>::TPoint3d cadcam::mw3dBoundingBox<T>::GetSize() const
{
	ValidateIfBoxIsInitialized();
	return GetMax() - GetMin();
}

// deprecated functions:
template <class T>
inline const typename mw3dBoundingBox<T>::TPoint3d& mw3dBoundingBox<T>::GetUpperRightFarCorner()
	const
{
	return m_maxCorner;
}
template <class T>
inline const typename mw3dBoundingBox<T>::TPoint3d& mw3dBoundingBox<T>::GetBottomLeftNearCorner()
	const
{
	return m_minCorner;
}
template <class T>
inline T mw3dBoundingBox<T>::GetDepth() const
{
	return GetSizeZ();
}
template <class T>
inline T mw3dBoundingBox<T>::GetHeight() const
{
	return GetSizeY();
}
template <class T>
inline T mw3dBoundingBox<T>::GetWidth() const
{
	return GetSizeX();
}

template <class T>
inline bool mw3dBoundingBox<T>::operator!=(const mw3dBoundingBox& toCompare) const
{
	return !(*this == toCompare);
}

template <class T>
inline bool mw3dBoundingBox<T>::operator==(const mw3dBoundingBox& toCompare) const
{
	return m_minCorner == toCompare.m_minCorner && m_maxCorner == toCompare.m_maxCorner;
}

template <class T>
inline mw3dBoundingBox<T>::mw3dBoundingBox(
	const mwTPoint3d<T>& corner1, const mwTPoint3d<T>& corner2, bool checkCorners)
{
	if (checkCorners)
	{
		SetCorners(corner1, corner2);
	}
	else
	{
		m_minCorner = corner1;
		m_maxCorner = corner2;
	}
}

template <class T>
inline void mw3dBoundingBox<T>::SetCorners(
	const mwTPoint3d<T>& corner1, const mwTPoint3d<T>& corner2)
{
	m_maxCorner = mwTPointUtils<TPoint3d>::GetMaxPoint(corner1, corner2);
	m_minCorner = mwTPointUtils<TPoint3d>::GetMinPoint(corner1, corner2);
}

template <class T>
inline mw3dBoundingBox<T>::mw3dBoundingBox()
	: m_minCorner(mathdef::mw_maxvalue(T()), mathdef::mw_maxvalue(T()), mathdef::mw_maxvalue(T())),
	  m_maxCorner(
		  -mathdef::mw_maxvalue(T()), -mathdef::mw_maxvalue(T()), -mathdef::mw_maxvalue(T()))
{
}
//------------------------------------------------------------------------------
template <class T>
inline typename mw3dBoundingBox<T>::TPoint3d mw3dBoundingBox<T>::Iterator::operator*() const
{
	if (m_bb == NULL)
		throw misc::mwException(0, _T("Uninitialized iterator of bounding box"));
	const TPoint3d& c1 = m_bb->m_maxCorner;
	const TPoint3d& c2 = m_bb->m_minCorner;
	return TPoint3d(
		(m_idx & 1) ? c1.x() : c2.x(),
		(m_idx & 2) ? c1.y() : c2.y(),
		(m_idx & 4) ? c1.z() : c2.z());
}
//------------------------------------------------------------------------------
template <class T>
inline bool mw3dBoundingBox<T>::Iterator::operator!=(const Iterator& i) const
{
	return m_idx != i.m_idx;
}
//------------------------------------------------------------------------------
template <class T>
inline typename mw3dBoundingBox<T>::Iterator& mw3dBoundingBox<T>::Iterator::operator++()
{
	++m_idx;
	return *this;
}
//------------------------------------------------------------------------------
template <class T>
inline mw3dBoundingBox<T>::Iterator::Iterator(): m_bb(NULL), m_idx(0)
{
}
//------------------------------------------------------------------------------
template <class T>
inline mw3dBoundingBox<T>::Iterator::Iterator(const mw3dBoundingBox<T>* bb, int idx)
	: m_bb(bb), m_idx(idx)
{
}
//------------------------------------------------------------------------------
template <class T>
inline mw3dBoundingBox<T>::operator mw::Verifier::geom::TAlignedBox3<T>&()
{
	return *static_cast<mw::Verifier::geom::TAlignedBox3<T>*>(static_cast<void*>(this));
}
template <class T>
inline mw3dBoundingBox<T>::operator const mw::Verifier::geom::TAlignedBox3<T>&() const
{
	return *static_cast<const mw::Verifier::geom::TAlignedBox3<T>*>(static_cast<const void*>(this));
}
template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const mw3dBoundingBox<T>& toDump)
{
	os << _T("class cadcam::mw3dBoundingBox\n");
	// public properties from cadcam::mw3dBoundingBox class.
	os << _T("GetBottomLeftNearCorner = ") << toDump.GetMin() << _T("\n");
	os << _T("GetUpperRightFarCorner  = ") << toDump.GetMax() << _T("\n");
	os << _T("GetWidth                = ") << toDump.GetSizeX() << _T("\n");
	os << _T("GetHeight               = ") << toDump.GetSizeY() << _T("\n");
	os << _T("GetDepth                = ") << toDump.GetSizeZ() << _T("\n");
	os << _T("GetVolume               = ") << toDump.GetVolume() << _T("\n");
	os << _T("GetDiagonalLength       = ") << toDump.GetDiagonalLength() << _T("\n");
	os << _T("IsSinglePoint           = ") << toDump.IsSinglePoint() << _T("\n");
	os << _T("IsPlane                 = ") << toDump.IsPlane() << _T("\n");
	os << _T("IsInitialized           = ") << toDump.IsInitialized() << _T("\n");
	return os;
}
#pragma CACHING_INTERNAL_END
}  // namespace cadcam
#endif  //	MW_MW3DBOUNDINGBOX_HPP_
