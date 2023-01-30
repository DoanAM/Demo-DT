// (C) 2003-2018 by ModuleWorks GmbH
// Owner: 3Axis

#ifndef MW_MWTPSECTIONFIT_HPP_
#define MW_MWTPSECTIONFIT_HPP_
#include "mwAutoPointer.hpp"
#include "mwCNCMove.hpp"
#include "mwCNCMoveUtils.hpp"
#include "mwCollectionOfContainers.hpp"
#include "mwMovesAccessor.hpp"
#include "mwTPAttribute.hpp"

#include <list>


namespace cadcam
{
class mwTPSectionFit;
class mwTPPolyLineFit;
class mwTPHelixFit;

/// Base class for any visitor classes derived from mwTPSectionFit.
/// Let's traverse the collection of pointers to mwTPSectionFit and perform actions
/// specific to a real sub-type of an object (helix/polyline)
class MW_5AXUTIL_API mwTPSFitVisitor
{
public:
	virtual ~mwTPSFitVisitor() MW_DEFAULT_DESTRUCTOR_IMPL

	virtual void Visit(const mwTPSectionFit& tps) = 0;
	virtual void Visit(const mwTPPolyLineFit& polyLineFit) = 0;
	virtual void Visit(const mwTPHelixFit& helixFit) = 0;
};

/// Base class for any toolpath section fit.
/// Implements a list of moves that represent a fit for other geometrical structures (such as
/// polyline or helix).
class MW_5AXUTIL_API mwTPSectionFit: public mwMovesAccessor<std::list<movePtr>>
{
public:
	typedef misc::mwAutoPointer<mwTPSectionFit> Ptr;

	mwTPSectionFit() {}
	virtual ~mwTPSectionFit() {}
	/// Allows you to visit this class based on the Visitor pattern.
	virtual void AcceptVisitor(mwTPSFitVisitor& visitor) const = 0;
	/// Push the new move to the end of the section.
	void PushBack(const movePtr& newMove) { push_back(newMove); }
	/// Removes the specified range of moves (first...last) from the sequence.
	virtual OverMovesIterator EraseMoves(OverMovesIterator first, OverMovesIterator last)
	{
		return erase(first, last);
	}
	/// Checks whether 2 section fits are equal
	///
	/// @param toCompare section to compare against
	///	@returns <b>true</b> if the sections equal, false otherwise
	const bool operator==(const mwTPSectionFit& toCompare) const
	{
		if (&toCompare == this)
			return true;

		return mwMovesAccessor<std::list<movePtr>>::operator==(toCompare);
	}
	/// Checks whether 2 section fits are unequal
	const bool operator!=(const mwTPSectionFit& toCompare) const { return !((*this) == toCompare); }
	///	Checks whether 2 sections have the same structure and equivalent moves.
	///
	/// As well as comparing the structures, it tests whether the distances between the positions of
	/// the moves are within tolerance and whether the difference between the tool orientation
	/// vectors is not more than minCos.
	///		@param toCompare is the section that will be compared with the current section.
	///		@param delta is the tolerance.
	///		@param minCos is the minimal cosine of the angle between the moves.
	const bool ExactCompareTolerance(
		const mwTPSectionFit& toCompare, double delta, double minCos) const
	{
		if (&toCompare == this)
			return true;

		return mwMovesAccessor<std::list<movePtr>>::ExactCompareTolerance(toCompare, delta, minCos);
	}
	/// Checks whether 2 sections have the same structure and equivalent moves.
	///
	/// As well as comparing the structures, it tests whether the distances between the positions of
	/// the moves are within tolerance and whether the difference between the tool orientation
	/// vectors is not more than minCos. It marks moves that do not satisfy these conditions
	///	@param toCompare is the section that will be compared with the current section.
	///	@param delta is the tolerance.
	///	@param minCos is the minimal cosine of the angle between moves.
	/// @param markersMap merkers' map
	bool ExactCompareToleranceMark(
		const mwTPSectionFit& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap) const
	{
		int nbDifferences = 0;
		return ExactCompareToleranceMark(toCompare, delta, minCos, markersMap, 0, nbDifferences);
	}

	bool ExactCompareToleranceMark(
		const mwTPSectionFit& toCompare,
		double delta,
		double minCos,
		GenericMarkersMap& markersMap,
		const int maxNbDifferences,
		int& nbDifferences) const
	{
		if (&toCompare == this)
			return true;

		return mwMovesAccessor<std::list<movePtr>>::ExactCompareToleranceMark(
			toCompare, delta, minCos, markersMap, maxNbDifferences, nbDifferences);
	}
	/// Deep-copy a given tp section fit into this object.
	/// @param toCopy is the input tp section fit which will be deep-copied in this object.
	void DeepCopy(const mwTPSectionFit& toCopy)
	{
		clear();

		for (ConstOverMovesIterator It = toCopy.GetMovesBegin(); It != toCopy.GetMovesEnd(); ++It)
		{
			movePtr move;
			mwMoveDeepCopy moveDeepCopy(move);
			(*It)->AcceptVisitor(moveDeepCopy);

			push_back(move);
		}
	}

protected:
	virtual void AssureSpace4Move(){};
	friend class misc::mwCollectionOfContainers<std::list<misc::mwAutoPointer<mwTPSectionFit>>>;
};
}  // namespace cadcam
#endif  //	MW_MWTPSECTIONFIT_HPP_
