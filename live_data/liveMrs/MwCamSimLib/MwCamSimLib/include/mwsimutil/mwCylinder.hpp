// (C) 2004-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCYLINDER_HPP_
#define MW_MWCYLINDER_HPP_
#include "mwCenterlineShape.hpp"
#include "mwTruncatedCone.hpp"

namespace cadcam
{
/// Cylinder defined by base center point, height and radius
template <class T>
class MW_5AXUTIL_API mwCylinder : public mwCenterlineShape<T>
{
public:
	typedef typename misc::mwAutoPointer<mwCylinder<T>> mwCylinderPtr;
	typedef mw3dPoint<T> Point;
	typedef typename misc::mwAutoPointer<mw3dPoint<T>> PointPtr;

	mwCylinder() : mwCenterlineShape<T>(), m_r(static_cast<T>(MW_SHAPE_DEFAULT_RADIUS)) {}

	/// Constructor
	///
	///	@param radius radius
	///	@param height height
	///	@param parts the parts
	/// (MW_SHAPE_PARTS_SIDES, MW_SHAPE_PARTS_BOTTOM, MW_SHAPE_PARTS_TOP or MW_SHAPE_PARTS_ALL)
	mwCylinder(T radius, T height, int parts = MW_SHAPE_PARTS_ALL)
		: mwCenterlineShape<T>(height, parts), m_r(radius)
	{
	}

	/// Constructor
	///
	///	@param center1 first point of cylinder axis
	///	@param radius cylinder radius
	///	@param center2 second point of cylinder axis
	///	@param parts the parts
	/// (MW_SHAPE_PARTS_SIDES, MW_SHAPE_PARTS_BOTTOM, MW_SHAPE_PARTS_TOP or MW_SHAPE_PARTS_ALL)
	mwCylinder(PointPtr center1, T radius, PointPtr center2, int parts = MW_SHAPE_PARTS_ALL)
		: mwCenterlineShape<T>(center1, center2, parts), m_r(radius)
	{
	}

	const bool operator==(const mwCylinder& toCompare) const
	{
		if (&toCompare == this)
			return true;

		if (!mwCenterlineShape<T>::operator==(toCompare))  // compare measurement units
			return false;

		return m_r == toCompare.m_r;
	}

	void SetRadius(const T radius)
	{
		m_r = radius;
		this->m_bBoxDirty = true;
	}

	T GetRadius() const { return m_r; }

	/// @name Visitor pattern
	/// @{
	virtual void AcceptVisitor(mw3dObjectVisitor<T>& visitor) { visitor.Visit(*this); }
	virtual void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const { visitor.Visit(*this); }
	virtual void AcceptVisitor(mw3dShapeVisitor<T>& visitor) const { visitor.Visit(*this); };
	/// @}

protected:
	///	Returns the area of cylinder
	T GetArea() const
	{
		T height = this->GetHeight();
		T area = 0.;
		int iParts = this->GetParts();

		if (iParts & MW_SHAPE_PARTS_BOTTOM)
			area += (T)mathdef::MW_PI * m_r * m_r;

		if (iParts & MW_SHAPE_PARTS_TOP)
			area += (T)mathdef::MW_PI * m_r * m_r;

		if (iParts & MW_SHAPE_PARTS_SIDES)
			area += (T)mathdef::MW_PI * height * (T)2.0 * m_r;

		return area;
	}
	///	Returns the volume of cylinder
	T GetVolume() const
	{
		T height = this->GetHeight();
		return (T)mathdef::MW_PI * height * m_r * m_r;
	}
	void CalculateBoundingBox() const
	{
		Point c1 = *this->GetCenter1();
		Point c2 = *this->GetCenter2();
		T height = this->GetHeight();
		T Dx = sqrt(height * height - (c1.x() - c2.x()) * (c1.x() - c2.x())) / height;
		T Dy = sqrt(height * height - (c1.y() - c2.y()) * (c1.y() - c2.y())) / height;
		T Dz = sqrt(height * height - (c1.z() - c2.z()) * (c1.z() - c2.z())) / height;
		Point D(Dx, Dy, Dz);
		Point R = m_r * D;
		mw3dBoundingBox<T> bbox2((c2 - R).getTPoint(), (c2 + R).getTPoint());
		this->m_bbox.SetCorners((c1 - R).getTPoint(), (c1 + R).getTPoint());
		this->m_bbox += bbox2;
	}
	/// @hidden
	T m_r;
};
}  // namespace cadcam
#endif  //	MW_MWCYLINDER_HPP_