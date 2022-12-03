// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCHAMFERMILL_HPP_
#define MW_MWCHAMFERMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwChamferMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwChamferMill& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a chamfer mill tool.
class MW_5AXUTIL_API mwChamferMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwChamferMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwChamferMill(const Units units = Units::METRIC);

	/// Destructor
	~mwChamferMill();

	/// Constructor
	///
	/// Constructs a chamfer mill tool using the given parameters.If the corner radius type is none
	/// or full,
	///   the passed newCornerRad value is ignored and the corner radius is set to 0.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///           @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor diameter.
	///   @param newCornerRad is the corner radius of the tool.
	///   @param newTaperAngle is the taper angle of the tool.
	///   @param newOutsideDiameter is the outside diameter of the tool.
	///   @param newCornerRadType is the corner radius type of the tool.
	///   @param units are the units.
	mwChamferMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newTaperAngle,
		const double& newOutsideDiameter,
		const cornerRadiusType& newCornerRadType,
		const Units units);

	/// Constructor
	///
	/// Constructs a chamfer mill tool using the given parameters.If the corner radius type is none
	/// or full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newOutsideDiameter is the outside diameter of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShoulderDefinition is the new shoulder definition.
	/// @param units are the units.
	mwChamferMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newTaperAngle,
		const double& newOutsideDiameter,
		const cornerRadiusType& newCornerRadType,
		const mwShoulderDefinitionExtender& newShoulderDefinition,
		const Units units);

	/// Constructs an Chamfer mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newOutsideDiameter is the outside diameter of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwChamferMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newTaperAngle,
		const double& newOutsideDiameter,
		const cornerRadiusType& newCornerRadType,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a given tool.
	///   @param toCopy is the tool that will be copied.
	mwChamferMill(const mwChamferMill& toCopy);
	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	///  @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Gets the corner radius type.
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Gets the taper angle.
	///
	///  @returns Taper angle.
	const double GetTaperAngle() const;

	/// Gets the outside diameter
	///
	///  @returns The outside diameter of the tool.
	const double GetOutsideDiameter() const;

	//########################## Operators ########################################

	/// Assignment operator for assigning one tool to another.
	///
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwChamferMill& operator=(const mwChamferMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwChamferMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwChamferMill& toCompare);

	/// Implements the visitor pattern
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;

protected:
	virtual mw3dBoundingBox<double> GetCuttingPartBoundingBox() const;


	/// Checks the validity of the taper/shoulder intersection.
	///
	///   @param newTapeAngle is the taper angle.
	///   @param newDiameter is the tool diameter.
	///   @param newOutsideDiameter is the outside diameter.
	///   @param newShoulderLen is the shoulder length.
	///   @throws mwException if the taper does not intersect the shoulder.
	void ValidateIntersection(
		const double& newTapeAngle,
		const double& newDiameter,
		const double& newOutsideDiameter,
		const double& newShoulderLen) const;

	/// Checks the validity of the taper angle. A valid taper angle is  >=0.1 and <=89.0
	///
	///   @param newTaperAngle is the taper angle.
	///   @throws mwException if the taper angle is not between 0.1 and 89.0
	void ValidateTaperAngle(const double& newTaperAngle) const;

	/// Validates the diameter against the outside diameter.
	///
	///	@param newDia is the diameter.
	///	@param newOutsideDia is the outside diameter.
	void ValidateDiameterVSOutsideDiameter(const double& newDia, const double& newOutsideDia) const;

	/// Check the validity of the corner radius against the taper and diameter.
	///
	///	@param newCornerRadius is the corner radius.
	///	@param newDia is the diameter.
	///	@param newTaperAngle is the taper angle.
	void ValidateCornerRadiusVSDiaAndTaperAngle(
		const double& newCornerRadius, const double& newDia, const double& newTaperAngle) const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// if the type is corner, it leaves the radius unchanged;
	///	if the type is none or full, it changes the radius to 0.0;
	///	if the type is any other value, it throws an exception.
	///	@param newCornerRadiusType is the corner radius type.
	///	@param CornerRadius is the corner radius.
	///	@param newDiamater is the diameter.
	///	@param newTaperAngle is the taper angle.
	///	@return The new corner radius.
	///
	/// @throws mwException if the corner radius type is any other value then none, corner or full.
	const double ComputeCornerRadius(
		const cornerRadiusType newCornerRadiusType,
		const double& CornerRadius,
		const double& newDiamater,
		const double& newTaperAngle) const;

	/// Validates the outside diameter. The outside diameter is valid if it is > 0.
	///
	/// @param newDia is the diameter.
	/// @param newOutsideDia is the outside diameter.
	/// @param newCornerRadius is the corner radius.
	/// @param newTaperAngle is the taper angle.
	/// @throws mwException if the outside diameter is <= 0.
	void ValidateOutsideDiameter(
		const double& newDia,
		const double& newOutsideDia,
		const double& newCornerRadius,
		const double& newTaperAngle) const;

	/// Checks the validity of the corner radius. A valid corner radius is >=0 for all types and > 0
	/// for the "corner" type.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	void ValidateCornerRadiusTypeVSDiameter(
		const cornerRadiusType newCornerRadiusType, const double& newDiamater);


	/// Scale the tool (its measurable components).
	///
	///	@param units are the measurement units.
	///	@param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwChamferMill
	void Copy(const mwChamferMill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newDiameter is the diameter of the tool.
	///	@param newShoulderLenn is the shoulder length of the tool.
	///	@param newCornerRad is the new corner radius of the tool.
	///	@param newTaperAngle is the new taper angle of the tool.
	///	@param newOutsideDiameter is the new outside diameter of the tool.
	///	@param newCornerRadiusType is the new corner radius type of the tool.
	void InternalConstructor(
		const double& newDiameter,
		const double& newShoulderLen,
		const double& newCornerRad,
		const double& newTaperAngle,
		const double& newOutsideDiameter,
		const cornerRadiusType& newCornerRadiusType);

	/// Calculate the tool's cone height from other tool elements.
	///
	///	@param toolDiameter is the tool's diameter.
	///	@param outsideDiameter is the tool's outside diameter.
	///	@param taperAngle is the tool's taper angle.
	///	@param fluteLen is the tool's flute length.
	///	@return tool's cone height.
	double CalcConeHeightGivingToolElements(
		const double& toolDiameter,
		const double& outsideDiameter,
		const double& taperAngle,
		const double& fluteLen) const;
	/// Corner radius
	double mCornerRadius;
	/// Taper angle
	double mTaperAngle;
	/// Corner radius type
	cornerRadiusType mCornerRadiusType;
	/// Outside diameter
	double mOutsideDiameter;
};
}  // namespace cadcam
#endif  //	MW_MWCHAMFERMILL_HPP_
