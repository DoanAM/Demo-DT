// (C) 2008-2017 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWEFFICIENTVECTOR_HPP_
#define MW_MWEFFICIENTVECTOR_HPP_
#include "mwMemoryHeap.hpp"
#include "mwMathConstants.hpp"
#include "mwDefines.hpp"
#include "mwDllImpExpDef.hpp"
#include <vector>

namespace misc
{
    template <typename T, typename S=size_t>
    class MW_5AXUTIL_API mwEfficientVector
    {
    public:
        typedef T* iterator;
        typedef T const* const_iterator;

    public:
        mwEfficientVector() {}

        MW_DEPRECATED("This constructor is deprecated since 2022.04. Use the default constructor instead.")
		mwEfficientVector(mwMemoryHeap::MemoryHeapPtr /*heap*/)
        {}

        explicit mwEfficientVector(size_t count)
            : vector(count, T())
        {}

        MW_DEPRECATED("This constructor is deprecated since 2022.04. Use the constructor taking one size_t instead.")
        explicit mwEfficientVector(size_t count, mwMemoryHeap::MemoryHeapPtr /*heap*/)
            : vector(count, T())
        {}

        MW_DEPRECATED("This constructor is deprecated since 2022.04. Use the copy-constructor instead.")
        mwEfficientVector(const mwEfficientVector<T, S>& other, mwMemoryHeap::MemoryHeapPtr /*heap*/)
            : vector(other.vector)
        {}

        bool empty() const { return vector.empty(); }
        size_t size() const { return vector.size(); }

        void clear()
        {
            vector.clear();
        }

        void resize(size_t count, const T* data=MW_NULL) { Allocate(count, data); }

        const_iterator begin() const {
#ifndef MW_USE_VS2008_COMPATIBILITY
			return vector.data();
#else
			return &vector[0];
#endif
        }
        const_iterator end() const { return begin() + size(); }

        iterator begin() {
#ifndef MW_USE_VS2008_COMPATIBILITY
			return vector.data();
#else
			return &vector[0];
#endif
		}
        iterator end() { return begin() + size(); }

        const T& operator[](size_t index) const
        {
            return vector[index];
        }

        T& operator[](size_t index)
        {
            return vector[index];
        }

        bool operator==(const mwEfficientVector<T, S>& other) const
        {
            if (size() != other.size())
                return false;
            
            for (size_t i = 0; i != size(); ++i)
				if( mathdef::is_neq(vector[i],other.vector[i]) )
                    return false;
            return true;
        }

        bool operator!=(const mwEfficientVector<T, S>& other) const
        {
            return !(*this == other);
        }

    private:
        void Allocate(size_t count, const T* data)
        {
            vector.resize(count, T());

            if (data != MW_NULL)
                for (size_t i = 0; i < size(); ++i)
                    vector[i] = data[i];
        }

        std::vector<T> vector;
    };
}
#endif	//	MW_MWEFFICIENTVECTOR_HPP_
