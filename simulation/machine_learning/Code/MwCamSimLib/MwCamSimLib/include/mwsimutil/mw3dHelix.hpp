// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DHELIX_HPP_
#define MW_MW3DHELIX_HPP_
#include "mw3dBoundingBox.hpp"
#include "mw3dGeometry.hpp"
#include "mwException.hpp"
#include "mwTrig.hpp"

namespace cadcam
{
template <class T>
class mw3dHelix;

template <class Archive, class T>
void serialize(Archive& ar, cadcam::mw3dHelix<T>& helix, unsigned int);

/// Implements a 3d circular helix
///
/// by holding circle center, start point, sweeping angle, height and radius change
template <class T>
class MW_5AXUTIL_API mw3dHelix: public mw3dGeometry<T>
{
	template <class Archive, class Ty>
	friend void serialize(Archive& ar, cadcam::mw3dHelix<Ty>& helix, unsigned int);

public:
	typedef typename misc::mwAutoPointer<mw3dHelix<T>> Ptr;
	// Linux specific
	typedef typename mw3dGeometry<T>::TPoint TPoint;
	typedef typename mw3dGeometry<T>::PointPtr PointPtr;
	typedef typename mw3dGeometry<T>::Point Point;
	// Linux specific

	/// Constructor
	mw3dHelix(): m_bboxDirty(true), m_startPointDirty(true), m_endPointDirty(true) {}

	/// Constructor
	///
	/// Init helix with circle center, start point, normal, sweeping angle, height and radius change
	///	@param center a const ref to mwTPoint3d for circle center coordinates
	///	@param startVector a const ref to mwTPoint3d for start coords
	///	@param normalVector a const ref to mwTPoint3d for the helix normal
	///	@param sweepAngleDeg a const ref to the helix sweep angle in degrees,
	///		@remark represents full angle of helix
	///		@remark if negative, then helix gets CW orientation, otherwise CCW (along normal)
	///	@param height a const ref to the helix full height
	///	@param radiusChange helix radius change
	/// @param toleranceProvided tolerance to validate input parameters with
	mw3dHelix(
		const TPoint& center,
		const TPoint& startVector,
		const TPoint& normalVector,
		const T& sweepAngleDeg,
		const T& height,
		const T& radiusChange = 0,
		const T toleranceProvided = mathdef::mw_tol(T()))
		: m_bboxDirty(true),
		  m_center(center),
		  m_startVector(startVector),
		  m_normalVector(normalVector),
		  m_sweepAngle(sweepAngleDeg),
		  m_height(height),
		  m_radiusChange(radiusChange),
		  m_startPointDirty(true),
		  m_endPointDirty(true)
	{
		ValidateVectors(toleranceProvided);
	}

	/// Performs a deep copy of mw3dHelix object
	///	@param toCopy object to make copy of
	mw3dHelix(const mw3dHelix<T>& toCopy)
		: m_center(toCopy.m_center),
		  m_startVector(toCopy.m_startVector),
		  m_normalVector(toCopy.m_normalVector),
		  m_sweepAngle(toCopy.m_sweepAngle),
		  m_height(toCopy.m_height),
		  m_radiusChange(toCopy.m_radiusChange),
		  m_bbox(toCopy.m_bbox),
		  m_bboxDirty(toCopy.m_bboxDirty),
		  m_startPoint(toCopy.m_startPoint),
		  m_startPointDirty(toCopy.m_startPointDirty),
		  m_endPoint(toCopy.m_endPoint),
		  m_endPointDirty(toCopy.m_endPointDirty)
	{
	}

	/// Set helix base center position
	///	@param center base center point
	void SetCenter(const TPoint& center)
	{
		m_center = center;

		m_bboxDirty = true;
		m_startPointDirty = true;
		m_endPointDirty = true;
	}

	/// Get helix' base center position
	const TPoint& GetCenter() const { return m_center; }

	/// Set helix normal vector (base axis direction)
	///	@param normalVector const ref to mwTPoint3d
	/// @param toleranceProvided tolerance to validate input parameters with
	///	@throws mwException if normal and start vectors not orthogonal
	void SetNormalVector(
		const TPoint& normalVector, const T toleranceProvided = mathdef::mw_tol(T()))
	{
		m_normalVector = normalVector;
		ValidateVectors(toleranceProvided);

		m_bboxDirty = true;
		m_endPointDirty = true;
	}

	/// Get helix normal vector (base axis direction)
	const TPoint& GetNormalVector() const { return m_normalVector; }

	/// Set helix start vector
	///	@param startVector start vector of helix
	/// @param toleranceProvided tolerance to validate input parameters with
	///	@throws mwException if normal and start vectors not orthogonal
	void SetStartVector(const TPoint& startVector, const T toleranceProvided = mathdef::mw_tol(T()))
	{
		m_startVector = startVector;
		ValidateVectors(toleranceProvided);

		m_bboxDirty = true;
		m_startPointDirty = true;
		m_endPointDirty = true;
	}

	/// Get helix start vector
	const TPoint& GetStartVector() const { return m_startVector; }

	/// Set helix start and normal vector
	///	@param startVector ref to mwTPoint3d
	///	@param normalVector ref to mwTPoint3d
	/// @param toleranceProvided tolerance to validate input parameters with
	///	@throws mwException if normal and start vectors not orthogonal
	void SetStartAndNormalVector(
		const TPoint& startVector,
		const TPoint& normalVector,
		const T toleranceProvided = mathdef::mw_tol(T()))
	{
		m_startVector = startVector;
		m_normalVector = normalVector;
		ValidateVectors(toleranceProvided);

		m_bboxDirty = true;
		m_startPointDirty = true;
		m_endPointDirty = true;
	}

