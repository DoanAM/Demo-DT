// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWFACEMILL_HPP_
#define MW_MWFACEMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwFaceMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwFaceMill& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a face mill tool.
class MW_5AXUTIL_API mwFaceMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwFaceMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwFaceMill(const Units units = Units::METRIC);

	/// Destructor
	~mwFaceMill();

	/// Constructor
	///
	/// Constructs a face mill tool using the given parameters.If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newOutsideDia is the outside diameter of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param units are the units.
	mwFaceMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newOutsideDia,
		const double& newTaperAngle,
		const cornerRadiusType& newCornerRadType,
		const Units units);

	/// Constructor
	///
	/// Constructs a face mill tool using the given parameters.If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newOutsideDia is the outside diameter of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the units.
	mwFaceMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newOutsideDia,
		const double& newTaperAngle,
		const cornerRadiusType& newCornerRadType,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool.
	/// @param toCopy is the tool that will be copied.
	mwFaceMill(const mwFaceMill& toCopy);


	//#########################  Gets  ############################################

	/// Get the corner radius.
	///
	///  @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Gets the outside diameter of the tool.
	///
	///  @returns The outside diameter of the tool.
	const double& GetOutsideDiameter() const;

	/// Gets the taper angle of the tool.
	///
	///  @returns The taper angle of the tool.
	const double& GetTaperAngle() const;

	/// Gets the corner radius type
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator.
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwFaceMill& operator=(const mwFaceMill& toCopy);

	/// Equality operator.
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwFaceMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwFaceMill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the taper/shoulder intersection. It is valid when the taper
	/// intersects the shoulder.
	///
	///   @param newCornerRadius is the corner radius.
	///   @param newTaperAngle is the taper angle.
	///   @param newDiameter is the tool diameter.
	///   @param newOutsideDiameter is the outside diameter.
	///   @param newShoulderLen is the shoulder length.
	///   @throws mwException if the taper does not intersect the shoulder.
	void ValidateIntersection(
		const double& newCornerRadius,
		const double& newTaperAngle,
		const double& newDiameter,
		const double& newOutsideDiameter,
		const double& newShoulderLen) const;

	/// Checks the validity of the taper angle. A valid taper angle is >=0.1 and <=89.0
	///
	///   @param newTaperAngle is the taper angle.
	///   @throws mwException if the taper angle is not between 0. and 89.0
	void ValidateTaperAngle(const double& newTaperAngle) const;

	/// Checks the validity of the corner radius. A valid corner radius is >=0 for all types and > 0
	/// for the "corner" type.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// if the type is corner, it leaves the radius unchanged;
	///	if the type is none or full it changes the radius to 0.0;
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value then none, corner or
	///   full.
	void ComputeCornerRadius();

protected:
	/// Scales a tool (its measurable units).
	///
	///	@param units are the measurement units.
	///	@param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwFaceMill
	void Copy(const mwFaceMill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(
		const double& newDiameter,
		const double& newShoulderLen,
		const double& newCornerRad,
		const double& newOutsideDia,
		const double& newTaperAngle,
		const cornerRadiusType& newCRType);


	/// Corner radius
	double mCornerRadius;
	/// Outside diameter
	double mOutsideDiameter;
	/// Taper angle
	double mTaperAngle;
	/// Corner radius type
	cornerRadiusType mCornerRadiusType;
};
}  // namespace cadcam
#endif  //	MW_MWFACEMILL_HPP_
