// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCTRDRILL_HPP_
#define MW_MWCTRDRILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwCtrDrill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwCtrDrill& toDump);


namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a ctr drill tool.
class MW_5AXUTIL_API mwCtrDrill: public mwTypedRevolvedTool
{
	///  @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwCtrDrill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	//##################### Lifecycle #############################################
	/// Default constructor
	explicit mwCtrDrill(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the shoulder length.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor.
	///   @param newTipAngle is the tip angle of the tool.
	///   @param newShoulderAngle is the shoulder angle of the tool.
	///   @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const Units units);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderAngle is the shoulder angle of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the shoulder length.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor.
	///   @param newTipAngle is the tip angle of the tool.
	///   @param newShoulderAngle is the shoulder angle of the tool.
	///   @param newCoreDIameter is the core diameter of the tool.
	///   @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const double& newCoreDIameter,
		const Units units);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderAngle is the shoulder angle of the tool.
	/// @param newCoreDIameter is the core diameter of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const double& newCoreDIameter,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor that arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderAngle is the shoulder angle of the tool.
	/// @param newCoreDIameter is the core diameter of the tool.
	/// @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const double& newCoreDIameter,
		const double coreheight,
		const Units units);

	/// Constructor
	///
	/// Constructs a ctr drill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor.
	/// @param newTipAngle is the tip angle of the tool.
	/// @param newShoulderAngle is the shoulder angle of the tool.
	/// @param newCoreDIameter is the core diameter of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool
	/// @param units are the units.
	mwCtrDrill(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const double& newCoreDIameter,
		const double coreheight,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);


	/// Destructor
	~mwCtrDrill();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool.
	///   @param toCopy is the tool to be copied.
	mwCtrDrill(const mwCtrDrill& toCopy);

	//#########################  Gets  ############################################

	/// Get tip angle.
	///
	/// Returns tip angle of the tool.
	///   @returns The current tip angle of the tool.
	const double& GetTipAngle() const;

	/// Gets the shoulder angle.
	///
	/// Returns The shoulder angle of the tool.
	///   @returns The current shoulder angle of the tool.
	const double& GetShoulderAngle() const;

	/// Gets the core diameter.
	///
	/// Returns the core diameter of the tool.
	///   @returns The current core diameter of the tool.
	const double& GetCoreDiameter() const;

	const double GetCoreHeight() const;

	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwCtrDrill& operator=(const mwCtrDrill& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise
	bool operator==(const mwCtrDrill& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwCtrDrill& toCompare);

	/// Implements the visitor pattern
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Checks the validity of the tip/shoulder intersection. The intersection is valid when the tip
	/// intersects the shoulder.
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

	/// Checks the validity of the shoulder angle. A valid shoulder angle is >=1 and <=180
	///
	///   @param newShoulderAngle is the shoulder angle.
	///   @throws mwException if the newShoulderAngle angle is not between 1 and 180.
	void ValidateShoulderAngle(const double& newShoulderAngle) const;
	/// Checks the validity of the core diameter. A valid core diameter is >0 and <tool diameter.
	///
	///	@param newCoreDiameter is the core diameter.
	///	@throws mwException if the newCoreDiameter angle is not in the accepted range.
	void ValidateCoreDiameter(const double newCoreDiameter) const;

protected:
	/// Scale this tool according with measurement units
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies data from mwCtrDrill.
	void Copy(const mwCtrDrill& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///	@param newDiameter is the tool's diameter.
	///	@param newShoulderLen is the tool's shoulder length.
	///	@param newTipAngle is the tool's tip angle.
	///	@param newShoulderAngle is the tool's shoulder angle.
	void InternalConstructor(
		const double& newDiameter,
		const double& newShoulderLen,
		const double& newTipAngle,
		const double& newShoulderAngle,
		const double& newCoreDiameter,
		const double coreHeight);


	/// tip angle
	double mTipAngle;
	/// shoulder angle
	double mShoulderAngle;
	// tool core diameter
	double mCoreDiameter;
	// tool core height
	double mCoreHeight;
};
}  // namespace cadcam
#endif  //	MW_MWCTRDRILL_HPP_
