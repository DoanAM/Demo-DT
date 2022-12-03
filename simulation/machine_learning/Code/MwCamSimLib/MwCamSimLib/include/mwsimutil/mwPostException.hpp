// (C) 2003-2021 by ModuleWorks GmbH
// Owner: MultiXPost

/// \file
/// this module describe the mwPostException class

#ifndef MW_MWPOSTEXCEPTION_HPP_
#define MW_MWPOSTEXCEPTION_HPP_
//#############################################################################
#include "mwException.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwPostLimitType.hpp"
//#############################################################################
namespace post
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
//#############################################################################
//!extends mwException implements mwPostException specific exception
class MW_5AXUTIL_API mwPostException : public misc::mwException
{
public:
	typedef misc::mwAutoPointer<post::mwPostException> PostExceptionPtr;

	//#############################################################################
	//use 5000 to 5299
	enum Code
	{
		UNKNOWN                                                              = 0,
		ABSTARCT_FUNCTION_CALLED                                             = 5303,
		BAD_TOOL_ORIENTATION                                                 = 5000,
		NULL_VECTOR_PASSED                                                   = 5001,
		EQUAL_ROTATION_AXIS_DIRECTION_PASSED                                 = 5002,
		INVALID_AXIS_NAMES_COUNT                                             = 5003,
		DUPLICATE_AXIS_NAME                                                  = 5122,
		NOT_ALFA_AXIS_NAME                                                   = 5005,
		//5006 and 5007 in misc (not used)
		IS_EXCEEDING_LIMIT                                                   = 5008,
		IS_EXCEEDING_LIMIT_POLE_ANGLE_TOL                                    = 5009,
		IS_EXCEEDING_LIMIT_X_MIN                                             = 5010,
		IS_EXCEEDING_LIMIT_Y_MIN                                             = 5011,
		IS_EXCEEDING_LIMIT_Z_MIN                                             = 5012,
		IS_EXCEEDING_LIMIT_R1_MIN                                            = 5013,
		IS_EXCEEDING_LIMIT_R2_MIN                                            = 5014,
		IS_EXCEEDING_LIMIT_X_MAX                                             = 5015,
		IS_EXCEEDING_LIMIT_Y_MAX                                             = 5016,
		IS_EXCEEDING_LIMIT_Z_MAX                                             = 5017,
		IS_EXCEEDING_LIMIT_R1_MAX                                            = 5018,
		IS_EXCEEDING_LIMIT_R2_MAX                                            = 5019,
		IS_EXCEEDING_CIRCULAR_LIMIT                                          = 5020,
		EXCEPTION_IN_REWINDING_ALGORITHM                                     = 5021,
		BAD_ALLOCATION                                                       = 5022,
		REWIND_FOR_3AXIS_MACHINE                                             = 5023,
		SPINDLE_DIRECTION_VECTOR_WITH_LENGTH_0_PASSED                        = 5024,
		ROTATION_AXIS_DIRECTION_WITH_LENGTH_0_PASSED                         = 5025,
		FIRST_ROTATION_AXIS_DIRECTION_WITH_LENGTH_0_PASSED                   = 5026,
		SECOND_ROTATION_AXIS_DIRECTION_WITH_LENGTH_0_PASSED                  = 5027,
		THIRD_ROTATION_AXIS_DIRECTION_WITH_LENGTH_0_PASSED                   = 5028,
		TOOLPATH_IS_NOT_FOR_3AXES_MACHINE                                    = 5029,
		TOOLPATH_IS_NOT_FOR_4AXES_MACHINE                                    = 5030,
		UNKNOWN_MACHINE_TYPE                                                 = 5031,
		TOOLPATH_METRIC_MACHINE_DEF_INCH                                     = 5032,
		TOOLPATH_INCH_MACHINE_DEF_METRIC                                     = 5033,
		NULL_POINTER_PASSED                                                  = 5034,
		VECTOR_TOO_SHORT                                                     = 5035,
		A_DUPLICATE_AXIS_HAS_BEEN_FOUND                                      = 5036,
		TRANSLATION_AXIS_MISSING                                             = 5037,
		TOO_MANY_TRANSLATION_AXIS                                            = 5038,
		INVALID_VECTOR_PASSED                                                = 5039,
		TOO_MANY_ROTATION_AXIS                                               = 5040,
		AXIS_TO_FIND_IS_WRONG                                                = 5041,
		MXP_XML_SYNCHRONIZATION                                              = 5042,
		WRONG_METHOD_CALLED                                                  = 5043,
		TOOLPATH_CANNOT_BE_ALIGNED_WITH_MACHINE                              = 5044,
		ROTATIONAL_AXES_PARALLEL_WITH_SPINDLE_NOT_FIRST_AXIS                 = 5045,
		UNKNOWN_MACHINE_LIMITS                                               = 5046,
		NULL_PTR_PASSED                                                      = 5047,
		NULL_PTR_EXTENDEDPOSTEDMOVE                                          = 5048,
		UNKNOWN_DEFINITION_FOR_MW_RELMOVE                                    = 5049,
		UNKNOWN_DEFINITION_FOR_RAPID_MOVE					                 = 5050,
		REWIND_ALGORITHM_FAILD                                               = 5051,
		UNKNOWN_DEFINITION_FOR_MW_MACHMOVE                                   = 5052,
		UNKNOWN_DEFINITION_OF_RETRACT_TO_MACHINE_LIMITS_MOVE                 = 5053,
		RETRACT_TO_MACHINE_LIMITS_MOVE_REQUIRES_PREEXISTENT_MOVES            = 5054,
		UNKNOWN_MOVE_TYPE                                                    = 5055,
		NEGATIVE_OFFSET                                                      = 5056,
		OFFSETTING_IS_TOO_BIG                                                = 5057,
		MISSING_VERSION                                                      = 5058,
		OLD_VERSION                                                          = 5059,
		NO_UNITS                                                             = 5060,
		UNKNOWN_UNITS                                                        = 5061,
		UNKNOWN_DETECTION_MODE                                               = 5062,
		UNKNOWN_ORDER                                                        = 5063,
		UNKNOWN_AXIS_POS                                                     = 5064,
		INVALID_NUMBER_OF_AXIS                                               = 5065,
		A_ROTATION_AXIS_MISSING                                              = 5066,
		MATRIX_IS_NOT_4X4                                                    = 5067,
		MATRIX_IS_NOT_ISOMETRIC                                              = 5068,
		UNKNOWN_TRANSFORM_ID                                                 = 5069,
		INVALID_AXIS_NAMES                                                   = 5070,
		POST_SETTING_ID_MISSING                                              = 5071,
		DUPLICATE_TOOL_NAME_FOUND                                            = 5072,
		DUPLICATE_WORKPIECE_NAME_FOUND                                       = 5073,
		TOOL_DOES_NOT_EXIST                                                  = 5074,
		WORKPIECE_DOES_NOT_EXIST                                             = 5075,
		UNKNOWN_FIXED_ANGLE                                                  = 5076,
		ONLY_MANUAL_MODE_IN_SHORT_XML                                        = 5077,
		IS_EXCEEDING_LIMIT_TOOLPATH_TOL                                      = 5078,
		MW_RELMOVE_ALONG_TOOLAXIS_TO_MACHINE_LIMITS_ERROR                    = 5079,
		MACHINE_SYSYTEM_WITH_SINGULAR_MATRIX                                 = 5080,
		AXIS_NAME_PASSED_TOO_SHORT                                           = 5081,
		EXCEPTION_FOR_ROTATION_AXIS_FOR_INVALID_MACHINE_DEF                  = 5082,
		MWMACHDEF2XML_UNKNOWN_5AXIS_MACH_TYPE                                = 5083,
		MWMACHDEF2XML_AXIS_NAME_INVALID                                      = 5084,
		DISPLAY_ABSOLUTE_WITH_TLC_NULL_MACHDEF                               = 5085,
		ERROR_READING_XML_FILE                                               = 5086,
		OPPOSITE_ORIENTATIONS                                                = 5087,
		MISSING_FEED_RATE						                             = 5088,
		MISSING_BLK							                                 = 5089,
		EXCEPTION_IN_MULTIXPOST_CAN_NOT_FIND_A_NEW_LINK			             = 5090,
		TOO_MANY_AXES_PROVIDED						                         = 5091,
		INPUT_POSTED_MOVE_OUT_OF_MACHINE_LIMITS                              = 5092,
		UNKNOWN_TOOLPATH_SECTION_TYPE                                        = 5093,
		UNKNOWN_TOOLPATH_ABSTRACT_CLASS                                      = 5094,
		UNKNOWN_TOOLPATH_NO_HELIX_IN_MWTCOORDSYSTEM3D                        = 5095,
		UNKNOWN_TOOLPATH_NO_HELIX_IN_MWTICOORDSYSTEM3D                       = 5096,
		ARC_HELIX_NORMAL_NOT_SUPPORTED                                       = 5097,
		ARC_HELIX_WITH_INSUFFICIENT_POINTS                                   = 5098,
		EXCEPTION_IN_MULTIXPOST_NO_SOLUTIONS_FOR_6_AXIS                      = 5099,
		SAW_ORIENTATION_IS_0                                                 = 5100,
		THIRD_AXIS_NOT_FIXED                                                 = 5101,
		TOOLPATH_IS_NOT_6AXIS                                                = 5102,
		TOOLPATH_IS_6AXIS                                                    = 5103,
		INVALID_TOOLPATH_FOR_TURNING_TOOL                                    = 5104,
		WRONG_TURRET_DEFINITION                                              = 5105,
		INVALID_TRANSLATION_X_PASSED_TO_MACH_DEF                             = 5106,
		INVALID_TRANSLATION_Y_PASSED_TO_MACH_DEF                             = 5107,
		INVALID_TRANSLATION_Z_PASSED_TO_MACH_DEF                             = 5108,
		UNKNOWN_TURNING_MACHINE_DEF                                          = 5109,
		UNKNOWN_4AX_TURNING_MACH_DEF                                         = 5110,
		POST_DEFINITION_ID_DOES_NOT_EXIST                                    = 5111,
		DUPLICATE_POST_DEFINITION_ID                                         = 5112,
		INVALID_MACHINE_TYPE_MILL                                            = 5113,
		INVALID_MACHINE_TYPE_TURN                                            = 5114,
		INVALID_MACHINE_TYPE_CONTOUR                                         = 5115,
		UNKNOWN_MACHINE_DEFINITION_TYPE                                      = 5116,
		TURRET_ON_TABLE                                                      = 5117,
		INVALID_MACHINE_TYPE_FOR_TURNING                                     = 5118,
		ABSTRACT_CNCMOVE_USED                                                = 5119,
		AUTODETECT_FULL_FOR_UNKNOWN_MACHINE                                  = 5120,
		INVALID_ARC                                                          = 5121,
		//5122
		UNKNOWN_DEFINITION_OF_MXP_PARAM_IN_XML_FILE                          = 5123,
		MULTIXPOST_LICENSE_NOT_VALID										 = 5124,
		UNSUPPORTED_6AXIS_MACHINE                                            = 5125,
		UNSUPPORTED_TRANSFORMATION                                           = 5126,
		UNSUPPORTED_5PLUS1KINEMATIC                                          = 5127,
		INVALID_REPORT_FOR_SHORT_MOVE                                        = 5128,
		POST_CALCULATION_CANCELED											 = 5129,
		INVALID_ATTRIBUTE_FOR_SHORT_MOVE                                     = 5130,
		INVALID_ATTRIBUTE_SIZE                                               = 5131,
		SPINDLE_IS_DEFINED_AS_MATRIX                                         = 5132,
		SPINDLE_AND_CUT_DEFINITION_NOT_SUPPORTED                             = 5133,
		INVALID_HOLDER_TRANSF_DEFINITION                                     = 5134,
		INVALID_AXIS_INDEX													 = 5135,
		INVALID_PROVIDED_ROT_AXIS_INTERVAL									 = 5136,
		INVALID_ADDITIONAL_FIXED_AXIS										 = 5137,
		INVALID_ADDITIONAL_FIXED_AXIS_SIZE                                   = 5138,
		INVALID_MACHINE_TYPE_LASER                                           = 5139,
		INVALID_MACHINE_TYPE_KINFE_GRINDING                                  = 5140,
		INVALID_ARC_FILTER_PARAMETER                                         = 5141,
		INVALID_RAPID_MOTION_FROM_EXIT                                       = 5142,
		INVALID_FEED_MOTION_FROM_ENTRY										 = 5143,
		INVALID_FILENAME_IN_INI                                              = 5144,
		ILLEGAL_CHARS_IN_PATH                                                = 5145,
		INVALID_PARTITION_NAME                                               = 5146,
		UNWRITABLE_FOLDER                                                    = 5147,
		MXP_LOG_FILE_NOT_CREATED                                             = 5148,
		INVALID_MOVE_OPPOSITE_DIR_VEC										 = 5149,
		UNKNOWN_ENDEFFECTOR													 = 5150,
		MULTIXPOST_ROBOTIC_LICENSE_NOT_VALID								 = 5151,
		DUPLICATE_AXIS_NAME_IN_XML_START_POSITION						     = 5152,
		MISSING_AXIS_NAME_XML_START_POSITION								 = 5153,
		VELOCITY_CTRL_DEFINITION_ID_DOES_NOT_EXIST							 = 5154,
		DUPLICATE_VELOCITY_CONTROL_DEFINITION_ID							 = 5155,
		MOTION_FILTER_VISITOR_METHOD_VISIT_IS_NOT_IMPLEMENTED				 = 5156,
		WRONG_TRANSITION_MODE												 = 5157,
		WRONG_BUFFER_MODE													 = 5158,
		WRONG_VELOCITY_PROFILE_TYPE											 = 5159,
		WRONG_COLLISION_AVOIDANCE_MODE										 = 5160,
		WRONG_CONSTRAINT_TYPE												 = 5161,
		WRONG_OPTIMIZATION_TYPE												 = 5162,
		DUPLICATE_AXIS_NAME_IN_XML_AVOIDANCE_ZONES							 = 5163,
		MISSING_AXIS_NAME_XML_AVOIDANCE_ZONES								 = 5164,
		SOMETHING_GOT_WRONG_AT_MOVE											 = 5165,
		WRONG_CALCULATION_SPEED_MODE										 = 5166,
		TOO_LOW_DESIRED_STREAMING_CHUNK_SIZE								 = 5167,
		STREAM_ALREADY_INITIALIZED											 = 5168,
		EMPTY_TOOLPATH														 = 5169,
		GET_NEXT_BEFORE_HAS_NEXT											 = 5170,
		DIFFERENT_MOVES_TYPE												 = 5172,
		MACHINE_DOESNT_SUPPORT_THREADING									 = 5173,
		INVALID_TOOLPATH_FOR_THREADING										 = 5174,
		INVALID_6AXIS_MOVE                                                   = 5175,
		MISSING_AXIS_NAME_XML_MASS_MATRIX									 = 5176,
		INVALID_MACH_KINEMATIC_WITH_MOUNT_ADAPTER                            = 5177,
		INVALID_MACHINE_TYPE_CONSTANT_TRANSLATION                            = 5178,
		TOOL_SAW_DIRECTIONS_NOT_PERPENDICULAR                                = 5179,
		INVALID_MACHINE_TYPE_CONSTANT_TRANSLATION_NO_FIXED_AXIS              = 5180
	};
	//*****************************************************************************/
	// 
	// RULES WHEN ADDING NEW EXCEPTION:
	// -Add message error in mwPostException.cpp
	// -Add message error in postComponents/English/postComponents.txt and postComponents/German/postComponents.txt 
	//
	//*****************************************************************************/

	//#############################################################################
	//!Default constructor
	/*!
		\param errCode error code of the exception. 
		The default value is an unknown error
		\param prevLevel exception catched from the previous level. 
		MW_NULL if this is the first level of no exception history should be provided
	*/
	mwPostException(
		const Code vExcpID = UNKNOWN, 
		const mwPostException *pPrevLevel = 0,
		const mwPostLimitType limitType = mwPostLimitType());
	//#############################################################################
	//! Throw this exception
	virtual void Throw() const;
	//#############################################################################
	//! Clone exception object
	/*!
		\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;
	//#############################################################################
	const mwPostLimitType GetLimitType() const {return m_postLimitType;}
	void SetLimitType(const mwPostLimitType limitType) {m_postLimitType = limitType;}
	//#############################################################################
private:
	//#############################################################################
	mwPostLimitType m_postLimitType; // only for Limits
	//#############################################################################

};//end class mwPostException
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
};//end namespace post
#endif	//	MW_MWPOSTEXCEPTION_HPP_
