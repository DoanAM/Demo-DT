// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW2DARC_HPP_
#define MW_MW2DARC_HPP_
#include "mw2dGeometry.hpp"
#include "mw2dPoint.hpp"
#include "mwAngleUtils.hpp"
#include "mwClampedValue.hpp"
#include "mwMathConstants.hpp"
#include "mwTrig.hpp"
#include "mwVectorUtils.hpp"

#include <algorithm>


#ifdef _WIN32  // VS14: mw2dArc.hpp(220): warning C4459: declaration of 'center' hides global
			   // declaration
#pragma warning(push)
#pragma warning(disable : 4459)
#endif


namespace cadcam
{
template <class T>
class mw2dArc;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw2dArc<T>& arc, unsigned int);
/// Implements a 2d circular arc
///
/// by holding circle coords and radius, start and sweeping angle
template <class T>
class MW_5AXUTIL_API mw2dArc: public mw2dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw2dArc<Ty>& arc, unsigned int);
	typedef misc::mwClampedValue<T> arcAttrib;

public:
	typedef typename misc::mwAutoPointer<mw2dArc<T>> Ptr;
	// Linux specific
	typedef typename mw2dGeometry<T>::TPoint TPoint;
	typedef typename mw2dGeometry<T>::PointPtr PointPtr;
	typedef typename mw2dGeometry<T>::Point Point;
	typedef typename mw2dGeometry<T>::ValueType ValueType;
	// Linux specific

	inline mw2dArc();

	/// Create based on center, radius, start and sweeping angle
	/// @param center 2D position of arc center
	/// @param radius arc Radius
	/// @param startAngle Start angle in degrees [0, 360]
	/// @param sweepAngle Sweep angle in degrees in range [-360, 360]
	/// 	@remark If negative, then arc gets CW orientation, otherwise CCW
	/// @throws mwException if the parameters are not in valid range
	inline mw2dArc(const TPoint& center, const T radius, const T startAngle, const T sweepAngle);

	/// Create based on center, radius, start and sweeping angle
	///
	/// Additionally accepts start and end points. These should be within tolerance to
	/// those calculated based on start/end angles and center point. Otherwise constructor throws.
	/// @param center 2D position of arc center
	/// @param radius arc Radius
	/// @param startAngle Start angle in degrees [0, 360]
	/// @param sweepAngle Sweep angle in degrees in range [-360, 360]
	/// @remark If negative, then arc gets CW orientation, otherwise CCW
	/// @param startPoint Exact start point of an arc. Should be sync with angle data.
	/// @param endPoint Exact end point of an arc. Should be sync with angle data.
	/// @throws mwException if the parameters are not in valid range
	inline mw2dArc(
		const TPoint& center,
		const T radius,
		const T startAngle,
		const T sweepAngle,
		const TPoint& startPoint,
		const TPoint& endPoint);

	/// Create arc based on center, radius, start and end points
	inline mw2dArc(
		const TPoint& center,
		const TPoint& startPoint,
		const TPoint& endPoint,
		const bool isClockWise);

	/// Set arc data
	inline void SetCenterRadiusAngles(
		const TPoint& center, const T radius, const T startAngle, const T sweepAngle);

	/// Get center of an arc circle
	inline void SetCenter(const TPoint& center);

	/// Get center of an arc circle
	inline const TPoint& GetCenter() const;

	/// Get arc center (point on an arc)
	inline TPoint GetCenterArc() const;

	/// Set arc radius
	///
	/// @throws mwException if negative Radius passed
	inline void SetRadius(const T radius);

	/// Get arc radius
	inline T GetRadius() const;

	/// Set start angle in range [0, 360]
	///
	/// @throws mwException if angle is outside of [0, 360] range
	inline void SetStartAngle(const T startAngle);

	/// Get start angle in range [0, 360]
	inline T GetStartAngle() const;

	/// Set arc sweep angle, can vary in range [-360, 360]
	///
	/// @throws mwException if angle is outside of [-360, 360] range
	inline void SetSweepAngle(const T sweepAngle);

	/// Get arc sweep angle, varies in range [-360, 360]
	///
	/// @throws mwException if angle is outside of [-360, 360] range
	inline T GetSweepAngle() const;

	/// Get arc length
	inline virtual T GetLength() const;

	/// Get arc chord length which is |startPoint - endPoint|
	inline T GetChordLength() const;

	/// Get start point
	///
	/// @returns Start point, calculated based on center and angles
	/// @remark Returns stored start point if it was explicitly set and is in sync with the
	/// calculated position
	inline virtual const TPoint& GetStartPoint() const;

	/// Get end point
	///
	/// @returns End point, calculated based on center and angles
	/// @remarks Returns stored end point if it was explicitly set and is in sync with the
	/// calculated position
	inline virtual TPoint& GetEndPoint() const;

	/// Calculate 2D point on arc based on an angle
	inline const TPoint GetPointOnArc(const T angle) const;

	///	Reverse an arc
	inline virtual void Reverse();

	/// Is an arc continuous?
	///
	/// @returns Always true for an arc
	inline virtual bool IsContinuous(const T) const;
	inline bool operator==(const mw2dArc<T>& src) const;
	inline bool operator!=(const mw2dArc<T>& src) const;
	inline virtual const mw2dBoundingBox<T>& GetBoundingBox() const;
	inline virtual bool IsClockwise() const;

	/// Implements visitor pattern
	inline virtual void AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const;
	/// Implements changing visitor pattern
	inline virtual void AcceptVisitor(mw2dGeometryVisitor<T>& visitor);