	/// Get helix radius
	T GetRadius() const { return ~m_startVector; }

	/// Set helix sweep angle in degrees
	///	@param sweepAngle const T
	void SetSweepAngle(const T sweepAngle)
	{
		m_sweepAngle = sweepAngle;

		m_bboxDirty = true;
		m_endPointDirty = true;
	}


	/// Get helix sweep angle in degrees
	T GetSweepAngle() const { return m_sweepAngle; }

	/// Get helix radius change
	T GetRadiusChange() const { return m_radiusChange; }

	/// Set helix height
	void SetHeight(const T height)
	{
		m_height = height;

		m_bboxDirty = true;
		m_endPointDirty = true;
	}

	/// Get helix height
	T GetHeight() const { return m_height; }

	/// Get length of helix
	virtual T GetLength() const
	{
		T circumf = GetRadius() * static_cast<T>(mathdef::MW_2PI);
		T lengthOneRotation = mathdef::mw_sqrt(GetPitch() * GetPitch() + circumf * circumf);
		return lengthOneRotation * mathdef::Abs(m_sweepAngle / static_cast<T>(360.));
	}

	/// Returns helix start point
	virtual const TPoint& GetStartPoint() const
	{
		if (m_startPointDirty)
		{
			m_startPoint = m_center + m_startVector;
			m_startPointDirty = false;
		}
		return m_startPoint;
	}

	/// Returns helix end point
	virtual const TPoint& GetEndPoint() const
	{
		if (m_endPointDirty)
		{
			const TPoint normal = m_normalVector.Normalized();
			m_endPoint = m_center + m_startVector;
			m_endPoint.Transform(cadcam::mwMatrixTransformationsFactory<T>::Create3dRotation(
				normal, m_center, m_sweepAngle));
			m_endPoint.Transform(cadcam::mwMatrixTransformationsFactory<T>::Create3dTranslation(
				m_radiusChange * (m_endPoint - m_center)));
			m_endPoint.Transform(
				cadcam::mwMatrixTransformationsFactory<T>::Create3dTranslation(m_height * normal));
			m_endPointDirty = false;
		}
		return m_endPoint;
	}

	/// Returns pitch: height of one full turn of helix
	virtual T GetPitch() const
	{
		return m_height * mathdef::Abs(static_cast<T>(360.) / m_sweepAngle);
	}


	/// @name Visitor pattern
	/// @{
	virtual void AcceptVisitor(mw3dGeometryVisitor<T>& visitor) { visitor.Visit(*this); }
	virtual void AcceptVisitor(mw3dGeometryConstVisitor<T>& visitor) const { visitor.Visit(*this); }
	/// @}
	
	/// Always returns true for helix
	virtual bool IsContinuous(const T) const { return true; }

	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		if (m_bboxDirty)
		{
			m_bbox = CalculateBoundingBox();
			m_bboxDirty = false;
		}
		return m_bbox;
	}

	/// Reverse helix direction
	virtual void Reverse()
	{
		m_startPoint = GetEndPoint();
		m_center += m_normalVector.Normalized() * m_height;
		m_startVector = m_startPoint - m_center;
		m_normalVector = -m_normalVector;
		m_startPointDirty = false;
		m_endPointDirty = true;
	}

	bool operator==(const mw3dHelix<T>& toCompare) const
	{
		return GetCenter() == toCompare.GetCenter() &&
			GetStartVector() == toCompare.GetStartVector() &&
			GetNormalVector() == toCompare.GetNormalVector() &&
			GetSweepAngle() == toCompare.GetSweepAngle() && GetHeight() == toCompare.GetHeight() &&
			GetRadiusChange() == toCompare.GetRadiusChange();
	}

	bool operator!=(const mw3dHelix<T>& toCompare) const { return !(*this == toCompare); }

	virtual ~mw3dHelix() {}

private:
	TPoint m_center;
	TPoint m_startVector;
	TPoint m_normalVector;
	T m_sweepAngle;
	T m_height;
	T m_radiusChange;  // Not implemented
	mutable mw3dBoundingBox<T> m_bbox;
	mutable TPoint m_startPoint;
	mutable TPoint m_endPoint;
	mutable bool m_bboxDirty;
	mutable bool m_startPointDirty;
	mutable bool m_endPointDirty;

	void ValidateVectors(const T toleranceProvided) const
	{
		const T scale = mathdef::mw_max(
							mathdef::Abs(GetCenter().x()),
							mathdef::Abs(GetCenter().y()),
							mathdef::Abs(GetCenter().z())) +
			GetRadius();

		const T tolerance = mathdef::mw_max(mathdef::mw_tol(T()) * (1 + scale), toleranceProvided);

		if (mathdef::is_not_zero(m_startVector * m_normalVector, tolerance))
		{
			MW_EXCEPTION(_T("Helix start point is not in the same plane as the center point!"));
		}
	}

	mw3dBoundingBox<T> CalculateBoundingBox() const;

	static std::pair<T, T> CalculateCoordinateExtremum(
		const TPoint& vec, const T radius, const T stepRad, const T tMax);
};
}  // namespace cadcam
#endif  //	MW_MW3DHELIX_HPP_
