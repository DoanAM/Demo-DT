// (C) 2018-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELDPROFMILL_HPP_
#define MW_MWBARRELDPROFMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwBarrelDProfMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelDProfMill& toDump);

namespace cadcam
{
/// This class represents the double profile barrel mill tool
class MW_5AXUTIL_API mwBarrelDProfMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelDProfMill& toDump);

public:
		using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
		explicit mwBarrelDProfMill(const Units units = Units::METRIC);


	/// Constructor
	///
	/// Constructs a double profile barrel mill tool using the given parameters.
	/// @param newToolDiameter is the shaft/tool diameter of the constructed tool.
	/// @param newUpperProfileRadius is the upper-profile radius of the constructed tool.
	/// @param newBlendRadius is the blend radius of the constructed tool
	/// @param newLowerProfileRadius is the lower-profile radius of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length of the constructed tool.
	/// @param newArbor is the arbor.
	/// @param units are the measurement units.
	mwBarrelDProfMill(
		const double& newToolDiameter,
					  const double& newUpperProfileRadius,
					  const double& newBlendRadius,
					  const double& newLowerProfileRadius,
		const HolderDefinition& newHolder,
					  const double& newShoulderLen,
					  const double& newFluteLen,
		const ArborDefinition& newArbor,
					  const Units units);

	/// Constructor
	///
	/// Constructs a double profile barrel mill tool using the given parameters.
	/// @param newToolDiameter is the shaft/tool diameter of the constructed tool.
	/// @param newCuttingDiameter is the cutting diameter of the tool.
	/// @param newUpperProfileRadius is the upper-profile radius of the constructed tool.
	/// @param newBlendRadius is the blend radius of the constructed tool
	/// @param newLowerProfileRadius is the lower-profile radius of the constructed tool.
	/// @param flatnessDiameter is the flatness diameter of the constructed tool.
	/// @param useFluteLengthAsAxialDistance set whether to use the flute length
	///	as the axial distance or as the actual flute length.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length of the constructed tool.
	/// @param newArbor is the arbor.
	/// @param units are the measurement units.
	mwBarrelDProfMill(
		const double& newToolDiameter,
			const double& newCuttingDiameter,
			const double& newUpperProfileRadius,
			const double& newBlendRadius,
			const double& newLowerProfileRadius,
			const double& flatnessDiameter,
			const bool& useFluteLengthAsAxialDistance,
		const HolderDefinition& newHolder,
			const double& newShoulderLen,
			const double& newFluteLen,
		const ArborDefinition& newArbor,
			const Units units);


	/// Constructor with parameters and user given shoulder definition extender
	///
	/// Constructs a double profile barrel mill tool using the given parameters.
	/// @param newToolDiameter is the shaft/tool diameter of the constructed tool.
	/// @param newUpperProfileRadius is the upper-profile radius of the constructed tool.
	/// @param newBlendRadius is the blend radius of the constructed tool
	/// @param newLowerProfileRadius is the lower-profile radius of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length of the constructed tool.
	/// @param newArbor is the arbor.
	/// @param shoulderDefinition is the shoulder definition extender.
	/// @param units are the measurement units.
	mwBarrelDProfMill(
		const double& newToolDiameter,
					  const double& newUpperProfileRadius,
					  const double& newBlendRadius,
					  const double& newLowerProfileRadius,
		const HolderDefinition& newHolder,
					  const double& newShoulderLen,
					  const double& newFluteLen,
		const ArborDefinition& newArbor,
					  const mwShoulderDefinitionExtender& shoulderDefinition,
					  const Units units);

	/// Destructor
		virtual ~mwBarrelDProfMill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwBarrelDProfMill(const mwBarrelDProfMill& toCopy);

	//#########################  Gets  ############################################


	/// Gets the upper-profile radius.
	///
	///  @returns The upper-profile radius of the tool.
	const double& GetUpperProfileRadius() const;


	/// Gets the blend radius of the tool.
	///
	///	@return The blend radius of the tool.
		const double& GetBlendRadius() const;


	/// Gets the lower-profile radius of the tool.
	///
	///	@return The lower-profile radius of the tool.
		const double& GetLowerProfileRadius() const;


	/// Gets the flatness diameter of the tool.
	///
	///	@return The flatness diameter of the tool.
		const double& GetFlatnessDiameter() const;


	/// Gets the cutting diameter of the tool.
	///
	///	@return The cutting diameter of the tool.
		const double& GetCuttingDiameter() const;


	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	/// @return true is this tool has an advanced shoulder definition
	///		false if this tool doesn't have an advanced shoulder definition
		virtual const bool HasAdvancedShoulderDefinition() const;


	/// Check if the flute length value is considered to represent the axial distance
	/// of the tool
	///
	/// @return true if the flute length is equivalent to the axial distance
	///		false if the flute length is used a the actual flute length
		virtual const bool UseFluteLengthAsAxialDistance() const;


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
	const mwBarrelDProfMill& operator=(const mwBarrelDProfMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwBarrelDProfMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBarrelDProfMill& toCompare);

	/// Implements the visitor pattern.
	///
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	/// Copy data members from given tool to current tool
	///
	///	@param toCopy is barrel to be copied into this object
	void Copy(const mwBarrelDProfMill& toCopy);

	/// Validates the upper-profile radius
	///
	/// Validates the upper-profile radius of the tool
	/// @param newUpperProfileRadius upper-profile radius
	/// @throws mwException if the upper-profile radius is not valid
	void ValidateUpperProfileRadius(const double& newUpperProfileRadius) const;

	/// Validates the blend radius
	///
	/// Validates the blend radius of the tool
	///	@param newBlendRadius the new blend radius
	///	@throws mwException if the blend radius is not valid
	void ValidateBlendRadius(const double& newBlendRadius) const;

	/// Validates the lower-profile radius
	///
	/// Validates the lower-profile radius of the tool
	///	@param newLowerProfileRadius the new lower-profile radius
	///	@throws mwException if the lower-profile radius is not valid
	void ValidateLowerProfileRadius(const double& newLowerProfileRadius) const;

	/// Internal constructor to set member variables and perform validations.
	///
	/// @param newToolDiameter is the shaft/tool diameter of the tool.
	/// @param newCuttingDiameter the cutting diameter of the tool.
	/// @param newUpperProfileRadius is the upper-profile radius of the tool.
	/// @param newBlendRadius is the blend radius of the tool.
	/// @param newLowerProfileRadius is the lower-profile radius of the tool.
	/// @param newFluteLen is the flute length of the tool.
	void InternalConstructor(
		const double& newToolDiameter,
		const double& newCuttingDiameter,
		const double& newUpperProfileRadius,
		const double& newBlendRadius,
		const double& newLowerProfileRadius,
		const double& newFluteLen);

	/// Validate individual params
	///
	/// @param newUpperProfileRadius is the upper-profile radius of the tool.
	/// @param newBlendRadius is the blend radius of the tool.
	/// @param newLowerProfileRadius is the lower-profile radius of the tool.
	void IndividualParamsValidations(
		const double& newUpperProfileRadius,
									const double& newBlendRadius,
									const double& newLowerProfileRadius) const;

	/// Validate dependencies between parameters
	///
	/// @param newToolDiameter is the shaft/tool diameter of the tool.
	/// @param newUpperProfileRadius is the upper-profile radius of the tool.
	/// @param newBlendRadius is the blend radius of the tool.
	/// @param newLowerProfileRadius is the lower-profile radius of the tool.
	/// @param newFluteLen is the flute length of the tool.
	void DependenciesParamsValidations(
		const double& newToolDiameter,
		const double& newUpperProfileRadius,
									const double& newBlendRadius,
									const double& newLowerProfileRadius,
									const double& newFluteLen) const;

	void DependenciesParamsValidations(
		const double& newToolDiameter,
		const double& newCuttingDiameter,
		const double& newUpperProfileRadius,
		const double& newBlendRadius,
		const double& newLowerProfileRadius,
		const double& newFluteLen) const;


	double m_upperProfileRadius;
	double m_blendRadius;
	double m_lowerProfileRadius;
	double m_flatnessDiameter;
	double m_cuttingDiameter;
	bool m_useFluteLengthAsAxialDistance;
};
}  // namespace cadcam
#endif	//	MW_MWBARRELDPROFMILL_HPP_
