// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWREVOLVEDTOOL_HPP_
#define MW_MWREVOLVEDTOOL_HPP_

#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTool.hpp"

namespace misc
{
class mwException;
}
namespace cadcam
{

/// Base class for revolved tools
class MW_5AXUTIL_API mwRevolvedTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwRevolvedTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;
	typedef mwCuttingPartDefinition<double> CutPartDefinition;
	typedef mwNonCuttingPartDefinition<double> NonCutPartDefinition;

	typedef mwSolidDefinition<double> SolidDefinition;
	typedef mwRevolvedSolidDefinition<double> RevolvedSolidDefinition;
	typedef mwRevolvedSolidExtractor<double> RevolvedSolidExtractor;
	typedef mwExtrudedSolidDefinition<double> ExtrudedSolidDefinition;
	typedef mwMeshSolidDefinition<double> MeshSolidDefinition;
	typedef mwMeshSolidExtractor<double> MeshSolidExtractor;
	typedef mwTurningSolidDefinition<double> TurningSolidDefinition;
	typedef mwWireSolidDefinition<double> WireSolidDefinition;
	typedef mwThreadTapSolidDefinition<double> ThreadTapSolidDefinition;
	typedef mwContourTurningSolidDefinition<double> ContourTurningSolidDefinition;
	typedef mwPrimeTurningSolidDefinition<double> PrimeTurningSolidDefinition;
	typedef mwSolidDefinitionVisitorGetter<double> SolidDefinitionVisitorGetter;
	typedef mwToolPartDefinition<double> ToolPartDefinition;

	virtual ~mwRevolvedTool() {}

	/// Constructor
	///	@param holder holder for this tool
	///	@param arbor arbor for this tool
	///	@param units metric/inches system to be used for this tool
	mwRevolvedTool(const HolderDefinition& holder, const ArborDefinition& arbor, const Units units);

	mwRevolvedTool(const mwRevolvedTool& toCopy);

	/// Get holder
	///
	/// This function returns the holder of the tool
	/// @returns current holder
	const HolderDefinition& GetHolder() const;

	/// Get arbor diameter
	///
	/// This function returns the arbor diameter of the tool
	/// @returns current arbor diameter
	const ArborDefinition& GetArbor() const;

	/// Get tool diameter
	///
	/// This function returns the diameter of the tool
	///	@returns current tool diameter
	virtual const double GetToolDiameter() const = 0;


	/// @name Visitor pattern
	/// @{
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;
	/// @}

protected:
	const mwRevolvedTool& operator=(const mwRevolvedTool& toCopy);

	bool operator==(const mwRevolvedTool& toCompare) const;

	/// Scale the tool to new metric system
	///	@param units the new metric system to be used
	///	@param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);

#pragma warning(push)
#pragma warning(disable : 4251)
	/// Arbor part of the tool
	ArborDefinition mArbor;
	/// Holder part of the tool
	HolderDefinition mHolder;
#pragma warning(pop)

private:
	/// Copies data
	void Copy(const mwRevolvedTool& rToCopy);

	/// Validate the new holder
	///	@param newHolder the holder to be checked
	virtual void ValidateHolder(const HolderDefinition& newHolder);

	/// Validate the new arbor
	///	@param newArbor the arbor to be checked
	virtual void ValidateArbor(const ArborDefinition& newArbor);

	struct HolderValidator: public SolidDefinitionVisitorGetter
	{
		virtual void Visit(const SolidDefinition& visitor);
		virtual void Visit(const RevolvedSolidDefinition& visitor);
		virtual void Visit(const ExtrudedSolidDefinition& visitor);
		virtual void Visit(const MeshSolidDefinition& visitor);
		virtual void Visit(const TurningSolidDefinition& visitor);
		virtual void Visit(const WireSolidDefinition& visitor);
		virtual void Visit(const ContourTurningSolidDefinition& visitor);
		virtual void Visit(const PrimeTurningSolidDefinition& visitor);
		virtual void Visit(const ThreadTapSolidDefinition& visitor);
	};

	struct ArborValidator: public SolidDefinitionVisitorGetter
	{
		virtual void Visit(const SolidDefinition& visitor);
		virtual void Visit(const RevolvedSolidDefinition& visitor);
		virtual void Visit(const ExtrudedSolidDefinition& visitor);
		virtual void Visit(const MeshSolidDefinition& visitor);
		virtual void Visit(const TurningSolidDefinition& visitor);
		virtual void Visit(const ContourTurningSolidDefinition& visitor);
		virtual void Visit(const PrimeTurningSolidDefinition& visitor);
		virtual void Visit(const WireSolidDefinition& visitor);
		virtual void Visit(const ThreadTapSolidDefinition& visitor);
	};
};

typedef misc::mwAutoPointer<mwRevolvedTool> mwRevolvedToolPtr;
}  // namespace cadcam
#endif  //	MW_MWREVOLVEDTOOL_HPP_
