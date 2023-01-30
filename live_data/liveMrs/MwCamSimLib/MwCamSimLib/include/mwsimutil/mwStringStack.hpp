// (C) 2012-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWSTRINGSTACK_HPP_
#define MW_MWSTRINGSTACK_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwString.hpp"
#include <list>

namespace misc
{
	class MW_5AXUTIL_API mwStringStack
	{
		public:
			typedef std::list< misc::mwstring > reasonStack;

			misc::mwstring GetCompleteMessage() const;

			void Add( const misc::mwstring &newReason );

		private:
		#pragma warning(push)
		#pragma warning(disable : 4251)
		

			reasonStack		m_reasons;
	
	#pragma warning(pop)
	};//class __mwStringStack_hpp__

};//namespace misc
#endif	//	MW_MWSTRINGSTACK_HPP_
