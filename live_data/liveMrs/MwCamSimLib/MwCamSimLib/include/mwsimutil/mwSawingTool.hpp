// (C) 2012-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWSAWINGTOOL_HPP_
#define MW_MWSAWINGTOOL_HPP_
namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc

#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwTool.hpp"


namespace cadcam
{
class mwSawingToolVisitor;

/// Definition of a class for tool definition
///
/// This class defines a basis class for all tools
///	used in cam operations
class MW_5AXUTIL_API mwSawingTool: public mwTool
{
public:
	typedef misc::mwAutoPointer<mwSawingTool> Ptr;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwSolidDefinition<double> SolidDefinition;
	typedef mwExtrudedSolidDefinition<double> ExtrudedSolidDefinition;
	typedef mwMeshSolidDefinition<double> MeshSolidDefinition;
	typedef mwTurningSolidDefinition<double> TurningSolidDefinition;
	typedef mwWireSolidDefinition<double> WireSolidDefinition;
	typedef mwSolidDefinitionVisitorGetter<double> SolidDefinitionVisitorGetter;
	typedef mwRevolvedSolidDefinition<double> RevolvedSolidDefinition;
	typedef mwContourTurningSolidDefinition<double> ContourTurningSolidDefinition;
	typedef mwPrimeTurningSolidDefinition<double> PrimeTurningSolidDefinition;
	typedef mwThreadTapSolidDefinition<double> ThreadTapSolidDefinition;

	//###################### Enums and Typedefs      ##############################
	/// Destructor
	virtual ~mwSawingTool() {}

	/// Constructor
	///	@param holder holder for this tool
	///	@param newArbor arbor for this tool
	///	@param units metric/inches system to be used for this tool
	mwSawingTool(
		const HolderDefinition& holder,
		const ArborDefinition& newArbor,
		const double newBladeThickness,
		const Units units);

	mwSawingTool(const HolderDefinition& holder, const double newBladeThickness, const Units units);

	///  Copy Constructor
	///	@param toCopy tool to be copied
	mwSawingTool(const mwSawingTool& toCopy);

	/// Get holder
	///
	/// This function returns the holder of the tool
	/// @returns current holder
	const HolderDefinition& GetHolder() const;

	/// Get arbor definition
	///
	/// This function returns the arbor definition of the tool
	///	@returns current arbor definition
	const ArborDefinition& GetArbor() const;

	/// Get blade thickness
	///
	/// Returns  blade thickness
	///	@returns  blade thickness
	const double GetBladeThickness() const;
	//#################### Visitor scheme ########################################
	/// Visitor pattern
	/// @param visitor the visitor
	void virtual AcceptVirtual(mwToolBranchVisitor& visitor) const;

	/// Visitor pattern
	///	@param visitor the visitor
	void virtual AcceptVirtual(mwToolVisitor& visitor) const;

protected:
	//########################## Operators ########################################

	/// Assignment operator
	///
	/// Assigns one tool object to another
	/// @param toCopy tool to copy the information from
	/// @returns current tool with copied information
	const mwSawingTool& operator=(const mwSawingTool& toCopy);

	/// Equality operator
	///
	/// Are given tools equal?
	/// @param toCompare tool to compare the current tool with
	/// @returns <b>true</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwSawingTool& toCompare) const;

	/// Scale the tool to new metric system
	///	@param units the new metric system to be used
	///	@param scaleFactor the scale factor to be used when scaling the dimensions
	virtual void Scale(const Units units, const double& scaleFactor);

	/// Class members
	HolderDefinition m_holder;
	ArborDefinition m_arbor;
	double m_bladeThickness;

private:
	/// Copies data from another mwSawingTool object to this one (member by member)
	///
	///	@param rToCopy is object to copy data from
	void Copy(const mwSawingTool& rToCopy);

	/// Validate the new holder
	///	@param newHolder the holder to be checked
	virtual void ValidateHolder(const HolderDefinition& newHolder);

	/// Validates blade thickness for the tool
	///
	///	@param bladeThickness is tool blade thickness to be validated
	void ValidateBladeThickness(const double bladeThickness) const;

	/// Helper class for holder validation
	struct HolderValidator: public SolidDefinitionVisitorGetter
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

}  // namespace cadcam
#endif  //	MW_MWSAWINGTOOL_HPP_
