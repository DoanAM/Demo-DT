// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWAUTOPOINTER_HPP_
#define MW_MWAUTOPOINTER_HPP_
#include "mwWindowsInterlocked.hpp"
#include "mwException.hpp"
#include "mwAlignmentDefs.hpp"
#include "mwAvoid_Warnings.hpp"
#include "mwDeprecated.hpp"
#include "mwDefines.hpp"
#include "mwLanguageFeatures.hpp"
#include "mwNull.hpp"
#include <functional>
#include <typeinfo>
#include <utility>

#ifndef MW_USE_VS2008_COMPATIBILITY
#include <memory>
#include <type_traits>
#endif


#define THREAD_SAFE_MW_AUTO_POINTER

namespace misc
{
	template<class T> class mwAutoPointer;

	namespace detail
	{
		struct deleterBase
		{
			virtual ~deleterBase() {}
			virtual void callDelete() = 0;
			virtual const void* getDeleter(const std::type_info&) const
			{
				return MW_NULL;
			}
		};

#pragma warning(push)
#pragma warning(disable : 4503 4996)
		template<class T>
		struct pointerDeleter : deleterBase
		{
			explicit pointerDeleter(T* ptr) : m_ptr(ptr) {}
			void callDelete()
			{
				delete m_ptr;
			}
		private:
			T* m_ptr;
		};
#pragma warning(pop)

		template<class T, class Deleter>
		struct customDeleter : deleterBase
		{
			customDeleter(T* ptr, const Deleter& d)
				: m_deleter(d),
				m_ptr(ptr)
			{}
#ifndef MW_USE_VS2008_COMPATIBILITY
			customDeleter(T* ptr, Deleter&& d) : m_deleter(std::move(d)), m_ptr(ptr)
			{}
#endif

			void callDelete()
			{
				m_deleter(m_ptr);
			}

			const void* getDeleter(const std::type_info& ti) const
			{
				//I prefer using std::addressof over operator& for getting the address of an object.
				//But as the MSVC-implementation does it the same way, I will stick to it for consistency.
				//Otherwise a user might pass a Deleter that overrides operator& and everything works fine with the misc::mwAutoPointer
				//and then when we try to switch to the std::shared_ptr, the programs behavior changes.
				return (ti == typeid(Deleter) ? &m_deleter : MW_NULL);
			}

		private:
			customDeleter& operator=(const customDeleter&) { return *this; }
			//TODO: Put them in a compressed pair.
			Deleter m_deleter;
			T* m_ptr;
		};

		template<class Deleter, class T>
		Deleter* GetDeleterImpl(const misc::mwAutoPointer<T>& p);

#ifndef MW_USE_VS2008_COMPATIBILITY
		template<class T>
		struct SharedPtrHoldingDeleter
		{
			std::shared_ptr<T> sp;

			void operator()(T*) const {}
		};
#endif
	}

	template<class Archive, class T>
	void save(Archive& archive, const mwAutoPointer<T>& autoPointer, const unsigned int);

	template<class Archive, class T>
	void load(Archive& archive, misc::mwAutoPointer<T>& autoPointer, const unsigned int);
	/*!	\brief	The autoPtrData struct

	*/
	struct autoPtrData
	{
	public:
		void IncReferenceCount()
		{
			ref_cnt++;
		};


		void DecReferenceCount()
		{
			ref_cnt--;
		};

		void SetReferenceCount(const long& val)
		{
			ref_cnt = val;
		};

		long GetReferenceCount() const
		{

			return ref_cnt;

		};

		void SetOwnedPtr(const bool& val)
		{
			owned = val;

		};

		bool GetOwnedPtr() const
		{
			return owned;
		};

		void LockPointer() {
			// http://msdn.microsoft.com/en-us/library/windows/desktop/ms683560(v=vs.85).aspx

			//while isLocked != 0 (so is == 1), if isLocked == 0 set it to 1
			while(detail::WindowsInterlocked::mwInterlockedCompareExchange(&isLocked,1,0) )
				detail::WindowsInterlocked::mwSwitchToThread();
		};

		void UnlockPointer() {
			detail::WindowsInterlocked::mwInterlockedExchange(&isLocked,0);
		};

		detail::deleterBase*& deleter()
		{
			return deleter_;
		}

		~autoPtrData() {
			UnlockPointer();
			//The deleter will be deleted here and not from within the mwAutoPointer<T>
			//This probably makes no difference.
			delete deleter_;
		}

