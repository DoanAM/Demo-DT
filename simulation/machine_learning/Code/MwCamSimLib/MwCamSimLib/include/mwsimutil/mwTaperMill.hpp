// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWTAPERMILL_HPP_
#define MW_MWTAPERMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwTaperMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwTaperMill& toDump);


namespace misc
{
class mwException;
}


namespace cadcam
{
/// This class represents a taper mill tool.
class MW_5AXUTIL_API mwTaperMill: public mwTypedRevolvedTool
{
	/// Operator for inserting an mwTaperMill object in an output stream (serialization).
	///
	/// @param os is the output stream in which the mwTaperMill object will be inserted.
	///	@param toDump is the mwTaperMill object to be serialized.
	/// @return A reference to the stream in which the mwTaperMill object was inserted.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwTaperMill& toDump);

public:
		using mwRevolvedTool::AcceptVirtual;

		explicit mwTaperMill(const Units units = Units::METRIC);

		~mwTaperMill();

	/// Constructs a taper mill tool using the given parameters.
	/// If the corner radius type is none or full, the passed newCornerRad value is ignored and the
	/// corner radius is set to 0 or newDiameter/2, correspondingly.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param units are the measurement units used by this object.
		mwTaperMill(
			const double newDiameter,
			const HolderDefinition& newHolder,
			const double newShoulderLen,
			const double newFluteLen,
			const ArborDefinition& newArbor,
			const double newCornerRad,
			const double newTaperAngle,
			const cornerRadiusType& newCornerRadType,
			const Units units);

	/// Constructs a taper mill tool using the given parameters. If the corner radius type is none
	/// or full then the passed newCornerRad value is ignored and the corner radius is set to 0 or
	/// newDiameter/2, correspondingly.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the measurement units used by this object.
	mwTaperMill(
		const double newDiameter,
			const HolderDefinition& newHolder,
			const double newShoulderLen,
			const double newFluteLen,
			const ArborDefinition& newArbor,
			const double newCornerRad,
			const double newTaperAngle,
			const cornerRadiusType& newCornerRadType,
			const mwShoulderDefinitionExtender& newShoulderDef,
			const Units units);

	/// Creates a copy of a tool.
	/// @param toCopy is the tool that will be copied.
		mwTaperMill(const mwTaperMill& toCopy);

	/// Get the corner radius.
	/// @returns The corner radius of the tool.
		const double GetCornerRadius() const;

	/// Get the taper angle of the tool.
	/// @returns The taper angle of the tool.
		const double GetTaperAngle() const;

	/// Get the corner radius type.
	/// @returns The corner radius type.
		const cornerRadiusType GetCornerRadiusType() const;

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information will be copied.
	///  @returns Current tool with the copied information.
		const mwTaperMill& operator=(const mwTaperMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>true</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
		bool operator==(const mwTaperMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
		bool operator!=(const mwTaperMill& toCompare);

	/// AcceptVirtual
	///
	/// Use this function to call a tool visitor for this object.
	///	@param virtualVisitor is a visitor class used for tools.
		virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the taper angle.
	///
	/// A valid taper angle is >=0.1 and <=89.0
	///   @param newTaperAngle is the taper angle.
	///   @throws mwException if the taper angle is not between 0.1 and 89.0
		void ValidateTaperAngle(const double newTaperAngle) const;

	/// Checks the validity of the corner radius.
	///
	/// A valid corner radius is >=0 for all types and > 0 for the "corner" type.
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
		void ValidateCornerRadius(const double newCornerRadius) const;

	/// Computes the corner radius based on the selected corner radius type.
	///
	/// if the type is corner, this function leaves the radius unchanged,
	///	if the type is none it changes the radius to 0.0,
	///	if the type is full it changes the radius to diameter/2,
	///	if the type is any other value, the function throws an exception.
	///   @throws mwException if the corner radius type is any other value than none, corner or
	///   full.
	///   @param newCornerRadiusType is the corner radius type used for the calculation.
	///   @param CornerRadius is the corner radius used for the calculation.
	///   @param newDiamater is the tool diameter used for the calculation.
	const double ComputeCornerRadius(
		const cornerRadiusType newCornerRadiusType,
										 const double CornerRadius,
										 const double newDiamater) const;

	/// Checks the validity of the diameter and corner radius.
	///
	/// Checks whether the diameter is at least twice the corner radius.
	/// @throws mwException if the diameter is less than twice the corner radius.
	/// @param newDiameter is the diameter to be checked.
	/// @param newCornerRadius is the corner radius to be checked.
	static void ValidateDiameterVSCornerRadius(
		const double newDiameter, const double newCornerRadius);

	/// Calculate the upper diameter of the tool's flute.
	///
	///	@return The upper diameter of the tool's flute.
		const double ComputeFluteUpperDiameter() const;

	/// Calculate the upper diameter of the tool's shoulder.
	///
	///	@return The upper diameter of the tool's shoulder.
		const double ComputeShoulderUpperDiameter() const;

	/// Test if this tool has advanced shoulder definition
	///
	/// Check description for mwTypedRevolvedTool::HasAdvancedShoulderDefinition() for
	/// the conditions needed for an advanced shoulder definition
	///	@return true is this tool has an advanced shoulder definition
	///			false if this tool doesn't have an advanced shoulder definition
		virtual const bool HasAdvancedShoulderDefinition() const;

protected:
		virtual mw3dBoundingBox<double> GetCuttingPartBoundingBox() const;

	/// Scales this object (its measurable components).
	/// @param units are the measurement units passed to the object.
	/// @param scaleFactor is the scaling factor.
		virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Calculate transitionPoint from Corner Radius to cone
		mwTPoint2d<double> CalcCornerRadToConeTransitionPoint() const;

	/// Copies the data from mwTaperMill.
		void Copy(const mwTaperMill& src);
	/// Validates the conic part of this tool
	///
	/// Checks that the shoulder length is \f$> cornerRadius * (1 - sin(taperAngle))\f$
	///	@param newShoulderLength is the new shoulder length passed for validation.
	///	@param newCornerRadius is the new corner radius passed for validation.
	///	@param newTaperAngle is the new taper angle passed for validation.
	void ValidateConicPart(
		const double newShoulderLength,
			const double newCornerRadius,
			const double newTaperAngle) const;
	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(
		const double newDiameter,
		const double newCornerRad,
		const double newTaperAngle,
		const cornerRadiusType& newCRType);
	/// Calculates the tool's upper diameter based on the parameters you pass to the function.
	/// @param toolDiameter is the tool's diameter.
	/// @param cornerRadius is tool's corner radius.
	/// @param taperAngle is tool's taper angle.
	/// @param shoulderLen is the tool's shoulder length.
	/// @param fluteLen is the tool's flute length.
	/// @return The upper diameter of the tool.
	double CalcUpperDiaGivingToolElements(
		const double toolDiameter,
			const double cornerRadius,
			const double taperAngle,
			const double shoulderLen,
			const double fluteLen) const;

	/// Corner radius value for this tool.
		double m_cornerRadius;
	/// Taper angle value for this tool.
		double m_taperAngle;
	/// Type of corner radius for this tool.
		cornerRadiusType m_cornerRadiusType;
};
}  // namespace cadcam
#endif	//	MW_MWTAPERMILL_HPP_
