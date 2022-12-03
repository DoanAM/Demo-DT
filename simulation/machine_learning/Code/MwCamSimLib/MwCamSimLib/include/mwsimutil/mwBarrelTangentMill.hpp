// (C) 2017-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELTANGENTMILL_HPP_
#define MW_MWBARRELTANGENTMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwBarrelTangentMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelTangentMill& toDump);

namespace cadcam
{
/// This class represents the tangent to shaft barrel mill tool
class MW_5AXUTIL_API mwBarrelTangentMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelTangentMill& toDump);

public:
		using mwRevolvedTool::AcceptVirtual;
		//############################ Lifecycle ######################################
	/// Default constructor
		explicit mwBarrelTangentMill(const Units units = Units::METRIC);


	/// Constructor
	///
	/// Constructs a tangent to shaft barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter/shaft of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerRadius is the centred-corner radius of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the entire length of this tool's flute.
	/// @param newArbor is the arbor.
	/// @param units are the measurement units.
	mwBarrelTangentMill(
		const double& newUpperDiameter,
			const double& newProfileRadius,
			const double& newLowerRadius,
		const HolderDefinition& newHolder,
			const double& newShoulderLen,
			const double& newFluteLen,
		const ArborDefinition& newArbor,
			const Units units);


	/// Constructor with parameters and user given shoulder definition extender
	///
	/// Constructs a tangent to shaft barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter/shaft of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newLowerRadius is the lower (centered-corner) radius of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the entire length of this tool's flute.
	/// @param newArbor is the arbor.
	/// @param shoulderDefinition is the shoulder definition extender.
	/// @param units are the measurement units.
	mwBarrelTangentMill(
		const double& newUpperDiameter,
			const double& newProfileRadius,
			const double& newLowerRadius,
		const HolderDefinition& newHolder,
			const double& newShoulderLen,
			const double& newFluteLen,
		const ArborDefinition& newArbor,
			const mwShoulderDefinitionExtender& shoulderDefinition,
			const Units units);

	/// Destructor
		virtual ~mwBarrelTangentMill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwBarrelTangentMill(const mwBarrelTangentMill& toCopy);

		//#########################  Gets  ############################################

	/// Gets the upper diameter of the tool.
	///
	///	@return The upper diameter of the tool.
		const double& GetUpperDiameter() const;

	/// Gets the profile radius of the tool.
	///
	///	@return The profile radius of the tool.
		const double& GetProfileRadius() const;

	/// Gets the lower (centered-corner) radius.
	///
	///  @returns The lower radius of the tool.
		const double& GetLowerRadius() const;

	/// Gets axial distance (OY distance) of center point (M) of tool profile circle
	///
	/// It's also the length of tangential part of the flute
	/// @return axial distance of profile center point (M)
		const double& GetAxialDistance() const;

	/// Gets radial distance (OX distance) of center point (M) of tool profile circle
	///
	/// @return radial distance of profile center point (M)
		const double& GetRadialDistance() const;

	/// Gets reference diameter of the tool
	///
	/// This is the diameter at the tip of the tool
	/// @return reference diameter
		const double& GetReferenceDiameter() const;

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
	const mwBarrelTangentMill& operator=(const mwBarrelTangentMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwBarrelTangentMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBarrelTangentMill& toCompare);

	/// Implements the visitor pattern.
	///
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	/// Copy data members from given tool to current tool
	///
	///	@param toCopy is barrel to be copied into this object
		void Copy(const mwBarrelTangentMill& toCopy);

	/// Validates the upper diameter
	///
	/// Validates the upper diameter of the tool
	///	@param newUpperDiameter the new upper diameter
	///	@throws mwException if the upper diameter is not valid
		void ValidateUpperDiameter(const double& newUpperDiameter) const;

	/// Validates the profile radius
	///
	/// Validates the profile radius of the tool
	///	@param newProfileRadius the new profile radius
	///	@throws mwException if the profile radius is not valid
		void ValidateProfileRadius(const double& newProfileRadius) const;

	/// Validates the lower radius
	///
	/// Validates if the lower radius is greater than zero
	/// @param newLowerRad lower radius
	/// @throws mwException if the lower radius is negative or zero
		void ValidateLowerRadius(const double& newLowerRadius) const;

	/// Validates reference diameter
	///
	/// Validates  reference diameter of the tool
	///	@param referenceDiameter is reference diameter to be validated
	///	@throws exception is parameter to be validated is not valid
		void ValidateReferenceDiameter(const double& referenceDiameter) const;

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newUpperDiameter is the upper diameter of the tool.
	///	@param newProfileRadius is the profile radius of the tool.
	///	@param newLowerRadius is the lower (centered-corner) radius of the tool.
	void InternalConstructor(
		const double& newUpperDiameter,
			const double& newProfileRadius,
			const double& newLowerRadius);

	/// Compute the axial distance of this tool
	///
	/// It's also the length of tangential part of the flute
	/// @return axial distance
	double ComputeAxialDistance(
		const double& newUpperDiameter,
			const double& newProfileRadius,
			const double& newLowerRadius) const;
	/// Validate individual params
	///
	///	@param upperDiameter is upper diameter to be validated
	///	@param profileRadius is profile radius to be validated
	///	@param lowerRadius is lower radius to be validated
	///	@param referenceDiameter  is reference diameter to be validated
	void IndividualParamsValidations(
		const double& upperDiameter,
			const double& profileRadius,
			const double& lowerRadius,
			const double& referenceDiameter) const;

	/// Validated dependencies between parameters
	///
	///	@param upperDiameter is upper diameter to be validated
	///	@param profileRadius is profile radius to be validated
	///	@param lowerRadius is lower radius to be validated
	///	@param referenceDiameter  is reference diameter to be validated
	///	@param axialDistance is axial distance to be validated
	///	@param radialDistance is radial distance to be validated
	void DependenciesParamsValidations(
		const double& upperDiameter,
			const double& profileRadius,
			const double& lowerRadius,
			const double& referenceDiameter,
			const double& axialDistance,
			const double& radialDistance);

		double m_upperDiameter;
		double m_profileRadius;
		double m_lowerRadius;
		double m_referenceDiameter;
		double m_axialDistance;
		double m_radialDistance;
};
}  // namespace cadcam
#endif	//	MW_MWBARRELTANGENTMILL_HPP_
