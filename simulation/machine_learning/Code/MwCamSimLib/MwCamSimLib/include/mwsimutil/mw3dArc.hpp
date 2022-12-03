// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DARC_HPP_
#define MW_MW3DARC_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwException.hpp"
#include "mwTPoint3d.hpp"
#include "mwTrig.hpp"
#include "mwcadcamException.hpp"

#include <algorithm>

namespace cadcam
{
template <class T>
class mw3dArc;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw3dArc<T>& arc, unsigned int);

/// Implements a 3d circular arc
///
/// by holding circle coords and radius, start and sweeping angle
template <class T>
class MW_5AXUTIL_API mw3dArc: public mw3dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw3dArc<Ty>& arc, unsigned int);

public:
	typedef typename misc::mwAutoPointer<mw3dArc<T>> Ptr;
	// Linux specific
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	typedef typename mw3dGeometry<T>::Point Point;
	// Linux specific

	mw3dArc(): m_bBoxDirty(true), m_startDirty(true), m_endDirty(true), m_isReversed(false) {}

	/// Constructor
	///
	/// Init Arc with circle center pos, start and end 3d PointPtrs
	///	@param center a const ref to 3d PointPtr for circle center coordinates
	///	@param startVector a const ref to 3d vector for start coords
	///	@param endVector a const ref to 3d vector for end coords
	///	@param normalVector a const ref to 3d vector for the normal arc.
	/// @param toleranceProvided tolerance to be used for input data validation
	///	The normal vector shows the direction of the arc, because if the arc has not 180*k
	/// degrees, there are two possible arcs. If we look at the arc's plane from the side of the
	/// normal vector, the arc from startVector to endVector is positive (anti-clockwise). 	When the
	/// arc is of 180*k degrees, the normal is the only parameter to indicate also the arc's plane.
	///	@throws mwException in case lengths of the two vectors do not match
	mw3dArc(
		const TPoint& center,
		const TPoint& startVector,
		const TPoint& endVector,
		const TPoint& normalVector,
		const T toleranceProvided = mathdef::mw_tol(T()))
		: m_bBoxDirty(true),
		  m_center(center),
		  m_startVector(startVector),
		  m_endVector(endVector),
		  m_normalVector(normalVector),
		  m_startDirty(true),
		  m_endDirty(true),
		  m_isReversed(false)
	{
		const T scale = GetScale();
		const T tolerance = mathdef::mw_max(mathdef::mw_tol(T()) * (1 + scale), toleranceProvided);

		if (!mathdef::is_eq(~startVector, ~endVector, tolerance))
			throw mwcadcamException(mwcadcamException::INVALID_3D_ARC);
	}

	mw3dArc(
		const TPoint& center,
		const TPoint& startVector,
		const TPoint& endVector,
		const TPoint& normalVector,
		const TPoint& startPoint,
		const TPoint& endPoint,
		const T toleranceProvided = mathdef::mw_tol(T()))
		: m_bBoxDirty(true),
		  m_center(center),
		  m_startVector(startVector),
		  m_endVector(endVector),
		  m_normalVector(normalVector),
		  m_startDirty(true),
		  m_endDirty(true),
		  m_isReversed(false)
	{
		const T scale = GetScale();
		const T tolerance = mathdef::mw_max(mathdef::mw_tol(T()) * (1 + scale), toleranceProvided);

		if (!mathdef::is_eq(~startVector, ~endVector, tolerance))
			throw mwcadcamException(mwcadcamException::INVALID_3D_ARC);

		m_startPoint = GetStartPoint();
		m_endPoint = GetEndPoint();

		const T toleranceSquared = tolerance * tolerance;
		const T startPointDeviationSquared = (m_startPoint - startPoint).Length2();
		const T endPointDeviationSquared = (m_endPoint - endPoint).Length2();
		if (mathdef::is_not_zero(startPointDeviationSquared, toleranceSquared) ||
			mathdef::is_not_zero(endPointDeviationSquared, toleranceSquared))
			throw mwcadcamException(mwcadcamException::INVALID_3D_ARC);

		m_startPoint = startPoint;
		m_startDirty = false;
		m_endPoint = endPoint;
		m_endDirty = false;
	}

	void SetCenter(const TPoint& center)
	{
		m_center = center;
		m_bBoxDirty = true;
		m_startDirty = true;
		m_endDirty = true;
	}

	const TPoint& GetCenter() const { return m_center; }

	void SetNormalVector(const TPoint& src)
	{
		m_normalVector = src;
		m_bBoxDirty = true;
		m_startDirty = true;
		m_endDirty = true;
	}

	const TPoint GetNormalVector() const
	{
		return m_normalVector * (m_isReversed ? static_cast<T>(-1.0) : static_cast<T>(1.0));
	}

	const TPoint& GetStartVector() const { return !m_isReversed ? m_startVector : m_endVector; }

	const TPoint& GetEndVector() const { return !m_isReversed ? m_endVector : m_startVector; }

	/// Get the center of the arc curve
	TPoint GetCenterArc() const
	{
		const TPoint ortoPoint = GetNormalVector() % GetStartVector();
		const T alpha = GetSweepAngle() / 2;
		return m_center + GetStartVector() * mathdef::Cos(static_cast<T>(alpha * mathdef::MW_D2R)) +
			ortoPoint * mathdef::Sin(static_cast<T>(alpha * mathdef::MW_D2R));
	}

	T GetRadius() const { return ~GetStartVector(); }

	T GetSweepAngle() const
	{
		const TPoint a = GetStartVector();
		const TPoint b = GetEndVector();
		const TPoint axb = a % b;
		const T ab = a * b;
		const T res = ab == 0 ? 90 : atan2(~axb, ab) * static_cast<T>(mathdef::MW_R2D);
		if (GetNormalVector() * axb < 0)
			return 360 - res;
		return res;
	}

	/// Get arc's length
	virtual T GetLength() const
	{
		return GetSweepAngle() * GetRadius() * static_cast<T>(mathdef::MW_D2R);
	}

	virtual const TPoint& GetStartPoint() const
	{
		if (m_startDirty)
		{
			m_startPoint = m_center + GetStartVector();
			m_startDirty = false;
		}
		return m_startPoint;
	}

	virtual const TPoint& GetEndPoint() const
	{
		if (m_endDirty)
		{
			m_endPoint = m_center + GetEndVector();
			m_endDirty = false;
		}
		return m_endPoint;
	}
	/// @name Visitor pattern
	/// @{
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }
	/// @}

	/// Returns true for arc
	virtual bool IsContinuous(const T) const { return true; }

	bool operator==(const mw3dArc<T>& src) const
	{
		return GetStartPoint() == src.GetStartPoint() && GetEndPoint() == src.GetEndPoint() &&
			GetStartVector() == src.GetStartVector() && GetEndVector() == src.GetEndVector() &&
			GetSweepAngle() == src.GetSweepAngle() && GetRadius() == src.GetRadius() &&
			GetCenter() == src.GetCenter();
	}

	bool operator!=(const mw3dArc<T>& src) const { return !(*this == src); }

	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		if (m_bBoxDirty)
		{
			T minX = mathdef::mw_min(m_startVector.x(), m_endVector.x());
			T maxX = mathdef::mw_max(m_startVector.x(), m_endVector.x());
			T minY = mathdef::mw_min(m_startVector.y(), m_endVector.y());
			T maxY = mathdef::mw_max(m_startVector.y(), m_endVector.y());
			T minZ = mathdef::mw_min(m_startVector.z(), m_endVector.z());
			T maxZ = mathdef::mw_max(m_startVector.z(), m_endVector.z());

			const TPoint ortoPoint(GetNormalVector().Normalized() % (m_startVector));
			const T alpha = GetSweepAngle() * static_cast<T>(mathdef::MW_D2R);

			CalculateCoordinateLimits(alpha, ortoPoint.x(), m_startVector.x(), minX, maxX);
			CalculateCoordinateLimits(alpha, ortoPoint.y(), m_startVector.y(), minY, maxY);
			CalculateCoordinateLimits(alpha, ortoPoint.z(), m_startVector.z(), minZ, maxZ);

			m_bbox = mw3dBoundingBox<T>(
				mwTPoint3d<T>(minX, minY, minZ) + GetCenter(),
				mwTPoint3d<T>(maxX, maxY, maxZ) + GetCenter());
			m_bBoxDirty = false;
		}
		return m_bbox;
	}

	virtual void Reverse()
	{
		m_isReversed = !m_isReversed;
		std::swap(m_startPoint, m_endPoint);
		std::swap(m_startDirty, m_endDirty);
	}

	/// @deprecated This constructor is deprecated.
	mw3dArc(PointPtr center, PointPtr startVector, PointPtr endVector, PointPtr normalVector)
		: m_bBoxDirty(true),
		  m_center(center->getTPoint()),
		  m_startVector(startVector->getTPoint()),
		  m_endVector(endVector->getTPoint()),
		  m_normalVector(normalVector->getTPoint()),
		  m_isReversed(false),
		  m_startDirty(true),
		  m_endDirty(true)
	{
		if (!mathdef::ExclusiveKnuthCompare(~(*startVector), ~(*endVector)))
			throw misc::mwException(
				0, _T("startVector length should equal endVector length (radius)"));
	}

	virtual ~mw3dArc() {}

