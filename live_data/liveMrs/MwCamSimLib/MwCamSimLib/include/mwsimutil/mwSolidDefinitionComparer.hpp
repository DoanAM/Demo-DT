// (C) 2007-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSOLIDDEFINITIONCOMPARER_HPP_
#define MW_MWSOLIDDEFINITIONCOMPARER_HPP_
#include "mwContourTurningSolidDefinition.hpp"
#include "mwDllImpExpDef.hpp"
#include "mwExtrudedSolidDefinition.hpp"
#include "mwMeshSolidDefinition.hpp"
#include "mwPrimeTurningSolidDefinition.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwSolidDefinition.hpp"
#include "mwThreadTapSolidDefinition.hpp"
#include "mwTurningSolidDefinition.hpp"
#include "mwWireSolidDefinition.hpp"
#include "mwcadcamException.hpp"

namespace cadcam
{
/// This class compares a solid definition derived from cadcam::mwSolidDefinition object
template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionComparer: public cadcam::mwSolidDefinitionVisitorGetter<T>
{
public:
	mwSolidDefinitionComparer(const typename mwSolidDefinition<T>::Ptr& second)
		: m_second(second), m_equal(false)
	{
	}
	/// @name Visitor pattern
	/// @{
	virtual void Visit(const mwSolidDefinition<T>&)
	{
		throw mwcadcamException(mwcadcamException::UNKNOWN_SOLID_DEFINITION);
	}
	virtual void Visit(const mwRevolvedSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{  // visitor variable is first not second, so call with second
			m_pRevolved = &visitor;
			m_pRevolved.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{  // visitor variable is second, we should do comparison
			if (m_pRevolved.IsNull())
			{  // first is of a different type than second
				m_equal = false;
			}
			else
			{  // same type, let's compare them
				m_equal = (visitor == *m_pRevolved);
			}
		}
	}
	virtual void Visit(const mwWireSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{  // visitor variable is first not second, so call with second
			m_pWire = &visitor;
			m_pWire.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{  // visitor variable is second, we should do comparison
			if (m_pWire.IsNull())
			{  // first is of a different type than second
				m_equal = false;
			}
			else
			{  // same type, let's compare them
				m_equal = (visitor == *m_pWire);
			}
		}
	}
	virtual void Visit(const mwExtrudedSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{  // visitor variable is first not second, so call with second
			m_pExtruded = &visitor;
			m_pExtruded.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{  // visitor variable is second, we should do comparison
			if (m_pExtruded.IsNull())
			{  // first is of a different type than second
				m_equal = false;
			}
			else
			{  // same type, let's compare them
				m_equal = (visitor == *m_pExtruded);
			}
		}
	}
	virtual void Visit(const mwMeshSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{  // visitor variable is first not second, so call with second
			m_pMesh = &visitor;
			m_pMesh.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{  // visitor variable is second, we should do comparison
			if (m_pMesh.IsNull())
			{  // first is of a different type than second
				m_equal = false;
			}
			else
			{  // same type, let's compare them
				m_equal = (visitor == *m_pMesh);
			}
		}
	}
	virtual void Visit(const mwTurningSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{
			m_turningSolid = &visitor;
			m_turningSolid.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{
			m_equal = m_turningSolid.IsNotNull() && (visitor == *m_turningSolid);
		}
	}
	virtual void Visit(const mwContourTurningSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{
			m_contourTurningSolid = &visitor;
			m_contourTurningSolid.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{
			m_equal = m_contourTurningSolid.IsNotNull() && (visitor == *m_contourTurningSolid);
		}
	}

#ifndef MW_USE_VS2008_COMPATIBILITY
	virtual void Visit(const mwPrimeTurningSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{
			m_primeTurningSolid = &visitor;
			m_primeTurningSolid.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{
			m_equal = m_primeTurningSolid.IsNotNull() && (visitor == *m_primeTurningSolid);
		}
	}
#endif

	virtual void Visit(const mwThreadTapSolidDefinition<T>& visitor)
	{
		if (IsSolidsNull())
		{
			m_threadTapSolid = &visitor;
			m_threadTapSolid.Release();
			m_second->AcceptVisitor(*this);
		}
		else
		{
			m_equal = m_threadTapSolid.IsNotNull() && (visitor == *m_threadTapSolid);
		}
	}
	/// @}
	bool Equal() const { return m_equal; }

private:
	mwSolidDefinitionComparer& operator=(mwSolidDefinitionComparer&);
	bool m_equal;
#pragma warning(push)
#pragma warning(disable : 4251)
	const typename mwSolidDefinition<T>::Ptr& m_second;
	typename misc::mwAutoPointer<const mwRevolvedSolidDefinition<T>> m_pRevolved;
	typename misc::mwAutoPointer<const mwExtrudedSolidDefinition<T>> m_pExtruded;
	typename misc::mwAutoPointer<const mwMeshSolidDefinition<T>> m_pMesh;
	typename misc::mwAutoPointer<const mwWireSolidDefinition<T>> m_pWire;
	typename misc::mwAutoPointer<const mwTurningSolidDefinition<T>> m_turningSolid;
	typename misc::mwAutoPointer<const mwContourTurningSolidDefinition<T>> m_contourTurningSolid;
	typename misc::mwAutoPointer<const mwPrimeTurningSolidDefinition<T>> m_primeTurningSolid;
	typename misc::mwAutoPointer<const mwThreadTapSolidDefinition<T>> m_threadTapSolid;
#pragma warning(pop)

	bool IsSolidsNull() const
	{
		return m_pRevolved.IsNull() && m_pExtruded.IsNull() && m_pMesh.IsNull() &&
			m_pWire.IsNull() && m_turningSolid.IsNull() && m_contourTurningSolid.IsNull() &&
			m_threadTapSolid.IsNull();
	}
};
}  // namespace cadcam
#endif  //	MW_MWSOLIDDEFINITIONCOMPARER_HPP_