		inline autoPtrData()
		{
			ref_cnt	= 0;
			owned	= false;
			isLocked = 0;
			deleter_ = MW_NULL;
		};

		//We often construct an autoPtrData and then set each member afterwards. This constructor is meant to directly initialize everything.
		explicit autoPtrData(detail::deleterBase* del)
			: ref_cnt(1), owned(true), deleter_(del), isLocked(0)
		{ }

	private:
		long	    	ref_cnt;
		bool			owned;
		detail::deleterBase* deleter_;
		MW_ALIGN(4) volatile long		isLocked;
	};
	struct ptrCSHelper
	{
		static void Lock(autoPtrData *data)
		{
			#ifdef THREAD_SAFE_MW_AUTO_POINTER
				if ( data)
				{
					data->LockPointer();
				}
			#else
				data;//prevent warning for not used variable
			#endif
		}
		static void Unlock(autoPtrData *data)
		{
			#ifdef THREAD_SAFE_MW_AUTO_POINTER
				if ( data)
				{
					data->UnlockPointer();
				}
			#else
				data;//prevent warning for not used variable
			#endif
		}
	};
	class MW_5AXUTIL_API mwAutoPointerBase
	{
	protected:
		mwAutoPointerBase():
			mData(MW_NULL)
		{}

		mwAutoPointerBase(autoPtrData* pData)
		{
			ptrCSHelper::Lock(pData);
			mData = pData;
			ptrCSHelper::Unlock(pData);

		}

	protected:
		inline void ThrowNullPointerException() const;
		autoPtrData*	mData;
	};

	//! Auto pointer class
	/*!This class is currently not MT safe */
	template <typename T>
	class MW_5AXUTIL_API mwAutoPointer:
		private mwAutoPointerBase
	{
		template<class Archive, class T2>
		friend void save(Archive& archive, const mwAutoPointer<T2>& autoPointer, const unsigned int);

		template<class Archive, class T2>
		friend void load(Archive& archive, misc::mwAutoPointer<T2>& autoPointer, const unsigned int);

		template<class Deleter, class T2>
		friend Deleter* detail::GetDeleterImpl(const misc::mwAutoPointer<T2>& p);

	public:
#if defined(_MSC_VER) && _MSC_VER < 1916 //Only since a version of VS2017 [[deprecated]] is supported for typedefs.
		typedef __declspec(deprecated("Deprecated since 2021.12. Use element_type instead.")) T value_type;
#else
		[[deprecated("Deprecated since 2021.12. Use element_type instead.")]] typedef T value_type;
#endif

		typedef T element_type; //Note: No array-support in mwAutoPointer and therefore no need to use std::remove_extent_t<T> as shared_ptr does it.

		inline mwAutoPointer();
		inline ~mwAutoPointer();
		template <class other>
		inline mwAutoPointer(const mwAutoPointer<other>& tc);
		inline mwAutoPointer(T* ptr);
		inline mwAutoPointer(const mwAutoPointer& tc);
		template<class Deleter> //TODO: SFINAE Deleter to be a valid deleter
		mwAutoPointer(T* ptr, Deleter deleter);
		template<class Y>
		mwAutoPointer(const mwAutoPointer<Y>& parent, T* ptr);
#ifndef MW_USE_VS2008_COMPATIBILITY
		inline mwAutoPointer(mwAutoPointer&& tm) noexcept;
		template <class other>
		inline mwAutoPointer(mwAutoPointer<other>&& tm) noexcept;
		template<class Y>
		mwAutoPointer(const std::shared_ptr<Y>& sp);
		template<class Y>
		mwAutoPointer(std::shared_ptr<Y>&& sp);
		template<class Y, class Deleter>
		mwAutoPointer(std::unique_ptr<Y, Deleter>&& up);
		template<class Y>
		mwAutoPointer& operator=(const std::shared_ptr<Y>& sp);
		template<class Y>
		mwAutoPointer& operator=(std::shared_ptr<Y>&& sp);
		template<class Y, class Deleter>
		mwAutoPointer& operator=(std::unique_ptr<Y, Deleter>&& up);
		inline mwAutoPointer& operator=(mwAutoPointer&& tm) noexcept;
		operator std::shared_ptr<T>() const;
		explicit operator bool() const { return m_realPtr != nullptr; }
#endif
		inline mwAutoPointer<T> DeepCopy() const;
		inline mwAutoPointer& operator=(const mwAutoPointer& tc);
		inline bool operator==(const mwAutoPointer& tc) const;
		inline bool operator!=(const mwAutoPointer& tc) const;
		inline T& operator*() const;
		inline T* operator->() const;
		inline T* Release();
		inline void Owner(T* ptr);
		inline void Owner();
		inline T* GetPointer();
		inline const T* GetPointer() const;
		inline const T* GetPointerUnsafe() const
		{
			return m_realPtr;
		};
		inline T* GetPointerUnsafe()
		{
			return m_realPtr;
		};

		MW_DEPRECATED("Deprecated since 2021.12. Use get() or operator->() instead.")
		T* GetConstPointer() const
		{
			if (!m_realPtr)
			{
				ThrowNullPointerException();
			}
			return m_realPtr;
		}

		template <class other>
		inline mwAutoPointer<T>& UnsafeAssign(const mwAutoPointer<other>& tc);
		template <class other>
		inline mwAutoPointer<T>& Assign(const mwAutoPointer<other>& tc);
		template <typename other> friend class mwAutoPointer;
		inline static bool ShallowComparer(mwAutoPointer<T> firstObject, mwAutoPointer<T> secondObject);

		bool IsNull() const
		{
			return m_realPtr == MW_NULL;
		}

		bool IsNotNull() const
		{
			return !IsNull();
		}

		MW_DEPRECATED("Deprecated since 2021.08. Use use_count instead.")
		unsigned long GetRefCount() const
		{
			return static_cast<unsigned long>(use_count());
		}

		T* get() const
		{
			return m_realPtr;
		}

		void reset() MW_NOEXCEPT
		{
			mwAutoPointer().swap(*this);
		}

		long use_count() const
		{
			long ref_count = 0;
			ptrCSHelper::Lock(mData);
			if (mData)
			{
				ref_count = mData->GetReferenceCount();
			}
			ptrCSHelper::Unlock(mData);
			return ref_count;
		}

		void swap(mwAutoPointer& rhs) MW_NOEXCEPT
		{
			std::swap(m_realPtr, rhs.m_realPtr);
			std::swap(mData, rhs.mData);
		}

		friend bool operator<(const mwAutoPointer& lhs, const mwAutoPointer& rhs)
		{
			return std::less<T*>()(lhs.get(), rhs.get());
		}

		friend bool operator>(const mwAutoPointer& lhs, const mwAutoPointer& rhs)
		{
			return rhs < lhs;
		}

	private:
		T*				m_realPtr;
		inline void UnReference();
	};
	//----------------------------------------------------------------------------------
	//! Needed for associative containers like map
	class MW_DEPRECATED("Deprecated since 2021.08. Use operator< instead.") mwIsAddressLess
	{
	public:
		template <typename T>
		inline bool operator()(const mwAutoPointer<T>& lhs, const mwAutoPointer<T>& rhs) const
		{
			return &(*lhs) < &(*rhs);
		}
	};

