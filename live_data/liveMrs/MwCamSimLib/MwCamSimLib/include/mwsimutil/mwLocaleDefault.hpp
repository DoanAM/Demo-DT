// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWLOCALEDEFAULT_HPP_
#define MW_MWLOCALEDEFAULT_HPP_
#include "mwLocale.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
	class mwResourceDll;
}

namespace interact
{
	//! The class that permits obtaining the internationalized text from a text file or resource dll
	class MW_5AXUTIL_API mwLocaleDefault : public interact::mwLocaleIntf
	{
	public:
		virtual ~mwLocaleDefault() {}

		//! Function obtaining the localized text from txt files
		/*!
			\param text the section name where the message is to be found
			\param title the message number within the section
			\returns the message text found
		*/
		virtual const misc::mwstring GetMsg(const misc::mwstring& section, unsigned int msgNo) const;

		//!Display a message box with regular windows MessageBox
		/*!
			\param text the message text
			\param title the message title
			\param nType the style of the message box same as MSDN MessageBox nType 
				for the special type:MB_YESNOYESTOALL it actualy use MB_CANCELTRYCONTINUE
			\returns the same as MSDN MessageBox returns, 
				for the special custom MB_YESNOYESTOALL it returns IDNO,IDYES,IDCONTINUE
		*/
		virtual int MsgBox(const misc::mwstring& text,const misc::mwstring& title =_T(""), unsigned int nType = MW_MB_DEFAULT ) const;

		enum mwUsesResources
		{
			MW_RESOURCE_TXT,
			MW_RESOURCE_DLL
		};

		//! Setting the file (txt sau dll) where the messages will be written from
		static void GlobalSetFile( const mwUsesResources& useResource, const misc::mwstring &resFileName,
			const bool &bForceReread = false );

		//! Returning the resource dll object, creating a new one if none exists
		static misc::mwResourceDll& GetResDll();

		//! Returning the so far used resource type
		static  mwUsesResources GetLastUsedResource();

		//! Resets the file name contained by the last used resource
		static const misc::mwstring GetResourceFile();

		//##############################################################################
		//! Set locale settings for language passed as localeLanguage
		static void SetLocale( const misc::mwstring& localeLanguage ) ;

		//! Return "User" Account default language.
		static const misc::mwstring GetUserLocaleLanguage() ;

		//! Return "Administrator" Account language 
		static const misc::mwstring GetSystemLocaleLanguage() ;

		//! Return MW default language (English)
		static const misc::mwstring GetMWDefaultLocaleLanguage() ;		
		//##############################################################################
	protected:
		//!Display a message box with regular windows MessageBox
		/*! This function is call by MsgBox function, and allow derived classes to user their own type of message box
			Default implementation is windows api MessageBox, but you may use AfxMessageBox, BCGMessageBox, or other by overwriting this
		*/
		virtual int MsgBoxPlatformSpecific(const misc::mwstring& text,const misc::mwstring& title , unsigned int nType) const;
	};
}
#endif	//	MW_MWLOCALEDEFAULT_HPP_
