// (C) 2010-2021 by ModuleWorks GmbH
// Owner: CutSim

#ifndef MW_MWWIRETOOL_HPP_
#define MW_MWWIRETOOL_HPP_
namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc


#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwTool.hpp"


namespace cadcam
{
class mwWireToolVisitor;

/// @class mwWireTool
/// This class defines a tool consisting of a wire.
class MW_5AXUTIL_API mwWireTool: public mwTool
{
public:
	//###################### Enums and Typedefs      ##############################
	typedef misc::mwAutoPointer<mwWireTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwSolidDefinition<double> SolidDefinition;

	/// Default constructor
	///
	/// Sets wireDiameter = 0.05, wireLength = 100, units = metric, infiniteLength = true.
	explicit mwWireTool(const Units units = Units::METRIC);

	/// Constructor
	///
	///	@param wireDiameter is the thickness of the wire.
	///	@param wireLength defines the length of the tool (for visualization and laser cutting).
	///	@param units are the measurement units.
	///	@param infiniteLength True (default) for wireEDM, false for laser cut.
	mwWireTool(
		const double wireDiameter,
		const double wireLength,
		const Units units,
		const bool infiniteLength = true);

	/// Destructor
	virtual ~mwWireTool(){};

	//########################## Operators ########################################
	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///  @param toCompare is the tool that will be compared with the current tool.
	///  @returns <b>True</b> if both tools contain the same parameters,
	///  <b>False</b> otherwise.
	bool operator==(const mwWireTool& toCompare) const;

	//#########################  Gets  ############################################
	const double GetWireDiameter() const { return m_wireDiameter; }
	const double GetWireLength() const { return m_wireLength; }

	const bool HasInfiniteLength() const { return m_hasInfiniteLength; }

	const HolderDefinition& GetHolder() const;
	const ArborDefinition& GetArbor() const;

	//#################### Visitor scheme ########################################
	/// This function is used in the visitor scheme.
	///
	/// It differentiates between tool types: mwTool, mwRevolvedTool, mwWireTool, mwSawingTool, etc
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;
	/// This function is used in the visitor scheme.
	///
	/// It covers all tool types.
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;
	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

protected:
	/// Scales the wire tool (its measurable components).
	///
	/// @param units are the measurement units of this object.
	/// @param scaleFactor is the factor by which the object is scaled.
	virtual void Scale(const Units units, const double& scaleFactor);

	double m_wireDiameter;
	double m_wireLength;
	bool m_hasInfiniteLength;

private:
};

typedef misc::mwAutoPointer<mwWireTool> mwWireToolPtr;
}  // namespace cadcam
#endif  //	MW_MWWIRETOOL_HPP_
