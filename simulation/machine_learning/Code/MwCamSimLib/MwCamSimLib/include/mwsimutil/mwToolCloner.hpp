// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLCLONER_HPP_
#define MW_MWTOOLCLONER_HPP_
#include "mwAutoPointer.hpp"
#include "mwBarrelAdvancedMill.hpp"
#include "mwBarrelBarrSecMill.hpp"
#include "mwBarrelDProfMill.hpp"
#include "mwBarrelLensMill.hpp"
#include "mwBarrelMill.hpp"
#include "mwBarrelTangentMill.hpp"
#include "mwBarrelTangentMillConicalShaft.hpp"
#include "mwBarrelTaperMill.hpp"
#include "mwBoreBar.hpp"
#include "mwBullMill.hpp"
#include "mwCSink.hpp"
#include "mwChainSawTool.hpp"
#include "mwChamferMill.hpp"
#include "mwChiselingTool.hpp"
#include "mwCntrBore.hpp"
#include "mwContourTurningTool.hpp"
#include "mwConvexTipMill.hpp"
#include "mwCtrDrill.hpp"
#include "mwDiamondTurningTool.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwDoveMill.hpp"
#include "mwDrill.hpp"
#include "mwEndMill.hpp"
#include "mwFaceMill.hpp"
#include "mwGenericExtrudedTool.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwGenericSawingTool.hpp"
#include "mwGenericTool.hpp"
#include "mwGrooveTurningTool.hpp"
#include "mwHexagonalTurningTool.hpp"
#include "mwLolMill.hpp"
#include "mwOctagonalTurningTool.hpp"
#include "mwOpticDiamondTool.hpp"
#include "mwParallelogramTurningTool.hpp"
#include "mwPentagonalTurningTool.hpp"
#include "mwPotGrinderTool.hpp"
#include "mwPrimeTurningTool.hpp"
#include "mwRadMill.hpp"
#include "mwReamer.hpp"
#include "mwRoundTurningTool.hpp"
#include "mwSlotMill.hpp"
#include "mwSpeedShapeTool.hpp"
#include "mwSphereMill.hpp"
#include "mwSpotDrill.hpp"
#include "mwSquareTurningTool.hpp"
#include "mwTapLH.hpp"
#include "mwTapRH.hpp"
#include "mwTaperMill.hpp"
#include "mwThreadTapTool.hpp"
#include "mwThreadTriangleTurningTool.hpp"
#include "mwTool.hpp"
#include "mwTriangleTurningTool.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwWireTool.hpp"
#include "mwThreadMillSingleFormTool.hpp"

namespace cadcam
{
/// This class clones a tool derived from a mwTool object


class MW_5AXUTIL_API mwToolCloner: public cadcam::mwToolVisitor
{
public:
	/// Class constructor
	///
	/// @param toolDest reference to an existing autopointer to an mwTool object
	mwToolCloner(mwTool::Ptr& toolDest);

	/// Class destructor
	virtual ~mwToolCloner() {}

	/// Visit method for a mwTool object
	///
	///	@param visitor a reference to a mwTool object
	///	@throws an exception, since mwTool is an abstract class
	virtual void Visit(const mwTool& visitor);

	/// Visit method for a mwBoreBar tool, that is a concrete tool
	///
	/// Creates a new object of type mwBoreBar, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwBoreBar object that will be cloned
	virtual void Visit(const mwBoreBar& visitor);

	/// Visit method for a mwBullMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBullMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwBullMill object that will be cloned
	virtual void Visit(const mwBullMill& visitor);

	/// Visit method for a mwChamferMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwChamferMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwChamferMill object that will be cloned
	virtual void Visit(const mwChamferMill& visitor);

	/// Visit method for a mwCntrBore tool, that is a concrete tool
	///
	/// Creates a new object of type mwCntrBore, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwCntrBore object that will be cloned
	virtual void Visit(const mwCntrBore& visitor);

	/// Visit method for a mwCSink tool, that is a concrete tool
	///
	/// Creates a new object of type mwCSink, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwCSink object that will be cloned
	virtual void Visit(const mwCSink& visitor);

