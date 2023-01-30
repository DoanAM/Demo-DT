// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWRADMILL_HPP_
#define MW_MWRADMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwRadMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwRadMill& toDump);

namespace cadcam
{
/// This class represents a rad mill tool.
class MW_5AXUTIL_API mwRadMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwRadMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwRadMill(const Units units = Units::METRIC);

	/// Destructor
	~mwRadMill();

	/// Constructor
	///
	/// Constructs a rad mill tool using the given parameters. The corner radius type is always
	/// corner.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor.
	///   @param newCornerRad is the corner radius of the tool.
	///   @param units are the units.
	mwRadMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const Units units);

	/// Constructor
	///
	/// Constructs a rad mill tool using the given parameters. The corner radius type is always
	/// corner.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the units.
	mwRadMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	/// @param toCopy is the tool that will be copied.
	mwRadMill(const mwRadMill& toCopy);

	//#########################  Gets  ############################################

	/// Gets the corner radius.
	///
	/// @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Gets corner radius type.
	///
	/// @returns The corner radius type
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwRadMill& operator=(const mwRadMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwRadMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>false</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwRadMill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
	/// Scales an object (its measurable components).
	///
	///	@param units are the measurable units.
	///	@param scaleFactor is the factor by which the object is scaled.

	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data from mwRadMill.
	void Copy(const mwRadMill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(const double& newCornerRadius);

	/// Corner radius
	double mCornerRadius;
};
}  // namespace cadcam
#endif  //	MW_MWRADMILL_HPP_
