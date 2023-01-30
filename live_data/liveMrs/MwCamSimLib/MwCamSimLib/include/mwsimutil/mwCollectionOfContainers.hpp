// (C) 2003-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWCOLLECTIONOFCONTAINERS_HPP_
#define MW_MWCOLLECTIONOFCONTAINERS_HPP_
#include "mwmiscException.hpp"
#include "mwDllImpExpDef.hpp"

#include <cstddef>

namespace misc
{
//! this class allows access of objects that are stored in a collection of containers eg:list of
//! lists
/*! this class assumes that in collection you are storing mwAutoPointers to the containers,
	and not the containers itself. It's well known the all stl containers are making a lot of
	copies on in/out operations, so it looks strange (u may read as time consuming) to have a
	collection of real containers instead of pointers to the containers. But if this is what you
	need, you may generalize this template, i just did not need it yet.
*/
template <typename CollectionType>
class MW_5AXUTIL_API mwCollectionOfContainers
{
public:

	typedef typename CollectionType::value_type Pointer2ContainerType;
	typedef typename Pointer2ContainerType::element_type ContainerType;
	typedef typename ContainerType::value_type value_type;

private:

	typedef mwCollectionOfContainers<CollectionType> ThisType;

	typedef typename CollectionType::iterator CollectionIterator;
	typedef typename CollectionType::const_iterator CollectionConstIterator;

	typedef typename ContainerType::iterator ContainerIterator;
	typedef typename ContainerType::const_iterator ContainerConstIterator;

public:

	virtual ~mwCollectionOfContainers(){};

	//! allows jumping from value to value (value= objects stored inside the containers) in both
	//! directions fwd and bw
	/*! it is the const version so it is not allowing you to modify the leaf
	 */
	class const_iterator
	{
	public:
		typedef typename ContainerType::value_type value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef std::bidirectional_iterator_tag iterator_category;

	protected:
		const ThisType* m_pCollection;
		CollectionConstIterator m_container;
		ContainerConstIterator m_current;

		const_iterator(
			const ThisType * collection,
			const CollectionConstIterator& container,
			const ContainerConstIterator& it)
			: m_pCollection(collection), m_container(container), m_current(it)
		{
		}

	public:

		const_iterator() : m_pCollection(0)
		{
		}

		//! destructor
		~const_iterator()
		{
		}

		//! fwd operator (preincrement)
		const const_iterator& operator++()
		{
			++m_current;
			while (m_current == m_pCollection->GetEndOfContainer(m_container))
			{
				++m_container;
				if (m_container == m_pCollection->GetEndOfCollection())
				{
					break;
				}
				m_current = m_pCollection->GetBeginOfContainer(m_container);
			}
			return (*this);
		}

