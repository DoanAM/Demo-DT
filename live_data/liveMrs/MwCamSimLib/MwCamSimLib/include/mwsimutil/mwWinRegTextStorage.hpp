// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWWINREGTEXTSTORAGE_HPP_
#define MW_MWWINREGTEXTSTORAGE_HPP_
#if defined (_WIN32)

#include "mwString.hpp"
#include "mwDllImpExpDef.hpp"

namespace misc
{
	class MW_5AXUTIL_API mwWinRegTextStorage
	{
	public:
		mwWinRegTextStorage(
			const mwstring& companyName,
			const mwstring& applicationName, 
			const mwstring& sectionName);

		bool GetParamBool(const mwstring& key, const mwstring& addPath = _T(""));
		void SetParamBool(const mwstring& key, bool value, const mwstring& addPath = _T(""));

		mwstring GetParamString(const mwstring& key, const mwstring& addPath = _T(""));
		void SetParamString(const mwstring& key, const mwstring& value, const mwstring& addPath = _T(""));
	protected:

		bool GetKey(const mwstring& iName, mwstring& oValue, const mwstring& addPath = _T(""));
		bool SetKey(const mwstring& iName, const mwstring& iValue, const mwstring& addPath = _T(""));
		

		mwstring m_registryPath;
		
	};	
}

#endif
#endif	//	MW_MWWINREGTEXTSTORAGE_HPP_
