// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWRESOURCEINTF_HPP_
#define MW_MWRESOURCEINTF_HPP_
#include "mwStringConversions.hpp"
#include "mwLanguageFeatures.hpp"
#include <map>
#include	"mwDllImpExpDef.hpp"

namespace misc
{
	//!This class is used as base class for the class interacting with a resource dll library
	class  MW_5AXUTIL_API mwResourceIntf
	{
	public:
		typedef unsigned long MsgNumT;	// the type of a message number

		virtual ~mwResourceIntf() MW_DEFAULT_DESTRUCTOR_IMPL

		//!Get text string by number
		/*!This function returns a string with a given number
		\param msgNum number of the text string to get
		\returns the requested message
		*/
		virtual const misc::mwstring GetMsg(MsgNumT msgNum ) const = 0;
		

		//!Get text string by number and section name
		/*!This function returns a string with a given number and section name
		\param msgNum number of the text string to get
		\param sectionName name of the section from where to get text string
		\returns the requested message
		*/
		virtual const misc::mwstring GetMsg(
			MsgNumT msgNum, misc::mwstring sectionName ) const = 0;
		

		//!returns true if resource is initialized
		virtual bool IsInitialized() const = 0;
		
	};
};
#endif	//	MW_MWRESOURCEINTF_HPP_
