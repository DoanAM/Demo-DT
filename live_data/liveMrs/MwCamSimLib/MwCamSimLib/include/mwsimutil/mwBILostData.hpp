// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWBILOSTDATA_HPP_
#define MW_MWBILOSTDATA_HPP_


#include "mwStringConversions.hpp"

namespace misc
{
	
		//! stores information about lost data during an older bin conversion
		/*! stores information about lost data during an older bin conversion
		*/
	class mwBILostData
	{
	public:
	
		enum MessageID
		{
			LD_AVOID_TILT_DIR_NOT_ALLOWED_FOR_CRT_TILT_STRATEGY						= 1,
			LD_ALL_PARAMS_WERE_SET_TO_DEFAULT_DUE_TO_BINARY_VERSION_MISMATCH		= 2,
			LD_INVALID_ARBOR_RADIUS_WAS_RESETTED_TO_A_CYLINDER						= 3,
			LD_INVALID_DIAMETER_RESETTED_TO_TWICE_CORNER_RADIUS						= 4,
			LD_SECOND_ROT_AXIS_DIR_PARALLEL_SPINDLE_DIR								= 5,
			LD_BOTH_ROT_AXES_DIR_PARALLEL_SPINDLE_DIR								= 6,
			LD_SPLIT_LONG_CONTOURS_DISABLE											= 7,
			LD_LINK_TYPES_CHANGED_FROM_FOLLOW_SURF_TO_BLEND_SPLINE_FOR_TRI_MESH_PARAMS = 8,
			LD_DEPTH_STEP_PARAM_FOR_TRI_MESH_CALC_RESET_TO_DEFAULT_VALUE			= 9, 
			LD_CLEARANCE_TYPE_CHANGED_TO_PLANE_FOR_3AX_OUTPUT_TRI_MESH_ROUGH_PARAMS	= 10,
			LD_CLEARANCE_AXIS_CHANGED_TO_MACH_DIR_FOR_3AX_OUTPUT_TRI_MESH_ROUGH_PARAMS = 11,
			LD_SMALL_GAPS_LINK_TYPE_CHANGED_TO_DIRECT_FOR_TRI_MESH_PARAMS			= 12,
			LD_CLEARANCE_TYPE_CHANGED_TO_CYLINDER_FOR_PORT_MACH_PARAMS				= 13,
			LD_REST_ROUGH_TOOL_CHANGED_TO_ENDMILL									= 14,
			LD_RESERCH_PRJ_SETTINGS_PARAM_TRUNCATED									= 15,
			LD_START_POINT_OFFSET_CHANGED											= 16,
			LD_LINKS_BETW_SLICES_CHANGED_TO_DEFAULT_FOR_MULTIBLADE_PARAMS			= 17,
			LD_LINKS_BETW_PASSES_CHANGED_TO_DEFAULT_FOR_MULTIBLADE_PARAMS			= 18,
			LD_INVALID_SHAFT_DIAMETER_CHANGED_TO_OUTSIDE_DIAMETER_FOR_LOLLIPOP_TOOL	= 19,
			LD_INVALID_FLUTE_LENGTH_CHANGED_TO_BALL_RADIUS_FOR_LOLLIPOP_TOOL		= 20,
			LD_INVALID_OUTSIDE_DIAMETER_CHANGED_TO_SHAFT_DIAMETER_FOR_LOLLIPOP_TOOL	= 21,
			LD_INVALID_MAINTAIN_ORIENTATION_ACROSS_GAPS_LESS_CHANGED_TO_UNCHECK		= 22,
			LD_ALL_RAMPS_DISABLED_BECAUSE_CENTER_CUT_TOOL_IS_OFF					= 23,
			LD_AREA_LINK_WITHIN_GROUP_SET_TO_DIRECT_AND_RAMP_DISABLED_BECAUSE_ADAPTIVE_ROUGHING_IS_ON = 24,
			LD_STOCK_CLEARANCE_TRIMMED_TO_MAX_STOCK_CLEARANCE						= 25,
			LD_MULTI_BLADE_PARAMS_WERE_SWITCHED_TO_BASIC_CALCULATION				= 26,
			LD_MULTI_BLADE_FILLET_FINISH_CONTOUR_SWITCHED_TO_FULL					= 27,
			LD_INVALID_ARBOR_DEFINITION_REPLACED_WITH_EMPTY_ONE						= 28,
			LD_INVALID_HOLDER_DEFINITION_REPLACED_WITH_EMPTY_ONE					= 29,
			LD_CLEARANCE_AXIS_CHANGED_TO_MACH_DIR_FOR_4AX_OUTPUT_TRI_MESH_ROTARY_PARAMS = 30,
			LD_SWARF_PARAMS_ADJUSTED_FOR_SINGLE_SLICE_PATTERN_TYPE					= 31,
			LD_SWARF_PARAMS_ADJUSTED_FOR_SINGLE_LAYER_PATTERN_TYPE					= 32,
			LD_SWARF_PARAMS_ALL_COLLISION_OPS_WERE_DISABLED							= 33,
			LD_SWARF_PARAMS_NUMBER_OF_SLICES_CHANGED_FROM_0_TO_1					= 34,
			LD_SWARF_PARAMS_NUMBER_OF_LAYERS_CHANGED_FROM_0_TO_1					= 35,
			LD_PREFERRED_LEAD_ANGLE_ADJUSTED_FOR_MULTIBLADE_PARAMS					= 36,
			LD_RUN_TOOL_CHANGED_TO_AUTO												= 37,
			LD_DESIRED_STEPOVER_ADJUSTED_BASED_ON_MAX_STEPOVER						= 38,
			LD_HEIGHTS_PARAMS_ADJUSTED_TO_MIN_MAX_FROM_MACH_SURF_FOR_TRI_MESH_PARAMS = 39,
			LD_TRIANGLE_MESH_ROTARY_TOOL_AXIS_CONTROL_4AXIS							= 40,
			LD_TRAINGLE_MESH_ROTARY_4TH_AXIS_DIRECTION								= 41,
			LD_SSB_WAS_TURNED_OFF													= 42,
			LD_TOOL_AXIS_CONTROL_CHANGED_TO_PRESERVE_GOUGE_3TO5_CONVERSION			= 43,
			LD_DRILL_DIAMETER_IN_PERCENTS_ADJUSTED									= 44,
			LD_LINKS_BETWEEN_REGION_ADJUSTED										= 45,
			LD_ADAPTIVE_ROUGHING_RAMP_TYPE_SET_TO_AUTOMATIC							= 46,
			LD_ADAPTIVE_ROUGHING_LINE_RAMP_ANGLE_SET_TO_90_DEGREES					= 47,
			LD_MULTI_AXIS_LINK_CLEARENCE_AREA_LINK_ADJUSTED							= 48,
			LD_TRAINGLE_MESH_PROJECT_CURVES_MACH_TYPE_ADJUSTED						= 49,
			LD_ADAPTIVE_ROUGHING_GROUP_DIRECT_LINK_ADJUSTED							= 50,
			LD_PROFILE_CHANGED_TO_POLYLINE_DUE_TO_REMOVAL_OF_BACKWARDS_MOVES_AT_SAME_Y_FROM_PROFILE = 51,
			LD_REST_FINISHING_BIG_TOOL_CORNER_RADIUS_ADJUSTED_TO_TOOL_RADIUS = 52,
			LD_TRIANGLE_MESH_BASED_TOOL_AXIS_CONTROL_OUTPUT_TYPE_ADJUSTED_TO_3_AXIS = 53,
			LD_WIREFRAME_BASED_TOOL_AXIS_CONTROL_OUTPUT_TYPE_ADJUSTED_TO_3_AXIS = 54,
			LD_GOUGE_CHECK_TILT_TOOL_STRATEGY_DISABLED = 55,
			LD_ADAPTIVE_ROUGH_HEIGHT_CLEARANCE_WAS_SET_TO_DEFAULT = 56,
			LD_REGION_BASED_MODE_SET_FOR_SPIRALIZATION = 57,
			LD_DIRECT_BLEND_LINKS_ADJUSTED_TO_DIRECT_LINKS_FOR_NON_IMPELLER = 58,
			LD_AUTOMATIC_TILTING_PREFERANCE_NOT_IMPLEMENTED_SWITCHED_TO_ROTARY_PREFERENCE = 59,
			LD_UNSUPPORTED_MACH_DIRECTION_CHANGED_TO_CLIMB = 60,
			LD_ORTHO_TO_LOWER_EDGE_CURVE_AND_TILTED_LEADS_CHANGED_TO_FIXED_LEADS = 61,
			LD_CONTOUR_START_SIDE_EXTENSION_LENGTH_CHANGED_FROM_NEGATIVE_TO_O = 62,
			LD_CONTOUR_END_SIDE_EXTENSION_LENGTH_CHANGED_FROM_NEGATIVE_TO_O = 63,
			LD_TOOL_AXIS_SMOOTHING_STRENGHT_WAS_SET_TO_A_VALID_VALUE = 64,
			LD_COORDS_ADJUSTED_TO_CREATE_VALID_WCS = 65,
			LD_UNSUPPORTED_CUTTING_SIDE_SWITCHED_TO_CENTER = 66,
			LD_UNSUPPORTED_ARC_ROUND_CORNERS_CHANGED_TO_SPLINE = 67,
			LD_ADAPTIVE_ROUGHING_LINK_BETWEEN_GROUPS_ADJUSTED = 68,
			LD_FLATLANDS_ADAPTIVE_GROUP_DIRECT_LINK_ADJUSTED = 69,
			LD_ROUGHING_MAX_RAMP_DIAMETER_ADJUSTED = 70,
			LD_LEAD_ORIENTATION_ADJUSTED_TO_FIXED_FOR_3_AXIS_OUTPUT_FORMAT = 71,
			LD_NULL_AXIS_VECTOR_ADJUSTED_TO_Z_AXIS = 72,
			LD_ADAPTIVE_ROUGHING_FIRST_ENTRY_ADJUSTED = 73,
			LD_ADAPTIVE_ROUGHING_LAST_EXIT_ADJUSTED = 74,
			LD_CIRCULAR_SAW_STEPOVER_AND_CUTTING_DEPTH_TYPE_ADJUSTED = 75,
			LD_INVALID_CORNER_RADIUS_TYPE_IN_DEBURRING = 76,
			LD_CIRCULAR_SAW_CUT_PLANE1_TYPE_ADJUSTED = 77,
			LD_INVALID_TILT_MAX_RANGE_IN_DEBURRING = 78,
			LD_INVALID_TOOL_FOR_DRILLING = 79,
			LD_UNSUPPORTED_ARC_ROUND_CORNERS_CHANGED_TO_SPLINE_CONSTANT_Z = 80,
			LD_PARAMS_VALIDATION_IS_DISABLED = 81,
			LD_PARAMS_RUN_TOOL_DLG_BARREL_MILL_NOT_SUPPORTED_AT_USER_GIVE_POINT = 82,
			LD_FACE_UNSUPPORTED_LINK_BETWEEN_PASSES_ADJUSTED = 83,
			LD_ENGRAVE_ADJUSTED_START_POINTS_OPTION = 84,
			LD_ENGRAVE_DEPRECATED_START_FROM_CORNER_OPTION = 85,
			LD_ENGRAVE_DEPRECATED_START_POINTS_OPTION = 86, 
			LD_TOOL_AXIS_SMOOTHING_AVAILABLE_ONLY_FOR_SPHERICAL_TOOLS = 87,
			LD_ADAPTIVE_ROUGHING_RAMP_FALLBACK_SEQUENCE_ADJUSTED= 88,
			LD_PARAMS_GOUGE_CHECK_DLG_BARREL_MILL_NOT_SUPPORTED_IN_AUTO_TILT_TOOL_CHANGED = 89,
			LD_INVALID_TOOL_FOR_HOLE_MAKING_THREAD_TAPPING = 90,
			LD_DRILL_CYCLE_ADJUSTED_TO_DRILL = 91,
			LD_SWARF_MILLING_EXTENSION_START_ANGLE_ADJUSTED = 92,
			LD_UNSUPPORTED_TOOL_AXIS_CONTROL_OUTPUT_TYPE_CHANGED_TO_4_AXIS = 93,
			LD_UNSUPPORTED_CLEARANCE_PLANE_CHANGED_TO_CYLINDRICAL = 94,
			LD_INVALID_TPI_FOR_THREAD_TAP_TOOL_CHANGED_TO_DEFAULT = 95,
			LD_INVALID_PITCH_FOR_THREAD_TAP_TOOL_CHANGED_TO_DEFAULT = 96,
			LD_UNSUPORTED_MESH_FOR_HOLDER_CHANGED_TO_EXTRACT = 97,
			LD_UNSUPORTED_MESH_FOR_ARBOR_CHANGED_TO_EXTRACT = 98,
			LD_PARAMS_BARREL_MILL_NOT_SUPPORTED_FOR_MULTIAXIS_ROUGHING_TOOL_CHANGED = 99,
			LD_ROUGHING_PARALLEL_LEAD_OUT_DEPRECATED = 100,
			LD_TOOLPATH_MARKERS_WERE_TRUNCATED = 101,
			LD_PARAMS_BARREL_MILL_NOT_SUPPORTED_FOR_MULTIAXIS_FINISHING_TOOL_CHANGED = 102,
			LD_DETECT_THICKER_THAN_OF_INTERMEDIATE_SLICES_DEPRECATED_AND_SET_ZERO = 103,
			LD_INVALID_TOOL_FOR_HOLE_MAKING_REAMING = 104,
			LD_PARAMS_LOLLIPOP_MILL_NOT_SUPPORTED_FOR_SWARF_MILLING_TOOL_CHANGED = 105,
			LD_PARAMS_TOOLS_NOT_SUPPORTED_FOR_GEODESIC_MACHINING_TOOL_CHANGED = 106,
			LD_2_AXIS_PROFILE_DEPRECATED_START_POINTS_OPTION = 107,
			LD_ADAPTIVE_CUTS_MIN_STEPOVER_ADJUSTED = 108,
			LD_TURNING_ROUGH_PRIME_DEPTH_STEP_ADJUSTED = 109,
			LD_UNSUPPORTED_TOOL_AXIS_CONTROL_OUTPUT_TYPE_CHANGED_TO_3_AXIS = 110,
			LD_UNSUPPORTED_TAC_CONTACT_POINT_START_CHANGED_TO_1 = 111,
			LD_UNSUPPORTED_TAC_CONTACT_POINT_END_CHANGED_TO_1 = 112,
			LD_UNSUPPORTED_MAXM_CONTACT_ON_TOOL_PROFILE_CHANGED_TO_1 = 113,
			LD_UNSUPPORTED_MAXM_MINIMAL_CONTACT_POINT_HEIGHT_CHANGED_TO_1 = 114,
			LD_UNSUPPORTED_MAXM_MAXIMAL_CONTACT_POINT_HEIGHT_CHANGED_TO_1 = 115,
			LD_UNSUPPORTED_MAXM_CONTACT_ON_TOOL_PROFILE_FLOOR_CHANGED_TO_1 = 116,
			LD_UNSUPPORTED_MAXM_MINIMAL_CONTACT_POINT_HEIGHT_FLOOR_CHANGED_TO_1 = 117,
			LD_UNSUPPORTED_MAXM_MAXIMAL_CONTACT_POINT_HEIGHT_FLOOR_CHANGED_TO_1 = 118,
			LD_UNSUPPORTED_COLL_OPS_CONTACT_POINT_START_AUTO_TILT_CHANGED_TO_1 = 119,
			LD_UNSUPPORTED_COLL_OPS_CONTACT_POINT_END_AUTO_TILT_CHANGED_TO_1 = 120,
			LD_ENGRAVE_INVALID_PROFILE_RAMP_DEFINITION_MODE_CHANGED = 121,
			LD_UNSUPPORTED_STOCK_TRIMMING_FOR_REST_FINISHING_BASED_ON_STOCK_TURNED_OFF = 122,
			LD_PARAMS_BARREL_MILL_NOT_ALLOWED_FOR_EXISTING_TOOLPATH_PATTERNS = 123,
			LD_PITCH_GREATER_THAN_TOOL_DIA_THREAD_TAP_TOOL_CHANGED_TO_DEFAULT=124,
			LD_HOLE_MAKING_PARAMS_DEPTH_CHANGED_TO_DEFAULT=125,
			LD_DHC_UNSUPPORTED_SHAFT_CLEARANCE = 126,
			LD_DHC_UNSUPPORTED_ARBOR_CLEARANCE = 127,
			LD_DHC_UNSUPPORTED_HOLDER_CLEARANCE = 128,
			LD_DHC_IN_PROCESS_STOCK_UNSUPORTED_MIN_SEGMENT_LENGTH_FILTERING_TURNED_OFF = 129,
			LD_DHC_IN_PROCESS_STOCK_UNSUPORTED_DEPTH_STEP_Z_VALUES_TURNED_OFF = 130,
			LD_DHC_IN_PROCESS_STOCK_UNSUPORTED_FINAL_CONTOUR_PASS_TYPE_ADJUSTED = 131,
			LD_COLL_OPS_SIDE_TILT_MIN_ANGLE_AUTOMATIC_ADJUSTED = 132,
			LD_COLL_OPS_SIDE_TILT_MAX_ANGLE_AUTOMATIC_ADJUSTED = 133,
			LD_UNSUPPORTED_BARREL_MILL_NOT_ALLOWED_FOR_OPTIC_PATTERNS = 134,
			LD_CONTAINMENT_TYPE_CHANGED_TO_MACH_SURF_BOUNDARY_DUE_TO_EMPTY_CONTAINMENT_CURVES = 135,
			LD_WELDING_MACH_TOL_ADJUSTED_BASED_ON_LAYER_STEPOVER = 136,
			LD_WELDING_CONTAINMENT_TYPE_CHANGED_TO_BODY_MESH=137,
			LD_TURNMILLING_UNSUPPORTED_TOOL_CHANGED_TO_ENDMILL = 138,
			LD_LINK_ENTRY_EXIT_FEED_DISTANCES_CHANGED_TO_DEFAULT=139,
			LD_LINK_ENTRY_FEED_DISTANCE_CHANGED_TO_DEFAULT=140,
			LD_LINK_EXIT_FEED_DISTANCE_CHANGED_TO_DEFAULT=141,
			LD_UNSUPORTED_GOUGE_CHECKING_WITH_FINAL_CONTOUR_PASS_AND_CONPENSATION_TYPE_TURNED_OFF = 142,
			LD_FIRST_ENTRY_CHANGED_TO_APPROACH_FROM_RAPID_PLANE = 143,
			LD_LAST_EXIT_CHANGED_TO_RETRACT_TO_RAPID_PLANE = 144,
			LD_UNSUPORTED_DETECT_THICKER_THAN_TURNED_OFF = 145,
			LD_UNSUPPORTED_SHALLOW_STEEP_AREA_CHANGED_TO_DEFAULT = 146,
			LD_UNSUPPORTED_FEED_RATE_CHANGED_TO_DEFAULT = 147,
			LD_UNSUPPORTED_ORDERING_FOR_SPIRAL_METHOD_CHANGED_TO_DEFAULT = 148,
			LD_UNSUPPORTED_MIN_LEAD_ANGLE_FOR_AUTOTILT_CHANGED_TO_DEFAULT = 149,
			LD_UNSUPPORTED_MAX_LEAD_ANGLE_FOR_AUTOTILT_CHANGED_TO_DEFAULT = 150,
			LD_STOCK_DEFINITION_TURNED_ON_FOR_AUTOMATIC_ROUGHING = 151,
			LD_WELDING_SMOOTHING_LOOK_AHEAD_DISABLED_AND_SET_TO_DEFAULT = 152,
			LD_PRIME_TURNING_UNSUPPORTED_TOOL_CHANGED_TO_PRIME = 153,
			LD_INVALID_TOOL_FOR_HOLE_MAKING_THREAD_MILLING = 154
		};
	
