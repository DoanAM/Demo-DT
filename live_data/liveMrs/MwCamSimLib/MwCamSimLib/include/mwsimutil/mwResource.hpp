// (C) 2003-2016 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWRESOURCE_HPP_
#define MW_MWRESOURCE_HPP_
#include "mwFileStream.hpp"
#include <map>
#include <exception>
#include "mwStringConversions.hpp"
#include "mwResourceIntf.hpp"
#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwWarningPragmas.hpp" //For the existing users who might want to use MW-Warning-Pragmas

namespace misc
{
	//!This class provides a basic resource reader capabilities
	/*!Sections are supported.
	*/
	class MW_DEPRECATED("mwResource is deprecated since 2021.12. It is not meant for customers.") MW_5AXUTIL_API mwResource
	{
	public:

		//!Get text string by number
		/*!This function returns a string with a given number
			\param msgNum number of the text string to get
			\returns the requested message
		*/
		static const misc::mwstring &GetMsg( unsigned long msgNum );

		//!Get text string by number and section name
		/*!This function returns a string with a given number and section name
			\param msgNum number of the text string to get
			\param sectionName name of the section from where to get text string
			\returns the requested message
		*/
		static const misc::mwstring &GetMsg( unsigned long msgNum, misc::mwstring sectionName );

		//!Set the name of the file to get messages from
		/*!Reads resource strings from the file with a given name
		   \param fileName name of the file
		*/
		static void SetFile( const misc::mwstring &fileName );
#ifdef _WIN32
		static void SetFile(void* /* HRSRC */ resource);
#endif
		static void SetFile(std::istream& strm);
		//clears the passed file name, and unload the resources messages
		//this function you don't need to call since this is always performed
		//on the unloading of dll holding the mwResource class
		static void ClearFile();

		static const misc::mwstring GetFile();

		static const unsigned int GetParserVersion();
		static const unsigned int GetMaxParserVersion();
		static void SetParserVersion( const unsigned int& newVersion );
		static void ResetParserVersion();
		static void SetMaxParserVersion();

		static const int GetMenuCount();
		static const int GetMenuItemCount( const int& menuidx );
		static void GetMenuItemText( const int& menuidx,
			const int& menuitemidx, misc::mwstring& menuItemText );


	private:
		//this is a static class
		mwResource();
		struct InitResData;
		static void InitRes();
		template<typename Char>
		static void InitRes(std::basic_istream<Char>& resStrm);
	};
};
#endif	//	MW_MWRESOURCE_HPP_
