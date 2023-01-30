// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWTAPLH_HPP_
#define MW_MWTAPLH_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwTapLH;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwTapLH& toDump);


namespace misc
{
class mwException;
}


namespace cadcam
{
/// This class represents a left hand tap tool.
class MW_5AXUTIL_API mwTapLH: public mwTypedRevolvedTool
{
	/// Operator for inserting an mwTapLH object into an output stream (serialization).
	///
	///	@param os is the output stream.
	///	@param toDump is the mwTapLH object to be serialized.
	///	@return A reference to the stream in which the mwTapLH object was inserted.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwTapLH& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwTapLH(const Units units = Units::METRIC);

	/// Destructor
	~mwTapLH();

	/// Constructor
	///
	/// Constructs a left hand tap tool using the given parameters. If the corner radius type is
	/// none or full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor.
	///   @param newCornerRad is the corner radius of the tool.
	///   @param newCornerRadType is the corner radius type of the tool.
	///   @param newTipAngle is the tip angle of the tool.
	///   @param newThrdsNum is the number of threads.
	///   @param units are the units used by this object.
	mwTapLH(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const cornerRadiusType& newCornerRadType,
		const double& newTipAngle,
		const int newThrdsNum,
		const Units units);

	/// Constructor
	///
	/// Constructs a left hand tap tool using the given parameters. If the corner radius type is
	/// none or full, the passed newCornerRad value is ignored and the corner radius is set to 0.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newCornerRadType is the corner radius type of the tool.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newThrdsNum is the number of threads.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the measurement units used by this object.
	mwTapLH(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const cornerRadiusType& newCornerRadType,
		const double& newTipAngle,
		const int newThrdsNum,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwTapLH(const mwTapLH& toCopy);


	/// Set the number of threads.
	///
	/// Sets the number of threads to the specified value.
	///  @param newThrdsNum is the number of threads to set.
	void SetThreadsNumber(const int newThrdsNum);

	//#########################  Gets  ############################################

	/// Get the corner radius.
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

	/// Gets the number of threads.
	///
	///  @returns The number of threads.
	const int GetThreadsNumber() const;


	//########################## Operators ########################################

	/// Assignment oeprator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwTapLH& operator=(const mwTapLH& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwTapLH& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwTapLH& toCompare);

	/// Implements visitor pattern
	/// @param virtualVisitor is a visitor class used for tools.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the tip/shoulder intersection. It is valid when the tip intersects
	/// the shoulder.
	///
	///   @param newTipAngle is the tip angle.
	///   @param newDiameter is the tool diameter.
	///   @param newShoulderLen is the shoulder length.
	///   @throws mwException if the tip does not intersect the shoulder.
	void ValidateIntersection(
		const double& newTipAngle, const double& newDiameter, const double& newShoulderLen) const;

	/// Checks the validity of the tip angle. The tip angle is valid when it is is >=1 and <=180
	///
	///   @param newTipAngle is the tip angle.
	///   @throws mwException if the tip angle is not between 1 and 180
	void ValidateTipAngle(const double& newTipAngle) const;

	/// Checks the validity of the corner radius. A valid corner radius is >=0 for all types and > 0
	/// for the "corner" type.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the validation fails.
	void ValidateCornerRadius(const double& newCornerRadius) const;

	/// Calculates the corner radius based on the selected corner radius type.
	///
	/// if the type is corner, it leaves the radius unchanged;
	///	if the type is none or full, it changes the radius to 0.0.
	///	if the type is any other value, it throws an exception.
	///   @throws mwException if the corner radius type is any other value then none, corner or
	///   full.
	void ComputeCornerRadius();

protected:
	/// Scales this object (its measurable components).
	///
	///	@param units are the measurement units of the object.
	///	@param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies only data from mwTapLH
	void Copy(const mwTapLH& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(
		const double& newDiameter,
		const double& newShoulderLen,
		const double& newCornerRad,
		const cornerRadiusType& newCRType,
		const double& newTipAngle,
		const int newThrdsNum);


	/// Corner radius for this tool
	double mCornerRadius;
	/// Type of corner radius for this tool.
	cornerRadiusType mCornerRadiusType;
	/// Tip angle for this tool.
	double mTipAngle;
	/// Number of threads
	int mThreadsNumber;
};
}  // namespace cadcam
#endif  //	MW_MWTAPLH_HPP_
