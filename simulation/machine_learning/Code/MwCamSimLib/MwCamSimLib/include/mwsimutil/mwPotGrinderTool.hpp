// (C) 2019-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWPOTGRINDERTOOL_HPP_
#define MW_MWPOTGRINDERTOOL_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwTypedRevolvedTool.hpp"

#include "iostream"

namespace cadcam
{
class mwPotGrinderTool;
}

std::ostream& operator<<(std::ostream& os, const cadcam::mwPotGrinderTool& toDump);

namespace misc
{
class mwException;
}

namespace cadcam
{
/// This class represents a pot grinding tool.
class MW_5AXUTIL_API mwPotGrinderTool: public mwTypedRevolvedTool
{
	/// @param os is the stream.
	/// @param toDump is this class.
	/// @return The resulting stream.
	friend std::ostream& operator<<(std::ostream& os, const cadcam::mwPotGrinderTool& toDump);

public:
	using mwRevolvedTool::AcceptVirtual;
	//############################ Lifecycle ######################################
	/// Default constructor
	explicit mwPotGrinderTool(const Units units = Units::METRIC);

	/// Destructor
	~mwPotGrinderTool();

	/// Constructor
	///
	/// Constructs a pot grinder tool using the given parameters.
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newHolder is the holder length.
	///   @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newTopThickness is the top thickness of the tool.
	///   @param newFlatnessArea is the flatness area of the tool.
	///   @param newWallThickness is the wall thickness of the tool.
	///   @param newInclinationHeight is the inclination height of the tool.
	///   @param newArbor is the arbor.
	///   @param units are the units.
	mwPotGrinderTool(
		const double& newDiameter,
		const HolderDefinition& newHolder,
		const double& newHeight,
		const ArborDefinition& newArbor,
		const double& newTopThickness,
		const double& newFlatnessArea,
		const double& newWallThickness,
		const double& newInclinationHeight,
		const Units units);

	/// Copy constructor
	///
	/// Creates an exact copy of a given tool.
	///   @param toCopy is the tool that will be copied.
	mwPotGrinderTool(const mwPotGrinderTool& toCopy);

	//#########################  Gets  ############################################
	/// Get Top Thickness.
	///
	///  @returns The Top Thickness of the tool.
	const double& GetTopThickness() const;

	/// Get Flatness Area.
	///
	///  @returns The Flatness Area of the tool.
	const double& GetFlatnessArea() const;

	/// Get Wall Thickness.
	///
	///  @returns The Wall Thickness of the tool.
	const double& GetWallThickness() const;

	/// Get Inclination Width.
	///
	///  @returns The Inclination Height of the tool.
	const double& GetInclinationHeight() const;

	//########################## Operators ########################################

	/// Assignment operator for assigning one tool object to another.
	///
	///  @param toCopy is the tool from which the information is copied.
	///  @returns The current tool with the copied information.
	const mwPotGrinderTool& operator=(const mwPotGrinderTool& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>false</b> otherwise.
	bool operator==(const mwPotGrinderTool& toCompare) const;

	/// Inequality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>False</b> if both tools contain the same parameters,
	///  <b>true</b> otherwise.
	bool operator!=(const mwPotGrinderTool& toCompare);

	/// Implements the visitor pattern
	///
	///	@param virtualVisitor is the visitor to be accepted.
	virtual void AcceptVirtual(mwToolVisitor& virtualVisitor) const;

protected:
	/// Scale the tool.
	/// @param units are the units.
	/// @param scaleFactor is the factor by which the tool is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);
	// Validations
	void ValidateFlatnessArea(const double newFlatnessArea) const;
	void ValidateWallThickness(const double newWallThickness) const;
	void ValidateInclinationHeight(const double newInclinationHeight) const;
	void ValidateTopThickness(const double newTopThickness) const;

	void ValidateDiameterWallThickness(
		const double newDiameter, const double newWallThickness) const;
	void ValidateWallThicknessFlatnessArea(
		const double newWallThickness, const double newFlatnessArea) const;
	void ValidateInclinationHeightWidthTopThickness(
		const double newWidth,
		const double newTopThickness,
		const double newInclinationHeight) const;

private:
	/// Copies the data from mwPotGrinderTool
	void Copy(const mwPotGrinderTool& rToCopy);

	/// Internal constructor to set member variables and perform validations.
	///
	///   @param newDiameter is the diameter of the constructed tool.
	///   @param newShoulderLen is the length of the shoulder.
	///   @param newFluteLen is the flute length.
	///   @param newTopThickness is the top thickness of the tool.
	///   @param newFlatnessArea is the flatness area of the tool.
	///   @param newWallThickness is the wall thickness of the tool.
	///   @param newInclinationWidth is the inclination width of the tool.
	void InternalConstructor(
		const double newDiameter,
		const double newTopThickness,
		const double newFlatnessArea,
		const double newWallThickness,
		const double newInclinationHeight,
		const double newWidth);

	double m_topThickness;
	double m_flatnessArea;
	double m_wallThickness;
	double m_inclinationHeight;
};
}  // namespace cadcam
#endif  //	MW_MWPOTGRINDERTOOL_HPP_
