// (C) 2010-2014 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWEXTENDEDMOVEATTRIBUTE_HPP_
#define MW_MWEXTENDEDMOVEATTRIBUTE_HPP_
#include "mwAutoPointer.hpp"

#include <list>


class mwExtendedMoveAttribute;
class mwKeepPartsAttribute;
class mwThreadAttribute;
class mwArcAttribute;
class mwAdditionalInfoAttribute;
class mwChuckJawsStateChangeAttribute;
class mwCustomerMoveAttribute;
class mwShortestPathRotationAttribute;

typedef misc::mwAutoPointer<mwExtendedMoveAttribute> mwExtendedMoveAttributePtr;
typedef std::list<mwExtendedMoveAttributePtr> mwExtendedMoveAttributeList;

class mwExtendedMoveAttributeVisitor;


class MW_5AXUTIL_API mwExtendedMoveAttribute
{
public:
	/// Abstract visit
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) = 0;
	/// Abstract visit
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const = 0;

	/// Destructor
	virtual ~mwExtendedMoveAttribute() {}
};


/// Abstract mwExtendedMoveAttribute visitor
class MW_5AXUTIL_API mwExtendedMoveAttributeVisitor
{
public:
	virtual void Visit(const mwExtendedMoveAttribute& toVisit) = 0;


	virtual void Visit(const mwKeepPartsAttribute& toVisit) = 0;


	virtual void Visit(const mwAdditionalInfoAttribute& toVisit) = 0;


	virtual void Visit(const mwThreadAttribute& toVisit) = 0;


	virtual void Visit(const mwArcAttribute& toVisit) = 0;


	virtual void Visit(const mwChuckJawsStateChangeAttribute& toVisit) = 0;


	virtual void Visit(const mwCustomerMoveAttribute& toVisit) = 0;


	virtual void Visit(const mwShortestPathRotationAttribute& toVisit) = 0;


	/// Destructor
	virtual ~mwExtendedMoveAttributeVisitor() {}
};
#endif  //	MW_MWEXTENDEDMOVEATTRIBUTE_HPP_