	// This method is needed for using mwAutoPointer with boost functions like mem_fn or bind.
	// More info here: http://www.boost.org/doc/libs/1_53_0/libs/bind/mem_fn.html
	template<class T>
	inline T* get_pointer(misc::mwAutoPointer<T>& p);
	//----------------------------------------------------------------------------------
	//Needed for serialization
	enum mwAutoPointerVersion
	{
		AUTO_PTR_VERSION_SAVE_ONLY_POINTER = 0,
		AUTO_PTR_VERSION_SAVE_REF_COUNTER = 1
	};

	//-------------------------------------------------------
	inline void mwAutoPointerBase::ThrowNullPointerException() const
	{
		throw misc::mwException(0, _T("Accessing MW_NULL pointer"));
	}
	//-------------------------------------------------------
	template <typename T>
	inline void misc::mwAutoPointer<T>::UnReference()
	{
		if( mData )
		{

			if( mData->GetReferenceCount() )
			{
				mData->DecReferenceCount();
			}

			if( mData->GetReferenceCount() == 0 )
			{
				if( mData->GetOwnedPtr() )
				{
					mData->deleter()->callDelete();
					m_realPtr = MW_NULL;
				}

				delete mData;
				mData = MW_NULL;
			};
		}
	}
	//-------------------------------------------------------
	template <typename T>
	inline bool misc::mwAutoPointer<T>::ShallowComparer(mwAutoPointer<T> firstObject, mwAutoPointer<T> secondObject)
	{
		if(firstObject.IsNull() ^ secondObject.IsNull())
			return false;
		if(firstObject.IsNull())
			return true;
		return (*firstObject == *secondObject);
	}
	//-------------------------------------------------------
	//! Assign function
	/*!
		\param tc of type const mwAutoPointer<other>&
		\return &Assign of type mwAutoPointer<other> to type mwAutoPointer<T>
	*/

