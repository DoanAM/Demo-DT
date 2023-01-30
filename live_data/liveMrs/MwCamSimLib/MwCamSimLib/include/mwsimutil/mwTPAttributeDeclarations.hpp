// (C) 2011-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPATTRIBUTEDECLARATIONS_HPP_
#define MW_MWTPATTRIBUTEDECLARATIONS_HPP_
#include "mwAnyType.hpp"


namespace cadcam
{
class mwTPAttributeDeclarations
{
public:
	enum AC_GOUGE_FLAGS_ATTRIBUTE
	{
		TRIMMED_FLAG_NO = 0,
		TRIMMED_FLAG_BEGIN = 1,
		TRIMMED_FLAG_END = 2,
		TRIMMED_FLAG_BOTH = 3
	};

	enum AC_CORNER_TYPE_ATTRIBUTE
	{
		SHARP_CORNER = 0,
		ROUND_CORNER = 1,
		LEAD_CORNER = 2
	};

	enum AC_ADDITIVE_LINK_TYPE_ATTRIBUTE
	{
		ADDITIVE_LINK = 0,
		ADDITIVE_RETRACT = 1,
		ADDITIVE_INSIDE_LINK = 2,
		ADDITIVE_OUTSIDE_LINK = 3,
		ADDITIVE_VERTICAL_LINK = 4,
	};

	enum AC_ADDITIVE_CONTOUR_ORIENTATION_ATTRIBUTE
	{
		ADDITIVE_CONTOUR_CCW,
		ADDITIVE_CONTOUR_CW,
		ADDITIVE_CONTOUR_OPEN,
	};

