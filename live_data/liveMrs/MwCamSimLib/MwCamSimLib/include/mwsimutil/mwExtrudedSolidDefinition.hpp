// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWEXTRUDEDSOLIDDEFINITION_HPP_
#define MW_MWEXTRUDEDSOLIDDEFINITION_HPP_
#include "mw2dPolyLine.hpp"
#include "mw3dPolyLine.hpp"
#include "mwSolidDefinition.hpp"

#include <vector>


namespace cadcam
{
template <typename T>
/// @class mwExtrudedSolidDefinition
/// This class represents an extruded solid.
/// You can use it to build cadcam::mwToolPartDefinition objects.
class MW_5AXUTIL_API mwExtrudedSolidDefinition: public mwSolidDefinition<T>
{
public:
	struct mwExtrusionBase;
	struct mwContourExtrusionBase;

	typedef mw2dPolyLine<T> PolyLine;
	typedef typename mwSolidDefinition<T>::Contour Contour;
	typedef typename Contour::Point Point;
	typedef typename mw3dPolyLine<T>::Point Vector3d;
	typedef typename misc::mwAutoPointer<mwExtrudedSolidDefinition<T>> Ptr;
	typedef typename mwSolidDefinition<T>::Units Units;
	typedef typename mwSolidDefinition<T>::ContourPtr ContourPtr;

	explicit mwExtrudedSolidDefinition(const Units units);
	/// Constructor
	///
	/// Constructs an extruded solid definition using the given parameters.
	///	@param extrusionContour is the base contour to be extruded.
	///	@param extrusionVector is the vector used for the extrusion.
	///	@param units are the measurement units.
	MW_DEPRECATED(
		"Deprecated in 2016.08, please use BuildExtrudedSolidDefFrom2dContours or the "
		"mwContourExtrusionBase version which supports contours instead of polylines.")
	mwExtrudedSolidDefinition(
		const mwExtrusionBase& extrusionContour,
		const Vector3d& extrusionVector,
		const Units units);

	/// Constructor
	///
	/// Constructs an extruded solid definition using the given parameters.
	/// @param extrusionContour is the base contour to be extruded.
	/// @param extrusionVector is the vector used for the extrusion.
	/// @param units are the measurement units.
	mwExtrudedSolidDefinition(
		const mwContourExtrusionBase& extrusionContour,
		const Vector3d& extrusionVector,
		const Units units);

	/// Copy constructor
	mwExtrudedSolidDefinition(const mwExtrudedSolidDefinition& rToCopy);

	/// Destructor
	virtual ~mwExtrudedSolidDefinition(){};

	/// Copy operator
	const mwExtrudedSolidDefinition& operator=(const mwExtrudedSolidDefinition& rToCopy);

	void Copy(const mwExtrudedSolidDefinition& rToCopy);

	/// Comparison operator
	///
	///	@param rToCompare is the mwExtrudedSolidDefinition object to be compared with the current
	///object.
	///	@returns <b>True</b> if both tools contain the same parameters,
	///	<b>false</b> otherwise.
	bool operator==(const mwExtrudedSolidDefinition& rToCompare) const;

	/// Constructs an extruded solid definition from the given parameters.
	/// @param contours is the vector of contours to be extruded.
	/// @param tolerance is used for creating polygons from the contours.
	/// @param thickness thickness of extrusion
	/// @param planeZ is the 'height' from which the solid starts.
	/// @param units are the measurement units.
	MW_DEPRECATED(
		"Deprecated in 2021.08, please use BuildExtrudedSolidDefFrom2dContours(.. planePosition, "
		"constructionPlane, units).")
	static const mwExtrudedSolidDefinition BuildExtrudedSolidDefFrom2dContours(
		const std::vector<cadcam::mw2dContour<T>>& contours,
		const T& tolerance,
		const T& thickness,
		const T& planeZ,
		const measures::mwUnitsFactory::Units& units);

