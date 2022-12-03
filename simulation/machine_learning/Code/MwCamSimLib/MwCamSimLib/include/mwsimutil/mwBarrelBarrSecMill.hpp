// (C) 2018-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELBARRSECMILL_HPP_
#define MW_MWBARRELBARRSECMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwBarrelBarrSecMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelBarrSecMill& toDump);

namespace cadcam
{
/// This class represents the barrel section barrel mill tool
class MW_5AXUTIL_API mwBarrelBarrSecMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelBarrSecMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwBarrelBarrSecMill(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a barrel section barrel mill tool using the given parameters.
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newToolDiameter is the maximum diameter of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length of the constructed tool.
	/// @param newArbor is the arbor.
	/// @param units are the measurement units.
	mwBarrelBarrSecMill(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newToolDiameter,
		const double& newCenterHeight,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);


	/// Constructor with parameters and user given shoulder definition extender
	///
	/// Constructs a barrel section barrel mill tool using the given parameters.
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newToolDiameter is the maximum diameter of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length of the constructed tool.
	/// @param newArbor is the arbor.
	/// @param shoulderDefinition is the shoulder definition extender.
	/// @param units are the measurement units.
	mwBarrelBarrSecMill(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newToolDiameter,
		const double& newCenterHeight,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs a barrel section barrel mill tool using the given parameters.
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newToolDiameter is the maximum diameter of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwBarrelBarrSecMill(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newToolDiameter,
		const double& newCenterHeight,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Destructor
	virtual ~mwBarrelBarrSecMill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwBarrelBarrSecMill(const mwBarrelBarrSecMill& toCopy);

	//#########################  Gets  ############################################


	/// Gets the upper-blend radius.
	///
	/// @returns The shaft diameter of the tool.
	const double& GetShaftDiameter() const;


	/// Gets the upper-blend radius.
	///
	///  @returns The upper-blend radius of the tool.
	const double& GetUpperBlendRadius() const;


	/// Gets the profile radius of the tool.
	///
	///	@return The profile radius of the tool.
	const double& GetProfileRadius() const;


	/// Gets the lower-blend radius of the tool.
	///
	///	@return The lower-blend radius of the tool.
	const double& GetLowerBlendRadius() const;


	/// Gets the profile center-point axial of the tool.
	///
	///	@return The profile center-point axial of the tool.
	const double& GetCenterHeight() const;


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
	const mwBarrelBarrSecMill& operator=(const mwBarrelBarrSecMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwBarrelBarrSecMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBarrelBarrSecMill& toCompare);

	/// Implements the visitor pattern.
	///
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	/// Copy data members from given tool to current tool
	///
	///	@param toCopy is barrel to be copied into this object
	void Copy(const mwBarrelBarrSecMill& toCopy);

	/// Validates the shaft diameter
	///
	/// Validates the shaft diameter of the tool
	/// @param newShaftDiameter shaft diameter
	/// @throws mwException if the shaft diameter is not valid
	void ValidateShaftDiameter(const double& newShaftDiameter) const;

	/// Validates the upper-blend radius
	///
	/// Validates the upper-blend radius of the tool
	/// @param newUpperBlendRadius upper-blend radius
	/// @throws mwException if the upper-blend radius is not valid
	void ValidateUpperBlendRadius(const double& newUpperBlendRadius) const;

	/// Validates the profile radius
	///
	/// Validates the profile radius of the tool
	///	@param newProfileRadius the new profile radius
	///	@throws mwException if the profile radius is not valid
	void ValidateProfileRadius(const double& newProfileRadius) const;

	/// Validates the lower-blend radius
	///
	/// Validates the lower-blend radius of the tool
	///	@param newLowerBlendRadius the new lower-blend radius
	///	@throws mwException if the lower-blend radius is not valid
	void ValidateLowerBlendRadius(const double& newLowerBlendRadius) const;

	/// Validates the profile center-point axial
	///
	/// Validates the profile center-point axial of the tool
	///	@param newCenterHeight the new profile center-point axial
	///	@throws mwException if the profile center-point axial is not valid
	void ValidateCenterHeight(const double& newCenterHeight) const;

	/// Internal constructor to set member variables and perform validations.
	///
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newToolDiameter is the maximum diameter of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	/// @param newFluteLen is the flute length of the tool.
	void InternalConstructor(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newToolDiameter,
		const double& newCenterHeight,
		const double& newFluteLen);

	/// Validate individual params
	///
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	void IndividualParamsValidations(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newCenterHeight) const;

	/// Validate dependencies between parameters
	///
	/// @param newShaftDiameter is the shaft diameter of the constructed tool.
	/// @param newUpperBlendRadius is the upper-blend radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerBlendRadius is the lower-blend radius of the constructed tool.
	/// @param newToolDiameter is the maximum diameter of the constructed tool.
	/// @param newCenterHeight is the profile center-point axial of the constructed tool.
	/// @param newFluteLen is the flute length of the tool.
	void DependenciesParamsValidations(
		const double& newShaftDiameter,
		const double& newUpperBlendRadius,
		const double& newProfileRadius,
		const double& newLowerBlendRadius,
		const double& newToolDiameter,
		const double& newCenterHeight,
		const double& newFluteLen) const;


	double m_shaftDiameter;
	double m_upperBlendRadius;
	double m_profileRadius;
	double m_lowerBlendRadius;
	double m_centerHeight;
};
}  // namespace cadcam
#endif  //	MW_MWBARRELDPROFMILL_HPP_
