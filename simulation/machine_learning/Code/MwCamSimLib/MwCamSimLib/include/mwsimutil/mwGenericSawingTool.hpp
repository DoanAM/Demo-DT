// (C) 2012-2020 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWGENERICSAWINGTOOL_HPP_
#define MW_MWGENERICSAWINGTOOL_HPP_
#include "mwCuttingPartDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwNonCuttingPartDefinition.hpp"
#include "mwSawingTool.hpp"

#include <list>


namespace cadcam
{
/// class mwGenericSawingTool
/// This class defines a general sawing tool (defined by its custom profile)
/// Sawing tools are used for saw machining cycle
class MW_5AXUTIL_API mwGenericSawingTool: public mwSawingTool
{
public:
	using mwSawingTool::AcceptVirtual;

	typedef misc::mwAutoPointer<mwGenericSawingTool> Ptr;
	typedef mwSawingTool::HolderDefinition HolderDefinition;

	typedef mwToolPartDefinition<double> PartDefinition;
	typedef misc::mwAutoPointer<PartDefinition> PartDefinitionPtr;
	typedef mwCuttingPartDefinition<double> CutPartDefinition;
	typedef mwNonCuttingPartDefinition<double> NonCutPartDefinition;

	typedef std::pair<CutPartDefinition, double> OffsetedCuttingPart;
	typedef std::list<OffsetedCuttingPart> OffsetedCuttingParts;
	typedef std::list<OffsetedCuttingPart>::iterator OffsetedCuttingPartsIt;
	typedef std::list<OffsetedCuttingPart>::const_iterator OffsetedCuttingPartsConstIt;
	typedef std::pair<NonCutPartDefinition, double> OffsetedNonCuttingPart;
	typedef std::list<OffsetedNonCuttingPart> OffsetedNonCuttingParts;
	typedef std::list<OffsetedNonCuttingPart>::iterator OffsetedNonCuttingPartsIt;
	typedef std::list<OffsetedNonCuttingPart>::const_iterator OffsetedNonCuttingPartsConstIt;


	typedef std::list<PartDefinitionPtr> PartDefinitions;
	typedef std::list<PartDefinitionPtr>::iterator PartDefinitionsIt;
	typedef std::list<PartDefinitionPtr>::const_iterator PartDefinitionsConstIt;

	typedef mwSolidDefinition<double> SolidDefinition;
	typedef mwRevolvedSolidDefinition<double> RevolvedSolidDefinition;
	typedef mwSolidDefinitionVisitorGetter<double> SolidDefinitionVisitor;

	explicit mwGenericSawingTool(const Units units = Units::METRIC);

	virtual ~mwGenericSawingTool(){};

	/// Constructor
	///
	/// Constructs a generic sawing tool using the given parameters.
	///	@param holder is the tool holder.
	///	@param arbor is the tool arbor.
	///	@param shaft is the tool shaft.
	///	@param units are the measurement units for this tool.
	mwGenericSawingTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const double& bladeThickness,
		const Units units);

	mwGenericSawingTool(
		const HolderDefinition& holder, const double& bladeThickness, const Units units);

	/// This function is used in the visitor scheme
	void virtual AcceptVirtual(mwToolVisitor& virtualVisitor) const;

	/// Equality operator
	///
	/// Use this operator to compare the parameters of two tools.
	///	@param toCompare is the tool that will be compared with the current tool.
	///	@returns <b>True</b> if both tools contain the same parameters,
	///	<b>false</b> otherwise
	bool operator==(const mwGenericSawingTool& toCompare) const;
	/// Get specifyed tool part(s) bounding box. See base class function for more details
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const;

protected:
	/// Scales this object (its measurable components).
	/// @param units the new metric system to be used.
	/// @param scaleFactor the scale factor to be used when scaling the dimensions.
	virtual void Scale(const Units units, const double& scaleFactor);
};
}  // namespace cadcam
#endif  //	MW_MWGENERICSAWINGTOOL_HPP_
