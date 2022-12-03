// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCSINK_HPP_
#define MW_MWCSINK_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwCSink;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwCSink& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a csink tool.
class MW_5AXUTIL_API mwCSink: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwCSink& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwCSink(const Units units = Units::METRIC);

	/// Destructor
	~mwCSink();

	/// Constructor
	///
	/// Constructs a csink tool using the given parameters.If the corner radius type is none or
	/// full,the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param units are the units.
	mwCSink(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const cornerRadiusType& newCornerRadType,
		const double& newTipAngle,
		const Units units);

	/// Constructor
	///
	/// Constructs a csink tool using the given parameters. If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwCSink(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const cornerRadiusType& newCornerRadType,
		const double& newTipAngle,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs a csink tool using the given parameters.If the corner radius type is none or
	/// full,the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param bottomDiameter is the bottom diameter of the tool.
	/// @param units are the units.
	mwCSink(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double newCornerRad,
		const cornerRadiusType& newCornerRadType,
		const double newTipAngle,
		const double bottomDiameter,
		const Units units);

	/// Constructor
	///
	/// Constructs a csink tool using the given parameters. If the corner radius type is none or
	/// full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param bottomDiameter is the bottom diameter of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwCSink(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double newCornerRad,
		const cornerRadiusType newCornerRadType,
		const double newTipAngle,
		const double bottomDiameter,
		const mwShoulderDefinitionExtender& newShoulderDefinition,
		const Units units);


	/// Copy constructor
	///
	/// Creates an exact copy of a given tool.
	///   @param toCopy is the tool to be copied.
	mwCSink(const mwCSink& toCopy);

	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	///  @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Gets the corner radius type.
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	/// Gets the tip angle.
	///
	///  @returns The tip angle of the tool.
	const double& GetTipAngle() const;

	// Returns current bottom diameter
	double GetBottomDiameter() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	///
	const mwCSink& operator=(const mwCSink& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwCSink& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwCSink& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks whether the tip intersects the shoulder.
	///
	///   @param newTipAngle is the tip angle.
	///   @param newDiameter is the tool diameter.
	///   @param newShoulderLen is the shoulder length.
	///   @throws mwException if the tip does not intersect the shoulder.
	void ValidateIntersection(
		const double& newTipAngle, const double& newDiameter, const double& newShoulderLen) const;

	/// Checks the validity of the tip angle. A valid tip angle is >=1 and <=180
	///
	///   @param newTipAngle is the tip angle.
	///   @throws mwException if the tip angle is not between 1 and 180.
	void ValidateTipAngle(const double& newTipAngle) const;

	/// Checks the validity of the diameter and corner radius. They are valid if the diameter is at
	/// least twice the corner radius.
	///
	///   @param newDiameter is the tool diameter.
	///   @param newCornerRad is the corner radius.
	///   @throws mwException if the diameter is less than twice the corner radius.
	void ValidateDiameterVSCornerRadius(
		const double& newDiameter, const double& newCornerRad) const;
	/// Checks the validity of the corner radius. A valid corner radius is >=0 for all types and > 0
	/// for the "corner" type.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// if the type is corner, it leaves the radius unchanged;
	///	if the type is none or full, it changes the radius to 0.0;
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value then none, corner or
	///   full.
	void ComputeCornerRadius();

protected:
	/// Scales the tool (its measurable components).
	///
	///	@param units are the measurement units.
	///	@param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwCSink
	void Copy(const mwCSink& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newDiameter is the diameter of the tool.
	///	@param newShoulderLen is the shoulder length of the tool.
	///	@param newCornerRad is the corner radius of the tool.
	///	@param newCRType is the corner radius type of the tool.
	///	@param newTipAngle is the tip angle of the tool.
	void InternalConstructor(
		const double newDiameter,
		const double newShoulderLen,
		const double newCornerRad,
		const cornerRadiusType newCRType,
		const double newTipAngle,
		const double bottomDiameter);


	/// corner radius
	double mCornerRadius;
	/// Corner radius type
	cornerRadiusType mCornerRadiusType;
	/// Tip angle
	double mTipAngle;
	double m_bottomDiameter;
};
}  // namespace cadcam
#endif  //	MW_MWCSINK_HPP_
