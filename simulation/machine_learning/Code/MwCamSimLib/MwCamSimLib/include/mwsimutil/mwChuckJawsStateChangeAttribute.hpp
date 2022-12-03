// (C) 2012-2017 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCHUCKJAWSSTATECHANGEATTRIBUTE_HPP_
#define MW_MWCHUCKJAWSSTATECHANGEATTRIBUTE_HPP_
#include "mwExtendedMoveAttribute.hpp"


/// mwChuckJawsStateChangeAttribute - stores information regarding a move level change in chuck jaws
/// state
class MW_5AXUTIL_API mwChuckJawsStateChangeAttribute: public mwExtendedMoveAttribute
{
public:
	typedef std::vector<misc::mwstring> objectList;


	enum State
	{
		CLAMPED = 0,
		UNCLAMPED = 1
	};


	/// mwChuckJawsStateChangeAttribute
	/// Stores information for a move that defines a change of the chuck jaws state
	/// @param jawObjects - vector of object ids
	/// @param newState - the state of the jaws, value from an enum
	mwChuckJawsStateChangeAttribute(const objectList& jawObjects, const State newState);


	///  mwChuckJawsStateChangeAttribute
	/// Stores information for a move that defines a change of the chuck jaws state
	/// @param revolvingSetId - name of the revolved set associated with the jaws
	/// @param newState - the state of the jaws, value from an enum
	/// @param unclampOffset - offset
	mwChuckJawsStateChangeAttribute(
		const misc::mwstring& revolvingSetId, const State newState, int unclampOffset = 0);


	/// mwChuckJawsStateChangeAttribute equal operator
	const bool operator==(const mwChuckJawsStateChangeAttribute& tc) const;


	/// mwChuckJawsStateChangeAttribute different operator
	const bool operator!=(const mwChuckJawsStateChangeAttribute& tc) const;


	/// Returns the name of the revolving set
	const misc::mwstring& GetRevolvingSetId() const;


	/// Returns a reference to the list of jaw objects
	const objectList& GetJawObjects() const;


	/// Returns the state of the jaws
	const State GetNewState() const;


	/// Returns the offset of the unclamped jaws
	const int GetUnclampOffset() const;


	/// Sets the clamp target
	void SetClampTargetID(const misc::mwstring& toSet);


	/// Returns the clamp target
	const misc::mwstring& GetClampTargetID() const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Accept mwExtendedMoveAttributeVisitor visitor const
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;

private:
	State m_newState;
	misc::mwstring m_revolvingSetId;
	int m_unclampOffset;
	misc::mwstring m_clampTargetID;
	objectList m_jawObjects;
};
#endif  //	MW_MWCHUCKJAWSSTATECHANGEATTRIBUTE_HPP_
