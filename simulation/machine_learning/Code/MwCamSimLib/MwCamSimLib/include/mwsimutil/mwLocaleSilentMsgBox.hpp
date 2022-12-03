// (C) 2003-2021 by ModuleWorks GmbH
// Owner: 5Axis Core

#ifndef MW_MWLOCALESILENTMSGBOX_HPP_
#define MW_MWLOCALESILENTMSGBOX_HPP_
#include "mwLocale.hpp"
#include "mwLogger.hpp"
#include "mwException.hpp"


namespace interact
{
	//!Decorator class that does not pop up Message boxes
	class MW_5AXUTIL_API mwLocaleSilentMsgBox : public mwLocaleDecorator
	{
	public:
		//!Constructor
		/*!
			\param core the enclosed instance of mwLocaleIntf, accepts null but returns warnings on GetMsg in this case
			\param messagesLogger, if provided then MsgBox texts are sent to it, other way they are just stacked in a mwException object
		*/
		mwLocaleSilentMsgBox(const misc::mwAutoPointer<mwLocaleIntf>& core, misc::mwAutoPointer<misc::mwLogger> messagesLogger= NULL);

		//!We override this method in order not to display a message box
		/*!We accumulate the messages in a stacked mwException or (not and) send them to constructor passed logger
			\param text the message to log or accumulate
			\param title the message title, it's ignored in this version
			\param nType this is neither logged or accumulated for now
			\returns IDCANCEL/IDNO/IDABORT/IDOK,in this priority order, based on nType 
		*/
		virtual int MsgBox(const misc::mwstring& text,const misc::mwstring& title =_T(""), unsigned int nType = MW_MB_DEFAULT) const;

		//!Simple delegation to the enclosed mwLocaleIntf if it's not null
		/*!For null core, it keep the idea of "silent", and don't throw, but it 
			returns a string warning that a message for a specific no and section was requested while there
			was no localization initialized
		*/
		virtual const misc::mwstring GetMsg(const misc::mwstring& section, unsigned int msgNo) const;

		//!Returning the stacked exception (null if no exception so far)
		const misc::mwAutoPointer<misc::mwException> GetException() const;

		//!if the global mwLocale is mwLocaleSilentMsgBox and there is something accumulated then throw the enclosed exception
		static void ThrowException();

		//allow pimpl 
		virtual ~mwLocaleSilentMsgBox();

		//! returns the standard warning message for uninitialized interact::mwLocaleIntf object
		static const misc::mwstring& GetWarningMessageForUnitializedLocalizationHandler();

	private:
		//!Set exception back to null
		void ClearException();

		mutable misc::mwAutoPointer<misc::mwException>	m_exception;
		mutable misc::mwAutoPointer<misc::mwLogger>		m_messagesLogger;
		misc::mwAutoPointer<interact::mwLocaleIntf>		m_core;

		static const misc::mwstring m_warningLocalizationHandlerUninitialized;
	};
}
#endif	//	MW_MWLOCALESILENTMSGBOX_HPP_