		//! Constructor
		/*! 			
				  \param rMessageSection the new MessageSection
				  \param vMessageIDD the new MessageIDD
		*/
		inline mwBILostData(const int vMessageIDD,const misc::mwstring& rMessageSection=_T("BinLostData"))
		:m_MessageSection(rMessageSection),
		m_MessageIDD(vMessageIDD)
		{};
	
		//! gets MessageIDD
		/*! 			
				  \returns the MessageIDD
		*/
		inline const int GetMessageIDD() const
			 { return m_MessageIDD;};
	
		//! sets MessageIDD
		/*! 			
				  \param vMessageIDD the new MessageIDD
		*/
		inline void SetMessageIDD(const int vMessageIDD)
			 {m_MessageIDD=vMessageIDD;};
	
			//! gets MessageSection
		/*! 			
				\returns the MessageSection
		*/
		inline const misc::mwstring& GetMessageSection() const
			{ return m_MessageSection;};
	
		//! sets MessageSection
		/*! 			
				\param rMessageSection the new MessageSection
		*/
		inline void SetMessageSection(const misc::mwstring& rMessageSection)
			{m_MessageSection=rMessageSection;};
	
	private:
		misc::mwstring m_MessageSection;
		int m_MessageIDD;
	};
}
#endif	//	MW_MWBILOSTDATA_HPP_
