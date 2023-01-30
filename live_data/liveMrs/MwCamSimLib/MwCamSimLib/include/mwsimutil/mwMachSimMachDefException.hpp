// (C) 2014-2017 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMMACHDEFEXCEPTION_HPP_
#define MW_MWMACHSIMMACHDEFEXCEPTION_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwException.hpp"




/*	mwMachSimMachDefException - machine definition exception class.
	Machine definition may throw a mwMachSimMachDefException or derived type.
	The exception message can be translated based on mwMachSim_res.dll
	See and example at the end of this file.
*/
	

namespace machsim
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
class MW_SIMUTIL_API mwMachSimMachDefException : public misc::mwException
{
public:		
	enum errorIDD
	{
		UNKNOWN_EXCEPTION=1,
		NO_ELEMENT_WITH_SPECIFIED_NAME = 10,
		NO_ELEMENTS_OF_SPECIFIED_CLASS = 11,
		XML_UTIL_ERROR = 12,
		XML_PARSE_ERROR = 13,
		ELEMENT_WITH_SPECIFIED_NAME_ALREADY_EXISTS = 48,
		COULDNT_ACCESS_FILE=62,
		_IN_=63,
		READ_MODE=64,
		WRITE_MODE=65,
		READWRITE_MODE=66,
		SEMANTIC_ERROR_OCCURRED_WHILE_PARSING_MACHDEF_UNDER_NODE=70,			
		THE_MACHINE_HAS_NO_SPECIFIED_UNITS=100,
		FILE_DOES_NOT_EXIST=175,
		UNKNOWN_MAGAZINE_TREE=176,
		VISITING_ABSTRACT_CLASS_NOT_ALLOWED=177,
		NO_WORKPIECE_OR_DESCENDANT_FOUND_FOR_OBJECT=178,
		CORRUPTED_XML_FILE=179,
		UNKNOWN_UNITS=180,
		UNKNOWN_OBJTYPE=181,
		PREPROCESSOR_SOURCE_CODE_FILE_NOT_FOUND=182,
		EXCEPTION_OCCURRED_WHILE_READING_FILE=183,
		UNKNOWN_EXCEPTION_OCCURRED_WHILE_READING_FILE=184,
		PREPROCESSOR_TAG_HAS_NO_SPECIFIED_INSTANCE_VARIABLE_NAME=185,
		PREPROCESSOR_TAG_HAS_NO_SPECIFIED_FILENAME=186,
		UNDEFINED_IMPLEMENTATION_OF_COLLISION_GROUP_TYPE=187,
		UNKNOWN_TOOL_COMPONENT = 200,
		EMPTY_AXIS_NAME = 227
	};

	//! Construct exception with given error code.
	mwMachSimMachDefException(errorIDD errorCode, const misc::mwException *prevLevel=0);
	
	//! Construct exception with multiple error codes.
	mwMachSimMachDefException(const exceptionStack& messages, const misc::mwException *prevLevel=0);

	mwMachSimMachDefException(const errorIDD& errorCode, const misc::mwstring &addInfo);

protected:
	//! Set multiple error codes for this exception.
	void SetMessageBits(const exceptionStack& toSet);

	//! Get the default (en) message for the errorCode.
	void GetCodeMessage(errorIDD errorCode, misc::mwstring& en_msg);

	void SetCompleteErrorMessageFromBits();
};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
}; // namespace

/*
	How to translate the message of mwMachSimMachDefException:

	try
	{
		// code that throws
		...
		misc::mwAutoPointer<machsim::mwMachsimMachDef> machDef =
		xmlReader.CreateMachineDefinition(ptrUnit, bLoadSTL, true);
	}
	catch(const machsim::mwMachSimMachDefException& exc)
	{
		// translate the message
		misc::mwResourceDll handle(_T("path/to/mwMachSim_res.dll"));
		misc::mwstring error = handle.GetMsg(exc.GetErrorCode(), _T("ErrorMessages"));

		const misc::mwException::exceptionStack& exStack = exc.GetExceptionStack();
		for(misc::mwException::exceptionStack::const_iterator it = exStack.begin();
		it != exStack.end(); ++it)
		{
			error += _T("\n");
			error += handle.GetMsg((*it).first, _T("ErrorMessages"));
		}
		MessageBox(0, error.c_str(), 0, MB_OK);
	}
*/
#endif	//	MW_MWMACHSIMMACHDEFEXCEPTION_HPP_
