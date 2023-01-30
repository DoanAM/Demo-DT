// (C) 2015-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWVKEY_HPP_
#define MW_MWVKEY_HPP_
#include "mwStringConversions.hpp"


namespace misc 
{
	class MW_5AXUTIL_API mwVKey
		{
		public:
			mwVKey();		
			mwVKey(unsigned int code, bool isExt = false);
			bool operator==(const misc::mwVKey &other) const;
			bool operator!=(const misc::mwVKey &other) const;
			unsigned int GetCode() const;
			bool IsExtended() const;
			bool IsInitialized() const;
		private:
		#pragma warning(push)
		#pragma warning(disable : 4251)
		
			unsigned int	m_code;
			bool			m_isExtended;
		
		#pragma warning(pop)
		};	
}
#endif	//	MW_MWVKEY_HPP_
