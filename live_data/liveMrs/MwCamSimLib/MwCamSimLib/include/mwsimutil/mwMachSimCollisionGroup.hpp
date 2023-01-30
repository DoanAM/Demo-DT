// (C) 2003-2020 by ModuleWorks GmbH
// Owner: MachSim

#ifndef MW_MWMACHSIMCOLLISIONGROUP_HPP_
#define MW_MWMACHSIMCOLLISIONGROUP_HPP_
#include "mwSimUtilDllImpExpDef.hpp"
#include "mwAutoPointer.hpp"
#include <list>
#include "mwDeprecated.hpp"
#include "mwWarningPragmas.hpp"

class MW_SIMUTIL_API mwMachSimCollisionGroup
{
public:
	//! types
	typedef misc::mwAutoPointer<mwMachSimCollisionGroup>	Ptr;
	typedef misc::mwstring									object;
	typedef std::list<misc::mwstring>						objectGroup;
	typedef objectGroup::const_iterator						ogIterator;

	//!Default constructor
	mwMachSimCollisionGroup();

	//!Copy constructor
	mwMachSimCollisionGroup(const mwMachSimCollisionGroup& toCopy);

	//! Clone
	const misc::mwAutoPointer<mwMachSimCollisionGroup> Clone() const;

	//!Add object to the group
	void AddObject( const object &toAdd );

	//!Get list of the objects
	const objectGroup &GetObjects() const;

	//!Get list of the objects
	objectGroup &GetObjects();

	//!Get begin of the objects
	ogIterator GetObjectsBegin() const;

	//!Get end of the objects
	ogIterator GetObjectsEnd() const;

	//!Clear all objects
	void ClearObjects();

	//!Rename object
	void UpdateGroup(const misc::mwstring& oldID, const misc::mwstring& newID);

	//!Remove object
	void RemoveObject(const misc::mwstring& removedID );

	//!Query if object is added to group
	const bool IsObjectDefined(const misc::mwstring& ID) const;

	//! collision group type
	enum MW_DEPRECATED("Deprecated in 2015.12, do not use it") groupType
	{
		STATIC,
		DYNAMIC
	};


MW_WARNING_PUSH
MW_WARNING_DISABLE_DEPRECATED

	MW_DEPRECATED("Deprecated in 2015.12, do not use it")
	//!Set group type (static, dynamic)
	void SetGroupType(const groupType &toSet);

	MW_DEPRECATED("Deprecated in 2015.12, do not use it")
	//!Get current group type
	const groupType &GetGroupType() const;

MW_WARNING_POP

protected:
private:
#pragma warning(suppress:4251)
	objectGroup		mGroup;

MW_WARNING_PUSH
MW_WARNING_DISABLE_DEPRECATED
	groupType		mType;
MW_WARNING_POP
};
#endif	//	MW_MWMACHSIMCOLLISIONGROUP_HPP_
