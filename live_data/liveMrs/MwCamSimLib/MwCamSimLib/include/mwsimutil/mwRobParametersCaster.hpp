// (C) 2019-2021 by ModuleWorks GmbH
// Owner: MultiXPost

#ifndef MW_MWROBPARAMETERSCASTER_HPP_
#define MW_MWROBPARAMETERSCASTER_HPP_

#include "mwAutoPointer.hpp"
#include "mwRobMXPParams.hpp"
#include "mwPostException.hpp"

namespace post
{
class MW_5AXUTIL_API mwRobParametersCaster
{
public:
	template <typename T>
	static const misc::mwAutoPointer<T> SafeCast2Constraint(
		const misc::mwAutoPointer<mwEndEffector>& endEffector)
	{
		mwCasting2EndEffectorChecker<T> caster;
		endEffector->AcceptVirtual(caster);

		misc::mwAutoPointer<T> result;
		result.UnsafeAssign(endEffector);
		return result;
	}

	template <typename T>
	class mwCasting2EndEffectorChecker : public mwConstraintVisitor
	{
	public:
		explicit mwCasting2EndEffectorChecker(bool bAlwaysThrow = true)
			: m_bAlwaysThrow(bAlwaysThrow), m_bExceptionMet(false)
		{
		}

		~mwCasting2EndEffectorChecker()
		{
		}

		void Visit(const T&)
		{
			// do conversion;
		}

		const bool MetException() const
		{
			return m_bExceptionMet;
		}

	private:
		bool m_bExceptionMet;
		bool m_bAlwaysThrow;

		virtual void Default()
		{
			m_bExceptionMet = true;
			if (m_bAlwaysThrow)
				throw mwPostException(mwPostException::WRONG_METHOD_CALLED);
		}
	};
};
}  // namespace post
#endif	//	MW_MWROBPARAMETERSCASTER_HPP_
