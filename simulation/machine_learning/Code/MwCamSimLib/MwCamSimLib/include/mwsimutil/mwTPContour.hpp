// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPCONTOUR_HPP_
#define MW_MWTPCONTOUR_HPP_

#include "mwTPSection.hpp"


namespace cadcam
{
/// implements a toolpath contour described by moves
class MW_5AXUTIL_API mwTPContour: public mwTPSection
{
public:
	typedef misc::mwAutoPointer<mwTPContour> Ptr;

	mwTPContour(const mwTPAttributes& attributes = mwTPAttributes()): mwTPSection(attributes) {}
	/// implement the visitor pattern
	///
	///	@param visitor the vistior
	virtual void AcceptVisitor(mwTPSVisitor& visitor) const { visitor.Visit(*this); };

	/// It tests that 2 contours has the same structure and equal moves
	const bool operator==(const mwTPContour& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return mwTPSection::operator==(toCompare);
	}

	/// It tests 2 contours for inequality
	inline const bool operator!=(const mwTPContour& toCompare) const
	{
		return !((*this) == toCompare);
	};

	///	It tests that 2 contours has the same structure and equivalent moves
	///
	/// Besides structures it tests that distance between moves positions are within tolerance
	///	and if the tool orientation vectors differ not more than minCos
	///		@param toCompare the slice to be compared with.
	///		@param delta given tolerance factor.
	///		@param minCos given minimal cosinus of angle between moves orientations.
	const bool ExactCompareTolerance(
		const mwTPContour& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		return mwTPSection::ExactCompareTolerance(toCompare, delta, minCos);
	}

	/// Deep-copy a given tp contour into this object
	///
	///	@param toCopy is input tp contour which will  be deep-copied in this object
	void DeepCopy(const mwTPContour& toCopy) { mwTPSection::DeepCopy(toCopy); }
};
}  // namespace cadcam
#endif  //	MW_MWTPCONTOUR_HPP_
