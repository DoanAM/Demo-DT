// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWGENERICREVOLVEDTOOL_HPP_
#define MW_MWGENERICREVOLVEDTOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwCuttingPartDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwNonCuttingPartDefinition.hpp"
#include "mwRevolvedTool.hpp"

#include <list>

namespace cadcam
{
class mwToolPartsContainer;

/// This class defines a general revolved tool (defined by its custom profile).
class MW_5AXUTIL_API mwGenericRevolvedTool: public mwRevolvedTool
{
public:
	using mwRevolvedTool::AcceptVirtual;

	typedef misc::mwAutoPointer<mwGenericRevolvedTool> Ptr;
	typedef mwToolPartDefinition<double> PartDefinition;
	typedef misc::mwAutoPointer<PartDefinition> PartDefinitionPtr;

	typedef std::pair<PartDefinitionPtr, double> PositionedPart;
	typedef std::list<PositionedPart> PositionedParts;
	typedef std::list<PositionedPart>::iterator PositionedPartsIt;
	typedef std::list<PositionedPart>::const_iterator PositionedPartsConstIt;

	typedef mwCuttingPartDefinition<double> CutPartDefinition;
	typedef mwNonCuttingPartDefinition<double> NonCutPartDefinition;
	typedef mwArborDefinition<double> ArborDefinition;
	typedef mwHolderDefinition<double> HolderDefinition;

	typedef std::pair<CutPartDefinition, double> OffsetedCuttingPart;
	typedef std::list<OffsetedCuttingPart> OffsetedCuttingParts;
	typedef std::pair<NonCutPartDefinition, double> OffsetedNonCuttingPart;
	typedef std::list<OffsetedNonCuttingPart> OffsetedNonCuttingParts;
	typedef std::pair<ArborDefinition, double> OffsetedArborPart;
	typedef std::list<OffsetedArborPart> OffsetedArborParts;
	typedef std::pair<HolderDefinition, double> OffsetedHolderPart;
	typedef std::list<OffsetedHolderPart> OffsetedHolderParts;

	typedef std::list<PartDefinitionPtr> PartDefinitions;
	typedef std::list<PartDefinitionPtr>::iterator PartDefinitionsIt;
	typedef std::list<PartDefinitionPtr>::const_iterator PartDefinitionsConstIt;

	typedef mwSolidDefinition<double> SolidDefinition;
	typedef mwRevolvedSolidDefinition<double> RevolvedSolidDefinition;
	typedef mwSolidDefinitionVisitorGetter<double> SolidDefinitionVisitor;


	// DEPRECATED - unused
	typedef std::list<OffsetedCuttingPart>::iterator OffsetedCuttingPartsIt;
	typedef std::list<OffsetedCuttingPart>::const_iterator OffsetedCuttingPartsConstIt;
	typedef std::list<OffsetedNonCuttingPart>::iterator OffsetedNonCuttingPartsIt;
	typedef std::list<OffsetedNonCuttingPart>::const_iterator OffsetedNonCuttingPartsConstIt;

	//###################### Enums and Typedefs      ##############################

	/// Default constructor
	explicit mwGenericRevolvedTool(const Units units = Units::METRIC);

	/// Destructor
	virtual ~mwGenericRevolvedTool();

	// DEPRECATED in 2018.04
	/// Constructor
	///
	/// Constructs a revolved tool using the given parameters.
	///	@param holder is the tool holder.
	///	@param arbor is the tool arbor.
	///	@param nonCutPart is the non-cutting part of the tool.
	///	@param cutPart is the cutting part of the tool.
	///	@param units are the measurement units for the tool.
	mwGenericRevolvedTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const NonCutPartDefinition& nonCutPart,
		const CutPartDefinition& cutPart,
		const Units units);

