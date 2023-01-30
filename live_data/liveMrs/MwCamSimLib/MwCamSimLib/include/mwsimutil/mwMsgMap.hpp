// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMSGMAP_HPP_
#define MW_MWMSGMAP_HPP_
#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwDeprecated.hpp"
#include <vector>

namespace misc
{
	class mwFileName;
	class mwIFStream;

	//!This class is used to interact with a msgmap object used in the process of generating our
	//!5axui_res.dll file
	class MW_5AXUTIL_API mwMsgMap
	{
		public:
			typedef unsigned long MsgNumT;

			struct  MsgMapEntry
			{
			public:
				MsgMapEntry();
				MsgMapEntry(MsgNumT newMsgID,
							misc::mwstring sectionName,
							MsgNumT oldMsgID);

				const MsgNumT GetNewMsgID() const;
				const MsgNumT GetOldMsgID() const;
				const misc::mwstring& GetSectionName() const;
			private:
				MsgNumT m_newMsgID;//new message id, that was generated 
				MsgNumT m_oldMsgID;//oldmessageID, from .txt message file
				misc::mwstring m_sectionName;//the name of the section that oldmessageID belongs to
			};

			typedef std::vector <MsgMapEntry> mapEntries;
			typedef MsgMapEntry mapEntry;
#pragma deprecated(mapEntry)	// use MsgMapEntry
			typedef mapEntries::iterator ItMapEntries;
			typedef mapEntries::const_iterator ConstItMapEntries;
			
			//!Default constructor, builds an empty map
			mwMsgMap ();
			
			//!construct a map by passing a file name
			/*
			 This constructor is used in  mwRCFileGen when loading a map used for comparison (in order to
			 prevent string table shifting)
			*/
			mwMsgMap (const misc::mwFileName& mapFileName);
			
			//!Construct a map by reading from a memory stringstream, obtained with LockResource
			/*
				This constructor is used in  mwResourceDll when loading the map from resource dll file
				
			*/
			mwMsgMap (std::istringstream& inStream);
			
			//!Copy - constructor
			mwMsgMap (const mwMsgMap& toCopy);
			
			//!Copy operator
			const mwMsgMap& operator = (const mwMsgMap& toCopy);
			
			//!Returns all entries from map
			const mapEntries& GetMapEntries() const;
			
			
			//!Search in a map, if an entry specified by oldMessageID and oldmessageSection exists
			/*
				\param oldMsgID, the ID of old message from .txt message file
				\param sectionName, the name of the section to which oldMsgID belongs to.
				\returns the newMsgID of the first entry that matches search criteria.
					If no entry is found, returns an invalid mwMsgMap::MsgNumT(-1)
			*/
			MsgNumT GetNewMsgGivenOldMsgIDAndSection(
				const MsgNumT& oldMsgID,
				const misc::mwstring& sectionName) const;
			


			
			//!Search in a map, if an entry specified by oldMessageID and oldmessageSection exists
			/*
				\param oldMsgID, the ID of old message from .txt message file
				\param sectionName, the name of the section to which oldMsgID belongs to.
				\returns a const_iterator to the first entry that match search criteria.
				If no entry is found, end() iterator is returned
			*/
			MW_DEPRECATED("Deprecated since 2020.08. Please use GetNewMsgGivenOldMsgIDAndSection")
			ConstItMapEntries GetEntryGivingOldMsgIDAndSection(
				const MsgNumT& oldMsgID,
				const misc::mwstring& sectionName) const;

			MW_DEPRECATED("Deprecated since 2020.08. Please use GetNewMsgGivenOldMsgIDAndSection or GetMapEntries")
			ConstItMapEntries GetMapBegin() const;

			MW_DEPRECATED("Deprecated since 2020.08. Please use GetNewMsgGivenOldMsgIDAndSection or GetMapEntries")
			ConstItMapEntries GetMapEnd() const;

		private:
		#pragma warning(push)
		#pragma warning(disable : 4251)
			
			
			//!builds the map by reading from an input stream
			void BuildMapFromStringStream(std::istringstream& inStream);
			
			void BuildMapFromFileStream(misc::mwIFStream& inFileStream);
			
			//!Test if a line readed from an external source is a valid map entry
			const bool ValidMapEntry(const misc::mwstring& lineRead) const;
			
			//!returns a map entry from a line readed from input stream
			const MsgMapEntry GetMapEntry(const misc::mwstring& lineRead) const;
			
			void TrimCRFromBuf(char* buf,const size_t bufSize) const;
			
			void AddMapEntry(const misc::mwstring& lineRead);
			


			mapEntries m_mapEntries;
			

	
	#pragma warning(pop)
	};

};//end namespace
#endif	//	MW_MWMSGMAP_HPP_
