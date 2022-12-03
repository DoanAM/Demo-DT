// (C) 2009-2021 by ModuleWorks GmbH
// Owner: 5Axis Application

#ifndef MW_MWTPATTRIBUTE_HPP_
#define MW_MWTPATTRIBUTE_HPP_
#include "mwAnyType.hpp"
#include "mwCachingInternalDefs.hpp"
#include "mwTPAttributeDeclarations.hpp"

#include <map>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4459)
#endif


namespace cadcam
{
#pragma CACHING_INTERNAL_BEGIN
template <class Declarations>
class MW_5AXUTIL_API mwTPGenericAttributes: public Declarations
{
public:
	typedef misc::mwAutoPointer<mwTPGenericAttributes> Ptr;
	typedef misc::mwAnyType Attribute;

	template <class Functor>
	void ForEachAttributeDefinition(Functor& functor) const
	{
		m_declarations.ForEachAttributeDefinition(functor);
	}

	template <class Functor>
	void ForEachAttribute(Functor functor) const
	{
		FunctorForEachAttribute<Functor> functorForEachAttribute(functor, *this);
		m_declarations.template ForEachAttributeDefinition<FunctorForEachAttribute<Functor>>(
			functorForEachAttribute);
	}


	template <class Functor>
	class FunctorForEachAttribute
	{
	public:
		/// Constructor
		FunctorForEachAttribute(Functor& functor, const mwTPGenericAttributes& TPAttributes)
			: m_functor(functor), m_TPAttributes(TPAttributes)
		{
		}

		template <typename AttrDef>
		void operator()()
		{
			if (m_TPAttributes.template HasAttribute<AttrDef>())
			{
				Declarations::template Call<AttrDef>(m_functor);
			}
		}

	private:
		FunctorForEachAttribute& operator=(const FunctorForEachAttribute&);  // = delete
		Functor& m_functor;
		const mwTPGenericAttributes& m_TPAttributes;
	};


	class FunctorForEachCompare
	{
	public:
		/// Constructor
		FunctorForEachCompare(
			const mwTPGenericAttributes& TPAttributes1,
			const mwTPGenericAttributes& TPAttributes2,
			bool& bEqual)
			: m_TPAttributes1(TPAttributes1), m_TPAttributes2(TPAttributes2), m_bEqual(bEqual)
		{
			m_bEqual = true;
		}

		template <typename AttrDef>
		void operator()()
		{
			if (m_bEqual && !m_TPAttributes1.IsAttributeEqual<AttrDef>(m_TPAttributes2))
				m_bEqual = false;
		}

	private:
		FunctorForEachCompare& operator=(const FunctorForEachCompare&);  // = delete
		const mwTPGenericAttributes& m_TPAttributes1;
		const mwTPGenericAttributes& m_TPAttributes2;
		bool& m_bEqual;
	};

	/// It tests that the attributes are the same
	const bool operator==(const mwTPGenericAttributes& toCompare) const
	{
		if (&toCompare == this)
			return true;

		bool bEqual;
		FunctorForEachCompare functorForEachCompare(*this, toCompare, bEqual);
		m_declarations.template ForEachAttributeDefinition<FunctorForEachCompare>(
			functorForEachCompare);

		return bEqual;
	}

	/// It tests the attributes for inequality
	inline const bool operator!=(const mwTPGenericAttributes& toCompare) const
	{
		return !((*this) == toCompare);
	};


	template <class AttrDef>
	void SetAttribute(const typename AttrDef::AttributeType& value)
	{
		m_values[AttrDef::GetMapKey()] =
			AttributePtr(new misc::mwTAnyType<typename AttrDef::AttributeType>(value));
	}

	template <class AttrDef>
	void ClearAttribute()
	{
		AttributeMapIt attr = m_values.find(AttrDef::GetMapKey());

		if (attr != m_values.end())
			m_values.erase(attr);
	}

	void ClearAttributes() { m_values.clear(); }

