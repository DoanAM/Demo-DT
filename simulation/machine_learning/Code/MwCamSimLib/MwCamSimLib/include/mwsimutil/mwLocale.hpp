// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

/// \file
/// An interactor and utilities functions to facilitate internationalization

#ifndef MW_MWLOCALE_HPP_
#define MW_MWLOCALE_HPP_
#include "mwStringConversions.hpp"
#include "mwAutoPointer.hpp"
#include "mwDllImpExpDef.hpp"

namespace interact
{
	class MW_5AXUTIL_API mwLocaleIntf   
	{
	public:
		//! Function to be implemented for obtaining the localized text
		/*!
			\param section the section name where the message is to be found
			\param msgNo the message number within the section
			\returns the message text found
		*/
		virtual const misc::mwstring GetMsg(const misc::mwstring& section, unsigned int msgNo) const = 0;
		
		virtual ~mwLocaleIntf(){}

		/*! special custom type of message boxes you may check it with MB_MISCMASK, when this is specified
			anything under MB_TYPEMASK is ignored
		*/
		#define MW_MB_YESNOYESTOALL 0x00004000L 
		//MB_OK | MB_ICONEXCLAMATION
		#define MW_MB_DEFAULT 0x00000030L 
		
		//!Display a message box with a text
		/*!Can be overridden in order to handle differently the error, instead of popping up
			a a message box
			\param text the message text
			\param title the message title
			\param nType the style of the message box same as MSDN AfxMessageBox nType 
				plus a special custom type:MB_YESNOYESTOALL
			\returns the same as MSDN MessageBox returns, for the special custom MB_YESNOYESTOALL it returns 
						IDCONTINUE for YesToAll button
		*/
		virtual int MsgBox(const misc::mwstring& text,const misc::mwstring& title =_T(""), unsigned int nType = MW_MB_DEFAULT ) const =0 ;

		//!allow call of MsgBox just with text and style, using default emty title
		int MsgBox(const misc::mwstring& text,unsigned int nType) const 
			{return MsgBox(text,_T(""),nType);};

		
	};

	//! defines the decorator pattern for localizations
	class MW_5AXUTIL_API mwLocaleDecorator : public mwLocaleIntf
	{
	public:
		mwLocaleDecorator (const misc::mwAutoPointer<mwLocaleIntf>& toDecorate )
		: m_toDecorate(toDecorate) {};

		virtual const misc::mwstring GetMsg(const misc::mwstring& section, unsigned int msgNo) const
		{return m_toDecorate->GetMsg(section,msgNo);};
		virtual int MsgBox(const misc::mwstring& text,const misc::mwstring& title =_T(""), unsigned int nType = MW_MB_DEFAULT ) const 
		{return m_toDecorate->MsgBox(text,title,nType);};

	private:
#pragma warning(push)
#pragma warning(disable : 4251)
		misc::mwAutoPointer<mwLocaleIntf> m_toDecorate;
#pragma warning(pop)
	};

	//! defines usual functions a localization SINGLETON has
	/*! Most of projects need their own resource singleton 
		so it need to have a static class with a static member of type mwLocaleIntf from witch
		to get msg, to display msg etc. 
		Not to duplicate the functions in each project classes you may derive from mwLocaleSingletonInterface
		using project class as template argument also, see lower mwLocale example.
		You must implement two private functions: GetNotConstUnsafeInstance() and GetDefaultInstance()
	*/
	template <typename TStaticInstanceProvider>
	class MW_5AXUTIL_API mwLocaleSingletonInterface
	{
	public:
		//! Gets the unique instance responsible for handling the localization in a application
		/*!
			\returns the instance to be used for localization
		*/
		static const misc::mwAutoPointer<mwLocaleIntf> GetInstance()
		{
			return GetNotConstInstance();
		}

		//! Sets the unique instance responsible for handling the localization in a application
		/*!
			\param the new instance to be used from now on
		*/
		static void SetInstance(const misc::mwAutoPointer<mwLocaleIntf>& newinstance)
		{
			TStaticInstanceProvider::GetNotConstUnsafeInstance() = newinstance;
		}
		//!Display a message box with a localized text from the section and number specified
		/*!
			\param section the section name where the message is to be found
			\param msgNo the message number within the section
			*/
		static void GetMsgAndDisplayMsgBox(const misc::mwstring& section, unsigned int msgNo)
		{
			const misc::mwAutoPointer<mwLocaleIntf> inst = GetInstance();
			inst->MsgBox(inst->GetMsg(section, msgNo));
		}
		//!Display a message box with the text specified
		/*!
			\param text the text to be displayed
		*/
		static int MsgBox(const misc::mwstring& text,const misc::mwstring& title =_T(""), unsigned int nType = MW_MB_DEFAULT) 
		{
			const misc::mwAutoPointer<mwLocaleIntf> inst = GetInstance();
			return inst->MsgBox(text,title,nType);
		}
		//!Display a message box with the text specified
		/*!
			\param text the text to be displayed
		*/
		static int MsgBox(const misc::mwstring& text, unsigned int nType) 
		{
			const misc::mwAutoPointer<mwLocaleIntf> inst = GetInstance();
			return inst->MsgBox(text,nType);
		}
		//!Gets a localized text from the section and number specified
		/*!
			\param section the section name where the message is to be found
			\param msgNo the message number within the section
			\returns the message text found
		*/
		static const misc::mwstring GetMsg(const misc::mwstring& section, unsigned int msgNo)
		{
			const misc::mwAutoPointer<mwLocaleIntf> inst = GetInstance();
			return inst->GetMsg(section, msgNo);
		}
	protected:
		static misc::mwAutoPointer<mwLocaleIntf> GetNotConstInstance()
		{
			if (TStaticInstanceProvider::GetNotConstUnsafeInstance().IsNull())
				TStaticInstanceProvider::GetNotConstUnsafeInstance() = TStaticInstanceProvider::GetDefaultInstance();
			return TStaticInstanceProvider::GetNotConstUnsafeInstance();
		}
	private:
		//! Constructor not allowed since it's a static class
		mwLocaleSingletonInterface();
	};

	//! default ModuleWorks locale singleton
	class MW_5AXUTIL_API mwLocale : public mwLocaleSingletonInterface <mwLocale>
	{	
	private:
		friend mwLocaleSingletonInterface;
		//! Gets the default ModuleWorks instance
		/*! should be used only by mwLocaleSingletonInterface
		*/
		static const misc::mwAutoPointer<mwLocaleIntf> GetDefaultInstance();
		static misc::mwAutoPointer<interact::mwLocaleIntf>& GetNotConstUnsafeInstance();
		//! Constructor not allowed since it's a static class
		mwLocale();
	};
	
	

}
#endif	//	MW_MWLOCALE_HPP_
