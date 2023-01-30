// (C) 2017-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELTAPERMILL_HPP_
#define MW_MWBARRELTAPERMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwBarrelTaperMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelTaperMill& toDump);

namespace cadcam
{
/// This class represents the taper barrel mill tool
class MW_5AXUTIL_API mwBarrelTaperMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelTaperMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwBarrelTaperMill(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a taper barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter/shaft of the constructed tool.
	/// @param newTaperAngle is the taper angle of the constructed tool.
	/// @param newLowerRadius is the centered-corner radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newUpperRadius is the upper-corner radius of the constructed tool.
	/// @param flatnessDiameter is the flatness diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the entire length of this tool's flute.
	/// @param newArbor is the arbor.
	/// @param units are the measurement units.
	mwBarrelTaperMill(
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& flatnessDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);


	/// Constructor with parameters and user given shoulder definition extender
	///
	/// Constructs a taper barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter/shaft of the constructed tool.
	/// @param newTaperAngle is the taper angle of the constructed tool.
	/// @param newLowerRadius is the centered-corner radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newUpperRadius is the upper-corner radius of the constructed tool.
	/// @param flatnessDiameter is the flatness diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the entire length of this tool's flute.
	/// @param newArbor is the arbor.
	/// @param shoulderDefinition is the shoulder definition extender.
	/// @param units are the measurement units.
	mwBarrelTaperMill(
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& flatnessDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs a taper barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter/shaft of the constructed tool.
	/// @param newTaperAngle is the taper angle of the constructed tool.
	/// @param newLowerRadius is the centered-corner radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newUpperRadius is the upper-corner radius of the constructed tool.
	/// @param flatnessDiameter is the flatness diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwBarrelTaperMill(
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& flatnessDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Destructor
	virtual ~mwBarrelTaperMill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwBarrelTaperMill(const mwBarrelTaperMill& toCopy);

	//#########################  Gets  ############################################

	/// Gets the upper diameter of the tool.
	///
	///	@return The upper diameter of the tool.
	const double& GetUpperDiameter() const;


	/// Gets the taper angle of the tool.
	///
	///	@return The taper angle of the tool.
	const double& GetTaperAngle() const;


	/// Gets the lower (centered-corner) radius.
	///
	/// @returns The lower radius of the tool.
	const double& GetLowerRadius() const;


	/// Gets the profile radius of the tool.
	///
	///	@return The profile radius of the tool.
	const double& GetProfileRadius() const;


	/// Gets the upper-corner radius of the tool.
	///
	///	@return The upper-corner radius of the tool.
	const double& GetUpperRadius() const;


	/// Gets the flatness diameter of the tool.
	///
	///	@return The flatness diameter of the tool.
	const double& GetFlatnessDiameter() const;


	/// Compute the adjusted length of the flute's taper portion
	///
	/// Return unchanged flute length if the user given value is sufficient.
	///	@param newFluteLength is the given flute length of the tool.
	///	@param newUpperDiameter is the upper diameter/shaft of the tool.
	///	@param newTaperAngle is the taper angle of the tool.
	///	@param newLowerRadius is the lower (centered-corner) radius of the tool.
	///	@param newProfileRadius is the profile radius of the tool.
	///	@param newUpperRadius is the upper-corner radius of the tool.
	///	@param newFlatnessDiameter is the flatness diameter of the tool.
	///	@return the adjusted length of the flute's taper part
	static double ComputeAdjustedTaperFluteLength(
		const double& newFluteLength,
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& newFlatnessDiameter);


	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	/// @return true is this tool has an advanced shoulder definition
	///		false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;


	/// Scales this object (its measurable components).
	///
	/// @param  units are the measurement units of this object.
	/// @param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwBarrelTaperMill& operator=(const mwBarrelTaperMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwBarrelTaperMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBarrelTaperMill& toCompare);

	/// Implements the visitor pattern.
	///
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	/// Copy data members from given tool to current tool
	///
	///	@param toCopy is barrel to be copied into this object
	void Copy(const mwBarrelTaperMill& toCopy);

	/// Validates the upper diameter
	///
	/// Validates the upper diameter of the tool
	///	@param newUpperDiameter the new upper diameter
	///	@throws mwException if the upper diameter is not valid
	void ValidateUpperDiameter(const double& newUpperDiameter) const;

	/// Validates the taper angle
	///
	/// Validates the taper angle of the tool
	/// @param newTaperAngle the taper angle
	/// @throws mwException if the taper angle is not valid
	void ValidateTaperAngle(const double& newTaperAngle) const;

	/// Validates the lower radius
	///
	/// Validates if the lower radius is greater than zero
	/// @param newLowerRad lower radius
	/// @throws mwException if the lower radius is negative or zero
	void ValidateLowerRadius(const double& newLowerRadius) const;

	/// Validates the profile radius
	///
	/// Validates the profile radius of the tool
	///	@param newProfileRadius the new profile radius
	///	@throws mwException if the profile radius is not valid
	void ValidateProfileRadius(const double& newProfileRadius) const;

	/// Validates the upper-corner radius
	///
	/// Validates the upper-corner radius of the tool
	///	@param newUpperRadius the new upper-corner radius
	///	@throws mwException if the upper-corner radius is not valid
	void ValidateUpperRadius(const double& newUpperRadius) const;

	/// Validates the flatness diameter
	///
	/// Validates if the flatness diameter is positive or zero
	/// @param newFlatnessDiameter the new flatness diameter
	/// @throws mwException if the flatness diameter is negative
	void ValidateFlatnessDiameter(const double& newFlatnessDiameter) const;

	/// Compute the length of the flute's taper portion
	///
	/// It also represents the y-coordinate of the upper-corner center point.
	/// @param newUpperDiameter is the upper diameter/shaft of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newLowerRadius is the lower (centered-corner) radius of the tool.
	/// @param newProfileRadius is the profile radius of the tool.
	/// @param newUpperRadius is the upper-corner radius of the tool.
	/// @param newFlatnessDiameter is the flatness diameter of the tool.
	/// @return the length of the flute's taper part
	double ComputeTaperFluteLength(
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& newFlatnessDiameter) const;

	/// Internal constructor to set member variables and perform validations.
	///
	/// @param newUpperDiameter is the upper diameter/shaft of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newLowerRadius is the lower (centered-corner) radius of the tool.
	/// @param newProfileRadius is the profile radius of the tool.
	/// @param newUpperRadius is the upper-corner radius of the tool.
	/// @param newFlatnessDiameter is the flatness diameter of the tool.
	void InternalConstructor(
		const double& newUpperDiameter,
		const double& newTaperAngle,
		const double& newLowerRadius,
		const double& newProfileRadius,
		const double& newUpperRadius,
		const double& newFlatnessDiameter);

	/// Validate individual params
	///
	/// @param upperDiameter is the upper diameter/shaft to be validated.
	/// @param taperAngle is the taper angle of the tool.
	/// @param lowerRadius is the lower (centered-corner) radius to be validated.
	/// @param profileRadius is the profile radius to be validated.
	/// @param upperRadius is the upper-corner radius to be validated.
	/// @param newFlatnessDiameter is the flatness diameter to be validated.
	void IndividualParamsValidations(
		const double& upperDiameter,
		const double& taperAngle,
		const double& lowerRadius,
		const double& profileRadius,
		const double& upperRadius,
		const double& newFlatnessDiameter) const;

	/// Validate dependencies between parameters
	///
	/// @param upperDiameter is the upper diameter/shaft to be validated.
	/// @param profileRadius is the profile radius to be validated.
	/// @param referenceDiameter is reference diameter to be validated
	/// @param axialDistance is axial distance to be validated
	/// @param radialDistance is radial distance to be validated
	void DependenciesParamsValidations(
		const double& upperDiameter,
		const double& profileRadius,
		const double& referenceDiameter,
		const double& axialDistance,
		const double& radialDistance) const;


	double m_upperDiameter;
	double m_taperAngle;
	double m_lowerRadius;
	double m_profileRadius;
	double m_upperRadius;
	double m_flatnessDiameter;
};
}  // namespace cadcam
#endif  //	MW_MWBARRELTAPERMILL_HPP_
