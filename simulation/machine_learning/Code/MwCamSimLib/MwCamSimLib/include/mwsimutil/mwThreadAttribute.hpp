// (C) 2011-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTHREADATTRIBUTE_HPP_
#define MW_MWTHREADATTRIBUTE_HPP_
#include "mwEnrichedPostedMove.hpp"
#include "mwKeepPartsAttribute.hpp"
#include "mwTPoint3d.hpp"

/// Move level information regarding a threading process
class MW_5AXUTIL_API mwThreadAttribute: public mwExtendedMoveAttribute
{
public:
	/// mwThreadAttribute
	/// Thread attribute. Determined by a lead value and an offset value
	mwThreadAttribute(void);


	/// mwThreadAttribute destructor
	virtual ~mwThreadAttribute(void);


	/// mwThreadAttribute equal operator
	const bool operator==(const mwThreadAttribute& tc) const;


	/// mwThreadAttribute different operator
	const bool operator!=(const mwThreadAttribute& tc) const;


	/// Accept mwExtendedMoveAttributeVisitor visitor
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor);


	/// Accept mwExtendedMoveAttributeVisitor visitor const
	virtual void AcceptVisitor(mwExtendedMoveAttributeVisitor& visitor) const;


	/// Returns the offset
	const double GetOffset() const;


	/// Sets the offset
	void SetOffset(const double offset);


	/// Returns the lead
	const double GetLead() const;


	/// Sets the lead
	void SetLead(const double toSet);

protected:
	double m_offset;
	double m_lead;
};
#endif  //	MW_MWTHREADATTRIBUTE_HPP_
