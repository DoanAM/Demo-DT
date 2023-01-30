// (C) 2018-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_CALCULATIONTHREADPARAMS_HPP_
#define MW_CALCULATIONTHREADPARAMS_HPP_

#include "mwDllImpExpDef.hpp"

namespace misc
{
	class MW_5AXUTIL_API mwCalculationThreadParams
	{
	public:
		enum Priority
		{
			IDLE,
			LOWEST,
			BELOW_NORMAL,
			NORMAL,
			ABOVE_NORMAL,
			HIGHEST,
			CRITICAL,
			BACKGROUND_START,
			BACKGROUND_END
		};

		static void SetThreadPriority(const Priority);
		static Priority GetThreadPriority();
	private:
		static void Init();

		static Priority m_priority;
	};
}
#endif //MW_CALCULATIONTHREADPARAMS_HPP_