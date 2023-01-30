// (C) 2003-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWREAMER_HPP_
#define MW_MWREAMER_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"


namespace cadcam
{
class mwReamer;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwReamer& toDump);


namespace misc
{
class mwException;
}


namespace cadcam
{
/// This class represents a reamer tool.
class MW_5AXUTIL_API mwReamer: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwReamer& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	//##################### Lifecycle #############################################
	/// Default constructor
	explicit mwReamer(const Units units = Units::METRIC);

	/// Constructor
	///
	/// Constructs a reamer tool using the given parameters.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder.
	///   @param newShoulderLen is the shoulder length.
	///   @param newFluteLen is the flute length.
	///   @param newArbor is the arbor of the tool.
	///   @param units are the units.
	mwReamer(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const Units units,
		const double factor = GetDefaultFactor());

	/// Constructor
	///
	/// Constructs a reamer tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor of the tool.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the units.
	mwReamer(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newShoulderLen,
		const double& newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units,
		const double factor = GetDefaultFactor());

	/// Destructor
	~mwReamer();


	/// Copy constructor
	///
	/// Creates an exact copy of a tool
	///   @param toCopy is the tool that will be copied.
	mwReamer(const mwReamer& toCopy);

	//#########################  Gets  ############################################
	const double GetFactor() const;
	void SetFactor(const double toSet);
	void ValidateFactor(const double factor);
	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another.
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with copied information.
	const mwReamer& operator=(const mwReamer& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwReamer& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwReamer& toCompare);

	/// Implements the visitor pattern.
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
private:
	/// Copys only the data from mwReamer
	void Copy(const mwReamer& rToCopy);
	static double GetDefaultFactor();

	double m_factor;
};
}  // namespace cadcam
#endif  //	MW_MWREAMER_HPP_
