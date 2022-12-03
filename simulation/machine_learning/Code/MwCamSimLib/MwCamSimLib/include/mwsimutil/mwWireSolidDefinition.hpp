// (C) 2015-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWWIRESOLIDDEFINITION_HPP_
#define MW_MWWIRESOLIDDEFINITION_HPP_
#include "mw2dContour.hpp"
#include "mw2dGeometry.hpp"
#include "mw2dPolyLine.hpp"
#include "mw3dGeometry.hpp"
#include "mwAutoPointer.hpp"
#include "mwSolidDefinition.hpp"


namespace cadcam
{
/// @class mwWireSolidDefinition
/// Represents solid definition for wire tool
template <typename T>
class MW_5AXUTIL_API mwWireSolidDefinition: public mwSolidDefinition<T>
{
public:
	typedef mw2dPolyLine<T> PolyLine;
	typedef mw2dContour<T> Contour2d;
	typedef typename misc::mwAutoPointer<mwWireSolidDefinition<T>> Ptr;
	typedef typename mwSolidDefinition<T>::Units Units;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	/// Constructor
	mwWireSolidDefinition(
		const T wireDiameter,
		const T wireLength,
		const Units units,
		const bool infiniteLength = true);

	/// Comparison operator.
	///
	/// Use this operator to compare the parameters of two objects.
	///	@param rToCompare is the mwWireSolidDefinition to be compared with the current definition.
	///	@return <b>True</b> if both definitions contain the same parameters,
	///	<b>false</b> otherwise.
	bool operator==(const mwWireSolidDefinition<T>& rToCompare) const;

	inline const T GetWireDiameter() const { return m_wireDiameter; }
	inline const T GetWireLength() const { return m_wireLength; }
	inline const bool HasInfiniteLength() const { return m_hasInfiniteLength; }

	/// Returns the 3D bounding box of the revolved solid.
	///
	///	@return infinite box for an infinite tool.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// This function is used in the visitor scheme
	///
	///	@param visitor of type mwSolidDefinitionVisitorSetter<T>
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// This function is used in the visitor scheme. It accepts const visitors.
	///
	/// @param visitor of type mwSolidDefinitionVisitorGetter<T>
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

private:
	/// Data members
	T m_wireDiameter;
	T m_wireLength;
	bool m_hasInfiniteLength;

protected:
	/// Scales the solid.
	///
	///	@param units are the measurement units of the solid.
	///	@param scaleFactor is the scaling factor by which the solid is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);
};

template <typename T>
/// This class represents a revolved solid extractor. It ensures that a given mwSolidDefinition
/// derived object is in fact of type mwWireSolidDefinition. If not, an exception is thrown.
class mwWireSolidExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	/// Default constructor
	mwWireSolidExtractor();

	/// Visitor for mwSolidDefinition class objects.
	///
	/// @param visitor mwSolidDefinition object.
	virtual void Visit(const mwSolidDefinition<T>& visitor);

	/// Visitor for mwRevolvedSolidDefinition class objects.
	///
	/// @param visitor mwRevolvedSolidDefinition object.
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);

	/// Visitor for mwWireSolidDefinition class objects.
	///
	/// @param visitor mwWireSolidDefinition object.
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);

	/// Visitor for mwExtrudedSolidDefinition class objects.
	///
	/// @param visitor mwExtrudedSolidDefinition object.
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);

	/// Visitor for mwMeshSolidDefinition class objects.
	///
	/// @param visitor mwMeshSolidDefinition object.
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);

	/// Visitor for mwTurningSolidDefinition class objects.
	///
	/// @param visitor mwTurningSolidDefinition object.
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);

	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);

	/// Returns the mwWireSolidDefinition "certified" object.
	const mwWireSolidDefinition<T>& GetSolid() const;

private:
	/// The member mwWireSolidDefinition.
	/// This is valid only when a mwWireSolidDefinition has been visited.
	mwWireSolidDefinition<T> m_wireSolid;
};
}  // namespace cadcam
#endif  //	MW_MWWIRESOLIDDEFINITION_HPP_
