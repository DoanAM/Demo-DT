// (C) 2009-2021 by ModuleWorks GmbH
// Owner: ARB Library Structure

#ifndef MW_MWANYTYPE_HPP_
#define MW_MWANYTYPE_HPP_
#include <typeinfo>
#include "mwAutoPointer.hpp"
#include "mwOverrideFinal.hpp"

namespace misc
{
	class MW_5AXUTIL_API mwAnyType
	{
	public:
		typedef mwAnyType Myself;
		typedef misc::mwAutoPointer<Myself> Ptr;
		virtual const std::type_info &GetType() const = 0;

		virtual ~mwAnyType() {}

		template<class T> bool IsType() const;
	};

	template<class T> class MW_5AXUTIL_API mwTAnyType : public mwAnyType
	{
	public:
		mwTAnyType(const T &value);

		const T &GetValue() const;
		virtual const std::type_info &GetType() const MW_OVERRIDE;
	private:
		T m_value;
	};


	template<class T> bool mwAnyType::IsType() const
	{
		return GetType() == typeid( mwTAnyType<T> );
	}

	template<class T> mwTAnyType<T>::mwTAnyType( const T &value )
		: m_value( value )
	{
	}

	template<class T> const T &mwTAnyType<T>::GetValue() const
	{
		return m_value;
	}

	template<class T> const std::type_info &mwTAnyType<T>::GetType() const
	{
		return typeid(mwTAnyType<T>);
	}

	template<int K, class T> struct mwAnyTypeDeclaration
	{
	public:
		typedef T AttributeType;
		static int GetMapKey() { return K; }
	};
}
#endif	//	MW_MWANYTYPE_HPP_
