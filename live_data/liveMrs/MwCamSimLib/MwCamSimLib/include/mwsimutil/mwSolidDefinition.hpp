// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSOLIDDEFINITION_HPP_
#define MW_MWSOLIDDEFINITION_HPP_

#include "mw2dBoundingBox.hpp"
#include "mw2dContour.hpp"
#include "mw3dBoundingBox.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwMeasurable.hpp"
#include "mwVirtualPureDef.hpp"


namespace cadcam
{
//=========== Templates declarations.=============

template <typename T>
class MW_5AXUTIL_API mwSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwRevolvedSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwRevolvedSolidExtractor;

template <typename T>
class MW_5AXUTIL_API mwExtrudedSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwMeshSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwTypedExtrudedSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwTurningSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionVisitorGetter;

template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionVisitorSetter;

template <typename T>
class MW_5AXUTIL_API mwWireSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwWireSolidExtractor;

template <typename T>
class MW_5AXUTIL_API mwContourTurningSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwPrimeTurningSolidDefinition;

template <typename T>
class MW_5AXUTIL_API mwThreadTapSolidDefinition;


//=========== Classes declarations.=============
// float Solids
typedef mwSolidDefinition<float> mwfSolidDefinition;
typedef mwRevolvedSolidDefinition<float> mwfRevolvedSolidDefinition;
typedef mwRevolvedSolidExtractor<float> mwfRevolvedSolidExtractor;
typedef mwExtrudedSolidDefinition<float> mwfExtrudedSolidDefinition;
typedef mwMeshSolidDefinition<float> mwfMeshSolidDefinition;
typedef mwTypedExtrudedSolidDefinition<float> mwfTypedExtrudedSolidDefinition;
typedef mwTurningSolidDefinition<float> mwfTurningSolidDefinition;
typedef mwSolidDefinitionVisitorGetter<float> mwfSolidDefinitionVisitorGetter;
typedef mwSolidDefinitionVisitorSetter<float> mwfSolidDefinitionVisitorSetter;
typedef mwContourTurningSolidDefinition<float> mwfContourTurningSolidDefinition;
typedef mwThreadTapSolidDefinition<float> mwfThreadTapSolidDefinition;

// double Solids
typedef mwSolidDefinition<double> mwdSolidDefinition;
typedef mwRevolvedSolidDefinition<double> mwdRevolvedSolidDefinition;
typedef mwRevolvedSolidExtractor<double> mwdRevolvedSolidExtractor;
typedef mwExtrudedSolidDefinition<double> mwdExtrudedSolidDefinition;
typedef mwMeshSolidDefinition<double> mwdMeshSolidDefinition;
typedef mwTypedExtrudedSolidDefinition<double> mwdTypedExtrudedSolidDefinition;
typedef mwTurningSolidDefinition<double> mwdTurningSolidDefinition;
typedef mwWireSolidDefinition<double> mwdWireSolidDefinition;
typedef mwSolidDefinitionVisitorGetter<double> mwdSolidDefinitionVisitorGetter;
typedef mwSolidDefinitionVisitorSetter<double> mwdSolidDefinitionVisitorSetter;
typedef mwContourTurningSolidDefinition<double> mwdContourTurningSolidDefinition;
typedef mwPrimeTurningSolidDefinition<double> mwdPrimeTurningSolidDefinition;
typedef mwThreadTapSolidDefinition<double> mwdThreadTapSolidDefinition;

/// @class mwSolidDefinition
/// Base class for 3D solid definition
/// it is created in x,y,z coordinates where:
/// X axis represents width
/// Y axis represents height
/// Z axis represents Depth
template <typename T>
class MW_5AXUTIL_API mwSolidDefinition: public measures::mwMeasurable
{
public:
	typedef typename misc::mwAutoPointer<mwSolidDefinition<T>> Ptr;
	typedef typename measures::mwMeasurable::Units Units;
	typedef cadcam::mw2dContour<T> Contour;
	typedef typename Contour::Ptr ContourPtr;

	/// Constructor
	mwSolidDefinition(const Units units);

	/// Destructor
	virtual ~mwSolidDefinition(){};

	/// Comparison operator
	///
	/// Use this operator to compare the parameters of two tools.
	/// @param rToCompare is the mwSolidDefinition object to be compared with the current object.
	/// @return <b>True</b> if both definitions contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwSolidDefinition<T>& rToCompare) const;

	/// Returns the 3d bounding box of the revolved solid.
	///
	/// @return infinite box for an infinite tool.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const = 0;

	/// AcceptVisitor implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor) = 0;

	/// Implements the visitor pattern for const visitors.
	///
	/// @param visitor is a const reference to the getter visitor.
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const = 0;

