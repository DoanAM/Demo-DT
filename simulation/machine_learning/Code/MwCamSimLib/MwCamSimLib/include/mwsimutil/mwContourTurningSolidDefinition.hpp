// (C) 2014-2021 by ModuleWorks GmbH
// Owner: 3Axis

/*ToDoDoc: Do we need any general introduction/description for this hpp file?*/

#ifndef MW_MWCONTOURTURNINGSOLIDDEFINITION_HPP_
#define MW_MWCONTOURTURNINGSOLIDDEFINITION_HPP_
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTypedExtrudedSolidDefinition.hpp"

namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwContourTurningSolidDefinition: public mwTypedExtrudedSolidDefinition<T>
{
public:
	typedef typename misc::mwAutoPointer<mwContourTurningSolidDefinition<T>> Ptr;

	typedef typename mwTypedExtrudedSolidDefinition<T>::Units Units;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Contour Contour;
	typedef typename mwTypedExtrudedSolidDefinition<T>::ContourPtr ContourPtr;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Shank Shank;
	typedef typename mwTypedExtrudedSolidDefinition<T>::Hand Hand;

	explicit mwContourTurningSolidDefinition(const Units units);

	mwContourTurningSolidDefinition(
		const Contour& src, const T height, const Hand hand, const Shank shank, const Units units);

	bool operator==(const mwContourTurningSolidDefinition& rToCompare) const;

	/// Returns the contour solid.
	const Contour GetContour() const;

	/// Returns the 3D bounding box of the revolved solid.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// Implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// Implements the visitor pattern
	///
	/// @param visitor is a const reference to the getter visitor.
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

private:
	Contour m_contour;

	virtual void Scale(const Units units, const double& scaleFactor);
};

/// This class represents an extruded solid extractor.
///
/// I ensures that a given mwSolidDefinition derived object is in fact of type
/// mwTurningSolidDefinition. If not, an exception is thrown.
template <typename T>
class MW_5AXUTIL_API mwContourTurningSolidDefinitionExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	mwContourTurningSolidDefinitionExtractor();

	virtual void Visit(const mwSolidDefinition<T>& visitor);
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);
	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

	const mwContourTurningSolidDefinition<T>& GetSolid() const;

private:
	mwContourTurningSolidDefinition<T> m_contourTurningSolid;
};
}  // namespace cadcam
#endif  //	MW_MWCONTOURTURNINGSOLIDDEFINITION_HPP_
