// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWBULLMILL_HPP_
#define MW_MWBULLMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwBullMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwBullMill& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a bull mill tool.
class MW_5AXUTIL_API mwBullMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwBullMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwBullMill(const Units units = Units::METRIC);

	/// Destructor
	~mwBullMill();

	/// Constructor
	///
	/// Constructs a bull mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder length.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param units are the units.
	mwBullMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const Units units);

	/// Constructor
	///
	/// Constructs a bull mill tool using the given parameters:
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder length.
	/// @param newShoulderLen is the length of the shoulder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param shoulderDefinition is the definition for the shoulder.
	/// @param units are the units.
	mwBullMill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const mwShoulderDefinitionExtender& shoulderDefinition,
		const Units units);

	/// Constructs an bull mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newCornerRad is the corner radius of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwBullMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const double& newCornerRad,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a given tool.
	///   @param toCopy is the tool that will be copied.
	mwBullMill(const mwBullMill& toCopy);

	//#########################  Gets  ############################################

	/// Get corner radius.
	///
	///  @returns The corner radius of the tool.
	const double& GetCornerRadius() const;

	/// Get corner radius type.
	///
	///  @returns The corner radius type.
	const cornerRadiusType GetCornerRadiusType() const;

	//########################## Operators ########################################

	/// Assignment operator for assigning one tool object to another.
	///
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwBullMill& operator=(const mwBullMill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwBullMill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwBullMill& toCompare);

	/// Implements the visitor pattern
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the diameter and corner radius. They are valid when the diameter is
	/// at least twice the corner radius.
	///
	///   @param newDiameter is the tool diameter.
	///   @param newCornerRad is the corner radius.
	///   @throws mwException if the diameter is less than twice the corner radius.
	void ValidateDiameterVSCornerRadius(
		const double& newDiameter, const double& newCornerRad) const;

	/// Checks the validity of the corner radius. The corner radius is valid when it is greater than
	/// or equal to zero.
	///
	/// @param newCornerRad is the corner radius.
	/// @throws mwException if the corner radius is negative.
	void ValidateCornerRadius(const double& newCornerRad) const;

	/// Checks the validity of the Shoulder Definition Extender length. The flute length and
	/// cylinder base length must be less than base length.
	///
	/// @param newFluteLen is the flute length.
	/// @param shoulderDefinition is the definition for the shoulder.
	/// @throws mwException if the corner radius is negative.
	void ValidateShoulderDefinitionExtenderLength(
		const mwShoulderDefinitionExtender& newShoulderDefinition, const double newFluteLen) const;

protected:
	/// Scale the tool.
	/// @param units are the units.
	/// @param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data from mwBullMill
	void Copy(const mwBullMill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newDiameter is the diameter of the tool.
	///	@param newCornerRadius is the new corner radius of the tool.
	void InternalConstructor(const double& newDiameter, const double& newCornerRadius);

	/// Corner radius
	double mCornerRadius;

	static const mwPoint2d
		m_defaultHolderPnts[];  // The list of points used to build the default holder for the tool.
	static const mwPoint2d
		m_defaultArborPnts[];  // The list of points used to build the default arbor for the tool.
};
}  // namespace cadcam
#endif  //	MW_MWBULLMILL_HPP_
