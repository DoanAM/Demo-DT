// (C) 2007-2017 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMISCEXCEPTION_HPP_
#define MW_MWMISCEXCEPTION_HPP_
#include "mwException.hpp"
#include "mwDllImpExpDef.hpp"

#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif

class MW_5AXUTIL_API mwmiscException : public misc::mwException
{
public:
	enum errorIDD
	{
		UNEXPECTED_END_OF_BINARY_LOG_STREAM = 2018,
		INDEX_OUT_OF_BOUNDS = 10011,
		UNEXPECTED_END_OF_INPUT_STREAM = 10012,
		UNEXPECTED_END_OF_OUTPUT_STREAM = 2149,
		CONVERSION_FROM_64_TO_32_FAILED = 2157,
		CONVERSION_FROM_VALUE_TO_STRING_FAILED = 2576,
		CONVERSION_TO_ASCII_FAILED = 10013,
		STRING_TOO_BIG = 2578,
		CONVERSION_FROM_STRING_TO_VALUE_FAILED = 2579,
		THE_REQUESTED_MESSAGE_DOES_NOT_EXIST = 3600,
		THE_REQUESTED_FILE_COULD_NOT_BE_LOADED = 3601,
		FAILED_TO_UNLOAD_RESOURCE_FILE = 3602,
		FAILED_LOCKING_SPECIFIED_RESOURCE = 3603,
		FAILED_LOADING_SPECIFIED_RESOURCE = 3604,
		REQUESTED_RESOURCE_WAS_NOT_FOUND = 3605,
		INVALID_ENTRY_FOUND_WHILE_PARSING_MWMSGMAP = 3606,
		RESOURCE_DLL_IS_NOT_INITIALIZED = 3607,
		NO_CONTAINER_AVAILABLE = 5503,
		USER_HAS_ABORTED_THE_OPERATION = 6000,
		PARSER_NOT_IMPLEMENTED = 6252,
		UNKNOWN_KEYWORD = 6253,
		UNDEFINED_MATH_EXCEPTION_TYPE = 7100,
		DIVISION_BY_ZERO_EXCEPTION = 7101,
		MATRIX_NOT_SQUARE = 7110,
		INCOMPATIBLE_VECTORS = 7103,
		INCOMPATIBLE_MATRICES = 7104,
		MATRIX_AND_VECTOR_ARE_INCOMPATIBLE = 7105,
		MATRIX_CREATION_PARAMETERS_ARE_INVALID = 7111,
		VECTOR_CREATION_PARAMETERS_ARE_INVALID = 7112,
		DETERMINANT_IS_ZERO = 7113,
		INCOMPATIBLE_PAIR_OF_MATRICES = 7109,
		UNRECOGNIZED_ACTION_STRING = 8000,
		GIVEN_ACTION_STRING_IS_ALREADY_EMPLOYED = 8001,
		GIVEN_ACTION_WAS_NOT_FOUND = 8002,
		NO_ACTION_STRING_FOUND = 8003,
		NO_KEYWORD_FOUND = 8004,
		KEYWORD_WAS_ALREADY_ASSIGNED = 8005,
		VALUE_IS_OUT_OF_RANGE = 8006,
		UTF8_ENCODING_IS_NOT_SUPPORTED = 8007,
		ERROR_READING_LICENSE_FILE = 10005,
		LICENSE_EVALUATION_EXPIRED = 10006,
		CACHING_EXCEPTION = 10007,
		UNKNOWN_FILE_FORMAT = 10008,
		DUPLICATE_MESSAGE_ID_FOUND_DURING_RC_FILE_GEN = 10009,//! don't change this error code, it is used for res file gen mechanism 
		LICENSE_FILE_MARKER_MISSING = 10020,
		LICENSE_INVALID_VERSION_OF_LICENSE_FILE = 10021,
		LICENSE_STREAM_IS_ABSENT = 10022,
		LICENSE_FILE_CAN_NOT_BE_OPENED = 10023,
		LICENSE_CANNOT_OPEN_FOR_WRITING_THE_TXT_FILE = 10024,
		LICENSE_INVALID_NUMBER_OF_PRODUCTS = 10025,
		LICENSE_CAN_NOT_UPDATE_LICENSE_FILE = 10026,
		LICENSE_CAN_NOT_OPEN_LICENSE_FILE_FOR_WRITING = 10027,
		NOT_SUPPORTED_EXCEPTION = 8008,
	};

	mwmiscException(errorIDD errorCode, const misc::mwException *prevLevel=0);

	//! Throw this exception
	virtual void Throw() const;

	//! Clone exception object
	/*!
	\param[out] dst pointer to this exception object
	*/
	const Ptr GetCopy() const;
};

#if defined(__APPLE__)
#pragma GCC visibility pop
#endif

#endif	//	MW_MWMISCEXCEPTION_HPP_