	template <class T>
	template <class other> 
	inline mwAutoPointer<T>& misc::mwAutoPointer<T>::Assign(const mwAutoPointer<other>& tc)
	{
		ptrCSHelper::Lock(mData);
		UnReference();
		ptrCSHelper::Unlock(mData);

		mData = tc.mData;
		if(mData)
		{
			ptrCSHelper::Lock(mData);
			mData->IncReferenceCount();
			ptrCSHelper::Unlock(mData);
		}

		// get pointer to base class
		m_realPtr = tc.m_realPtr;
		return *this;
	}
	
	//! UnsafeAssign function
	/*!
		\param tc of type const mwAutoPointer<other>&
		\return &UnsafeAssign of type mwAutoPointer<other> to type mwAutoPointer<T>
		*/
	
	template <class T>
	template <class other>
	inline mwAutoPointer<T>& misc::mwAutoPointer<T>::UnsafeAssign(const mwAutoPointer<other>& tc)
	{
		// make sure UnsafeAssign is only used to cast a base class into a derived class
		other* base = MW_NULL;
		T* derived = MW_NULL;
		base = derived;
		// silence compiler warning about unused variable
		(void)base;

		ptrCSHelper::Lock(mData);
		UnReference();
		ptrCSHelper::Unlock(mData);
		
		mData = tc.mData;

		if( mData )
		{
			ptrCSHelper::Lock(mData);
			mData->IncReferenceCount();
			ptrCSHelper::Unlock(mData);
		}
		// get pointer to base class
		m_realPtr = (T*) ((other*)tc.m_realPtr);
		return *this;
	}
	//-------------------------------------------------------
	template <typename T>
	inline const T* misc::mwAutoPointer<T>::GetPointer() const
	{
		if(!m_realPtr)
		{
			ThrowNullPointerException();
		}
		return m_realPtr;
	}
	// Convert to a "raw" pointer
	template <typename T>
	inline T* misc::mwAutoPointer<T>::GetPointer()
	{
		if(!m_realPtr)
		{
			ThrowNullPointerException();
		}
		return m_realPtr;
	}
	//!Destructor
	template <typename T>
	inline misc::mwAutoPointer<T>::~mwAutoPointer()
	{
		if (mData)
		{
			ptrCSHelper::Lock(mData);
			UnReference();
			ptrCSHelper::Unlock(mData);
		}
	}
	//!Take ownership of the pointer
	template <typename T>
	inline void misc::mwAutoPointer<T>::Owner()
	{
		if(!mData)
		{
			ThrowNullPointerException();
		}
		ptrCSHelper::Lock(mData);
		mData->SetOwnedPtr(true);
		ptrCSHelper::Unlock(mData);
	}
	//!Take ownership of the pointer
	template <typename T>
	inline void misc::mwAutoPointer<T>::Owner(T* ptr)
	{
		if(!ptr)
		{
			ThrowNullPointerException();
		}
		ptrCSHelper::Lock(mData);
		UnReference();
		ptrCSHelper::Unlock(mData);
		
		mData			= new autoPtrData(new detail::pointerDeleter<T>(ptr));
		m_realPtr		= ptr;
	}
	//!Release the ownership of the pointer
	template <typename T>
	inline T* misc::mwAutoPointer<T>::Release()
	{
		if(!mData)
		{
			ThrowNullPointerException();
		}
		ptrCSHelper::Lock(mData);
		mData->SetOwnedPtr(false);
		ptrCSHelper::Unlock(mData);
		
		return m_realPtr;
	}
	//!Access to the real pointer
	template <typename T>
	inline T* misc::mwAutoPointer<T>::operator->() const
	{
		if(!m_realPtr)
		{
			ThrowNullPointerException();
		}
		return m_realPtr;
	}
	//!Access to the real object
	template <typename T>
	inline T& misc::mwAutoPointer<T>::operator*() const
	{
		if(!m_realPtr)
		{
			ThrowNullPointerException();
		}
		return *(m_realPtr);
	}
	//!Inequality operator
	template <typename T>
	inline bool misc::mwAutoPointer<T>::operator!=(const mwAutoPointer& tc) const
	{
		return !(*this == tc);
	}
	//!Equality operator
	template <typename T>
	inline bool misc::mwAutoPointer<T>::operator==(const mwAutoPointer& tc) const
	{
		return m_realPtr == tc.m_realPtr;
	}
	//!Assignment operator
	/*!Assigns the auto pointer to the current one */
	
