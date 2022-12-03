// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWSPHEREMILL_HPP_
#define MW_MWSPHEREMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwSphereMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwSphereMill& toDump);

namespace cadcam
{
/// This class represents a sphere mill tool.
class MW_5AXUTIL_API mwSphereMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwSphereMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwSphereMill(const Units units = Units::METRIC);

	/// Destructor
	~mwSphereMill();

	/// Constructor
	///
	/// Constructs an end sphere tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the length of the flute.
	/// @param newArbor is the arbor.
	/// @param units are the units.
	mwSphereMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);


	/// Constructor
	///
	/// Constructs an end sphere tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the length of the flute.
	/// @param newArbor is the arbor.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the units.
	mwSphereMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs an sphere mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwSphereMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	/// @param toCopy is the tool to be copied.
	mwSphereMill(const mwSphereMill& toCopy);

	//#########################  Gets  ############################################

	/// Gets the corner radius
	///
	///  @returns The corner radius of the tool.
	const double GetCornerRadius() const;

	/// Gets the corner radius type.
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which information is copied.
	///  @returns The current tool with copied information.
	const mwSphereMill& operator=(const mwSphereMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwSphereMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwSphereMill& toCompare);

	/// Implements visitor pattern
	/// @param virtualVisitor the visitor to be accepted
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
private:
	/// Copies only data from mwSphereMill.
	void Copy(const mwSphereMill& rToCopy);
};
}  // namespace cadcam
#endif  //	MW_MWSPHEREMILL_HPP_
