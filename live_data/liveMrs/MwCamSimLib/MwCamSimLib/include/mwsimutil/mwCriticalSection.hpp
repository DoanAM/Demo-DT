// (C) 2008-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCRITICALSECTION_HPP_
#define MW_MWCRITICALSECTION_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
	namespace detail
	{
		class mwCriticalSectionImpl;
	}

	/**
	This class provide operating system independent support for thread synchronization using critical section.
	Critical sections mark areas of code that should not be accessed simultaneously. Entering a critical section,
	prevents other threads to enter the same critical section at the same time. 
	*/
	class MW_5AXUTIL_API mwCriticalSection
	{
	public:
		mwCriticalSection();
		~mwCriticalSection();

		//! Enters a critical section
		/**
		Calling this function will wait until the critical section can be entered.
		Entering the critical section on the same thread multiple times is possible without blocking.
		
		\note Instead of calling \ref Enter, \ref Leave and \ref TryEnter explicitly,
		it is recommended to use \ref mwAutoCriticalSection and \ref mwAutoCriticalSectionTry
		*/
		void Enter();
		
		//! Leaves a critical section
		/**
		Leaves the critical section. Other threads waiting for the critical section will automatically try to enter the critical section.
		Calling this function without entering the critical section on the same thread before, results in undefined behavior.

		\note Instead of calling \ref Enter, \ref Leave and \ref TryEnter explicitly,
		it is recommended to use \ref mwAutoCriticalSection and \ref mwAutoCriticalSectionTry
		*/
		void Leave();

		/**
		Calling this function will immediately return indicating if a critical section was successfully entered or not.
		The critical section cannot be entered when on other thread already has access to the critical section.
		Entering the critical section on the same thread multiple times is possible without blocking.
		\return True, if the critical section was entered successfully, otherwise false.
		\note Instead of calling \ref Enter, \ref Leave and \ref TryEnter explicitly,
		it is recommended to use \ref mwAutoCriticalSection and \ref mwAutoCriticalSectionTry
		\warning Ignoring that this function returns false, can result in race conditions
		*/
		bool TryEnter();

		MW_DEPRECATED("Deprecated since 2019.08, please use Enter() instead")
		int Lock() const 
		{
			const_cast<mwCriticalSection&>(*this).Enter();
			return 0;
		}

		MW_DEPRECATED("Deprecated since 2019.08, please use Leave() instead")
		void Unlock() const
		{
			const_cast<mwCriticalSection&>(*this).Leave();
		}

		MW_DEPRECATED("Deprecated since 2019.08, please use TryEnter() instead")
		bool TryLock() const
		{
			return const_cast<mwCriticalSection&>(*this).TryEnter();
		}

	private:
		mwCriticalSection(const mwCriticalSection& /*other*/) {}
		mwCriticalSection& operator=(const mwCriticalSection& /*other*/) { return *this; }

	private:
		detail::mwCriticalSectionImpl* m_pImpl;
	};

	/**
	\ref mwAutoCriticalSection securely marks a critical section of code that needs to be synchronized using a \ref mwCriticalSection.
	Using the RAII principle (resource acquisition is initialization), \ref mwAutoCriticalSection guarantees thread-safe access 
	to that particular region of code.
	*/
    class MW_5AXUTIL_API mwAutoCriticalSection
    {
    public:
		MW_DEPRECATED("Deprecated since 2019.08, please pass criticalSection as non-const (or mutable) reference")
        explicit mwAutoCriticalSection(const mwCriticalSection& criticalSection) :
			m_CriticalSection(const_cast<mwCriticalSection&>(criticalSection))
		{ 
			m_CriticalSection.Enter();
		}

		explicit mwAutoCriticalSection(mwCriticalSection& criticalSection) :
			m_CriticalSection(criticalSection)
		{
			m_CriticalSection.Enter();
		}

        ~mwAutoCriticalSection() 
		{
			m_CriticalSection.Leave();
		}

    private:
        mwAutoCriticalSection(const mwAutoCriticalSection& /*other*/);
        mwAutoCriticalSection& operator=(const mwAutoCriticalSection& /*other*/);

    private:
        mwCriticalSection& m_CriticalSection;
    };

	/**
	\ref mwAutoCriticalSectionTry securely marks a critical section of code that needs to be synchronized using a \ref mwCriticalSection, 
	similar to \ref mwAutoCriticalSection. In contrast, \ref mwAutoCriticalSectionTry does not wait for thread-safe access, 
	but immediately indicates that thread-safe access could not be acquired.
	*/
	class MW_5AXUTIL_API mwAutoCriticalSectionTry
	{
	public:
		MW_DEPRECATED("Deprecated since 2019.08, please pass criticalSection as non-const (or mutable) reference")
		explicit mwAutoCriticalSectionTry(const mwCriticalSection& criticalSection) 
			: m_CriticalSection(const_cast<mwCriticalSection&>(criticalSection))
		{ 
			m_AcquiredLock = m_CriticalSection.TryEnter();
		}

		explicit mwAutoCriticalSectionTry(mwCriticalSection& criticalSection)
			: m_CriticalSection(criticalSection)
		{
			m_AcquiredLock = m_CriticalSection.TryEnter();
		}

		~mwAutoCriticalSectionTry() 
		{
			if(m_AcquiredLock)
				m_CriticalSection.Leave();
		}

		//! Checks whether thread-safe access to critical section was achieved
		/**
		\return True if thread-safe access to critical section is guaranteed, otherwise false
		\warning Ignoring that this function returns false, can result in race conditions
		*/
		bool AcquiredLock() const
		{
			return m_AcquiredLock;
		}

	private:
		mwAutoCriticalSectionTry(const mwAutoCriticalSectionTry& /*other*/);
		mwAutoCriticalSectionTry& operator=(const mwAutoCriticalSectionTry& /*other*/);

	private:
		mwCriticalSection& m_CriticalSection;
		bool m_AcquiredLock;
	};
}
#endif	//	MW_MWCRITICALSECTION_HPP_
