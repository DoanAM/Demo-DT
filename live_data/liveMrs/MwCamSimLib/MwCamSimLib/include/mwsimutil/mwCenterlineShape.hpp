// (C) 2007-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCENTERLINESHAPE_HPP_
#define MW_MWCENTERLINESHAPE_HPP_
#include "mw3dShape.hpp"


namespace cadcam
{
/// Shapes_Parts const sides
const int MW_SHAPE_PARTS_SIDES = 1;
/// Shapes_Parts const bottom
const int MW_SHAPE_PARTS_BOTTOM = 2;
/// Shapes_Parts const top
const int MW_SHAPE_PARTS_TOP = 4;
/// Shapes_Parts const all
const int MW_SHAPE_PARTS_ALL = 7;

/// Default radius
const double MW_SHAPE_DEFAULT_RADIUS = 50.;
/// Default height
const double MW_SHAPE_DEFAULT_HEIGHT = 100.;

/// Implements a shape with two center points
///
/// by holding the centers' coordinates
template <class T>
class MW_5AXUTIL_API mwCenterlineShape: public mw3dShape<T>
{
public:
	typedef misc::mwAutoPointer<mwCenterlineShape<T>> mwCenterlineShapePtr;
	typedef typename mw3dShape<T>::homogenousMatrix homogenousMatrix;
	typedef typename mw3dShape<T>::PointPtr PointPtr;
	typedef typename mw3dShape<T>::Point Point;

	/// Default Constructor
	///
	/// Init Truncated Cone with center positions in the origin and radiuses 0 and
	/// MW_SHAPE_DEFAULT_RADIUS.
	mwCenterlineShape()
		: Center1(new Point(mwTPoint3d<T>(0, 0, static_cast<T>(-MW_SHAPE_DEFAULT_HEIGHT * .5)))),
		  Center2(new Point(mwTPoint3d<T>(0, 0, static_cast<T>(MW_SHAPE_DEFAULT_HEIGHT * .5)))),
		  Parts(MW_SHAPE_PARTS_ALL),
		  m_bBoxDirty(true)
	{
	}


	/// Constructor
	///
	/// Init shape with center positions
	///	@param height a const ref to T for Cone's height
	///	@param parts the parts(sides, bottom, top or all)
	mwCenterlineShape(T height, int parts = MW_SHAPE_PARTS_ALL)
		: Center1(new Point(mwTPoint3d<T>(0., 0., 0.))),
		  Center2(new Point(mwTPoint3d<T>(0., 0., height))),
		  Parts(parts),
		  m_bBoxDirty(true)
	{
	}


	/// Constructor
	///
	/// Init shape with center positions
	///	@param center1 a const ref to 3d PointPtr for Truncated Cone's center coordinates
	///	@param center2 a const ref to 3d PointPtr for Truncated Cone's center coordinates
	///	@param parts the parts(sides, bottom, top or all)
	mwCenterlineShape(PointPtr center1, PointPtr center2, int parts = MW_SHAPE_PARTS_ALL)
		: m_bBoxDirty(true)
	{
		if (mathdef::is_eq(~(*center1 - *center2), 0, static_cast<T>(mathdef::MW_MATH_TOL)))
			throw misc::mwException(0, _T("center1 and center2 should be not equal"));
		Center1 = center1;
		Center2 = center2;
		Parts = parts;
	}

	/// Copy shape
	///
	/// Creates a exact copy of a given shape
	/// @param toCopy shape to create a copy of
	mwCenterlineShape(const mwCenterlineShape& toCopy) { Copy(toCopy); }

	/// Assignment operator
	///
	/// Assigns one shape object to another
	///  @param toCopy shape to copy the information from
	///  @returns current shape with copied information
	const mwCenterlineShape& operator=(const mwCenterlineShape& toCopy)
	{
		if (&toCopy == this)
			return *this;

		Copy(toCopy);

		return *this;
	}

	/// Equality operator
	///
	/// Are given shapes equal?
	///  @param toCompare shape to compare with
	///  @returns <b>true</b> if both shapes contain the same parameters,
	///  <b>false</b> otherwise
	const bool operator==(const mwCenterlineShape& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return Parts == toCompare.Parts && PointPtr::ShallowComparer(Center1, toCompare.Center1) &&
			PointPtr::ShallowComparer(Center2, toCompare.Center2);
	}


	/// SetCenter1
	///
	/// Set shape's Center1 position
	///	@param center const ref to 3d PointPtr
	void SetCenter1(PointPtr& center)
	{
		// TODO: this function should be removed, SetCenters is to be used instead
		if (mathdef::is_eq(
				~(*center - *Center2), static_cast<T>(0.), static_cast<T>(mathdef::MW_MATH_TOL)))
			throw misc::mwException(0, _T("center1 and center2 should be not equal"));

		Center1 = center;
		m_bBoxDirty = true;
	}


