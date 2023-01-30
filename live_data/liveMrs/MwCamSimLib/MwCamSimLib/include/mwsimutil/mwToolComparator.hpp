// (C) 2012-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLCOMPARATOR_HPP_
#define MW_MWTOOLCOMPARATOR_HPP_
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
#include "mwDllImpExpDef.hpp"
#include "mwDoveMill.hpp"
#include "mwDrill.hpp"
#include "mwEndMill.hpp"
#include "mwFaceMill.hpp"
#include "mwGenericExtrudedTool.hpp"
#include "mwGenericRevolvedTool.hpp"
#include "mwGenericSawingTool.hpp"
#include "mwGenericTool.hpp"
#include "mwLolMill.hpp"
#include "mwOpticDiamondTool.hpp"
#include "mwPotGrinderTool.hpp"
#include "mwPrimeTurningTool.hpp"
#include "mwRadMill.hpp"
#include "mwReamer.hpp"
#include "mwSlotMill.hpp"
#include "mwSpeedShapeTool.hpp"
#include "mwSphereMill.hpp"
#include "mwSpotDrill.hpp"
#include "mwTapLH.hpp"
#include "mwTapRH.hpp"
#include "mwTaperMill.hpp"
#include "mwThreadTapTool.hpp"
#include "mwThreadTriangleTurningTool.hpp"
#include "mwTool.hpp"
#include "mwToolTypeQuestioner.hpp"
#include "mwTypedExtrudedTool.hpp"
#include "mwWireTool.hpp"
#include "mwThreadMillSingleFormTool.hpp"

namespace cadcam
{
class MW_5AXUTIL_API mwToolComparator: public mwToolVisitor
{
public:
	mwToolComparator(const mwTool& tool1, const mwTool& tool2);
	~mwToolComparator();

	bool Compare();

	/// Visit const mwTool
	virtual void Visit(const mwTool& visitor);
	/// Visit const mwBoreBar
	virtual void Visit(const mwBoreBar& visitor);
	/// Visit const mwBullMill
	virtual void Visit(const mwBullMill& visitor);
	/// Visit const mwChamferMill
	virtual void Visit(const mwChamferMill& visitor);
	/// Visit const mwCntrBore
	virtual void Visit(const mwCntrBore& visitor);
	/// Visit const mwCSink
	virtual void Visit(const mwCSink& visitor);
	/// Visit const mwCtrDrill
	virtual void Visit(const mwCtrDrill& visitor);
	/// Visit const mwDoveMill
	virtual void Visit(const mwDoveMill& visitor);
	/// Visit const mwDrill
	virtual void Visit(const mwDrill& visitor);
	/// Visit const mwEndMill
	virtual void Visit(const mwEndMill& visitor);
	/// Visit const mwFaceMill
	virtual void Visit(const mwFaceMill& visitor);
	/// Visit const mwLolMill
	virtual void Visit(const mwLolMill& visitor);
	/// Visit const mwRadMill
	virtual void Visit(const mwRadMill& visitor);
	/// Visit const mwReamer
	virtual void Visit(const mwReamer& visitor);
	/// Visit const mwSlotMill
	virtual void Visit(const mwSlotMill& visitor);
	/// Visit const mwSphereMill
	virtual void Visit(const mwSphereMill& visitor);
	/// Visit const mwSpotDrill
	virtual void Visit(const mwSpotDrill& visitor);
	/// Visit const mwTaperMill
	virtual void Visit(const mwTaperMill& visitor);
	/// Visit const mwTapLH
	virtual void Visit(const mwTapLH& visitor);
	/// Visit const mwTapRH
	virtual void Visit(const mwTapRH& visitor);
	/// Visit const mwBarrelMill
	virtual void Visit(const mwBarrelMill& visitor);
	/// Visit const mwBarrelAdvancedMill
	virtual void Visit(const mwBarrelAdvancedMill& visitor);
	/// Visit const mwBarrelBarrSecMill
	virtual void Visit(const mwBarrelBarrSecMill& visitor);
	/// Visit const mwBarrelDProfMill
	virtual void Visit(const mwBarrelDProfMill& visitor);
	/// Visit const mwBarrelLensMill
	virtual void Visit(const mwBarrelLensMill& visitor);
	/// Visit const mwBarrelTangentMill
	virtual void Visit(const mwBarrelTangentMill& visitor);
	/// Visit const mwBarrelTangentMillConicalShaft
	virtual void Visit(const mwBarrelTangentMillConicalShaft& visitor);
	/// Visit const mwBarrelTaperMill
	virtual void Visit(const mwBarrelTaperMill& visitor);
	/// Visit const mwConvexTipMill
	virtual void Visit(const mwConvexTipMill& visitor);
	/// Visit const mwThreadTapTool
	virtual void Visit(const mwThreadTapTool& visitor);
	/// Visit const mwGenericRevolvedTool
	virtual void Visit(const mwGenericRevolvedTool& visitor);
	/// Visit const mwGenericExtrudedTool
	virtual void Visit(const mwGenericExtrudedTool& visitor);
	/// Visit const mwWireTool
	virtual void Visit(const mwWireTool& visitor);
	/// Visit const mwGenericSawingTool
	virtual void Visit(const mwGenericSawingTool& visitor);
	/// Visit const mwChainSawTool
	virtual void Visit(const mwChainSawTool& visitor);
	/// Visit const mwOpticDiamondTool
	virtual void Visit(const mwChiselingTool& visitor);
	/// Visit const mwOpticDiamondTool
	virtual void Visit(const mwOpticDiamondTool& visitor);
	/// Visit const mwSpeedShapeTool
	virtual void Visit(const mwSpeedShapeTool& visitor);
	/// Visit const mwPotGrinderTool
	virtual void Visit(const mwPotGrinderTool& visitor);
	/// Visit const mwThreadMillSingleFormTool
	virtual void Visit(const mwThreadMillSingleFormTool& visitor);

