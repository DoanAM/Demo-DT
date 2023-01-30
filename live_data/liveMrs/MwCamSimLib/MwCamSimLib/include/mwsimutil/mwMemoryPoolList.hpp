// (C) 2008-2019 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYPOOLLIST_HPP_
#define MW_MWMEMORYPOOLLIST_HPP_
#include "mwException.hpp"
#include "mwMemoryPool.hpp"
#include "mwMemoryMultiAllocator.hpp"

namespace misc
{
	template <typename T>
	class MW_5AXUTIL_API mwMemoryPoolList
	{
	public:
		typedef T value_type;

		typedef T* pointer;
		typedef const T* const_pointer;

		typedef T& reference;
		typedef const T& const_reference;

		struct Node
		{
			Node* next;
			Node* prev;
			T     data;
		};

		class const_iterator;

		class iterator
		{
		public:
			typedef std::bidirectional_iterator_tag iterator_category;

			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;

			iterator() : m_Node(MW_NULL), m_Tail(MW_NULL) { }
			iterator(const iterator& it) : m_Node(it.m_Node), m_Tail(it.m_Tail) { }
			explicit iterator(Node* node, Node* tail) : m_Node(node), m_Tail(tail) { }

			iterator& operator++()
			{
				if (m_Node == MW_NULL)
				{
					throw misc::mwException(0, _T("mwMemoryPoolList::const_iterator will run out of scope (operator ++)"));
				}
				m_Node = m_Node->next;
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
				m_Node = (m_Node != MW_NULL) ? m_Node->prev : m_Tail;
				return *this;
			}

			iterator operator--(int)
			{
				iterator temp = *this;
				--*this;
				return temp;
			}

			pointer operator->() const { return &m_Node->data; }
			reference operator*() const { return m_Node->data; }

			bool operator==(const iterator& right) const { return m_Node == right.m_Node; }
			bool operator!=(const iterator& right) const { return !(*this == right); }

			Node* GetNode() { return m_Node; }
			const Node* GetNode() const { return m_Node; }

		private:
			Node* GetTail() { return m_Tail; }
			const Node* GetTail() const { return m_Tail; }

		private:
			Node* m_Node;
			Node* m_Tail;

			friend class const_iterator;
		};

		class const_iterator
		{
		public:
			typedef std::bidirectional_iterator_tag iterator_category;

			typedef T value_type;
			typedef const T* pointer;
			typedef const T& reference;

			const_iterator() : m_Node(MW_NULL), m_Tail(MW_NULL) { }
			const_iterator(const iterator& it) : m_Node(it.GetNode()), m_Tail(it.GetTail()) { }
			const_iterator(const const_iterator& it) : m_Node(it.m_Node), m_Tail(it.m_Tail) { }
			explicit const_iterator(const Node* node, const Node* tail) : m_Node(node), m_Tail(tail) { }

			const_iterator& operator++()
			{
				if (m_Node == MW_NULL)
				{
					throw misc::mwException(0, _T("mwMemoryPoolList::const_iterator will run out of scope (operator ++)"));
				}
				m_Node = m_Node->next;
				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator temp = *this;
				++*this;
				return temp;
			}

			const_iterator& operator--()
			{
				m_Node = (m_Node != MW_NULL) ? m_Node->prev : m_Tail;
				return *this;
			}

			const_iterator operator--(int)
			{
				const_iterator temp = *this;
				--*this;
				return temp;
			}

			pointer operator->() const { return &m_Node->data; }
			reference operator*() const { return m_Node->data; }

			bool operator==(const const_iterator& right) const { return m_Node == right.m_Node; }
			bool operator!=(const const_iterator& right) const { return !(*this == right); }

			const Node* GetNode() const { return m_Node; }

		private:
			const Node* GetTail() const { return m_Tail; }

		private:
			const Node* m_Node;
			const Node* m_Tail;
		};

	public:
		// please take care not to destroy allocator before destroing the memoryPoolList
		explicit mwMemoryPoolList(mwMemoryMultiAllocator& allocator)
			: m_Pool(allocator.GetPool(sizeof(Node))),
			m_Head(MW_NULL),
			m_Tail(MW_NULL),
			m_Count(0)
		{

		}

		mwMemoryPoolList(const mwMemoryPoolList<T>& other, mwMemoryMultiAllocator& allocator)
			: m_Pool(allocator.GetPool(sizeof(Node))),
			m_Head(MW_NULL),
			m_Tail(MW_NULL),
			m_Count(0)
		{
			for (const_iterator pos = other.begin(); pos != other.end(); ++pos)
				push_back(*pos);
		}

		~mwMemoryPoolList() { clear(); }

