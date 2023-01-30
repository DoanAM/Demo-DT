// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWRESOURCEDLL_HPP_
#define MW_MWRESOURCEDLL_HPP_
#if defined (_WIN32)

#include "mwStringConversions.hpp"
#include <map>
#include <windows.h>
#include "mwResourceIntf.hpp"
#include "mwNeutralResourceDll.hpp"
#include	"mwDllImpExpDef.hpp"

namespace misc
{
	//!This class is used for interacting with a resource dll library
	class  MW_5AXUTIL_API mwResourceDll : public mwResourceIntf 
	{
	 
	public:
		static const int MWMSGMAP_ID;
		static const misc::mwstring MWMSGMAP_NAME;


		typedef std::pair <MsgNumT, misc::mwstring> StringTableMapKey;
		typedef std::map <StringTableMapKey, MsgNumT> StringTableMap;
		
		//!Constructor
		mwResourceDll();

		//!Constructor
		/*!if no language is set the current thread language will be used
			\param fileName name of the resource dll file
		 */
		mwResourceDll(const misc::mwstring& fileName);

		//!Constructor
		/*!
			\param fileName name of the resource dll file
			\param language language for resource to be used. Use the MAKELANGID macro to create this parameter
		 */
		mwResourceDll(const misc::mwstring& fileName,const UINT language);

		//!Destructor
		~mwResourceDll() MW_OVERRIDE;
		
		//!	Unloads the resource dll file
		void Unload();

				
		//!Get text string by number
		/*!This function returns a string with a given number
		\param msgNum number of the text string to get
		\returns the requested message
		*/
		virtual const misc::mwstring GetMsg(MsgNumT msgNum ) const;


		//!Get text string by number and section name
		/*!This function returns a string with a given number and section name
		\param msgNum number of the text string to get
		\param sectionName name of the section from where to get text string
		\returns the requested message
		*/
		virtual const misc::mwstring GetMsg(
			MsgNumT msgNum, misc::mwstring sectionName ) const;

		//!Get the mapped message ID (from MSGMAP) given the internal message ID (from *.txt)
		/*!Finds the row in the MSGMAP section of the resource dll which contains
			the internal message ID (Eg. from sampleintegration.txt, 5axui.txt)
			and returns the mapped message ID. (Eg. from cvs_msgmap.bin)
		\return the message id mapped to the old message id
		\throw mwException if the message ID was not found
		Example: if the MSGMAP contains a row: #16#5axui-PARAMPAGES#10121#
			and if the given message ID is 10121, it returns 16
		*/
		MsgNumT GetMappedMsgId(MsgNumT msgNum, const misc::mwstring& sectionName) const;

		//!Set the name of the resource dll file to get resources from
		/*!Reads resources from the library file with a given name
		   \param fileName name of the resource dll file
		*/
		void SetFile( const misc::mwstring& fileName );

		void SetFile(const misc::mwstring &fileName, const mwResourceDll::StringTableMap &map);

		const StringTableMap & GetResourceStringTableMap()const;

		//!Gets the name of the resource dll file
		/*
			\returns the name of resource dll library 
		*/
		const misc::mwstring& GetFile() const;


		//!Gets the handler of resource dll library
		/*
			\returns HINSTANCE - handler of the resource dll library  
		*/
		const HINSTANCE GetResourceDllHandler() const;

		//! gets resources Language
		/*! 			
				\returns the resources Language
		*/
		inline const UINT GetLanguage() const
		{ return m_Language;};

		//! sets resources Language
		/*! 			
				\param vLanguage the new Language. Use the MAKELANGID macro to create this parameter
		*/
		inline void SetLanguage(const UINT vLanguage)
			{m_Language=vLanguage;};


		//!returns true if resource is initialized
		virtual bool IsInitialized() const;


	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	

			//!Gets a string from the string table of resource dll
			/*
				\param 	messageID the ID  of the string to be retrieved
				\returns the string associated with messageID	
			*/
			const misc::mwstring GetMessageFromDll(MsgNumT messageID) const;

			//!Gets a string from the string table of resource dll
			/* search the string for specified language, if it does not exist for that language then is 
				using first string table available
				\param 	HINSTANCE the instance of resource dll
				\param 	uId the ID  of the string to be retrieved
				\param 	langId language id
				\returns the string associated with messageID	
			*/
			const misc::mwstring GetResourceString(HINSTANCE hinst, MsgNumT uId, UINT langId) const;

			
			//!Initialize resource dll - loads .dll file into memory, performs additional initializations 
			void InitRes();


			//!Parse a custom resource from resource dll file called MSGMAP that contains the mappings
			/*between old message ID's from .txt msgs. files (i.e. sampleintegration.txt, 5axui.txt)
			  and the new message ID's from string table of resource dll.
			  A std::map object is build during this process of reading MSGMAP resource
			*/
			void MapStringTable();

			//!tests if the resource was initialize
			/*throws exception if the resource is not initialize
			*/
			void ValidateRes() const;

			UINT m_Language;
			StringTableMap m_resdllMap;
			mutable misc::mwstring m_message;//!stores string message loaded from resource dll and returned
											 //by GetMsg functions 
			misc::mwstring m_defaultSection;

			mwNeutralResourceDll m_resourceDll;
	
	#pragma warning(pop)
	};
};

#endif
#endif	//	MW_MWRESOURCEDLL_HPP_