	/// Visit typed extruded tools
	virtual void Visit(const mwTriangleTurningTool& visitor);
	virtual void Visit(const mwParallelogramTurningTool& visitor);
	virtual void Visit(const mwSquareTurningTool& visitor);
	virtual void Visit(const mwPentagonalTurningTool& visitor);
	virtual void Visit(const mwRoundTurningTool& visitor);
	virtual void Visit(const mwOctagonalTurningTool& visitor);
	virtual void Visit(const mwHexagonalTurningTool& visitor);
	virtual void Visit(const mwGrooveTurningTool& visitor);
	virtual void Visit(const mwDiamondTurningTool& visitor);
	virtual void Visit(const mwContourTurningTool& visitor);
	virtual void Visit(const mwThreadTriangleTurningTool& visitor);
#ifndef MW_USE_VS2008_COMPATIBILITY
	virtual void Visit(const mwPrimeTurningTool& visitor);
#endif

	virtual void Visit(const mwGenericTool& visitor);

private:
	mwToolComparator& operator=(const mwToolComparator&);
	bool m_equal;
	const mwTool& m_tool1;
	const mwTool& m_tool2;
	typedef cadcam::mwToolTypes::TOOL_TYPE toolType;

	toolType m_firstToolType;
	bool m_firstToolTypeUnknown;

	template <class T>
	void ComparisonFunction(const T& visitor, toolType visitorType)
	{
		if (m_firstToolTypeUnknown)
		{
			m_firstToolTypeUnknown = false;
			m_firstToolType = visitorType;
			m_tool2.AcceptVirtual(*this);
		}
		else if (m_firstToolType == visitorType)
		{
			const T* unsafeFirstToolPtr = reinterpret_cast<const T*>(&m_tool1);
			m_equal = (visitor == *unsafeFirstToolPtr);
		}
		else
		{
			m_equal = false;
		}
	}
};
}  // namespace cadcam
#endif  //	MW_MWTOOLCOMPARATOR_HPP_
