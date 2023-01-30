// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOL_HPP_
#define MW_MWTOOL_HPP_
#include "mwArborDefinition.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwHolderDefinition.hpp"
#include "mwMeasurable.hpp"
#include "mwNonCuttingPartDefinition.hpp"

namespace misc
{
template <class T>
class mwAutoPointer;
}
namespace cadcam
{
class mwToolVisitor;
class mwToolBranchVisitor;
class mwBasicToolShaftAnalyser;
template <class T>
class mwHolderDefinition;
template <class T>
class mwArborDefinition;
template <class T>
class mwNonCuttingPartDefinition;
template <class T>
class mwCuttingPartDefinition;

/// @class mwTool mwTool.hpp
/// Defines a base class for all the tools used in CAM operations.
/// This one is used as an interface class for all the concrete tools in the hierarchy.
class MW_5AXUTIL_API mwTool: public measures::mwMeasurable
{
public:
	typedef misc::mwAutoPointer<mwTool> Ptr;
	typedef mwToolPartDefinition<double> ToolPartDefinition;
	typedef mwHolderDefinition<double> HolderDefinition;
	typedef mwArborDefinition<double> ArborDefinition;
	typedef mwNonCuttingPartDefinition<double> NonCuttingPartDefinition;
	typedef mwCuttingPartDefinition<double> CuttingPartDefinition;

	enum ToolPartFlags
	{
		TPF_CUTTING = 1,
		TPF_NONCUTTING = 2,
		TPF_ARBOR = 4,
		TPF_HOLDER = 8,
		TPF_ALL_EXCLUDING_HOLDER = TPF_CUTTING | TPF_NONCUTTING | TPF_ARBOR,
		TPF_ALL = TPF_ALL_EXCLUDING_HOLDER | TPF_HOLDER
	};

	/// Constructor
	/// @param units are the units that will be used for this tool (metric or inches).
	mwTool(const Units units);
	virtual ~mwTool();

	/// Get the tool holder.
	virtual const HolderDefinition& GetHolder() const = 0;
	/// Get the tool arbor
	virtual const ArborDefinition& GetArbor() const = 0;

	/// Get the length along tool of the selected tool part(s)
	///
	/// In other words, it returns the length along Z axis of the Bounding Box of the selected tool
	/// part(s).
	///	See GetToolPartBoundingBox for more details.
	double GetToolPartLength(const ToolPartFlags selection) const;

	/// Get the holder's length 
	const double GetHolderLength() const;

	/// Get the bounding box of selected tool part(s)
	///
	/// You may use | operator to do multiple selections eg: TPF_CUTTING | TPF_NONCUTTING for shaft
	/// bounding box of a mill tool.
	///	@note The bounding box only of selected parts is computed. eg:
	///GetToolPartBoundingBox(TPF_CUTTING | TPF_HOLDER) != GetToolPartBoundingBox(TPF_ALL)
	/// @note The bounding box is positioned inside the tool. eg:
	/// GetToolPartBoundingBox(TPF_HOLDER).GetMin() !=
	/// GetHolder().GetSolid().GetBoundingBox().GetMin()
	virtual mw3dBoundingBox<double> GetToolPartBoundingBox(const ToolPartFlags selection) const = 0;

	/// This function is used in the visitor scheme.
	void virtual AcceptVirtual(mwToolVisitor& virtualvisitor) const = 0;
	/// This function is used in the visitor scheme.
	void virtual AcceptVirtual(mwToolBranchVisitor& virtualvisitor) const = 0;

	MW_DEPRECATED("Deprecated since 2017.12. Use GetToolPartLength(TPF_CUTTING | TPF_NONCUTTING)")
	virtual const double GetShoulderLength() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetToolPartLength(TPF_ALL_EXCLUDING_HOLDER)")
	virtual const double GetOverallLength() const;
	MW_DEPRECATED("Deprecated since 2017.12. Use GetToolPartLength(TPF_CUTTING)")
	virtual const double GetFluteLength() const;

protected:
	/// Compare the tools
	/// @param toCompare is the tool whose parameters will be compared with the parameters of the
	/// current tool.
	/// @returns <b>true</b> if both tools contain the same parameters,
	/// <b>false</b> otherwise
	bool operator==(const mwTool& toCompare) const;