	template <typename T>
	inline mwAutoPointer<T>& misc::mwAutoPointer<T>::operator=(const mwAutoPointer& tc)
	{
		if (&tc != this)
		{
			ptrCSHelper::Lock(mData);
			UnReference();							//unreference this				
			ptrCSHelper::Unlock(mData);
			
			ptrCSHelper::Lock(tc.mData);
			mData = tc.mData;						//copy 				
			if(mData)
			{
				mData->IncReferenceCount();
			}
			m_realPtr = tc.m_realPtr;
			ptrCSHelper::Unlock(tc.mData);				
		}						
		return *this;
	}
	
	//!Deep Copy method
	/*! Performs the copy of the data enclosed in this autopointer
	*/
	
	template <typename T>
	inline mwAutoPointer<T> misc::mwAutoPointer<T>::DeepCopy() const
	{
		ptrCSHelper::Lock(mData);
		T* newData = MW_NULL;
		if (m_realPtr)
		{
			newData = new T(*m_realPtr);
		}
		ptrCSHelper::Unlock(mData);
		return mwAutoPointer (newData);
	}
	
	//!Copy constructor
	template <typename T>
	inline misc::mwAutoPointer<T>::mwAutoPointer(const mwAutoPointer& tc): 
		mwAutoPointerBase(tc.mData)
	{
		ptrCSHelper::Lock(tc.mData);
		if (mData)
		{				
			mData->IncReferenceCount();
		}
		m_realPtr = tc.m_realPtr;
		ptrCSHelper::Unlock(tc.mData);
	}
	//!Construct an auto ptr with a given pointer
	/*!Constructs an auto pointer from a "normal"
		pointer, the auto pointer destroys the pointer if
		number of references is 0 at the destruction time
		\param ptr the "real" pointer
	*/
	template <typename T>
	inline misc::mwAutoPointer<T>::mwAutoPointer(T* ptr)
	{
		if (ptr)
		{
			mData = new autoPtrData(new detail::pointerDeleter<T>(ptr));
			m_realPtr = ptr;
		}
		else
		{
			mData = MW_NULL;
			m_realPtr = MW_NULL;
		}
	}

	template<class T>
	template<class Deleter>
	inline mwAutoPointer<T>::mwAutoPointer(T* ptr, Deleter deleter)
	{
		if (ptr)
		{
			mData = new autoPtrData(new detail::customDeleter<T, Deleter>(ptr, deleter));
			m_realPtr = ptr;
		}
		else
		{
			mData = MW_NULL;
			m_realPtr = MW_NULL;
		}
	}

