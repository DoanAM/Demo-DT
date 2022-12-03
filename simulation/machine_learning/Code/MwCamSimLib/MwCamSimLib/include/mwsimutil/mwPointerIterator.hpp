// (C) 2008-2010 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWPOINTERITERATOR_HPP_
#define MW_MWPOINTERITERATOR_HPP_
// DEPRECATED: please don't include this header
#pragma message ("Warning: please don't include " __FILE__ ", it is deprecated and will be removed")

#include "mwDeprecated.hpp"
#include <iterator>

namespace misc
{
    template <class T>
    class MW_DEPRECATED("mwPointerIterator is deprecated since 2022.04. Use a raw pointer instead.") mwPointerIterator
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;

        typedef T value_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef mwPointerIterator<T> iterator;

        mwPointerIterator() : m_Ptr(MW_NULL) { }
        mwPointerIterator(const iterator& it) : m_Ptr(it.m_Ptr) { }
        explicit mwPointerIterator(pointer ptr) : m_Ptr(ptr) { }

        iterator& operator++()
        {
            ++m_Ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        iterator& operator--()
        {
            --m_Ptr;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }

        iterator operator+(difference_type offset) const
        {
            iterator temp = *this;
            return temp += offset;
        }

        iterator& operator+=(difference_type offset)
        {
            m_Ptr += offset;
            return *this;
        }

        iterator operator-(difference_type offset) const
        {
            iterator temp = *this;
            return temp -= offset;
        }

        iterator& operator-=(difference_type offset)
        {
            return *this += -offset;
        }

        difference_type operator-(const iterator& right) const
        {
            return m_Ptr - right.m_Ptr;
        }

        pointer operator->() const { return &**this; }
        reference operator*() const { return *m_Ptr; }

        reference operator[](difference_type offset) const { return *(*this + offset); }

        bool operator==(const iterator& right) const { return m_Ptr == right.m_Ptr; }
        bool operator!=(const iterator& right) const { return !(*this == right); }
        bool operator<(const iterator& right) const { return m_Ptr < right.m_Ptr; }
        bool operator>(const iterator& right) const { return right < *this; }
        bool operator<=(const iterator& right) const { return !(right < *this); }
        bool operator>=(const iterator& right) const { return !(*this < right); }

    private:
        pointer m_Ptr;
    };

    template <class T>
    class MW_DEPRECATED("mwConstPointerIterator is deprecated since 2022.04. Use a raw pointer indstead.") mwConstPointerIterator
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;

        typedef T value_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef mwConstPointerIterator<T> iterator;

        mwConstPointerIterator() : m_Ptr(MW_NULL) { }
        mwConstPointerIterator(const iterator& it) : m_Ptr(it.m_Ptr) { }
        mwConstPointerIterator(const mwPointerIterator<T>& it) : m_Ptr(&*it) { }
        explicit mwConstPointerIterator(pointer ptr) : m_Ptr(ptr) { }

        iterator& operator++()
        {
            ++m_Ptr;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        iterator& operator--()
        {
            --m_Ptr;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --*this;
            return temp;
        }

        iterator operator+(difference_type offset) const
        {
            iterator temp = *this;
            return temp += offset;
        }

        iterator& operator+=(difference_type offset)
        {
            m_Ptr += offset;
            return *this;
        }

        iterator operator-(difference_type offset) const
        {
            iterator temp = *this;
            return temp -= offset;
        }

        iterator& operator-=(difference_type offset)
        {
            return *this += -offset;
        }

        difference_type operator-(const iterator& right) const
        {
            return m_Ptr - right.m_Ptr;
        }

        pointer operator->() const { return &**this; }
        reference operator*() const { return *m_Ptr; }

        reference operator[](difference_type offset) const { return *(*this + offset); }

        bool operator==(const iterator& right) const { return m_Ptr == right.m_Ptr; }
        bool operator!=(const iterator& right) const { return !(*this == right); }
        bool operator<(const iterator& right) const { return m_Ptr < right.m_Ptr; }
        bool operator>(const iterator& right) const { return right < *this; }
        bool operator<=(const iterator& right) const { return !(right < *this); }
        bool operator>=(const iterator& right) const { return !(*this < right); }

    private:
        pointer m_Ptr;
    };
}
#endif	//	MW_MWPOINTERITERATOR_HPP_
