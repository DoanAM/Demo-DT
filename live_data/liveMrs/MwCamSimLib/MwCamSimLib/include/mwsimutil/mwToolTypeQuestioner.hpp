// (C) 2008-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTOOLTYPEQUESTIONER_HPP_
#define MW_MWTOOLTYPEQUESTIONER_HPP_
#include "mwTool.hpp"


namespace cadcam
{
class mwTool;


class MW_5AXUTIL_API mwToolTypes
{
public:
	enum TOOL_TYPE
	{
		TTCENTER_DRILL = 1,
		TTSPOT_DRILL = 2,
		TTDRILL = 3,
		TTRIGHT_HAND_TAP = 4,
		TTLEFT_HAND_TAP = 5,
		TTREAMER = 6,
		TTBORING_BAR = 7,
		TTCOUNTER_BORE = 8,
		TTCOUNTER_SINK = 9,
		TTEND_MILL_FLAT = 10,
		TTEND_MILL_SPHER = 11,
		TTCHAMFER_MILL = 12,
		TTFACE_MILL = 13,
		TTSLOT_MILL = 14,
		TTRADIUS_MILL = 15,
		TTDOVETAIL_MILL = 16,
		TTTAPERED_MILL = 17,
		TTLOLLIPOP_MILL = 18,
		TTEND_MILL_BULLNOSE = 19,
		TTBARREL_MILL = 20,
		TTCONVEX_TIP_MILL = 21,
		TTTRIANGLE_TURNING = 22,
		TTDIAMOND_TURNING = 23,
		TTPARALLELOGRAM_TURNING = 24,
		TTSQUARE_TURNING = 25,
		TTPENTAGONAL_TURNING = 26,
		TTROUND_TURNING = 27,
		TTOCTAGONAL_TURNING = 28,
		TTHEXAGONAL_TURNING = 29,
		TTGENERIC_REVOLVED = 30,
		TTGROOVE_TURNING = 31,
		TTGENERIC_EXTRUDED = 40,
		TTWIRE = 41,
		TTGENERIC_SAWING_TOOL = 42,
		TTCHAIN_SAW_TOOL = 43,
		TTLASER = 44,
		TTGENERIC_TOOL = 45,
		TTBARREL_ADVANCED_MILL = 46,

		TTLATHE = TTGENERIC_EXTRUDED,
		TTOPTIC_DIAMOND = 47,
		TTSPEEDSHAPE_TOOL = 48,

		TTCONTOUR_TURNING = 49,
		TTBARREL_TANGENT_TO_SHAFT = 50,
		TTBARREL_LENS_MILL = 51,
		TTBARREL_TAPER_MILL = 52,
		TTBARREL_SECTION_MILL = 53,
		TTBARREL_DPROFILE_MILL = 54,

		TTPOT_GRINGER_TOOL = 55,
		TTPOT_GRINDER_TOOL = TTPOT_GRINGER_TOOL,

		TTTHREAD_TAP_TOOL = 56,
		TTBARREL_TANGENT_TO_CONICAL_SHAFT = 57,

		TTCHISELING_TOOL = 58,
		TTTHREAD_TRIANGLE_TURNING = 59,
		TTPRIME_TURNING = 60,
		TTTHREAD_MILL_SINGLE_FORM_TOOL = 61
	};

	enum TOOL_BRANCH
	{
		TB_REVOLVED = 0,
		TB_EXTRUDED = 1,
		TB_WIRE = 2,
		TB_SAW = 3,
		TB_OPTIC_DIAMOND = 4,
		TB_SPEEDSHAPE = 5,
		TB_CHISELING = 6,
		TB_GENERIC = 20
	};

	enum TOOL_REPRESENTATION
	{
		TR_GENERIC = 0,
		TR_TYPED = 1
	};
};

// typedef mwToolTypes::TOOL_TYPE TOOL_TYPE;


class mwToolFinder;
class MW_5AXUTIL_API mwToolTypeFinder
{
public:
	mwToolTypeFinder(const mwTool& tool);
	mwToolTypeFinder();

	const mwToolTypes::TOOL_TYPE GetToolType() const;
	const mwToolTypes::TOOL_BRANCH GetToolBranch() const;
	const mwToolTypes::TOOL_REPRESENTATION GetToolRepresentation() const;

	const mwToolTypes::TOOL_TYPE GetToolType(const mwTool& tool);
	const mwToolTypes::TOOL_BRANCH GetToolBranch(const mwTool& tool);
	const mwToolTypes::TOOL_REPRESENTATION GetToolRepresentation(const mwTool& tool);

	~mwToolTypeFinder();

private:
	mwToolTypes::TOOL_TYPE m_type;
	mwToolTypes::TOOL_BRANCH m_branch;
	mwToolTypes::TOOL_REPRESENTATION m_representation;
	bool m_visited;
	mwToolFinder* finder;
};


class MW_5AXUTIL_API mwToolTypeQuestioner
{
public:
	static const bool IsBall(const double toolDiameter, const double cornerRadius);
	static const bool IsFlat(const double cornerRadius);
	static const bool IsBullNose(const double toolDiameter, const double cornerRadius);

	// mwToolTypeFinder should be used instead of the following, if possible
	static bool IsRevolvedTool(const mwTool& tool);
	static bool IsLatheTool(const mwTool& tool);
	static bool IsWireTool(const mwTool& tool);
	static bool IsSawingTool(const mwTool& tool);
	static bool IsTypedExtrudedTool(const mwTool& tool);
	static bool IsOpticDiamondTool(const mwTool& tool);
	static bool IsChiselingTool(const mwTool& tool);
	static bool IsGenericRevolvedTool(const mwTool& tool);
	static bool IsSpeedShapeTool(const mwTool& tool);
	static bool IsBarrelTangentToConeTool(const mwTool& tool);
	static bool ToolsHaveSameType(const mwTool& tool1, const mwTool& tool2);
	static bool IsBarrelTangentToShaftTool(const mwTool& tool);

private:
	/// Constructor not allowed since it's a static class
	mwToolTypeQuestioner();
};


}  // namespace cadcam
#endif  //	MW_MWTOOLTYPEQUESTIONER_HPP_