	// DEPRECATED in 2018.04
	/// Constructor
	///
	/// Constructs a revolved tool using the given parameters.
	///	@param holder is the tool holder.
	///	@param arbor is the tool arbor.
	///	@param shaft is the tool shaft.
	///	@param units are the measurement units for this tool.
	mwGenericRevolvedTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const PartDefinitions& shaft,
		const Units units);

	/// Constructor
	///
	/// Constructs a revolved tool using the given parameters.
	///	The GetArbor and GetHolder functions will return empty objects if you use this constructor.
	///	@param parts is a collection of tool parts; it can contain at most one arbor part and one
	///holder part, but any number of the others
	///	@param units are the measurement units for this tool.
	mwGenericRevolvedTool(const PartDefinitions& parts, const Units units);

	/// Copy Constructor
	///
	/// Creates an exact copy of a tool.
	///	@param toCopy is the tool to be copied.
	mwGenericRevolvedTool(const mwGenericRevolvedTool& toCopy);
	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another
	///	@param toCopy is the tool from which the information is copied.
	///	@returns The current tool with copied information.
	const mwGenericRevolvedTool& operator=(const mwGenericRevolvedTool& toCopy);

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///	@param toCompare is the tool that will be compared with the current tool.
	///	@returns <b>True</b> if both tools contain the same parameters,
	///	<b>false</b> otherwise.
	bool operator==(const mwGenericRevolvedTool& toCompare) const;

	/// Get the tool holder - you should not call this if you used the newer constructor
	const HolderDefinition& GetHolder() const;
	/// Get the tool arbor - you should not call this if you used the newer constructor
	const ArborDefinition& GetArbor() const;

	const NonCuttingPartDefinition& GetNonCutting() const;
	const CuttingPartDefinition& GetCutting() const;

	/// Gets non-cutting parts and their offset along the shaft.
	const PositionedParts GetPositionedNonCuttingParts() const;

	/// Gets cutting parts and their offset along the shaft.
	const PositionedParts GetPositionedCuttingParts() const;

	/// Gets arbor parts and their offset along the shaft.
	const PositionedParts GetPositionedArborParts() const;

	/// Gets holder parts and their offset along the shaft.
	const PositionedParts GetPositionedHolderParts() const;

	/// Gets all shaft parts and their calculated offsets.
	const PositionedParts GetPositionedShaftParts() const;

	/// Gets all shaft parts without their calculated offsets.
	const PartDefinitions& GetShaftParts() const;

	/// Gets all shaft parts without their calculated offsets.
	const PartDefinitions& GetToolParts() const;

	/// Get non-cutting parts of the tool
	const OffsetedNonCuttingParts GetNonCuttingParts() const;

	/// Get cutting parts of the tool
	const OffsetedCuttingParts GetCuttingParts() const;

	/// Get non-cutting parts of the tool
	const OffsetedArborParts GetArborParts() const;

	/// Get cutting parts of the tool
	const OffsetedHolderParts GetHolderParts() const;

	/// Gets the tool diameter.
	///
	/// @returns The tool diameter.
	const double GetToolDiameter() const;

	/// Gets the shaft offset.
	///
	/// @returns The minimum Y position of the shaft.
	const double GetShaftOffset() const;

	//#################### Visitor scheme ########################################
	/// This function is used in the visitor scheme.
	void virtual AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Gets a tag to a generic revolved tool
	///
	/// This is used only by ModuleWorks, internally
	///	@returns tag
	const misc::mwstring& GetTag() const;

	/// Sets a tag to a generic revolved tool
	///
	/// This is used only by ModuleWorks, internally
	///	@param toSet is tag to be set
	void SetTag(const misc::mwstring& toSet);
	/// Get specified tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

protected:
	/// Scales the tool.
	///
	///	@param units are the measurement units.
	///	@param scaleFactor is the scaling factor.
	virtual void Scale(const Units units, const double& scaleFactor);

private:
	/// Copies the data mwGenericRevolvedTool
	void Copy(const mwGenericRevolvedTool& rToCopy);

	/// Parts definition
#pragma warning(suppress : 4251)
	misc::mwAutoPointer<mwToolPartsContainer> m_parts;
	misc::mwstring m_tag;

	bool m_multipleArbHold;  // false = old mode, arbor and holder can be recovered from the base
							 // class
	NonCuttingPartDefinition m_dummyShaft;
	CuttingPartDefinition m_dummyFlute;
};  // mwGenericRevolvedTool class

typedef misc::mwAutoPointer<mwGenericRevolvedTool> mwGenericRevolvedToolPtr;
}  // namespace cadcam
#endif  //	MW_MWGENERICREVOLVEDTOOL_HPP_