private:
	TPoint m_center;
	TPoint m_startVector;
	TPoint m_endVector;
	TPoint m_normalVector;
	mutable mw3dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;
	mutable TPoint m_startPoint;
	mutable bool m_startDirty;
	mutable TPoint m_endPoint;
	mutable bool m_endDirty;
	mutable bool m_isReversed;

	void CalculateCoordinateLimits(
		const T alpha,
		const T ortoPointCoordinate,
		const T startVectorCoordinate,
		T& minCoord,
		T& maxCoord) const
	{
		T extrAngle = atan2(ortoPointCoordinate, startVectorCoordinate);
		if (extrAngle < 0)
		{
			extrAngle += static_cast<T>(mathdef::MW_PI);
		}
		T extreme = startVectorCoordinate * static_cast<T>(mathdef::Cos(1. * extrAngle)) +
			ortoPointCoordinate * static_cast<T>(mathdef::Sin(1. * extrAngle));
		if (extrAngle <= alpha)
		{
			minCoord = mathdef::mw_min(minCoord, extreme);
			maxCoord = mathdef::mw_max(maxCoord, extreme);
		}

		if (extrAngle >= static_cast<T>(mathdef::MW_PI))
		{
			extrAngle -= static_cast<T>(mathdef::MW_PI);
		}
		else
		{
			extrAngle += static_cast<T>(mathdef::MW_PI);
		}

		if (extrAngle <= alpha)
		{
			extreme = -extreme;
			minCoord = mathdef::mw_min(minCoord, extreme);
			maxCoord = mathdef::mw_max(maxCoord, extreme);
		}
	}

	const T GetScale() const
	{
		return mathdef::mw_max(
				   mathdef::Abs(GetCenter().x()),
				   mathdef::Abs(GetCenter().y()),
				   mathdef::Abs(GetCenter().z())) +
			GetRadius();
	}
};
}  // namespace cadcam
#endif  //	MW_MW3DARC_HPP_