	/// Visit method for a mwCtrDrill tool, that is a concrete tool
	///
	/// Creates a new object of type mwCtrDrill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwCtrDrill object that will be cloned
	virtual void Visit(const mwCtrDrill& visitor);

	/// Visit method for a mwDoveMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwDoveMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwDoveMill object that will be cloned
	virtual void Visit(const mwDoveMill& visitor);

	/// Visit method for a mwDrill tool, that is a concrete tool
	///
	/// Creates a new object of type mwDrill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwDrill object that will be cloned
	virtual void Visit(const mwDrill& visitor);

	/// Visit method for a mwEndMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwEndMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwEndMill object that will be cloned
	virtual void Visit(const mwEndMill& visitor);

	/// Visit method for a mwFaceMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwFaceMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwFaceMill object that will be cloned
	virtual void Visit(const mwFaceMill& visitor);

	/// Visit method for a mwLolMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwLolMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwLolMill object that will be cloned
	virtual void Visit(const mwLolMill& visitor);

	/// Visit method for a mwRadMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwRadMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwRadMill object that will be cloned
	virtual void Visit(const mwRadMill& visitor);

	/// Visit method for a mwReamer tool, that is a concrete tool
	///
	/// Creates a new object of type mwReamer, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwReamer object that will be cloned
	virtual void Visit(const mwReamer& visitor);

	/// Visit method for a mwSlotMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwSlotMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwSlotMill object that will be cloned
	virtual void Visit(const mwSlotMill& visitor);

	/// Visit method for a mwSphereMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwSphereMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwSphereMill object that will be cloned
	virtual void Visit(const mwSphereMill& visitor);

	/// Visit method for a mwSpotDrill tool, that is a concrete tool
	///
	/// Creates a new object of type mwSpotDrill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwSpotDrill object that will be cloned
	virtual void Visit(const mwSpotDrill& visitor);

	/// Visit method for a mwTaperMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwTaperMill, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwTaperMill object that will be cloned
	virtual void Visit(const mwTaperMill& visitor);

	/// Visit method for a mwTapLH tool, that is a concrete tool
	///
	/// Creates a new object of type mwTapLH, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwTapLH object that will be cloned
	virtual void Visit(const mwTapLH& visitor);

	/// Visit method for a mwTapRH tool, that is a concrete tool
	///
	/// Creates a new object of type mwTapRH, and make it an exact copy of the passed object
	/// @param visitor a const reference to an existing mwTapRH object that will be cloned
	virtual void Visit(const mwTapRH& visitor);

	/// Visit method for a mwBarrelMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelMill, and make it an exact copy of the passed object
	/// @param visitor a const reference to an existing mwBarrelMill object that will be cloned
	virtual void Visit(const mwBarrelMill& visitor);

	/// Visit method for a mwBarrelAdvancedMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelAdvancedMill, and make it an exact copy of the passed
	/// object
	///	@param visitor a const reference to an existing mwBarrelAdvancedMill object that will be
	///cloned
	virtual void Visit(const mwBarrelAdvancedMill& visitor);

	/// Visit method for a mwBarrelBarrSecMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelBarrSecMill, and make it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwBarrelBarrSecMill object that will be
	/// cloned
	virtual void Visit(const mwBarrelBarrSecMill& visitor);

	/// Visit method for a mwBarrelDProfMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelDProfMill, and make it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwBarrelDProfMill object that will be cloned
	virtual void Visit(const mwBarrelDProfMill& visitor);

	/// Visit method for a mwBarrelTangentMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelTangentMill, and make it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwBarrelTangentMill object that will be
	/// cloned
	virtual void Visit(const mwBarrelTangentMill& visitor);

	/// Visit method for a mwBarrelTangentMillConicalShaft tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelTangentMillConicalShaft, and make it an exact copy of
	/// the passed object
	/// @param visitor a const reference to an existing mwBarrelTangentMillConicalShaft object that
	/// will be cloned
	virtual void Visit(const mwBarrelTangentMillConicalShaft& visitor);


	/// Visit method for a mwBarrelTaperMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelTaperMill, and make it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwBarrelTaperMill object that will be cloned
	virtual void Visit(const mwBarrelTaperMill& visitor);


