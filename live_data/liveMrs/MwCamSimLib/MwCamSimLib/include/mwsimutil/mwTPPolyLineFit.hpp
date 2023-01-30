// (C) 2003-2016 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPPOLYLINEFIT_HPP_
#define MW_MWTPPOLYLINEFIT_HPP_

#include "mwTPSectionFit.hpp"


namespace cadcam
{
/// implements a toolpath PolyLineFit described by moves
class MW_5AXUTIL_API mwTPPolyLineFit: public mwTPSectionFit
{
public:
	typedef misc::mwAutoPointer<mwTPPolyLineFit> Ptr;

	mwTPPolyLineFit() {}

	/// implement the visitor pattern
	///
	///	@param visitor the vistior
	virtual void AcceptVisitor(mwTPSFitVisitor& visitor) const { visitor.Visit(*this); };

	///	It tests that 2 PolyLineFit has the same structure and equal moves
	const bool operator==(const mwTPPolyLineFit& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return mwTPSectionFit::operator==(toCompare);
	}

	///	It tests 2 contours for inequality
	inline const bool operator!=(const mwTPPolyLineFit& toCompare) const
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
		const mwTPPolyLineFit& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		return mwTPSectionFit::ExactCompareTolerance(toCompare, delta, minCos);
	}

	/// Deep-copy a given tp polyline fit into this object
	///
	///	@param toCopy is input tp polyline fit which will  be deep-copied in this object
	void DeepCopy(const mwTPPolyLineFit& toCopy) { mwTPSectionFit::DeepCopy(toCopy); }
};
}  // namespace cadcam
#endif  //	MW_MWTPPOLYLINEFIT_HPP_
