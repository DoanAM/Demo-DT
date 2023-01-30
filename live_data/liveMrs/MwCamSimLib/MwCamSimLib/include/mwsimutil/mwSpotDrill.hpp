// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWSPOTDRILL_HPP_
#define MW_MWSPOTDRILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwSpotDrill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwSpotDrill& toDump);

namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a spot drill tool.
class MW_5AXUTIL_API mwSpotDrill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwSpotDrill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	//##################### Lifecycle #############################################
	/// Default constructor
	explicit mwSpotDrill(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a spot drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param units are the units.
	mwSpotDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const Units units);

	/// Constructor
	///
	/// Constructs a spot drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwSpotDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Destructor
	~mwSpotDrill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool to be copied.
	mwSpotDrill(const mwSpotDrill& toCopy);

	//#########################  Gets  ############################################

	/// Gets the tip angle.
	///
	/// @returns The current tip angle of the tool.
	const double& GetTipAngle() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwSpotDrill& operator=(const mwSpotDrill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwSpotDrill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwSpotDrill& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the tip/shoulder intersection. It is valid when the tip intersects
	/// the shoulder.
	///
	/// @param newTipAngle is the tip angle.
	/// @param newDiameter is the tool diameter.
	/// @param newShoulderLen is the shoulder length.
	/// @throws mwException if the tip does not intersect the shoulder.
	void ValidateIntersection(
		const double& newTipAngle, const double& newDiameter, const double& newShoulderLen) const;

	/// Checks the validity of the tip angle. A valid tip angle is >=1 and <=180
	///
	/// @param newTipAngle is the tip angle.
	/// @throws mwException if the tip angle is not between 1 and 180.
	void ValidateTipAngle(const double& newTipAngle) const;

protected:
private:
	/// Copies the data from mwSpotDrill
	void Copy(const mwSpotDrill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	void InternalConstructor(
		const double& newDiameter, const double& newShoulderLen, const double& newTipAngle);

	/// Tip angle
	double mTipAngle;
};
}  // namespace cadcam
#endif  //	MW_MWSPOTDRILL_HPP_
