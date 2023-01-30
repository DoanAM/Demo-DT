// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYVIRTUAL_HPP_
#define MW_MWMEMORYVIRTUAL_HPP_

#include "mwDeprecated.hpp"
#include "mwDllImpExpDef.hpp"
#include <cstddef>

namespace misc
{
    class MW_5AXUTIL_API MW_DEPRECATED("mwMemoryVirtual is deprecated since 2022.04. Use std::malloc and std::free instead.") mwMemoryVirtual
    {
    public:
        static void* Alloc(size_t size);

        static void Free(void* ptr);

        static std::size_t QuerySize(const void* ptr);

        template <typename T>
        static T* TypedAlloc(std::size_t count)
        {
            return static_cast<T*>(Alloc(count * sizeof(T)));
        }
    };
}
#endif	//	MW_MWMEMORYVIRTUAL_HPP_
