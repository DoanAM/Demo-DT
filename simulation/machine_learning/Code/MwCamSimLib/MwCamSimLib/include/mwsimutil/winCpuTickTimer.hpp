// (C) 2003-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_WINCPUTICKTIMER_HPP_
#define MW_WINCPUTICKTIMER_HPP_
#include "mwDllImpExpDef.hpp"

namespace misc
{
	class MW_5AXUTIL_API winCpuTickTimer
	{
	public:
		winCpuTickTimer();
		~winCpuTickTimer();

		/// Initializes or resets timer.
		void StartClock();

		/// @return time since last call to StartClock() in seconds.
		double EndClock();

		/// @return time since last call to StartClock() in seconds.
		double GetClock();

#if defined (_WIN32)
		/// @return CPU frequency in MHz.
		static size_t GetCPUFrequency();
#endif

	private:
		struct Data;
		Data* pData;
	};
}

#if defined (_WIN32)

namespace misc
{
	class MW_5AXUTIL_API winCpuTickTimerRestartable
	{
	public:
		winCpuTickTimerRestartable();

		/// Initializes or resets the EndClock() timer.
		/// Note: Does not interact with the GetClock() timer.
		void StartClock();

		/// Stops current period and adds its value to GetClock() timer.
		/// @return time since last call to StartClock() in seconds.
		double EndClock();

		/// Resets the GetClock() timer to zero. 
		/// Note: Does not interact with StartClock(), EndClock().
		void ResetClock();

		/// Returns the sum of all previously finished periods (updated via EndClock()).
		/// @return time in seconds.
		double GetClock();

	protected:
		double m_totalTime;
		winCpuTickTimer m_clock;
		bool m_isStoped;
	};
}

#else  // linux
namespace misc
{
	/// Empty dummy implementation.
	class MW_5AXUTIL_API winCpuTickTimerRestartable
	{
	public:
		winCpuTickTimerRestartable ()
		{}
		void ResetClock()
		{}
		void StartClock()
		{}
		double EndClock()
		{
			return 0;
		}
		double GetClock()
		{
			return 0;
		}

	protected:
		double m_totalTime;
		winCpuTickTimer m_clock;
	};
}
#endif
#endif	//	MW_WINCPUTICKTIMER_HPP_