		//! fwd operator (postincrement)
		const_iterator operator++(int)
		{
			const_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		//! bw operator (predecrement)
		const const_iterator& operator--()
		{
			if (m_container == m_pCollection->GetEndOfCollection())
			{
				--m_container;
				m_current = m_pCollection->GetEndOfContainer(m_container);
			}

			while (m_current == m_pCollection->GetBeginOfContainer(m_container))
			{
				--m_container;
				m_current = m_pCollection->GetEndOfContainer(m_container);
			}

			--m_current;
			return (*this);
		}

		//! bw operator (postdecrement)
		const_iterator operator--(int)
		{
			const_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		//! are equal operator
		bool operator==(const const_iterator& toCompare) const
		{
			return m_container == toCompare.m_container &&
				   (m_container == m_pCollection->GetEndOfCollection() ||
					m_current == toCompare.m_current);
		}

		//! are different operator
		bool operator!=(const const_iterator& toCompare) const
		{
			return !(*this == toCompare);
		}

		//! ref access to the value
		const value_type& operator*() const
		{
			return *m_current;
		}

		//! pointer style access to the value
		const value_type* operator->() const
		{
			return &*m_current;
		}

	private:
		friend class mwCollectionOfContainers;

		const CollectionConstIterator& GetContainerIterator() const
		{
			return m_container;
		}

		const ContainerConstIterator& GetValueIterator() const
		{
			return m_current;
		}
	};  // const_iterator

	class iterator : public const_iterator
	{
	public:
		iterator()
		{
		}

		explicit iterator(const const_iterator& it) : const_iterator(it)
		{
		}

		iterator& operator=(const iterator& rToCopy)
		{
			const_iterator::operator=(rToCopy);
			return *this;
		}

		//! fwd operator (preincrement)
		const iterator& operator++()
		{
			const_iterator::operator++();
			return *this;
		}

		//! fwd operator (postincrement)
		iterator operator++(int)
		{
			iterator tmp = *this;
			const_iterator::operator++();
			return tmp;
		}

		//! bw operator (predecrement)
		const iterator& operator--()
		{
			const_iterator::operator--();
			return *this;
		}

		//! bw operator (postdecrement)
		iterator operator--(int)
		{
			iterator tmp = *this;
			const_iterator::operator--();
			return tmp;
		}

		value_type& operator*() const
		{
			return const_cast<value_type&>(const_iterator::operator*());
		}

		//! pointer style access to the value
		value_type* operator->() const
		{
			return const_cast<value_type*>(const_iterator::operator->());
		}
	};  // iterator

	//! return true if the toolpath is empty
	const bool empty() const
	{
		if (m_Collection.empty())
			return true;

		CollectionConstIterator endIt = m_Collection.end();
		for (CollectionConstIterator it = m_Collection.begin(); it != endIt; ++it)
		{
			if (!(*it)->empty())
				return false;
		}

		return true;
	}

	//! returns a bidirectional iterator to the first value
	/*! returns a bidirectional iterator that points at the first value
		available in containers (or just beyond the end of the collection if there is no value).
	*/
	iterator begin()
	{
		return iterator(const_cast<const ThisType*>(this)->begin());
	}

	//! const version of begin()
	const_iterator begin() const
	{
		// first valid element
		if (!m_Collection.empty())
		{  // if we have at least one container then the iterator should point to the begin of this
		   // container
			CollectionConstIterator containerIt = m_Collection.begin();
			while ((*containerIt)->empty())
			{
				++containerIt;
				if (containerIt == m_Collection.end())
					return end();
			}
			return const_iterator(this, containerIt, (*containerIt)->begin());
		}
		else
		{  // if no container at all then the begin is actually the list end
			return end();
		}
	}

	//! returns a bidirectional iterator that points just beyond the end of the collection.
	iterator end()
	{
		return iterator(const_cast<const ThisType*>(this)->end());
	}

	//! const version of end()
	const_iterator end() const
	{
		return const_iterator(this, m_Collection.end(), ContainerConstIterator());
	}

	//! returns how many values are in all containers of the collection
	size_t size() const
	{
		size_t count = 0;
		CollectionConstIterator endIt = m_Collection.end();
		for (CollectionConstIterator it = m_Collection.begin(); it != endIt; ++it)
		{
			count += (*it)->size();
		}
		return count;
	}

	//! inserts a value in the last container of the collections
	/*! it throws exception if there is no container at all,
		this is why insert function is virtual. In case you need to assure at least one container
		you may overwrite that function.
	*/
	void push_back(const value_type& value)
	{
		insert(end(), value);
	}

	//! inserts a value in the first container of the collections
	/*! it throws exception if there is no container at all,
		this is why insert function is virtual. In case you need to assure at least one container
		you may overwrite that function.
	*/
	virtual void push_front(const value_type& value)
	{
		insert(begin(), value);
	}

	//! inserts a value just before specified position
	/*! it throws exception if there is no container at all in the collection.
		Convention: if you specifies an insertionPoint to a value which is the first one in it's
		container, the new value is inserted in the same container.
	*/
	virtual iterator insert(const const_iterator& insertionPoint, const value_type& value)
	{
		if (m_Collection.empty())
			throw mwmiscException(mwmiscException::NO_CONTAINER_AVAILABLE);

		CollectionConstIterator containerIt = insertionPoint.GetContainerIterator();
		ContainerConstIterator beforeValueIt;

		if (containerIt == m_Collection.end())
		{
			--containerIt;
			beforeValueIt = (*containerIt)->end();
		}
		else
		{
			beforeValueIt = insertionPoint.GetValueIterator();
		}

		ContainerType & container = const_cast<ContainerType&>(**containerIt);
		ContainerIterator insertedValue = container.insert(beforeValueIt, value);

		return iterator(const_iterator(this, containerIt, insertedValue));
	}

protected:
	friend class const_iterator;

	CollectionType m_Collection;

	const CollectionConstIterator& GetContainer(const const_iterator& it) const
	{
		return it.GetContainerIterator();
	}

	const ContainerConstIterator& GetValue(const const_iterator& it) const
	{
		return it.GetValueIterator();
	}

	//! returns the end of a specified container
	/*! this function is used by const_iterator to detect when it's getting to a container end
	 * during ++
	 */
	ContainerConstIterator GetEndOfContainer(const CollectionConstIterator& conatinerIt) const
	{
		return (*conatinerIt)->end();
	}

	//! returns the beginning of a specified container
	/*! this function is used by const_iterator on ++ and --
	 */
	ContainerConstIterator GetBeginOfContainer(const CollectionConstIterator& conatinerIt) const
	{
		return (*conatinerIt)->begin();
	}

	//! returns the end of collection
	/*! this function is used by const_iterator
	 */
	CollectionConstIterator GetEndOfCollection() const
	{
		return m_Collection.end();
	}
};
}  // namespace misc
#endif  //	MW_MWCOLLECTIONOFCONTAINERS_HPP_
