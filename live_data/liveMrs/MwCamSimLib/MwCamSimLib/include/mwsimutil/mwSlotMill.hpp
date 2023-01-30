// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWSLOTMILL_HPP_
#define MW_MWSLOTMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwSlotMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwSlotMill& toDump);

namespace cadcam
{
/// This class represents a slot mill tool.
class MW_5AXUTIL_API mwSlotMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwSlotMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################

	/// Default constructor
	explicit mwSlotMill(const Units units = Units::METRIC);

	/// Destructor
	~mwSlotMill();

	/// Constructor
	///
	/// Constructs a slot mill tool using the given parameters. If the corner radius type is none or
	/// full,
	///   the passed cornerRadius value is ignored and the corner radius is set to 0.
	///   @param diameter is the diameter of the constructed tool.
	///   @param holder is the holder.
	///   @param fluteLength is the flute length.
	///   @param arbor is the arbor.
	///   @param cornerRadius is the corner radius of the tool.
	///	This corner radius will be set both at lower and upper part of the flute
	///   @param cornerRadType is the corner radius type of the tool.
	///   @param units are the units.
	mwSlotMill(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const double& cornerRadius,
		const cornerRadiusType& cornerRadType,
		const Units units);

	/// Constructor
	///
	/// Constructs a slot mill tool using the given parameters. If the corner radius type is none or
	/// full,
	///   the passed cornerRadius value is ignored and the corner radius is set to 0.
	///   @param diameter is the diameter of the constructed tool.
	///   @param holder is the new holder.
	///   @param fluteLength is the flute length.
	///   @param arbor is the arbor.
	///   @param cornerRadius is the corner radius of the tool.
	///   This corner radius will be set both at lower and upper part of the flute
	///   @param cornerRadType is the corner radius type of the tool.
	///   @param shoulderLength is the tool shoulder length.
	///   @param shoulderDefinition is the tool shoulder definition.
	///   @param units are the units.
	mwSlotMill(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const double& cornerRadius,
		const cornerRadiusType& cornerRadType,
		const double& shoulderLength,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs an slot mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param cornerRadius is the corner radius of the tool.
	/// This corner radius will be set both at lower and upper part of the flute
	/// @param cornerRadType is the corner radius type of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwSlotMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& cornerRadius,
		const cornerRadiusType& cornerRadType,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Constructor
	///
	/// Constructs a slot mill tool using the given parameters.
	///   It allows user to set distinct corner radii at lower/upper parts of the flute.
	///   If the corner radius type is none or full,the passed lowerCornerRadius/upperCornerRadius
	///   values are ignored and the corner radius is automatically computed.
	///	@param diameter is the diameter of the constructed tool.
	///	@param holder is the holder definition.
	///	@param fluteLen is the flute length of the tool.
	///	@param arbor is the arbor definition.
	///	@param lowerCornerRadius is the corner radius at the lower part of the flute
	///	@param upperCornerRadius is the corner radius at the upper part of the flute
	///	@param cornerRadType is the corner radius type of the tool.
	///	@param units are the measurement units in which the tool is constructed.
	mwSlotMill(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLen,
		const ArborDefinition& arbor,
		const double& lowerCornerRadius,
		const double& upperCornerRadius,
		const cornerRadiusType& cornerRadType,
		const Units units);

	/// Constructor
	///
	/// Constructs a slot mill tool using the given parameters. If the corner radius type is none or
	/// full, the passed cornerRadius value is ignored and the corner radius is set to 0. It allows
	/// user to set distinct corner radii at lower/upper parts of the flute.
	///	@param diameter is the diameter of the constructed tool.
	///	@param holder is the new holder.
	///	@param fluteLength is the flute length.
	///	@param arbor is the arbor.
	///	@param lowerCornerRadius is the corner radius at the lower part of the flute
	///	@param upperCornerRadius is the corner radius at the upper part of the flute
	///	@param cornerRadType is the corner radius type of the tool.
	///	@param shoulderLength is the tool shoulder length.
	///	@param shoulderDefinition is the tool shoulder definition.
	///	@param units are the units.
	mwSlotMill(
		const double& diameter,
		const HolderDefinition& holder,
		const double& fluteLength,
		const ArborDefinition& arbor,
		const double& lowerCornerRadius,
		const double& upperCornerRadius,
		const cornerRadiusType& cornerRadType,
		const double& shoulderLength,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs an slot mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param lowerCornerRadius is the corner radius at the lower part of the flute
	/// @param upperCornerRadius is the corner radius at the upper part of the flute
	/// @param cornerRadType is the corner radius type of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwSlotMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& lowerCornerRadius,
		const double& upperCornerRadius,
		const cornerRadiusType& cornerRadType,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Creates an exact copy of a given tool.
	///
	/// @param toCopy is the tool to be copied.
	mwSlotMill(const mwSlotMill& toCopy);

	//#########################  Gets  ############################################
	/// Get the corner radius at the lower part of the flute
	///
	/// @returns corner radius at the lower part of the flute.
	const double& GetCornerRadius() const;

	/// Get the corner radius at the upper part of the flute
	///
	///	@returns corner radius at the upper part of the flute.
	const double& GetUpperCornerRadius() const;

	/// Get the corner radius type.
	///
	/// @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwSlotMill& operator=(const mwSlotMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters
	///  <b>False</b> otherwise
	bool operator==(const mwSlotMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>True</b> otherwise
	bool operator!=(const mwSlotMill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the flute and corner radius.
	///
	/// This function is used for the case when both lower/upper corner radii are identical as
	/// values
	///  Checked parameters are valid when the flute length is at least twice the corner radius.
	///   @param fluteLengthgth is the flute length.
	///   @param cornerRadius is the corner radius.
	///   @throws mwException if the flute length is less than twice the corner radius.
	void ValidateFluteLengthVSCornerRadius(
		const double& fluteLength, const double& cornerRadius) const;

	/// Checks the validity of the flute and lower/upper corner radii
	///
	/// This function is used for the case when lower/upper corner radii have different values
	///	@param fluteLength is the flute length.
	///	@param lowerCornerRadius is the corner radius at lower part of the flute
	///	@param upperCornerRadius is the corner radius at upper part of the flute
	///	@throws mwException if the validation fails
	void ValidateFluteLengthVSCornerRadii(
		const double& fluteLength,
		const double& lowerCornerRadius,
		const double& upperCornerRadius) const;


	/// Checks whether the relationship between the arbor, diameter and corner radius is valid.
	///
	/// Reserved for future checks, it does not currently validate anything.
	///	@param arbor is the arbor.
	///	@param diameter is the diameter.
	///	@param cornerRadiusius is the corner radius.
	static void ArborValidationVSDiameterAndCorner(
		const ArborDefinition& arbor, const double& diameter, const double& cornerRadius);

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// If the type is corner, it leaves the radius unchanged;
	///	if the type is none it changes the radius to 0.0;
	///	if the type is full it changes the radius to fluteLen/2
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value then none, corner or
	///   full.
	void ComputeCornerRadius();

	/// Checks the validity of the corner radius.
	///
	/// The corner radius is valid when it is greater or equal 0
	///	@param cornerRadius is the corner radius.
	///	@throws mwException if the validation fails.
	void ValidateCornerRadius(const double& cornerRadius) const;

	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;


protected:
	/// Scale the tool.
	/// @param units new units
	/// @param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data from mwSlotMill.
	void Copy(const mwSlotMill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(
		const double& diameter,
		const double& fluteLen,
		const double& lowerCornerRadius,
		const double& upperCornerRadius,
		const cornerRadiusType& cornerRadType);


	/// corner radius
	double m_lowerCornerRadius;  // corner radius at lower part of the flute
	double m_upperCornerRadius;  // corner radius at upper part of the flute

	/// diameter
	cornerRadiusType m_cornerRadiusType;
};
}  // namespace cadcam
#endif  //	MW_MWSLOTMILL_HPP_