	enum AC_HOLE_MAKING_THREAD_MILL_CONTOUR_TYPE_ATRIBUTE
	{
		SAFE_POINT,
		LINEAR_APPROACH,
		LINEAR_RETRACT,
		HELICAL_APPROACH,
		HELICAL_RETRACT,
		HELICAL_CUT,
		HELICAL_BREAKTHROUGH
	};
	// INSTRUCTIONS
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// WARNING!
	// 1. Thou shalt not add or remove a declaration without making the correspondent change in
	// ForEachAttributeDefinition().
	// 2. Thou shalt not change the type or the key of a type declaration.
	// 3. You may remove a type declaration, but don't change the keys of the others.
	// 4. If you want to break these rules, you need to update serialization/deserialization and
	// handle the version.
	// 5. Add the item in misc::mwstring
	// mwMPlusWriter::FunctorForEachAttributeToString::GetAttributesName(const int &attrIdx) and in
	// FunctorForEachCompare::GetAttributesName(const int& attrIdx) in mwTPUtils.cpp.
	// 6. Add the item to the enum in TPAttributes.hpp and extend the switch statements in
	// TPAttributes.cpp (mwWrapper).
	/* If you want to add functionality which uses the attributes, please avoid using them
	   explicitly, use instead functors and ForEachAttributeDefinition or ForEachAttribute, upon the
	   examples in this file. If you added anyway some places where the type declarations are used
	   explicitly, please update rule #1.*/
	typedef misc::mwAnyTypeDeclaration<1, bool> AC_IMPELLER_START_LEADING_SIDE;
	typedef misc::mwAnyTypeDeclaration<2, bool> AC_IMPELLER_START_TRAILING_SIDE;
	typedef misc::mwAnyTypeDeclaration<3, bool> AC_IMPELLER_AROUND_BLADE_CW;
	typedef misc::mwAnyTypeDeclaration<4, bool> AC_IMPELLER_AROUND_BLADE_CCW;
	typedef misc::mwAnyTypeDeclaration<5, bool> AC_IMPELLER_SLOT_CUT;
	typedef misc::mwAnyTypeDeclaration<6, bool> AC_IMPELLER_BLADE_TO_THE_LEFT;
	typedef misc::mwAnyTypeDeclaration<7, bool> AC_IMPELLER_BLADE_TO_THE_RIGHT;
	typedef misc::mwAnyTypeDeclaration<8, bool> AC_IMPELLER_INCOMPLETE_CUT;
	typedef misc::mwAnyTypeDeclaration<9, int> AC_IMPELLER_CUT_NUMBER;
	typedef misc::mwAnyTypeDeclaration<10, int> AC_IMPELLER_APPROACH_NUMBER;
	typedef misc::mwAnyTypeDeclaration<11, int> AC_IMPELLER_BLADE_NUMBER;
	typedef misc::mwAnyTypeDeclaration<12, int> AC_IMPELLER_SECTION_NUMBER;
	typedef misc::mwAnyTypeDeclaration<13, int> AC_IMPELLER_LAYER_NUMBER;
	typedef misc::mwAnyTypeDeclaration<14, int> AC_ROTATION_NUMBER;
	typedef misc::mwAnyTypeDeclaration<15, bool> AC_ORIGINAL_TOOLPATH;
	typedef misc::mwAnyTypeDeclaration<16, bool> AC_IMPELLER_FOLLOWING_CUT_IS_MISSING;
	typedef misc::mwAnyTypeDeclaration<17, bool> AC_IMPELLER_PREVIOUS_CUT_IS_MISSING;
	typedef misc::mwAnyTypeDeclaration<18, unsigned int> AC_GOUGE_FLAGS;
	typedef misc::mwAnyTypeDeclaration<19, unsigned int> AC_CORNER_TYPE;
	typedef misc::mwAnyTypeDeclaration<20, bool> AC_SWARF_WITHIN_BALANCE_THRESHOLD;
	typedef misc::mwAnyTypeDeclaration<21, bool> AC_TOOL_INSPECTION;
	typedef misc::mwAnyTypeDeclaration<22, bool> AC_NON_CUTTING;
	typedef misc::mwAnyTypeDeclaration<23, bool> AC_CRC_ON;
	typedef misc::mwAnyTypeDeclaration<24, bool> AC_IGNORE_FLUTE_COLLISION;
	typedef misc::mwAnyTypeDeclaration<25, bool> AC_OFFSETTED_CORNERS;
	typedef misc::mwAnyTypeDeclaration<26, bool> AC_GEODESIC_NORMALS_FLIPPED;
	typedef misc::mwAnyTypeDeclaration<27, bool> AC_GEODESIC_IS_CURVE;
	typedef misc::mwAnyTypeDeclaration<28, double> AC_GEODESIC_DISTANCE;
	typedef misc::mwAnyTypeDeclaration<29, bool> AC_SURFACE_PATHS_CUT_DIRECTION_CHANGE;
	typedef misc::mwAnyTypeDeclaration<30, unsigned int> AC_ORIGINAL_DRIVE_CURVE_INDEX;
	typedef misc::mwAnyTypeDeclaration<31, bool> AC_CURVE_REVERSED;
	typedef misc::mwAnyTypeDeclaration<32, bool> AC_IGNORE_TILTING_OPTIONS;
	typedef misc::mwAnyTypeDeclaration<33, bool> AC_IS_PILLAR_REMOVAL_HELIX;
	typedef misc::mwAnyTypeDeclaration<34, bool> AC_CIRCULAR_SAW_DEPTH;
	typedef misc::mwAnyTypeDeclaration<35, bool> AC_SPEEDSHAPE_INCOMPLETE_CUT;
	typedef misc::mwAnyTypeDeclaration<36, bool> AC_IMPELLER_FINAL_CUT;
	typedef misc::mwAnyTypeDeclaration<37, bool> AC_IMPELLER_INTERMEDIATE_CUT;
	typedef misc::mwAnyTypeDeclaration<38, unsigned int> AC_MACHINE_LIMIT_BREAK;
	typedef misc::mwAnyTypeDeclaration<39, bool> AC_IS_AR_DIG_MOVE;
	typedef misc::mwAnyTypeDeclaration<40, bool> AC_IMPELLER_BELOW_MIN_LEAD_ANGLE;
	typedef misc::mwAnyTypeDeclaration<41, bool> AC_ADDITIVE_PATH_CONTOUR;
	typedef misc::mwAnyTypeDeclaration<42, bool> AC_ADDITIVE_PATH_CONTOUR_BLOCKED;
	typedef misc::mwAnyTypeDeclaration<43, bool> AC_ADDITIVE_PATH_FILL_CONTOUR;
	typedef misc::mwAnyTypeDeclaration<44, bool> AC_ADDITIVE_PATH_FILL_CONTOUR_BLOCKED;
	typedef misc::mwAnyTypeDeclaration<45, bool> AC_ADDITIVE_PATH_INFILL_SEGMENT;
	typedef misc::mwAnyTypeDeclaration<46, bool> AC_ADDITIVE_PATH_INFILL_SEGMENT_RETRACT;
	typedef misc::mwAnyTypeDeclaration<47, bool> AC_ADDITIVE_REGION_VOLUME;
	typedef misc::mwAnyTypeDeclaration<48, bool> AC_ADDITIVE_REGION_DOWN_SKIN;
	typedef misc::mwAnyTypeDeclaration<49, bool> AC_ADDITIVE_REGION_UP_SKIN_REMELTING;
	typedef misc::mwAnyTypeDeclaration<50, bool> AC_ADDITIVE_REGION_UP_SKIN_RECOATING;
	typedef misc::mwAnyTypeDeclaration<51, bool> AC_ADDITIVE_REGION_CORE;
	typedef misc::mwAnyTypeDeclaration<52, bool> AC_ADDITIVE_REGION_SUPPORT;
	typedef misc::mwAnyTypeDeclaration<53, bool> AC_ADDITIVE_REGION_ADDITIONAL_VOLUME;
	typedef misc::mwAnyTypeDeclaration<54, int> AC_ADDITIVE_OFFSET_INDEX;
	typedef misc::mwAnyTypeDeclaration<55, double> AC_ADDITIVE_LASER_POWER;
	typedef misc::mwAnyTypeDeclaration<56, double> AC_ADDITIVE_LASER_SPEED;
	typedef misc::mwAnyTypeDeclaration<57, double> AC_ADDITIVE_LASER_FOCUS;
	typedef misc::mwAnyTypeDeclaration<58, unsigned int> AC_LINEBASED_UNROLLED_SLICE_IDX;
	typedef misc::mwAnyTypeDeclaration<59, unsigned int> AC_LINEBASED_SAME_CONTOUR_IDX;
	typedef misc::mwAnyTypeDeclaration<60, bool> AC_GEODESIC_LINK;
	typedef misc::mwAnyTypeDeclaration<61, bool> AC_GEODESIC_IS_OUTER_FINISH_PATH;
	typedef misc::mwAnyTypeDeclaration<62, bool> AC_ADDITIVE_REGION_UP_SKIN;
	typedef misc::mwAnyTypeDeclaration<63, bool> AC_ADDITIVE_REGION_SKIRT;
	typedef misc::mwAnyTypeDeclaration<64, bool> AC_ADDITIVE_REGION_BRIM;
	typedef misc::mwAnyTypeDeclaration<65, bool> AC_ADDITIVE_PATH_LINK;
	typedef misc::mwAnyTypeDeclaration<66, bool> AC_ADDITIVE_PATH_INSIDE_LINK;
	typedef misc::mwAnyTypeDeclaration<67, bool> AC_ADDITIVE_PATH_OUTSIDE_LINK;
	typedef misc::mwAnyTypeDeclaration<68, bool> AC_ADDITIVE_PATH_RETRACT;
	typedef misc::mwAnyTypeDeclaration<69, unsigned int> AC_MACHINE_REPOSITION_MOVES;
	typedef misc::mwAnyTypeDeclaration<70, unsigned int> AC_ADDITIVE_LAYER_IDX;
	typedef misc::mwAnyTypeDeclaration<71, unsigned int> AC_ADDITIVE_CONTOUR_IDX;
	typedef misc::mwAnyTypeDeclaration<72, double> AC_ADDITIVE_CONTOUR_HOLLOW_VOLUME;
	typedef misc::mwAnyTypeDeclaration<73, double> AC_ADDITIVE_PRINT_TIME;
	typedef misc::mwAnyTypeDeclaration<74, bool> AC_ADDITIVE_REGION_INITIAL_LAYER;
	typedef misc::mwAnyTypeDeclaration<75, bool> AC_ADDITIVE_REGION_IRONING;
	typedef misc::mwAnyTypeDeclaration<76, bool> AC_ADDITIVE_PATH_GAP_CONTOUR;
	typedef misc::mwAnyTypeDeclaration<77, bool> AC_SWARF_ARE_RAILS_INTERSECTING;
	typedef misc::mwAnyTypeDeclaration<78, int> AC_GEODESIC_LAYER_INDEX;
	typedef misc::mwAnyTypeDeclaration<79, bool> AC_FINAL_PROFILE;
	typedef misc::mwAnyTypeDeclaration<80, double> AC_KNIFE_GRINDING_DISTANCE_TO_TABLE_AXIS;
	typedef misc::mwAnyTypeDeclaration<81, double> AC_GENERIC_LIFTED_LEAD_MOVE;
	typedef misc::mwAnyTypeDeclaration<82, int> AC_GEODESIC_ORIGIN_GUIDE_CURVE_INDEX;
	typedef misc::mwAnyTypeDeclaration<83, int> AC_GEODESIC_IS_CUT;
	typedef misc::mwAnyTypeDeclaration<84, int> AC_GEODESIC_REGION_INDEX;
	typedef misc::mwAnyTypeDeclaration<85, bool> AC_IS_HELIX_LEAD_IN;
	typedef misc::mwAnyTypeDeclaration<86, bool> AC_ROUGH_LINK_WITHIN_GROUP;
	typedef misc::mwAnyTypeDeclaration<87, bool> AC_ROUGH_LINK_BETWEEN_GROUPS;
	typedef misc::mwAnyTypeDeclaration<88, unsigned int> AC_SPIRAL_TURNS;
	typedef misc::mwAnyTypeDeclaration<89, AC_ADDITIVE_LINK_TYPE_ATTRIBUTE> AC_ADDITIVE_LINK_TYPE;
	typedef misc::mwAnyTypeDeclaration<90, AC_ADDITIVE_CONTOUR_ORIENTATION_ATTRIBUTE> AC_ADDITIVE_CONTOUR_ORIENTATION;
	typedef misc::mwAnyTypeDeclaration<91, unsigned int> AC_ADDITIVE_PART_IDX;
	typedef misc::mwAnyTypeDeclaration<92, unsigned int> AC_ADDITIVE_BUILD_STYLE_IDX;
	typedef misc::mwAnyTypeDeclaration<93, double> AC_MULTIBLADE_SPINDLESPEED_MULTIPLIER;
	typedef misc::mwAnyTypeDeclaration<94, unsigned int> AC_LAYER_NUMBER;
	typedef misc::mwAnyTypeDeclaration<95, AC_HOLE_MAKING_THREAD_MILL_CONTOUR_TYPE_ATRIBUTE> AC_HOLE_MAKING_THREAD_MILL_CONTOUR_TYPE;
	typedef misc::mwAnyTypeDeclaration<96, double> AC_HOLE_MAKING_HELICAL_ARC_LEAD_RAMP_ANGLE;
	
