// (C) 2014-2020 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWROTATIONATTRIBUTECHECK_HPP_
#define MW_MWROTATIONATTRIBUTECHECK_HPP_
#include "mwExtendedMoveAttribute.hpp"


class MW_5AXUTIL_API mwRotationAttributeCheck: protected mwExtendedMoveAttributeVisitor
{
public:
	mwRotationAttributeCheck(const mwExtendedMoveAttributePtr& extendedMoveAttribute);

	mwRotationAttributeCheck(const mwExtendedMoveAttributeList& extendedMoveAttributes);

	virtual ~mwRotationAttributeCheck(void);

	/// returns true if visited attribute is rotation attribute
	bool HasRotationAttribute();
	bool IsAtLeastOneAxisProcessedForShortestPath();

protected:
	virtual void Visit(const mwExtendedMoveAttribute& toVisit);
	virtual void Visit(const mwKeepPartsAttribute& toVisit);
	virtual void Visit(const mwAdditionalInfoAttribute& toVisit);
	virtual void Visit(const mwThreadAttribute& toVisit);
	virtual void Visit(const mwArcAttribute& toVisit);
	virtual void Visit(const mwChuckJawsStateChangeAttribute& toVisit);
	virtual void Visit(const mwCustomerMoveAttribute& toVisit);
	virtual void Visit(const mwShortestPathRotationAttribute& toVisit);

private:
	bool m_hasRotationAttribute;
	bool m_isShortestPath;
};
#endif  //	MW_MWROTATIONATTRIBUTECHECK_HPP_
