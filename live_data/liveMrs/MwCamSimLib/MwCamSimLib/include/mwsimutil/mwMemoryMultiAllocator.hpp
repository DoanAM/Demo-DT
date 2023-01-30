// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYMULTIALLOCATOR_HPP_
#define MW_MWMEMORYMULTIALLOCATOR_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwMemoryHeap.hpp"
#include "mwMemoryPool.hpp"

namespace misc
{
    struct ThreadData;
	struct mwMemoryMultiAllocatorData;

    class MW_5AXUTIL_API mwMemoryMultiAllocator
    {
    public:

        mwMemoryMultiAllocator();

        explicit mwMemoryMultiAllocator(size_t arenaSize);

        mwMemoryMultiAllocator(const mwMemoryMultiAllocator& other);

        ~mwMemoryMultiAllocator();

        size_t GetMemoryUsage();

        mwMemoryHeap::MemoryHeapPtr GetHeap();

		mwMemoryPool::MemoryPoolPtr GetPool(size_t nodeSize);

        void ResetHeap();

        void ClearAll();
		void Clear();

		// FIXME: behavior is different to copy ctor!
		// this should be private anyway (aka =delete)?
        mwMemoryMultiAllocator& operator=(const mwMemoryMultiAllocator& /*other*/)
        {
			return *this;
        }

    private:
		void AllocTLSIndex();
        ThreadData& GetThreadData();

		mwMemoryMultiAllocatorData* m_data;

    };

} // end of namespace misc

#endif	//	MW_MWMEMORYMULTIALLOCATOR_HPP_
