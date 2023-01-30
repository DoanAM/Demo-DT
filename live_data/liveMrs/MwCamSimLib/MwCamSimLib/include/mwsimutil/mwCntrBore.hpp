// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWCNTRBORE_HPP_
#define MW_MWCNTRBORE_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwCntrBore;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwCntrBore& toDump);

namespace cadcam
{
/// This class represents a contour bore tool.
class MW_5AXUTIL_API mwCntrBore: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwCntrBore& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	//##################### Lifecycle #############################################
	/// Default constructor
	explicit mwCntrBore(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a contour bore tool using the given parameters.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the shoulder length.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor diameter of the tool.
	///   @param units are the units.
	mwCntrBore(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);

	/// Constructor
	///
	/// Constructs a contour bore tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShoulderDef is the new shoulder definition of the tool.
	/// @param units are the units.
	mwCntrBore(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Destructor
	~mwCntrBore();

	/// Copy constructor
	///
	/// Creates an exact copy of a tool.
	///   @param toCopy is the tool to be copied.
	mwCntrBore(const mwCntrBore& toCopy);

	//######################### Sets   ############################################


	//#########################  Gets  ############################################


	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwCntrBore& operator=(const mwCntrBore& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwCntrBore& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwCntrBore& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;


protected:
private:
	/// Copies the data from mwCntrBore.
	void Copy(const mwCntrBore& rToCopy);
};
}  // namespace cadcam
#endif  //	MW_MWCNTRBORE_HPP_