	/// Visit method for a mwBarrelLensMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwBarrelLensMill, and make it an exact copy of the passed
	/// object
	/// @param visitor a const reference to an existing mwBarrelLensMill object that will be cloned
	virtual void Visit(const mwBarrelLensMill& visitor);


	/// Visit method for a mwConvexTipMill tool, that is a concrete tool
	///
	/// Creates a new object of type mwConvexTipMill, and make it an exact copy of the passed object
	/// @param visitor a const reference to an existing mwConvexTipMill object that will be cloned
	virtual void Visit(const mwConvexTipMill& visitor);


	/// Visit method for a mwGenericRevolvedTool tool, that is a concrete tool
	///
	/// Creates a new object of type mwGenericRevolvedTool, and make it an exact copy of the passed
	/// object
	///	@param visitor a const reference to an existing mwGenericRevolvedTool object that will be
	///cloned
	virtual void Visit(const mwGenericRevolvedTool& visitor);

	/// Visit method for a mwGenericExtrudedTool tool, that is a concrete tool
	///
	/// Creates a new object of type mwGenericExtrudedTool, and make it an exact copy of the passed
	/// object
	///	@param visitor a const reference to an existing mwGenericExtrudedTool object that will be
	///cloned
	virtual void Visit(const mwGenericExtrudedTool& visitor);

	/// Visit method for a mwWireTool tool, that is a concrete tool
	///
	/// Creates a new object of type mwWireTool, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwWireTool object that will be cloned
	virtual void Visit(const mwWireTool& visitor);

	/// Visit method for a mwGenericSawingTool tool, that is a concrete tool
	///
	/// Creates a new object of type mwGenericSawingTool, and make it an exact copy of the passed
	/// object
	///	@param visitor a const reference to an existing mwGenericSawingTool object that will be
	///cloned
	virtual void Visit(const mwGenericSawingTool& visitor);

	/// Visit method for a mwChainSawTool tool, that is a concrete tool
	///
	/// Creates a new object of type mwChainSawTool, and make it an exact copy of the passed object
	///	@param visitor a const reference to an existing mwChainSawTool object that will be cloned
	virtual void Visit(const mwChainSawTool& visitor);

	virtual void Visit(const mwTriangleTurningTool& toVisit);
	virtual void Visit(const mwParallelogramTurningTool& toVisit);
	virtual void Visit(const mwSquareTurningTool& toVisit);
	virtual void Visit(const mwPentagonalTurningTool& toVisit);
	virtual void Visit(const mwRoundTurningTool& toVisit);
	virtual void Visit(const mwOctagonalTurningTool& toVisit);
	virtual void Visit(const mwHexagonalTurningTool& toVisit);
	virtual void Visit(const mwGrooveTurningTool& toVisit);
	virtual void Visit(const mwDiamondTurningTool& toVisit);
	virtual void Visit(const mwContourTurningTool& toVisit);
	virtual void Visit(const mwThreadTriangleTurningTool& toVisit);
#ifndef MW_USE_VS2008_COMPATIBILITY
	virtual void Visit(const mwPrimeTurningTool& toVisit);
#endif

	virtual void Visit(const mwGenericTool& toVisit);

	virtual void Visit(const mwChiselingTool& toVisit);

	virtual void Visit(const mwOpticDiamondTool& toVisit);

	virtual void Visit(const mwSpeedShapeTool& toVisit);

	virtual void Visit(const mwPotGrinderTool& toVisit);
	virtual void Visit(const mwThreadTapTool& toVisit);
	virtual void Visit(const mwThreadMillSingleFormTool& toVisit);

private:
	mwToolCloner& operator=(mwToolCloner&);  // avoid warning C4512
	/// Reference to an existing autopointer to an mwTool.
	/// After calling Visit method for a concrete tool, this autopointer will contain the
	/// address of a new created and cloned tool, obtained from the tool passed on Visit method
	mwTool::Ptr& ptrToTool;
};
}  // namespace cadcam
#endif  //	MW_MWTOOLCLONER_HPP_
