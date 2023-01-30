// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINREGTEXTPATCHUTILS_HPP_
#define MW_MWWINREGTEXTPATCHUTILS_HPP_
#if defined (_WIN32)

#include "mwWinRegTextStorage.hpp"
#include <vector>

namespace misc
{
	struct MW_5AXUTIL_API mwPatchRegEntry
	{
		mwPatchRegEntry(mwstring pathToClient, mwstring pathToMwPatch, bool activ, bool open_5axui, bool dumpBin)
			: m_pathToClient(pathToClient)
			, m_pathToMwPatch(pathToMwPatch)
			, m_activ(activ)
			, m_open_5axui(open_5axui)
			, m_dumpBin(dumpBin)
		{
		}

		bool operator == (const mwPatchRegEntry& toCompare) const
		{
			return m_pathToClient == toCompare.m_pathToClient &&
				m_pathToMwPatch == toCompare.m_pathToMwPatch &&
				m_activ == toCompare.m_activ &&
				m_open_5axui == toCompare.m_open_5axui &&
				m_dumpBin == toCompare.m_dumpBin;
		}
		bool operator != (const mwPatchRegEntry& toCompare) const
		{
			return !(*this == toCompare);
		}

		mwstring        m_pathToClient; // who use mwGeoLib.dll or 5axmsurf.dll
		mwstring        m_pathToMwPatch; // mwpatch application 
		bool            m_activ;
		bool            m_open_5axui;
		bool            m_dumpBin;
	};// end class mwPatchRegEntry
	class MW_5AXUTIL_API mwWinRegTextPatchUtils : public mwWinRegTextStorage
	{
	public:
		typedef std::vector<mwPatchRegEntry>  mwPatchRegEntryVect;


		mwWinRegTextPatchUtils(); // for mw-patch
		mwWinRegTextPatchUtils(const mwstring& applicationClient);// for application client

		mwPatchRegEntryVect GetRegEntryVect() const;
		void SetRegEntryVect(const mwPatchRegEntryVect& patchRegEntryVect);
		bool Open5AxUIDlg(const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
		void EnablePatch(const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
		void DisablePatch(const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
		mwPatchRegEntryVect DeleteEntry(const size_t id);
		mwstring ReadDumpBinPath();
		bool DumpBin(const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
		void WriteDumpBinPath(const mwstring& path);
		
		bool IsPatchActive(); // just for client application
		mwstring GetPathnameToMwPatch(); // just for client application
		

		void SetTest(const bool test); // temp, review
		bool GetTest() const; // temp , review

		static misc::mwstring GetCompanyName();
		static misc::mwstring GetApplicationName();
		static misc::mwstring GetSectionName();

	protected:

#pragma warning(push)
#pragma warning(disable : 4251)
		enum Type
		{
			MWPATCH = 0,//for mwPatch application...
			MWGEOLIB//for mwGeoLib.dll...
		};

		static const TCHAR REG_COMPANY_NAME[];
		static const TCHAR REG_APP_NAME[];
		static const TCHAR REG_SECTION_NAME[];
		static const TCHAR REG_KEY_ACTIVATE_PATCH[];
		static const TCHAR REG_KEY_PATH_TO_FOLDER[];
		static const TCHAR REG_KEY_OPEN_5AXUI[];
		static const TCHAR REG_KEY_NR_OF_PATCHES[];
		static const TCHAR REG_KEY_MWGEOLIBDLL_PATH[];
		static const TCHAR REG_KEY_TEST[];
		static const TCHAR REG_KEY_DUMP_BIN[];
		static const TCHAR REG_KEY_DUMP_BIN_PATH[];

		mwPatchRegEntryVect m_mwPatchRegEntryVect;

		const Type      m_type;
		bool            m_activ;
		bool            m_test;
		size_t    m_number;
#pragma warning(pop)

		size_t GetParamSize_t(const mwstring& key);
		void SetParamSize_t(const mwstring& key, const size_t value);
		bool CreateNewEntry(const mwstring& iName);
		void Find(const mwstring& applicationClient);
		void Read();
		void DeleteEntry(const mwstring& key);
		void DeleteDuplicateEntrys();
		mwPatchRegEntry GetAt(const size_t key);
		void SetAt(const size_t key, const mwPatchRegEntry& patchRegEntry);
		void AddAt(const mwPatchRegEntry& patchRegEntry);
		void EnableOrDisable(const bool ed, const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
		void MagicTrick(mwstring& path); 
		int FindId(const mwstring& mwpatch, const mwstring& applicationClient = _T("") /*for old clients*/);
	private:
		mwWinRegTextPatchUtils& operator=(const mwWinRegTextPatchUtils& tmp);
	};
}
#endif
#endif	//	MW_MWWINREGTEXTPATCHUTILS_HPP_
