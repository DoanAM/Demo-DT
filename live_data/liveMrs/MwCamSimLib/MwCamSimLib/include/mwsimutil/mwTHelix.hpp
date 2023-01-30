// (C) 2005-2016 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWTHELIX_HPP_
#define MW_MWTHELIX_HPP_
#include <mwTGeometry3d.hpp>
#include <mwTHelixBase.hpp>

namespace geoDef
{
//! Implements a linear Helix
/*! The Helix is build using the followings conventions:

	- has the center in the origin of SC
	- angle is CCW
	- start point is (R,0,0) in SC
	- the step of the helix is for one radian

	The Helix is parameterized by X = C + R*(cos(A)*i + sin(A)*j) + (A*step)*k where
	A is an angle in radian

	The Helix is define using vectors i,j and k(XYZ plane)
*/
template<typename T, typename TCoordSystem>
class MW_5AXUTIL_API mwTHelix : public mwTGeometry3d<T, TCoordSystem>
{
public:
	typedef typename mwTGeometry3d<T, TCoordSystem>::BaseGeoValueType	BaseGeoValueType;
	typedef typename mwTGeometry3d<T, TCoordSystem>::CoordSystem		CoordSystem;
	typedef typename mwTGeometry3d<T, TCoordSystem>::CSValueType		CSValueType;
	typedef typename mwTGeometry3d<T, TCoordSystem>::GeoGetter3d		GeoGetter3d;
	typedef typename mwTGeometry3d<T, TCoordSystem>::GeoSetter3d		GeoSetter3d;
	typedef typename mwTGeometry3d<T, TCoordSystem>::PositionVector		PositionVector;
	typedef typename mwTGeometry3d<T, TCoordSystem>::ViewPtr			ViewPtr;

private:
	typedef mwTHelix<BaseGeoValueType, CoordSystem>						MySelf;

public:
	typedef mwTGeometry3d<BaseGeoValueType, CoordSystem>				GeometryType;
	typedef mwTHelixBase<BaseGeoValueType>								BaseGeo;
	typedef typename misc::mwAutoPointer<MySelf>						Ptr;

	//!Constructor
	//! \param base geometry definition
	//! \param cs coordinate system to be used
	//! \param view the view to which the cs is relative to
	//! 	MW_NULL means the cs is relative to world coordinates
	mwTHelix(const BaseGeo& base, const CoordSystem& cs, const ViewPtr& view = ViewPtr());

	//! Obtain the Position Vector of a point from the helix at a specific angle
	//! \return the vector of position
	const PositionVector GetVector(const BaseGeoValueType& angle) const;

	//! Obtain the length of the helix for a specific sweep angle
	//! \return length of the helix
	const BaseGeoValueType GetLength(const BaseGeoValueType& angle) const;

	//! gets base Helix
	//! \returns the base Helix
	inline const BaseGeo& GetBase() const
	{
		return m_Base;
	}

	//! sets base Helix
	//! \param base the new base Helix
	inline void SetBase(const BaseGeo& base)
	{
		m_Base = base;
	}

	//! gets base Geometry3d
	//! \returns the base Geometry3d
	virtual const typename GeometryType::BaseGeo& GetBaseGeometry3d() const
	{
		return GetBase();
	}

	//! implements visitor pattern for setting data in the current 3d geometry
	//! \param setter the visitor to setting data in the current CS
	virtual void AcceptVisitor(const GeoSetter3d& setter);

	//! implements visitor pattern for getting data from the current 3d geometry
	//! \param getter the visitor to interrogate the current CS
	virtual void AcceptVisitor(GeoGetter3d& getter) const;

	//! Check if two helices are equal
	const bool operator==(const mwTHelix<T, TCoordSystem>& toCompare) const;

	//! Check if two helices are not equal
	const bool operator!=(const mwTHelix<T, TCoordSystem>& toCompare) const;

	//! Checks if parameters of two helices are equal within tolerances
	/*! Checks if distance between start/end/center points are within tolerance
		and their orientations differ not more than minCos.
			\param toCompare the helix to be compared with.
			\param delta given tolerance factor.
			\param minCos given minimal cosines of angle between orientations in defined points.
	*/
	const bool ExactCompareTolerance(
		const mwTHelix<T, TCoordSystem>& helix,
		const T delta,
		const T minCos) const;
private:
	BaseGeo m_Base;
};

typedef mwTHelix<float, CS3df> HelixfIn3df;
typedef mwTHelix<double, CS3dd> HelixdIn3dd;
}  // namespace geoDef
#endif	//	MW_MWTHELIX_HPP_
