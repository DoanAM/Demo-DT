// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBARRELMILL_HPP_
#define MW_MWBARRELMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwBarrelMill;
class mwBarrelAdvancedMill;
}  // namespace cadcam
std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelMill& toDump);

namespace cadcam
{
/// This class represents a lolipop mill tool
class MW_5AXUTIL_API mwBarrelMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBarrelMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwBarrelMill(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwBarrelMill();


	/// Constructor
	///
	/// Constructs a barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter of the constructed tool.
	/// @param newMaximumDiameter is the maximum diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param units are the measurement units.
	mwBarrelMill(
		const double& newUpperDiameter,
		const double& newMaximumDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newProfileRadius,
		const Units units);


	mwBarrelMill(
		const double& newUpperDiameter,
		const double& newMaximumDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newProfileRadius,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs an Barrel mill tool using the given parameters.
	/// @param newUpperDiameter is the upper diameter of the constructed tool.
	/// @param newMaximumDiameter is the maximum diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newCornerRadius is the corner radius of the constructed tool.
	/// @param newProfileRadius is the profile radius of the constructed tool
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwBarrelMill(
		const double& newUpperDiameter,
		const double& newMaximumDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRadius,
		const double& newProfileRadius,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwBarrelMill(const mwBarrelMill& toCopy);


	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	///  @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets corner radius type
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Gets the upper diameter of the tool.
	///
	///	@return The upper diameter of the tool.
	const double GetUpperDiameter() const;

	/// Gets the profile radius of the tool.
	///
	///	@return The profile radius of the tool.
	const double GetProfileRadius() const;


	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwBarrelMill& operator=(const mwBarrelMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwBarrelMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBarrelMill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	double m_D2, m_D3, m_R1, m_R2, m_H1, m_H2;

public:
	/// Gets the H1 parameter of the barrel tool, which is the flute length of the tool.
	/// @return The tool's flute length.
	const double& GetH1() const { return m_H1; }

	/// Gets the H2 parameter of the barrel tool, which is equal to shoulder length - flute length.
	/// @return The H2 parameter of the tool.
	const double& GetH2() const { return m_H2; }

	/// Gets the R1 parameter of the tool, which is the profile radius of the tool.
	///
	///	@return The tool's profile radius.
	const double& GetR1() const { return m_R1; }

	/// Gets the R2 parameter of the tool, which is the corner radius of the tool.
	///
	///	@return The tool's corner radius.
	const double& GetR2() const { return m_R2; }

	/// Gets the D2 parameter of the tool, which is the tool's upper diameter/2 (i.e. its upper
	/// radius).
	///
	///	@return The tool's upper radius.
	const double& GetD2() const { return m_D2; }

	/// Gets the D3 parameter of the tool, which is the tool's maximum diameter/2 (i.e. its maximum
	/// radius).
	///
	///	@return The tool's maximum radius.
	const double& GetD3() const { return m_D3; }

	/// Gets the HU parameter of the tool, which is the OY distance from the flute's upper point to
	/// the reference point (M) of the profile.
	/// @return The HU distance.
	const double GetHU() const
	{
		double x = m_D2 + m_R1 - m_D3;
		return ::sqrt(m_R1 * m_R1 - x * x);
	}

	/// Gets the HL parameter of the tool, which is the OY distance from the base of the tool to the
	/// reference point (M) of the profile.
	/// @return The HL distance.
	const double GetHL() const
	{
		double HL = m_H1 - GetHU();
		return HL;
	}

	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
	virtual const bool HasAdvancedShoulderDefinition() const;

	/// Convert an object of this class to a mwBarrelAdvancedMill advanced object.
	///
	/// In some situations, depending on the parameters settings, the conversion might not be
	/// successful. In this case an exception is thrown.
	///	@param toConvert is the object to be converted.
	///	@return autopointer to the newly constructed mwBarrelAdvancedMill object (when the
	///conversion is successful).
	///	@throws an exception if the conversion fails.
	static const misc::mwAutoPointer<mwBarrelAdvancedMill> Convert(const mwBarrelMill& toConvert);

	/// Scales this object (its measurable components).
	///
	/// @param  units are the measurement units of this object.
	/// @param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

protected:
	/// Validates the arbor
	///
	/// Reserved, all arbors are valid now
	///	@param newArbor is the arbor to validate.
	void ArborValidation(const ArborDefinition& newArbor);

private:
	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newUpperDiameter is the upper diameter of the tool.
	///	@param newMaximumDiameter is the maximum diameter of the tool.
	///	@param newShoulderLen is the shoulder length.
	///	@param newFluteLen is the flute length of the tool.
	///	@param newCornerRadius is the flute length of the tool.
	///	@param newProfileRadius is the profile radius of the tool.
	///	@param newArbor is the arbor definition of the tool.
	void InternalConstructor(
		const double& newUpperDiameter,
		const double& newMaximumDiameter,
		const double& newShoulderLen,
		const double& newFluteLen,
		const double& newCornerRadius,
		const double& newProfileRadius,
		const ArborDefinition& newArbor);

	/// Checks the validity of the upper diameter
	///
	/// Upper diameter is valid when it is non-negative
	///	@param newUpperDiameter the new upper diameter
	///	@throws mwException if the upper diameter is not valid
	void ValidateUpperDiameter(const double& newUpperDiameter);

	/// Checks the validity of the corner radius.
	///
	/// A valid corner radius is greater then or equal to zero.
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the corner radius is negative.
	void ValidateCornerRadius(const double& newCornerRadius);

	/// Checks the validity of the profile radius.
	///
	/// A valid profile radius is greater then or equal to zero.
	///	@param newProfileRadius is the new profile radius.
	///	@throws mwException if the profile radius is not valid.
	void ValidateProfileRadius(const double& newProfileRadius);

	static void IsBarrelConstructionParamsValid(
		const double& upperDiameter,
		const double& maximumDiameter,
		const double& shoulderLength,
		const double& fluteLength,
		const double& cornerRadius,
		const double& profileRadius);


	/// Copies the data from mwBarrelMill.
	void Copy(const mwBarrelMill& rToCopy);

	/// Class validates the arbor solid
	class ArborSolidValidator: public mwRevolvedTool::SolidDefinitionVisitorGetter
	{
	public:
		ArborSolidValidator(const double& referenceDiameter);
		virtual void Visit(const mwRevolvedTool::SolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::RevolvedSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ExtrudedSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::MeshSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::TurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ContourTurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::PrimeTurningSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::WireSolidDefinition& visitor);
		virtual void Visit(const mwRevolvedTool::ThreadTapSolidDefinition& visitor);

	private:
		/// diameter
		double m_referenceDiameter;
	};
};
}  // namespace cadcam
#endif  //	MW_MWBARRELMILL_HPP_
