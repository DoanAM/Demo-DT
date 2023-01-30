// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYPOOL_HPP_
#define MW_MWMEMORYPOOL_HPP_

#include "mwDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"

#include <vector>

namespace misc
{
class MW_5AXUTIL_API mwMemoryPool
{
public:
	typedef mwAutoPointer<mwMemoryPool> MemoryPoolPtr;
	typedef std::vector<MemoryPoolPtr> Vector;

public:
	mwMemoryPool(size_t nodeSize, size_t arenaSize = 256 * 1024);
	~mwMemoryPool();

	size_t GetNodeSize() const;
	size_t GetMemoryUsage() const;
	size_t GetAllocatedNodeCount() const;

	void* Alloc(size_t size);
	template <typename T>
	T* TypedAlloc(size_t count)
	{
		return static_cast<T*>(Alloc(count * sizeof(T)));
	}

	void Free(void* node);
	void Clear();

private:
	mwMemoryPool(const mwMemoryPool&);
	mwMemoryPool& operator=(const mwMemoryPool&);

private:
	struct mwMemoryPoolImpl;
	//As we have to support VS2008 we can't use std::unique_ptr.
	//But it is fine to use a raw-pointer and do the memory management manually
	//as we only have one constructor and one destructor. Copy/Move-semantics are disabled.
	mwMemoryPoolImpl* m_pimpl;
};
}  // namespace misc
#endif  //	MW_MWMEMORYPOOL_HPP_
