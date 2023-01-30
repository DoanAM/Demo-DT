// (C) 2008-2020 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPOINTERALLOCATOR_HPP_
#define MW_MWPOINTERALLOCATOR_HPP_
#include <memory>
#include <cstddef>
#include "mwException.hpp"
#include "mwMemoryHeap.hpp"
#include "mwDeprecated.hpp"

namespace misc
{
    template <class T>
    class MW_DEPRECATED("Deprecated since 2020.12. Do not use it.") mwPointerAllocator
    {
    public:
        typedef T value_type;

        typedef value_type* pointer;
        typedef value_type& reference;
        typedef const value_type* const_pointer;
        typedef const value_type& const_reference;

        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;

        template<class Other>
        struct rebind
        {
            typedef mwPointerAllocator<Other> other;
        };

        mwPointerAllocator()
            : m_MemoryHeap(MW_NULL)
        {
            throw mwException(0, _T("mwPointerAllocator must be constructed with a mwMemoryHeap instance"));
        }

        mwPointerAllocator(const mwMemoryHeap& memoryHeap)
            : m_MemoryHeap(&memoryHeap)
        {

        }

        mwPointerAllocator(const mwPointerAllocator<T>& other)
            : m_MemoryHeap(other.GetMemoryHeapAllocator())
        {

        }


        // VC6 doesn't support template member methods
        template<class Other>
        mwPointerAllocator(const mwPointerAllocator<Other>& other)
            : m_MemoryHeap(other.GetMemoryHeapAllocator())
        {

        }

        template<class Other>
        mwPointerAllocator<T>& operator=(const mwPointerAllocator<Other>& /*other*/)
        {
            return *this;
        }

        pointer address(reference value) const
        {
            return &value;
        }

        const_pointer address(const_reference value) const
        {
            return &value;
        }

        void deallocate(pointer ptr, size_type /*size*/)
        {
            m_MemoryHeap->Free(ptr);
        }

        pointer allocate(size_type count)
        {
            if (count <= 0)
                count = 0;
            else if ((static_cast<size_t>(-1) / count) < sizeof(T))
                throw std::bad_alloc();
            return m_MemoryHeap->TypedAlloc<T>(count);
        }

        pointer allocate(size_type count, const void* /*hint*/)
        {
            return allocate(count);
        }

        void construct(pointer ptr, const T& value)
        {
            void *temp = ptr;
            ::new (temp) T(value);
        }

        void destroy(pointer ptr)
        {
            ptr->~T();

            // Required: VS2005 will throw an "unused 'ptr' variable" warning otherwise
            UNREFERENCED_PARAMETER(ptr);
        }

        size_t max_size() const
        {
            // estimate maximum array size
            size_t count = static_cast<size_t>(-1) / sizeof(T);
            return 0 < count ? count : 1;
        }

        const mwMemoryHeap* GetMemoryHeapAllocator() const
        {
            return m_MemoryHeap;
        }

    private:
        const mwMemoryHeap* m_MemoryHeap;
    };
}
#endif	//	MW_MWPOINTERALLOCATOR_HPP_