		mwMemoryPoolList& operator=(const mwMemoryPoolList<T>& other)
		{
			if (&other == this)
				return *this;

			clear();

			for (const_iterator pos = other.begin(); pos != other.end(); ++pos)
				push_back(*pos);

			return *this;
		}

		bool empty() const { return m_Count == 0; }
		size_t size() const { return m_Count; }

		void push_back(const T& elem)
		{
			::new (Alloc()) T(elem);
		}

		void push_front(const T& elem)
		{
			insert(begin(), elem);
		}

		void push_back(const T& elem, mwMemoryMultiAllocator& allocator)
		{
			::new (Alloc()) T(elem, allocator);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

		void clear()
		{
			if (m_Count != 0)
			{
				Node* node = m_Head;
				while (node != MW_NULL)
				{
					Node* temp = node;
					node = node->next;
					Free(temp);
				}
				m_Head = MW_NULL;
				m_Tail = MW_NULL;
				m_Count = 0;
			}
		}

		void insert(iterator pos, const T& elem)
		{
			::new (Insert(pos)) T(elem);
		}

		iterator erase(iterator pos)
		{
			Node* node = pos.GetNode();
			const iterator next = ++pos;

			if (m_Head == node)
			{
				m_Head = node->next;
				if(m_Head)
					m_Head->prev = MW_NULL;
			}
			else
				node->prev->next = node->next;

			if (m_Tail == node)
			{
				m_Tail = node->prev;
				if(m_Tail)
					m_Tail->next = MW_NULL;
			}
			else
				node->next->prev = node->prev;

			Free(node);

			--m_Count;
			return next;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
			{
				clear();
				return end();
			}
			else
			{
				while (first != last)
					first = erase(first);
				return last;
			}
		}

		const_iterator begin() const { return const_iterator(m_Head, m_Tail); }
		const_iterator end() const { return const_iterator(MW_NULL, m_Tail); }

		iterator begin() { return iterator(m_Head, m_Tail); }
		iterator end() { return iterator(MW_NULL, m_Tail); }

		reference front() { return m_Head->data; }
		reference back() { return m_Tail->data; }

		const_reference front() const { return m_Head->data; }
		const_reference back() const { return m_Tail->data; }

		bool operator==(const mwMemoryPoolList<T>& other) const
		{
			if (m_Count != other.m_Count)
				return false;
			if (m_Count != 0)
			{
				Node* node = m_Head;
				Node* otherNode = other.m_Head;
				while (node != MW_NULL)
				{
					if (!(node->data == otherNode->data))
						return false;
					node = node->next;
					otherNode = otherNode->next;
				}
			}
			return true;
		}

		bool operator!=(const mwMemoryPoolList<T>& other) const
		{
			return !(*this == other);
		}

		static size_t GetNodeSize() { return sizeof(Node); }

	private:
		T* Alloc()
		{
			Node* node = static_cast<Node*>(m_Pool->Alloc(sizeof(Node)));
			node->next = MW_NULL;
			if (m_Count != 0)
			{
				m_Tail->next = node;
				node->prev = m_Tail;
				m_Tail = node;
			}
			else
			{
				node->prev = MW_NULL;
				m_Head = node;
				m_Tail = node;
			}
			++m_Count;
			return &node->data;
		}

		T* Insert(iterator pos)
		{
			Node* nPos = pos.GetNode();
			if(pos == end())
			{
				return Alloc();
			}
			else
				if(m_Head == nPos)//pos first
				{
					if(m_Count == 0)
						throw misc::mwException(0, _T("Invalide iterator!"));
					Node* node = static_cast<Node*>(m_Pool->Alloc(sizeof(Node)));
					node->prev = MW_NULL;
					node->next = nPos;
					nPos->prev = node;
					m_Head = node;
					++m_Count;
					return &node->data;
				}
				else
				{
					Node* node = static_cast<Node*>(m_Pool->Alloc(sizeof(Node)));
					iterator before = pos;
					--before;
					Node*  nBefore = before.GetNode();
					node->prev = nBefore;
					node->next = nPos;
					nBefore->next = node;
					nPos->prev = node;
					++m_Count;
					return &node->data;
				}
		}//*/

		void Free(Node* node)
		{
			node->data.~T();
			m_Pool->Free(node);
		}

	private:
	#pragma warning(push)
	#pragma warning(disable : 4251)
	
		mwMemoryPool::MemoryPoolPtr m_Pool;
		Node* m_Head;
		Node* m_Tail;
		size_t m_Count;
	
	#pragma warning(pop)
	};
}
#endif	//	MW_MWMEMORYPOOLLIST_HPP_
