// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWREVOLVEDSOLIDDEFINITION_HPP_
#define MW_MWREVOLVEDSOLIDDEFINITION_HPP_
#include "mw2dContour.hpp"
#include "mw2dGeometry.hpp"
#include "mw2dPolyLine.hpp"
#include "mw3dGeometry.hpp"
#include "mwAutoPointer.hpp"
#include "mwSolidDefinition.hpp"


namespace cadcam
{
template <typename T>
class MW_5AXUTIL_API mwRevolvedSolidDefinition: public mwSolidDefinition<T>
{
public:
	typedef mw2dPolyLine<T> PolyLine;
	typedef mw2dContour<T> Contour2d;
	typedef typename misc::mwAutoPointer<mwRevolvedSolidDefinition<T>> Ptr;
	typedef typename mwSolidDefinition<T>::Units Units;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	mwRevolvedSolidDefinition(const Units units);

	/// Creates an exact copy of the revolved solid definition.
	/// @param rToCopy is the definition to be copied.
	mwRevolvedSolidDefinition(const mwRevolvedSolidDefinition& rToCopy);

	/// Builds a mwRevolvedSolidDefinition using the given parameters.
	/// @param rToCopy is the profile.
	/// @param units are the measurement units.
	mwRevolvedSolidDefinition(const PolyLine& rToCopy, const Units units);

	/// Builds a mwRevolvedSolidDefinition using the given parameters.
	/// @param rToCopy is the profile.
	/// @param units are the measurement units.
	mwRevolvedSolidDefinition(const Contour2d& rToCopy, const Units units);

	/// Assigns one object to another.
	/// @param rToCopy is the object from which the information is copied.
	/// @return A const reference to the mwRevolvedSolidDefinition object.
	const mwRevolvedSolidDefinition& operator=(const mwRevolvedSolidDefinition& rToCopy);

	/// Comparison operator
	///
	/// Use this operator to compare the parameters of two definitions.
	///	@param rToCompare is the mwRevolvedSolidDefinition that will be compared with the current
	///definition.
	///	@return <b>True</b> if both definitions contain the same parameters,
	///	<b>false</b> otherwise.
	bool operator==(const mwRevolvedSolidDefinition<T>& rToCompare) const;

	/// Sets a PolyLine object as the solid's profile.
	///
	///	@param rToCopy is the PolyLine object that represents the profile.
	virtual void SetProfile(const PolyLine& rToCopy);

	/// Gets the profile as a PolyLine object.
	virtual const PolyLine GetProfile() const;

	/// Gets the profile as a PolyLine object
	///
	///	@param tolerance chordal deviation to be used for profile polygonization
	virtual const PolyLine GetProfile(const double tolerance) const;

	/// Sets a Contour2d object as the solid's profile.
	///
	///	@param rToCopy is the Contour2d object that represents the profile.
	virtual void SetProfileAsContour(const Contour2d& rToCopy);

	/// Gets the profile as a Contour2d object.
	virtual const Contour2d& GetProfileAsContour() const;

	/// Gets the solid's radius.
	virtual const T GetRadius() const;

	/// Returns the 3d bounding box of the revolved solid.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// This function is used in the visitor scheme
	///
	///	@param visitor of type mwSolidDefinitionVisitorSetter<T>
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// This function is used in the visitor scheme - accepts const visitors
	///
	///	@param visitor of type mwSolidDefinitionVisitorGetter<T>
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

private:
	/// Data members
	Contour2d m_Profile;

	/// Adds a PolyLine object to the member contour.
	///
	///	@param newProfile is the PolyLine object to be added.
	void SetPolyLine(const PolyLine& newProfile);

	void SetContour(const Contour2d& newProfile);

	/// Gets the solid's lowest height.
	virtual const T GetLowestPointHeight() const;

protected:
	/// Scales the solid
	///
	///	@param units are the measurement units.
	///	@param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);
};

template <typename T>
/// This class represents a revolved solid extractor. It ensures that a given mwSolidDefinition
/// derived object is in fact of type mwRevolvedSolidDefinition. If not, an exception is thrown.
class MW_5AXUTIL_API mwRevolvedSolidExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	/// Default constructor
	mwRevolvedSolidExtractor();

	/// Visitor for mwSolidDefinition class objects.
	///
	/// @param visitor for the mwSolidDefinition object.
	virtual void Visit(const mwSolidDefinition<T>& visitor);

	/// Visitor for mwRevolvedSolidDefinition class objects.
	///
	/// @param visitor for the mwRevolvedSolidDefinition object.
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);

	/// Visitor for mwExtrudedSolidDefinition class objects.
	///
	/// @param visitor for the mwExtrudedSolidDefinition object.
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);

	/// Visitor for mwMeshSolidDefinition class objects.
	///
	/// @param visitor for the mwMeshSolidDefinition object.
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);

	/// Visitor for mwTurningSolidDefinition class objects.
	///
	/// @param visitor for the mwTurningSolidDefinition object.
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);

	/// Visitor for mwContourTurningSolidDefinition class objects.
	///
	/// @param visitor for the mwContourTurningSolidDefinition object.
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);

	/// Visitor for mwPrimeTurningSolidDefinition class objects.
	///
	/// @param visitor for the mwPrimeTurningSolidDefinition object.
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);

	/// Visitor for mwWireSolidDefinition class objects.
	///
	/// @param visitor for the mwWireSolidDefinition object.
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);
	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor);

	/// Returns the mwRevolvedSolidDefinition "certified" object.
	const mwRevolvedSolidDefinition<T>& GetSolid() const;

private:
	/// The member mwRevolvedSolidDefinition.
	/// This is valid only when a mwRevolvedSolidDefinition was visited.
	mwRevolvedSolidDefinition<T> m_revolvedSolid;
};
}  // namespace cadcam
#endif  //	MW_MWREVOLVEDSOLIDDEFINITION_HPP_
