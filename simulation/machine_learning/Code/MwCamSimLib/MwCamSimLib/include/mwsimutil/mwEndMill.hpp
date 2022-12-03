// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWENDMILL_HPP_
#define MW_MWENDMILL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include <iostream>


namespace cadcam
{
class mwEndMill;
}
std::ostream& operator<<(std::ostream& os, const cadcam::mwEndMill& toDump);

namespace cadcam
{
/// @class mwEndMill
/// This class represents an end mill tool.
class MW_5AXUTIL_API mwEndMill: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwEndMill& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;

	explicit mwEndMill(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwEndMill();

	/// Constructs an end mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param units are the units.
	mwEndMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const Units units);
	/// Constructs an end mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newShoulderLen is the shoulder length.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShoulderDef is the shoulder definition of the tool.
	/// @param units are the units.
	mwEndMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newShoulderLen,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const mwShoulderDefinitionExtender& newShoulderDef,
		const Units units);

	/// Constructs an end mill tool using the given parameters.
	/// @param newDiameter is the diameter of the constructed tool.
	/// @param newHolder is the holder.
	/// @param newFluteLen is the flute length.
	/// @param newArbor is the arbor diameter of the tool.
	/// @param newShaftDef is the shaft definition of the tool.
	/// @param units are the units.
	mwEndMill(
		const double newDiameter,
		const HolderDefinition& newHolder,
		const double newFluteLen,
		const ArborDefinition& newArbor,
		const NonCutPartDefinition& newShaftDef,
		const Units units);

	/// Creates an exact copy of the tool.
	/// @param toCopy is the tool that you want to copy.
	mwEndMill(const mwEndMill& toCopy);

	/// Assigns one tool object to another.
	/// @param toCopy is the tool from which the information will be to copied.
	/// @returns The current tool with the copied information.
	const mwEndMill& operator=(const mwEndMill& toCopy);

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>True</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise.
	bool operator==(const mwEndMill& toCompare) const;

	/// Use this operator to compare the parameters of two tools.
	/// @param toCompare is the tool that will be compared with the current tool.
	/// @returns <b>False</b> if both tools contain the same parameters,
	/// <b>true</b> otherwise.
	bool operator!=(const mwEndMill& toCompare);

	/// Implements the visitor pattern
	/// @param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

private:
	/// Copies the data from mwEndMill
	/// @param src Source tool from which the data will bve copied.
	void Copy(const mwEndMill& src);
};
}  //  namespace cadcam
#endif  //	MW_MWENDMILL_HPP_
