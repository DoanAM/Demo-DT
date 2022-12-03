// (C) 2005-2014 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMMACHDEFSEMANTICEXCEPTION_HPP_
#define MW_MWMACHSIMMACHDEFSEMANTICEXCEPTION_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwString.hpp"
#include "mwMachSimMachDefException.hpp"


namespace machsim
{
#if defined(__APPLE__)
#pragma GCC visibility push(default)
#endif
/*!	It represents a semantic exception occurred during parsing the XML file.
	It is also a utility class that can create a meaningful exception
	out of different parameters (see constructors).
*/
class MW_SIMUTIL_API mwMachSimMachDefSemanticException : public mwMachSimMachDefException
{
public:
	/*! Parameterized constructor
		\param nodeName the node where the error occurred
		\param nodeID the kinematic element name where the error occurred
		\param errCode the exception code
		\param errMsg the error message
		\param prevLevel the exception that needs to be preserved
	*/
	mwMachSimMachDefSemanticException(
		const misc::mwstring& nodeName,
		const misc::mwstring& nodeID,
		const unsigned long& errCode,
		const misc::mwstring& errMsg,
		const misc::mwException* prevLevel=0);


	/*! Parameterized constructor
		\param nodeName the node where the error occurred
		\param nodeID the kinematic element name where the error occurred
		\param prevLevel the exception that needs to be preserved
	*/
	mwMachSimMachDefSemanticException(
		const misc::mwstring& nodeName,
		const misc::mwstring& nodeID,
		const misc::mwException* prevLevel);


	/*! Parameterized constructor
		\param errorCode the error code
		\param string to be added (cannot be translated)
		\param prevLevel the exception that needs to be preserved
	*/
	mwMachSimMachDefSemanticException(
		errorIDD errorCode,
		const misc::mwstring& infoToAdd,
		const misc::mwException* prevLevel=0);

};
#if defined(__APPLE__)
#pragma GCC visibility pop
#endif
};	// namespace
#endif	//	MW_MWMACHSIMMACHDEFSEMANTICEXCEPTION_HPP_