	/// Constructs an extruded solid definition from the given parameters.
	/// @param contours is the vector of contours to be extruded.
	/// @param tolerance is used for creating polygons from the contours.
	/// @param extrusionVector is the vector along which the extrusion takes place.
	/// @param planeZ is the 'height' from which the solid starts.
	/// @param units are the measurement units.
	MW_DEPRECATED(
		"Deprecated in 2021.08, please use BuildExtrudedSolidDefFrom2dContours(.. planePosition, "
		"constructionPlane, units).")
	static const mwExtrudedSolidDefinition BuildExtrudedSolidDefFrom2dContours(
		const std::vector<cadcam::mw2dContour<T>>& contours,
		const T& tolerance,
		const Vector3d& extrusionVector,
		const T& planeZ,
		const measures::mwUnitsFactory::Units& units);

	/// Constructs an extruded solid definition from the given parameters.
	/// @param src is the vector of contours to be extruded.
	/// @param tolerance is used for creating polygons from the contours.
	/// @param extrusionVector is the vector along which the extrusion takes place
	/// 	relative construction plane. The thiсkness is defined by extrusionVector.
	/// @param planePosition is the position from which the solid starts.
	/// @param constructionPlane define the plane in which the contours to be extruded.
	/// @param units measurement units.
	static const mwExtrudedSolidDefinition BuildExtrudedSolidDefFrom2dContours(
		const std::vector<cadcam::mw2dContour<T>>& src,
		const T& tolerance,
		const Vector3d& extrusionVector,
		const T& planePosition,
		const Vector3d& constructionPlane,
		const measures::mwUnitsFactory::Units& units);

	/// Returns the extrusion base.
	/// MW_DEPRECATED("Deprecated in 2016.08, please use GetContourExtrusionBase which supports
	/// contours instead of polylines.")
	const mwExtrusionBase& GetExtrusionBase() const;

	/// Sets a new extrusion base.
	///
	///	@param toSet is the mwExtrusionBase object to be set.
	///	@returns void
	/// MW_DEPRECATED("Deprecated in 2016.08, please use SetContourExtrusionBase which supports
	/// contours instead of polylines.")
	void SetExtrusionBase(const mwExtrusionBase& toSet);

	/// Returns the extrusion base.
	const mwContourExtrusionBase& GetContourExtrusionBase() const;

	/// Sets a new extrusion base.
	///
	/// @param toSet is the mwExtrusionBase object to be set.
	/// @returns void
	void SetContourExtrusionBase(const mwContourExtrusionBase& toSet);

	/// Returns the vector used for the extrusion.
	const Vector3d& GetExtrusionVector() const;

	/// Sets the vector to be used for the extrusion.
	///
	///	@param toSet is the vector used for the extrusion.
	///	@returns void
	void SetExtrusionVector(const Vector3d& toSet);

	/// Returns the 3D bounding box of the revolved solid.
	virtual const mw3dBoundingBox<T> GetBoundingBox3d() const;

	/// Implements the visitor pattern.
	///
	/// @param visitor is a reference to the setter visitor.
	virtual void AcceptVisitor(const mwSolidDefinitionVisitorSetter<T>& visitor);

	/// Implements the visitor pattern.
	///
	/// @param visitor is a const reference to the getter visitor.
	virtual void AcceptVisitor(mwSolidDefinitionVisitorGetter<T>& visitor) const;

	/// DEPRECATED in 2016.08, please use mwContourExtrusionBase which supports contours instead of
	/// polylines.
	struct mwExtrusionBase
	{
		/// The polylines that serve as base contours for the extrusion.
		typedef std::vector<PolyLine> contourArray;
		typedef typename contourArray::iterator contourArrayIt;
		typedef typename contourArray::const_iterator constContourArrayIt;

		contourArray contours;
		/// T type value that signifies the third axis position.
		T planePosition;
		Vector3d constructionPlane;

		mwExtrusionBase(): planePosition(0), constructionPlane(0, 1, 0) {}