	template<class T>
	template<class Y>
	inline mwAutoPointer<T>::mwAutoPointer(const mwAutoPointer<Y>& parent, T* ptr)
		: mwAutoPointerBase(parent.mData)
	{
		ptrCSHelper::Lock(parent.mData);
		if (mData)
		{
			mData->IncReferenceCount();
		}
		m_realPtr = ptr;
		ptrCSHelper::Unlock(parent.mData);
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	//!Move constructor
	template <typename T>
	inline misc::mwAutoPointer<T>::mwAutoPointer(mwAutoPointer&& tm) noexcept
	{
		mData = tm.mData;
		m_realPtr = tm.m_realPtr;

		tm.mData = MW_NULL;
		tm.m_realPtr = MW_NULL;
	}
	//!Move constructor
	template <typename T>
	template <typename other>
	inline misc::mwAutoPointer<T>::mwAutoPointer(mwAutoPointer<other>&& tm) noexcept
	{
		mData = tm.mData;
		m_realPtr = tm.m_realPtr;

		tm.mData = MW_NULL;
		tm.m_realPtr = MW_NULL;
	}
	//move assignment
	template <typename T>
	inline mwAutoPointer<T>& misc::mwAutoPointer<T>::operator=(mwAutoPointer&& tm) noexcept
	{
		if (&tm != this)
		{
			ptrCSHelper::Lock(mData);
			UnReference();
			ptrCSHelper::Unlock(mData);
			mData = tm.mData;
			m_realPtr = tm.m_realPtr;

			tm.mData = MW_NULL;
			tm.m_realPtr = MW_NULL;
		}
		return *this;
	}

	template<class T>
	template<class Y>
	inline mwAutoPointer<T>::mwAutoPointer(const std::shared_ptr<Y>& sp) : m_realPtr(sp.get())
	{
		const bool managesControlBlock = sp.use_count() > 0;
		if (managesControlBlock)
		{
			using Del = detail::SharedPtrHoldingDeleter<T>;
			mData = new autoPtrData(new detail::customDeleter<T, Del>(m_realPtr, Del{ sp }));
		}
		else
		{
			mData = nullptr;
		}
	}

	template<class T>
	template<class Y>
	inline mwAutoPointer<T>::mwAutoPointer(std::shared_ptr<Y>&& sp) : m_realPtr(sp.get())
	{
		const bool managesControlBlock = sp.use_count() > 0;
		if (managesControlBlock)
		{
			using Del = detail::SharedPtrHoldingDeleter<T>;
			mData = new autoPtrData(new detail::customDeleter<T, Del>(m_realPtr, Del{ std::move(sp) }));
		}
		else
		{
			mData = nullptr;
		}
	}

	template<class T>
	template<class Y, class Deleter>
	inline mwAutoPointer<T>::mwAutoPointer(std::unique_ptr<Y, Deleter>&& up) : mwAutoPointer(mwAutoPointer<Y>(up.release(), up.get_deleter()))
	{
		//For now we do not support constructing from a deleter that is a reference. The reason is that we want to come close to the
		//behavior of std::shared_ptr. And in VS2013 it just copied the deleter and in VS2019 it handles references by wrapping them in a reference_wrapper.
		//To avoid possible bugs when switching to std::shared_ptr we just disable support for references for now.
		static_assert(!std::is_reference<Deleter>::value, "[mwAutoPointer]: Constructing from unique_ptr with Deleter being a reference is not supported");
	}

	template<class T>
	template<class Y>
	inline mwAutoPointer<T>& mwAutoPointer<T>::operator=(const std::shared_ptr<Y>& sp)
	{
		return *this = mwAutoPointer<T>(sp);
	}

	template<class T>
	template<class Y>
	inline mwAutoPointer<T>& mwAutoPointer<T>::operator=(std::shared_ptr<Y>&& sp)
	{
		return *this = mwAutoPointer<T>(std::move(sp));
	}

	template<class T>
	template<class Y, class Deleter>
	inline mwAutoPointer<T>& mwAutoPointer<T>::operator=(std::unique_ptr<Y, Deleter>&& up)
	{
		return *this = mwAutoPointer<T>(std::move(up));
	}

	template<class T>
	inline mwAutoPointer<T>::operator std::shared_ptr<T>() const
	{
		std::shared_ptr<T> nrv;
		if (mData)
		{
			auto self = *this;
			auto deleter = [self](T*) mutable { self = mwAutoPointer<T>(); };
			nrv = {m_realPtr, std::move(deleter)};
		}
		else
		{
			std::shared_ptr<void> emptyControlBlock;
			nrv = {emptyControlBlock, m_realPtr};
		}
		return nrv;
	}
#endif

	//!Construct an auto pointer from an auto pointer
	// of the derived class
	template <class T>
	template <class other>
	inline misc::mwAutoPointer<T>::mwAutoPointer(const mwAutoPointer<other>& tc): 
		m_realPtr(MW_NULL)
	{
		this->Assign(tc);
	}
	//----------------------------------------------------------------------------------
	template <typename T>
	inline misc::mwAutoPointer<T>::mwAutoPointer(): 
		m_realPtr(MW_NULL)
	{}

	// This method is needed for using mwAutoPointer with boost functions like mem_fn or bind.
	// More info here: http://www.boost.org/doc/libs/1_53_0/libs/bind/mem_fn.html
	template<class T> 
	inline T* get_pointer(misc::mwAutoPointer<T>& p)
	{
		return p.GetPointer();
	}

	template<class T>
	void swap(mwAutoPointer<T>& a, mwAutoPointer<T>& b) MW_NOEXCEPT
	{
		a.swap(b);
	}

	namespace detail
	{
		template<class Deleter, class T>
		inline Deleter* GetDeleterImpl(const misc::mwAutoPointer<T>& p)
		{
			return static_cast<Deleter*>(p.mData ? const_cast<void*>(p.mData->deleter()->getDeleter(typeid(Deleter))) : MW_NULL);
		}
	}

	template<class Deleter, class T>
	inline Deleter* get_deleter(const misc::mwAutoPointer<T>& p)
	{
		return detail::GetDeleterImpl<Deleter>(p);
	}
}  // namespace misc
#endif	//	MW_MWAUTOPOINTER_HPP_
