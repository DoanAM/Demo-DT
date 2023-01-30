// (C) 2012-2019 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWTYPEDSAWINGTOOL_HPP_
#define MW_MWTYPEDSAWINGTOOL_HPP_
namespace misc
{
// Predefine for the exception class
class mwException;
}  // namespace misc

#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwSawingTool.hpp"


namespace cadcam
{
/// Definition of a class for tool definition
///
/// This class defines a basis class for all tools
///   used in cam operations
class MW_5AXUTIL_API mwTypedSawingTool: public mwSawingTool
{
public:
	//###################### Enums and Typedefs      ##############################
	enum cornerRadiusType
	{
		corner,
		full
	};

	typedef misc::mwAutoPointer<mwTypedSawingTool> Ptr;
	typedef mwSawingTool::HolderDefinition HolderDefinition;

	/// Destructor
	virtual ~mwTypedSawingTool(){};

	/// Constructor
	///	@param holder holder for this tool
	///	@param arbor arbor for this tool
	///	@param units metric/inches system to be used for this tool
	///	@param inHouseValidationForHolderAndArbor, implicitly on - temporary parameter,
	///		will be removed after reunifying arbor and holder validation handling for all tool types
	mwTypedSawingTool(
		const HolderDefinition& holder,
		const ArborDefinition& arbor,
		const double& newBladeThickness,
		const Units& units);


	/// Constructor
	///	@param holder holder for this tool
	///	@param units metric/inches system to be used for this tool
	///	@param inHouseValidationForHolderAndArbor, implicitly on - temporary parameter,
	///		will be removed after reunifying arbor and holder validation handling for all tool types
	mwTypedSawingTool(
		const HolderDefinition& holder, const double& newBladeThickness, const Units& units);

	virtual const bool HasAdvancedShoulderDefinition() const;


protected:
};


}  // namespace cadcam
#endif  //	MW_MWTYPEDSAWINGTOOL_HPP_
