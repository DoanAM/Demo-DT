// (C) 2006-2021 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWSOLIDDEFINITIONCASTER_HPP_
#define MW_MWSOLIDDEFINITIONCASTER_HPP_
#include "mwExtrudedSolidDefinition.hpp"
#include "mwRevolvedSolidDefinition.hpp"
#include "mwSolidDefinition.hpp"
#include "mwTurningSolidDefinition.hpp"


namespace cadcam
{
// a checking class for safe conversion
template <class T>
class MW_5AXUTIL_API mwCasting2SolidDefinitionChecker: public mwSolidDefinitionVisitorGetter<T>
{
public:
	~mwCasting2SolidDefinitionChecker() {}

	void Visit(const mwSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwSolidDefinition& to mwRevolvedSolidDefinition& type ")
			_T("object"));
	}

	void Visit(const mwRevolvedSolidDefinition<T>&)
	{
		// do conversion;
	}

	void Visit(const mwExtrudedSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwExtrudedSolidDefinition& to mwRevolvedSolidDefinition& ")
			_T("type object"));
	}

	void Visit(const mwMeshSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwMeshSolidDefinition& to mwRevolvedSolidDefinition& type ")
			_T("object"));
	}

	void Visit(const mwTurningSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwTurningSolidDefinition& to mwRevolvedSolidDefinition& ")
			_T("type object"));
	}

	void Visit(const mwContourTurningSolidDefinition<T>&)
	{
		MW_EXCEPTION(
			"Illegal conversion of mwContourTurningSolidDefinition& to mwRevolvedSolidDefinition& "
			"type object");
	}

	void Visit(const mwPrimeTurningSolidDefinition<T>&)
	{
		MW_EXCEPTION(
			"Illegal conversion of mwPrimeTurningSolidDefinition& to mwRevolvedSolidDefinition& "
			"type object");
	}

	void Visit(const mwWireSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwWireSolidDefinition& to mwRevolvedSolidDefinition& type ")
			_T("object"));
	}

	void Visit(const mwThreadTapSolidDefinition<T>&)
	{
		throw misc::mwException(
			0,
			_T("Illegal conversion of mwThreadTapSolidDefinition& to mwRevolvedSolidDefinition& ")
			_T("type object"));
	}
};


template <typename T>
class MW_5AXUTIL_API mwSolidDefinitionCaster
{
	typedef cadcam::mwRevolvedSolidDefinition<T> RevolvedSolidDefinition;
	typedef cadcam::mwSolidDefinition<T> SolidDefinition;

public:
	~mwSolidDefinitionCaster(){};


	static const misc::mwAutoPointer<RevolvedSolidDefinition> SafeCast2RevolvedSolidDefinition(
		const misc::mwAutoPointer<SolidDefinition> solidPtr)
	{
		cadcam::mwCasting2SolidDefinitionChecker<T> castingChecker;
		solidPtr->AcceptVisitor(castingChecker);
		misc::mwAutoPointer<RevolvedSolidDefinition> rtrn;
		rtrn.UnsafeAssign(solidPtr);
		return rtrn;
	}


	static const RevolvedSolidDefinition& SafeCast2RevolvedSolidDefinition(
		const SolidDefinition& solid)
	{
		cadcam::mwCasting2SolidDefinitionChecker<T> castingChecker;
		solid.AcceptVisitor(castingChecker);
		const RevolvedSolidDefinition* revSolidDef =
			static_cast<const RevolvedSolidDefinition*>(&solid);
		return *revSolidDef;
	}


private:
	// private constructor since it is a static class
	mwSolidDefinitionCaster();
};

}  // namespace cadcam
#endif  //	MW_MWSOLIDDEFINITIONCASTER_HPP_
