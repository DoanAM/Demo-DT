// (C) 2010-2019 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWARCATTRIBUTERETRIEVER_HPP_
#define MW_MWARCATTRIBUTERETRIEVER_HPP_
#include "mwArcAttribute.hpp"
#include "mwExtendedMoveAttribute.hpp"

class MW_5AXUTIL_API mwArcAttributeRetriever: protected mwExtendedMoveAttributeVisitor
{
public:
	mwArcAttributeRetriever(): m_hasArcAttribute(false) {}

	mwArcAttributeRetriever(const mwExtendedMoveAttributePtr& extendedMoveAttribute);

	mwArcAttributeRetriever(const mwExtendedMoveAttributeList& extendedMoveAttributes);

	void Check(const mwExtendedMoveAttributeList& extendedMoveAttributes);

	virtual ~mwArcAttributeRetriever(void);

	/// returns arc attribute
	misc::mwAutoPointer<mwArcAttribute> GetArcAttribute();

	/// returns true if visited attribute is arc attribute
	bool HasArcAttribute();

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
#pragma warning(suppress : 4251)
	misc::mwAutoPointer<mwArcAttribute> m_arcAttribute;
	bool m_hasArcAttribute;
};
#endif  //	MW_MWARCATTRIBUTERETRIEVER_HPP_