	/// SetCenter2
	///
	/// Set shape's Center2 position
	///	@param center const ref to 3d PointPtr
	void SetCenter2(PointPtr& center)
	{
		// TODO: this function should be removed, SetCenters is to be used instead
		if (mathdef::is_eq(
				~(*Center1 - *center), static_cast<T>(0), static_cast<T>(mathdef::MW_MATH_TOL)))
			throw misc::mwException(0, _T("center1 and center2 should be not equal"));

		Center2 = center;
		m_bBoxDirty = true;
	}


	/// SetCenters
	///
	/// Set shape's centers positions
	/// @param center1 ref to 3d PointPtr
	/// @param center2 ref to 3d PointPtr
	void SetCenters(PointPtr& center1, PointPtr& center2)
	{
		if (mathdef::is_eq(
				~(*center2 - *center1), static_cast<T>(0), static_cast<T>(mathdef::MW_MATH_TOL)))
			throw misc::mwException(0, _T("center1 and center2 should be not equal"));
		Center1 = center1;
		Center2 = center2;
		m_bBoxDirty = true;
	}

	/// GetCenter1
	///
	/// Get shape's Center1 position
	///	@returns const 3d PointPtr
	PointPtr GetCenter1() const { return Center1; }


	/// GetCenter2
	///
	/// Get Truncated Cone's Center2 position
	///	@returns const 3d PointPtr
	PointPtr GetCenter2() const { return Center2; }


	/// SetHeight
	///
	/// Set shape's height
	///	@param height const T
	void SetHeight(const T height)
	{
		Point v1 = *GetCenter1();
		Point v2old = *GetCenter2();
		Point v2new = v1 + height * (!(v2old - v1));
		SetCenter2(v2new);
	}


	/// GetHeight
	///
	/// Get shape's height
	///	@returns const T
	///		Where T can be int, float or double
	T GetHeight() const
	{
		Point v1 = *GetCenter1();
		Point v2 = *GetCenter2();
		return ~(v2 - v1);
	}


	/// GetTransformationMatrix
	///
	/// Get shape's Transformation Matrix assuming y the axis
	///	@returns const homogenousMatrix
	const homogenousMatrix GetTransformationMatrix() const
	{
		homogenousMatrix transf;
		Point v1 = *GetCenter1();
		Point v2 = *GetCenter2();

		//			if (! is_eq<T> ( ~(v1-v2), 0.,mathdef::MW_MATH_TOL) )
		//			{

		Point axis[4];

		axis[3] = (v1 + v2) * (T)0.5;
		axis[1] = (v2 - v1).Normalized();
		axis[0] = Point(1, 0, 0);
		axis[2] = Point(0, 0, 1);

		if (~(axis[0] % axis[1]) != 0)
		{
			axis[0] = (axis[0] % axis[1]).Normalized();
			axis[2] = (axis[0] % axis[1]).Normalized();
		}
		else
		{
			axis[2] = (axis[1] % axis[2]).Normalized();
			axis[0] = (axis[1] % axis[2]).Normalized();
		}

		for (int i = 0; i < 3; ++i)
		{
			transf[0][i] = axis[i].x();
			transf[1][i] = axis[i].y();
			transf[2][i] = axis[i].z();
			transf[3][i] = 0;
		}

		transf[0][3] = axis[3].x();
		transf[1][3] = axis[3].y();
		transf[2][3] = axis[3].z();
		transf[3][3] = 1;
		//			}
		return transf;
	}


	/// SetParts
	///
	/// Set Truncated Cone's parts
	///	@param parts const int
	void SetParts(const int parts) { Parts = parts; }

	/// GetParts
	///
	/// Get Truncated Cone's Parts
	///	@returns const int
	int GetParts() const { return Parts; }
	/// GetBoundingBox retrieves the 3d object's bounding box
	///
	/// @returns 3d bounding box
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const
	{
		if (m_bBoxDirty)
		{
			CalculateBoundingBox();
			m_bBoxDirty = false;
		}
		return m_bbox;
	}
	///	IsContinuous
	///
	///	Returns true if the geometric object is continuous
	///	@returns const bool
	bool IsContinuous(const T&) const { return true; }
	/// Destructor
	~mwCenterlineShape(){};

protected:
	virtual void CalculateBoundingBox() const = 0;

	/// The center of the first basis
	PointPtr Center1;
	/// The center of the second basis
	PointPtr Center2;
	/// The number of the parts toe shape has, from MW_SHAPE_PARTS_SIDES to MW_SHAPE_PARTS_ALL
	int Parts;
	mutable mw3dBoundingBox<T> m_bbox;
	mutable bool m_bBoxDirty;

private:
	void Copy(const mwCenterlineShape& toCopy)
	{
		Center1 = new Point(*toCopy.Center1);
		Center2 = new Point(*toCopy.Center2);
		Parts = toCopy.Parts;
		m_bbox = toCopy.m_bbox;
		m_bBoxDirty = toCopy.m_bBoxDirty;
	}
};
}  // namespace cadcam
#endif  //	MW_MWCENTERLINESHAPE_HPP_
