// (C) 2013 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWCUSTOMERMOVEATTRIBUTE_HPP_
#define MW_MWCUSTOMERMOVEATTRIBUTE_HPP_
#include "mwExtendedMoveAttribute.hpp"


class MW_5AXUTIL_API mwCustomerMoveAttribute: public mwExtendedMoveAttribute
{
public:
	/// default ctor
	mwCustomerMoveAttribute(void);
	/// copy ctor
	mwCustomerMoveAttribute(const mwCustomerMoveAttribute& tc);
	/// dtor
	~mwCustomerMoveAttribute(void);
	/// copy op
	mwCustomerMoveAttribute& operator=(const mwCustomerMoveAttribute& tc);
	/// Accept visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);
	/// Accept visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;
};
#endif  //	MW_MWCUSTOMERMOVEATTRIBUTE_HPP_
