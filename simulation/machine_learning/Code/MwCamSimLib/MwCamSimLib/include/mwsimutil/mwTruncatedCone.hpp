// (C) 2004-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTRUNCATEDCONE_HPP_
#define MW_MWTRUNCATEDCONE_HPP_
#include "mwCenterlineShape.hpp"


namespace cadcam
{
/// Implements a Truncated Cone
///
/// by holding the centers' coordinates and radii of the two circles that defines it
template <class T>
class MW_5AXUTIL_API mwTruncatedCone: public mwCenterlineShape<T>
{
public:
	typedef typename misc::mwAutoPointer<mwTruncatedCone<T>> mwTruncatedConePtr;
	typedef typename mwCenterlineShape<T>::PointPtr PointPtr;
	typedef typename mwCenterlineShape<T>::Point Point;

	/// Default Constructor
	///
	/// Init Truncated Cone with center positions in the origin and radiuses 0 and
	/// MW_SHAPE_DEFAULT_RADIUS.
	mwTruncatedCone()
		: mwCenterlineShape<T>(),
		  Radius1(static_cast<T>(MW_SHAPE_DEFAULT_RADIUS)),
		  Radius2(static_cast<T>(0))
	{
	}

	/// Constructor
	///
	/// Init Truncated Cone with center positions and radiuses
	///	@param radius1 a const ref to T for Truncated Cone's radius
	///	@param radius2 a const ref to T for Truncated Cone's radius
	///	@param height a const ref to T for Cone's height
	///	@param parts the parts(sides, bottom, top or all)
	mwTruncatedCone(T radius1, T radius2, T height, int parts = MW_SHAPE_PARTS_ALL)
		: mwCenterlineShape<T>(height, parts), Radius1(radius1), Radius2(radius2)
	{
	}

	/// Constructor
	///
	/// Init Truncated Cone with center positions and radiuses
	///	@param center1 a const ref to 3d PointPtr for Truncated Cone's center coordinates
	///	@param radius1 a const ref to T for Truncated Cone's radius
	///	@param center2 a const ref to 3d PointPtr for Truncated Cone's center coordinates
	///	@param radius2 a const ref to T for Truncated Cone's radius
	///	@param parts the parts(sides, bottom, top or all)
	mwTruncatedCone(
		PointPtr center1,
		T radius1,
		PointPtr center2,
		T radius2,
		int parts = cadcam::MW_SHAPE_PARTS_ALL)
		: mwCenterlineShape<T>(center1, center2, parts), Radius1(radius1), Radius2(radius2)
	{
	}

	/// SetRadius1
	///
	/// Set Truncated Cone's radius1
	///	@param radius const T
	void SetRadius1(const T radius)
	{
		Radius1 = radius;
		this->m_bBoxDirty = true;
	}

	/// SetRadius2
	///
	/// Set Truncated Cone's radius2
	///	@param radius const T
	void SetRadius2(const T radius)
	{
		Radius2 = radius;
		this->m_bBoxDirty = true;
	}

	/// GetRadius1
	///
	/// Get Truncated Cone's Radius1
	///	@returns const T
	///		Where T can be int, float or double
	T GetRadius1() const { return Radius1; }

	/// GetRadius2
	///
	/// Get Truncated Cone's Radius2
	///	@returns const T
	///		Where T can be int, float or double
	T GetRadius2() const { return Radius2; }

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	virtual void AcceptVisitor(mw3dObjectVisitor<T>& visitor) { visitor.Visit(*this); }

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	virtual void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const { visitor.Visit(*this); }


	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	void AcceptVisitor(mw3dShapeVisitor<T>& visitor) const { visitor.Visit(*this); }

	///	GetArea
	///
	///	Returns the area of the Truncated Cone
	///	@returns const T
	T GetArea() const
	{
		T radius1 = GetRadius1();
		T radius2 = GetRadius2();
		T height = this->GetHeight();
		T generatrix = sqrt((radius2 - radius1) * (radius2 - radius1) - height * height);
		T area = 0.;
		int iParts = this->GetParts();

		if (iParts & MW_SHAPE_PARTS_BOTTOM)
			area += (T)mathdef::MW_PI * radius1 * radius1;

		if (iParts & MW_SHAPE_PARTS_TOP)
			area += (T)mathdef::MW_PI * radius2 * radius2;

		if (iParts & MW_SHAPE_PARTS_SIDES)
			area += (T)mathdef::MW_PI * generatrix * (radius1 + radius2);

		return area;
	}

	///	GetVolume
	///
	///	Returns the volume of the Truncated Cone
	///	@returns const T
	T GetVolume() const
	{
		T radius1 = GetRadius1();
		T radius2 = GetRadius2();
		T height = this->GetHeight();
		return (T)mathdef::MW_PI / (T)3. * height *
			(radius1 * radius1 + radius1 * radius2 + radius2 * radius2);
	}

	///	Normalize
	///
	///	Normalizes the Truncated Cone: if Radius2 > Radius1,
	///	swaps the radiuses and the centers
	///	@returns const bool true if needed to normalize
	bool Normalize()
	{
		T radius1 = GetRadius1();
		T radius2 = GetRadius2();

		if (radius1 >= radius2)
			return false;

		// Swap radiuses
		SetRadius1(radius2);
		SetRadius2(radius1);

		// Swap centers
		PointPtr center1 = this->GetCenter2();
		PointPtr center2 = this->GetCenter1();

		this->Center1 = center1;
		this->Center2 = center2;
		// SetCenter1( center1 );
		// SetCenter2( center2 );

		return true;
	}

	/// Destructor
	virtual ~mwTruncatedCone(){};

protected:
	/// CalculateBoundingBox function
	void CalculateBoundingBox() const
	{
		Point c1 = *this->GetCenter1();
		Point c2 = *this->GetCenter2();
		T height = this->GetHeight();
		T radius1 = GetRadius1();
		T radius2 = GetRadius2();
		T Dx = mathdef::mw_sqrt(height * height - (c1.x() - c2.x()) * (c1.x() - c2.x())) / height;
		T Dy = mathdef::mw_sqrt(height * height - (c1.y() - c2.y()) * (c1.y() - c2.y())) / height;
		T Dz = mathdef::mw_sqrt(height * height - (c1.z() - c2.z()) * (c1.z() - c2.z())) / height;
		Point D(Dx, Dy, Dz);
		Point R1 = radius1 * D;
		Point R2 = radius2 * D;
		mw3dBoundingBox<T> bbox2((c2 - R2).getTPoint(), (c2 + R2).getTPoint());
		this->m_bbox.SetCorners((c1 - R1).getTPoint(), (c1 + R1).getTPoint());
		this->m_bbox += bbox2;
	}

private:
	/// The radius of the first basis
	T Radius1;
	/// The radius of the second basis
	T Radius2;
};
}  // namespace cadcam
#endif  //	MW_MWTRUNCATEDCONE_HPP_