	template <class AttrDef>
	const typename AttrDef::AttributeType& GetAttribute() const
	{
		AttributeMapConstIt attr = m_values.find(AttrDef::GetMapKey());

		if (attr == m_values.end())
			throw misc::mwException(0, _T("Attribute not set"));

		if (!attr->second->IsType<typename AttrDef::AttributeType>())
			throw misc::mwException(0, _T("Wrong attribute type"));

		const misc::mwTAnyType<typename AttrDef::AttributeType>& tAttr =
			static_cast<const misc::mwTAnyType<typename AttrDef::AttributeType>&>(*(attr->second));

		return tAttr.GetValue();
	}

	template <class AttrDef>
	const typename AttrDef::AttributeType& GetAttributeDefault(
		const typename AttrDef::AttributeType& defaultAttribType) const
	{
		AttributeMapConstIt attr = m_values.find(AttrDef::GetMapKey());

		if (attr == m_values.end())
			return defaultAttribType;

		if (!attr->second->IsType<typename AttrDef::AttributeType>())
			return defaultAttribType;

		const misc::mwTAnyType<typename AttrDef::AttributeType>& tAttr =
			static_cast<const misc::mwTAnyType<typename AttrDef::AttributeType>&>(*(attr->second));

		return tAttr.GetValue();
	}

	template <class AttrDef>
	bool IsAttributeEqual(const mwTPGenericAttributes& other) const
	{
		const bool bHas1 = HasAttribute<AttrDef>();
		const bool bHas2 = other.HasAttribute<AttrDef>();

		if (bHas1 && bHas2)
			if (GetAttribute<AttrDef>() == other.GetAttribute<AttrDef>())
				return true;
			else
				return false;
		else if (bHas1 || bHas2)
			return false;
		else
			return true;
	}

	template <class AttrDef>
	bool HasAttribute() const
	{
		AttributeMapConstIt attr = m_values.find(AttrDef::GetMapKey());

		if (attr == m_values.end())
			return false;

		if (!attr->second->IsType<typename AttrDef::AttributeType>())
			return false;

		return true;
	}

	const mwTPGenericAttributes<Declarations>& GetAttributes() const { return *this; }

	const size_t GetNumberOfAttributes() const { return m_values.size(); }

protected:
	void CopyAttributesFrom(const mwTPGenericAttributes& attr)
	{
		m_values.clear();
		m_values.insert(attr.m_values.begin(), attr.m_values.end());
	}

	class FunctorForEachAttributeDeepCopy
	{
	public:
		/// Constructor
		FunctorForEachAttributeDeepCopy(
			const mwTPGenericAttributes& toCopy, mwTPGenericAttributes& retCopy)
			: m_toCopy(toCopy), retCopy(retCopy)
		{
			retCopy.ClearAttributes();
		}
		FunctorForEachAttributeDeepCopy(const FunctorForEachAttributeDeepCopy& other)
			: m_toCopy(other.m_toCopy), retCopy(other.retCopy)
		{
		}

		template <typename AttrDef>
		void operator()()
		{
			retCopy.SetAttribute<AttrDef>(m_toCopy.GetAttribute<AttrDef>());
		}

	private:
		FunctorForEachAttributeDeepCopy& operator=(FunctorForEachAttributeDeepCopy&);  // = delete
		const mwTPGenericAttributes& m_toCopy;
		mwTPGenericAttributes& retCopy;
	};

	/// Deep copy attributes
	void DeepCopy(const mwTPGenericAttributes& toCopy)
	{
		m_values.clear();

		FunctorForEachAttributeDeepCopy functorDeepCopyAttributes(toCopy, *this);
		toCopy.ForEachAttribute<FunctorForEachAttributeDeepCopy>(functorDeepCopyAttributes);
	}

private:
	typedef Attribute::Ptr AttributePtr;
	typedef std::map<int, AttributePtr> AttributeMap;
	typedef AttributeMap::iterator AttributeMapIt;
	typedef AttributeMap::const_iterator AttributeMapConstIt;

private:
#pragma warning(push)
#pragma warning( \
	disable : 4251)  // needed for CContour, which extends this class and is dll exported
	AttributeMap m_values;
	Declarations m_declarations;
#pragma warning(pop)
};
#pragma CACHING_INTERNAL_END

typedef mwTPGenericAttributes<mwTPAttributeDeclarations> mwTPAttributes;
}  // namespace cadcam

#ifdef _WIN32
#pragma warning(pop)
#endif
#endif  //	MW_MWTPATTRIBUTE_HPP_
