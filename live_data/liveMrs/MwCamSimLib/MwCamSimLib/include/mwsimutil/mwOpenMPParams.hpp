// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWOPENMPPARAMS_HPP_
#define MW_MWOPENMPPARAMS_HPP_
#include "mwDllImpExpDef.hpp"
#include "mwWinRegOrCustomParamStorage.hpp"
#ifdef _OPENMP
#include <omp.h>
#endif
#include <cstddef>

namespace misc
{
	/// mwOpenMPParams is a static class that reads/stores OpenMP-related
	/// parameters from the param storage (on windows it is registry by default)
	/// the class is static so that nobody would be tempted to pass some
	/// instance by reference. the getThreadCount could use a local defined
	/// member for quick access, but in such situation a critical section
	/// needs to be maintained to ensure safe access to the member(s)
	class MW_5AXUTIL_API mwOpenMPParams
	{
	public:
		~mwOpenMPParams();
		static int getThreadCount();
		static void saveToRegistry(const int &threadCnt);
		static void deInitialize();
		
		static void SetDebugThreadCount(const unsigned long& debugThreadCount, const bool saveToStorage = true);
		
		static void SetThreadCount(const unsigned long threadCount, const bool saveToStorage = false);
		
		static unsigned long GetDebugThreadCount();
		
		/// Return index of current openmp thread
		/// main thread is 0. So if openMP is not activated the function returns 0
		/// @returns index of current thread
		static size_t GetThreadNumber()
		{
#if defined(_OPENMP)
			return omp_get_thread_num();
#else
			return 0;
#endif
		}
		
		static unsigned long  getProcessorCount();
		
		static bool IsDebugThreadCountSetFlg();
		
		static void recheckThreadCount();
		
		static void ChangeCurrentThreadPriorityToBelowNormal();
		
		static bool IsInParallelSection();

	private:
		mwOpenMPParams();
		static void initialize();
		static unsigned long SaveLoadSettingStorage(const bool doSave, const bool isDebug, const unsigned long threadCnt);
		static unsigned long  m_threadCount;
		static unsigned long  m_debugThreadCount;

		static bool m_isDebugThreadCountSetFlg;
#if !defined(UNDER_CE)
		static misc::mwWinRegOrCustomParamStorage* m_settingsStoragePtr;
#endif
	};


	//! mwOmpThreadPriorityLower
	/** Usage:
	1)
	@code{.cpp}
	#pragma omp parallel
	{
		mwOmpThreadPriorityLower lowPrio;
		...
		#pragma omp for
		...
	}
	@endcode
	2)
	@code{.cpp}
	mwOmpThreadPriorityLower lowPrio(false);
	#pragma omp parallel for private(lowPrio)
	{
	...
	}
	@endcode
	*/
	class MW_5AXUTIL_API mwOmpThreadPriorityLower
	{
	public:
		//! ctor lower current omp thread priority
		// Use delayToCopy to instantiate this class and set the priority later.
		// A common use case is before a omp parallel loop with private(theThreadPriorityLowerObject).
		mwOmpThreadPriorityLower(const bool setPriority = true);
		mwOmpThreadPriorityLower(mwOmpThreadPriorityLower&);
		//! dtor restore current omp thread priority
		~mwOmpThreadPriorityLower();
	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	
		// forbidden
		mwOmpThreadPriorityLower& operator=(const mwOmpThreadPriorityLower&);
		int		m_priority;
		bool	m_prio_changed;
	
	#pragma warning(pop)
	};

};
#endif	//	MW_MWOPENMPPARAMS_HPP_
