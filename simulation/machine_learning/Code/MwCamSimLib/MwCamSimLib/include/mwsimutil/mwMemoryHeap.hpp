// (C) 2007-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYHEAP_HPP_
#define MW_MWMEMORYHEAP_HPP_


#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
    struct mwMemoryHeapData;

    class MW_5AXUTIL_API mwMemoryHeap
    {
    public:
		typedef mwAutoPointer<mwMemoryHeap> MemoryHeapPtr;

        mwMemoryHeap(bool serialized = true, size_t blockSize = 128 * 1024);

		~mwMemoryHeap();

        void* Alloc(size_t size) const;

        void Free(void* ptr) const;

        template <typename T>
        void FreeAndMakeZero(T& ptr) const
        {
            Free(ptr);
            ptr = MW_NULL;
        }

        template <typename T>
        T* TypedAlloc(size_t count) const
        {
            return static_cast<T*>(Alloc(count * sizeof(T)));
        }

		size_t GetAllocationCount() const;


		#if defined (_WIN32)  && !defined (UNDER_CE)
        MW_DEPRECATED("Deprecated since 2022.04. Since Windows Vista this function does not have any effect any more.")
		static void EnableLowFragmentationHeap(...)
        {
            //We keep this function as we consider it API.
            //In a previous version it took a HANDLE as parameter. But to get rid of windows.h we replaced it by the ellipsis operator.
        }
		#endif

	private:
		// TODO: use =delete when we dropped VS2008
		mwMemoryHeap(const mwMemoryHeap& /*other*/) {}
		mwMemoryHeap& operator=(const mwMemoryHeap& /*other*/) { return *this; }

		mwMemoryHeapData* m_data;

    };

} // end of namespace misc

#endif	//	MW_MWMEMORYHEAP_HPP_
