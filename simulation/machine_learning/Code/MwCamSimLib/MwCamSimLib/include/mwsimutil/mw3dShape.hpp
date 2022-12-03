// (C) 2004-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DSHAPE_HPP_
#define MW_MW3DSHAPE_HPP_
#include "mw3dObject.hpp"
#include "mw3dPoint.hpp"


namespace cadcam
{
//=========== Templates declarations.=============
template <class T>
class MW_5AXUTIL_API mw3dPoint;
template <class T>
class MW_5AXUTIL_API mwSphere;
template <class T>
class MW_5AXUTIL_API mwTruncatedCone;
template <class T>
class MW_5AXUTIL_API mwCone;
template <class T>
class MW_5AXUTIL_API mwCylinder;
template <class T>
class MW_5AXUTIL_API mwBox;
template <class T>
class MW_5AXUTIL_API mwClosedTorus;

template <class T>
class MW_5AXUTIL_API mw3dShapeVisitor;

//=========== Classes declarations.=============
// float Geometry
typedef mw3dPoint<float> mw3dfPoint;

typedef misc::mwAutoPointer<mw3dfPoint> mw3dfPointPtr;

typedef mw3dShapeVisitor<float> mw3dfShapeVisitor;

/// double field
typedef mw3dPoint<double> mw3ddPoint;

typedef misc::mwAutoPointer<mw3ddPoint> mw3ddPointPtr;

typedef mw3dShapeVisitor<double> mw3ddShapeVisitor;

/// Interface for 3d Shape entities like Sphere, Cylinder, Cone and Box
template <typename T>
class MW_5AXUTIL_API mw3dShape: public mw3dObject<T>
{
public:
	typedef typename misc::mwAutoPointer<mw3dShape<T>> Ptr;
	typedef typename misc::mwAutoPointer<mw3dShape<T>> mw3dShapePtr;
	typedef mw3dPoint<T> Point;
	typedef misc::mwAutoPointer<Point> PointPtr;
	typedef mwMatrix<T, 4, 4> homogenousMatrix;

	/// The AcceptVisitor function
	/// @param	visitor	a parameter of type mw3dObjectVisitor&
	virtual void AcceptVisitor(mw3dObjectVisitor<T>& visitor) = 0;

	/// The AcceptVisitor function
	/// @param	visitor	a parameter of type const mw3dObjectVisitor&
	virtual void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const = 0;

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	virtual void AcceptVisitor(mw3dShapeVisitor<T>& visitor) const = 0;

	///	IsContinuous
	///
	///	Returns true if the geometric object is continuous
	///	@returns const bool
	virtual bool IsContinuous(const T& tolerance = 0) const = 0;

	///	GetVolume
	///
	///	Returns the volume of shape object.
	///	@returns volume
	virtual T GetVolume() const = 0;

	///	GetArea
	///
	///	Returns the area of shape object.
	///	@returns area
	virtual T GetArea() const = 0;

	/// Destructor
	virtual ~mw3dShape(){};
};


template <class T>
class MW_5AXUTIL_API mw3dShapeVisitor
{
public:
	virtual ~mw3dShapeVisitor() MW_DEFAULT_DESTRUCTOR_IMPL

	/// Visit const mwSphere< T >
	virtual void Visit(const mwSphere<T>& tv) = 0;

	/// Visit const mwTruncatedCone< T >
	virtual void Visit(const mwTruncatedCone<T>& tv) = 0;

	/// Visit const mwClosedTorus< T >
	virtual void Visit(const mwClosedTorus<T>& tv) = 0;

	/// Visit const mwCone< T >
	virtual void Visit(const mwCone<T>& tv) = 0;

	/// Visit const mwCylinder< T >
	virtual void Visit(const mwCylinder<T>& tv) = 0;

	/// Visit const mwBox< T >
	virtual void Visit(const mwBox<T>& tv) = 0;
};
}  // namespace cadcam
#endif  //	MW_MW3DSHAPE_HPP_
