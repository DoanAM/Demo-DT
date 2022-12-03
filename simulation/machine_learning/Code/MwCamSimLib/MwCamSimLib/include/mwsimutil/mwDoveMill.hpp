// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWDOVEMILL_HPP_
#define MW_MWDOVEMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwDoveMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwDoveMill& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a dove mill tool.
class MW_5AXUTIL_API mwDoveMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwDoveMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	explicit mwDoveMill(const Units units = Units::METRIC);

	~mwDoveMill();
	/// Constructs a dove mill tool using the given parameters. If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param units units
	mwDoveMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double newCornerRad,
		const double newTaperAngle,
		const cornerRadiusType newCornerRadType,
		const Units units);
	/// Constructs a dove mill tool using the given parameters. If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShoulderDef is the shoulder definition of tool.
	/// @param units are the units.
	mwDoveMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double newCornerRad,
		const double newTaperAngle,
		const cornerRadiusType newCornerRadType,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs an taper mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwDoveMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double newCornerRad,
		const double newTaperAngle,
		const cornerRadiusType newCornerRadType,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Creates an exact copy of a given tool.
	/// @param toCopy is the tool to be copied
	mwDoveMill(const mwDoveMill& toCopy);

	/// Gets the corner radius.
	/// @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets the taper angle of the tool.
	/// @returns The taper angle of the tool.
	const double GetTaperAngle() const;

	/// Gets the corner radius type.
	/// @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Assigns one tool object to another
	/// @param toCopy is the tool from which the information is copied.
	/// @returns The current tool with the copied information.
	const mwDoveMill& operator=(const mwDoveMill& toCopy);

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwDoveMill& toCompare) const;

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise
	bool operator!=(const mwDoveMill& toCompare);

	/// Implements the visitor pattern.
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Validate
	///
	/// Checks the validity of the taper angle. A valid taper angle is >=0.1 and <=89.0
	///   @param newTaperAngle is the taper angle.
	///   @throws mwException if the taper angle is not between 0.1 and 89.0
	void ValidateTaperAngle(const double newTaperAngle) const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// If the type is corner, it leaves the radius unchanged;
	///	if the type is none or full, it changes the radius to 0.0;
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value than none, corner or
	///   full.
	void ComputeCornerRadius();

	const double GetFixedCornerRadiusValueBasedOnType(
		const double& toBeFixed, const cornerRadiusType cRType) const;

	/// Checks the validity of the corner radius.
	///
	/// A valid corner radius is >=0 for all types and > 0 for the "corner" type.
	///	@param newCornerRad is the corner radius.
	///	@throws mwException if the validation fails.
	void ValidateCornerRadius(const double newCornerRadius) const;

	/// Calculate tool upper diameter
	/// @return computed upper (biggest) diameter of the tool.
	const double ComputeUpperDiameter() const;

	/// Test whether this tool has an advanced shoulder definition.
	///
	/// An advanced shoulder definition means that the shoulder of this tool consists of a cylinder
	/// and a cone.
	///	@return True is this tool's shoulder consists of a cylinder and a cone.
	///	False if this tool's shoulder is cylindrical only.
	virtual const bool HasAdvancedShoulderDefinition() const;


protected:
	/// Scales an object (its measurable components)
	///
	///	@param units are the measurement units of this object.
	///	@param scaleFactor is the factor by which the object is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwDoveMill.
	void Copy(const mwDoveMill& rToCopy);

	/// Internal constructor to set member variables and perform validations
	void InternalConstructor(
		const double newCornerRad,
		const cornerRadiusType newCornerRadType,
		const double newTaperAngle);

	/// Calculates the tool's upper diameter based on other tool elements.
	/// @param toolDiameter is tool's diameter.
	/// @param cornerRadius is the tool's corner radius.
	/// @param taperAng is the tool's taper angle.
	/// @param fluteLen is the tool's flute length.
	/// @return The calculated upper diameter of the flute.
	double CalcUpperDiaGivingToolElements(
		const double toolDiameter,
		const double cornerRadius,
		const double taperAng,
		const double fluteLen,
		const cornerRadiusType newCRType) const;

	/// Checks the validity of the tool's upper diameter. The upper diameter is valid if it is a
	/// positive number.
	///
	///	@throws mwException if flute upper diameter is not positive.
	void ValidateUpperDiameter();

	/// Corner radius
	double m_cornerRadius;
	/// Taper angle
	double m_taperAngle;
	/// Corner radius type
	cornerRadiusType m_cornerRadiusType;
};
}  // namespace cadcam
#endif  //	MW_MWDOVEMILL_HPP_