	/// Stack pass tool part over an existing stack bounding box, then enlarge that stack bounding
	/// box to fit the tool part also, then check if the user requested the part bounding box and
	/// enlarge the user requested bounding box to fit the stack part.
	void StackUpAndOrEnlargeBasedOnMatchingSelection(
		mw3dBoundingBox<double>& stackBB,
		mw3dBoundingBox<double>& userRequestedBB,
		const ToolPartFlags userRequestedParts,
		const ToolPartDefinition& partToBeStack,
		const ToolPartFlags partTypeToBeStack) const
	{
		StackUpAndOrEnlargeBasedOnMatchingSelection(
			stackBB,
			userRequestedBB,
			userRequestedParts,
			partToBeStack.GetSolid().GetBoundingBox3d(),
			partTypeToBeStack);
	}
	void StackUpAndOrEnlargeBasedOnMatchingSelection(
		mw3dBoundingBox<double>& stackBB,
		mw3dBoundingBox<double>& userRequestedBB,
		const ToolPartFlags userRequestedParts,
		const mw3dBoundingBox<double>& partToBeStack,
		const ToolPartFlags partTypeToBeStack) const;

	/// Assignment operator.
	/// This is hidden from the public section because mwTool is an abstract class.
	/// That is why assignment to mwTool objects is not explicitly permitted.
	/// @param src is the tool data to be copied.
	/// @returns A reference to the updated tool.
	mwTool& operator=(const mwTool& src)
	{
		mwMeasurable::operator=(src);
		return *this;
	}

private:
	/// Stack pass tool part over an existing bounding box, then enlarge that bounding box to fit
	/// the tool part also. returns the stacked(repositioned) bounding box of the tool part
	inline const mw3dBoundingBox<double> StackUpToolPart(
		mw3dBoundingBox<double>& bb2Enlarge, const ToolPartDefinition& toolPart) const
	{
		return StackUpToolPart(bb2Enlarge, toolPart.GetSolid().GetBoundingBox3d());
	}
	const mw3dBoundingBox<double> StackUpToolPart(
		mw3dBoundingBox<double>& bb2Enlarge, const mw3dBoundingBox<double>& toolPartBB) const;
};


class mwRevolvedTool;
class mwTool;
class mwBoreBar;
class mwBullMill;
class mwChamferMill;
class mwCntrBore;
class mwCSink;
class mwCtrDrill;
class mwDoveMill;
class mwDrill;
class mwEndMill;
class mwFaceMill;
class mwLolMill;
class mwRadMill;
class mwReamer;
class mwSlotMill;
class mwSphereMill;
class mwSpotDrill;
class mwTaperMill;
class mwTapLH;
class mwTapRH;
class mwBarrelMill;
class mwBarrelAdvancedMill;
class mwBarrelBarrSecMill;
class mwBarrelDProfMill;
class mwBarrelLensMill;
class mwBarrelTangentMill;
class mwBarrelTangentMillConicalShaft;
class mwBarrelTaperMill;
class mwConvexTipMill;
class mwGenericRevolvedTool;
class mwChainSawTool;
class mwGenericSawingTool;
class mwSawingTool;
class mwWireTool;
class mwExtrudedTool;
class mwGenericExtrudedTool;
class mwTriangleTurningTool;
class mwParallelogramTurningTool;
class mwSquareTurningTool;
class mwPentagonalTurningTool;
class mwRoundTurningTool;
class mwOctagonalTurningTool;
class mwHexagonalTurningTool;
class mwGrooveTurningTool;
class mwDiamondTurningTool;
class mwGenericTool;
class mwOpticDiamondTool;
class mwChiselingTool;
class mwSpeedShapeTool;
class mwPotGrinderTool;
class mwContourTurningTool;
class mwThreadTapTool;
class mwThreadTriangleTurningTool;
class mwPrimeTurningTool;
class mwThreadMillSingleFormTool;
typedef mwGenericExtrudedTool mwLatheTool;

/// @class mwToolVisitor
/// Use this class to implement additional virtual functions in the mwTool class. It uses the
/// 'visitor' scheme.
class MW_5AXUTIL_API mwToolVisitor
{
public:
	mwToolVisitor();
	virtual ~mwToolVisitor();
	virtual void Visit(const mwTool& visitor);
	virtual void Visit(const mwBoreBar& visitor);
	virtual void Visit(const mwBullMill& visitor);
	virtual void Visit(const mwChamferMill& visitor);
	virtual void Visit(const mwCntrBore& visitor);
	virtual void Visit(const mwCSink& visitor);
	virtual void Visit(const mwCtrDrill& visitor);
	virtual void Visit(const mwDoveMill& visitor);
	virtual void Visit(const mwDrill& visitor);
	virtual void Visit(const mwEndMill& visitor);
	virtual void Visit(const mwFaceMill& visitor);
	virtual void Visit(const mwLolMill& visitor);
	virtual void Visit(const mwRadMill& visitor);
	virtual void Visit(const mwReamer& visitor);
	virtual void Visit(const mwSlotMill& visitor);
	virtual void Visit(const mwSphereMill& visitor);
	virtual void Visit(const mwSpotDrill& visitor);
	virtual void Visit(const mwTaperMill& visitor);
	virtual void Visit(const mwTapLH& visitor);
	virtual void Visit(const mwTapRH& visitor);
	virtual void Visit(const mwBarrelMill& visitor);
	virtual void Visit(const mwBarrelAdvancedMill& visitor);
	virtual void Visit(const mwBarrelBarrSecMill& visitor);
	virtual void Visit(const mwBarrelDProfMill& visitor);
	virtual void Visit(const mwBarrelLensMill& visitor);
	virtual void Visit(const mwBarrelTangentMill& visitor);
	virtual void Visit(const mwBarrelTangentMillConicalShaft& visitor);
	virtual void Visit(const mwBarrelTaperMill& visitor);
	virtual void Visit(const mwConvexTipMill& visitor);
	virtual void Visit(const mwGenericRevolvedTool& visitor);
	virtual void Visit(const mwGenericExtrudedTool& visitor);
	virtual void Visit(const mwWireTool& visitor);
	virtual void Visit(const mwGenericSawingTool& visitor);
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
	virtual void Visit(const mwGenericTool& toVisit);
	virtual void Visit(const mwOpticDiamondTool& toVisit);
	virtual void Visit(const mwChiselingTool& toVisit);
	virtual void Visit(const mwSpeedShapeTool& toVisit);
	virtual void Visit(const mwPotGrinderTool& toVisit);
	virtual void Visit(const mwThreadTapTool& toVisit);
	virtual void Visit(const mwThreadTriangleTurningTool& toVisit);
	virtual void Visit(const mwContourTurningTool& toVisit);
	virtual void Visit(const mwPrimeTurningTool& toVisit);
	virtual void Visit(const mwThreadMillSingleFormTool& toVisit);

protected:
	/// Override this virtual method in a derived class to set up the default behavior for the Visit
	/// methods. By default, the exception "Visitor's method 'Visit' is not implemented" is thrown
	/// for non-overridden Visit methods.
	virtual void Default();
};


/// @class mwToolBranchVisitor
///  Use this class to implement additional virtual functions in the mwTool class. It uses the
///  'visitor' scheme.
class MW_5AXUTIL_API mwToolBranchVisitor
{
public:
	mwToolBranchVisitor();
	virtual ~mwToolBranchVisitor();
	virtual void Visit(const mwTool& visitor);
	virtual void Visit(const mwRevolvedTool& visitor);
	virtual void Visit(const mwExtrudedTool& visitor);
	virtual void Visit(const mwWireTool& visitor);
	virtual void Visit(const mwSawingTool& visitor);
	virtual void Visit(const mwGenericTool& visitor);
	virtual void Visit(const mwOpticDiamondTool& visitor);
	virtual void Visit(const mwChiselingTool& visitor);
	virtual void Visit(const mwSpeedShapeTool& visitor);
	virtual void Visit(const mwPotGrinderTool& toVisit);

protected:
	/// Override this virtual method in a derived class to set up the default behavior for Visit
	/// methods. By default, the exception "Visitor's method 'Visit' is not implemented" is thrown
	/// for non-overridden Visit methods.
	virtual void Default();

private:
	/*
	API change: The base class mwToolBranchvisitor has been changed to non-const Visit() functions.
	This allows derived classes to store gathered information in their member variables.

	To adapt the code to the the changed API, remove the 'const' keyword:

		void Visit(const mwTool&) const

	should be modified to

		void Visit(const mwTool&)

	It is now possible to access member variables inside classes derived from
	mwToolBranchvisitorwithout extra effort (e.g. mutable variables).
	*/
	virtual void Visit(const mwTool&) const {}
	virtual void Visit(const mwRevolvedTool&) const {}
	virtual void Visit(const mwExtrudedTool&) const {}
	virtual void Visit(const mwWireTool&) const {}
	virtual void Visit(const mwSawingTool&) const {}
	virtual void Visit(const mwGenericTool&) const {}
	virtual void Default() const {}
};
typedef misc::mwAutoPointer<mwTool> mwToolPtr;
typedef misc::mwAutoPointer<const mwTool> mwConstToolPtr;
}  //  namespace cadcam
// define it in the global space such as to work from any place
MW_5AXUTIL_API cadcam::mwTool::ToolPartFlags operator|(
	cadcam::mwTool::ToolPartFlags a, cadcam::mwTool::ToolPartFlags b);
#endif  //	MW_MWTOOL_HPP_