		mw2dBoundingBox<T> GetBoundingBox() const
		{
			if (contours.empty())
				return mw2dBoundingBox<T>();
			constContourArrayIt it = contours.begin();
			mw2dBoundingBox<T> bbox = it->GetBoundingBox();
			for (; it != contours.end(); ++it)
				bbox += it->GetBoundingBox();
			return bbox;
		}
	};

	struct mwContourExtrusionBase
	{
		/// Base contours for the extrusion.
		typedef std::vector<Contour> contourArray;
		typedef typename contourArray::iterator contourArrayIt;
		typedef typename contourArray::const_iterator constContourArrayIt;

		contourArray contours;
		/// T type value that signifies the third axis position.
		T planePosition;
		Vector3d constructionPlane;

		mwContourExtrusionBase(): planePosition(0), constructionPlane(0, 1, 0) {}

		mw2dBoundingBox<T> GetBoundingBox() const
		{
			if (contours.empty())
				return mw2dBoundingBox<T>();
			constContourArrayIt it = contours.begin();
			mw2dBoundingBox<T> bbox = it->GetBoundingBox();
			for (; it != contours.end(); ++it)
				bbox += it->GetBoundingBox();
			return bbox;
		}
	};

protected:
	/// Scales the extruded solid.
	///
	///	@param units units of measurement
	///	@param scaleFactor of type double
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// The base contour used for the extrusion.
	mwContourExtrusionBase m_extrusionBase;
	// DEPRECATED: To be removed
	mwExtrusionBase m_oldExtrusionBase;
	// DEPRECATED: To be removed
	// T m_tolerance;
	/// The vector used for the extrusion.
	Vector3d m_extrusionVector;
};

template <typename T>
/// This class represents an extruded solid extractor. It ensures that a given mwSolidDefinition
/// derived object is in fact of type mwExtrudedSolidDefinition. If not, an exception is thrown.
class MW_5AXUTIL_API mwExtrudedSolidExtractor: public mwSolidDefinitionVisitorGetter<T>
{
public:
	/// Default constructor
	mwExtrudedSolidExtractor();
	/// Visitor for mwSolidDefinition class objects.
	///
	///	@param visitor for the mwSolidDefinition object.
	virtual void Visit(const mwSolidDefinition<T>& visitor);
	/// Visitor for mwRevolvedSolidDefinition class objects.
	///
	///	@param visitor for the mwRevolvedSolidDefinition object.
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor);
	/// Visitor for mwWireSolidDefinition class objects.
	///
	///	@param visitor for the mwWireSolidDefinition object.
	virtual void Visit(const mwWireSolidDefinition<T>& visitor);
	/// Visitor for mwExtrudedSolidDefinition class objects.
	///
	///	@param visitor for the mwExtrudedSolidDefinition object.
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor);
	/// Visitor for mwMeshSolidDefinition class objects.
	///
	/// @param visitor for the mwMeshSolidDefinition object.
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor);
	/// Visitor for mwTurningSolidDefinition class objects.
	///
	///	@param visitor for the mwTurningSolidDefinition object.
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor);
	/// Visitor for mwContourTurningSolidDefinition class objects.
	///
	/// @param visitor for the mwContourTurningSolidDefinition object.
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor);

	/// Visitor for mwPrimeTurningSolidDefinition class objects.
	///
	/// @param visitor for the mwPrimeTurningSolidDefinition object.
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor);
	/// Returns the mwExtrudedSolidDefinition "certified" object.
	const mwExtrudedSolidDefinition<T>& GetSolid() const;

private:
	/// The member mwExtrudedSolidDefinition.
	/// This is valid only when a mwExtrudedSolidDefinition was visited.
	mwExtrudedSolidDefinition<T> m_extrudedSolid;
};
}  // namespace cadcam
#endif  //	MW_MWEXTRUDEDSOLIDDEFINITION_HPP_