private:
	/// CalculateBoundingBox function
	///
	/// Performs the bounding box calculation
	inline void CalculateBoundingBox() const;

	TPoint m_center;
	arcAttrib m_dRadius;
	arcAttrib m_dStartAngle;
	arcAttrib m_dSweepAngle;
	mutable TPoint m_start;
	mutable bool m_startDirty;
	mutable TPoint m_end;
	mutable bool m_endDirty;
	mutable mw2dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
	mutable bool m_isReversed;
};

template <class T>
inline mw2dArc<T>::mw2dArc()
	: m_dRadius(0.0, mathdef::mw_maxvalue(ValueType()), 0),
	  m_dStartAngle(0.0, 360.0, 0),
	  m_dSweepAngle(-360.0, 360.0, 0),
	  m_bBoxDirty(true),
	  m_startDirty(true),
	  m_endDirty(true),
	  m_isReversed(false)
{
}

template <class T>
inline mw2dArc<T>::mw2dArc(
	const TPoint& center, const T radius, const T startAngle, const T sweepAngle)
	: m_dRadius(0.0, mathdef::mw_maxvalue(radius)),
	  m_dStartAngle(0.0, 360.0),
	  m_dSweepAngle(-360.0, 360.0),
	  m_bBoxDirty(true),
	  m_startDirty(true),
	  m_endDirty(true),
	  m_isReversed(false)
{
	SetCenterRadiusAngles(center, radius, startAngle, sweepAngle);
}

template <class T>
inline mw2dArc<T>::mw2dArc(
	const TPoint& center,
	const T radius,
	const T startAngle,
	const T sweepAngle,
	const TPoint& startPoint,
	const TPoint& endPoint)
	: m_dRadius(0.0, mathdef::mw_maxvalue(radius)),
	  m_dStartAngle(0.0, 360.0),
	  m_dSweepAngle(-360.0, 360.0),
	  m_isReversed(false)
{
	SetCenterRadiusAngles(center, radius, startAngle, sweepAngle);
	m_start = GetStartPoint();
	m_end = GetEndPoint();

	const T diameter = radius * 2;
	const T scale = diameter + ~startPoint + ~endPoint + ~center;
	const T tolerance = mathdef::mw_tol(T()) * (1 + scale);
	const T startPointDeviation = ~(m_start - startPoint);
	const T endPointDeviation = ~(m_end - endPoint);
	if (!mathdef::is_zero(startPointDeviation, tolerance) ||
		!mathdef::is_zero(endPointDeviation, tolerance))
		MW_EXCEPTION("Arc end points are in conflict with other data.");

	m_start = startPoint;
	m_startDirty = false;
	m_end = endPoint;
	m_endDirty = false;
}

