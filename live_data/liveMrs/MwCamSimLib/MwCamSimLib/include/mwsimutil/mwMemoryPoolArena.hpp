// (C) 2008-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWMEMORYPOOLARENA_HPP_
#define MW_MWMEMORYPOOLARENA_HPP_
#include "mwDeprecated.hpp"
#include "mwWarningPragmas.hpp"

MW_WARNING_PUSH
MW_WARNING_DISABLE_DEPRECATED

#include "mwMemoryVirtual.hpp"
#include <cstring>
#include <list>

#if defined (_WIN32)
#if !defined(_WIN64)
typedef int ssize_t;
#else
typedef __int64 ssize_t;
#endif
#endif

typedef size_t uintptr_t;	// TODO: PVS-Studio warning V677: Custom declaration of a standard 'uintptr_t'. The system header file should be used: #include "STDDEF.H"
typedef ssize_t intptr_t;	// TODO: PVS-Studio warning V677: Custom declaration of a standard 'intptr_t'. The system header file should be used: #include "STDDEF.H"

namespace misc
{
	typedef unsigned char byte_t;
    class MW_5AXUTIL_API MW_DEPRECATED("mwMemoryPoolArena is deprecated since 2022.04. Use mwMemoryPool instead.") mwMemoryPoolArena
    {
    public:
        typedef std::list<mwMemoryPoolArena*> List;

    public:
        mwMemoryPoolArena(size_t nodeSize, size_t nodeCount)
          : m_NodeSize(nodeSize),
            m_NodeCount(nodeCount),
            m_UsedNodeCount(0),
            m_Node(static_cast<byte_t*>(mwMemoryVirtual::Alloc(nodeCount * nodeSize))),
            m_FirstFreeNode(NULL)
        {
            Clear();
        }

        ~mwMemoryPoolArena()
        {
            mwMemoryVirtual::Free(m_Node);

#if defined(_DEBUG)
            m_Node = NULL;
            m_NodeSize = 0;
            m_NodeCount = 0;
#endif
        }

        bool IsEmpty() const
        {
            return m_UsedNodeCount == 0;
        }

        bool IsOwned(const void* node) const
        {
            const byte_t* ptr = static_cast<const byte_t*>(node);
            return ptr >= m_Node && (ptr + m_NodeSize) <= (m_Node + m_NodeCount * m_NodeSize);
        }

        size_t GetMemoryUsage() const
        {
            return mwMemoryVirtual::QuerySize(m_Node);
        }

        size_t GetAllocatedNodeCount() const
        {
            return m_UsedNodeCount;
        }

        void* Alloc()
        {
            if (m_UsedNodeCount >= m_NodeCount)
                return NULL;

            void* ptr = m_FirstFreeNode;
            m_FirstFreeNode = reinterpret_cast<byte_t*>(*reinterpret_cast<uintptr_t*>(m_FirstFreeNode));
            ++m_UsedNodeCount;
            return ptr;
        }

        void Free(void* node)
        {
#if defined(_DEBUG)
            memset(node, ARENA_FILLER, m_NodeSize);
#endif

            uintptr_t* nodePtr = static_cast<uintptr_t*>(node);
            *nodePtr = reinterpret_cast<uintptr_t>(m_FirstFreeNode);
            m_FirstFreeNode = static_cast<byte_t*>(node);

            // FIXME: check for double free
            --m_UsedNodeCount;
        }

        bool FreeIfOwned(void* node)
        {
            if (!IsOwned(node))
                return false;
            Free(node);
            return true;
        }

        void Clear()
        {
#if defined(_DEBUG)
            memset(m_Node, ARENA_FILLER, m_NodeCount * m_NodeSize);
#endif

            byte_t* node = m_Node;
            uintptr_t nextNodeAddress = reinterpret_cast<uintptr_t>(node) + m_NodeSize;
            for (size_t i = 0; i < m_NodeCount - 1; ++i)
            {
                *reinterpret_cast<uintptr_t*>(node) = nextNodeAddress;
                node += m_NodeSize;
                nextNodeAddress += m_NodeSize;
            }
            *reinterpret_cast<uintptr_t*>(node) = uintptr_t(0);

            m_UsedNodeCount = 0;
            m_FirstFreeNode = m_Node;
        }

    private:
        mwMemoryPoolArena(const mwMemoryPoolArena& /*other*/);
        mwMemoryPoolArena& operator=(const mwMemoryPoolArena& /*other*/);

    private:
        enum { ARENA_FILLER = 0x21 };

        size_t m_NodeSize;
        size_t m_NodeCount;
        size_t m_UsedNodeCount;

        byte_t* m_Node;
        byte_t* m_FirstFreeNode;
    };
}

MW_WARNING_POP

#endif	//	MW_MWMEMORYPOOLARENA_HPP_
