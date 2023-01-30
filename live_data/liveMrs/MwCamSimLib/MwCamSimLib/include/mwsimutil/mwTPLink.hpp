// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPLINK_HPP_
#define MW_MWTPLINK_HPP_

#include "mwCadcamEnumDefinitions.hpp"
#include "mwTPSection.hpp"


namespace cadcam
{
/// implements a toolpath link between toolpath contours described by moves
class MW_5AXUTIL_API mwTPLink: public mwTPSection
{
public:
	typedef misc::mwAutoPointer<mwTPLink> Ptr;

	typedef mwTPLinkN::Types Types;
	static const Types APPROACH_LINK = mwTPLinkN::APPROACH_LINK;
	static const Types LEAD_IN_LINK = mwTPLinkN::LEAD_IN_LINK;
	static const Types CONNECTION_NOT_CLEAREANCE_ARREA_LINK =
		mwTPLinkN::CONNECTION_NOT_CLEAREANCE_ARREA_LINK;
	static const Types CONNECTION_CLEAREANCE_ARREA_LINK =
		mwTPLinkN::CONNECTION_CLEAREANCE_ARREA_LINK;
	static const Types LEAD_OUT_LINK = mwTPLinkN::LEAD_OUT_LINK;
	static const Types RETRACT_LINK = mwTPLinkN::RETRACT_LINK;

	/// constructor
	explicit mwTPLink(const Types linkType, const mwTPAttributes& attributes = mwTPAttributes())
		: mwTPSection(attributes), m_linkType(linkType)
	{
	}

	/// implement the visitor pattern
	///
	/// @param visitor the vistior
	virtual void AcceptVisitor(mwTPSVisitor& visitor) const { visitor.Visit(*this); };

	/// It tests that 2 links have the same structure and equal moves
	const bool operator==(const mwTPLink& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return (m_linkType == toCompare.m_linkType && mwTPSection::operator==(toCompare));
	}

	/// It tests 2 links for inequality
	inline const bool operator!=(const mwTPLink& toCompare) const
	{
		return !((*this) == toCompare);
	};

	///	It tests that 2 links has the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos
	///		@param toCompare the slice to be compared with.
	///		@param delta given tolerance factor.
	///		@param minCos given minimal cosinus of angle between moves orientations.
	const bool ExactCompareTolerance(const mwTPLink& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		return mwTPSection::ExactCompareTolerance(toCompare, delta, minCos);
	}

	/// gets LinkType
	///
	///	@return the LinkType
	inline const Types GetLinkType() const { return m_linkType; };

	/// sets LinkType
	///
	///	@param linkType the new LinkType
	inline void SetLinkType(const Types linkType) { m_linkType = linkType; };

	/// Deep-copy a given tp link into this object
	///
	///	@param toCopy is input tp link which will  be deep-copied in this object
	void DeepCopy(const mwTPLink& toCopy)
	{
		mwTPSection::DeepCopy(toCopy);
		m_linkType = toCopy.m_linkType;
	}

private:
	Types m_linkType;
};
}  // namespace cadcam
#endif  //	MW_MWTPLINK_HPP_
