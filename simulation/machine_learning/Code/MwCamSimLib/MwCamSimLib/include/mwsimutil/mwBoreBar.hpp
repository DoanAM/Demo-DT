// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBOREBAR_HPP_
#define MW_MWBOREBAR_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwBoreBar;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBoreBar& toDump);

namespace cadcam
{
/// This class represents a bore bar tool.
class MW_5AXUTIL_API mwBoreBar: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBoreBar& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwBoreBar(const Units units = Units::METRIC);

	/// Destructor
	~mwBoreBar();

	/// Constructor
	///
	/// Constructs a bore bar tool using the given parameters. If the corner radius type is none or
	/// full,
	///   the passed newCornerRad value is ignored and the corner radius is set to 0.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param holder is the holder.
	///   @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor diameter.
	///   @param newCornerRad is the corner radius of the tool.
	///   @param newTaperAngle is the taper angle of the tool.
	///   @param newCornerRadType is the corner radius type of the tool.
	///   @param units are the units.
	mwBoreBar(
		const double& newDiameter,
		const HolderDefinition& holder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newTaperAngle,
		const cornerRadiusType& newCornerRadType,
		const Units units);

	/// Constructor
	///
	/// Constructs a bore bar tool using the given parameters.If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param holder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newTaperAngle is the taper angle of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param shoulderDefinition is the shoulder definition.
	/// @param units are the units.
	mwBoreBar(
		const double& newDiameter,
		const HolderDefinition& holder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const double& newTaperAngle,
		const cornerRadiusType& newCornerRadType,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);


	/// Copy constructor
	///
	/// Creates an exact copy of a given tool.
	///   @param toCopy is the tool that will be copied.
	mwBoreBar(const mwBoreBar& toCopy);


	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	/// @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Gets the taper angle of the tool.
	///
	///  @returns The taper angle of the tool.
	const double& GetTaperAngle() const;

	/// Gets the corner radius type
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information will be copied.
	///  @returns The current tool with the copied information.
	const mwBoreBar& operator=(const mwBoreBar& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwBoreBar& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>fFalse</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBoreBar& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	void virtual AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the taper angle. A valid taper angle is >=0.1 and <=89.0.
	///
	///   @param newTaperAngle is the taper angle.
	///   @throws mwException if the taper angle is not between 0.1 and 89.0
	void ValidateTaperAngle(const double& newTaperAngle) const;

	/// Checks the validity of the corner radius. A valid corner radius is >=0 for all types and > 0
	/// for the "corner" type.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	void ValidateDiameterTaperAngleCornerRadiusFluteLength() const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// If the type is corner, it leaves the radius unchanged;
	///	if the type is none or full, it changes the radius to 0.0;
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value than none, corner or
	///   full.
	void ComputeCornerRadius();

protected:
	/// Scale the tool (its measurable components).
	///
	///	@param units are the measurement units of the tool.
	///	@param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwBoreBar.
	void Copy(const mwBoreBar& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newCornerRad is the corner radius of the tool.
	///	@param newTaperAngle is the taper angle of the tool.
	///	@param newCornerRadType is the corner radius type of the tool.
	void InternalConstructor(
		const double& newCornerRad,
		const double& newTaperAngle,
		const cornerRadiusType& newCornerRadType);

	/// corner radius
	double mCornerRadius;
	/// taper angle
	double mTaperAngle;
	/// corner radius type
	cornerRadiusType mCornerRadiusType;
};
}  // namespace cadcam
#endif  //	MW_MWBOREBAR_HPP_