template <class T>
inline mw2dArc<T>::mw2dArc(
	const TPoint& center, const TPoint& startPoint, const TPoint& endPoint, const bool isClockWise)
	: mw2dGeometry<T>(),
	  m_dRadius(0.0, mathdef::mw_maxvalue(T())),
	  m_dStartAngle(0.0, 360.0),
	  m_dSweepAngle(-360.0, 360.0),
	  m_isReversed(false)
{
	const T startAngle = mwVectorUtils<T>::GetAngleFromXAxisDegree(startPoint - center);
	const T endAngle = mwVectorUtils<T>::GetAngleFromXAxisDegree(endPoint - center);
	T sweepAngle = endAngle - startAngle;
	if (isClockWise != (sweepAngle < 0))
	{
		if (sweepAngle < 0)
		{
			sweepAngle += 360;
		}
		else
		{
			sweepAngle -= 360;
		}
	}
	const T radius = (~(center - startPoint) + ~(center - endPoint)) / 2;

	SetCenterRadiusAngles(center, radius, startAngle, sweepAngle);
	const T diameter = radius * 2;
	const T scale = diameter + ~startPoint + ~endPoint + ~center;
	const T tolerance = mathdef::mw_tol(T()) * (1 + scale);
	const T startPointDeviation = ~(center - startPoint) - radius;
	const T endPointDeviation = ~(center - endPoint) - radius;
	if (mathdef::is_not_zero(startPointDeviation, tolerance) ||
		mathdef::is_not_zero(endPointDeviation, tolerance))
		throw misc::mwException(
			0,
			_T("Provided start/end points to Arc constructor are in different distance from ")
			_T("center."));

	m_start = startPoint;
	m_startDirty = false;
	m_end = endPoint;
	m_endDirty = false;
}

template <class T>
inline void mw2dArc<T>::SetCenterRadiusAngles(
	const TPoint& center, const T radius, const T startAngle, const T sweepAngle)
{
	SetCenter(center);
	SetRadius(radius);
	SetStartAngle(startAngle);
	SetSweepAngle(sweepAngle);
}

template <class T>
inline void mw2dArc<T>::SetCenter(const TPoint& center)
{
	m_center = center;
	m_bBoxDirty = true;
	m_startDirty = true;
	m_endDirty = true;
}

template <class T>
inline const typename mw2dArc<T>::TPoint& mw2dArc<T>::GetCenter() const
{
	return m_center;
}

template <class T>
inline typename mw2dArc<T>::TPoint mw2dArc<T>::GetCenterArc() const
{
	return GetPointOnArc(m_dStartAngle.GetValue() + m_dSweepAngle.GetValue() * static_cast<T>(0.5));
}

template <class T>
inline void mw2dArc<T>::SetRadius(const T Radius)
{
	m_dRadius.SetValue(Radius);
	m_bBoxDirty = true;
	m_startDirty = true;
	m_endDirty = true;
}

template <class T>
inline T mw2dArc<T>::GetRadius() const
{
	return m_dRadius.GetValue();
}

template <class T>
inline void mw2dArc<T>::SetStartAngle(const T startAngle)
{
	if (m_isReversed)
	{
		const T sweepAngle =
			mathdef::Abs(m_dSweepAngle.GetValue()) == 360 ? 0 : m_dSweepAngle.GetValue();
		m_dSweepAngle.SetValue(-sweepAngle);
		m_isReversed = !m_isReversed;
	}
	m_dStartAngle.SetValue(startAngle);
	m_bBoxDirty = true;
	m_startDirty = true;
	m_endDirty = true;
}

template <class T>
inline T mw2dArc<T>::GetStartAngle() const
{
	if (!m_isReversed)
		return m_dStartAngle.GetValue();

	arcAttrib startAngle(m_dStartAngle);
	T angle = m_dStartAngle.GetValue() + m_dSweepAngle.GetValue();
	measures::mwAngleUtils<T>::MapAngleBetween0And360(angle);
	startAngle.SetValue(angle);
	return startAngle.GetValue();
}

template <class T>
inline void mw2dArc<T>::SetSweepAngle(const T sweepAngle)
{
	if (m_isReversed)
	{
		T angle = m_dStartAngle.GetValue() + m_dSweepAngle.GetValue();
		measures::mwAngleUtils<T>::MapAngleBetween0And360(angle);
		m_dStartAngle.SetValue(angle);
		m_isReversed = !m_isReversed;
	}
	m_dSweepAngle.SetValue(sweepAngle);
	m_bBoxDirty = true;
	m_startDirty = true;
	m_endDirty = true;
}

template <class T>
inline T mw2dArc<T>::GetSweepAngle() const
{
	arcAttrib sweepAngle(m_dSweepAngle);
	sweepAngle.SetValue(!m_isReversed ? m_dSweepAngle.GetValue() : -m_dSweepAngle.GetValue());
	return sweepAngle.GetValue();
}

template <class T>
inline T mw2dArc<T>::GetLength() const
{
	return static_cast<T>(mathdef::MW_D2R) * m_dRadius.GetValue() * std::fabs(m_dSweepAngle.GetValue());
}

template <class T>
inline T mw2dArc<T>::GetChordLength() const
{
	const TPoint v1 = GetStartPoint();
	const TPoint v2 = GetEndPoint();
	return ~(v1 - v2);
}

