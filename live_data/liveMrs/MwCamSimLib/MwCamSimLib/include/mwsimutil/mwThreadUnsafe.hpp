// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWTHREADUNSAFE_HPP_
#define MW_MWTHREADUNSAFE_HPP_
#include "mwDllImpExpDef.hpp"

#if defined (_WIN32)
#include "mwStringConversions.hpp"
#elif (defined(__linux__) || defined(__APPLE__)) 
#include "mwException.hpp"

#include <pthread.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#endif

namespace misc
{
	//!This class represents a thread.
	class MW_5AXUTIL_API mwThreadUnsafe
	{
	public:
		enum ThreadPrio
		{
			MW_PRIO_HIGHEST,
			MW_PRIO_HIGH,
			MW_PRIO_LOW,
			MW_PRIO_IDLE,
			MW_PRIO_LOWEST,
			MW_PRIO_NORMAL,
			MW_PRIO_REALTIME
		};

		//!SetPriority
		/*!Sets threads priority.
			\param newPrio new priority level
		*/
		bool SetPriority(const ThreadPrio &newPrio) ;
		
		//!Set Priority from current thread
		/*!Set Priority from current thread
		*/
		bool SetPriorityFromCurrentThread();

		//!GetPriority
		/*!Gets threads priority.
			\returns priority level
		*/
		int GetPriority() ;
	
		//!Compelled run
		/*!Runs the thread in any circumstances.
		*/
		void CompelledRun() ;

		//!Run
		/*!Runs the thread.
		*/
		void Run() ;

		//!Stop
		/*!Terminates the thread.
		*/
		void Stop() ;

		//!Suspend
		/*!Suspends the thread.
		*/
		void Suspend() ;

		//!Resume
		/*!Resumes the thread.
		*/
		void Resume() ;
		
		//!Is running ?
		/*!Is running ?
			\returns <b>true</b> if thread is STILL_ACTIVE
					 <b>false</b> else
		*/
		bool IsRunning();

		//!Get return value.
		/*!Gets return value.
			\returns return value
		*/
		unsigned long GetReturnValue();

		//! Wait for thread
		/*! Wait for thread to change state to signaled
			\param milliseconds time to wait
		*/
		unsigned long Wait(const unsigned long milliseconds) const;

		//! Get thread handle
		void* GetHandle() const
		{
			#if defined (_WIN32)
			return threadH;
			#elif (defined(__linux__) || defined(__APPLE__)) 
			return reinterpret_cast<void*>(const_cast<pthread_t*>(&threadID));
			#endif
		}
		
		//! Get thread ID
		#if (defined(__linux__) || defined(__APPLE__))
		pthread_t GetThreadID() const
		#else
		unsigned long GetThreadID() const
		#endif
		{
			return threadID;
		}

	protected:
		virtual int ThreadFunction() = 0;

		//!Default constructor.
		/*!Creates a new thread.
		*/
		mwThreadUnsafe();

		//!Destructor
		virtual ~mwThreadUnsafe();

	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	

		int ConvertPriority(const ThreadPrio prio);

#if defined (_WIN32)
		unsigned long		threadID;
		void				*threadH;
		unsigned long		nReturnValue;
#elif (defined(__linux__) || defined(__APPLE__)) 
		pthread_t 		threadID;
		mutable std::atomic_bool m_isRunning;
		mutable bool m_isJoinable;
		mutable std::mutex	m_mtx;
		mutable std::condition_variable	m_cv;
#endif

#if defined (_WIN32)
		static unsigned long __stdcall ThreadCallBack( void *params );
#elif (defined(__linux__) || defined(__APPLE__)) 
		static void* ThreadCallBack( void *params );
#endif
	
	#pragma warning(pop)
	};
};
#endif	//	MW_MWTHREADUNSAFE_HPP_
