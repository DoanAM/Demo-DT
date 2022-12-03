// (C) 2003-2015 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MW3DOBJECT_HPP_
#define MW_MW3DOBJECT_HPP_
#include "mwCachingInternalDefs.hpp"
#include "mwDllImpExpDef.hpp"


namespace misc
{
template <typename T>
class mwAutoPointer;
}

namespace cadcam
{
//=========== Templates declarations.=============
template <class T>
class MW_5AXUTIL_API mw3dObject;
template <class T>
class MW_5AXUTIL_API mw3dGeometry;
template <class T>
class MW_5AXUTIL_API mw3dShape;
template <class T>
class MW_5AXUTIL_API mwTMesh;
template <class T>
class MW_5AXUTIL_API mw3dBoundingBox;
template <class T>
class MW_5AXUTIL_API mwTOrderedPntCloud;

template <class T>
class MW_5AXUTIL_API mw3dObjectVisitor;
template <class T>
class MW_5AXUTIL_API mw3dObjectVisitorBase;

//=========== Classes declarations.=============
// float Geometry
typedef mw3dObject<float> mw3dfObject;
typedef mw3dGeometry<float> mw3dfGeometry;
typedef mw3dShape<float> mw3dfShape;
typedef mwTMesh<float> mwfMesh;
typedef mwTOrderedPntCloud<float> mwfOrderedPntCloud;

typedef misc::mwAutoPointer<mw3dfObject> mw3dfObjectPtr;
typedef misc::mwAutoPointer<mw3dfGeometry> mw3dfGeometryPtr;
typedef misc::mwAutoPointer<mw3dfShape> mw3dfShapePtr;
typedef misc::mwAutoPointer<mwfMesh> mwfMeshPtr;
typedef misc::mwAutoPointer<mwfOrderedPntCloud> mwfOrderedPntCloudPtr;

typedef mw3dObjectVisitor<float> mw3dfObjectVisitor;
typedef mw3dObjectVisitorBase<float> mw3dfObjectVisitorBase;

// double field
typedef mw3dObject<double> mw3ddObject;
typedef mw3dGeometry<double> mw3ddGeometry;
typedef mw3dShape<double> mw3ddShape;
typedef mwTMesh<double> mwdMesh;
typedef mwTOrderedPntCloud<double> mwdOrderedPntCloud;

typedef misc::mwAutoPointer<mw3ddObject> mw3ddObjectPtr;
typedef misc::mwAutoPointer<mw3ddGeometry> mw3ddGeometryPtr;
typedef misc::mwAutoPointer<mw3ddShape> mw3ddShapePtr;
typedef misc::mwAutoPointer<mwdMesh> mwdMeshPtr;
typedef misc::mwAutoPointer<mwdOrderedPntCloud> mwdOrderedPntCloudPtr;

typedef mw3dObjectVisitor<double> mw3ddObjectVisitor;
typedef mw3dObjectVisitorBase<double> mw3ddObjectVisitorBase;

// collection definitions will comes...

/// Top level brand
#pragma CACHING_INTERNAL_BEGIN
template <typename T>
class MW_5AXUTIL_API mw3dObject
{
public:
	typedef T ValueType;
	typedef typename misc::mwAutoPointer<mw3dObject<T>> Ptr;
	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor ref to visitor
	virtual void AcceptVisitor(mw3dObjectVisitor<T>& visitor) = 0;

	/// AcceptVisitor implements visitor pattern
	///
	/// @param visitor const ref to visitor
	virtual void AcceptVisitor(const mw3dObjectVisitor<T>& visitor) const = 0;

	/// GetBoundingBox retrieves the 3d object's bounding box
	///
	/// @returns 3d bounding box
	virtual const mw3dBoundingBox<T>& GetBoundingBox() const = 0;

	/// Destructor
	virtual ~mw3dObject(){};
};
#pragma CACHING_INTERNAL_END

template <typename T>
class mw3dObjectVisitor
{
public:
	/// Visit mw3dGeometry<T>
	virtual void Visit(mw3dGeometry<T>& tv) = 0;
	/// Visit const mw3dGeometry<T>
	virtual void Visit(const mw3dGeometry<T>& tv) const = 0;

	/// Visit mwTOrderedPntCloud<T>
	virtual void Visit(mwTOrderedPntCloud<T>& tv) = 0;
	/// Visit const mwTOrderedPntCloud<T>
	virtual void Visit(const mwTOrderedPntCloud<T>& tv) const = 0;

	/// Visit mwTMesh<T>
	virtual void Visit(mwTMesh<T>& tv) = 0;
	/// Visit const mwTMesh<T>
	virtual void Visit(const mwTMesh<T>& tv) const = 0;

	/// Visit mw3dShape<T>
	virtual void Visit(mw3dShape<T>& tv) = 0;
	/// Visit const mw3dShape<T>
	virtual void Visit(const mw3dShape<T>& tv) const = 0;

	/// Destructor
	virtual ~mw3dObjectVisitor(){};
};

}  // namespace cadcam
#endif  //	MW_MW3DOBJECT_HPP_