	MW_DEPRECATED("Deprecated since 2017.12. Use GetBoundingBox3d().GetSizeZ()")
	virtual const T GetHeight() const
	{
		const cadcam::mw3dBoundingBox<T>& bbox = GetBoundingBox3d();
		return bbox.IsInitialized() ? bbox.GetSizeZ() : 0;
	};

	MW_DEPRECATED(
		"Deprecated since 2017.08. Use mwRevolvedSolidDefinition::GetProfile().GetBoundingBox() or "
		"mwExtrudedSolidDefinition::GetContourExtrusionBase().GetBoundingBox()")
	virtual const mw2dBoundingBox<T> GetPlanarBoundingBox() const
	{
		mw3dBoundingBox<T> bb3d = GetBoundingBox3d();
		return mw2dBoundingBox<T>(
			mwTPoint2d<T>(bb3d.GetMin().x(), bb3d.GetMin().z()),
			mwTPoint2d<T>(bb3d.GetMax().x(), bb3d.GetMax().z()));
	};

protected:
	/// Scales the solid by a given scale factor.
	///
	/// @param  units are the measurement units of this solid.
	/// @param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor) = 0;

	/// Copy constructor
	mwSolidDefinition(const mwSolidDefinition<T>& rToCopy);

	/// Copy operator
	const mwSolidDefinition& operator=(const mwSolidDefinition<T>& rToCopy);
};

template <typename T>
/// This class represents a solid definition visitor to be used for const objects.
class MW_5AXUTIL_API mwSolidDefinitionVisitorGetter
{
public:
	/// Destructor
	virtual ~mwSolidDefinitionVisitorGetter() {}
	/// Visit const mwSolidDefinition< T >
	virtual void Visit(const mwSolidDefinition<T>& visitor) = 0;
	/// Visit const mwRevolvedSolidDefinition< T >
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor) = 0;
	/// Visit const mwExtrudedSolidDefinition<T>
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor) = 0;
	/// Visit const mwMeshSolidDefinition<T>
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor) = 0;
	/// Visit mwTurningSolidDefinition<T>
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor) = 0;

	virtual void Visit(const mwContourTurningSolidDefinition<T>&) MW_VIRTUAL_PURE_DEFINITION(void);

	virtual void Visit(const mwPrimeTurningSolidDefinition<T>&) MW_VIRTUAL_PURE_DEFINITION(void);

	/// Visit mwWireSolidDefinition< T >
	virtual void Visit(const mwWireSolidDefinition<T>& visitor) = 0;

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor) = 0;
};

/// This class represents a solid definition visitor to be used for non-const objects.
template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionVisitorSetter
{
public:
	/// Destructor
	virtual ~mwSolidDefinitionVisitorSetter() {}
	/// Visit mwSolidDefinition< T >
	virtual void Visit(mwSolidDefinition<T>& visitor) const = 0;
	/// Visit mwRevolvedSolidDefinition< T >
	virtual void Visit(mwRevolvedSolidDefinition<T>& visitor) const = 0;
	/// Visit mwExtrudedSolidDefinition<T>
	virtual void Visit(mwExtrudedSolidDefinition<T>& visitor) const = 0;
	/// Visit mwMeshSolidDefinition<T>
	virtual void Visit(mwMeshSolidDefinition<T>& visitor) const = 0;
	/// Visit mwTurningSolidDefinition<T>
	virtual void Visit(mwTurningSolidDefinition<T>& visitor) const = 0;

	virtual void Visit(mwContourTurningSolidDefinition<T>&) const MW_VIRTUAL_PURE_DEFINITION(void);

	virtual void Visit(mwPrimeTurningSolidDefinition<T>&) const MW_VIRTUAL_PURE_DEFINITION(void);
	/// Visit mwWireSolidDefinition< T >
	virtual void Visit(const mwWireSolidDefinition<T>& visitor) const = 0;

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor) const = 0;
};

template <typename T>
mwSolidDefinition<T>::mwSolidDefinition(const Units units): mwMeasurable(units)
{
}

template <typename T>
bool cadcam::mwSolidDefinition<T>::operator==(const mwSolidDefinition& rToCompare) const
{
	if (&rToCompare == this)
		return true;

	return rToCompare.GetUnits() == GetUnits();
}

template <typename T>
cadcam::mwSolidDefinition<T>::mwSolidDefinition(const mwSolidDefinition& rToCopy)
	: mwMeasurable(rToCopy.GetUnits())
{
}

template <typename T>
const mwSolidDefinition<T>& mwSolidDefinition<T>::operator=(const mwSolidDefinition& rToCopy)
{
	if (&rToCopy == this)
		return *this;

	mwMeasurable::operator=(rToCopy);
	return rToCopy;
}
}  // namespace cadcam
#endif  //	MW_MWSOLIDDEFINITION_HPP_
