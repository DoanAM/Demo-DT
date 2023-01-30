// (C) 2009-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWMESHSOLIDDEFINITION_HPP_
#define MW_MWMESHSOLIDDEFINITION_HPP_
#include "mw2dGeometry.hpp"
#include "mwAutoPointer.hpp"
#include "mwExtrudedSolidDefinition.hpp"
#include "mwMesh.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwSolidDefinition.hpp"
#include "mwTurningSolidDefinition.hpp"


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwMeshSolidDefinition: public mwSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwMeshSolidDefinition<T>> Ptr;
	typedef cadcam::mwTMesh<T> meshData;
	typedef misc::mwAutoPointer<meshData> meshDataPtr;
	typedef typename mwSolidDefinition<T>::Units Units;
	typedef typename mwSolidDefinition<T>::Contour Contour;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	/// Constructor
	mwMeshSolidDefinition(const meshData& toSet);
	/// if you want to share same data between different solids, null pointer not accepted, but you
	/// may pass empty mesh
	mwMeshSolidDefinition(const meshDataPtr& toSet);

	/// Constructor
	mwMeshSolidDefinition(const measures::mwUnitsFactory::Units units);

	/// Constructor
	MW_DEPRECATED("Deprecated since 2017.08. use the constructor with one parameter only")
	mwMeshSolidDefinition(const meshData& toSet, const Contour&);
	MW_DEPRECATED("Deprecated since 2017.08. use the constructor with one parameter only")
	mwMeshSolidDefinition(const meshDataPtr& toSet, const Contour&);

	/// Copy constructor
	///
	/// @param rToCopy  of type mwMeshSolidDefinition
	mwMeshSolidDefinition(const mwMeshSolidDefinition& rToCopy);

	/// Assignment operator
	///
	/// @param rToCopy to assign
	/// @return const reference to mwMeshSolidDefinition object
	const mwMeshSolidDefinition& operator=(const mwMeshSolidDefinition& rToCopy);

	/// Comparison operator
	///
	/// @param rToCompare  mwMeshSolidDefinition to compare with
	/// @return <b>true</b> if both definitions contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwMeshSolidDefinition<T>& rToCompare) const;

	/// Returns the 3d bounding box of the revolved solid
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// This function is used in the visitor scheme
	///
	/// @param visitor of type mwSolidDefinitionVisitorSetter<T>
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// This function is used in the visitor scheme - accepts const visitors
	///
	/// @param visitor  of type mwSolidDefinitionVisitorGetter<T>
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

	const meshData& GetMesh() const;

	void SetMesh(const meshData& toSet);

	const meshDataPtr& GetMeshPtr() const;
	/// if you want to share same data between different solids, null pointer not accepted, but you
	/// may pass empty mesh
	void SetMeshPtr(const meshDataPtr& toSet);

private:
	/// Data members
	meshDataPtr m_mesh;

protected:
	/// Scales the solid
	///
	/// @param units  units of measurement
	/// @param scaleFactor scale factor
	virtual void Scale(const Units units, const double& scaleFactor);
};


template <typename T>
/// This class represents an revolved solid extractor. Basically this assures that a given
/// mwSolidDefinition derived object is in fact of type mwMeshSolidDefinition. If not, an exception
/// is thrown.
class MW_5AXUTIL_API mwMeshSolidExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	/// Default constructor
	mwMeshSolidExtractor();

	/// Visitor for mwSolidDefinition class objects
	///
	/// @param visitor mwSolidDefinition object
	virtual void Visit(const mwSolidDefinition<T>& visitor);

	/// Visitor for mwRevolvedSolidDefinition class objects
	///
	/// @param visitor mwRevolvedSolidDefinition object
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);

	/// Visitor for mwExtrudedSolidDefinition class objects
	///
	/// @param visitor mwExtrudedSolidDefinition object
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);

	/// Visitor for mwWireSolidDefinition class objects
	///
	/// @param visitor mwWireSolidDefinition object
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);

	/// Visitor for mwMeshSolidDefinition class objects
	///
	/// @param visitor mwMeshSolidDefinition object
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);

	/// Visitor for mwTurningSolidDefinition class objects
	///
	/// @param visitor mwTurningSolidDefinition object
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);

	/// Visitor for mwContourTurningSolidDefinition class objects
	///
	/// @param visitor mwContourTurningSolidDefinition object
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);

	/// Visitor for mwPrimeTurningSolidDefinition class objects
	///
	/// @param visitor mwPrimeTurningSolidDefinition object
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

	/// Returns the mwMeshSolidDefinition "certified" object
	const mwMeshSolidDefinition<T>& GetSolid() const;

private:
	/// The member mwMeshSolidDefinition.
	/// This is valid indeed only when a mwMeshSolidDefinition was visited.
	mwMeshSolidDefinition<T> m_meshSolid;
};


template <typename T>
class MW_5AXUTIL_API mwMeshSolidDefinitionGetMesh: public mwSolidDefinitionVisitorGetter<T>
{
public:
	mwMeshSolidDefinitionGetMesh();
	mwTMesh<T> GetMesh(const mwSolidDefinition<T>& sd);

	virtual void Visit(const mwSolidDefinition<T>& visitor)
	{
		visitor;
		// throw misc::mwException(0, _T("mwSolidDefinition object does not have a mesh"));
	};

	/// Visit const mwRevolvedSolidDefinition< T >
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor)
	{
		visitor;
		// throw misc::mwException(0, _T("mwRevolvedSolidDefinition object does not have a mesh"));
	};

	/// Visit const mwExtrudedSolidDefinition<T>
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor)
	{
		visitor;
		// throw misc::mwException(0, _T("mwExtrudedSolidDefinition object does not have a mesh"));
	};

	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);
	virtual void Visit(const mwTurningSolidDefinition<T>&);
	virtual void Visit(const mwThreadTapSolidDefinition<T>&) {}

	mwTMesh<T> my_mesh;
};
}  // namespace cadcam
#endif  //	MW_MWMESHSOLIDDEFINITION_HPP_