template <class T>
inline const typename mw2dArc<T>::TPoint& mw2dArc<T>::GetStartPoint() const
{
	if (m_startDirty)
	{
		const T sweepAngle = mathdef::Abs(m_dSweepAngle.GetValue()) == 360 || !m_isReversed
			? 0
			: m_dSweepAngle.GetValue();

		m_start = GetPointOnArc(m_dStartAngle.GetValue() + sweepAngle);
		m_startDirty = false;
	}
	return m_start;
}

template <class T>
inline typename mw2dArc<T>::TPoint& mw2dArc<T>::GetEndPoint() const
{
	if (m_endDirty)
	{
		const T sweepAngle = mathdef::Abs(m_dSweepAngle.GetValue()) == 360 || m_isReversed
			? 0
			: m_dSweepAngle.GetValue();

		m_end = GetPointOnArc(m_dStartAngle.GetValue() + sweepAngle);
		m_endDirty = false;
	}
	return m_end;
}

template <class T>
inline const typename mw2dArc<T>::TPoint mw2dArc<T>::GetPointOnArc(const T angle) const
{
	const T dx = m_dRadius.GetValue() * mathdef::CosDegree(angle);
	const T dy = m_dRadius.GetValue() * mathdef::SinDegree(angle);
	return TPoint(m_center.x() + dx, m_center.y() + dy);
}

template <class T>
inline void mw2dArc<T>::Reverse()
{
	m_isReversed = !m_isReversed;
	std::swap(m_start, m_end);
	std::swap(m_startDirty, m_endDirty);
}

template <class T>
inline void mw2dArc<T>::AcceptVisitor(mw2dGeometryConstVisitor<T>& visitor) const
{
	visitor.Visit(*this);
}

template <class T>
inline void mw2dArc<T>::AcceptVisitor(mw2dGeometryVisitor<T>& visitor)
{
	visitor.Visit(*this);
}

template <class T>
inline bool mw2dArc<T>::IsContinuous(const T) const
{
	return true;
}

template <class T>
inline bool mw2dArc<T>::IsClockwise() const
{
	return GetSweepAngle() < 0;
}

template <class T>
inline bool mw2dArc<T>::operator==(const mw2dArc<T>& src) const
{
	return GetStartAngle() == src.GetStartAngle() && GetSweepAngle() == src.GetSweepAngle() &&
		GetRadius() == src.GetRadius() && GetCenter() == src.GetCenter();
}

template <class T>
inline bool mw2dArc<T>::operator!=(const mw2dArc<T>& src) const
{
	return !(*this == src);
}

template <class T>
inline const mw2dBoundingBox<T>& mw2dArc<T>::GetBoundingBox() const
{
	if (m_bBoxDirty)
	{
		CalculateBoundingBox();
	}
	return m_bbox;
}

template <class T>
inline void mw2dArc<T>::CalculateBoundingBox() const
{
	m_bbox.SetCorners(GetStartPoint(), GetEndPoint());

	T minAngle = GetStartAngle();
	T maxAngle = GetStartAngle() + GetSweepAngle();
	if (minAngle > maxAngle)
	{
		std::swap(minAngle, maxAngle);
	}

	const T minAngleVal = m_dStartAngle.GetMinValue() + m_dSweepAngle.GetMinValue();
	const T maxAngleVal = m_dStartAngle.GetMaxValue() + m_dSweepAngle.GetMaxValue();
	for (T angle = minAngleVal; angle <= maxAngleVal; angle += 90)
	{
		if (minAngle < angle && angle < maxAngle)
		{
			m_bbox.EnlargeForPoint(GetPointOnArc(angle));
		}
	}

	m_bBoxDirty = false;
}

template <class T>
inline misc::mwLogger& operator<<(misc::mwLogger& os, const cadcam::mw2dArc<T>& toDump)
{
	os << _T("class cadcam::mw2dArc\n");
	// public properties from cadcam::mw2dArc class.
	os << _T("GetCenter     = ") << toDump.GetCenter() << _T("\n");
	os << _T("GetRadius     = ") << toDump.GetRadius() << _T("\n");
	os << _T("GetStartAngle = ") << toDump.GetStartAngle() << _T("\n");
	os << _T("GetSweepAngle = ") << toDump.GetSweepAngle() << _T("\n");
	return os;
}
}  // namespace cadcam

#ifdef _WIN32
#pragma warning(pop)
#endif
#endif  //	MW_MW2DARC_HPP_