	//^^^ ATTENTION: PLEASE READ THE INSTRUCTIONS BEFORE ADDING A LINE ^^^

	template <class Functor>
	void ForEachAttributeDefinition(Functor& functor) const
	{
		// Please make sure to call the functor in increasing order of the key
		Call<AC_IMPELLER_START_LEADING_SIDE>(functor);
		Call<AC_IMPELLER_START_TRAILING_SIDE>(functor);
		Call<AC_IMPELLER_AROUND_BLADE_CW>(functor);
		Call<AC_IMPELLER_AROUND_BLADE_CCW>(functor);
		Call<AC_IMPELLER_SLOT_CUT>(functor);
		Call<AC_IMPELLER_BLADE_TO_THE_LEFT>(functor);
		Call<AC_IMPELLER_BLADE_TO_THE_RIGHT>(functor);
		Call<AC_IMPELLER_INCOMPLETE_CUT>(functor);
		Call<AC_IMPELLER_CUT_NUMBER>(functor);
		Call<AC_IMPELLER_APPROACH_NUMBER>(functor);
		Call<AC_IMPELLER_BLADE_NUMBER>(functor);
		Call<AC_IMPELLER_SECTION_NUMBER>(functor);
		Call<AC_IMPELLER_LAYER_NUMBER>(functor);
		Call<AC_ROTATION_NUMBER>(functor);
		Call<AC_ORIGINAL_TOOLPATH>(functor);
		Call<AC_IMPELLER_FOLLOWING_CUT_IS_MISSING>(functor);
		Call<AC_IMPELLER_PREVIOUS_CUT_IS_MISSING>(functor);
		Call<AC_GOUGE_FLAGS>(functor);
		Call<AC_CORNER_TYPE>(functor);
		Call<AC_SWARF_WITHIN_BALANCE_THRESHOLD>(functor);
		Call<AC_TOOL_INSPECTION>(functor);
		Call<AC_NON_CUTTING>(functor);
		Call<AC_CRC_ON>(functor);
		Call<AC_IGNORE_FLUTE_COLLISION>(functor);
		Call<AC_OFFSETTED_CORNERS>(functor);
		Call<AC_GEODESIC_NORMALS_FLIPPED>(functor);
		Call<AC_GEODESIC_IS_CURVE>(functor);
		Call<AC_GEODESIC_DISTANCE>(functor);
		Call<AC_SURFACE_PATHS_CUT_DIRECTION_CHANGE>(functor);
		Call<AC_ORIGINAL_DRIVE_CURVE_INDEX>(functor);
		Call<AC_CURVE_REVERSED>(functor);
		Call<AC_IGNORE_TILTING_OPTIONS>(functor);
		Call<AC_IS_PILLAR_REMOVAL_HELIX>(functor);
		Call<AC_CIRCULAR_SAW_DEPTH>(functor);
		Call<AC_SPEEDSHAPE_INCOMPLETE_CUT>(functor);
		Call<AC_IMPELLER_FINAL_CUT>(functor);
		Call<AC_IMPELLER_INTERMEDIATE_CUT>(functor);
		Call<AC_MACHINE_LIMIT_BREAK>(functor);
		Call<AC_IS_AR_DIG_MOVE>(functor);
		Call<AC_IMPELLER_BELOW_MIN_LEAD_ANGLE>(functor);
		Call<AC_ADDITIVE_PATH_CONTOUR>(functor);
		Call<AC_ADDITIVE_PATH_CONTOUR_BLOCKED>(functor);
		Call<AC_ADDITIVE_PATH_FILL_CONTOUR>(functor);
		Call<AC_ADDITIVE_PATH_FILL_CONTOUR_BLOCKED>(functor);
		Call<AC_ADDITIVE_PATH_INFILL_SEGMENT>(functor);
		Call<AC_ADDITIVE_PATH_INFILL_SEGMENT_RETRACT>(functor);
		Call<AC_ADDITIVE_REGION_VOLUME>(functor);
		Call<AC_ADDITIVE_REGION_DOWN_SKIN>(functor);
		Call<AC_ADDITIVE_REGION_UP_SKIN_REMELTING>(functor);
		Call<AC_ADDITIVE_REGION_UP_SKIN_RECOATING>(functor);
		Call<AC_ADDITIVE_REGION_CORE>(functor);
		Call<AC_ADDITIVE_REGION_SUPPORT>(functor);
		Call<AC_ADDITIVE_REGION_ADDITIONAL_VOLUME>(functor);
		Call<AC_ADDITIVE_OFFSET_INDEX>(functor);
		Call<AC_ADDITIVE_LASER_POWER>(functor);
		Call<AC_ADDITIVE_LASER_SPEED>(functor);
		Call<AC_ADDITIVE_LASER_FOCUS>(functor);
		Call<AC_LINEBASED_UNROLLED_SLICE_IDX>(functor);
		Call<AC_LINEBASED_SAME_CONTOUR_IDX>(functor);
		Call<AC_GEODESIC_LINK>(functor);
		Call<AC_GEODESIC_IS_OUTER_FINISH_PATH>(functor);
		Call<AC_ADDITIVE_REGION_UP_SKIN>(functor);
		Call<AC_ADDITIVE_REGION_SKIRT>(functor);
		Call<AC_ADDITIVE_REGION_BRIM>(functor);
		Call<AC_ADDITIVE_PATH_LINK>(functor);
		Call<AC_ADDITIVE_PATH_INSIDE_LINK>(functor);
		Call<AC_ADDITIVE_PATH_OUTSIDE_LINK>(functor);
		Call<AC_ADDITIVE_PATH_RETRACT>(functor);
		Call<AC_MACHINE_REPOSITION_MOVES>(functor);
		Call<AC_ADDITIVE_LAYER_IDX>(functor);
		Call<AC_ADDITIVE_CONTOUR_IDX>(functor);
		Call<AC_ADDITIVE_CONTOUR_HOLLOW_VOLUME>(functor);
		Call<AC_ADDITIVE_PRINT_TIME>(functor);
		Call<AC_ADDITIVE_REGION_INITIAL_LAYER>(functor);
		Call<AC_ADDITIVE_REGION_IRONING>(functor);
		Call<AC_ADDITIVE_PATH_GAP_CONTOUR>(functor);
		Call<AC_SWARF_ARE_RAILS_INTERSECTING>(functor);
		Call<AC_GEODESIC_LAYER_INDEX>(functor);
		Call<AC_FINAL_PROFILE>(functor);
		Call<AC_KNIFE_GRINDING_DISTANCE_TO_TABLE_AXIS>(functor);
		Call<AC_GENERIC_LIFTED_LEAD_MOVE>(functor);
		Call<AC_GEODESIC_ORIGIN_GUIDE_CURVE_INDEX>(functor);
		Call<AC_GEODESIC_IS_CUT>(functor);
		Call<AC_GEODESIC_REGION_INDEX>(functor);
		Call<AC_IS_HELIX_LEAD_IN>(functor);
		Call<AC_ROUGH_LINK_WITHIN_GROUP>(functor);
		Call<AC_ROUGH_LINK_BETWEEN_GROUPS>(functor);
		Call<AC_SPIRAL_TURNS>(functor);
		Call<AC_ADDITIVE_LINK_TYPE>(functor);
		Call<AC_ADDITIVE_CONTOUR_ORIENTATION>(functor);
		Call<AC_ADDITIVE_PART_IDX>(functor);
		Call<AC_ADDITIVE_BUILD_STYLE_IDX>(functor);
		Call<AC_MULTIBLADE_SPINDLESPEED_MULTIPLIER>(functor);
		Call<AC_LAYER_NUMBER>(functor);
		Call<AC_HOLE_MAKING_THREAD_MILL_CONTOUR_TYPE>(functor);
		Call<AC_HOLE_MAKING_HELICAL_ARC_LEAD_RAMP_ANGLE>(functor);
	}

protected:
	template <typename Param, class Functor>
	static void Call(Functor& functor)
	{
#if defined(__GNUC__) || defined(__clang__)
		functor.template operator()<Param>();
#else
		functor.operator()<Param>();
#endif
	}
	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
};
}  // namespace cadcam
#endif  //	MW_MWTPATTRIBUTEDECLARATIONS_HPP_
